//
// Created by Magnesium on 2023/7/16.
//

#include "../include/Parser.h"

namespace hdg {
    Parser::Parser(std::vector<Token> tokens, Environment* environment):
            m_tokens(std::move(tokens)), m_currentToken(m_tokens.begin()), m_environment(environment){
    }

    void Parser::advance() {
        if (m_currentToken->getType() != EF) m_currentToken++;
    }

    void Parser::retreat() {
        if (m_currentToken != m_tokens.begin()) m_currentToken--;
    }

    Node* Parser::run() {
        if (m_tokens.empty())return nullptr;

        Node* result = expr(m_environment);

        if (m_currentToken->getType() != EF){
            throw InvalidSyntaxError(
                    "Expected '+', '-', '*', '/' or '^'.",
                    {m_currentToken->thisPosition()->thisContext(),
                     m_currentToken->thisPosition()->getPosStart(),
                     m_currentToken->thisPosition()->getPosEnd()
                    });
        }

        return result;
    }

    Node* Parser::expr(Environment* environment) {
        if (TokenType::IDENTIFIER == m_currentToken->getType()){
            std::string name = m_currentToken->getValue();
            int posStart = m_currentToken->thisPosition()->getPosStart(),
                posEnd = -1;
            advance();

            if (m_currentToken->getType() == TokenType::EQ){
                advance();

                Node* exprNode = expr(environment);
                posEnd = exprNode->thisPosition()->getPosEnd();

                return new VariableAssignNode(
                        name,
                        exprNode,
                        Position(m_currentToken->thisPosition()->thisContext(), posStart, posEnd),
                        environment
                        );
            }
            else {
                retreat();
            }
        }

        return binaryOperator(
                environment,
            std::set<Token, std::less<>>{{KEYWORD, "or"}, {KEYWORD, "and"}},
            [this](Environment* e){return this->compExpr(e);}
        );
    }

    Node *Parser::compExpr(Environment* environment) {
        if (m_currentToken->match(KEYWORD, "not")){
            Token token(*m_currentToken);
            advance();
            Node* obj = compExpr(environment);

            return new UnaryOperatorNode(
                    token,
                    obj,
                    Position(token.thisPosition()->thisContext(), token.thisPosition()->getPosStart(), obj->thisPosition()->getPosEnd()),
                    environment
                    );
        }
        return binaryOperator(
                environment,
                std::set<Token, std::less<>>{{EE}, {GT}, {LT}, {GTE}, {LTE}},
                [this](Environment* e){return this->arithExpr(e);});
    }

    Node *Parser::arithExpr(Environment* environment) {
        return binaryOperator(
                environment,
                std::set<Token, std::less<>>{{PLUS}, {MINUS}},
                [this](Environment* e){return this->term(e);}
        );
    }

    Node *Parser::term(Environment* environment) {
        return binaryOperator(
                environment,
                std::set<Token, std::less<>>{{MUL}, {DIV}},
                [this](Environment* e){return this->factor(e);}
                );
    }

    Node *Parser::factor(Environment* environment) {
        return binaryOperator(
                environment,
                std::set<Token, std::less<>>{{POW}},
                [this](Environment* e){return this->power(e);},
                [this](Environment* e){return this->factor(e);}
                );
    }

    Node *Parser::power(Environment* environment) {

        if (m_currentToken->getType() == INT){
            Node *node = new NumberNode(std::atoi(m_currentToken->getValue().c_str()), *m_currentToken->thisPosition());
            advance();
            return node;
        }
        else if (m_currentToken->getType() == FLOAT){
            Node* node = new NumberNode((double)std::atof(m_currentToken->getValue().c_str()), *m_currentToken->thisPosition());
            advance();
            return node;
        }
        else if (m_currentToken->getType() == PLUS || m_currentToken->getType() == MINUS){
            Token oper = *m_currentToken;
            advance();
            Node* obj = power(environment);

            return new UnaryOperatorNode(
                    oper,
                    obj,
                    Position(oper.thisPosition()->thisContext(), oper.thisPosition()->getPosStart(), obj->thisPosition()->getPosEnd()),
                    environment
                    );
        }
        else if (m_currentToken->getType() == LPAREN){
            advance();
            Node* node = expr(environment);

            if (m_currentToken->getType() != RPAREN){
                throw InvalidSyntaxError(
                        "Expected ')'.",
                        {m_currentToken->thisPosition()->thisContext(),
                         m_currentToken->thisPosition()->getPosStart(),
                         m_currentToken->thisPosition()->getPosEnd()
                        });
            }else{
                advance();
            }

            return node;
        }
        else if (m_currentToken->getType() == TokenType::IDENTIFIER){
            Node* node = new VariableAccessNode(
                    m_currentToken->getValue(),
                    Position(m_currentToken->thisPosition()->thisContext(), m_currentToken->thisPosition()->getPosStart(), m_currentToken->thisPosition()->getPosEnd()),
                    environment
                    );

            advance();
            return node;
        }
        else if (m_currentToken->match(KEYWORD, "if")){
            return ifExpr(environment);
        }
        else if (m_currentToken->match(KEYWORD, "for")){
            return forExpr(environment);
        }
        else if (m_currentToken->match(KEYWORD, "while")){
            return whileExpr(environment);
        }
        else {
            throw InvalidSyntaxError(
                    "Expected identifier, int, float, '+', '-' or '('.",
            {m_currentToken->thisPosition()->thisContext(),
                    m_currentToken->thisPosition()->getPosStart(),
                    m_currentToken->thisPosition()->getPosEnd()}
                    );
        }
    }

