#include <iostream>

#include "./classes/house.h"

#define newl "\n"                      // skip 1 line
#define log(x) std::cout << x << newl  // Print with newline

using namespace HouseExchanger;

int main() {
    House *house = new House();

    house->setLocation("Hanoi");
    house->setDescription("This is a house in Hanoi");
    house->setListingStart("2020-05-01");
    house->setListingEnd("2020-05-31");
    house->setConsumptionPts(100);

    log("Location: " + house->getLocation());
    log("Description: " + house->getDescription());
    log("Listing start: " + house->getListingStart());
    log("Listing end: " + house->getListingEnd());
    log("Consumption points: " + std::to_string(house->getConsumptionPts()));

    return 0;
}