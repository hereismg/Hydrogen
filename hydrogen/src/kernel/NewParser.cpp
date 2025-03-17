#include "../../include/kernel/NewParser.h"

namespace hdg_lexer{
    std::unique_ptr<hdg::Node> Parser::run(const std::vector<Token>& tokens, std::weak_ptr<hdg::Environment> envir){
        if (tokens.empty()) return nullptr;
    }
}


