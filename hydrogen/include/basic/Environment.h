//
// Created by Magnesium on 2023/7/27.
//

#pragma once

#include <map>
#include <string>
#include <initializer_list>
#include <stack>
#include <memory>

namespace hdg {
    class Object;
    typedef std::unique_ptr<Object> uObject;
    typedef std::shared_ptr<Object> sObject;
    typedef std::weak_ptr<Object>   wObject;
    
    /**
     * @brief       环境。主要用来存储符号、模块名称等信息。
     * @details     信息这里式信息是
     * @section     213
     * */

    class Environment {
    public:
        typedef std::map<std::string, Object*> SymbolTable;
        enum Mode{
            GLOBAL,
            LOCAL
        };

    protected:
        Environment* m_parent{nullptr};
        SymbolTable m_symbolTable;

        std::string m_fPath;            ///< 创建该环境的代码的文件目录
        std::string m_moduleName;       ///< 创建该环境的模块名称，一般是函数的名称

    public:
        Environment();
        Environment(Environment* parent, std::string fPath, std::string moduleName);
        ~Environment();

        void setFilePath(const std::string& fPath);
        void setModuleName(const std::string& moduleName);
        void setParent(Environment* parent);

        /**
         * @brief 给环境中的符号表设置符号
         * @param name      符号名字
         * @param value     符号值
         * @param mode      设置模式，0为父级模式，1为本地模式；默认为父级模式
         * */

        void setSymbol(const std::string& name, Object* value, Mode mode=GLOBAL);

        std::string getFilePath();
        std::string getModuleName();
        Environment* getParent();
        Object* getSymbol(const std::string& name);
    };


    class New_Environment{
    protected:
        std::map<std::string, sObject> m_table;

    public:
        New_Environment() = default;
        New_Environment(std::map<std::string, sObject>&& table)
            : m_table(std::move(table)) {}
        
        void setSymbol(const std::string& name, sObject obj);
        sObject  getSymbol(const std::string& name);
        sObject* getSymbolPtr(const std::string& name);
    };

} // hdg

