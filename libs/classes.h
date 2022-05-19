#ifndef CLASSES_INCLUDED
#define CLASSES_INCLUDED

#include <string>
#include <vector>

using std::string;
using std::vector;

enum RequestStatus {
    PENDING,
    APPROVED,
    DENIED
};

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
   public:
    // Default constructor
    Guest();

    // Destructor
    ~Guest();

    // Authentication methods
    virtual bool signUp();
    virtual bool login();

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

    // Authentication methods
    // Override Guest methods to display error message.
    bool signUp();
    bool login();
    bool logout();

    // Setters
    void setId(string id);
    void setUsername(string username);
    void setPassword(string password);
    void setFullName(string fullName);
    void setPhone(string phone);

    // Getters
    string getId();
    string getUsername();
    string getPassword();
    string getFullName();
    string getPhone();

    int getCreditPoint();

    House* getHouse();

    void viewHouseDetail(House* house);
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
    int status = RequestStatus::PENDING;

   public:
    // Default constructor
    Request();

    // Destructor
    ~Request();

    // Setters
    void setHouse(House* house);
    void setRequester(Member* requester);
    void setContent(string content);
    void setStatus(int status);

    // Getters
    House* getHouse();
    Member* getRequester();
    string getContent();
    int getStatus();
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
    // Singleton instance
    static System* instancePtr;

    // Default constructor
    System();

    // System data
    vector<string> availableLocations = {"Hanoi", "Saigon", "Da Nang"};

    vector<Member> members;
    vector<House> houses;
    vector<Rating> ratings;
    vector<Comment> comments;
    vector<Request> requests;

    // Current user data
    Member* currentMember = nullptr;
    bool isUserLoggedIn = false;
    bool isUserAdmin = false;

    // Setters
    void setCurrentMember(Member* member);
    void setIsLoggedIn(bool isLoggedIn);
    void setIsAdmin(bool isAdmin);

   public:
    //* System methods
    // Destructor
    ~System();

    // Singleton pattern
    static System* getInstance();

    // Authentication methods
    bool signUp(Member member);
    bool login(string username, string password);
    bool logout();

    // Utility methods
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

    //* Current user
    Member* getCurrentMember();
    bool isLoggedIn();
    bool isAdmin();
};
}  // namespace HouseExchanger

#endif  // CLASSES_INCLUDED