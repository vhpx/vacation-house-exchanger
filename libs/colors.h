#ifndef COLORS_INCLUDED
#define COLORS_INCLUDED

#include <string>

namespace Colors {
const std::string RED = "\033[0;31m";
const std::string GREEN = "\033[0;32m";
const std::string YELLOW = "\033[0;33m";
const std::string BLUE = "\033[0;34m";
const std::string MAGENTA = "\033[0;35m";
const std::string CYAN = "\033[0;36m";
const std::string WHITE = "\033[0;37m";
const std::string RESET = "\033[0m";

const std::string BOLD = "\033[1m";
const std::string UNDERLINE = "\033[4m";
const std::string REVERSE = "\033[7m";
const std::string HIDDEN = "\033[8m";

const std::string BLACK = "\033[30m";
}  // namespace Colors

#endif  // COLORS_INCLUDED