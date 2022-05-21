#include "loops.h"

#include <iostream>

#include "classes.h"
#include "colors.h"
#include "utils.h"

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
    illog(Colors::CYAN);       \
    std::getline(std::cin, x); \
    illog(Colors::RESET)

// Input string with spaces or any other types
#define input(x)         \
    illog(Colors::CYAN); \
    std::cin >> x;       \
    illog(Colors::RESET)

namespace HouseExchanger {
void mainLoop() {
    System *system = System::getInstance();
    int choice = -1;

    // Execute main loop
    while (choice != 0) {
        // User authentication status
        bool isLoggedIn = system->isLoggedIn();

        // Display the default menu
        displayDefaultMenu();

        // Get user choice.
        illogInfo("Enter your choice: ");

        std::string buffer;
        input(buffer);

        // Check if the user entered an integer.
        if (checkIfInteger(buffer)) {
            choice = std::stoi(buffer);
        } else {
            logError("Error: Invalid input. Please enter an integer.");
            choice = -1;

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
        bool skipPause = false;

        if (isLoggedIn) {
            //* User is logged in.
            Member *member = system->getCurrentMember();

            switch (choice) {
                case 1:
                    profileLoop();
                    skipPause = true;
                    break;

                case 2:
                    houseDetailsLoop();
                    skipPause = true;
                    break;

                case 3:
                    houseBrowserLoop();
                    skipPause = true;
                    break;

                case 4:
                    member->logout();
                    break;

                case 0:
                    // Exit program
                    break;

                default:
                    logError("Error: Invalid choice!");
                    choice = -1;
                    break;
            }

            // Exit the loop if the user
            // wishes to quit the program.
            if (choice == 0)
                break;
        } else {
            //* User is not logged in.
            Guest guest;

            switch (choice) {
                case 1:
                    guest.login();
                    break;

                case 2: {
                    Member *newMember = guest.signUp();
                    if (newMember == nullptr) break;

                    string response;

                    skipLine();
                    illogInfo("Would you like to list a house now? (Y/N): ");
                    input(response);

                    if (response == "Y" || response == "y") {
                        skipLine();
                        skipPause = true;

                        while (!newMember->listHouse()) {
                            std::system("cls");
                            logError("Error: Failed to setup house. Please try again.");
                            skipLine();
                        }
                    }
                    break;
                }

                case 3:
                    system->displayHouseBrowser(false, "", Date(), Date());

                    skipLine();
                    log(DIVIDER);
                    logInfo("To view the house details and book it, you need to login first.");
                    break;

                case 0:
                    // Exit program
                    break;

                default:
                    logError("Error: Invalid choice!");
                    choice = -1;
                    break;
            }

            // Exit the loop if the user
            // wishes to quit the program.
            if (choice == 0)
                break;
        }

        // Wait for user to press enter.
        if (!skipPause) {
            skipLine();
            std::system("PAUSE");  // Only works on Windows.
        }

        // Clear screen
        std::system("cls");
    }
}

void profileLoop() {
    System *system = System::getInstance();
    Member *currentUser = system->getCurrentMember();

    int choice = -1;

    // Execute profile loop
    while (choice != 0) {
        // Clear screen
        std::system("cls");

        // Display the profile menu
        displayProfileMenu();

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

            continue;
        }

        skipLine();
        log(DIVIDER);

        // Process user choice.
        switch (choice) {
            case 1:
                currentUser->updateInfo();
                break;

            case 2:
                currentUser->changePassword();
                break;

            case 3:
                if (currentUser->deleteProfile()) return;
                break;

            case 0:
                // Exit profile loop
                break;

            default:
                logError("Error: Invalid choice!");
                choice = -1;

                skipLine();
                std::system("PAUSE");  // Only works on Windows.
                break;
        }

        // Exit the loop if the user
        // wishes to quit the program.
        if (choice == 0)
            break;
    }

    // Wait for user to press enter.
    if (choice != 0) {
        skipLine();
        std::system("PAUSE");  // Only works on Windows.
    }
}

void houseDetailsLoop() {
    System *system = System::getInstance();
    Member *currentUser = system->getCurrentMember();
    House *currentHouse = currentUser->getHouse();

    int choice = -1;

    // Execute house details loop
    while (choice != 0) {
        // Clear screen
        std::system("cls");

        if (currentHouse == nullptr) {
            system->showUserHouseDetails();
            return;
        }

        // Display the house details menu
        displayHouseDetailsMenu();

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

            continue;
        }

        skipLine();
        log(DIVIDER);

        // Process user choice.
        switch (choice) {
            case 1:
                currentHouse->updateInfo();
                break;

            case 2:
                // "View requests",
                break;

            case 3:
                // "View comments",
                break;

            case 4:
                // "View ratings",
                break;

            case 5:
                if (system->unlistCurrentHouse()) return;
                break;

            case 0:
                // Exit house details loop
                break;

            default:
                logError("Error: Invalid choice!");
                choice = -1;

                skipLine();
                std::system("PAUSE");  // Only works on Windows.
                break;
        }

        // Exit the loop if the user
        // wishes to quit the program.
        if (choice == 0)
            break;
    }

