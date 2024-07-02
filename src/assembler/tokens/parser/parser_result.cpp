#include "./parser_result.hpp"

using namespace std;
namespace basilar::assembler::tokens::parser {

ParseResult fail_parse() {
    return nullopt;
}

} // namespace basilar::assembler::tokens::parser