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
            Position pos(*m_currentToken->thisPosition());
            advance();

            if (m_currentToken->getType() == TokenType::EQ){
                advance();

                Node* obj = expr(environment);
                pos.setPosEnd(obj->thisPosition()->getPosEnd());

                return new ObjAssignNode(name, obj, pos, environment);
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
        if (m_currentToken->getType() == PLUS || m_currentToken->getType() == MINUS){
            return unaryOperator(
                    environment,
                    std::set<Token, std::less<>>{{PLUS}, {MINUS}},
                    [this](Environment* e){return this->factor(e);}
                    );
        }else{
            return power(environment);
        }
    }

    Node *Parser::power(Environment* environment) {
        return binaryOperator(
                environment,
                std::set<Token, std::less<>>{{POW}},
                [this](Environment* e){return this->call(e);},
                [this](Environment* e){return this->factor(e);}
                );
    }

    Node *Parser::call(Environment *environment) {
        Node* node = atom(environment);

        if (m_currentToken->getType() == LPAREN){
            auto* callNode = new CallNode(*node->thisPosition(), environment);
            advance();

            while (m_currentToken->getType() != RPAREN){
                callNode->addNode(expr(environment));

                if (m_currentToken->getType() == COMMA){
                    advance();
                    if (m_currentToken->getType()==RPAREN){
                        throw InvalidSyntaxError(
                                "Expected int, float, plus, minus.",
                                *m_currentToken->thisPosition()
                                );
                    }
                }
            }

            if (m_currentToken->getType() == RPAREN){
                callNode->setCall(node);
                callNode->setOperator(LPAREN);
                callNode->thisPosition()->setPosEnd(m_currentToken->thisPosition()->getPosEnd());
                advance();
                return callNode;
            }else{
                throw InvalidSyntaxError(
                        "Expected ')'.",
                        *m_currentToken->thisPosition()
                        );
            }
        }
        else{
            return node;
        }
    }

    Node *Parser::atom(Environment *environment) {
        if (m_currentToken->getType() == INT){
            Node *node = new NumObjNode((long long)std::atoi(m_currentToken->getValue().c_str()), *m_currentToken->thisPosition());
            advance();
            return node;
        }
        else if (m_currentToken->getType() == FLOAT){
            Node* node = new NumObjNode((double)std::atof(m_currentToken->getValue().c_str()), *m_currentToken->thisPosition());
            advance();
            return node;
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
            Node* node = new ObjAccessNode(
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
        else if (m_currentToken->match(KEYWORD, "function")){
            return funcExpr(environment);
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
        Token index(IDENTIFIER);
        auto* forNode = new ForNode(index, 0, -1, 1, nullptr, *m_currentToken->thisPosition(), environment);

        if (m_currentToken->match(KEYWORD, "for")) advance();

        if (m_currentToken->getType() == IDENTIFIER) forNode->setIndex({IDENTIFIER, m_currentToken->getValue()});
        else throw InvalidSyntaxError(
                "Expected identifier.",
                *m_currentToken->thisPosition()
                );
        advance();

        if (m_currentToken->match(KEYWORD, "from")){
            advance();

            int flag = 1;
            if (m_currentToken->getType() ==PLUS){
                advance();
            }
            if (m_currentToken->getType() == MINUS) {
                flag = -1;
                advance();
            }


            if (m_currentToken->getType() != INT){
                throw InvalidSyntaxError(
                        "Expected int.",
                        *m_currentToken->thisPosition()
                        );
            }

            forNode->setFrom(atoi(m_currentToken->getValue().c_str()) * flag);
            advance();
        }

        if (m_currentToken->match(KEYWORD, "to")){
            advance();
            int flag = 1;

            if (m_currentToken->getType() ==PLUS){
                advance();
            }
            if (m_currentToken->getType() == MINUS) {
                flag = -1;
                advance();
            }

            if (m_currentToken->getType() != INT){
                throw InvalidSyntaxError(
                        "Expected int.",
                        *m_currentToken->thisPosition()
                );
            }

            forNode->setTo(atoi(m_currentToken->getValue().c_str()) * flag);
            advance();
        }
        else{
            throw InvalidSyntaxError(
                    "Expected 'to'.",
                    *m_currentToken->thisPosition()
                    );
        }

        if (m_currentToken->match(KEYWORD, "step")){
            advance();
            int flag = 1;

            if (m_currentToken->getType() ==PLUS){
                advance();
            }
            if (m_currentToken->getType() == MINUS) {
                flag = -1;
                advance();
            }


            if (m_currentToken->getType() != INT){
                throw InvalidSyntaxError(
                        "Expected int.",
                        *m_currentToken->thisPosition()
                );
            }

            forNode->setStep(atoi(m_currentToken->getValue().c_str()) * flag);
            advance();
        }

        if (m_currentToken->getType() != COLON){
            throw InvalidSyntaxError(
                    "Expected ':'.",
                    *m_currentToken->thisPosition()
                    );
        }
        advance();

        Node* node = expr(forNode->thisEnvironment());
        forNode->setExpr(node);
        forNode->thisPosition()->setPosEnd(node->thisPosition()->getPosEnd());

        return forNode;
    }

    Node *Parser::whileExpr(Environment *environment) {
        WhileNode *node;
        node = new WhileNode(nullptr, nullptr, *m_currentToken->thisPosition(), environment);
        Node *condition, *expression;

        if (m_currentToken->match(KEYWORD, "while")) advance();

        condition = expr(node->thisEnvironment());

        if (m_currentToken->getType() != COLON){
            throw InvalidSyntaxError(
                    "Expected ':'.",
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

    Node *Parser::funcExpr(hdg::Environment *environment) {
        auto* func = new FuncObjNode;
        Token name;
        func->thisEnvironment()->setParent(environment);
        func->thisPosition()->setPosStart(m_currentToken->thisPosition()->getPosStart());
        advance();

        if (m_currentToken->getType() == IDENTIFIER){
            name = *m_currentToken;
            advance();
        }else{
            throw InvalidSyntaxError(
                    "Expected identifier.",
                    *m_currentToken->thisPosition()
            );
        }

        if (m_currentToken->getType() == LPAREN){
            advance();
        }else{
            throw InvalidSyntaxError(
                    "Expected '('",
                    *m_currentToken->thisPosition()
            );
        }

        while (m_tokens.end() != m_currentToken && m_currentToken->getType() == IDENTIFIER){
            Position pos(*m_currentToken->thisPosition());
            std::string argName = m_currentToken->getValue();
            Node* argExpr = nullptr;
            advance();

            if (m_currentToken->getType() == EQ){
                advance();
                argExpr = expr(func->thisEnvironment());
                pos.setPosEnd(argExpr->thisPosition()->getPosEnd());
            }
            func->setArg(new ObjAssignNode(argName, argExpr, pos, func->thisEnvironment()));

            if (m_currentToken->getType() == COMMA) {
                advance();
                if (m_currentToken->getType()!=IDENTIFIER)
                    throw InvalidSyntaxError(
                            "Expected identifier.",
                            *m_currentToken->thisPosition()
                        );
                continue;
            }
            else {
                break;
            }
        }

        if (m_currentToken->getType() == RPAREN){
            advance();
        }else{
            throw InvalidSyntaxError(
                    "Expected ',' or ')'",
                    *m_currentToken->thisPosition()
            );
        }

        if (m_currentToken->getType() == COLON){
            advance();
        }else{
            throw InvalidSyntaxError(
                    "Expected ':'",
                    *m_currentToken->thisPosition()
                    );
        }
        Node* temp = expr(func->thisEnvironment());
        func->setBody(temp);
        func->thisPosition()->setPosEnd(temp->thisPosition()->getPosEnd());
        func->setName(name.getValue());

        return new ObjAssignNode(name.getValue(), func, *func->thisPosition(), environment);
    }

    Node *Parser::binaryOperator(Environment* environment, const std::set<Token, std::less<>>&opers, std::function<Node*(Environment* envir)> funA, std::function<Node*(Environment* envir)> funB) {
        if (funB == nullptr) funB = funA;
        Node* left = funA(environment);

        while(m_tokens.end() != m_currentToken && opers.find(*m_currentToken) != opers.end()){
            BinaryOperatorNode *oper;
            oper = new BinaryOperatorNode(
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

    Node *Parser::unaryOperator(Environment* environment, const std::set<Token, std::less<>>&opers, std::function<Node*(Environment* envir)> fun) {
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