//
// Created by Hoang Phuc on 5/19/21.
//

#include <iostream>
#include <string>
#include "itemType.h"

using namespace std;

ItemType::ItemType() {
    this->item_id = " ";
    this->title = " ";
    this->rental_type = " ";
    this->loan_type = " ";
    this->number_of_copies = 0;
    this->rental_fee = 0.0;
    this->rental_status = false;
    this->genre = " ";
}



void ItemType::setItemId(string item_id) { this->item_id = item_id; }
void ItemType::setTitle(string title) { this->title = title; }
void ItemType::setRentalType(string rental_type) { this->rental_type = rental_type; }
void ItemType::setLoanType(string loanType) { this->loan_type = loanType; }
void ItemType::setNumberOfCopies(int number_of_copies) { this->number_of_copies = number_of_copies; }
void ItemType::setRentalFee(double rental_fee) { this->rental_fee = rental_fee; }
void ItemType::setRentalStatus(bool rental_status) { this->rental_status = rental_status; }
void ItemType::setGenre(string genre) { this->genre = genre; }

string ItemType::getItemId() { return this->item_id; }
string ItemType::getTitle() { return this->title; }
string ItemType::getRentalType() { return this->rental_type; }
string ItemType::getLoanType() { return this->loan_type; }
int ItemType::getNumberOfCopies() { return this->number_of_copies; }
double ItemType::getRentalFee() { return this->rental_fee; }
bool ItemType::getRentalStatus() { return this->rental_status; }
string ItemType::getGenre() { return this->genre; }

// build option
void ItemType::decreaseNumberOfCopies() { this->number_of_copies--; }
void ItemType::increaseNumberOfCopies() { this->number_of_copies++; }
