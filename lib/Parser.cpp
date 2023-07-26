//
// Created by Magnesium on 2023/7/16.
//

#include "Parser.h"

namespace hdg {
    Parser::Parser(std::vector<Token> tokens):
        tokens(std::move(tokens)), currentToken(this->tokens.begin()){
    }

    void Parser::advance() {
        if (currentToken->getType() != TT_EOF) currentToken++;
    }

    Node* Parser::run() {
        if (tokens.empty())return nullptr;

        Node* result = expr();

        if (currentToken->getType() != TT_EOF){
            throw InvalidSyntaxError(
                    currentToken->thisPosition().getPosStart(),
                    tokens[tokens.size()-1].thisPosition().getPosEnd(),
                    currentToken->thisPosition().getContext(),
                    "Expected '+', '-', '*', '/' or '^'"
            );
        }

        return result;
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
            node = new NumberNode(std::atoi(currentToken->getValue().c_str()), currentToken->thisPosition());
            advance();
        }
        else if (currentToken->getType() == TT_FLOAT){
            node = new NumberNode((float)std::atof(currentToken->getValue().c_str()), currentToken->thisPosition());
            advance();
        }
        else if (currentToken->getType() == TT_PLUS || currentToken->getType() == TT_MINUS){
            std::string token = currentToken->getType();
            Position currentPos(currentToken->thisPosition());

            advance();
            Node* obj = power();
            node = new UnaryOperatorNode(
                    token,
                    obj,
                    Position(currentPos.getContext(), currentPos.getPosStart(), obj->thisPosition().getPosEnd())
                    );
        }
        else if (currentToken->getType() == TT_LPAREN){
            advance();
            node = expr();
            advance();

            if (currentToken->getType() != TT_RPAREN){
                throw InvalidSyntaxError(
                        currentToken->thisPosition().getPosStart(),
                        currentToken->thisPosition().getPosEnd(),
                        currentToken->thisPosition().getContext(),
                        "Expected ')'."
                        );
            }
        }
        else {
            throw InvalidSyntaxError(
                    currentToken->thisPosition().getPosStart(),
                    currentToken->thisPosition().getPosEnd(),
                    currentToken->thisPosition().getContext(),
                    "Expected int, float, '+', '-' or '('."
                    );
        }
        return node;
    }

    Node *Parser::binaryOperator(const std::set<std::string>&opers, std::function<Node*()> funA, std::function<Node*()> funB) {
        if (funB == nullptr) funB = funA;
        Node* left = funA();

        while(tokens.end() != currentToken && opers.find(currentToken->getType())!=opers.end()){
            BinaryOperatorNode* oper = new BinaryOperatorNode(
                    currentToken->getType(),
                    nullptr,
                    nullptr,
                    Position(currentToken->thisPosition().getContext(), left->thisPosition().getPosStart(), -1)
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