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
                    m_currentToken->thisPosition().getPosStart(),
                    m_tokens[m_tokens.size() - 1].thisPosition().getPosEnd(),
                    m_currentToken->thisPosition().getContext(),
                    "Expected '+', '-', '*', '/' or '^'."
            );
        }
        return result;
    }

    Node* Parser::expr() {
        if (m_currentToken->getType() == TokenType::IDENTIFIER){
            std::string name = m_currentToken->getValue();
            int posStart = m_currentToken->thisPosition().getPosStart(),
                posEnd = -1;
            advance();

            if (m_currentToken->getType() == TokenType::EQ){
                advance();

                Node* exprNode = expr();
                posEnd = exprNode->thisPosition().getPosEnd();

                return new VariableAssignNode(
                        name,
                        exprNode,
                        Position(m_currentToken->thisPosition().getContext(), posStart, posEnd),
                        m_environment
                        );
            }
            else {
                retreat();
                return binaryOperator(
                        std::set<TokenType>{PLUS, MINUS},
                        [this](){return this->term();}
                );
            }
        }
    }

    Node *Parser::compExpr() {
        return nullptr;
    }

    Node *Parser::arithExpr() {
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
        Node* node;

        if (m_currentToken->getType() == INT){
            node = new NumberNode(std::atoi(m_currentToken->getValue().c_str()), m_currentToken->thisPosition());
            advance();
        }
        else if (m_currentToken->getType() == FLOAT){
            node = new NumberNode((double)std::atof(m_currentToken->getValue().c_str()), m_currentToken->thisPosition());
            advance();
        }
        else if (m_currentToken->getType() == PLUS || m_currentToken->getType() == MINUS){
            TokenType token = m_currentToken->getType();
            Position currentPos(m_currentToken->thisPosition());

            advance();
            Node* obj = power();
            node = new UnaryOperatorNode(
                    token,
                    obj,
                    Position(currentPos.getContext(), currentPos.getPosStart(), obj->thisPosition().getPosEnd())
                    );
        }
        else if (m_currentToken->getType() == LPAREN){
            advance();
            node = expr();

            if (m_currentToken->getType() != RPAREN){
                throw InvalidSyntaxError(
                        m_currentToken->thisPosition().getPosStart(),
                        m_currentToken->thisPosition().getPosEnd(),
                        m_currentToken->thisPosition().getContext(),
                        "Expected ')'."
                        );
            }else{
                advance();
            }
        }
        else if (m_currentToken->getType() == TokenType::IDENTIFIER){
            Node* node = new VariableAccessNode(
                    m_currentToken->getValue(),
                    Position(m_currentToken->thisPosition().getContext(), m_currentToken->thisPosition().getPosStart(), m_currentToken->thisPosition().getPosEnd()),
                    m_environment
                    );

            advance();
            return node;
        }
        else {
            throw InvalidSyntaxError(
                    m_currentToken->thisPosition().getPosStart(),
                    m_currentToken->thisPosition().getPosEnd(),
                    m_currentToken->thisPosition().getContext(),
                    "Expected int, float, '+', '-' or '('."
                    );
        }
        return node;
    }

    Node *Parser::binaryOperator(const std::set<TokenType>&opers, std::function<Node*()> funA, std::function<Node*()> funB) {
        if (funB == nullptr) funB = funA;
        Node* left = funA();

        while(m_tokens.end() != m_currentToken && opers.find(m_currentToken->getType()) != opers.end()){
            BinaryOperatorNode* oper = new BinaryOperatorNode(
                    m_currentToken->getType(),
                    nullptr,
                    nullptr,
                    Position(m_currentToken->thisPosition().getContext(), left->thisPosition().getPosStart(), -1)
                    );
            advance();

            Node* right = funB();

            oper->setLeft(left);
            oper->setRight(right);
            oper->thisPosition().setPosEnd(right->thisPosition().getPosEnd());
            left = oper;
        }

        return left;
    }

    Node *Parser::unaryOperator() {
        return nullptr;
    }



} // hdg