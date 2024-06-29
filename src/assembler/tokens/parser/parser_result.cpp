#include "./parser_result.hpp"

using namespace std;
namespace basilar::tokens::parser {

ParseResult fail_parse() {
    return nullopt;
}

} // namespace basilar::tokens::parser