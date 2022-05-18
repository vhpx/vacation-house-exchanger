#include "house.h"

#include <iostream>

using std::string;
using std::vector;

#define newl "\n"                      // skip 1 line
#define log(x) std::cout << x << newl  // Print with newline

namespace HouseExchanger {
// Default constructor
House::House() {}

// Destructor
House::~House() {}

// Setters
void House::setLocation(string location) {
    this->location = location;
}

void House::setDescription(string description) {
    this->description = description;
}

void House::setListingStart(string listingStart) {
    this->listingStart = listingStart;
}

void House::setListingEnd(string listingEnd) {
    this->listingEnd = listingEnd;
}

void House::setConsumptionPts(int points) {
    this->consumptionPts = points;
}

// Getters
string House::getLocation() {
    return this->location;
}

string House::getDescription() {
    return this->description;
}

string House::getListingStart() {
    return this->listingStart;
}

string House::getListingEnd() {
    return this->listingEnd;
}

int House::getConsumptionPts() {
    return this->consumptionPts;
}
}  // namespace HouseExchanger