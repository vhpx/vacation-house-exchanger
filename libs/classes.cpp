#include "classes.h"

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "colors.h"

//* Constants
// Preferences
#define SHOW_PROCESSED_AMOUNT true  // Log out the amount of loaded / saved data

// Data
const string DATA_PATH = "data/";

const string MEMBERS_FILE = "members.dat";
const string HOUSES_FILE = "houses.dat";
const string RATINGS_FILE = "ratings.dat";
const string COMMENTS_FILE = "comments.dat";

//* Helper preprocessor macros
// I/O macros
#define newl "\n"  // skip 1 line
#define DIVIDER "---------------------------------------"

#define illog(x) std::cout << x  // In-line print (DEFAULT)
#define skipLine() illog(newl)   // Skip 1 line in terminal

#define illogInfo(x) std::cout << Colors::YELLOW << x << Colors::RESET    // In-line print (YELLOW)
#define illogError(x) std::cout << Colors::RED << x << Colors::RESET      // In-line print (RED)
#define illogSuccess(x) std::cout << Colors::GREEN << x << Colors::RESET  // In-line print (GREEN)

#define log(x) illog(x << newl)                // Print with newline (DEFAULT)
#define logInfo(x) illogInfo(x << newl)        // Print with newline (YELLOW)
#define logError(x) illogError(x << newl)      // Print with newline (RED)
#define logSuccess(x) illogSuccess(x << newl)  // Print with newline (GREEN)

// Input string with/without spaces
#define inputStr(x)            \
    illog(Colors::CYAN);       \
    std::getline(std::cin, x); \
    illog(Colors::RESET)

// Input string with spaces or any other types
#define input(x)         \
    illog(Colors::CYAN); \
    std::cin >> x;       \
    illog(Colors::RESET)

using std::string;
using std::vector;

const string REQUESTS_FILE = "requests.dat";

string getFilePath(const string& fileName) {
    return DATA_PATH + fileName;
}

// UUID generator source:
// https://stackoverflow.com/a/60198074/18811079
namespace uuid {
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> dis(0, 15);
static std::uniform_int_distribution<> dis2(8, 11);

std::string generate_uuid_v4() {
    std::stringstream ss;
    ss << std::hex;

    for (int i = 0; i < 8; i++)
        ss << dis(gen);
    ss << "-";

    for (int i = 0; i < 4; i++)
        ss << dis(gen);
    ss << "-4";

    for (int i = 0; i < 3; i++)
        ss << dis(gen);
    ss << "-";
    ss << dis2(gen);

    for (int i = 0; i < 3; i++)
        ss << dis(gen);

    ss << "-";
    for (int i = 0; i < 12; i++)
        ss << dis(gen);

    return ss.str();
}
}  // namespace uuid

