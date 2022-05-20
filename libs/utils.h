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
void displayProfileMenu();
void displayHouseDetailsMenu();
void displayHouseBrowserMenu();
}  // namespace HouseExchanger