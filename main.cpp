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
    //* Setup
    // Create a new system object to manage all the data
    System *system = new System();

    // By default, the system is not initialized.
    // Therefore, Load all the data before the user can interact with the system.
    bool loadSuccess = system->loadAll();
    if (!loadSuccess)
        return 1;

    // System is now initialized.
    // Display welcome message.
    displayWelcomeMsg();

    // By default, the user is not logged in.
    // Therefore, Create guest object to interact with the system.
    Guest *guest = new Guest();

    // To keep track of user data before and after login,
    // A Member object is created to store the data.
    Member *member = new Member();

    //* Main loop
    // The main loop is a while loop that runs until the user quits.

    // Save all the data after the user exits the system.
    bool saveSuccess = system->saveAll();
    if (!saveSuccess)
        return 2;

    return 0;
}