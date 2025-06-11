//
// Created by Magnesium on 2023/7/19.
//
#pragma once

#include <string>
#include <cmath>
#include <utility>
#include <cassert>
#include <optional>

#include <nlohmann/json.hpp>

#include "Node.h"
#include "../basic/Token.h"
#include "../basic/Error.h"

namespace hdg {
    using std::vector;
    using std::optional;
    using std::nullopt;

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

        virtual std::string toString() override;
        virtual Object* interpret() override;
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

        const Token& getOper() const { return m_oper; }
        uNode& getLeft() { return m_left; }
        uNode& getRight() { return m_right; }

        virtual nlohmann::json toJSON() const override;

        virtual std::string toString() override;
        virtual Object* interpret() override;
        virtual void accept(Visitor& visitor) override; 
    };

    /**
     * 后缀结点
     * 
     * 该结点是“后缀表达式”的 AST 实现。譬如，对于表达式：
     * 
     * ```hdg
     * list[1]
     * ```
     * 
     * 它会被 PostfixNode 构建为下面的样子：
     * 
     * ```YAML
     * __class__ : PostfixNode
     * type   : Token::LBRACKET
     * primary: 
     *     __class__: IdentNode
     *     ident    : "list"
     * args : 
     *     - __class__: IntNode
     *       value    : 1
     * ```
     * 
     * 以上面的表达式为例，可以归纳出 PostfixNode 的三个基本要素：
     * 
     * 1. 后缀类型 type   ：用来标记进行后缀运算的类型，圆括号运算符、方括号运算符、花括号运算符、点号运算符
     * 2. 运算主体 primary：执行后缀运算的主体对象。例如，对于 list[1]，它的运算对象就是 list。
     * 3. 运算参数 args   ：执行后缀运算的参数。
     * 
     * 因此，在海琛中，三类括号运算符内部都能够同时传入多个值。
     * 
     * 但点号运算符比较特别。它只能传入一个 IdentNode 类型的结点作为参数。例如：
     * 
     * ```hdg
     * list.len
     * ```
     * 
     * 上面的表达式会被解析成下面的样子：
     * 
     * ```YAML
     * __class__ : PostfixNode
     * type   : Token::DOT
     * primary: 
     *     __class__: IdentNode
     *     ident    : "list"
     * args : 
     *     - __class__: IdentNode
     *       ident    : "len"
     * ```
     * 
     * 那么，海琛是怎么实现调用对象的方法的？海琛的解决方案是链式调用。
     * 
     * 例如下面的代码：
     * 
     * ```hdg
     * list.append(1)
     * ```
     * 
     * 它会被解析为：
     * 
     * ```YAML
     * __class__ : PostfixNode
     * type   : Token::LPAREN
     * primary: 
     *     __class__ : PostfixNode
     *     type   : Token::DOT
     *     primary: 
     *         __class__: IdentNode
     *         ident    : "list"
     *     args : 
     *         - __class__: IdentNode
     *         ident    : "append"
     * args : 
     *     - __class__: IntNode
     *       ident    : 1
     * ```
    */
    class PostfixNode; 
    typedef std::unique_ptr<PostfixNode> uPostfixNode;

    class PostfixNode: public Node{
    public:
        enum Type{
            PAREN,   // 圆括号()
            BRACKET, // 方括号[]
            BRACE,   // 花括号{}
            DOT      // 点号  .
        };

    protected:
        Type m_new_type;
        Token::Type m_type;
        uNode m_primary;
        std::string m_ident;
        std::vector<uNode> m_exprList;

    public:
        // PostfixNode(Token::Type type, std::string ident, const Position& pos);
        PostfixNode(Token::Type type, uNode&& primary, std::string ident, std::vector<uNode>&& exprList, const Position& pos);
        PostfixNode(Token::Type type, uNode&& primary, std::string ident, std::vector<uNode>&& exprList);
        PostfixNode(Token::Type type, uNode&& primary, std::vector<uNode>&& exprList, const Position& pos);
        PostfixNode(Token::Type type, uNode&& primary, std::vector<uNode>&& exprList);

        PostfixNode(Type type, uNode&& primary, vector<uNode>&& args, Position pos);

        static optional<uPostfixNode> from(uNode&& node);
        
        static uPostfixNode createParen(uNode&& primary, vector<uNode> args, optional<Position> pos = nullopt);
        static uPostfixNode createBracket(uNode&& primary, vector<uNode> args, optional<Position> pos = nullopt);
        static uPostfixNode createBrace(uNode&& primary, vector<uNode> args, optional<Position> pos = nullopt);
        static uPostfixNode createDot(uNode&& primary, const std::string& ident, optional<Position> pos = nullopt);
        
        inline std::vector<uNode>& getExprList() { return m_exprList; }
        inline uNode& getPrimary() { return m_primary; }
        inline std::string getIdent() { return m_ident; }
        inline Token::Type getType() { return m_type; }

        virtual nlohmann::json toJSON() const override;
        virtual std::string toString() override;
        virtual Object* interpret() override { assert(false); return nullptr; }
        virtual void accept(Visitor& visitor) override;
    };

} // hdg

