#include "assembler_flow.hpp"

// TODO: Remove this
#include <iostream>
using namespace std;

namespace basilar::assembler::flow {

AssemblerFlow AssemblerFlow::add_step(AssemblerStep* step) {
    __steps.push_back(step);
    return *this;
}

void AssemblerFlow::run() {
    while (this->__source->next_line()) {
        auto ctx = this->__source->read_current_line();

        // TODO: Remove this
        cout << ctx.get_remaining_input() << endl;
        
        for (auto step : this->__steps) {
            // TODO: Remove this
            cout << "Running step" << endl;
            
            auto result = step->run(ctx, this->__source);

            if (!result.has_value()) {
                break;
            }

            ctx = result.value();
        }
    }
}

}  // namespace basilar::assembler::flow