    Node *Parser::ifExpr(Environment* environment) {
        IfNode *ifNode = new IfNode(
                Position(m_currentToken->thisPosition()->thisContext(), m_currentToken->thisPosition()->getPosStart()),
                m_environment);
        Node *condition, *expression;

        while(m_currentToken != m_tokens.end() && (m_currentToken->match(KEYWORD, "if") || m_currentToken->match(KEYWORD, "elif"))){
            advance();
            condition = expr(ifNode->thisEnvironment());

            if (m_currentToken->getType() != COLON){
                throw InvalidSyntaxError(
                        "Expected ':'.",
                        *m_currentToken->thisPosition()
                        );
            }
            advance();

            expression = expr(ifNode->thisEnvironment());
            ifNode->addBranch(condition, expression);
        }

        if (m_currentToken != m_tokens.end() && m_currentToken->match(KEYWORD, "else")){
            advance();
            if (m_currentToken->getType() != COLON){
                throw InvalidSyntaxError(
                        "Expected ':'.",
                        *m_currentToken->thisPosition()
                );
            }
            advance();

            ifNode->addBranch(nullptr, expr(ifNode->thisEnvironment()));
        }

        return ifNode;
    }

    Node *Parser::forExpr(Environment* environment) {
        Position position(*m_currentToken->thisPosition());
        ForNode* forNode;
        Token index(IDENTIFIER);
        int from = 0,
            to,
            step = 1;
        Node* node;

        if (m_currentToken->match(KEYWORD, "for")) advance();

        if (m_currentToken->getType() == IDENTIFIER) index.setValue(m_currentToken->getValue());
        else throw InvalidSyntaxError(
                "Expected identifier.",
                *m_currentToken->thisPosition()
                );
        advance();

        if (m_currentToken->match(KEYWORD, "from")){
            advance();

            if (m_currentToken->getType() != INT){
                throw InvalidSyntaxError(
                        "Expected int",
                        *m_currentToken->thisPosition()
                        );
            }

            from = atoi(m_currentToken->getValue().c_str());
            advance();
        }

        if (m_currentToken->match(KEYWORD, "to")){
            advance();

            if (m_currentToken->getType() != INT){
                throw InvalidSyntaxError(
                        "Expected int",
                        *m_currentToken->thisPosition()
                );
            }

            to = atoi(m_currentToken->getValue().c_str());
            advance();
        }
        else{
            throw InvalidSyntaxError(
                    "Expected 'to'",
                    *m_currentToken->thisPosition()
                    );
        }

        if (m_currentToken->match(KEYWORD, "step")){
            advance();

            if (m_currentToken->getType() != INT){
                throw InvalidSyntaxError(
                        "Expected int",
                        *m_currentToken->thisPosition()
                );
            }

            step = atoi(m_currentToken->getValue().c_str());
            advance();
        }

        if (m_currentToken->getType() != COLON){
            throw InvalidSyntaxError(
                    "Expected ':'",
                    *m_currentToken->thisPosition()
                    );
        }
        advance();

        node = expr(environment);

        position.setPosEnd(node->thisPosition()->getPosEnd());

        return new ForNode(index, from, to, step, node, position, environment);
    }

    Node *Parser::whileExpr(Environment *environment) {
        WhileNode* node = new WhileNode(nullptr, nullptr, *m_currentToken->thisPosition(), environment);
        Node *condition, *expression;

        if (m_currentToken->match(KEYWORD, "while")) advance();

        condition = expr(node->thisEnvironment());

        if (m_currentToken->getType() != COLON){
            throw InvalidSyntaxError(
                    "Expected ':'",
                    *m_currentToken->thisPosition()
            );
        }
        advance();

        expression = expr(node->thisEnvironment());
        node->thisPosition()->setPosEnd(expression->thisPosition()->getPosEnd());
        node->setCondition(condition);
        node->setExpression(expression);
        return node;
    }

    Node *Parser::binaryOperator(Environment* environment, const std::set<Token, std::less<>>&opers, std::function<Node*(Environment* envir)> funA, std::function<Node*(Environment* envir)> funB) {
        if (funB == nullptr) funB = funA;
        Node* left = funA(environment);

        while(m_tokens.end() != m_currentToken && opers.find(*m_currentToken) != opers.end()){
            BinaryOperatorNode* oper = new BinaryOperatorNode(
                    *m_currentToken,
                    nullptr,
                    nullptr,
                    Position(m_currentToken->thisPosition()->thisContext(), left->thisPosition()->getPosStart())
                    );
            advance();

            Node* right = funB(environment);

            oper->setLeft(left);
            oper->setRight(right);
            oper->thisPosition()->setPosEnd(right->thisPosition()->getPosEnd());
            left = oper;
        }

        return left;
    }

    Node *Parser::unaryOperator(Environment* environment, const std::set<Token>&opers, std::function<Node*(Environment* envir)> fun) {
        Node* node;

        Token oper(*m_currentToken);
        Position currentPos(*m_currentToken->thisPosition());

        advance();
        Node* obj = fun(environment);

        node = new UnaryOperatorNode(
                oper,
                obj,
                Position(currentPos.thisContext(), currentPos.getPosStart(), obj->thisPosition()->getPosEnd()),
                environment
                );
        return node;
    }



} // hdg