namespace HouseExchanger {
//* House Class
// Default constructor
House::House() {}

// Destructor
House::~House() {}

// Setters
void House::setOwner(Member* owner) {
    this->owner = owner;
}

void House::setId(string id) {
    this->id = id;
}

void House::setLocation(string location) {
    this->location = location;
}

void House::setDescription(string description) {
    this->description = description;
}

void House::setListingStart(string listingStart) {
    this->listingStart = listingStart;
}

void House::setListingEnd(string listingEnd) {
    this->listingEnd = listingEnd;
}

void House::setConsumptionPts(int points) {
    this->consumptionPts = points;
}

// Getters
Member* House::getOwner() {
    return owner;
}

string House::getId() {
    return this->id;
}

string House::getLocation() {
    return this->location;
}

string House::getDescription() {
    return this->description;
}

string House::getListingStart() {
    return this->listingStart;
}

string House::getListingEnd() {
    return this->listingEnd;
}

int House::getConsumptionPts() {
    return this->consumptionPts;
}

//* Guest class
// Default constructor
Guest::Guest() {}

// Destructor
Guest::~Guest() {}

Member* Guest::signUp() {
    //* Sign up
    // Create a new member object to store the data.
    Member member;

    // Get user input.
    string username, password, fullName, phone;

    illogInfo("Enter your username: ");
    input(username);

    illogInfo("Enter your password: ");
    input(password);

    illogInfo("Enter your full name: ");

    std::cin.ignore();
    inputStr(fullName);

    illogInfo("Enter your phone number: ");
    input(phone);

    // Set member data.
    member.setUsername(username);
    member.setPassword(password);
    member.setFullName(fullName);
    member.setPhone(phone);

    // Sign up the member through the System.
    return System::getInstance()->signUp(member);
}

Member* Guest::login() {
    //* Login
    // Get user input.
    string username, password;

    illogInfo("Enter your username: ");
    input(username);

    illogInfo("Enter your password: ");
    input(password);

    // Login the member through the System.
    return System::getInstance()->login(username, password);
}

void Guest::viewHouseDetail(House* house) {
    logInfo("Location: " << Colors::GREEN << house->getLocation());
    logInfo("Description: " << Colors::GREEN << house->getDescription());
}

//* Member class
// Default constructor
Member::Member() {}

// Destructor
Member::~Member() {}

Member* Member::signUp() {
    logError("You are already logged in.");
    logError("Operation failed.");
    return this;
}

Member* Member::login() {
    logError("You are already logged in.");
    logError("Operation failed.");
    return this;
}

bool Member::logout() {
    return System::getInstance()->logout();
}

bool Member::verifyPassword(string password) {
    return password.compare(this->password) == 0;
}

bool Member::changePassword() {
    // Get user input.
    string oldPassword, newPassword;

    illogInfo("Enter your old password: ");
    input(oldPassword);

    illogInfo("Enter your new password: ");
    input(newPassword);

    // Change the password through the System.
    bool changeSuccessful = System::getInstance()->changePassword(oldPassword, newPassword);

    skipLine();
    if (changeSuccessful) {
        logSuccess("Password changed successfully.");
    } else {
        logError("Password change failed.");
    }

    skipLine();
    std::system("PAUSE");  // Only works on Windows.

    return changeSuccessful;
}

bool Member::updateProfile() {
    // Get user input.
    string fullName, phone;

    illogInfo("Enter your new full name: ");

    std::cin.ignore();
    inputStr(fullName);

    illogInfo("Enter your new phone number: ");
    input(phone);

    if (fullName.compare(this->fullName) != 0)
        setFullName(fullName);

    if (phone.compare(this->phone) != 0)
        setPhone(phone);

    skipLine();
    logSuccess("Profile updated successfully.");

    skipLine();
    std::system("PAUSE");  // Only works on Windows.

    return true;
}

bool Member::deleteProfile() {
    // Get user input.
    string password;

    illogInfo("Enter your password: ");
    input(password);

    // Delete the member through the System.
    bool successful = System::getInstance()->deleteProfile(password);

    skipLine();
    if (successful) {
        logSuccess("Profile deleted successfully.");
    } else {
        logError("Profile deletion failed.");
    }

    skipLine();
    std::system("PAUSE");  // Only works on Windows.

    return successful;
}

// Setters
void Member::setId(string id) {
    this->id = id;
}

void Member::setUsername(string username) {
    this->username = username;
}

void Member::setPassword(string password) {
    this->password = password;
}

void Member::setFullName(string fullName) {
    this->fullName = fullName;
}

void Member::setPhone(string phone) {
    this->phone = phone;
}

void Member::setHouse(House* house) {
    this->house = house;
}

// Getters
string Member::getId() {
    return this->id;
}

string Member::getUsername() {
    return this->username;
}

string Member::getPassword() {
    return this->password;
}

string Member::getFullName() {
    return this->fullName;
}

string Member::getPhone() {
    return this->phone;
}

int Member::getCreditPoint() {
    return this->creditPoint;
}

House* Member::getHouse() {
    return this->house;
}

bool Member::setupHouse() {
    // Get user input.
    string location, description, listingStart, listingEnd;
    int consumptionPts;

    System* system = System::getInstance();
    system->displayAvailableLocations();

    illogInfo("House location: ");

    if (std::cin.peek() == '\n') std::cin.ignore();
    inputStr(location);

    // Check if the location is available.
    if (!system->isLocationAvailable(location)) {
        skipLine();
        logError("Location is not available.");

        skipLine();
        std::system("PAUSE");  // Only works on Windows.

        return false;
    }

    illogInfo("House description: ");
    inputStr(description);

    illogInfo("Listing start date (dd/mm/yyyy): ");
    input(listingStart);

    illogInfo("Listing end date (dd/mm/yyyy): ");
    input(listingEnd);

    illogInfo("Consumption points: ");
    input(consumptionPts);

    // Create a new house object to store the data.
    House house;

    // Set house data.
    house.setOwner(this);
    house.setLocation(location);
    house.setDescription(description);
    house.setListingStart(listingStart);
    house.setListingEnd(listingEnd);
    house.setConsumptionPts(consumptionPts);

    // Add the house to the system.
    House* savedHouse = System::getInstance()->addHouse(house);

    skipLine();
    if (savedHouse != nullptr) {
        setHouse(savedHouse);
        logSuccess("House added successfully.");
    } else {
        logError("House setup failed.");
    }

    skipLine();
    std::system("PAUSE");  // Only works on Windows.

    return savedHouse != nullptr;
}

void Member::viewHouseDetail(House* house) {
    logInfo("Location: " << Colors::GREEN << house->getLocation());
    logInfo("Description: " << Colors::GREEN << house->getDescription());
    logInfo("Listing start: " << Colors::GREEN << house->getListingStart());
    logInfo("Listing end: " << Colors::GREEN << house->getListingEnd());
    logInfo("Consumption points: " << Colors::GREEN << house->getConsumptionPts());
}

//* Rating class
// Default constructor
Rating::Rating() {}

// Destructor
Rating::~Rating() {}

// Setters
void Rating::setId(string id) {
    this->id = id;
}

void Rating::setHouse(House* house) {
    this->house = house;
}

void Rating::setAuthor(Member* author) {
    this->author = author;
}

void Rating::setContent(string content) {
    this->content = content;
}

// Getters
string Rating::getId() {
    return this->id;
}

House* Rating::getHouse() {
    return this->house;
}

Member* Rating::getAuthor() {
    return this->author;
}

string Rating::getContent() {
    return this->content;
}

//* Request class
// Default constructor
Request::Request() {}

// Destructor
Request::~Request() {}

// Setters
void Request::setId(string id) {
    this->id = id;
}

void Request::setHouse(House* house) {
    this->house = house;
}

void Request::setRequester(Member* requester) {
    this->requester = requester;
}

void Request::setContent(string content) {
    this->content = content;
}

void Request::setStatus(int status) {
    this->status = status;
}

// Getters
string Request::getId() {
    return this->id;
}

House* Request::getHouse() {
    return this->house;
}

Member* Request::getRequester() {
    return this->requester;
}

string Request::getContent() {
    return this->content;
}

int Request::getStatus() {
    return this->status;
}

//* Comment class
// Default constructor
Comment::Comment() {}

// Destructor
Comment::~Comment() {}

// Setters
void Comment::setId(string id) {
    this->id = id;
}

void Comment::setHouse(House* house) {
    this->house = house;
}

void Comment::setAuthor(Member* author) {
    this->author = author;
}

void Comment::setContent(string content) {
    this->content = content;
}

// Getters
string Comment::getId() {
    return this->id;
}

House* Comment::getHouse() {
    return this->house;
}

Member* Comment::getAuthor() {
    return this->author;
}

string Comment::getContent() {
    return this->content;
}

//* System class
// Default constructor
System::System() {}

// Destructor
System::~System() {
    delete this->instancePtr;
}

// Singleton instance
System* System::instancePtr = nullptr;

// Static getInstance method
System* System::getInstance() {
    if (instancePtr == nullptr) {
        instancePtr = new System();
    }
    return instancePtr;
}

// Current user methods
void System::setCurrentMember(Member* member) {
    this->currentMember = member;
}

void System::setIsLoggedIn(bool isLoggedIn) {
    this->isUserLoggedIn = isLoggedIn;
}

void System::setIsAdmin(bool isAdmin) {
    this->isUserAdmin = isAdmin;
}

// Utility methods
string System::generateId() {
    return uuid::generate_uuid_v4();
}

void System::notify(string message, string color = Colors::YELLOW) {
    logInfo(Colors::CYAN << Colors::BOLD << "SYSTEM" << Colors::RESET << " - " << color << message << Colors::RESET);
}

// Authentication methods
Member* System::signUp(Member member) {
    Member* newMember = addMember(member);

    if (newMember == nullptr) {
        logError(newl << "Sign up failed.");
        return nullptr;
    }

    // Update current member
    setCurrentMember(newMember);
    setIsLoggedIn(true);

    // Display success message
    logSuccess(newl << "Sign up successful.");
    return newMember;
}

Member* System::login(string username, string password) {
    skipLine();

    // Check if username exists
    for (int i = 0; i < members.size(); i++) {
        if (members[i].getUsername().compare(username) == 0) {
            // Check if password is correct
            if (members[i].getPassword().compare(password) == 0) {
                // Update current member
                setCurrentMember(&members[i]);
                setIsLoggedIn(true);

                // Display success message
                logSuccess("Login successful.");
                return &members[i];
            } else {
                logError("Incorrect password.");
                return nullptr;
            }
        }
    }

    // Display failure message
    logError("Username not found.");
    return nullptr;
}

bool System::logout() {
    // Update current member
    setCurrentMember(nullptr);
    setIsLoggedIn(false);
    setIsAdmin(false);

    // Display success message
    logSuccess("Logout successful.");
    return true;
}

bool System::changePassword(string newPassword, Member* member) {
    // Allow for change password without old password
    // only if the current user is an admin.
    if (!isAdmin()) {
        logError("You must be an admin to change password without the old one.");
        return false;
    }
    member->setPassword(newPassword);
    return true;
}

bool System::changePassword(string oldPassword, string newPassword) {
    if (currentMember->getPassword().compare(oldPassword) == 0) {
        currentMember->setPassword(newPassword);
        return true;
    } else {
        skipLine();
        logError("Incorrect old password.");

        return false;
    }
}

bool System::deleteProfile(Member* member) {
    // Allow for delete profile without old password
    // only if the current user is an admin.
    if (!isAdmin()) {
        logError("You must be an admin to delete a profile without a password.");
        return false;
    }

    for (int i = 0; i < members.size(); i++) {
        if (members[i].getId().compare(member->getId()) == 0) {
            members.erase(members.begin() + i);
            logSuccess("Profile deleted.");
            return true;
        }
    }

    // Display failure message
    logError("Profile not found.");
    return false;
}

bool System::deleteProfile(string password) {
    skipLine();

    for (int i = 0; i < members.size(); i++) {
        if (members[i].getId().compare(currentMember->getId()) == 0) {
            if (members[i].getPassword().compare(password) != 0) {
                logError("Incorrect password.");
                return false;
            }

            members.erase(members.begin() + i);

            // Update current member
            setCurrentMember(nullptr);
            setIsLoggedIn(false);
            setIsAdmin(false);

            return true;
        }
    }

    // Display failure message
    logError("Profile not found.");
    return false;
}

// User related methods
void System::showHouses() {
    if (houses.size() == 0) {
        logInfo("There are no houses on our system.");
        return;
    }

    // Display all houses
    for (int i = 0; i < houses.size(); i++) {
        logInfo(newl << "House " + std::to_string(i + 1) + ":" << newl);

        logInfo("Location: " + houses[i].getLocation());
        logInfo("Description: " + houses[i].getDescription());

        if (isUserLoggedIn || isUserAdmin) {
            logInfo("Listing start: " + houses[i].getListingStart());
            logInfo("Listing end: " + houses[i].getListingEnd());
            logInfo("Consumption points: " + std::to_string(houses[i].getConsumptionPts()));
        }
    }
}

// Resouce management methods
Member* System::addMember(Member member) {
    // Check if username is already taken
    for (int i = 0; i < members.size(); i++) {
        if (members[i].getUsername() == member.getUsername()) {
            skipLine();
            illogError("Username already taken.");
            return nullptr;
        }
    }

    // Generate member ID
    string id = generateId();
    member.setId(id);

    // Add member to members vector
    members.push_back(member);
    return &members.back();
}

House* System::addHouse(House house) {
    // Generate house ID
    string id = generateId();
    house.setId(id);

    // Add house to houses vector
    houses.push_back(house);
    return &houses.back();
}

Rating* System::addRating(Rating rating) {
    // Generate rating ID
    string id = generateId();
    rating.setId(id);

    // Add rating to ratings vector
    ratings.push_back(rating);
    return &ratings.back();
}

Comment* System::addComment(Comment comment) {
    // Generate comment ID
    string id = generateId();
    comment.setId(id);

    // Add comment to comments vector
    comments.push_back(comment);
    return &comments.back();
}

Request* System::addRequest(Request request) {
    // Generate request ID
    string id = generateId();
    request.setId(id);

    // Add request to requests vector
    requests.push_back(request);
    return &requests.back();
}

bool System::loadMembers() {
    std::ifstream file;
    string filePath = getFilePath(MEMBERS_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        notify("Error: " + filePath + " not found.", Colors::RED);
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() != 5) {
            notify("Error: Invalid Member format.", Colors::RED);
            continue;
        }

        Member member;

        member.setId(tokens[0]);
        member.setUsername(tokens[1]);
        member.setPassword(tokens[2]);
        member.setFullName(tokens[3]);
        member.setPhone(tokens[4]);

        members.push_back(member);
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        notify("Loaded " + Colors::YELLOW + std::to_string(members.size()) + Colors::GREEN + " members.", Colors::GREEN);

    return true;
}

bool System::loadHouses() {
    std::ifstream file;
    string filePath = getFilePath(HOUSES_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        notify("Error: " + filePath + " not found.", Colors::RED);
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() != 7) {
            notify("Error: Invalid House format.", Colors::RED);
            continue;
        }

        System* system = System::getInstance();
        House house;

        string ownerId = tokens[0];
        Member* owner = system->getMember(ownerId);

        if (owner == nullptr) {
            notify("Error: Owner with ID " + ownerId + " not found.");
            continue;
        }

        house.setOwner(owner);

        house.setId(tokens[1]);
        house.setLocation(tokens[2]);
        house.setDescription(tokens[3]);
        house.setListingStart(tokens[4]);
        house.setListingEnd(tokens[5]);
        house.setConsumptionPts(std::stoi(tokens[6]));

        houses.push_back(house);
        owner->setHouse(&houses.back());
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        notify("Loaded " + Colors::YELLOW + std::to_string(houses.size()) + Colors::GREEN + " houses.", Colors::GREEN);

    return true;
}

bool System::loadRatings() {
    std::ifstream file;
    string filePath = getFilePath(RATINGS_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        notify("Error: " + filePath + " not found.", Colors::RED);
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() != 4) {
            notify("Error: Invalid Rating format.", Colors::RED);
            continue;
        }

        Rating rating;

        // rating.setHouse(tokens[1]);
        // rating.setAuthor(tokens[2]);
        // rating.setContent(tokens[3]);

        ratings.push_back(rating);
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        notify("Loaded " + Colors::YELLOW + std::to_string(ratings.size()) + Colors::GREEN + " ratings.", Colors::GREEN);

    return true;
}

bool System::loadComments() {
    std::ifstream file;
    string filePath = getFilePath(COMMENTS_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        notify("Error: " + filePath + " not found.", Colors::RED);
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() != 4) {
            notify("Error: Invalid Comment format.", Colors::RED);
            continue;
        }

        Comment comment;

        // comment.setHouse(tokens[1]);
        // comment.setAuthor(tokens[2]);
        // comment.setContent(tokens[3]);

        comments.push_back(comment);
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        notify("Loaded " + Colors::YELLOW + std::to_string(comments.size()) + Colors::GREEN + " comments.", Colors::GREEN);

    return true;
}

bool System::loadRequests() {
    std::ifstream file;
    string filePath = getFilePath(REQUESTS_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        notify("Error: " + filePath + " not found.", Colors::RED);
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() != 3) {
            notify("Error: Invalid Request format.", Colors::RED);
            continue;
        }

        Request request;

        // request.setHouse(tokens[1]);
        // request.setRequester(tokens[2]);
        // request.setContent(tokens[3]);

        requests.push_back(request);
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        notify("Loaded " + Colors::YELLOW + std::to_string(requests.size()) + Colors::GREEN + " requests.", Colors::GREEN);

    return true;
}

bool System::saveMembers() {
    std::ofstream file;
    string filePath = getFilePath(MEMBERS_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        notify("Error: " + filePath + " not found.", Colors::RED);
        return false;
    }

    for (Member member : members) {
        file << member.getId() << "," << member.getUsername() << ","
             << member.getPassword() << "," << member.getFullName() << ","
             << member.getPhone() << newl;
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        notify("Saved " + Colors::YELLOW + std::to_string(members.size()) + Colors::GREEN + " members.", Colors::GREEN);

    return true;
}

bool System::saveHouses() {
    std::ofstream file;
    string filePath = getFilePath(HOUSES_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        notify("Error: " + filePath + " not found.", Colors::RED);
        return false;
    }

    for (House house : houses) {
        file << house.getOwner()->getId() << ","
             << house.getId() << "," << house.getLocation() << ","
             << house.getDescription() << "," << house.getListingStart() << ","
             << house.getListingEnd() << "," << house.getConsumptionPts() << newl;
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        notify("Saved " + Colors::YELLOW + std::to_string(houses.size()) + Colors::GREEN + " houses.", Colors::GREEN);

    return true;
}

bool System::saveRatings() {
    std::ofstream file;
    string filePath = getFilePath(RATINGS_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        notify("Error: " + filePath + " not found.", Colors::RED);
        return false;
    }

    for (Rating rating : ratings) {
        file << rating.getHouse() << "," << rating.getAuthor()
             << "," << rating.getContent() << newl;
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        notify("Saved " + Colors::YELLOW + std::to_string(ratings.size()) + Colors::GREEN + " ratings.", Colors::GREEN);

    return true;
}

bool System::saveComments() {
    std::ofstream file;
    string filePath = getFilePath(COMMENTS_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        notify("Error: " + filePath + " not found.", Colors::RED);
        return false;
    }

    for (Comment comment : comments) {
        file << comment.getHouse() << "," << comment.getAuthor()
             << "," << comment.getContent() << newl;
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        notify("Saved " + Colors::YELLOW + std::to_string(comments.size()) + Colors::GREEN + " comments.", Colors::GREEN);

    return true;
}

bool System::saveRequests() {
    std::ofstream file;
    string filePath = getFilePath(REQUESTS_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        notify("Error: " + filePath + " not found.", Colors::RED);
        return false;
    }

    for (Request request : requests) {
        file << request.getHouse() << "," << request.getRequester()
             << "," << request.getContent() << newl;
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        notify("Saved " + Colors::YELLOW + std::to_string(requests.size()) + Colors::GREEN + " requests.", Colors::GREEN);

    return true;
}

bool System::initialize() {
    skipLine();
    log(DIVIDER);
    skipLine();

    notify("Loading data...\n");

    if (!loadMembers()) {
        notify("Failed to load Members.", Colors::RED);
        return false;
    }

    if (!loadHouses()) {
        notify("Failed to load Houses.", Colors::RED);
        return false;
    }

    if (!loadRatings()) {
        notify("Failed to load Ratings.", Colors::RED);
        return false;
    }

    if (!loadComments()) {
        notify("Failed to load Comments.", Colors::RED);
        return false;
    }

    if (!loadRequests()) {
        notify("Failed to load Requests.", Colors::RED);
        return false;
    }

    if (SHOW_PROCESSED_AMOUNT)
        skipLine();

    notify("Data loaded.\n", Colors::GREEN);

    return true;
}

bool System::shutdown() {
    skipLine();

    notify("Saving data...\n");

    if (!saveMembers()) {
        notify("Failed to save members.", Colors::RED);
        return false;
    }

    if (!saveHouses()) {
        notify("Failed to save houses.", Colors::RED);
        return false;
    }

    if (!saveRatings()) {
        notify("Failed to save ratings.", Colors::RED);
        return false;
    }

    if (!saveComments()) {
        notify("Failed to save comments.", Colors::RED);
        return false;
    }

    if (!saveRequests()) {
        notify("Failed to save requests.", Colors::RED);
        return false;
    }

    if (SHOW_PROCESSED_AMOUNT)
        skipLine();

    notify("Data saved.\n", Colors::GREEN);

    log(DIVIDER);
    skipLine();
    notify("Exiting...", Colors::GREEN);
    skipLine();

    return true;
}

//* Current user
Member* System::getCurrentMember() {
    return currentMember;
}

bool System::isLoggedIn() {
    return currentMember != nullptr;
}

bool System::isAdmin() {
    return isUserAdmin;
}

void System::showUserProfile() {
    if (currentMember == nullptr) {
        logError("You are not logged in.");
        return;
    }

    log(Colors::BLUE << Colors::BOLD
                     << "\t\tUser Profile"
                     << Colors::RESET << newl);

    logInfo("ID: " << Colors::GREEN << currentMember->getId());
    logInfo("Username: " << Colors::GREEN << currentMember->getUsername());
    logInfo("Full name: " << Colors::GREEN << currentMember->getFullName());
    logInfo("Phone: " << Colors::GREEN << currentMember->getPhone());
}

void System::showUserHouseDetails() {
    if (currentMember == nullptr) {
        logError("You are not logged in.");
        return;
    }

    House* house = currentMember->getHouse();

    if (house == nullptr) {
        logInfo("You don't have any house on the system.");
        skipLine();

        string response;
        illogInfo(Colors::GREEN << "Do you want to create one? (Y/N): ");
        input(response);

        if (response == "N" || response == "n")
            return;

        if (response != "Y" && response != "y") {
            skipLine();
            logError("Invalid response.");
            skipLine();

            std::system("PAUSE");  // Only works on Windows.
            return;
        }

        skipLine();
        currentMember->setupHouse();
        return;
    }

    logInfo("ID: " << Colors::GREEN << house->getId());
    logInfo("Location: " << Colors::GREEN << house->getLocation());
    logInfo("Description: " << Colors::GREEN << house->getDescription());
    logInfo("Listing start: " << Colors::GREEN << house->getListingStart());
    logInfo("Listing end: " << Colors::GREEN << house->getListingEnd());
    logInfo("Consumption points: " << Colors::GREEN << house->getConsumptionPts());

    skipLine();
    std::system("PAUSE");  // Only works on Windows.
}

Member* System::getMember(string id) {
    for (Member& member : members) {
        if (member.getId().compare(id) == 0)
            return &member;
    }

    return nullptr;
}

House* System::getHouse(string id) {
    for (House& house : houses) {
        if (house.getId() == id)
            return &house;
    }

    return nullptr;
}

Rating* System::getRating(string id) {
    for (Rating& rating : ratings) {
        if (rating.getId() == id)
            return &rating;
    }

    return nullptr;
}

Comment* System::getComment(string id) {
    for (Comment& comment : comments) {
        if (comment.getId() == id)
            return &comment;
    }

    return nullptr;
}

Request* System::getRequest(string id) {
    for (Request& request : requests) {
        if (request.getId() == id)
            return &request;
    }

    return nullptr;
}

void System::displayAvailableLocations() {
    log(Colors::BLUE << Colors::BOLD
                     << "Available Locations:"
                     << Colors::RESET << newl);

    for (string location : availableLocations)
        logInfo("- " << Colors::CYAN << location);

    skipLine();
}

bool System::isLocationAvailable(string location) {
    for (string loc : availableLocations) {
        if (loc.compare(location) == 0)
            return true;
    }

    return false;
}
}  // namespace HouseExchanger
