#include <gtest/gtest.h>
#include "LoggerAndFileTask.h"

TEST(OperationTest, Add) {
    std::string cmd = "add";
    Operation op(cmd, 2, 3);
    EXPECT_DOUBLE_EQ(op.execute(), 5);
}

TEST(FileTaskTest, CorrectFile) {
    Logger logger("test.log");

    std::ofstream f("test.dat");
    f << "mult 3 4";
    f.close();

    FileTask task("test.dat", logger);
    EXPECT_DOUBLE_EQ(task(), 12);

    std::filesystem::remove("test.dat");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}