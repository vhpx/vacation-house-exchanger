#pragma once

#include <string>

#include "guest.h"

using std::string;

namespace HouseExchanger {
class Member : public Guest {
   private:
    string username = "";
    string password = "";
    string fullName = "";
    string phone = "";

    int creditPoint = 500;

    House* house = nullptr;

   public:
    // Default constructor
    Member();

    // Destructor
    ~Member();

    // Setters
    void setUsername(string username);
    void setPassword(string password);
    void setFullName(string fullName);
    void setPhone(string phone);

    // Getters
    string getUsername();
    string getFullName();
    string getPhone();

    int getCreditPoint();

    House* getHouse();
};
}  // namespace HouseExchanger