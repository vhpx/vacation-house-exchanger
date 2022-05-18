#include "guest.h"

#include <iostream>

#define newl "\n"                      // skip 1 line
#define log(x) std::cout << x << newl  // Print with newline

namespace HouseExchanger {
//* Guest class
// Default constructor
Guest::Guest() {}

// Destructor
Guest::~Guest() {}

void Guest::signUp() {}
void Guest::login() {}

void Guest::viewHouseDetail(House* house) {
    log("Location: " + house->getLocation());
    log("Description: " + house->getDescription());
    log("Listing start: " + house->getListingStart());
    log("Listing end: " + house->getListingEnd());
    log("Consumption points: " + std::to_string(house->getConsumptionPts()));
}
}  // namespace HouseExchanger