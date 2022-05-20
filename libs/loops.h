#ifndef LOOPS_INCLUDED
#define LOOPS_INCLUDED

#include <string>

#include "classes.h"

using std::string;

namespace HouseExchanger {
void mainLoop();
void profileLoop();
void houseDetailsLoop();
void houseBrowserLoop();
void houseSelectorLoop(bool eligibleOnly, string location, Date startingDate, Date endingDate);
}  // namespace HouseExchanger

#endif  // LOOPS_INCLUDED