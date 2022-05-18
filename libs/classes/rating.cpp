#include "rating.h"

#include <string>

namespace HouseExchanger {
Rating::Rating() {}

// Destructor
Rating::~Rating() {}

// Setters
void Rating::setHouse(House* house) {
    this->house = house;
}

void Rating::setAuthor(Member* author) {
    this->author = author;
}

void Rating::setContent(string content) {
    this->content = content;
}

// Getters
House* Rating::getHouse() {
    return this->house;
}

Member* Rating::getAuthor() {
    return this->author;
}

string Rating::getContent() {
    return this->content;
}
}  // namespace HouseExchanger