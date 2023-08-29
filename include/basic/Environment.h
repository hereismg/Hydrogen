//
// Created by Magnesium on 2023/7/27.
//

#ifndef HDG_ENVIRONMENT_H
#define HDG_ENVIRONMENT_H

#include <map>
#include <string>
#include <initializer_list>
#include <stack>
#include "../object/Object.h"
#include "../object/Integer.h"
#include "../object/Float.h"

namespace hdg {
    typedef std::map<std::string, Object*> SymbolTable;

    /**
     * @brief       环境。主要用来存储符号、模块名称等信息。
     * @details     信息这里式信息是
     * @section     213
     * */

    class Environment {
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

        void setSymbol(const std::string& name, Object* value, int mode=0);

        std::string getFilePath();
        std::string getModuleName();
        Environment* getParent();
        Object* getSymbol(const std::string& name);
    };

} // hdg

#endif //HDG_ENVIRONMENT_H
