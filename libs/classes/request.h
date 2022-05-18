#pragma once

#include <string>

#include "house.h"
#include "member.h"

namespace HouseExchanger {
class Request {
   private:
    House* house = nullptr;
    Member* requester = nullptr;
    string content = "";

   public:
    // Default constructor
    Request();

    // Destructor
    ~Request();

    // Setters
    void setHouse(House* house);
    void setRequester(Member* requester);
    void setContent(string content);

    // Getters
    House* getHouse();
    Member* getRequester();
    string getContent();
};
}  // namespace HouseExchanger