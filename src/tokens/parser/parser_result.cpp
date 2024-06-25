#include "./parser_result.hpp"

using namespace std;
namespace basilar::tokens::parser {

ParseResult fail_parse() {
    return nullopt;
}

ParseResult succeed_parse(vector<Token> tokens, string remaining_input) {
    return ParseContext{tokens, remaining_input};
}

ParseResult succeed_parse(Token token, string remaining_input) {
    return succeed_parse(vector<Token>{token}, remaining_input);
}

ParseResult succeed_parse(ParseContext ctx, string type, string value, string remaining_input) {
    auto tokens = ctx.get_tokens();
    tokens.push_back(Token(type, value));
    return succeed_parse(tokens, remaining_input);
}

ParseResult succeed_parse(string type, string value, string remaining_input) {
    return succeed_parse(Token(type, value), remaining_input);
}

ParseResult succeed_parse(vector<Token> tokens1, vector<Token> tokens2, string remaining_input) {
    vector<Token> tokens;
    tokens.insert(tokens.end(), tokens1.begin(), tokens1.end());
    tokens.insert(tokens.end(), tokens2.begin(), tokens2.end());
    return succeed_parse(tokens, remaining_input);
}

ParseResult combine_results(ParseResult first, ParseResult second) {
    if (!first.has_value() || !second.has_value()) {
        return fail_parse();
    }

    return succeed_parse(first.value().get_tokens(), second.value().get_tokens(), second.value().get_remaining_input());
}

} // namespace basilar::tokens::parser