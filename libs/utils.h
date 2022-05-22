#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#include <string>
#include <vector>

namespace HouseExchanger {
//* Utilitiy functions
bool checkIfInteger(const std::string& str);

//* Core
void displayWelcomeMsg();
void displayAppHeader();
void displayMenuOptions(std::vector<std::string>& options);

//* Menus
void displayDefaultMenu();
void displayAdminMenu();
void displayProfileMenu();
void displayHouseDetailsMenu();
void displayHouseBrowserMenu();
void displayHouseSelectorMenu();
}  // namespace HouseExchanger

#endif  // UTILS_INCLUDED