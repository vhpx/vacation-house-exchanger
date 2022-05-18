#include "utils.h"

#include <iostream>

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

#define AUTHOR1_INFO "s3926761, Vo Hoang Phuc"
#define AUTHOR2_INFO "s3915195, Le Cam Tu"
#define AUTHOR3_INFO "s3926793, Nguyen Pham Anh Thu"
#define AUTHOR4_INFO "s3927460, Nguyen Ngoc Luong"

namespace HouseExchanger {
void displayWelcomeMsg() {
    skipLine();

    log(APP_HEADER);
    log(APP_NAME << newl);

    log("Instructor: " << LECTURER_NAME);
    log("Group: " << GROUP_NAME << newl);

    log(AUTHOR1_INFO);
    log(AUTHOR2_INFO);
    log(AUTHOR3_INFO);
    log(AUTHOR4_INFO);

    skipLine();
}
}  // namespace HouseExchanger