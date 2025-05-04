//
// Created by Magnesium on 2023/7/14.
//


#ifndef HDG_SHELL_H
#define HDG_SHELL_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include "../../hydrogen/include/kernel/Lexer.h"
// #include "NewLexer.h"
#include "../../hydrogen/include/kernel/Parser.h"
#include "../../hydrogen/include/kernel/Interpreter.h"
#include "../../hydrogen/include/basic/Error.h"
#include "../../hydrogen/include/basic/Environment.h"

namespace hdg {
    void hydrogen(int argc, char* argv[]);

    class ShellModel{
    protected:
        // std::list<File> fileArr;

    public:
        ShellModel() = default;
        ~ShellModel() = default;
        void run(const std::string& code);
    };


    class ShellView{
    public:
        std::string input();
    };


    class ShellController{
    protected:
        ShellModel m_model;
        ShellView m_view;
    public:
        ShellController() = default;

        [[noreturn]] void run();

    };

    /**
     * Shell 是整个海琛解释器的起点
     * */
    class Shell {
    protected:
        Interpreter::Mode m_mode;
        std::string m_fPath;

        Environment m_root;
        Interpreter m_interpreter;

    public:
        Shell();

        /**
         * 整个 Shell 的入口。会更具 argc 和 argv 的变化而变化。
         * @param argc 参数的个数
         * @param argv 参数数组
         * */
        void exe(int argc, char* argv[]);

        /**
         * 代码输入函数。主要用于命令行模式的代码输入。
         * */
        static std::string input();

        /**
         * 代码输入函数。主要用于文件的输入。
         * */
        static std::string input(const std::string& path);
    };

} // hdg

#endif //HDG_SHELL_H
