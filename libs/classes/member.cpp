#include "member.h"

namespace HouseExchanger {
Member::Member() {}

// Destructor
Member::~Member() {}

// Setters
void Member::setUsername(string username) {
    this->username = username;
}

void Member::setPassword(string password) {
    this->password = password;
}

void Member::setFullName(string fullName) {
    this->fullName = fullName;
}

void Member::setPhone(string phone) {
    this->phone = phone;
}

// Getters
string Member::getUsername() {
    return this->username;
}

string Member::getFullName() {
    return this->fullName;
}

string Member::getPhone() {
    return this->phone;
}

int Member::getCreditPoint() {
    return this->creditPoint;
}

House* Member::getHouse() {
    return this->house;
}
}  // namespace HouseExchanger