//
// Created by Magnesium on 2023/7/14.
//

#include "../../include/kernel/Shell.h"

namespace hdg {
    void hydrogen(int argc, char* argv[]){
        std::string fPath;

        if (argc == 0){
            ShellController shell;
            shell.run();
        }
        else if (argc > 1){
            for (int i=1; i<argc; i++){
                if (strcmp(argv[i], "-g") == 0){

                }
                else{
                    fPath = argv[i];
                }
            }
        }
    }

    Shell::Shell(): m_mode(Interpreter::Mode::release) {}

    /**
     * @details     Shell 的运行分为 release 模式和 debug 模式。
     *              其中 debug 模式会在每次输入命令后打印出 tokens 列表与语法树，而 release 模式则会直接输出结果。
     *              默认情况下，以 release 模式启动 Shell。\n\n
     *              除此之外，如果输入文件路径，那么 Shell 会直接解析文件里的代码；否则直接进入到命令行。
     * */

    void Shell::exe(int argc, char* argv[]) {

        /// 读取传入的参数，并且解析传入的参数。
        int pos = 1;
        for (int i=1; i<argc; i++){
            if (std::string(argv[i]) == "-debug"){
                m_mode = Interpreter::Mode::debug;
            }
            else if(std::string(argv[i]) == "-release") {
                m_mode = Interpreter::Mode::release;
            }
            else{
                m_fPath = argv[i];
            }
        }

        /// 构建解释器，并且根据前面解析的结果进行特定的行为。
        Interpreter interpreter;
        std::string code;
        if (m_fPath.empty()){
            interpreter.thisEnvironment()->setFilePath("<stdin>");
            interpreter.thisEnvironment()->setModuleName("global");
            while(true){
                code = input();
                std::cout << interpreter.interpret("<stdin>", code, m_mode) << std::endl;
            }
        }
        else{
            interpreter.thisEnvironment()->setFilePath(m_fPath);
            interpreter.thisEnvironment()->setModuleName("global");
            code = input(m_fPath);
            std::cout << interpreter.interpret(m_fPath, code, m_mode) << std::endl;
            return;
        }
    }

    std::string Shell::input() {
        std::string text;

        std::cout << ">>> ";

        int stk = 0;
        while(true){
            std::string temp;
            std::getline(std::cin, temp);
            if (temp.empty()) continue;

            for (char i : temp){
                if (i == '{') stk ++;
                else if (i == '}') stk --;
            }

            text += temp + '\n';

            if (stk <= 0) break;
        }

        return text;
    }

    /**
     * @note    如果参数 path 无法打开，则会输出异常，并且通过 system("pause") 暂停整个程序。任意健后会退出程序。
     * */
    std::string Shell::input(const std::string& path){
        std::ifstream file(path);
        if (!file) {
            std::cout << "The file cannot be opened: " << path << std::endl;
            system("pause");
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }


    void ShellModel::run(const std::string &code) {
        m_interpreter.interpret("<stdin>", code);
    }

    std::string ShellView::input() {
        std::string text;

        std::cout << ">>> ";

        int stk = 0;
        while(true){
            std::string temp;
            std::getline(std::cin, temp);
            if (temp.empty()) continue;

            for (char i : temp){
                if (i == '{') stk ++;
                else if (i == '}') stk --;
            }

            text += temp + '\n';

            if (stk <= 0) break;
        }

        return text;
    }

    [[noreturn]] void ShellController::run() {
        while(true){
            std::string code = m_view.input();
            m_model.run(code);
        }
    }
} // hdg