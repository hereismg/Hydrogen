//
// Created by Magnesium on 2023/7/19.
//

#include "../../include/node/BinaryOperatorNode.h"

#include <cassert>

#include "../../include/node/ObjectNode.h"

namespace hdg {

    BinaryOperatorNode::BinaryOperatorNode(const Token& oper, Node *left, Node *right, const Position& position):
        Node(position), m_oper(oper), m_left(left), m_right(right){}

    BinaryOperatorNode::BinaryOperatorNode(Token::Type oper, Node *left, Node *right, const Position& position, Environment* environment):
        Node(position, environment), m_oper(oper), m_left(left), m_right(right){}

    BinaryOperatorNode::~BinaryOperatorNode() = default;

    void BinaryOperatorNode::setOperator(const Token& oper){
        m_oper = oper;
    }

    void BinaryOperatorNode::setLeft(Node *node) {
        m_left = node;
    }

    void BinaryOperatorNode::setRight(Node *node) {
        m_right = node;
    }

    Token BinaryOperatorNode::getOperator() {
        return m_oper;
    }

    Node *BinaryOperatorNode::getLeft() {
        return m_left;
    }

    Node *BinaryOperatorNode::getRight() {
        return m_right;
    }

    std::string BinaryOperatorNode::toString() {
        if (m_left == nullptr && m_right == nullptr){
            return Token::TypeNameMap[m_oper.getType()];
        }else{
            return "(" + m_left->toString() + ", " + Token::TypeNameMap[m_oper.getType()] + ", " + m_right->toString() + ")";
        }
    }

    Object* BinaryOperatorNode::interpret() {
        Object* left = m_left->interpret();
//        if (left->getClass() == "None"){
//            throw RuntimeError(
//                "this is 'None'.",
//                *m_left->thisPosition()
//                    );
//        }
        Object* right = m_right->interpret();
//        if (right->getClass() == "None"){
//            throw RuntimeError(
//                    "this is 'None'.",
//                    *m_right->thisPosition()
//            );
//        }

        Object* result = nullptr;

        try{
            if (m_oper.getType() == Token::PLUS){
                result = left->plus(right);
            }
            else if (m_oper.getType() == Token::MINUS){
                result = left->minus(right);
            }
            else if (m_oper.getType() == Token::MUL){
                result = left->mul(right);
            }
            else if (m_oper.getType() == Token::DIV){
                result = left->div(right);
            }
            else if (m_oper.getType() == Token::MOD){
                result = left->mod(right);
            }
            else if (m_oper.getType() == Token::POW){
                result = left->pow(right);
            }
            else if (m_oper.getType() == Token::EE){
                result = left->equation(right);
            }
            else if (m_oper.getType() == Token::NE){
                result  = left->notEquation(right);
            }
            else if (m_oper.getType() == Token::GT){
                result = left->greaterThan(right);
            }
            else if (m_oper.getType() == Token::LT){
                result = left->lessThan(right);
            }
            else if (m_oper.getType() == Token::GTE){
                result = left->greaterThanEquation(right);
            }
            else if (m_oper.getType() == Token::LTE){
                result = left->lessThanEquation(right);
            }
            else if (m_oper.match(Token::KEYWORD, "and")){
                result = left->andOperator(right);
            }
            else if (m_oper.match(Token::KEYWORD, "or")){
                result = left->orOperator(right);
            }
            else{
                std::cout << "BinaryOperator::interpret(): Unknown token type.";
            }
        }
        catch (ZeroDivisionError& error){
            delete left;
            delete right;
            error.thisPosStack()->push_back(*m_right->thisPosition());
            throw error;
        }


        // delete left, right;
        return result;
    }

    BinOperNode::BinOperNode(Token oper, uNode&& left, uNode&& right, Position pos)
        : Node(pos),
          m_oper(std::move(oper)),
          m_left(std::move(left)),
          m_right(std::move(right))
    {
        assert(m_left  != nullptr && "Left Child cannot be null!");
        assert(m_right != nullptr && "Right Child cannot be null!");
    }

    BinOperNode::BinOperNode(Token oper, uNode&& left, uNode&& right)
        : m_oper(std::move(oper)),
          m_left(std::move(left)),
          m_right(std::move(right))
    {
        assert(m_left  != nullptr && "Left Child cannot be null!");
        assert(m_right != nullptr && "Right Child cannot be null!");
    }

    uBinOperNode BinOperNode::createPlus(int64_t num1, int64_t num2) {
        return std::make_unique<BinOperNode>(
            Token(Token::PLUS), 
            IntNode::create(num1),
            IntNode::create(num2)
        );
    }

    uBinOperNode BinOperNode::createPlus(uNode&& obj1, uNode&& obj2) {
        return std::make_unique<BinOperNode>(
            Token(Token::PLUS), 
            move(obj1),
            move(obj2)
        );
    }

