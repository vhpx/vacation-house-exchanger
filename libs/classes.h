#ifndef CLASSES_INCLUDED
#define CLASSES_INCLUDED

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace HouseExchanger {
//* Enums
enum RequestStatus {
    PENDING,
    APPROVED,
    DENIED
};

//* prototype classes
class Member;
class House;
class Rating;
class Comment;
class Request;

class Date {
   private:
    int day;
    int month;
    int year;

   public:
    //* Default constructor
    Date();

    //* Destructor
    ~Date();

    //* Copy constructor
    Date(const Date& other);

    //* Assignment operator
    Date& operator=(const Date& other);

    //* Getters
    int getDay();
    int getMonth();
    int getYear();

    //* Setters
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    //* Other methods
    static bool isValid(string date);
    static Date parse(string date);
    static int compare(Date date1, Date date2);
    static int getDurationInDays(Date date1, Date date2);

    string toString();
    string getMonthStr();
    string toDateString();
};

class House {
   private:
    Member* owner = nullptr;
    Member* occupier = nullptr;

    string id;
    string location;
    string description = "";

    Date listingStart;
    Date listingEnd;

    int consumptionPts = 0;  // points per day
    vector<Rating*> ratings;

   public:
    //* Default constructor
    House();

    //* Destructor
    ~House();

    //* Setters
    void setOwner(Member* owner);
    void setId(string id);
    void setLocation(string location);
    void setDescription(string description);

    void setListingStart(Date listingStart);
    void setListingEnd(Date listingEnd);

    void setConsumptionPts(int points);

    //* Getters
    Member* getOwner();
    string getId();
    string getLocation();
    string getDescription();

    Date getListingStart();
    Date getListingEnd();

    int getConsumptionPts();

    //* Miscellaneous
    bool isOccupied();
    bool isAvailable(Date startingDate, Date endingDate);
    bool updateInfo();
};

class Guest {
   public:
    //* Default constructor
    Guest();

    //* Destructor
    ~Guest();

    //* Authentication methods
    virtual Member* signUp();
    virtual Member* login();

    virtual void viewHouseDetail(House* house);
};

class Member : public Guest {
   private:
    string id = "";
    string username = "";
    string password = "";
    string fullName = "";
    string phone = "";

    House* house = nullptr;
    int creditPoints = 500;

   public:
    //* Default constructor
    Member();

    //* Destructor
    ~Member();

    //* Authentication methods
    // Override Guest methods to display error message.
    Member* signUp();
    Member* login();
    bool logout();

    bool verifyPassword(string password);
    bool changePassword();

    bool updateInfo();
    bool deleteProfile();

    //* Setters
    void setId(string id);
    void setUsername(string username);
    void setPassword(string password);
    void setFullName(string fullName);
    void setPhone(string phone);
    void setHouse(House* house);
    void setCreditPoints(int creditPoints);

    //* Getters
    string getId();
    string getUsername();
    string getPassword();
    string getFullName();
    string getPhone();
    House* getHouse();
    int getCreditPoints();

    bool listHouse();
    bool unlistHouse();

    void viewHouseDetail(House* house);
    bool isEligibleToBook(House* house, Date staringDate, Date endingDate);
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
    void setId(string id);
    void setHouse(House* house);
    void setAuthor(Member* author);
    void setContent(string content);

    // Getters
    string getId();
    House* getHouse();
    Member* getAuthor();
    string getContent();
};

class Request {
   private:
    string id = "";
    House* house = nullptr;
    Member* requester = nullptr;

    Date startingDate = Date();
    Date endingDate = Date();

    int status = PENDING;

   public:
    // Default constructor
    Request();

    // Destructor
    ~Request();

    // Setters
    void setId(string id);
    void setHouse(House* house);
    void setRequester(Member* requester);
    void setStatus(int status);

    // Getters
    string getId();
    House* getHouse();
    Member* getRequester();
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
    void setId(string id);
    void setHouse(House* house);
    void setAuthor(Member* author);
    void setContent(string content);

    // Getters
    string getId();
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
    Member* signUp(Member member);
    Member* login(string username, string password);
    bool logout();

    bool changePassword(string newPassword, Member* member);
    bool changePassword(string oldPassword, string newPassword);

    bool updateProfile(Member* member);

    bool deleteProfile(Member* member);
    bool deleteProfile(string password);

    // Utility methods
    string generateId();
    void notify(string message, string color);

    // Resouce management methods
    void getAvailableHouses(vector<House*>& buffer, bool eligibleOnly, string location, Date startingDate, Date endingDate);
    void displayHouseBrowser(bool eligibleOnly, string location, Date startingDate, Date endingDate);

    Member* addMember(Member member, string id = "");
    House* addHouse(House house, string id = "");
    Rating* addRating(Rating rating, string id = "");
    Comment* addComment(Comment comment, string id = "");
    Request* addRequest(Request request, string id = "");

    Member* getMember(string id);
    House* getHouse(string id);
    Rating* getRating(string id);
    Comment* getComment(string id);
    Request* getRequest(string id);

    // void deleteMember(Member* member);
    // void deleteHouse(House* house);
    // void deleteRating(Rating* rating);
    // void deleteComment(Comment* comment);
    // void deleteRequest(Request* request);

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

    // System control methods
    bool initialize();
    bool shutdown();

    //* Current user
    Member* getCurrentMember();
    bool isLoggedIn();
    bool isAdmin();

    bool unlistCurrentHouse();

    bool isLocationAvailable(string location);
    void displayAvailableLocations();

    void showUserProfile();
    void showUserHouseDetails();
};
}  // namespace HouseExchanger

#endif  // CLASSES_INCLUDED