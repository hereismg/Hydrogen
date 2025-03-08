//
// Created by Magnesium on 2023/7/16.
//


#ifndef HDG_PARSER_H
#define HDG_PARSER_H

#include <vector>
#include "../basic/Token.h"
#include "../node/Node.h"

namespace hdg {
    class Parser {
    protected:
        std::vector<Token> m_tokens;
        std::vector<Token>::iterator m_currentToken;
        Environment* m_environment;

    public:
        Parser(std::vector<Token> tokens, Environment* environment);
        Node* run();

    protected:
        void advance();
        void retreat();

        Node* expr      (Environment* environment);
        Node* compExpr  (Environment* environment);
        Node* arithExpr (Environment* environment);
        Node* term      (Environment* environment);
        Node* factor    (Environment* environment);
        Node* power     (Environment* environment);
        Node* call      (Environment* environment);
        Node* atom      (Environment* environment);
        Node* ifExpr    (Environment* environment);
        Node* forExpr   (Environment* environment);
        Node* whileExpr (Environment* environment);
        Node* funcExpr  (Environment* environment);
        Node* statements(Environment* environment);
        Node* core      (Environment* environment);

        Node* binaryOperator(
                Environment* environment,
                const std::set<Token, std::less<>>&opers,
                std::function<Node*(Environment* envir)> funA,
                std::function<Node*(Environment* envir)> funB=nullptr
                        );
        Node* unaryOperator(
                Environment* environment,
                const std::set<Token, std::less<>>&opers,
                std::function<Node*(Environment* envir)> fun
                );
    };

} // hdg

#endif //HDG_PARSER_H
