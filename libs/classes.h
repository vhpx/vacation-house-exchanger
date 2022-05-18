#ifndef CLASSES_INCLUDED
#define CLASSES_INCLUDED

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace HouseExchanger {
//* prototype classes
class Member;
class House;
class Rating;
class Comment;
class Request;

class House {
   private:
    string id = "";
    string location = "";
    string description = "";

    string listingStart = "";
    string listingEnd = "";

    int consumptionPts = 0;  // points per day
    vector<Rating*> ratings;

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

class Member : public Guest {
   private:
    string id = "";
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
    string getPassword();
    string getFullName();
    string getPhone();

    int getCreditPoint();

    House* getHouse();
};

class Rating {
   private:
    string id = "";
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

class Request {
   private:
    string id = "";
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

class Comment {
   private:
    string id = "";
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

    // Utility functions
    string generateId();

    // Loading methods
    bool loadMembers();
    bool loadHouses();
    bool loadRatings();
    bool loadComments();
    bool loadRequests();

    // Saving methods
    bool saveMembers();
    bool saveHouses();
    bool saveRatings();
    bool saveComments();
    bool saveRequests();

    // I/O bundle
    bool loadAll();
    bool saveAll();
};
}  // namespace HouseExchanger

#endif  // CLASSES_INCLUDED