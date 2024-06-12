#pragma once

#include <string>
#include <functional>

namespace basilar::tokens {
    typedef std::function<std::string(std::string)> Preprocessor;
} // namespace basilar::tokens