    // Wait for user to press enter.
    if (choice != 0) {
        skipLine();
        std::system("PAUSE");  // Only works on Windows.
    }
}

void houseSelectorLoop(bool eligibleOnly, string location, Date startingDate, Date endingDate) {
    System *system = System::getInstance();
    Member *currentUser = system->getCurrentMember();

    int choice = -1;

    // Execute house selector loop
    while (choice != 0) {
        // Clear screen
        std::system("cls");

        // Display all houses
        system->displayHouseBrowser(eligibleOnly, location, startingDate, endingDate);

        // Display the house selector menu
        displayHouseSelectorMenu();

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

            continue;
        }

        skipLine();
        log(DIVIDER);

        // Process user choice.
        switch (choice) {
            case 1: {
                int houseNumber;

                // Get user selection.
                illogInfo("Enter the house number: ");
                input(houseNumber);
                skipLine();

                // Get available houses.
                vector<House *> houses;
                system->getAvailableHouses(houses, false, location, startingDate, endingDate);

                // Get house at [number - 1] index.
                House *house = houses[houseNumber - 1];

                // Check if the user is eligible to book the house.
                if (currentUser->isEligibleToBook(house, startingDate, endingDate)) {
                    // Book the house.
                    // currentUser->bookHouse(house);
                    logInfo("Successfully booked the house!");
                } else {
                    logError("Error: You are not eligible to book this house.");
                }

                skipLine();
                std::system("PAUSE");  // Only works on Windows.

                break;
            }

            case 0:
                // Exit house selector loop
                break;

            default:
                logError("Error: Invalid choice!");
                choice = -1;

                skipLine();
                std::system("PAUSE");  // Only works on Windows.
                break;
        }

        // Exit the loop if the user
        // wishes to quit the program.
        if (choice == 0)
            break;
    }

    // Wait for user to press enter.
    if (choice != 0) {
        skipLine();
        std::system("PAUSE");  // Only works on Windows.
    }
}

void houseBrowserLoop() {
    System *system = System::getInstance();

    int choice = -1;

    // Execute house browser loop
    while (choice != 0) {
        // Clear screen
        std::system("cls");

        // Display the house browser menu
        displayHouseBrowserMenu();

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

            continue;
        }

        skipLine();
        log(DIVIDER);

        // Process user choice.
        switch (choice) {
            case 1:
                system->displayHouseBrowser(false, "", Date(), Date());

                // Wait for user to press enter.
                skipLine();
                std::system("PAUSE");  // Only works on Windows.
                break;

            case 2: {
                string location;
                system->displayAvailableLocations();

                illogInfo("Enter location: ");

                if (std::cin.peek() == '\n') std::cin.ignore();
                inputStr(location);

                // Check if the location is available.
                if (!system->isLocationAvailable(location)) {
                    skipLine();
                    logError("Location is not available.");

                    skipLine();
                    std::system("PAUSE");  // Only works on Windows.

                    break;
                }

                Date startingDate, endingDate;

                string buffer;
                illogInfo("Start date (dd/mm/yyyy): ");
                input(buffer);

                while (!Date::isValid(buffer)) {
                    illogInfo("Invalid date format. Please try again: ");
                    input(buffer);
                }

                startingDate = Date::parse(buffer);

                illogInfo("End date (dd/mm/yyyy): ");
                input(buffer);

                while (!Date::isValid(buffer)) {
                    illogInfo("Invalid date format. Please try again: ");
                    input(buffer);
                }

                endingDate = Date::parse(buffer);

                skipLine();
                log(DIVIDER);

                houseSelectorLoop(true, location, startingDate, endingDate);
                break;
            }

            case 0:
                // Exit house browser loop
                return;

            default:
                logError("Error: Invalid choice!");
                choice = -1;

                skipLine();
                std::system("PAUSE");  // Only works on Windows.
                break;
        }

        // Exit the loop if the user
        // wishes to quit the program.
        if (choice == 0)
            break;
    }

    // Wait for user to press enter.
    if (choice != 0) {
        skipLine();
        std::system("PAUSE");  // Only works on Windows.
    }
}
}  // namespace HouseExchanger