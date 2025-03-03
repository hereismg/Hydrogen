//
// Created by Magnesium on 2023/7/11.
//

#include "../../include/kernel/Lexer.h"
#include "../../include/basic/Error.h"
#include <cassert>

namespace hdg {

    int whatIsThis(char c){
        int res = 0;

        if (c>='0' && c<='9')    res |= DIGITAL;
        if (c>='0' && c<='9' ||
            c>='a' && c<='f' ||
            c>='A' && c<='F')    res |= HEX_DIGITAL;
        if (c>='a' && c<='z')    res |= LOWERCASE;
        if (c>='A' && c<='Z')    res |= UPPERCASE;
        if (c=='_')              res |= UNDERLINE;
        if (c==' ')              res |= BLANK;

        return res;
    }

    bool whatIsThis(char c, int target){
        int what = whatIsThis(c);
        return what & target;
    }

    AbstractStatus::AbstractStatus(StatusMachine *machine): m_machine(machine) {}

    void AbstractStatus::addEdge(int c, StatusType type, const std::function<bool(char)>& cond) {
        m_edges.emplace_back(c, type, cond);
    }

    bool AbstractStatus::accept(char cur) {
        int type = whatIsThis(cur);

        // 遍历当前节点的邻居节点
        for (auto & e : m_edges){
            bool cond = true;
            auto condFun = std::get<2>(e);
            if (condFun != nullptr) cond = condFun(cur);

            if (type & std::get<0>(e) && cond) {
                m_machine->move(std::get<1>(e));

                if (std::get<1>(e) == StatusType::ERROR ||
                    std::get<1>(e) == StatusType::ACCEPT)
                {
                    return true;
                }else {
                    return false;
                }
            }
        }

        // 若程序来到此处，则说明当前状态有无法处理的字符类型，必须要处理！
        assert(false);
    }

    StartStatus::StartStatus(StatusMachine *machine) : AbstractStatus(machine) {
        addEdge(LOWERCASE | UPPERCASE, StatusType::KEYWORD);
        addEdge(UNDERLINE,             StatusType::IDENT);
        addEdge(DIGITAL,               StatusType::INT_CONST);
        addEdge(BLANK,                 StatusType::START);
    }

    KeywordStatus::KeywordStatus(StatusMachine *machine) : AbstractStatus(machine) {
        keywordSet.insert({
            "not",
            "and",
            "or",

            "if",
            "elif",
            "else",

            "for",
            "from",
            "to",
            "step",
            "while",

            "function",
        });

        addEdge(LOWERCASE | UPPERCASE, StatusType::KEYWORD);
        addEdge(DIGITAL | UNDERLINE, StatusType::IDENT);
        addEdge(BLANK, StatusType::ACCEPT, [this](char c){
            auto txt  = this->m_machine->getTokenVal();
            if(keywordSet.find(txt) == keywordSet.end()){
                m_machine->move(StatusType::IDENT);
            }
            return true;
        });
    }

    IdentStatus::IdentStatus(hdg::StatusMachine *machine): AbstractStatus(machine) {
        addEdge(DIGITAL | LOWERCASE | UPPERCASE | UNDERLINE, StatusType::IDENT);
        addEdge(BLANK, StatusType::ACCEPT);
    }

    IntConstStatus::IntConstStatus(hdg::StatusMachine *machine): AbstractStatus(machine) {
        addEdge(DIGITAL, StatusType::INT_CONST);
        addEdge(BLANK, StatusType::ACCEPT);
        addEdge(OTHER, StatusType::ERROR);
    }

    ErrorStatus::ErrorStatus(hdg::StatusMachine *machine): AbstractStatus(machine) {}

    bool ErrorStatus::accept(char cur) {
        auto lastStatus = m_machine->getLastStatus();

        if (lastStatus == StatusType::INT_CONST){
            throw IllegalCharError(
                    "Expect digital.",
                    Position()
            );
        }else{
            // 若程序在此处，则说明有某种异常没有处理！
            assert(false);
        }

        return true;
    }


    AcceptStatus::AcceptStatus(StatusMachine *machine) : AbstractStatus(machine) {

    }

    bool AcceptStatus::accept(char cur) {
        m_machine->setCurrToken(m_machine->getLastStatus());
        return false;
    }

