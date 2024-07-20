#pragma once

#include "../assembler_steps.hpp"
#include <functional>

using namespace std;

namespace basilar::assembler::flow {

class ActionStep : public AssemblerPostStep {
public:
    ActionStep(function<void(void)> action) : __action(action) {}
    void run() override;
private:
    function<void(void)> __action;
};

} // namespace basilar::assembler::flow
