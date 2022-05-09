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

class House {
   private:
   public:
    // constructors
};

class Member {
   private:
   public:
    // constructors
};

class Registered_Member : public Member {
   private:
   public:
    // constructors
};

class Non_Registered_Member : public Member {
   private:
   public:
    // constructors
};