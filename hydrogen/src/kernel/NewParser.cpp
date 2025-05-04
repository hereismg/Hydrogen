// #include "../../include/kernel/NewParser.h"

// namespace hdg_lexer{
//     Parser::Parser(const std::vector<Token>& tokens, wEnvir envir): 
//         m_tokens(tokens), m_ptr(0){}

//     std::unique_ptr<hdg::Node> Parser::run(){
//         if (m_tokens.empty()) return nullptr;
        
        
//     }


//     // 表达式
//     std::unique_ptr<hdg::Node> Parser::Expr(wEnvir envir){
//         if (m_tokens[m_ptr].getType() == TokenType::IDENT){

//         }
//     }

//     // 可复用函数
//     uNode Parser::binOper(
//         wEnvir envir,
//         const std::vector<Token>& opers,
//         std::function<uNode(wEnvir envir)> funA,
//         std::function<uNode(wEnvir envir)> funB=nullptr
//     ){
//         if (funB == nullptr) funB = funA;

//         // 解析左边的内容
//         uNode left = funA(envir);

//         // 运算符
//         for (auto oper : opers){
//             if (!oper.equal(m_tokens[m_ptr])) continue;

//             std::unique_ptr<hdg::BinaryOperatorNode> node(m_cur);
//         }
//     }
// }


