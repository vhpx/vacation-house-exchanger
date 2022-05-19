#include "utils.h"

#include <iostream>
#include <string>

#include "classes.h"
#include "colors.h"

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

//* Constants
// Listing project, lecturer, and authors information
#define APP_HEADER "EEET2482/COSC2082 ASSIGNMENT"
#define APP_NAME "VACATION HOUSE EXCHANGE APPLICATION"

#define LECTURER_NAME "Mr. Linh Tran"
#define GROUP_NAME "Gucci Gang"

#define AUTHOR1_INFO "s3926761" << Colors::CYAN << ", " << Colors::GREEN << "Vo Hoang Phuc"
#define AUTHOR2_INFO "s3915195" << Colors::CYAN << ", " << Colors::GREEN << "Le Cam Tu"
#define AUTHOR3_INFO "s3926793" << Colors::CYAN << ", " << Colors::GREEN << "Nguyen Pham Anh Thu"
#define AUTHOR4_INFO "s3927460" << Colors::CYAN << ", " << Colors::GREEN << "Nguyen Ngoc Luong"

namespace HouseExchanger {
bool checkIfInteger(const std::string& str) {
    std::string::const_iterator it = str.begin();
    while ((it == str.begin() && *it == '-') || (it != str.end() && std::isdigit(*it))) ++it;
    return !str.empty() && it == str.end();
}

void displayWelcomeMsg() {
    log(DIVIDER);
    skipLine();

    log(Colors::CYAN << APP_HEADER);
    log(APP_NAME << newl);

    logInfo("Instructor: " << Colors::GREEN << LECTURER_NAME);
    logInfo("Group: " << Colors::GREEN << GROUP_NAME << newl);

    logInfo(AUTHOR1_INFO);
    logInfo(AUTHOR2_INFO);
    logInfo(AUTHOR3_INFO);
    logInfo(AUTHOR4_INFO);

    // Wait for user to press enter.
    skipLine();
    std::system("PAUSE");  // Only works on Windows.

    // Clear screen
    std::system("cls");
}

void displayDefaultMenu() {
    System* system = System::getInstance();

    bool isLoggedIn = system->isLoggedIn();
    bool isAdmin = system->isAdmin();

    log(DIVIDER);
    logInfo(Colors::BOLD << "  " << APP_NAME);

    if (isLoggedIn || isAdmin) {
        log(DIVIDER);
        logSuccess("\tLogged in as: "
                   << Colors::YELLOW
                   << system->getCurrentMember()->getUsername());
    }

    log(DIVIDER);
    log(Colors::BLUE << Colors::BOLD
                     << "\tPlease select an option"
                     << Colors::RESET << newl);

    if (isLoggedIn) {
        logInfo("1. " << Colors::CYAN << "Account profile");
        logInfo("2. " << Colors::CYAN << "House profile");
        logInfo("3. " << Colors::CYAN << "Browse houses");
        logInfo("4. " << Colors::CYAN << "Logout");
    } else {
        logInfo("1. " << Colors::CYAN << "Sign up");
        logInfo("2. " << Colors::CYAN << "Login");
        logInfo("3. " << Colors::CYAN << "Browse houses");
    }

    logInfo(newl << "0. " << Colors::RED << "Exit program");
    log(DIVIDER << newl);
}
}  // namespace HouseExchanger