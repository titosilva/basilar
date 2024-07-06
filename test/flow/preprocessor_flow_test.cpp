#include "../../src/assembler/flow/assembler_factory.hpp"
#include "../test_suite.hpp"

using namespace std;
using namespace basilar::assembler::flow;

DefineGlobalTestSuiteFor(PreporcessorFlow)

    DefineGlobalTest(ShouldRemoveComments) {
        auto file_path = DATA_FILE_PATH("commented_line.asm");
        auto out_path = DATA_FILE_PATH("commented_line.out.asm");
        auto flow = AssemblerFactory::create_preprocessor_flow(file_path, out_path);

        flow.run();

        auto out_file = DATA_FILE_CONTENT("commented_line.out.asm");
        auto expected = DATA_FILE_CONTENT("commented_line.expected.asm");
        ASSERT_EQ(out_file, expected);
    }

    DefineGlobalTest(ShouldRemoveEqu) {
        auto file_path = DATA_FILE_PATH("equ_line.asm");
        auto out_path = DATA_FILE_PATH("equ_line.out.asm");
        auto flow = AssemblerFactory::create_preprocessor_flow(file_path, out_path);

        flow.run();

        auto out_file = DATA_FILE_CONTENT("equ_line.out.asm");
        auto expected = DATA_FILE_CONTENT("equ_line.expected.asm");
        ASSERT_EQ(out_file, expected);
    }

    DefineGlobalTest(ShouldRemoveIfs) {
        auto file_path = DATA_FILE_PATH("if_line.asm");
        auto out_path = DATA_FILE_PATH("if_line.out.asm");
        auto flow = AssemblerFactory::create_preprocessor_flow(file_path, out_path);

        flow.run();

        auto out_file = DATA_FILE_CONTENT("if_line.out.asm");
        auto expected = DATA_FILE_CONTENT("if_line.expected.asm");
        ASSERT_EQ(out_file, expected);
    }

EndGlobalTestSuite

RunGlobalTest(PreporcessorFlow, ShouldRemoveComments)
RunGlobalTest(PreporcessorFlow, ShouldRemoveEqu)
RunGlobalTest(PreporcessorFlow, ShouldRemoveIfs)
