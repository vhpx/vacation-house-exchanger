#include "classes.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "colors.h"
#include "utils.h"

//* Constants
// Preferences
#define SHOW_PROCESSED_AMOUNT true  // Log out the amount of loaded / saved data

// Data
const string DATA_PATH = "data/";

const string MEMBERS_FILE = "members.dat";
const string HOUSES_FILE = "houses.dat";
const string RATINGS_FILE = "ratings.dat";
const string REQUESTS_FILE = "requests.dat";

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

string getFilePath(const string& fileName) {
    return DATA_PATH + fileName;
}

// UUID generator source:
// https://stackoverflow.com/a/60198074/18811079
namespace uuid {
string generate_uuid_v4() {
    static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_int_distribution<int> dist(0, 15);

    const char* v = "0123456789abcdef";
    const bool dash[] = {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0};

    string res;
    for (int i = 0; i < 16; i++) {
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}
}  // namespace uuid

namespace HouseExchanger {
//* Date Class
// Default constructor
Date::Date() {}

// Destructor
Date::~Date() {}

// Copy constructor
Date::Date(const Date& other) {
    day = other.day;
    month = other.month;
    year = other.year;
}

// Assignment operator
Date& Date::operator=(const Date& other) {
    day = other.day;
    month = other.month;
    year = other.year;
    return *this;
}

// Setters
void Date::setDay(int day) { this->day = day; }
void Date::setMonth(int month) { this->month = month; }
void Date::setYear(int year) { this->year = year; }

// Getters
int Date::getDay() { return day; }
int Date::getMonth() { return month; }
int Date::getYear() { return year; }

// Other methods
string Date::toString() {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << day << "/"
       << std::setfill('0') << std::setw(2) << month << "/" << year;
    return ss.str();
}

string Date::getMonthStr() {
    switch (month) {
        case 1:
            return "January";
        case 2:
            return "February";
        case 3:
            return "March";
        case 4:
            return "April";
        case 5:
            return "May";
        case 6:
            return "June";
        case 7:
            return "July";
        case 8:
            return "August";
        case 9:
            return "September";
        case 10:
            return "October";
        case 11:
            return "November";
        case 12:
            return "December";

        default:
            return "";
    }
}

string Date::toDateString() {
    std::stringstream ss;
    ss << day << (day % 10 == 1 ? "st" : day % 10 == 2 ? "nd"
                                     : day % 10 == 3   ? "rd"
                                                       : "th")
       << " " << getMonthStr() << ", " << year;
    return ss.str();
}

bool Date::isValid(string date) {
    // Check if the date is in the correct format
    // (dd/mm/yyyy)
    if (date.length() != 10)
        return false;

    if (!isdigit(date[0]) || !isdigit(date[1]) || date[2] != '/' ||
        !isdigit(date[3]) || !isdigit(date[4]) || date[5] != '/' ||
        !isdigit(date[6]) || !isdigit(date[7]) || !isdigit(date[8]) ||
        !isdigit(date[9]))
        return false;

    // Check if the date is valid
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));

    if (day < 1 || day > 31)
        return false;

    if (month < 1 || month > 12)
        return false;

    if (year < 0)
        return false;

    if (month == 2) {
        if (year % 4 == 0) {
            if (day > 29)
                return false;
        } else {
            if (day > 28)
                return false;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            return false;
    }

    return true;
}

Date Date::parse(string date) {
    Date d;
    d.setDay(std::stoi(date.substr(0, 2)));
    d.setMonth(std::stoi(date.substr(3, 2)));
    d.setYear(std::stoi(date.substr(6, 4)));
    return d;
}

int Date::compare(Date date1, Date date2) {
    if (date1.getYear() < date2.getYear())
        return -1;
    else if (date1.getYear() > date2.getYear())
        return 1;
    else {
        if (date1.getMonth() < date2.getMonth())
            return -1;
        else if (date1.getMonth() > date2.getMonth())
            return 1;
        else {
            if (date1.getDay() < date2.getDay())
                return -1;
            else if (date1.getDay() > date2.getDay())
                return 1;
            else
                return 0;
        }
    }
}

int Date::getDurationInDays(Date date1, Date date2) {
    int days = 0;

    int year1 = date1.getYear();
    int month1 = date1.getMonth();
    int day1 = date1.getDay();

    int year2 = date2.getYear();
    int month2 = date2.getMonth();
    int day2 = date2.getDay();

    // If the first date is after the second date
    if (year1 > year2 || (year1 == year2 && month1 > month2) ||
        (year1 == year2 && month1 == month2 && day1 > day2)) {
        int temp = year1;
        year1 = year2;
        year2 = temp;

        temp = month1;
        month1 = month2;
        month2 = temp;

        temp = day1;
        day1 = day2;
        day2 = temp;
    }

    // If the first date is the same as the second date
    if (year1 == year2 && month1 == month2 && day1 == day2)
        return 0;

    // Calculate the number of days between the two dates
    if (year1 == year2) {
        if (month1 == month2) {
            days = day2 - day1;
        } else {
            for (int i = month1; i < month2; i++) {
                if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 ||
                    i == 12)
                    days += 31;
                else if (i == 4 || i == 6 || i == 9 || i == 11)
                    days += 30;
                else if (i == 2) {
                    if (year1 % 4 == 0)
                        days += 29;
                    else
                        days += 28;
                }
            }
            days += day2;
        }
    } else {
        for (int i = year1; i < year2; i++) {
            if (i % 4 == 0)
                days += 366;
            else
                days += 365;
        }

        for (int i = month1; i < 13; i++) {
            if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 ||
                i == 12)
                days += 31;
            else if (i == 4 || i == 6 || i == 9 || i == 11)
                days += 30;
            else if (i == 2) {
                if (year1 % 4 == 0)
                    days += 29;
                else
                    days += 28;
            }
        }

