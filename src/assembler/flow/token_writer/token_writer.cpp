#include "token_writer.hpp"

#include <fstream>

using namespace std;

namespace basilar::assembler::flow {

optional<ParseContext> TokenWriter::run(ParseContext ctx, LineSource*) {
    ofstream file;

    if (!this->__file_is_clean) {
        file.open(__file_dest, ios::trunc);
        this->__file_is_clean = true;
    } else {
        file.open(__file_dest, ios::app);
    }

    auto tokens = ctx.get_tokens();
    for (size_t i = 0; i < tokens.size(); i++) {
        auto token = tokens[i];
        file << token.value;

        if (i < tokens.size() - 1) {
            file << " ";
        }
    }

    file << ctx.get_remaining_input();

    file << endl;
    file.close();
    return nullopt;
}

}  // namespace basilar::assembler::flow