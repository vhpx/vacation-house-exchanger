#include <iostream>

#include "./libs/classes.h"
#include "./libs/colors.h"
#include "./libs/utils.h"

using namespace HouseExchanger;

//* Helper preprocessor macros
// I/O macros
#define newl "\n"  // skip 1 line
#define DIVIDER "---------------------------------------"

#define illog(x) std::cout << x  // In-line print (DEFAULT)
#define skipLine() illog(newl)   // Skip 1 line in terminal

#define illogInfo(x) std::cout << Colors::YELLOW << x << Colors::RESET    // In-line print (YELLOW)
#define illogError(x) std::cout << Colors::RED << x << Colors::RESET      // In-line print (RED)
#define illogSuccess(x) std::cout << Colors::GREEN << x << Colors::RESET  // In-line print (GREEN)

#define log(x) illog(x << newl)                // Print with newline (DEFAULT)
#define logInfo(x) illogInfo(x << newl)        // Print with newline (YELLOW)
#define logError(x) illogError(x << newl)      // Print with newline (RED)
#define logSuccess(x) illogSuccess(x << newl)  // Print with newline (GREEN)

// Input string with/without spaces
#define inputStr(x)            \
    std::cin.ignore();         \
    std::getline(std::cin, x); \
    illog(Colors::RESET)

// Input string with spaces or any other types
#define input(x)         \
    illog(Colors::CYAN); \
    std::cin >> x;       \
    illog(Colors::RESET)

int main() {
    //* Setup
    // Clear screen
    std::system("cls");

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

    while (choice != -1) {
        // User authentication status
        bool isLoggedIn = system->isLoggedIn();

        // Display menu.
        displayMenu();

        // Get user choice.
        illogInfo("Enter your choice: ");

        std::string buffer;
        input(buffer);

        // Check if the user entered an integer.
        if (checkIfInteger(buffer)) {
            choice = std::stoi(buffer);
        } else {
            logError("Error: Invalid input. Please enter an integer.");

            // Wait for user to press enter.
            skipLine();
            std::system("PAUSE");  // Only works on Windows.

            // Clear screen
            std::system("cls");
            continue;
        }

        skipLine();
        log(DIVIDER);

        // Process user choice.
        if (isLoggedIn) {
            //* User is logged in.
            Member *member = system->getCurrentMember();

            switch (choice) {
                case 1:
                    system->showUserProfile();
                    break;

                case 2:
                    system->showUserHouseDetails();
                    break;

                case 3:
                    system->showHouses();
                    break;

                case 4:
                    member->logout();
                    break;

                case -1:
                    // Exit program
                    break;

                default:
                    logError("Error: Invalid choice!");
                    choice = 0;
                    break;
            }

            // Exit the loop the user wishes to quit the program.
            if (choice == -1)
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
                    system->showHouses();
                    break;

                case -1:
                    // Exit program
                    break;

                default:
                    logError("Error: Invalid choice!");
                    choice = 0;
                    break;
            }

            // Exit the loop the user wishes to quit the program.
            if (choice == -1)
                break;
        }

        // Wait for user to press enter.
        skipLine();
        std::system("PAUSE");  // Only works on Windows.

        // Clear screen
        std::system("cls");
    }

    skipLine();
    logInfo("SYSTEM NOTIFICATION: Exiting...");

    // Save all the data after the user exits the system.
    bool saveSuccess = system->saveAll();

    //* Cleanup
    delete system;

    // Throw an exception if the system failed to save all the data.
    if (!saveSuccess)
        return 2;

    return 0;
}