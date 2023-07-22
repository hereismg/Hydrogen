//
// Created by Magnesium on 2023/7/16.
//

#include "Parser.h"

namespace hdg {
    Parser::Parser(std::vector<Token> tokens):
        tokens(std::move(tokens)), currentToken(this->tokens.begin()){
    }

    void Parser::advance() {
        if (currentToken!=tokens.end()) currentToken++;
    }

    Node* Parser::run() {
        return expr();
    }

    Node* Parser::expr() {
        return binaryOperator(
                std::set<std::string>{TT_PLUS, TT_MINUS},
                [this](){return this->term();}
                );
    }

    Node *Parser::term() {
        return binaryOperator(
                std::set<std::string>{TT_MUL, TT_DIV},
                [this](){return this->factor();}
                );
    }

    Node *Parser::factor() {
        return binaryOperator(
                std::set<std::string>{TT_POW},
                [this](){return this->power();},
                [this](){return this->factor();}
                );
    }

    Node *Parser::power() {
        Node* node = nullptr;
        if (currentToken->getType() == TT_INT){
            node = new IntNode(std::atoi(currentToken->getValue().c_str()));
            advance();
        }
        else if (currentToken->getType() == TT_PLUS || currentToken->getType() == TT_MINUS){
            std::string token = currentToken->getType();
            advance();
            Node* obj = power();
            node = new UnaryOperatorNode(token, obj);
        }
        else if (currentToken->getType() == TT_LPAREN){
            advance();
            node = expr();
            advance();
        }
        return node;
    }

    Node *Parser::binaryOperator(const std::set<std::string>&opers, std::function<Node*()> funA, std::function<Node*()> funB) {
        if (funB == nullptr) funB = funA;
        Node* left = funA();

        while(tokens.end() != currentToken && opers.find(currentToken->getType())!=opers.end()){
            BinaryOperatorNode* oper = new BinaryOperatorNode(currentToken->getType());
            advance();

            Node* right = funB();

            oper->setLeft(left);
            oper->setRight(right);
            left = oper;
        }

        return left;
    }

    Node *Parser::unaryOperator() {
        return nullptr;
    }

} // hdg