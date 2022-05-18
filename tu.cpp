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

    public:
        virtual void viewHouseDetail(House *house){
            
        }
};

class Member : public Guest {
    private:
    // Member private information
        string username;
        string password;
        string fullName;
        string phone;

        int creditPoint = 500;    // Default credit point

    // Owned house information
        House *house;
        // Rating

        // Occupier

    public:
    // constructors
        Member(){} // default

        Member(string username, string password, string fullName, string phone){    // member without a house
            this->username = username;
            this->password = password;
            this->fullName = fullName;
            this->phone = phone;
        }

        Member(string username, string password, string fullName, string phone, House *house){    // member with a house
            this->username = username;
            this->password = password;
            this->fullName = fullName;
            this->phone = phone;
            this->house = house;
        }

    // lease-related activities
        void lease(Member *member);
        void resume();

    // rental-related activities
        void viewLeasedHouseList(vector<House*> houses){

        }



};