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

class Request {
    private:
        string id = "";
        int status = 0;
        Member *author = NULL;

    public:
        Request(){}  // Default constructor
        int getStatus() { return this->status; };
        void setStatus(int status) { this->status = status; };
        Member& getAuthor() { return *author; }

};

class Rating {
    private:
        string id = "";
        double value = 0;
        Member *author = NULL;
    public:
        Rating(){}  // Default constructor
        int getScore() { return this->value; };
        Member& getAuthor() { return *author; }
    
    friend class House;
};

class Comment {
    private:
        string id = "";
        string content = "";
        Member *author = NULL;

    public:
        Comment(){}  // Default constructor
        string getContent() { return this->content; };
        Member& getAuthor() { return *author; }
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
        int getConsumingPointsPerDev();

        // Add request, rating, or comment
        void addRequest(Request *request) {
            requests.push_back(request);
        }

        void addRating(Rating *rating) {
            houseRatingScores.push_back(rating);
        }

        void addComment(Comment *comment) {
            comments.push_back(comment);
        }

        // View all house's rental request
        void viewAllRequests() {
            for (int count = 0; count < requests.size(); count++) {
                log("Occupier: " << requests[count]->getAuthor());
            }
        }

        // Respond to rental requests
        void respondToRequest(Request *request, int status) {
            request->setStatus(status);
        }

        // Display details of the house
        void viewHouseDetails(House house) {
            log("Location: " << house.getLocation());
            log("Description: " << house.getDescription());
            log("Date Start: " << house.getDateStart());
            log("Date End: " << house.getDateEnd());
            log("Consuming Points Per Dev: " << house.getConsumingPointsPerDev());
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