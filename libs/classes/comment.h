#pragma once

#include <string>

#include "member.h"

namespace HouseExchanger {
class Comment {
   private:
    House* house = nullptr;
    Member* author = nullptr;
    string content = "";

   public:
    // Default constructor
    Comment();

    // Destructor
    ~Comment();

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