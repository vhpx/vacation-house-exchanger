#include <iostream>

#include "./libs/classes.h"
#include "./libs/utils.h"

//* Helper preprocessor macros
// I/O macros
#define newl "\n"  // skip 1 line

#define illog(x) std::cout << x        // In-line print
#define skipLine() illog(newl)         // Skip 1 line in I/O
#define log(x) std::cout << x << newl  // Print with newline
#define input(x) std::cin >> x         // Print with newline

#define DIVIDER "---------------------------------------"

using namespace HouseExchanger;

int main() {
    //* Setup
    // Create a new system object to manage all the data
    System *system = System::getInstance();

    // By default, the system is not initialized.
    // Therefore, Load all the data before the user can interact with the system.
    bool loadSuccess = system->loadAll();

    // Throw an exception if the system failed to load all the data.
    if (!loadSuccess)
        return 1;

    // System is now initialized.
    // Display welcome message.
    displayWelcomeMsg();

    //* Main loop
    // The main loop is a while loop that runs until the user quits.
    int choice = 0;

    while (choice != 4) {
        // User authentication status
        bool isLoggedIn = system->isLoggedIn();

        // Display menu.
        displayMenu(isLoggedIn);

        // Get user choice.
        illog("Enter your choice: ");
        input(choice);

        skipLine();
        log(DIVIDER);

        // Process user choice.
        if (isLoggedIn) {
            //* User is logged in.
            Member *member = system->getCurrentMember();

            switch (choice) {
                case 1:
                    log("Feature not yet implemented.");
                    break;

                case 2:
                    log("Feature not yet implemented.");
                    break;

                case 3:
                    // Logout
                    log("Logging out...");
                    member->logout();
                    break;

                case 4:
                    // Exit
                    break;

                default:
                    log("Invalid choice!");
                    choice = 0;
                    break;
            }

            // Exit the loop the user wishes to quit the program.
            if (choice == 4)
                break;
        } else {
            //* User is not logged in.
            Guest guest;

            switch (choice) {
                case 1:
                    guest.signUp();
                    break;

                case 2:
                    guest.login();
                    break;

                case 3:
                    // Browse houses
                    log("Feature not yet implemented.");
                    break;

                case 4:
                    // Exit
                    break;

                default:
                    log("Invalid choice!");
                    choice = 0;
                    break;
            }

            // Exit the loop the user wishes to quit the program.
            if (choice == 4)
                break;
        }

        // Wait for user to press enter.
        skipLine();
        std::system("PAUSE");  // Only works on Windows.

        // Clear screen
        std::system("cls");
    }

    skipLine();
    log("SYSTEM NOTIFICATION: Exiting...");

    // Save all the data after the user exits the system.
    bool saveSuccess = system->saveAll();

    //* Cleanup
    delete system;

    // Throw an exception if the system failed to save all the data.
    if (!saveSuccess)
        return 2;

    return 0;
}