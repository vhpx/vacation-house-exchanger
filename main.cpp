#include <iostream>

#include "./libs/classes.h"
#include "./libs/utils.h"

//* Helper preprocessor macros
// I/O macros
#define newl "\n"  // skip 1 line

#define illog(x) std::cout << x        // In-line print
#define skipLine() illog(newl)         // Skip 1 line in I/O
#define log(x) std::cout << x << newl  // Print with newline

using namespace HouseExchanger;

int main() {
    // Create a new system object to manage all the data
    System *system = new System();

    // Load all the data before the user can interact with the system
    bool loadSuccess = system->loadAll();
    if (!loadSuccess)
        return 1;

    // Display welcome message
    displayWelcomeMsg();

    // Save all the data after the user exits the system
    bool saveSuccess = system->saveAll();
    if (!saveSuccess)
        return 2;

    return 0;
}