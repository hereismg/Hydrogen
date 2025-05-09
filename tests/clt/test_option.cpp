#include <gtest/gtest.h>
#include <hdg_clt.h>
#include <iostream>
using namespace std;

TEST(Test, _1){
    int argc = 2;
    char *argv[] = {
        const_cast<char*>("./hdg_clt"),
        const_cast<char*>("main.hdg"),
        NULL
    };

    Option opt(argc, argv);

    ASSERT_EQ(opt.getFilePath(), string("main.hdg"));
    ASSERT_EQ(opt.isOutputLexerRes(), false);
}

TEST(Test, _2){
    int argc = 2;
    char *argv[] = {
        const_cast<char*>("./hdg_clt"),
        const_cast<char*>("main.hdg"),
        const_cast<char*>("-l"),
        NULL
    };

    Option opt(argc, argv);

    ASSERT_EQ(opt.getFilePath(), string("main.hdg"));
    ASSERT_EQ(opt.isOutputLexerRes(), true);
}
