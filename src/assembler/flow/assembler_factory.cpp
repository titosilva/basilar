#include "assembler_factory.hpp"
#include "action_step/action_step.hpp"

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

AssemblerFlow AssemblerFactory::create_assembler_flow(string file_source, string file_dest) {
    auto source = LineReader::from_file(file_source);
    source->with_common_formatters();
    auto flow = AssemblerFlow(source);

    auto line_assembler = new LineAssemblerStep(file_dest);

    flow.add_step(new ParserStep(&PreprocessingParser));
    flow.add_step(new Preprocessor());
    flow.add_step(new ParserStep(&AssemblerParser));
    flow.add_step(line_assembler);

    auto write_to_file = [=] (void) -> void {
        #if DEBUG
        line_assembler->write_debug_file();
        #endif

        line_assembler->write_object_file();
    };

    flow.add_post_step(new ActionStep(write_to_file));

    return flow;
}

}  // namespace basilar::assembler::flow