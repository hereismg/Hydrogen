//
// Created by Magnesium on 2023/7/16.
//

#include "../include/Parser.h"

namespace hdg {
    Parser::Parser(std::vector<Token> tokens, Environment* environment):
            m_tokens(std::move(tokens)), m_currentToken(m_tokens.begin()), m_environment(environment){
    }

    void Parser::advance() {
        if (m_currentToken->getType() != Token::EF) m_currentToken++;
    }

    void Parser::retreat() {
        if (m_currentToken != m_tokens.begin()) m_currentToken--;
    }

    Node* Parser::run() {
        if (m_tokens.empty())return nullptr;

        Node* result = statements(m_environment);

        if (m_currentToken->getType() != Token::EF){
            throw InvalidSyntaxError(
                    "Expected '+', '-', '*', '/' or '^'.",
                    *m_currentToken->thisPosition()
                    );
        }

        return result;
    }

    Node *Parser::statements(Environment *environment) {
        if (m_currentToken->getType() == Token::EL || m_currentToken->getType() == Token::EF){
            return nullptr;
        }

        ///? 这里是否要加上一行 if (m_currentToken.getType() == LPAREN) ？
        auto* stats = new StatementsNode(*m_currentToken->thisPosition(), environment);

        if (m_currentToken->getType() == Token::LBRACE){
            advance();

            while (m_currentToken->getType() != Token::RBRACE){
                if (m_currentToken->getType() == Token::EL) {
                    advance();       ///> 去除多余的换行符
                    continue;
                }
                Node* node = expr(environment);
                if (node == nullptr) continue;
                stats->append(node);
            }
            stats->thisPosition()->setEnd(m_currentToken->thisPosition()->getEnd());
            advance();
        }
        else {
            while (m_currentToken->getType() != Token::EF){
                if (m_currentToken->getType() == Token::EL) {
                    advance();       ///> 去除多余的换行符
                    continue;
                }
                Node* node = expr(environment);
                stats->append(node);
            }
            stats->thisPosition()->setEnd(m_currentToken->thisPosition()->getEnd());
            advance();
        }

        return stats;
    }

    Node* Parser::expr(Environment* environment) {
        if (Token::IDENTIFIER == m_currentToken->getType()){
            std::string name = m_currentToken->getValue();
            Position pos(*m_currentToken->thisPosition());
            advance();

            if (m_currentToken->getType() == Token::EQ){
                advance();

                Node* obj = expr(environment);
                pos.setEnd(obj->thisPosition()->getEnd());

                return new ObjAssignNode(name, obj, pos, environment);
            }
            else {
                retreat();
            }
        }

        return binaryOperator(
                environment,
            std::set<Token, std::less<>>{{Token::KEYWORD, "or"}, {Token::KEYWORD, "and"}},
            [this](Environment* e){return this->compExpr(e);}
        );
    }

    Node *Parser::compExpr(Environment* environment) {
        if (m_currentToken->match(Token::KEYWORD, "not")){
            Token token(*m_currentToken);
            advance();
            Node* obj = compExpr(environment);
            Position position(*token.thisPosition());
            position.setEnd(obj->thisPosition()->getEnd());

            return new UnaryOperatorNode(token, obj, position, environment);
        }
        return binaryOperator(
                environment,
                std::set<Token, std::less<>>{{Token::EE}, {Token::GT}, {Token::LT}, {Token::GTE}, {Token::LTE}},
                [this](Environment* e){return this->arithExpr(e);});
    }

    Node *Parser::arithExpr(Environment* environment) {
        return binaryOperator(
                environment,
                std::set<Token, std::less<>>{{Token::PLUS}, {Token::MINUS}},
                [this](Environment* e){return this->term(e);}
        );
    }

    Node *Parser::term(Environment* environment) {
        return binaryOperator(
                environment,
                std::set<Token, std::less<>>{{Token::MUL}, {Token::DIV}, {Token::MOD}},
                [this](Environment* e){return this->factor(e);}
                );
    }

