#include <iostream>
#include <vector>

//* Helper preprocessor macros
// Miscellaneous macros
#define newl "\n"     // skip 1 line
#define new2l "\n\n"  // skip 2 lines

// I/O macros
#define illog(x) std::cout << x                         // In-line print
#define log(x) std::cout << x << newl                   // Print with newline
#define debug(x) std::cout << #x << ": " << x << newl   // Print with variable name
#define show_error(x) std::cerr << x << newl            // Print error
#define input(x) std::cin >> x                          // Get input
#define inputStr(x) std::getline(std::cin, x)           // Input string

using std::string;
using std::vector;

// Pre-defined classes
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
        string getAdName(){
            return ad_username;
        }

        string getAdPassword(){
            return ad_password;
        }

        bool checkSignUp(string username, string password){

        }

        void saveMembers(){}
        void saveHouses(){}

        void viewMembers(){}
        void viewHouses(){}
};

class House {
    private:
        // General information
        string location;
        string description;

        // House owner
        Member *owner;

        // House reviews
        vector<Rating*> houseRatingScores;
        vector<Comment*> comments;
        vector<Request*> requests;

        // House lease details
        string dateStart;
        string dateEnd;
        int consumingPointsPerDay;

   public:
        // constructors
        House(string location, string description, string dateStart, string dateEnd, int consumingPointsPerDev, vector<Member> members, vector<Rating> ratings);
        
        // House lease details
        string getDateStart();
        string getDateEnd();
        int getConsumingPointsPerDev();

        // House Reviews
        void addRating(Rating rating);
        void addComments(Comment comment);
        void addRequest(Request request);

        // House owner
        void viewAllRequests();
        void viewHouseDetails(House house);
   private:
        string location;
        string description;
        string dateStart;
        string dateEnd;
        int consumingPointsPerDev;

        House(string location, string description, string dateStart, string dateEnd, int consumingPointsPerDev, vector<Member> members, vector<Rating> ratings);

        vector<Rating> houseRatingScore;
   public:
    // constructors

};

class Guest {
    private:

        void mem_register(){
        }

        void login(){
            string username, password;

            log("Enter username and password: ");
            inputStr(username);    inputStr(password);

            
            
        }

    public:
        virtual void viewHouseDetail(House *house){
            
        }
};

class Member : public Guest {
    private:
    // Member private information
        string username;    string password;
        string fullName;
        string phone;

        int creditPoint = 500;    // Default credit point

    // Owned house information
        House *house;

    // Occupier
        vector<Rating*> houseRatingScores;

    public:
    // constructors
        Member(){}    // default

        Member(string username, string password, string fullName, string phone) {    // member without a house
            this->username = username;
            this->password = password;
            this->fullName = fullName;
            this->phone = phone;
        }

        Member(string username, string password, string fullName, string phone, House *house) {    // member with a house
            this->username = username;
            this->password = password;
            this->fullName = fullName;
            this->phone = phone;
            this->house = house;
        }

    // get average occupier-rating score
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
        void viewRentHouse(vector<House*> houses){
        }

        void viewHouseDetail(House *house){      
        }

        void viewReview(House *house){
        }

        void request(House *house){
        }

};

class Rating {
    private:
        double value;

    public:
    // constructors

    friend class Member;
};

class Comment {
    private:
        string content;

        House *house;

    public:
    // constructors
};

class Request {
    private:
        int status;

        House *house;

    public:
    // constructors
};