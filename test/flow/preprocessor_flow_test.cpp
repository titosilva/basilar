#include "../../src/assembler/flow/assembler_factory.hpp"
#include "../test_suite.hpp"

using namespace std;
using namespace basilar::assembler::flow;

DefineGlobalTestSuiteFor(PreporcessorFlow)

    DefineGlobalTest(ShouldRemoveComments) {
        auto file_path = TestData::get_data_file_path("commented_line.asm");
        auto out_path = TestData::get_data_file_path("commented_line.out.asm");
        auto flow = AssemblerFactory::create_preprocessor_flow(file_path, out_path);

        flow.run();

        auto out_file = TestData::get_data_file_content("commented_line.out.asm");
        auto expected = TestData::get_data_file_content("commented_line.expected.asm");
        ASSERT_EQ(out_file, expected);
    }

    DefineGlobalTest(ShouldRemoveEqu) {
        auto file_path = TestData::get_data_file_path("equ_line.asm");
        auto out_path = TestData::get_data_file_path("equ_line.out.asm");
        auto flow = AssemblerFactory::create_preprocessor_flow(file_path, out_path);

        flow.run();

        auto out_file = TestData::get_data_file_content("equ_line.out.asm");
        auto expected = TestData::get_data_file_content("equ_line.expected.asm");
        ASSERT_EQ(out_file, expected);
    }

EndGlobalTestSuite

RunGlobalTest(PreporcessorFlow, ShouldRemoveComments)