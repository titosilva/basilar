#include "assembler_flow.hpp"
#include "../../utils/logger.hpp"

// TODO: Remove this
#include <iostream>
using namespace std;

namespace basilar::assembler::flow {

AssemblerFlow AssemblerFlow::add_step(AssemblerStep* step) {
    __steps.push_back(step);
    return *this;
}

AssemblerFlow AssemblerFlow::add_post_step(AssemblerPostStep* step) {
    __post_steps.push_back(step);
    return *this;
}

void AssemblerFlow::run() {    
    LOG_DEBUG("Running assembler steps");
    while (__source->next_line()) {
        auto ctx = __source->read_current_line();
        
        for (auto step : __steps) {
            auto result = step->run(ctx, __source);

            if (!result.has_value()) {
                break;
            }

            ctx = result.value();
        }
    }

    LOG_DEBUG("Running assembler post steps");
    for (auto step : __post_steps) {
        step->run();
    }

    LOG_DEBUG("Assembler steps finished");
}

}  // namespace basilar::assembler::flow