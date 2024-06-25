#pragma once

#include "token.hpp"
#include "parse_context.hpp"
#include "../../friend_test.hpp"

#include <optional>
#include <vector>

using namespace std;

namespace basilar::tokens::parser {

typedef optional<ParseContext> ParseResult;
ParseResult fail_parse();

} // namespace basilar::tokens::parser

