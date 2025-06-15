//
// Created by Magnesium on 2023/7/11.
//

#include <cstring>
#include <cassert>

#include "../../include/basic/Token.h"

namespace hdg {

    Token::Token(){}

    Token::Token(Type type, std::string value, const Position &position):
        m_type(type), m_value(std::move(value)), m_position(position){
    }

    Token::Token(Type type, std::string value):
        m_type(type), m_value(std::move(value)){
    }

    Token::Token(Type type): m_type(type){}

    Token::Token(Type type, const Position &position):
        m_type(type), m_position(position){
    }

    Token::Token(const hdg::Token &tok) = default;

    Token::~Token() = default;

    std::ostream& operator<<(std::ostream &out, Token& tok) {
        out << tok.toString();
        return out;
    }

    Position* Token::thisPosition() {
        return &m_position;
    }

    nlohmann::json Token::toJSON() const {
        return {
                {"__class__", getClass()}, 
                {"type", hdg::Token::TypeNameMap[getType()]}, 
                {"value", getValue()}  // mgtodo: 很多时候，Token 的 value 都是空的，那么这就看起来很冗余，优化这一点
            };
    }

    std::string Token::toString() {
        return kv_toString(TypeNameMap[m_type].c_str(), 12, m_value, 128);
    }

    std::string kv_toString(const std::string& key, size_t keyShowLen, const std::string val, size_t valShowLen){
        assert(keyShowLen >= 4);
        assert(valShowLen >= 4);

        int buf_max = keyShowLen + 3 + valShowLen + 4;
        char *buf = new char[buf_max]{'\0'};

        // 0. 初始化
        // 后面 5 个字符固定，因此，在第 3 步中，buf_max 需要减去 5
        buf[buf_max-1] = '\0';
        buf[buf_max-2] = '.';
        buf[buf_max-3] = '.';
        buf[buf_max-4] = '.';
        buf[buf_max-5] = '\0';

        int buf_ptr = 0;

        // 1. key
        for (size_t i=0; i<keyShowLen; i++, buf_ptr++){
            if (i < key.size()){
                buf[buf_ptr] = key[i];
            }else{
                buf[buf_ptr] = ' ';
            }
        }

        // 2. 分割
        buf[buf_ptr++] = ' ';
        buf[buf_ptr++] = ':';
        buf[buf_ptr++] = ' ';

        // 3. value
        for (size_t i = 0; i<val.size() && buf_ptr < buf_max - 4; i++, buf_ptr++){
            switch (val[i]){
            case '\r':
                buf[buf_ptr] = '\\';
                buf_ptr ++;
                buf[buf_ptr] = 'r';
                break;
            case '\n':
                buf[buf_ptr] = '\\';
                buf_ptr ++;
                buf[buf_ptr] = 'n';
                break;
            case '\t':
                buf[buf_ptr] = '\\';
                buf_ptr ++;
                buf[buf_ptr] = 't';
                break;
            case '\0':
                buf[buf_ptr] = '\\';
                buf_ptr ++;
                buf[buf_ptr] = '0';
                break;
            default:
                buf[buf_ptr] = val[i];
                break;
            }
        }

        std::string res(buf);
        delete[] buf;
        return res;
    }

    bool operator<(const Token &left, const Token &right) {
        if (left.m_type == right.m_type){
            return left.m_value < right.m_value;
        }
        else {
            return left.m_type < right.m_type;
        }
    }
} // hdg