#include "classes.h"

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "colors.h"

//* Constants
// Preferences
#define SHOW_PROCESSED_AMOUNT false  // Log out the amount of loaded / saved data

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
    std::cin.ignore();         \
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

bool Guest::signUp() {
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

bool Guest::login() {
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

bool Member::signUp() {
    logError("You are already logged in.");
    logError("Operation failed.");
    return false;
}

bool Member::login() {
    logError("You are already logged in.");
    logError("Operation failed.");
    return false;
}

bool Member::logout() {
    return System::getInstance()->logout();
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
System::~System() {}

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

// Authentication methods
bool System::signUp(Member member) {
    Member* newMember = addMember(member);

    if (newMember == nullptr) {
        logError(newl << "Sign up failed.");
        return false;
    }

    // Update current member
    setCurrentMember(newMember);
    setIsLoggedIn(true);

    // Display success message
    logSuccess(newl << "Sign up successful.");
    return true;
}

bool System::login(string username, string password) {
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
                return true;
            } else {
                logError("Incorrect password.");
                return false;
            }
        }
    }

    // Display failure message
    logError("Username not found.");
    return false;
}

bool System::logout() {
    // Update current member
    setCurrentMember(nullptr);
    setIsLoggedIn(false);

    // Display success message
    logSuccess("Logout successful.");
    return true;
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
        logError("Error: " << filePath + " not found.");
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
            logError("Invalid member format.");
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
        logInfo("Loaded " << members.size() << " members.");

    return true;
}

bool System::loadHouses() {
    std::ifstream file;
    string filePath = getFilePath(HOUSES_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        logError("Error: " << filePath + " not found.");
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

        if (tokens.size() != 6) {
            logError("Invalid house format.");
            continue;
        }

        House house;

        house.setLocation(tokens[1]);
        house.setDescription(tokens[2]);
        house.setListingStart(tokens[3]);
        house.setListingEnd(tokens[4]);
        house.setConsumptionPts(std::stoi(tokens[5]));

        houses.push_back(house);
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        logInfo("Loaded " << houses.size() << " houses.");

    return true;
}

bool System::loadRatings() {
    std::ifstream file;
    string filePath = getFilePath(RATINGS_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        logError("Error: " << filePath + " not found.");
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
            logError("Invalid rating format.");
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
        logInfo("Loaded " << ratings.size() << " ratings.");

    return true;
}

bool System::loadComments() {
    std::ifstream file;
    string filePath = getFilePath(COMMENTS_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        logError("Error: " << filePath + " not found.");
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
            logError("Invalid comment format.");
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
        logInfo("Loaded " << comments.size() << " comments.");

    return true;
}

bool System::loadRequests() {
    std::ifstream file;
    string filePath = getFilePath(REQUESTS_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        logError("Error: " << filePath + " not found.");
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
            logError("Invalid request format.");
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
        logInfo("Loaded " << requests.size() << " requests.");

    return true;
}

bool System::saveMembers() {
    std::ofstream file;
    string filePath = getFilePath(MEMBERS_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        logError("Error: " << filePath + " not found.");
        return false;
    }

    for (Member member : members) {
        file << member.getId() << "," << member.getUsername() << "," << member.getPassword() << "," << member.getFullName() << "," << member.getPhone() << newl;
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        logInfo("Saved " << members.size() << " members.");

    return true;
}

bool System::saveHouses() {
    std::ofstream file;
    string filePath = getFilePath(HOUSES_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        logError("Error: " << filePath + " not found.");
        return false;
    }

    for (House house : houses) {
        file << house.getLocation() << "," << house.getDescription() << "," << house.getListingStart() << "," << house.getListingEnd() << "," << house.getConsumptionPts() << newl;
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        logInfo("Saved " << houses.size() << " houses.");

    return true;
}

bool System::saveRatings() {
    std::ofstream file;
    string filePath = getFilePath(RATINGS_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        logError("Error: " << filePath + " not found.");
        return false;
    }

    for (Rating rating : ratings) {
        file << rating.getHouse() << "," << rating.getAuthor() << "," << rating.getContent() << newl;
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        logInfo("Saved " << ratings.size() << " ratings.");

    return true;
}

bool System::saveComments() {
    std::ofstream file;
    string filePath = getFilePath(COMMENTS_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        logError("Error: " << filePath + " not found.");
        return false;
    }

    for (Comment comment : comments) {
        file << comment.getHouse() << "," << comment.getAuthor() << "," << comment.getContent() << newl;
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        logInfo("Saved " << comments.size() << " comments.");

    return true;
}

bool System::saveRequests() {
    std::ofstream file;
    string filePath = getFilePath(REQUESTS_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        logError("Error: " << filePath + " not found.");
        return false;
    }

    for (Request request : requests) {
        file << request.getHouse() << "," << request.getRequester() << "," << request.getContent() << newl;
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        logInfo("Saved " << requests.size() << " requests.");

    return true;
}

bool System::loadAll() {
    skipLine();
    log(DIVIDER);
    skipLine();

    logInfo("SYSTEM NOTIFICATION: Loading data..." << newl);

    if (!loadMembers()) {
        logError("SYSTEM NOTIFICATION: Failed to load members.");
        return false;
    }

    if (!loadHouses()) {
        logError("SYSTEM NOTIFICATION: Failed to load houses.");
        return false;
    }

    if (!loadRatings()) {
        logError("SYSTEM NOTIFICATION: Failed to load ratings.");
        return false;
    }

    if (!loadComments()) {
        logError("SYSTEM NOTIFICATION: Failed to load comments.");
        return false;
    }

    if (!loadRequests()) {
        logError("SYSTEM NOTIFICATION: Failed to load requests.");
        return false;
    }

    if (SHOW_PROCESSED_AMOUNT)
        skipLine();

    logSuccess("SYSTEM NOTIFICATION: Data loaded." << newl);
    return true;
}

bool System::saveAll() {
    skipLine();
    log(DIVIDER);
    skipLine();

    logInfo("SYSTEM NOTIFICATION: Saving data..." << newl);

    if (!saveMembers()) {
        logError("SYSTEM NOTIFICATION: Failed to save members.");
        return false;
    }

    if (!saveHouses()) {
        logError("SYSTEM NOTIFICATION: Failed to save houses.");
        return false;
    }

    if (!saveRatings()) {
        logError("SYSTEM NOTIFICATION: Failed to save ratings.");
        return false;
    }

    if (!saveComments()) {
        logError("SYSTEM NOTIFICATION: Failed to save comments.");
        return false;
    }

    if (!saveRequests()) {
        logError("SYSTEM NOTIFICATION: Failed to save requests.");
        return false;
    }

    if (SHOW_PROCESSED_AMOUNT)
        skipLine();

    logSuccess("SYSTEM NOTIFICATION: Data saved." << newl);
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
        return;
    }

    logInfo("Location: " << Colors::GREEN << house->getLocation());
    logInfo("Description: " << Colors::GREEN << house->getDescription());
    logInfo("Listing start: " << Colors::GREEN << house->getListingStart());
    logInfo("Listing end: " << Colors::GREEN << house->getListingEnd());
    logInfo("Consumption points: " << Colors::GREEN << house->getConsumptionPts());
}
}  // namespace HouseExchanger
