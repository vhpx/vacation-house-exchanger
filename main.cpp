#include <iostream>

//* Constants
#define APP_HEADER "EEET2482/COSC2082 ASSIGNMENT"
#define APP_NAME "VACATION HOUSE EXCHANGE APPLICATION"

#define LECTURER_NAME "Mr. Linh Tran"
#define GROUP_NAME "Gucci Gang"

#define AUTHOR1_INFO "s3926761, Vo Hoang Phuc"
#define AUTHOR2_INFO "s3915195, Le Cam Tu"
#define AUTHOR3_INFO "s3926793, Nguyen Pham Anh Thu"
#define AUTHOR4_INFO "s3927460, Nguyen Ngoc Luong"

#define DIVIDER "----------------------------------------------------"

//* Helper preprocessor macros
// Miscellaneous macros
#define newl '\n'
#define new2l '\n\n'

// I/O macros
#define illog(x) std::cout << x
#define log(x) std::cout << x << newl
#define debug(x) std::cout << #x << ": " << x << newl
#define show_error(x) std::cerr << x << newl
#define input(x) std::cin >> x

void displayWelcomeMsg() {
    log(newl << DIVIDER << newl);
    log(APP_HEADER);
    log(APP_NAME);

    log(newl << DIVIDER << newl);
    log("Instructor: " << LECTURER_NAME);
    log("Group: " << GROUP_NAME);

    log(newl << DIVIDER);
    log("\t\t\tAuthors");
    log(DIVIDER << newl);

    log(AUTHOR1_INFO);
    log(AUTHOR2_INFO);
    log(AUTHOR3_INFO);
    log(AUTHOR4_INFO << newl);
}

int main() {
    displayWelcomeMsg();

    return 0;
}