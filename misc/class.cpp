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

class Rating;
class Comment;
class Request;
class House;
class Guess;
class Member;
class System;

class Rating {
   private:
      public:
    // constructors
    double value;
    Rating(int value);
    int getScore();
};

class Comment {
   private:
    string content;

    House *house;

   public:
    // constructors
    Comment(string content);
    string getContent();
};

class Request {
   private:
    int status;

    House *house;

   public:
    // constructors
    Request(int status);
    int getStatus();

    void viewRequest();
    void setStatus(int status);
};

class House {
   private:
    // General Info
    string location;
    string description;

    // Owner
    Member *owner;

    // House Reviews
    vector<Rating *> houseRatingScores;
    vector<Comment> Comments;
    vector<Request> Requests;

    // House lease details
    string dateStart;
    string dateEnd;
    int consumingPointsPerDev;

   public:
    // constructors
    House(string location, string description, string dateStart, string dateEnd, int consumingPointsPerDev, vector<Member> members, vector<Rating> ratings);

    // House lease details
    string getDateStart();
    string getDateEnd();
    string getLocation();
    string getDescription();

    int getConsumingPointsPerDev();

    // Something about house
    void addRating(Rating *rating) {
        houseRatingScores.push_back(rating);
    }

    void addRequest(Request request) {
        Requests.push_back(request);
    }

    void addComment(Comment comment) {
        Comments.push_back(comment);
    }

    // View all current house renting request
    void viewAllRequests() {
        for (int i = 0; i < Requests.size(); i++) {
            Requests[i].viewRequest();
        }
    }

    // Respond to request
    void respondToRequest(Request request, int status) {
        request.setStatus(status);
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