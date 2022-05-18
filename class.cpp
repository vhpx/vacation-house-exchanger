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

class Member{};
class House{};
class Rating{};
class Comment{};
class Request{};

class System {
    private:
        string ad_username;
        string ad_password;
    
        vector<Member> members;
        vector<House> houses;
    
    public:
        void saveMembers();
        void saveHouses();

        void viewMembers();
        void viewHouses();
};


class House {
   private:
        // General Info
        string location;
        string description;

        // Owner
        

        // House Reviews
        vector<Rating> houseRatingScore;
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
        int getConsumingPointsPerDev();

        // House Reviews
        void addRating(Rating rating) {
            houseRatingScore.push_back(rating);
        }

        void addRequest(Request request) {
            Requests.push_back(request);
        }

        void addComment(Comment comment) {
            Comments.push_back(comment);
        }

        // House owner
        void viewAllRequests();
        void viewHouseDetails(House house);

        // Get average rating score.
        double getAverageRatingScore() {
            double sum = 0;
            for (int i = 0; i < houseRatingScore.size(); i++) {
                sum += houseRatingScore[i].getScore();
            }
        }

};

class Guest {
    private:
        void mem_register(){

        }

    public:
        virtual void viewHouseDetail(House *house){
            
        }
};

class Member : public Guest {
    private:
        string username;
        string password;
        string fullName;
        string phone; 

        int creditPoint = 500;

        House *house;

    public:
    // constructors
};

class Rating {
    private:
        double value;


    public:  
        // constructors
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
};