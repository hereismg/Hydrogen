//
// Created by Magnesium on 2025/2/18.
//

#include <Token.h>
#include <Lexer.h>
#include <iostream>
using namespace std;

int main(){
    hdg::Lexer lexer;
    string code = "a = 1";
    auto tokens = lexer.run("<std>", &code);

    vector<hdg::Token::Type> expectedType = {hdg::Token::IDENTIFIER, hdg::Token::Type::EQ, hdg::Token::Type::INT, hdg::Token::Type::EF};
    for (int i=0; i<tokens.size(); i++){
        if (tokens[i].getType() != expectedType[i]){
            return -1;
        }
    }

    return 0;
}