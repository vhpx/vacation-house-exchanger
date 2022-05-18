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

using namespace HouseExchanger;

int main() {
    //* Setup
    // Create a new system object to manage all the data
    System *system = new System();

    // By default, the system is not initialized.
    // Therefore, Load all the data before the user can interact with the system.
    bool loadSuccess = system->loadAll();

    // Throw an exception if the system failed to load all the data.
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
    Member *member = nullptr;

    //* Main loop
    // The main loop is a while loop that runs until the user quits.
    int choice = 0;

    while (choice != 4) {
        // Display menu.
        displayMenu(member != nullptr);

        // Get user choice.
        illog("Enter your choice: ");
        input(choice);

        // Process user choice.
        switch (choice) {
            case 1:
                // Sign up
                // guest->signUp();
                log("Feature not yet implemented.");
                break;
            case 2:
                // Login
                // guest->login();
                log("Feature not yet implemented.");
                break;
            case 3:
                // Logout
                // guest->logout();
                log("Feature not yet implemented.");
                break;
            case 4:
                // Exit
                break;
            default:
                log("Invalid choice!");
                break;
        }

        // Exit the loop the user wishes to quit the program.
        if (choice == 4)
            break;

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
    delete guest;
    delete member;

    // Throw an exception if the system failed to save all the data.
    if (!saveSuccess)
        return 2;

    return 0;
}