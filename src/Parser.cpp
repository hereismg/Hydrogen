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
                std::set<TokenType>{PLUS, MINUS},
                [this](){return this->term();}
        );
    }

    Node *Parser::compExpr() {
        if (m_currentToken->match(TokenType::KEYWORD, "not")){
//            return unaryOperator();
        }
        return nullptr;
    }

    Node *Parser::arithExpr() {
        Node* node;
        if (m_currentToken->match(TokenType::KEYWORD, "not")){
        }
        return nullptr;
    }

    Node *Parser::term() {
        return binaryOperator(
                std::set<TokenType>{MUL, DIV},
                [this](){return this->factor();}
                );
    }

    Node *Parser::factor() {
        return binaryOperator(
                std::set<TokenType>{POW},
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
            return unaryOperator(std::set<TokenType>{PLUS, MINUS}, [this](){return this->power();});
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
        else {
            throw InvalidSyntaxError(
                    "Expected identifier, int, float, '+', '-' or '('.",
            {m_currentToken->thisPosition()->thisContext(),
                    m_currentToken->thisPosition()->getPosStart(),
                    m_currentToken->thisPosition()->getPosEnd()}
                    );
        }
    }

    Node *Parser::binaryOperator(const std::set<TokenType>&opers, std::function<Node*()> funA, std::function<Node*()> funB) {
        if (funB == nullptr) funB = funA;
        Node* left = funA();

        while(m_tokens.end() != m_currentToken && opers.find(m_currentToken->getType()) != opers.end()){
            BinaryOperatorNode* oper = new BinaryOperatorNode(
                    m_currentToken->getType(),
                    nullptr,
                    nullptr,
                    Position(m_currentToken->thisPosition()->thisContext(), left->thisPosition()->getPosStart(), -1)
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

    Node *Parser::unaryOperator(const std::set<TokenType>&opers, std::function<Node*()> fun) {
        Node* node;
        TokenType type = m_currentToken->getType();
        Position currentPos(*m_currentToken->thisPosition());

        advance();
        Node* obj = fun();

        node = new UnaryOperatorNode(
                type,
                obj,
                Position(currentPos.thisContext(), currentPos.getPosStart(), obj->thisPosition()->getPosEnd())
                );
        return node;
    }


} // hdg