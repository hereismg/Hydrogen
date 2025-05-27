//
// Created by Magnesium on 2023/7/19.
//

#ifndef HDG_BINARYOPERATORNODE_H
#define HDG_BINARYOPERATORNODE_H

#include <string>
#include <cmath>
#include <utility>
#include <cassert>
#include <nlohmann/json.hpp>

#include "Node.h"
#include "../basic/Token.h"
#include "../basic/Error.h"

namespace hdg {

    class BinaryOperatorNode: public Node{
    protected:
        Token m_oper;
        Node* m_left;
        Node* m_right;

        std::unique_ptr<Node> m_left_u;
        std::unique_ptr<Node> m_right_u;

    public:
        BinaryOperatorNode();
        BinaryOperatorNode(const Token& oper, Node* left, Node* right, const Position& position);
        BinaryOperatorNode(Token::Type oper, Node* left, Node* right, const Position& position, Environment* environment);
        ~BinaryOperatorNode() override;

        void setOperator(const Token& oper);
        void setLeft(Node* node);
        void setRight(Node* node);
        Token getOperator();
        Node* getLeft();
        Node* getRight();

        std::string toString() override;
        Object* interpret() override;
    };

    class BinOperNode: public Node{
    protected:
        Token m_oper;
        uNode m_left;
        uNode m_right;

    public:
        BinOperNode(Token oper, uNode&& left, uNode&& right);
        BinOperNode(Token oper, uNode&& left, uNode&& right, Position pos);
        
        ~BinOperNode() = default;

        BinOperNode(const BinOperNode&) = delete;
        BinOperNode& operator=(const BinOperNode&) = delete;
        
        BinOperNode(BinOperNode&&) noexcept = default;
        BinOperNode& operator=(BinOperNode&&) noexcept = default;

        void setOper(Token oper);
        void setLeft(uNode&& new_left);
        void setRight(uNode&& new_right);

        const Token& getOper() const;
        uNode& getLeft();
        uNode& getRight();

        virtual std::string toString();
        virtual Object* interpret();
        virtual void accept(Visitor& visitor);
    };

    class PostfixNode: public Node{
    protected:
        Token::Type m_type;
        uNode m_primary;
        std::string m_ident;
        std::vector<uNode> m_exprList;

    public:
        // PostfixNode(Token::Type type, std::string ident, const Position& pos);
        PostfixNode(Token::Type type, uNode&& primary, std::string ident, std::vector<uNode>&& exprList, const Position& pos);
        PostfixNode(Token::Type type, uNode&& primary, std::vector<uNode>&& exprList, const Position& pos);
        PostfixNode(Token::Type type, uNode&& primary, std::vector<uNode>&& exprList);

        inline std::vector<uNode>& getExprList() { return m_exprList; }
        inline uNode& getPrimary() { return m_primary; }
        inline std::string getIdent() {return m_ident; }
        inline Token::Type getType() { return m_type; }

        virtual std::string toString();
        virtual Object* interpret() { assert(false); }
        virtual void accept(Visitor& visitor);
    };

} // hdg

namespace nlohmann {
    template<>
    struct adl_serializer<hdg::BinOperNode> {
        // 将 Person 转为 JSON
        static void to_json(json& j, const hdg::BinOperNode& n) {
            j = json{
                {"__class__", "BinOperNode"}, 
                {"oper", "Plus"}, 
                {"left", "1"}, 
                {"right", "2"}
            };
        }
    };
}

#endif //HDG_BINARYOPERATORNODE_H
