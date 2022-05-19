#include "classes.h"

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

//* Helper preprocessor macros
// I/O macros
#define newl "\n"  // skip 1 line

#define illog(x) std::cout << x        // In-line print
#define skipLine() illog(newl)         // Skip 1 line in I/O
#define log(x) std::cout << x << newl  // Print with newline

using std::string;
using std::vector;

const string DATA_PATH = "data/";

const string MEMBERS_FILE = "members.dat";
const string HOUSES_FILE = "houses.dat";
const string RATINGS_FILE = "ratings.dat";
const string COMMENTS_FILE = "comments.dat";
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

void Guest::signUp() {}
void Guest::login() {}

void Guest::viewHouseDetail(House* house) {
    log("Location: " + house->getLocation());
    log("Description: " + house->getDescription());
    log("Listing start: " + house->getListingStart());
    log("Listing end: " + house->getListingEnd());
    log("Consumption points: " + std::to_string(house->getConsumptionPts()));
}

//* Member class
// Default constructor
Member::Member() {}

// Destructor
Member::~Member() {}

// Setters
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

//* Rating class
// Default constructor
Rating::Rating() {}

// Destructor
Rating::~Rating() {}

// Setters
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

string System::generateId() {
    return uuid::generate_uuid_v4();
}

bool System::loadMembers() {
    std::ifstream file;
    string filePath = getFilePath(MEMBERS_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        log("Warning: " << filePath + " not found.");
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
            log("Invalid member format.");
            continue;
        }

        Member member;

        member.setUsername(tokens[1]);
        member.setPassword(tokens[2]);
        member.setFullName(tokens[3]);
        member.setPhone(tokens[4]);

        members.push_back(member);
    }

    file.close();
    return true;
}

bool System::loadHouses() {
    std::ifstream file;
    string filePath = getFilePath(HOUSES_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        log("Warning: " << filePath + " not found.");
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
            log("Invalid house format.");
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
    return true;
}

bool System::loadRatings() {
    std::ifstream file;
    string filePath = getFilePath(RATINGS_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        log("Warning: " << filePath + " not found.");
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
            log("Invalid rating format.");
            continue;
        }

        Rating rating;

        // rating.setHouse(tokens[1]);
        // rating.setAuthor(tokens[2]);
        // rating.setContent(tokens[3]);

        ratings.push_back(rating);
    }

    file.close();
    return true;
}

bool System::loadComments() {
    std::ifstream file;
    string filePath = getFilePath(COMMENTS_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        log("Warning: " << filePath + " not found.");
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
            log("Invalid comment format.");
            continue;
        }

        Comment comment;

        // comment.setHouse(tokens[1]);
        // comment.setAuthor(tokens[2]);
        // comment.setContent(tokens[3]);

        comments.push_back(comment);
    }

    file.close();
    return true;
}

bool System::loadRequests() {
    std::ifstream file;
    string filePath = getFilePath(REQUESTS_FILE);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        log("Warning: " << filePath + " not found.");
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
            log("Invalid request format.");
            continue;
        }

        Request request;

        // request.setHouse(tokens[1]);
        // request.setRequester(tokens[2]);
        // request.setContent(tokens[3]);

        requests.push_back(request);
    }

    file.close();
    return true;
}

bool System::saveMembers() {
    std::ofstream file;
    string filePath = getFilePath(MEMBERS_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        log("Warning: " << filePath + " not found.");
        return false;
    }

    for (Member member : members) {
        file << member.getUsername() << "," << member.getPassword() << "," << member.getFullName() << "," << member.getPhone() << newl;
    }

    file.close();
    return true;
}

bool System::saveHouses() {
    std::ofstream file;
    string filePath = getFilePath(HOUSES_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        log("Warning: " << filePath + " not found.");
        return false;
    }

    for (House house : houses) {
        file << house.getLocation() << "," << house.getDescription() << "," << house.getListingStart() << "," << house.getListingEnd() << "," << house.getConsumptionPts() << newl;
    }

    file.close();
    return true;
}

bool System::saveRatings() {
    std::ofstream file;
    string filePath = getFilePath(RATINGS_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        log("Warning: " << filePath + " not found.");
        return false;
    }

    for (Rating rating : ratings) {
        file << rating.getHouse() << "," << rating.getAuthor() << "," << rating.getContent() << newl;
    }

    file.close();
    return true;
}

bool System::saveComments() {
    std::ofstream file;
    string filePath = getFilePath(COMMENTS_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        log("Warning: " << filePath + " not found.");
        return false;
    }

    for (Comment comment : comments) {
        file << comment.getHouse() << "," << comment.getAuthor() << "," << comment.getContent() << newl;
    }

    file.close();
    return true;
}

bool System::saveRequests() {
    std::ofstream file;
    string filePath = getFilePath(REQUESTS_FILE);

    file.open(filePath, std::ios::out);

    if (!file.is_open()) {
        log("Warning: " << filePath + " not found.");
        return false;
    }

    for (Request request : requests) {
        file << request.getHouse() << "," << request.getRequester() << "," << request.getContent() << newl;
    }

    file.close();
    return true;
}

bool System::loadAll() {
    log(newl << "SYSTEM NOTIFICATION: Loading data..." << newl);

    if (!loadMembers()) {
        log("SYSTEM NOTIFICATION: Failed to load members.");
        return false;
    }

    if (!loadHouses()) {
        log("SYSTEM NOTIFICATION: Failed to load houses.");
        return false;
    }

    if (!loadRatings()) {
        log("SYSTEM NOTIFICATION: Failed to load ratings.");
        return false;
    }

    if (!loadComments()) {
        log("SYSTEM NOTIFICATION: Failed to load comments.");
        return false;
    }

    if (!loadRequests()) {
        log("SYSTEM NOTIFICATION: Failed to load requests.");
        return false;
    }

    log("SYSTEM NOTIFICATION: Data loaded.");
    return true;
}

bool System::saveAll() {
    log(newl << "SYSTEM NOTIFICATION: Saving data..." << newl);

    if (!saveMembers()) {
        log("SYSTEM NOTIFICATION: Failed to save members.");
        return false;
    }

    if (!saveHouses()) {
        log("SYSTEM NOTIFICATION: Failed to save houses.");
        return false;
    }

    if (!saveRatings()) {
        log("SYSTEM NOTIFICATION: Failed to save ratings.");
        return false;
    }

    if (!saveComments()) {
        log("SYSTEM NOTIFICATION: Failed to save comments.");
        return false;
    }

    if (!saveRequests()) {
        log("SYSTEM NOTIFICATION: Failed to save requests.");
        return false;
    }

    log("SYSTEM NOTIFICATION: Data saved." << newl);
    return true;
}
}  // namespace HouseExchanger