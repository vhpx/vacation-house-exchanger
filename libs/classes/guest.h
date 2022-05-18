#pragma once

#include "house.h"

namespace HouseExchanger {
class Guest {
   private:
    void signUp();
    void login();

   public:
    // Default constructor
    Guest();

    // Destructor
    ~Guest();

    virtual void viewHouseDetail(House* house);
};
}  // namespace HouseExchanger