#pragma once

#include <string>

#include "house.h"
#include "member.h"

namespace HouseExchanger {
class Rating {
   private:
    House* house = nullptr;
    Member* author = nullptr;
    string content = "";

   public:
    // Default constructor
    Rating();

    // Destructor
    ~Rating();

    // Setters
    void setHouse(House* house);
    void setAuthor(Member* author);
    void setContent(string content);

    // Getters
    House* getHouse();
    Member* getAuthor();
    string getContent();
};
}  // namespace HouseExchanger