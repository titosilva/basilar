#include "parser_step.hpp"

namespace basilar::assembler::flow {

optional<ParseContext> ParserStep::run(ParseContext ctx, LineSource*) {
    auto r = this->__parser->parse(ctx);

    if (r.has_value()) {
        return r;
    }

    return ctx;
}

} // namespace basilar::assembler::flow