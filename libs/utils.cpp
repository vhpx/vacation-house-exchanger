#include "utils.h"

#include <iostream>
#include <string>

#include "classes.h"
#include "colors.h"

using namespace HouseExchanger;

//* Helper preprocessor macros
// I/O macros
#define newl "\n"  // skip 1 line

#define illog(x) std::cout << x        // In-line print
#define skipLine() illog(newl)         // Skip 1 line in I/O
#define log(x) std::cout << x << newl  // Print with newline

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

#define DIVIDER "---------------------------------------"

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

    log(Colors::YELLOW << "Instructor: " << Colors::GREEN << LECTURER_NAME);
    log(Colors::YELLOW << "Group: " << Colors::GREEN << GROUP_NAME << newl);

    log(Colors::YELLOW << AUTHOR1_INFO);
    log(Colors::YELLOW << AUTHOR2_INFO);
    log(Colors::YELLOW << AUTHOR3_INFO);
    log(Colors::YELLOW << AUTHOR4_INFO << Colors::RESET);

    skipLine();
}

void displayMenu() {
    System* system = System::getInstance();

    bool isLoggedIn = system->isLoggedIn();
    bool isAdmin = system->isAdmin();

    if (isLoggedIn || isAdmin) {
        log(DIVIDER);
        log(Colors::GREEN << "\tLogged in as: "
                          << Colors::YELLOW << system->getCurrentMember()->getUsername()
                          << Colors::RESET);
    }

    log(DIVIDER);
    log(Colors::BLUE << Colors::BOLD
                     << "\tPlease select an option"
                     << Colors::CYAN << newl);

    if (isLoggedIn) {
        log("1. Account profile");
        log("2. House profile");
        log("3. Browse houses");
        log("4. Logout");
    } else {
        log("1. Sign up");
        log("2. Login");
        log("3. Browse houses");
    }

    log(newl << Colors::RED << "-1. Exit program" << Colors::RESET);
    log(DIVIDER << newl);
}
}  // namespace HouseExchanger