#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace HouseExchanger {
class House {
   private:
    string location = "";
    string description = "";

    // vector<Rating*> ratings;

    string listingStart = "";
    string listingEnd = "";

    int consumptionPts = 0;  // points per day

   public:
    // Default constructor
    House();

    // Destructor
    ~House();

    // Setters
    void setLocation(string location);
    void setDescription(string description);

    void setListingStart(string listingStart);
    void setListingEnd(string listingEnd);

    void setConsumptionPts(int points);

    // Getters
    string getLocation();
    string getDescription();

    string getListingStart();
    string getListingEnd();

    int getConsumptionPts();
};
}