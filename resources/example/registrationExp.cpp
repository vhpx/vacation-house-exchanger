/*  Very basic code example to illustrate account registration process
    Of course, you can do it in another way if appropriate.

    Note: Complete development should be done with quality
    (e.g. check input validity, use private attributes for data encapsulation,
    all methods and attributes should belong to classes, etc...)
*/

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

class Acc {
   public:
    string username;
    string pwd;
};

class System {
   public:
    vector<Acc *> users;
    System(){};
};

int main() {
    System appSys;  // An Object to manage the whole system

    // Non-member do registration
    Acc *newAcc = new Acc();
    cout << "-----Register account--------\n";
    cout << "Please enter username: ";
    cin >> newAcc->username;

    cout << "Please enter password: ";
    cin >> newAcc->pwd;

    // Store account into the system (if the registration is successful)
    appSys.users.push_back(newAcc);

    // Check:
    cout << "All accounts in the system: \n";
    for (Acc *eachUser : appSys.users) {
        cout << "Name = " << eachUser->username << ", pwd = " << eachUser->pwd;
    }

    return 0;
}