        for (int i = 1; i < month2; i++) {
            if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 ||
                i == 12)
                days += 31;
            else if (i == 4 || i == 6 || i == 9 || i == 11)
                days += 30;
            else if (i == 2) {
                if (year1 % 4 == 0)
                    days += 29;
                else
                    days += 28;
            }
        }

        days += day2;
    }

    return days + 1;
}

//* House Class
// Default constructor
House::House() {}

// Destructor
House::~House() {}

// Setters
void House::setOwner(Member* owner) {
    this->owner = owner;
}

void House::setOccupier(Member* occupier) {
    this->occupier = occupier;
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

void House::setListingStart(Date listingStart) {
    this->listingStart = listingStart;
}

void House::setListingEnd(Date listingEnd) {
    this->listingEnd = listingEnd;
}

void House::setConsumptionPts(int points) {
    this->consumptionPts = points;
}

// Getters
Member* House::getOwner() {
    return owner;
}

Member* House::getOccupier() {
    return occupier;
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

Date House::getListingStart() {
    return this->listingStart;
}

Date House::getListingEnd() {
    return this->listingEnd;
}

int House::getConsumptionPts() {
    return this->consumptionPts;
}

bool House::getHasRatings() {
    System* system = System::getInstance();
    vector<Rating*> ratings;

    system->getRatings(ratings, this);

    return ratings.size() > 0;
}

bool House::isOccupied() {
    return occupier != nullptr;
}

bool House::updateInfo() {
    System* system = System::getInstance();
    Member* owner = system->getCurrentMember();

    owner->listHouse();

    return true;
}

bool House::isAvailable(Date startingDate, Date endingDate) {
    if (Date::compare(startingDate, listingStart) < 0 ||
        Date::compare(endingDate, listingEnd) > 0)
        return false;

    return true;
}

void House::viewRequests() {
    System* system = System::getInstance();
    Member* owner = system->getCurrentMember();

    if (owner->getId() != this->owner->getId()) {
        logError("You are not the owner of this house.");

        return;
    }

    vector<Request*> requests;
    system->getRequests(requests, this);

    if (requests.size() == 0) {
        logInfo("There are no requests for this house.");

        return;
    }

    logInfo("Requests for your listed house:");
    skipLine();

    for (int i = 0; i < requests.size(); i++) {
        log(Colors::BLUE << Colors::BOLD
                         << "\t\tRequest " + std::to_string(i + 1)
                         << Colors::RESET << newl);

        logInfo("Request ID: " << Colors::GREEN << requests[i]->getId());
        logInfo("Requested by: " << Colors::GREEN << requests[i]->getRequester()->getFullName());
        logInfo("Exchange from: " << Colors::GREEN << requests[i]->getStartingDate().toDateString());
        logInfo("Exchange to: " << Colors::GREEN << requests[i]->getEndingDate().toDateString());

        skipLine();
        log(DIVIDER);
    }

    displayHouseRequestsMenu();

    int choice = -1;

    // Execute house details loop
    while (choice != 0) {
        // Get user choice.
        illogInfo("Enter your choice: ");

        std::string buffer;
        input(buffer);

        // Check if the user entered an integer.
        if (checkIfInteger(buffer)) {
            choice = std::stoi(buffer);
        } else {
            logError("Error: Invalid input. Please enter an integer.");

            // Wait for user to press enter.
            skipLine();
            std::system("PAUSE");  // Only works on Windows.

            continue;
        }

        // Exit the loop if the user
        // wishes to quit the program.
        if (choice == 0)
            break;

        skipLine();
        log(DIVIDER);

        // Process user choice.
        switch (choice) {
            case 1: {
                int requestIndex = -1;
                // Ask user to enter the request number.
                illogInfo("Enter the request number: ");

                // Get user input.
                std::string buffer;
                input(buffer);

                // Check if the user entered an integer.
                if (checkIfInteger(buffer)) {
                    requestIndex = std::stoi(buffer) - 1;

                    if (requestIndex < 0 || requestIndex >= requests.size()) {
                        logError("Error: Invalid input. Please enter a valid request number.");

                        // Wait for user to press enter.
                        skipLine();
                        std::system("PAUSE");  // Only works on Windows.

                        continue;
                    }
                } else {
                    logError("Error: Invalid input. Please enter an integer.");

                    // Wait for user to press enter.
                    skipLine();
                    std::system("PAUSE");  // Only works on Windows.

                    continue;
                }

                acceptRequest(requests[requestIndex]);
                return;
            }

            case 2: {
                int requestIndex = -1;
                // Ask user to enter the request number.
                illogInfo("Enter the request number: ");

                // Get user input.
                std::string buffer;
                input(buffer);

                // Check if the user entered an integer.
                if (checkIfInteger(buffer)) {
                    requestIndex = std::stoi(buffer) - 1;
                } else {
                    logError("Error: Invalid input. Please enter an integer.");

                    // Wait for user to press enter.
                    skipLine();
                    std::system("PAUSE");  // Only works on Windows.

                    continue;
                }

                denyRequest(requests[requestIndex]);
                return;
            }

            case 0:
                // Exit house details loop
                return;

            default:
                logError("Error: Invalid choice!");
                choice = -1;

                skipLine();
                std::system("PAUSE");  // Only works on Windows.
                break;
        }
    }
}

bool House::acceptRequest(Request* request) {
    System* system = System::getInstance();
    Member* owner = system->getCurrentMember();

    if (owner->getId() != this->owner->getId()) {
        logError("You are not the owner of this house.");

        return false;
    }

    if (request->getStatus() != PENDING) {
        logError("This request is not pending.");

        return false;
    }

    if (request->getRequester()->getId() == owner->getId()) {
        logError("You cannot accept your own request.");

        return false;
    }

    int durationInDays = Date::getDurationInDays(request->getStartingDate(),
                                                 request->getEndingDate());
    int points = durationInDays * this->consumptionPts;

    if (request->getRequester()->getCreditPoints() < points) {
        logError("The requester does not have enough points.");

        return false;
    }

    skipLine();
    system->addPoints(owner, points);
    logInfo(std::to_string(points) << " points" << Colors::GREEN << " has been added to your account.");

    system->removePoints(request->getRequester(), points);
    logInfo(std::to_string(points) << " points" << Colors::GREEN << " has been removed from the requester's account.");

    request->getHouse()->setOccupier(request->getRequester());
    request->setStatus(APPROVED);

    skipLine();
    logInfo("You have accepted the request from " << Colors::GREEN << request->getRequester()->getFullName() + ".");

    // Remove all other pending requests for this house.
    vector<Request*> requests;
    system->getRequests(requests, this);

    for (int i = 0; i < requests.size(); i++) {
        if (requests[i]->getStatus() == PENDING &&
            requests[i]->getRequester()->getId() != owner->getId()) {
            requests[i]->setStatus(DENIED);
        }
    }

    skipLine();
    logInfo("All other pending requests have been denied.");

    return true;
}

bool House::denyRequest(Request* request) {
    System* system = System::getInstance();
    Member* owner = system->getCurrentMember();

    if (owner->getId() != this->owner->getId()) {
        logError("You are not the owner of this house.");

        return false;
    }

    if (request->getStatus() != PENDING) {
        logError("This request is not pending.");

        return false;
    }

    if (request->getRequester()->getId() == owner->getId()) {
        logError("You cannot deny your own request.");

        return false;
    }

    request->setStatus(DENIED);

    logInfo("You have denied the request from " + request->getRequester()->getFullName() + ".");

    return true;
}

void House::viewRatings() {
    System* system = System::getInstance();
    vector<Rating*> ratings;

    system->getRatings(ratings, this);

    if (ratings.size() == 0) {
        logInfo("No ratings have been made for this house.");

        return;
    }

    for (int i = 0; i < ratings.size(); i++) {
        log(Colors::BLUE << Colors::BOLD
                         << "\t\tRating #" + std::to_string(i + 1)
                         << Colors::RESET << newl);

        logInfo("Rated by: " << Colors::GREEN << ratings[i]->getAuthor()->getFullName());
        logInfo("Score: " << Colors::GREEN << ratings[i]->getScore());
        logInfo("Comment: " << Colors::GREEN << ratings[i]->getComment());

        skipLine();
        log(DIVIDER);
    }
}

float House::getRating() {
    System* system = System::getInstance();
    vector<Rating*> ratings;

    system->getRatings(ratings, this);

    if (ratings.size() == 0) {
        return 0;
    }

    float sum = 0;

    for (int i = 0; i < ratings.size(); i++) {
        sum += ratings[i]->getScore();
    }

    return sum / ratings.size();
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

bool Member::updateInfo() {
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

void Member::setCreditPoints(int creditPoints) {
    this->creditPoints = creditPoints;
}

void Member::setRequest(Request* request) {
    this->request = request;
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

bool Member::getHasRatings() {
    System* system = System::getInstance();
    vector<Rating*> ratings;

    system->getRatings(ratings, this);

    return ratings.size() > 0;
}

int Member::getCreditPoints() {
    return this->creditPoints;
}

House* Member::getHouse() {
    return this->house;
}

Request* Member::getRequest() {
    return this->request;
}

bool Member::listHouse() {
    // Check if existing house.
    bool isExistingHouse = this->getHouse() != nullptr;

    // Get user input.
    string location, description;
    Date listingStart, listingEnd;
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

    string buffer = "";
    illogInfo("Listing start date (dd/mm/yyyy): ");
    input(buffer);

    while (!Date::isValid(buffer)) {
        illogInfo("Invalid date format. Please try again: ");
        input(buffer);
    }

    listingStart = Date::parse(buffer);

    buffer = "";
    illogInfo("Listing end date (dd/mm/yyyy): ");
    input(buffer);

    while (!Date::isValid(buffer)) {
        illogInfo("Invalid date format. Please try again: ");
        input(buffer);
    }

    listingEnd = Date::parse(buffer);

    buffer = "";
    illogInfo("Consumption points: ");
    input(buffer);

    while (!checkIfInteger(buffer)) {
        illogInfo("Invalid number format. Please try again: ");
        input(buffer);
    }

    consumptionPts = std::stoi(buffer);

    // Create a new house object to store the data.
    House house;

    // Set house data.
    house.setOwner(this);
    house.setLocation(location);
    house.setDescription(description);
    house.setListingStart(listingStart);
    house.setListingEnd(listingEnd);
    house.setConsumptionPts(consumptionPts);

    // Check for existing house ID.
    string houseId = isExistingHouse ? this->getHouse()->getId() : "";
    if (isExistingHouse) house.setId(houseId);

    // Add the house to the system.
    House* savedHouse = System::getInstance()->addHouse(house, houseId);

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
    logInfo("Listing start: " << Colors::GREEN << house->getListingStart().toDateString());
    logInfo("Listing end: " << Colors::GREEN << house->getListingEnd().toDateString());
    logInfo("Consumption points: " << Colors::GREEN << house->getConsumptionPts());
}

bool Member::isEligibleToBook(House* house, Date startingDate, Date endingDate) {
    // Check if the house already has an occupant.
    if (house->isOccupied()) {
        logError("House is already occupied.");
        return false;
    }

    // Check if the house is available.
    if (!house->isAvailable(startingDate, endingDate)) {
        logError("House is not available.");
        return false;
    }

    // Check if the member has enough credit points.
    if (this->getCreditPoints() < Date::getDurationInDays(startingDate, endingDate) * house->getConsumptionPts()) {
        logError("You don't have enough credit points.");
        return false;
    }

    return true;
}

bool Member::bookHouse(House* house, Date startingDate, Date endingDate) {
    // Create a new request
    Request request;

    // Set request data.
    request.setRequester(this);
    request.setHouse(house);
    request.setStartingDate(startingDate);
    request.setEndingDate(endingDate);

    // Add a new request to the system.
    Request* newRequest = System::getInstance()->addRequest(request);

    // Check if the request was added successfully.
    if (newRequest != nullptr) {
        logSuccess("Request added successfully.");
        setRequest(newRequest);

        return true;
    } else {
        logError("Request failed.");
        return false;
    }
}

void Member::viewRatings() {
    System* system = System::getInstance();
    vector<Rating*> ratings;

    system->getRatings(ratings, this);

    if (ratings.size() == 0) {
        logInfo("No ratings found.");

        return;
    }

    for (int i = 0; i < ratings.size(); i++) {
        log(Colors::BLUE << Colors::BOLD
                         << "\t\tRating #" + std::to_string(i + 1)
                         << Colors::RESET << newl);

        logInfo("Rated by: " << Colors::GREEN << ratings[i]->getAuthor()->getFullName());
        logInfo("Score: " << Colors::GREEN << ratings[i]->getScore());
        logInfo("Comment: " << Colors::GREEN << ratings[i]->getComment());

        skipLine();
        log(DIVIDER);
    }
}

float Member::getRating() {
    System* system = System::getInstance();
    vector<Rating*> ratings;

    system->getRatings(ratings, this);

    if (ratings.size() == 0) {
        return 0;
    }

    float sum = 0;

    for (int i = 0; i < ratings.size(); i++) {
        sum += ratings[i]->getScore();
    }

    return sum / ratings.size();
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

void Rating::setTarget(Member* target) {
    this->target = target;
}

void Rating::setScore(int score) {
    this->score = score;
}

void Rating::setComment(string comment) {
    this->comment = comment;
}

// Getters
House* Rating::getHouse() {
    return this->house;
}

Member* Rating::getAuthor() {
    return this->author;
}

Member* Rating::getTarget() {
    return this->target;
}

int Rating::getScore() {
    return this->score;
}

string Rating::getComment() {
    return this->comment;
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

void Request::setStartingDate(Date startingDate) {
    this->startingDate = startingDate;
}

void Request::setEndingDate(Date endingDate) {
    this->endingDate = endingDate;
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

Date Request::getStartingDate() {
    return this->startingDate;
}

Date Request::getEndingDate() {
    return this->endingDate;
}

int Request::getStatus() {
    return this->status;
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
    log(newl << Colors::CYAN << "Deducted " << Colors::YELLOW << "$500" << Colors::CYAN << " as a sign up fee.");

    logSuccess(newl << "Sign up successful.");
    logSuccess("Awarded " << Colors::YELLOW << "500" << Colors::GREEN << " points for signing up.");

    return newMember;
}

Member* System::login(string username, string password) {
    skipLine();

    // Check if the user is trying to login as an admin.
    if (username.compare(adminUsername) == 0) {
        if (password.compare(adminPassword) == 0) {
            // Update current user
            setCurrentMember(nullptr);
            setIsLoggedIn(true);
            setIsAdmin(true);

            // Display success message
            logSuccess("Logged in as an admin.");

            return nullptr;
        } else {
            logError("Incorrect password.");
            return nullptr;
        }
    }

    // Check if username exists
    for (int i = 0; i < members.size(); i++) {
        if (members[i].getUsername().compare(username) == 0) {
            // Check if password is correct
            if (members[i].getPassword().compare(password) == 0) {
                // Update current member
                setCurrentMember(&members[i]);
                setIsLoggedIn(true);

                // Update current occupant
                if (members[i].getHouse() != nullptr) {
                    for (Request& request : requests) {
                        if (request.getHouse()->getOwner()->getId() == members[i].getId() && request.getStatus() == APPROVED) {
                            members[i].getHouse()->setOccupier(request.getRequester());
                        }
                    }
                }

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
void System::getAvailableHouses(vector<House*>& buffer, bool eligibleOnly, string location, Date startingDate, Date endingDate) {
    for (int i = 0; i < houses.size(); i++) {
        if (eligibleOnly && houses[i].getLocation().compare(location) != 0)
            continue;

        if (eligibleOnly &&
            (Date::compare(startingDate, houses[i].getListingStart()) < 0 ||
             Date::compare(endingDate, houses[i].getListingEnd()) > 0))
            continue;

        if (eligibleOnly && houses[i].getOwner() == currentMember)
            continue;

        buffer.push_back(&houses[i]);
    }
}

void System::displayHouseBrowser(bool eligibleOnly, string location, Date startingDate, Date endingDate) {
    log(Colors::BLUE << Colors::BOLD << "\t     "
                     << "House Browser"
                     << Colors::RESET << newl);

    if (houses.size() == 0) {
        skipLine();
        logInfo("There are no houses on our system.");
        return;
    }

    // Display all houses

    if (eligibleOnly) {
        vector<House*> availableHouses;
        getAvailableHouses(availableHouses, true, location, startingDate, endingDate);

        if (availableHouses.size() == 0) {
            skipLine();
            logInfo("There are no eligible houses.");
            return;
        }

        int days = Date::getDurationInDays(startingDate, endingDate);

        for (int i = 0; i < availableHouses.size(); i++) {
            log(DIVIDER);
            log(Colors::BLUE << Colors::BOLD
                             << "\t\tHouse #" + std::to_string(i + 1)
                             << Colors::RESET << newl);

            logInfo("Location: " << Colors::GREEN << availableHouses[i]->getLocation());
            logInfo("Description: " << Colors::GREEN << availableHouses[i]->getDescription());
            logInfo("Available from: " << Colors::GREEN << availableHouses[i]->getListingStart().toDateString());
            logInfo("Available until: " << Colors::GREEN << availableHouses[i]->getListingEnd().toDateString());
            logInfo("Consumption points (per day): " << Colors::GREEN << std::to_string(availableHouses[i]->getConsumptionPts()));
            logInfo("Expected consumption points: " << Colors::GREEN
                                                    << days * availableHouses[i]->getConsumptionPts());
        }
    } else {
        for (int i = 0; i < houses.size(); i++) {
            log(DIVIDER);
            log(Colors::BLUE << Colors::BOLD
                             << "\t\tHouse #" + std::to_string(i + 1)
                             << Colors::RESET << newl);
            if (isUserAdmin)
                logInfo("ID: " << Colors::GREEN << houses[i].getId());

            logInfo("Location: " << Colors::GREEN << houses[i].getLocation());
            logInfo("Description: " << Colors::GREEN << houses[i].getDescription());

            if (isUserLoggedIn || isUserAdmin) {
                logInfo("Listing start: " << Colors::GREEN << houses[i].getListingStart().toDateString());
                logInfo("Listing end: " << Colors::GREEN << houses[i].getListingEnd().toDateString());
                logInfo("Consumption points (per day): " << Colors::GREEN << std::to_string(houses[i].getConsumptionPts()));
            }

            if (isUserAdmin) {
                skipLine();
                logInfo("Owner ID: " << Colors::GREEN << houses[i].getOwner()->getId());
                logInfo("Owner Username: " << Colors::GREEN << houses[i].getOwner()->getUsername());
                logInfo("Owner Name: " << Colors::GREEN << houses[i].getOwner()->getFullName());
            }
        }
    }
}

void System::displayMemberBrowser() {
    log(Colors::BLUE << Colors::BOLD << "\t     "
                     << "Member Browser"
                     << Colors::RESET << newl);

    if (members.size() == 0) {
        skipLine();
        logInfo("There are no members on our system.");
        return;
    }

    if (!isUserAdmin) {
        skipLine();
        logInfo("You must be an admin to view member profiles.");
        return;
    }

    for (int i = 0; i < members.size(); i++) {
        log(DIVIDER);
        log(Colors::BLUE << Colors::BOLD
                         << "\t\tMember " + std::to_string(i + 1)
                         << Colors::RESET << newl);

        logInfo("ID: " << Colors::GREEN << members[i].getId());
        logInfo("Username: " << Colors::GREEN << members[i].getUsername());
        logInfo("Name: " << Colors::GREEN << members[i].getFullName());
        logInfo("Phone: " << Colors::GREEN << members[i].getPhone());
        logInfo("Credit points: " << Colors::GREEN << members[i].getCreditPoints());
    }
}

// Resouce management methods
Member* System::addMember(Member member, string id) {
    // Check if system is trying to add a member
    // with admin username.
    if (member.getUsername().compare(adminUsername) == 0) {
        skipLine();
        logError("Username already taken.");
        return nullptr;
    }

    // Check if username is already taken
    for (int i = 0; i < members.size(); i++) {
        if (members[i].getUsername() == member.getUsername()) {
            skipLine();
            illogError("Username already taken.");
            return nullptr;
        }
    }

    // Add member to members vector
    members.push_back(member);
    Member* newMember = &members.back();

    // Generate member ID
    if (newMember->getId().empty()) {
        string id = generateId();
        newMember->setId(id);
    }

    return newMember;
}

House* System::addHouse(House house, string id) {
    // Generate house ID if not provided
    if (id.empty()) {
        string id = generateId();

        // Add house to houses vector
        houses.push_back(house);

        House* newHouse = &houses.back();
        newHouse->setId(id);

        return newHouse;
    } else {
        // Check if house already exists
        // if it does, update the house
        for (int i = 0; i < houses.size(); i++) {
            if (houses[i].getId() == id) {
                houses[i] = house;
                houses[i].setId(id);

                return &houses[i];
            }
        }

        return nullptr;
    }
}

Rating* System::addRating(Rating rating) {
    // Check if rating already exists
    // if it does, update the rating
    for (int i = 0; i < ratings.size(); i++) {
        if (ratings[i].getHouse()->getId() == rating.getHouse()->getId() &&
            ratings[i].getAuthor()->getId() == rating.getAuthor()->getId()) {
            ratings[i] = rating;
            return &ratings[i];
        }
    }

    // Add rating to ratings vector
    ratings.push_back(rating);
    Rating* newRating = &ratings.back();

    return newRating;
}

Request* System::addRequest(Request request, string id) {
    // Generate request ID if not provided
    if (id.empty()) {
        // Check if the current user has any request.
        // If they do, return nullptr.
        if (currentMember->getRequest() != nullptr && currentMember->getRequest()->getStatus() == PENDING) {
            skipLine();
            illogError("You already have a request.");
            return nullptr;
        }

        string id = generateId();

        // Add request to requests vector
        requests.push_back(request);

        Request* newRequest = &requests.back();
        newRequest->setId(id);

        return newRequest;
    } else {
        // Check if request already exists
        // if it does, update the request
        for (int i = 0; i < requests.size(); i++) {
            if (requests[i].getId() == id) {
                requests[i] = request;
                requests[i].setId(id);

                return &requests[i];
            }
        }

        return nullptr;
    }
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

        if (tokens.size() != 6) {
            notify("Error: Invalid Member format.", Colors::RED);
            continue;
        }

        Member member;

        member.setId(tokens[0]);
        member.setUsername(tokens[1]);
        member.setPassword(tokens[2]);
        member.setFullName(tokens[3]);
        member.setPhone(tokens[4]);
        member.setCreditPoints(stoi(tokens[5]));

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
        house.setListingStart(Date::parse(tokens[4]));
        house.setListingEnd(Date::parse(tokens[5]));
        house.setConsumptionPts(std::stoi(tokens[6]));

        houses.push_back(house);
        House* newHouse = &houses.back();

        owner->setHouse(newHouse);
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

        if (tokens.size() != 5) {
            notify("Error: Invalid Rating format.", Colors::RED);
            continue;
        }

        Rating rating;

        string houseId = tokens[0];
        string authorId = tokens[1];
        string targetId = tokens[2];
        string scoreStr = tokens[3];
        string comment = tokens[4];

        House* house = getHouse(houseId);
        Member* author = getMember(authorId);
        Member* target = targetId.compare("none") == 0 ? nullptr : getMember(targetId);

        if (house == nullptr) {
            notify("Error: House with ID " + houseId + " not found.");
            continue;
        }

        if (author == nullptr) {
            notify("Error: Author with ID " + authorId + " not found.");
            continue;
        }

        rating.setHouse(house);
        rating.setAuthor(author);
        rating.setTarget(target);
        rating.setScore(stoi(scoreStr));
        rating.setComment(comment);

        ratings.push_back(rating);
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        notify("Loaded " + Colors::YELLOW + std::to_string(ratings.size()) + Colors::GREEN + " ratings.", Colors::GREEN);

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

        if (tokens.size() != 6) {
            notify("Error: Invalid Request format.", Colors::RED);
            continue;
        }

        System* system = System::getInstance();

        string requesterId = tokens[1];
        Member* requester = system->getMember(requesterId);

        if (requester == nullptr) {
            notify("Error: Owner with ID " + requesterId + " not found.");
            continue;
        }

        string houseId = tokens[2];
        House* requestedHouse = system->getHouse(houseId);

        if (requestedHouse == nullptr) {
            notify("Error: House with ID " + houseId + " not found.");
            continue;
        }

        Request request;

        request.setId(tokens[0]);
        request.setRequester(requester);
        request.setHouse(requestedHouse);
        request.setStartingDate(Date::parse(tokens[3]));
        request.setEndingDate(Date::parse(tokens[4]));
        request.setStatus(std::stoi(tokens[5]));

        requests.push_back(request);
        Request* newRequest = &requests.back();

        requester->setRequest(newRequest);

        if (newRequest->getStatus() == APPROVED) {
            // loop through all houses and find the one with the same id
            for (House& house : houses) {
                if (house.getId() == newRequest->getHouse()->getId()) {
                    house.setOccupier(requester);
                    break;
                }
            }
        }
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
             << member.getPhone() << "," << member.getCreditPoints() << newl;
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
             << house.getDescription() << "," << house.getListingStart().toString() << ","
             << house.getListingEnd().toString() << "," << house.getConsumptionPts() << newl;
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
        file << rating.getHouse()->getId() << ","
             << rating.getAuthor()->getId() << ","
             << (rating.getTarget() != nullptr ? rating.getTarget()->getId() : "none") << ","
             << rating.getScore() << ","
             << rating.getComment() << newl;
    }

    file.close();

    if (SHOW_PROCESSED_AMOUNT)
        notify("Saved " + Colors::YELLOW + std::to_string(ratings.size()) + Colors::GREEN + " ratings.", Colors::GREEN);

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
        file
            << request.getId() << ","
            << request.getRequester()->getId() << ","
            << request.getHouse()->getId() << ","
            << request.getStartingDate().toString() << ","
            << request.getEndingDate().toString() << ","
            << request.getStatus() << newl;
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

    if (!loadRequests()) {
        notify("Failed to load Requests.", Colors::RED);
        return false;
    }

    if (SHOW_PROCESSED_AMOUNT)
        skipLine();

    notify("Data loaded.\n");

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

    if (!saveRequests()) {
        notify("Failed to save requests.", Colors::RED);
        return false;
    }

    if (SHOW_PROCESSED_AMOUNT)
        skipLine();

    notify("Data saved.\n");

    log(DIVIDER);
    skipLine();
    notify("Exiting...");
    skipLine();

    return true;
}

//* Current user
Member* System::getCurrentMember() {
    return currentMember;
}

bool System::isLoggedIn() {
    return isUserLoggedIn || currentMember != nullptr;
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
                     << "\t\tYour Profile"
                     << Colors::RESET << newl);

    logInfo("ID: " << Colors::GREEN << currentMember->getId());
    logInfo("Username: " << Colors::GREEN << currentMember->getUsername());
    logInfo("Full name: " << Colors::GREEN << currentMember->getFullName());
    logInfo("Phone: " << Colors::GREEN << currentMember->getPhone());
    illogInfo("Credit points: " << Colors::GREEN << currentMember->getCreditPoints());

    bool hasRatings = currentMember->getHasRatings();
    if (hasRatings) {
        float rating = currentMember->getRating();
        logInfo("Rating: " << Colors::GREEN << std::fixed << std::setprecision(2) << rating);
        skipLine();
    } else {
        skipLine();
        logInfo(newl << "You have not been rated yet.");
    }
}

void System::showUserHouseDetails() {
    if (currentMember == nullptr) {
        logError("You are not logged in.");
        return;
    }

    log(Colors::BLUE << Colors::BOLD
                     << "\t\tYour House"
                     << Colors::RESET << newl);

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
        currentMember->listHouse();

        return;
    }

    logInfo("ID: " << Colors::GREEN << house->getId());
    logInfo("Location: " << Colors::GREEN << house->getLocation());
    logInfo("Description: " << Colors::GREEN << house->getDescription());
    logInfo("Listing start: " << Colors::GREEN << house->getListingStart().toDateString());
    logInfo("Listing end: " << Colors::GREEN << house->getListingEnd().toDateString());
    illogInfo("Consumption points: " << Colors::GREEN << house->getConsumptionPts());

    bool hasRatings = house->getHasRatings();
    if (hasRatings) {
        float rating = house->getRating();
        logInfo("House rating: " << Colors::GREEN << std::fixed << std::setprecision(2) << rating);
    } else {
        skipLine();
        logInfo(newl << "Your house have not been rated yet.");
    }

    if (house->getOccupier() != nullptr) {
        logInfo("Occupier: " << Colors::GREEN << house->getOccupier()->getFullName());
        logInfo("Occupier phone: " << Colors::GREEN << house->getOccupier()->getPhone());
    } else {
        logInfo("Occupier: " << Colors::GREEN << "None");
    }
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

Rating* System::getRating(string houseId, string authorId) {
    for (Rating& rating : ratings) {
        if (rating.getHouse()->getId() == houseId && rating.getAuthor()->getId() == authorId)
            return &rating;
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

bool System::unlistCurrentHouse() {
    if (currentMember == nullptr) {
        logError("You are not logged in.");
        return false;
    }

    House* house = currentMember->getHouse();

    if (house == nullptr) {
        logError("You don't have any house on the system.");
        return false;
    }

    string response;
    illogInfo("Are you sure you want to unlist your house? (Y/N): ");
    input(response);

    if (response == "N" || response == "n") {
        skipLine();
        return false;
    }

    if (response != "Y" && response != "y") {
        skipLine();
        logError("Invalid response.");
        skipLine();

        std::system("PAUSE");  // Only works on Windows.
        return false;
    }

    for (int i = 0; i < houses.size(); i++) {
        if (houses[i].getId().compare(house->getId()) == 0) {
            // Remove house from current member
            currentMember->setHouse(nullptr);

            // Remove house from houses list
            houses.erase(houses.begin() + i);

            skipLine();
            logSuccess("House unlisted.");

            skipLine();
            std::system("PAUSE");  // Only works on Windows.

            return true;
        }
    }

    // Couldn't find house in houses list
    return false;
}

void System::getRequests(vector<Request*>& buffer, House* house) {
    for (int i = 0; i < requests.size(); i++) {
        skipLine();

        if (requests[i].getHouse()->getId().compare(house->getId()) == 0 &&
            requests[i].getStatus() == PENDING)
            buffer.push_back(&requests[i]);
    }
}

bool System::addPoints(Member* member, int points) {
    if (member == nullptr) {
        logError("Member not found.");
        return false;
    }

    int newPoints = member->getCreditPoints() + points;
    if (newPoints < 0) {
        logError("You don't have enough credit points.");
        return false;
    }

    member->setCreditPoints(newPoints);

    return true;
}

bool System::removePoints(Member* member, int points) {
    if (member == nullptr) {
        logError("Member not found.");
        return false;
    }

    int newPoints = member->getCreditPoints() - points;
    if (newPoints < 0) {
        logError("You don't have enough credit points.");
        return false;
    }

    member->setCreditPoints(newPoints);

    return true;
}

void System::getRatings(vector<Rating*>& buffer, House* house) {
    for (int i = 0; i < ratings.size(); i++) {
        skipLine();

        if (ratings[i].getTarget() == nullptr && ratings[i].getHouse()->getId().compare(house->getId()) == 0)
            buffer.push_back(&ratings[i]);
    }
}

void System::getRatings(vector<Rating*>& buffer, Member* member) {
    for (int i = 0; i < ratings.size(); i++) {
        skipLine();

        if (ratings[i].getTarget() != nullptr && ratings[i].getTarget()->getId().compare(member->getId()) == 0)
            buffer.push_back(&ratings[i]);
    }
}
}  // namespace HouseExchanger
