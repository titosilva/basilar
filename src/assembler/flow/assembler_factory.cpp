#include "assembler_factory.hpp"

namespace basilar::assembler::flow {

AssemblerFlow AssemblerFactory::create_preprocessor_flow(string file_source, string file_dest) {
    auto source = LineReader::from_file(file_source);
    source->with_common_formatters();
    auto flow = AssemblerFlow(source);

    flow.add_step(new ParserStep(&PreprocessingParser));
    flow.add_step(new Preprocessor());
    flow.add_step(new TokenWriter(file_dest));

    return flow;
}

}  // namespace basilar::assembler::flow