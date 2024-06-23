#include "../../../src/tokens/parser/utility_parsers.hpp"
#include "../../test_suite.hpp"

using namespace std;
using namespace basilar::tokens::parser;

DefineGlobalTestSuiteFor(UtilityParsers)
    DefineGlobalTest(JoinWithType__ShouldJoinTokensWithType) {
        auto parser = Whitespace >> Number >> Whitespace >> JoinWithType("number_with_spaces");
        auto result = parser.parse("    123\t    ");

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value().get_tokens().size(), 1);
        ASSERT_EQ(result.value().get_tokens()[0].type, "number_with_spaces");
        ASSERT_EQ(result.value().get_tokens()[0].value, "    123\t    ");
    }
EndGlobalTestSuite

RunGlobalTest(UtilityParsers, JoinWithType__ShouldJoinTokensWithType)