    uBinOperNode BinOperNode::createMinus(int64_t num1, int64_t num2) {
        return std::make_unique<BinOperNode>(
            Token(Token::MINUS),
            IntNode::create(num1),
            IntNode::create(num2)
        );
    }

    uBinOperNode BinOperNode::createMinus(uNode&& obj1, uNode&& obj2) {
        return std::make_unique<BinOperNode>(
            Token(Token::MINUS),
            move(obj1),
            move(obj2)
        );
    }

    uBinOperNode BinOperNode::createMul(int64_t num1, int64_t num2) {
        return std::make_unique<BinOperNode>(
            Token(Token::MUL),
            IntNode::create(num1),
            IntNode::create(num2)
        );
    }
    
    uBinOperNode BinOperNode::createMul(uNode&& obj1, uNode&& obj2) {
        return std::make_unique<BinOperNode>(
            Token(Token::MUL),
            move(obj1),
            move(obj2)
        );
    }

    uBinOperNode BinOperNode::createDiv(int64_t num1, int64_t num2) {
        return std::make_unique<BinOperNode>(
            Token(Token::DIV),
            IntNode::create(num1),
            IntNode::create(num2)
        );
    }

    void BinOperNode::setOper(Token oper){
        m_oper = std::move(oper);
    }

    void BinOperNode::setLeft(uNode&& new_left){
        m_left = std::move(new_left);
    }

    void BinOperNode::setRight(uNode&& new_right){
        m_right = std::move(new_right);
    }
    
    nlohmann::json BinOperNode::toJSON() const {
        nlohmann::json j{ {"__class__", "BinOperNode"} };
        j["left"]  = m_left ->toJSON();
        j["oper"] = Token::TypeNameMap[m_oper.getType()];
        j["right"] = m_right->toJSON();
        
        return j;
    }

    std::string BinOperNode::toString(){
        std::stringstream context;
        // context << "{\n";

        return "BinOperNode";
    }

    Object* BinOperNode::interpret(){
        assert(false && "func 'interpret()' is deprecate!");
        return nullptr;
    }

    void BinOperNode::accept(Visitor& visitor) {
        visitor.visitBinOperNode(*this);
    }

    PostfixNode::PostfixNode(Type type, uNode&& primary, std::string ident, vector<uNode>&& args, optional<Position> pos)
        : m_new_type(type), m_primary(std::move(primary)), m_ident(std::move(ident)), m_exprList(std::move(args))
        {
            assert(m_primary != nullptr);
            if (pos.has_value()) m_position = pos.value();
        }

    uPostfixNode PostfixNode::createParen(uNode&& primary, vector<uNode> args, optional<Position> pos){
        assert(primary != nullptr);
        auto node = std::make_unique<PostfixNode> (
            PAREN,
            move(primary),
            "",
            move(args),
            pos
        );

        node->m_type = Token::LPAREN;

        return node;
    }

    uPostfixNode PostfixNode::createBracket(uNode&& primary, vector<uNode> args, optional<Position> pos){
        assert(primary != nullptr);
        auto node = std::make_unique<PostfixNode> (
            BRACKET,
            move(primary),
            "",
            move(args),
            pos
        );

        node->m_type = Token::LBRACKET;

        return node;
    }

    uPostfixNode PostfixNode::createDotFun(uNode&& primary, std::string ident, vector<uNode>&& args, optional<Position> pos){
        assert(primary != nullptr);
        auto node = std::make_unique<PostfixNode>(
            DOT_FUN, 
            move(primary), 
            move(ident), 
            move(args), 
            std::move(pos)
        );
        node->m_type = Token::DOT;
        return node;
    }

    uPostfixNode PostfixNode::createDotVar(uNode&& primary, std::string ident, optional<Position> pos) {
        assert(primary != nullptr);
        auto node = std::make_unique<PostfixNode>(
            DOT_FUN, 
            move(primary), 
            move(ident), 
            vector<uNode>(),
            std::move(pos)
        );

        node->m_type = Token::DOT;
        return node;
    }

    optional<uPostfixNode> PostfixNode::from(uNode&& node) {
        if (auto ptr = dynamic_cast<PostfixNode*>(node.get())) {
            node.release();
            return std::unique_ptr<PostfixNode>(ptr);
        }
        return nullopt;
    }

    nlohmann::json PostfixNode::toJSON() const {
        nlohmann::json j{
            {"__class__", "PostfixNode"},
            {"primary", m_primary->toJSON()},
            {"ident", m_ident}
        };

        j["exprList"] = nlohmann::json::array();

        for (auto& n : m_exprList) {
            j["exprList"].push_back(n->toJSON());
        }

        return j;
    }

    std::string PostfixNode::toString(){
        return "PostFixNode"; // hdgtodo: 更完整的输出 PostfixNode 内容
    }

    void PostfixNode::accept(Visitor& visitor) {
        visitor.visitPostfixNode(*this);
    }
} // hdg