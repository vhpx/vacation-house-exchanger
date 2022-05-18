#pragma once

#include <string>

#include "comment.h"
#include "rating.h"
#include "request.h"

namespace HouseExchanger {
class System {
   private:
    vector<string> availableLocations = {"Hanoi", "Saigon", "Da Nang"};

    vector<Member> members;
    vector<House> houses;
    vector<Rating> ratings;
    vector<Comment> comments;
    vector<Request> requests;

   public:
    // Default constructor
    System();

    // Destructor
    ~System();

    void loadMembers();
    void loadHouses();
    void loadRatings();
    void loadComments();
    void loadRequests();

    void saveMembers();
    void saveHouses();
    void saveRatings();
    void saveComments();
    void saveRequests();

    void loadAll();
    void saveAll();
};
}  // namespace HouseExchanger