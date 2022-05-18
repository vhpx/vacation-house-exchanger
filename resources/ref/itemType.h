//
// Created by Hoang Phuc on 5/19/21.
//



#pragma once
#include <iostream>
#include <string>

using namespace std;

class ItemType {
private:
    string item_id;
    string title;
    string rental_type;
    string loan_type;
    int number_of_copies;
    double rental_fee;
    bool rental_status; // false: borrowed, true: available
    string genre;
public:
    // default parameter
    ItemType();

    // Set component
    void setItemId(string item_id);
    void setTitle(string title);
    void setRentalType(string rental_type);
    void setLoanType(string loanType);
    void setNumberOfCopies(int number_of_copies);
    void setRentalFee(double rental_fee);
    void setRentalStatus(bool rental_status);
    void setGenre(string genre);

    // get component
    string getItemId();
    string getTitle();
    string getRentalType();
    string getLoanType();
    int getNumberOfCopies();
    double getRentalFee();
    bool getRentalStatus();
    string getGenre();

    // functions for renting and returning
    void decreaseNumberOfCopies();
    void increaseNumberOfCopies();
};