    StatusMachine::StatusMachine():
    m_lastStatus(StatusType::START),
    m_currStatus(StatusType::START),
    m_list(static_cast<int>(StatusType::ERROR), nullptr),
    m_currChar(' ')
    {
        m_list[static_cast<int>(StatusType::START)]     = new StartStatus(this);
        m_list[static_cast<int>(StatusType::KEYWORD)]   = new KeywordStatus(this);
        m_list[static_cast<int>(StatusType::IDENT)]     = new IdentStatus(this);
        m_list[static_cast<int>(StatusType::INT_CONST)] = new IntConstStatus(this);

        m_list[static_cast<int>(StatusType::ACCEPT)]    = new AcceptStatus(this);
        m_list[static_cast<int>(StatusType::ERROR)]     = new AcceptStatus(this);
    }

    StatusMachine::~StatusMachine() {
        for (auto i: m_list){
            delete i;
        }
    }

    std::string StatusMachine::getTokenVal() {
        return m_tokenVal;
    }

    void StatusMachine::move(StatusType target) {
        m_tokenVal.push_back(m_currChar);
        m_lastStatus = m_currStatus;
        m_currStatus = target;
    }

    std::shared_ptr<StatusType> StatusMachine::accept(char c) {
        // 状态机的主要工作如下：
        // 首先更新状态机的 m_currChar，方便操作。
        // 其次，调用当前状态的 accept 方法，传入字符
        // 状态发生改变以后，若返回值为 true，则说明不需要传入新的字符串，再进入到下一个状态中
        assert(m_list[static_cast<int>(m_currStatus)] != nullptr);
        m_currChar = c;
        while(m_list[static_cast<int>(m_currStatus)]->accept(c));

        // 若生成了新的 Token，那么先保存新生成的 Token，在初始化状态机，最后返回新 Token
        if (m_token == nullptr) {
            return nullptr;
        }
        else {
            auto temp = m_token;
            init();
            return temp;
        }
    }

    StatusType StatusMachine::getLastStatus() {
        return m_lastStatus;
    }

    void StatusMachine::init() {
        m_tokenVal.clear();
        m_currStatus = StatusType::START;
        m_lastStatus = StatusType::START;
        m_token = nullptr;
    }

    void StatusMachine::setCurrToken(StatusType type) {
        m_token = std::make_shared<StatusType>(type);
    }

    std::ostream& operator<<(std::ostream& out, std::vector<Token>& tokens) {
        if (tokens.empty()){
            out << "NONE";
        }else{
            out << "[";

            for (int i=0; i<tokens.size()-1; i++) {
                out << tokens[i] << ", ";
            }

            out << tokens[tokens.size()-1] << "]";
        }
        return out;
    }

    Lexer::Lexer(): m_pos(0, 0, 0){}

    std::string Lexer::getFilePath() {
        return m_fPath;
    }

    /**
     * @details     初始化函数，运行函数时，会重置 m_pos 方法，并且重置 m_currentChar.
     * */
    void Lexer::init(){
        m_pos.index = 0;
        m_pos.line ++;      ///> 注意，这里不是初始化为1，而是自增一位。这是为了能够记录行数
        m_pos.col = 0;
        m_currentChar = (*m_code)[0];
        m_tokens.clear();
    }

    void Lexer::advance() {
        if (m_pos.index >= m_code->length()) return;
        m_pos.index++;
        m_pos.col++;
        m_currentChar = (*m_code)[m_pos.index];

        if (m_pos.index>0 && (*m_code)[m_pos.index - 1] == '\n') {
            m_pos.line++;
            m_pos.col = 0;
        }
    }

    std::string* Lexer::thisText() {
        return m_code;
    }

