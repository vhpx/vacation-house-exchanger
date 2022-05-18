//
// Created by Hoang Phuc on 5/19/21.
//

#include <iostream>
#include "CustomerType.h"

CusType::CusType() {
    this->cus_id = " ";
    this->cus_name = " ";
    this->cus_address = " ";
    this->cus_phone = " ";
    this->cus_rank = " ";
    this->item_returned = 0;
    this->reward_point = 0;
}

CusType::~CusType() {

}

void CusType::setCusId(string cus_id) { this->cus_id = cus_id; }

void CusType::setCusName(string cus_name) { this->cus_name = cus_name; }

void CusType::setCusAddress(string cus_address) { this->cus_address = cus_address; }

void CusType::setCusPhone(string cus_phone) { this->cus_phone = cus_phone; }

void CusType::addRentalItemSpace() { this->rental_items.insertItem(); }

void CusType::setCusRentalItems(string item_id, int which_item) { rental_items.setItem(item_id, which_item); }

void CusType::addCusRentalItem(string value) { this->rental_items.addItem(value);}

void CusType::setCusRank(string cus_rank) { this->cus_rank = cus_rank; }

void CusType::increaseItemRented() { this->item_rented++; }
void CusType::setItemRented(int number) { this->item_rented = number; }
void CusType::increaseItemReturned() { this->item_returned += 1; }
void CusType::isPromoted() { this->item_returned -= 3; }
void CusType::setItemReturned(int number) { this->item_returned = number; }
void CusType::addRewardPoint(int value) { this->reward_point = value * 10; }
void CusType::usedRewardPoint() { this->reward_point -= 100; } // is the user use this free promote => their point will be decreased 100 points;

string CusType::getCusId() { return this->cus_id; }
string CusType::getCusName() { return this->cus_name; }
string CusType::getCusAddress() { return this->cus_address;}
string CusType::getCusPhone() { return this->cus_phone; }
int CusType::getNumberOfRentalItem() { return this->item_rented; }
string CusType::getRentalItem(int whichItem) { return rental_items.getItem(whichItem); }
string CusType::getCusRank() { return this->cus_rank; }
int CusType::getRewardPoint() { return this->reward_point; }
int CusType::getItemReturned() { return this->item_returned; }

// option function
void CusType::deleteRentalItem(string item_id) {
    this->rental_items.deleteItem(item_id);
}

void CusType::displayAllRentedItem() {
    this->rental_items.showAllItem();
}

bool CusType::isExist(string item_id) {
    return this->rental_items.isExist(item_id);
}

int CusType::getItemRented() { return this->rental_items.getNumberOfItem(); }

void CusType::decreaseItemReturned(int value) { this->item_returned = this->item_returned - 10; }

void CusType::decreaseItemRented() { this->item_rented -= 1;}








