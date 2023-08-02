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

        Node* result = expr();

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

    Node* Parser::expr() {
        if (TokenType::IDENTIFIER == m_currentToken->getType()){
            std::string name = m_currentToken->getValue();
            int posStart = m_currentToken->thisPosition()->getPosStart(),
                posEnd = -1;
            advance();

            if (m_currentToken->getType() == TokenType::EQ){
                advance();

                Node* exprNode = expr();
                posEnd = exprNode->thisPosition()->getPosEnd();

                return new VariableAssignNode(
                        name,
                        exprNode,
                        Position(m_currentToken->thisPosition()->thisContext(), posStart, posEnd),
                        m_environment
                        );
            }
            else {
                retreat();
            }
        }

        return binaryOperator(
            std::set<Token, std::less<>>{{KEYWORD, "or"}, {KEYWORD, "and"}},
            [this](){return this->compExpr();}
        );
    }

    Node *Parser::compExpr() {
        if (m_currentToken->match(KEYWORD, "not")){
            Token token(*m_currentToken);
            advance();
            Node* obj = compExpr();

            return new UnaryOperatorNode(
                    token,
                    obj,
                    Position(token.thisPosition()->thisContext(), token.thisPosition()->getPosStart(), obj->thisPosition()->getPosEnd())
                    );
        }
        return binaryOperator(
                std::set<Token, std::less<>>{{EE}, {GT}, {LT}, {GTE}, {LTE}},
                [this](){return this->arithExpr();});
    }

    Node *Parser::arithExpr() {
        return binaryOperator(
                std::set<Token, std::less<>>{{PLUS}, {MINUS}},
                [this](){return this->term();}
        );
    }

    Node *Parser::term() {
        return binaryOperator(
                std::set<Token, std::less<>>{{MUL}, {DIV}},
                [this](){return this->factor();}
                );
    }

    Node *Parser::factor() {
        return binaryOperator(
                std::set<Token, std::less<>>{{POW}},
                [this](){return this->power();},
                [this](){return this->factor();}
                );
    }

    Node *Parser::power() {

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
            Node* obj = power();

            return new UnaryOperatorNode(
                    oper,
                    obj,
                    Position(oper.thisPosition()->thisContext(), oper.thisPosition()->getPosStart(), obj->thisPosition()->getPosEnd())
                    );
        }
        else if (m_currentToken->getType() == LPAREN){
            advance();
            Node* node = expr();

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
                    m_environment
                    );

            advance();
            return node;
        }
        else if (m_currentToken->match(KEYWORD, "if")){
            return ifExpr();
        }
        else if (m_currentToken->match(KEYWORD, "for")){
            return forExpr();
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

    Node *Parser::ifExpr() {
        IfNode *ifNode = new IfNode(
                Position(m_currentToken->thisPosition()->thisContext(), m_currentToken->thisPosition()->getPosStart()),
                m_environment);
        Node *condition, *expression;

        while(m_currentToken != m_tokens.end() && (m_currentToken->match(KEYWORD, "if") || m_currentToken->match(KEYWORD, "elif"))){
            advance();
            condition = expr();

            if (m_currentToken->getType() != COLON){
                throw InvalidSyntaxError(
                        "Expected ':'.",
                        *m_currentToken->thisPosition()
                        );
            }
            advance();

            expression = expr();
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

            ifNode->addBranch(nullptr, expr());
        }

        return ifNode;
    }

    Node *Parser::forExpr() {
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

        node = expr();

        position.setPosEnd(node->thisPosition()->getPosEnd());

        return new ForNode(index, from, to, step, node, position, m_environment);
    }

    Node *Parser::binaryOperator(const std::set<Token, std::less<>>&opers, std::function<Node*()> funA, std::function<Node*()> funB) {
        if (funB == nullptr) funB = funA;
        Node* left = funA();

        while(m_tokens.end() != m_currentToken && opers.find(*m_currentToken) != opers.end()){
            BinaryOperatorNode* oper = new BinaryOperatorNode(
                    *m_currentToken,
                    nullptr,
                    nullptr,
                    Position(m_currentToken->thisPosition()->thisContext(), left->thisPosition()->getPosStart())
                    );
            advance();

            Node* right = funB();

            oper->setLeft(left);
            oper->setRight(right);
            oper->thisPosition()->setPosEnd(right->thisPosition()->getPosEnd());
            left = oper;
        }

        return left;
    }

    Node *Parser::unaryOperator(const std::set<Token>&opers, std::function<Node*()> fun) {
        Node* node;

        Token oper(*m_currentToken);
        Position currentPos(*m_currentToken->thisPosition());

        advance();
        Node* obj = fun();

        node = new UnaryOperatorNode(
                oper,
                obj,
                Position(currentPos.thisContext(), currentPos.getPosStart(), obj->thisPosition()->getPosEnd())
                );
        return node;
    }



} // hdg