    std::vector<Token> Lexer::run(const std::string& fPath, std::string* code) {
        m_fPath = fPath;
        m_code = code;
        init();

        while (m_pos.index < m_code->length()){
            if (m_currentChar == ' ' || m_currentChar == '\t'){
                advance();
            }
            else if (whatIsThis(m_currentChar) == LegalChar::DIGITAL){
                buildNumber();
            }
            else if (whatIsThis(m_currentChar, LegalChar::UNDERLINE | LegalChar::UPPERCASE | LegalChar::LOWERCASE)){
                buildIdentifier();
            }
            else if (m_currentChar == '>'){
                buildGreaterThan();
            }
            else if (m_currentChar == '<'){
                buildLessThan();
            }
            else if (m_currentChar == '='){
                buildEquation();
            }
            else if (m_currentChar == '\"'){
                buildString();
            }
            else if (m_currentChar == '\n' || m_currentChar == ';'){
                m_tokens.emplace_back(Token::EL, std::string(1,m_currentChar), Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '+'){
                m_tokens.emplace_back(Token::PLUS, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '-'){
                m_tokens.emplace_back(Token::MINUS, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '*'){
                m_tokens.emplace_back(Token::MUL , Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '/'){
                m_tokens.emplace_back(Token::DIV, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '%'){
                m_tokens.emplace_back(Token::MOD, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '^'){
                m_tokens.emplace_back(Token::POW, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '('){
                m_tokens.emplace_back(Token::LPAREN, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == ')'){
                m_tokens.emplace_back(Token::RPAREN, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '['){
                m_tokens.emplace_back(Token::LBRACKET, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == ']'){
                m_tokens.emplace_back(Token::RBRACKET, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '{'){
                m_tokens.emplace_back(Token::LBRACE, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == '}'){
                m_tokens.emplace_back(Token::RBRACE, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == ':'){
                m_tokens.emplace_back(Token::COLON, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else if (m_currentChar == ','){
                m_tokens.emplace_back(Token::COMMA, Position(m_fPath, m_code, m_pos));
                advance();
            }
            else{
                throw IllegalCharError(
                        "Expect digital, '+', '-', '*', '/' or '^'.",
                        Position(m_fPath, m_code, m_pos)
                        );
            }
        }
        m_tokens.emplace_back(Token::EF, Position(m_fPath, m_code, m_pos));

        return m_tokens;
    }

    void Lexer::buildNumber() {
        Position::Indicator posStart = m_pos;
        int counter = 0;
        Token::Type type = Token::INT;

        while(m_pos.index < m_code->length() && (whatIsThis(m_currentChar) == LegalChar::DIGITAL || m_currentChar == '.')) {
            if (m_currentChar == '.') {
                if (counter==1) break;
                type = Token::FLOAT;
                counter++;
            }
            advance();
        }

        m_tokens.emplace_back(type, m_code->substr(posStart.index, m_pos.index - posStart.index), Position(m_fPath, m_code, posStart, m_pos));
    }

    std::vector<Token>& Lexer::getTokens() {
        return m_tokens;
    }

    void Lexer::buildGreaterThan() {
        Position::Indicator posStart = m_pos;
        Token::Type type = Token::GT;

        advance();

        if (m_pos.index < m_code->length() && m_currentChar == '='){
            type = Token::GTE;
            advance();
        }

        m_tokens.emplace_back(type, "", Position(m_fPath, m_code, posStart, m_pos));
    }

    void Lexer::buildLessThan() {
        Position::Indicator posStart = m_pos;
        Token::Type type = Token::LT;

        advance();

        if (m_pos.index < m_code->length() && m_currentChar == '='){
            type = Token::LTE;
            advance();
        }

        m_tokens.emplace_back(type, "", Position(m_fPath, m_code, posStart, m_pos));
    }

    void Lexer::buildEquation() {
        Position::Indicator posStart = m_pos;
        Token::Type type = Token::EQ;

        advance();

        if (m_pos.index < m_code->length() && m_currentChar == '='){
            type = Token::EE;
            advance();
        }

        m_tokens.emplace_back(type, "", Position(m_fPath, m_code, posStart, m_pos));
    }

    void Lexer::buildIdentifier() {
        Position::Indicator posStart = m_pos;
        Token::Type type = Token::IDENTIFIER;

        advance();

        while(m_pos.index < m_code->size() && (whatIsThis(m_currentChar, LegalChar::DIGITAL | LegalChar::UPPERCASE | LegalChar::LOWERCASE | LegalChar::UNDERLINE))){
            advance();
        }

        std::string value = m_code->substr(posStart.index, m_pos.index - posStart.index);

        if (keywordSet.find(value) != keywordSet.end()) type = Token::KEYWORD;

        m_tokens.emplace_back(type, value, Position(m_fPath, m_code, posStart, m_pos));
    }

    void Lexer::buildString() {
        std::string str;
        Position pos(m_fPath, m_code, m_pos);
        advance();

        static std::map<char, char> transChar{
                {'n', '\n'},
                {'t', '\t'},
                {'\\', '\\'},
                {'\"', '\"'},
        };

        while (m_pos.index < m_code->size() && m_currentChar != '\"'){
            if (m_currentChar == '\\'){
                advance();
                auto trans = transChar.find(m_currentChar);
                if (trans != transChar.end()){
                    str += trans->second;
                }
                else{
                    str += ' ';
                }
            }else{
                str += m_currentChar;
            }
            advance();
        }
        advance();
        pos.setEnd(m_pos);

        m_tokens.emplace_back(Token::STRING, str, pos);
    }

} // hdg