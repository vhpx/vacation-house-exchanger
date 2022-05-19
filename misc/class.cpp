#include <iostream>
#include <vector>

//* Helper preprocessor macros
// Miscellaneous macros
#define newl "\n"     // skip 1 line
#define new2l "\n\n"  // skip 2 lines

// I/O macros
#define illog(x) std::cout << x                        // In-line print
#define log(x) std::cout << x << newl                  // Print with newline
#define debug(x) std::cout << #x << ": " << x << newl  // Print with variable name
#define show_error(x) std::cerr << x << newl           // Print error
#define input(x) std::cin >> x                         // Get input

using std::string;
using std::vector;

// Pre-defined classes
class System;
class House;
class Guest;
class Member;
class Request;
class Rating;
class Comment;

class Guest {
    private:
        void mem_register(){}
        void login(){}

    public:
        virtual void viewHouseDetail(House *house){}

};

class Member {
    private:
    // Member private information
        string username;    string password;
        string fullName;
        string phone;

        int creditPoint = 500;  // Default credit point

    // Owned house information
        House *house;

    // Occupier
        vector<Rating*> houseRatingScores;

    public:
    // Constructors
        Member(){}  // Default
        Member(string username, string password, string fullName, string phone) {  // Member without a house
            this->username = username;
            this->password = password;
            this->fullName = fullName;
            this->phone = phone;
        }
        Member(string username, string password, string fullName, string phone, House *house) {  // Member with a house
            this->username = username;
            this->password = password;
            this->fullName = fullName;
            this->phone = phone;
            this->house = house;
        }

    // Get private information
        string getUsername() { return username; }
        string getFullName() { return fullName; }
        string getPhone() { return phone; }

    // Get average occupier-rating score
        double getRatingScore() {
            double sum = 0;
            for (auto eachHouseRate : houseRatingScores) {
                sum += eachHouseRate->value;
            }
            return sum / houseRatingScores.size();
        }

    // lease-related activities
        void lease(Member *member){
            if(1) {
                

            }
        };

        void resume(){};

    // rental-related activities
        void viewRentHouses(vector<House*> houses){}
        void viewHouseDetails(House *house){}
        void viewHouseReviews(House *house){}
        void request(House *house){}

};

class House {
    private:
        // General info
        string location = "";
        string description = "";

        // Owner
        Member *owner = NULL;

        // House reviews
        vector<Rating*> houseRatingScores {};
        vector<Comment*> comments {};
        vector<Request*> requests {};
        
        // House's lease details
        string dateStart = "";
        string dateEnd = "";
        int consumingPointsPerDay = 0;

    public:
        House(){} // Default constructor

        // View house's general info
        string getLocation();
        string getDescription();

        // View house's lease details
        string getDateStart();
        string getDateEnd();
        int getConsumingPointsPerDay();

        // Add request, rating, or comment
        void addRequest(Request *request) { requests.push_back(request); }
        void addRating(Rating *rating) { houseRatingScores.push_back(rating); }
        void addComment(Comment *comment) { comments.push_back(comment); }

        // View all house's rental request
        void viewAllRequests() {
            for (int count = 0; count < requests.size(); count++) {
                requests[count]->viewRequest();
            }
        }

        // Respond to rental requests
        void respondToRequest(Request *request, int status) {
            request->setStatus(status);
        }

        // Display details of the house
        void viewHouseDetails(House house) {
            log("House's detail: ");
            log("Location: " << house.getLocation());
            log("Description: " << house.getDescription());
            log("Dates available for rent: " << house.getDateStart() << " - " << house.getDateEnd());
            log("Consuming points per day: " << house.getConsumingPointsPerDay());
        }

        // Get rating score of the house
        double getRatingScore() {
            double sum = 0;
            for (auto eachHouseRate : houseRatingScores) {
                sum += eachHouseRate->value;
            }
            return sum / houseRatingScores.size();
        }

};

class Request {
    private:
        string id = "";
        int status = 0;
        Member *requester = NULL;

    public:
        Request(){}  // Default constructor
        int getStatus() { return status; };
        void setStatus(int status) { status = status; };
        Member& getAuthor() { return *requester; }
        void viewRequest() { 
            log("Requester's information: ");
            log("Username: " << requester->getUsername());
            log("Full name: " << requester->getFullName());
            log("Phone number: " << requester->getPhone());
            log("Occupier-RatingScore: " << requester->getRatingScore());
            // Lacking of user's availabilty!
        }

};

class Rating {
    private:
        string id = "";
        double value = 0;
        Member *author = NULL;
    public:
        Rating(){}  // Default constructor
        int getScore() { return this->value; }
        Member& getAuthor() { return *author; }
    
    friend class Member;
    friend class House;

};

class Comment {
    private:
        string id = "";
        string content = "";
        Member *author = NULL;

    public:
        Comment(){}  // Default constructor
        string getContent() { return content; }
        Member& getAuthor() { return *author; }

};