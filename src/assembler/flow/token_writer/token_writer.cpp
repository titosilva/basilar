#include "token_writer.hpp"

#include <fstream>

// TODO: Remove this
#include <iostream>
using namespace std;

namespace basilar::assembler::flow {

optional<ParseContext> TokenWriter::run(ParseContext ctx, LineSource*) {
    // TODO: Remove this
    cout << "Opening file" << endl;

    ofstream file;

    if (!this->__file_is_clean) {
        file.open(__file_dest, ios::trunc);
        this->__file_is_clean = true;
    } else {
        file.open(__file_dest, ios::app);
    }

    // TODO: Remove this
    cout << "Writing tokens to file" << endl;

    auto tokens = ctx.get_tokens();
    cout << "To write: ";
    for (size_t i = 0; i < tokens.size(); i++) {
        auto token = tokens[i];
        file << token.value;
        cout << token.value;

        if (i < tokens.size() - 1) {
            cout << " ";
            file << " ";
        }
    }

    file << ctx.get_remaining_input();
    cout << ctx.get_remaining_input();

    file << endl;
    cout << endl;
    file.close();
    return nullopt;
}

}  // namespace basilar::assembler::flow