    Node *Parser::factor(Environment* environment) {
        if (m_currentToken->getType() == Token::PLUS || m_currentToken->getType() == Token::MINUS){
            return unaryOperator(
                    environment,
                    std::set<Token, std::less<>>{{Token::PLUS}, {Token::MINUS}},
                    [this](Environment* e){return this->factor(e);}
                    );
        }else{
            return power(environment);
        }
    }

    Node *Parser::power(Environment* environment) {
        return binaryOperator(
                environment,
                std::set<Token, std::less<>>{{Token::POW}},
                [this](Environment* e){return this->call(e);},
                [this](Environment* e){return this->factor(e);}
                );
    }

    Node *Parser::call(Environment *environment) {
        Node* node = atom(environment);

        if (m_currentToken->getType() == Token::LPAREN){
            auto* callNode = new CallNode(*node->thisPosition(), environment);
            advance();

            while (m_currentToken->getType() != Token::RPAREN){
                callNode->addNode(expr(environment));

                if (m_currentToken->getType() == Token::COMMA){
                    advance();
                    if (m_currentToken->getType()==Token::RPAREN){
                        throw InvalidSyntaxError(
                                "Expected int, float, plus, minus.",
                                *m_currentToken->thisPosition()
                                );
                    }
                }
            }

            if (m_currentToken->getType() == Token::RPAREN){
                callNode->setCall(node);
                callNode->setOperator(Token::LPAREN);
                callNode->thisPosition()->setEnd(m_currentToken->thisPosition()->getEnd());
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
        if (m_currentToken->getType() == Token::INT){
            Node *node = new NumObjNode((long long)std::atoi(m_currentToken->getValue().c_str()), *m_currentToken->thisPosition());
            advance();
            return node;
        }
        else if (m_currentToken->getType() == Token::FLOAT){
            Node* node = new NumObjNode((double)std::atof(m_currentToken->getValue().c_str()), *m_currentToken->thisPosition());
            advance();
            return node;
        }
        else if (m_currentToken->getType() == Token::STRING){
            Node* node = new StrObjNode(m_currentToken->getValue(), *m_currentToken->thisPosition(), environment);
            advance();
            return node;
        }
        else if (m_currentToken->getType() == Token::LPAREN){
            advance();
            Node* node = expr(environment);

            if (m_currentToken->getType() != Token::RPAREN){
                throw InvalidSyntaxError(
                        "Expected ')'.",
                        *m_currentToken->thisPosition());
            }else{
                advance();
            }

            return node;
        }
        else if (m_currentToken->getType() == Token::IDENTIFIER){
            Node* node = new ObjAccessNode(
                    m_currentToken->getValue(),
                    *m_currentToken->thisPosition(),
                    environment
            );

            advance();
            return node;
        }
        else if (m_currentToken->match(Token::KEYWORD, "if")){
            return ifExpr(environment);
        }
        else if (m_currentToken->match(Token::KEYWORD, "for")){
            return forExpr(environment);
        }
        else if (m_currentToken->match(Token::KEYWORD, "while")){
            return whileExpr(environment);
        }
        else if (m_currentToken->match(Token::KEYWORD, "function")){
            return funcExpr(environment);
        }
        else {
            throw InvalidSyntaxError(
                    "Expected identifier, int, float, '+', '-' or '('.",
                    *m_currentToken->thisPosition());
        }

    }

    /*
     * 注意：IfNode 的 Position 由 addBranch 函数维护，故在此只需要设定start即可。
     * */
    Node *Parser::ifExpr(Environment* environment) {
        auto *ifNode = new IfNode(
                Position(*m_currentToken->thisPosition()),
                environment);
        Node *condition;

        while(m_currentToken != m_tokens.end() && (m_currentToken->match(Token::KEYWORD, "if") || m_currentToken->match(Token::KEYWORD, "elif"))){
            advance();
            condition = expr(ifNode->thisEnvironment());

//            if (m_currentToken->getType() != Token::COLON){
//                throw InvalidSyntaxError(
//                        "Expected ':'.",
//                        *m_currentToken->thisPosition()
//                        );
//            }
//            advance();

            ifNode->addBranch(condition, core(ifNode->thisEnvironment()));
        }

        if (m_currentToken != m_tokens.end() && m_currentToken->match(Token::KEYWORD, "else")){
            advance();
//            if (m_currentToken->getType() != Token::COLON){
//                throw InvalidSyntaxError(
//                        "Expected ':'.",
//                        *m_currentToken->thisPosition()
//                );
//            }
//            advance();

            ifNode->addBranch(nullptr, core(ifNode->thisEnvironment()));
        }

        return ifNode;
    }

    Node *Parser::forExpr(Environment* environment) {
        Position position(*m_currentToken->thisPosition());
        Token index(Token::IDENTIFIER);
        auto* forNode = new ForNode(index, 0, -1, 1, nullptr, *m_currentToken->thisPosition(), environment);

        if (m_currentToken->match(Token::KEYWORD, "for")) advance();

        if (m_currentToken->getType() == Token::IDENTIFIER) forNode->setIndex({Token::IDENTIFIER, m_currentToken->getValue()});
        else throw InvalidSyntaxError(
                "Expected identifier.",
                *m_currentToken->thisPosition()
                );
        advance();

        if (m_currentToken->match(Token::KEYWORD, "from")){
            advance();

            int flag = 1;
            if (m_currentToken->getType() == Token::PLUS){
                advance();
            }
            if (m_currentToken->getType() == Token::MINUS) {
                flag = -1;
                advance();
            }


            if (m_currentToken->getType() != Token::INT){
                throw InvalidSyntaxError(
                        "Expected int.",
                        *m_currentToken->thisPosition()
                        );
            }

            forNode->setFrom(atoi(m_currentToken->getValue().c_str()) * flag);
            advance();
        }

        if (m_currentToken->match(Token::KEYWORD, "to")){
            advance();
            int flag = 1;

            if (m_currentToken->getType() == Token::PLUS){
                advance();
            }
            if (m_currentToken->getType() == Token::MINUS) {
                flag = -1;
                advance();
            }
            if (m_currentToken->getType() != Token::INT){
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

        if (m_currentToken->match(Token::KEYWORD, "step")){
            advance();
            int flag = 1;

            if (m_currentToken->getType() == Token::PLUS){
                advance();
            }
            if (m_currentToken->getType() == Token::MINUS) {
                flag = -1;
                advance();
            }


            if (m_currentToken->getType() != Token::INT){
                throw InvalidSyntaxError(
                        "Expected int.",
                        *m_currentToken->thisPosition()
                );
            }

            forNode->setStep(atoi(m_currentToken->getValue().c_str()) * flag);
            advance();
        }

        if (m_currentToken->getType() != Token::COLON){
            throw InvalidSyntaxError(
                    "Expected ':'.",
                    *m_currentToken->thisPosition()
                    );
        }
        advance();

        Node* body = core(forNode->thisEnvironment());
        forNode->setExpr(body);
        forNode->thisPosition()->setEnd(body->thisPosition()->getEnd());

        return forNode;
    }

    Node *Parser::whileExpr(Environment *environment) {
        WhileNode *node;
        node = new WhileNode(nullptr, nullptr, *m_currentToken->thisPosition(), environment);
        Node *condition, *body;

        if (m_currentToken->match(Token::KEYWORD, "while")) advance();

        condition = expr(node->thisEnvironment());

        body = core(node->thisEnvironment());
        node->thisPosition()->setEnd(body->thisPosition()->getEnd());
        node->setCondition(condition);
        node->setExpression(body);
        return node;
    }

    Node *Parser::funcExpr(hdg::Environment *environment) {
        auto* func = new FuncObjNode;
        Token name;
        func->thisEnvironment()->setParent(environment);
        func->thisPosition()->setStart(m_currentToken->thisPosition()->getStart());
        advance();

        if (m_currentToken->getType() == Token::IDENTIFIER){
            name = *m_currentToken;
            advance();
        }else{
            throw InvalidSyntaxError(
                    "Expected identifier.",
                    *m_currentToken->thisPosition()
            );
        }

        if (m_currentToken->getType() == Token::LPAREN){
            advance();
        }else{
            throw InvalidSyntaxError(
                    "Expected '('",
                    *m_currentToken->thisPosition()
            );
        }

        while (m_tokens.end() != m_currentToken && m_currentToken->getType() == Token::IDENTIFIER){
            Position pos(*m_currentToken->thisPosition());
            std::string argName = m_currentToken->getValue();
            Node* argExpr = nullptr;
            advance();

            if (m_currentToken->getType() == Token::EQ){
                advance();
                argExpr = expr(func->thisEnvironment());
                pos.setEnd(argExpr->thisPosition()->getEnd());
            }
            func->setArg(new ObjAssignNode(argName, argExpr, pos, func->thisEnvironment()));

            if (m_currentToken->getType() == Token::COMMA) {
                advance();
                if (m_currentToken->getType()!=Token::IDENTIFIER)
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

        if (m_currentToken->getType() == Token::RPAREN){
            advance();
        }else{
            throw InvalidSyntaxError(
                    "Expected ',' or ')'",
                    *m_currentToken->thisPosition()
            );
        }

        Node* body = core(func->thisEnvironment());
        func->setBody(body);
        func->thisPosition()->setEnd(body->thisPosition()->getEnd());
        func->setName(name.getValue());
        return new ObjAssignNode(name.getValue(), func, *func->thisPosition(), environment);
//
//        if (m_currentToken->getType() == Token::COLON){
//            advance();
//
//            Node* body = expr(func->thisEnvironment());
//            func->setBody(body);
//            func->thisPosition()->setEnd(body->thisPosition()->getEnd());
//            func->setName(name.getValue());
//
//            return new ObjAssignNode(name.getValue(), func, *func->thisPosition(), environment);
//        }
//        else if (m_currentToken->getType() == Token::LBRACE){
//            Environment* e = func->thisEnvironment();
//            Node* body = statements(e);
//            func->thisPosition()->setEnd(body->thisPosition()->getEnd());
//            func->setBody(body);
//            func->setName(name.getValue());
//
//            return new ObjAssignNode(name.getValue(), func, *func->thisPosition(), environment);
//        }
//        else{
//            throw InvalidSyntaxError(
//                    "Expected ':'",
//                    *m_currentToken->thisPosition()
//                    );
//        }
    }

    Node *Parser::core(Environment *environment) {
        if (m_currentToken->getType() == Token::COLON){
            advance();
            Node* body = expr(environment);
            return body;
        }

        ///> 是否要 advance 跳过LBRACE？
        else if (m_currentToken->getType() == Token::LBRACE){
            Node* body = statements(environment);
            return body;
        }
        else{
            throw InvalidSyntaxError(
                    "Expected ':' or '{'",
                    *m_currentToken->thisPosition()
            );
        }
    }

    Node *Parser::binaryOperator(Environment* environment, const std::set<Token, std::less<>>&opers, std::function<Node*(Environment* envir)> funA, std::function<Node*(Environment* envir)> funB) {
        if (funB == nullptr) funB = funA;
        Node* left = funA(environment);

        while(opers.find(*m_currentToken) != opers.end()){
            BinaryOperatorNode *oper;
            oper = new BinaryOperatorNode(
                    *m_currentToken,
                    nullptr,
                    nullptr,
                    *m_currentToken->thisPosition()
            );
            advance();

            Node* right = funB(environment);

            oper->setLeft(left);
            oper->setRight(right);
            oper->thisPosition()->setEnd(right->thisPosition()->getEnd());
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
        currentPos.setEnd(obj->thisPosition()->getEnd());

        node = new UnaryOperatorNode(
                oper,
                obj,
                currentPos,
                environment
                );
        return node;
    }

} // hdg