#include "request.h"

namespace HouseExchanger {
Request::Request() {}

// Destructor
Request::~Request() {}

// Setters
void Request::setHouse(House* house) {
    this->house = house;
}

void Request::setRequester(Member* requester) {
    this->requester = requester;
}

void Request::setContent(string content) {
    this->content = content;
}

// Getters
House* Request::getHouse() {
    return this->house;
}

Member* Request::getRequester() {
    return this->requester;
}

string Request::getContent() {
    return this->content;
}
}  // namespace HouseExchanger