#include "../test_suite.hpp"
#include "../../src/tokenizer/formatter.hpp"

#include <string>

using namespace std;
using namespace basilar::tokenizer;

DefineTestSuiteFor(Formatter)
    DefineTest(Trim__ShouldRemoveLeadingAndTrailingWhitespace) {
        string line = "  \tHello, World! \t\t \t";   
        string expected = "Hello, World!";
        auto actual = Trim(line);

        ASSERT_EQ(expected, actual);
    }

    DefineTest(ToLower__ShouldConvertAllCharactersToLowercase) {
        string line = "Hello, World!";
        string expected = "hello, world!";
        auto actual = ToLower(line);

        ASSERT_EQ(expected, actual);
    }

    DefineTest(UnifyWhitespace__ShouldReplaceMultipleWhitespaceCharactersWithSingleSpace) {
        string line = "\t    \tHello, \t\t  World!    ";
        string expected = " Hello, World! ";
        auto actual = UnifyWhitespace(line);

        ASSERT_EQ(expected, actual);
    }

    DefineTest(RemoveComments__ShouldRemoveComments) {
        string line = "Hello, World! ; This is a comment";
        string expected = "Hello, World! ";
        auto actual = RemoveComments(line);

        ASSERT_EQ(expected, actual);
    }

    DefineTest(RemoveComments__ShouldRemoveComments__WhenLineIsAllCommented) {
        string line = "; This is a comment";
        string expected = "";
        auto actual = RemoveComments(line);

        ASSERT_EQ(expected, actual);
    }

    DefineTest(EmptyBlankLines__ShouldTransformLinesWithOnlySpacesToEmpty) {
        string line = "\t  \t \t \t \t\t    ";
        string expected = "";
        auto actual = EmptyBlankLines(line);

        ASSERT_EQ(expected, actual);
    }
EndTestSuite

RunTest(Formatter, Trim__ShouldRemoveLeadingAndTrailingWhitespace)
RunTest(Formatter, ToLower__ShouldConvertAllCharactersToLowercase)
RunTest(Formatter, UnifyWhitespace__ShouldReplaceMultipleWhitespaceCharactersWithSingleSpace)
RunTest(Formatter, RemoveComments__ShouldRemoveComments)
RunTest(Formatter, RemoveComments__ShouldRemoveComments__WhenLineIsAllCommented)
RunTest(Formatter, EmptyBlankLines__ShouldTransformLinesWithOnlySpacesToEmpty)