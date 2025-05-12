#include <gtest/gtest.h>
// #include <gmock/gmock.h>
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

// class IFileSystem {
// public:
//     virtual ~IFileSystem() = default;
//     virtual bool FileExists(const std::string& path) const = 0;
//     virtual std::string ReadFile(const std::string& path) = 0;
//     virtual bool WriteFile(const std::string& path, const std::string& content) = 0;
// };

// class MockFileSystem : public IFileSystem {
// public:
//     MOCK_METHOD(bool, FileExists, (const std::string& path), (const override));
//     MOCK_METHOD(std::string, ReadFile, (const std::string& path), (override));
//     MOCK_METHOD(bool, WriteFile, (const std::string& path, const std::string& content), (override));
// };

// class FileProcessor {
// public:
//     FileProcessor(IFileSystem* fs) : fs_(fs) {}
    
//     std::string ProcessFile(const std::string& path) {
//         if (fs_->FileExists(path)) {
//             return fs_->ReadFile(path);
//         }
//         return "";
//     }

// private:
//     IFileSystem* fs_;
// };

 
// TEST(FileProcessorTest, ReadExistingFile) {
//     MockFileSystem mockFS;
//     std::string testPath = "/test.txt";
//     std::string testContent = "Hello, gmock!";
 
//     // 设置预期行为
//     EXPECT_CALL(mockFS, FileExists(testPath))
//         .WillOnce(testing::Return(true));
//     EXPECT_CALL(mockFS, ReadFile(testPath))
//         .WillOnce(testing::Return(testContent));
 
//     // 执行测试
//     FileProcessor processor(&mockFS);
//     std::string result = processor.ProcessFile(testPath);
 
//     // 验证结果
//     EXPECT_EQ(result, testContent);
// }