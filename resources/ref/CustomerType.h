//
// Created by Hoang Phuc on 5/19/21.
//



#include <iostream>
#include <string>
#include "rentalItemList.cpp"


using namespace std;

class CusType {
private:
    string cus_id;
    string cus_name;
    string cus_address;
    string cus_phone;
    // rental_items also has its own default constructor
    int item_rented;
    int item_returned;
    int reward_point;
    rentalItemList rental_items;
    string cus_rank;
public:

    // default constructor
    CusType();

    ~CusType();

    // set part
    void setCusId(string cus_id);
    void setCusName(string cus_name);
    void setCusAddress(string cus_address);
    void setCusPhone(string cus_phone);
    void setItemRented(int number);
    void increaseItemRented();
    void increaseItemReturned();
    void isPromoted(); // when custoemr was promoted => the returned item will be decrease for te next promotion
    void setItemReturned(int number);
    void addRentalItemSpace();
    void addRewardPoint(int value);
    void usedRewardPoint();
    void addCusRentalItem(string value);
    void setCusRentalItems(string item_id, int which_item);
    void setCusRank(string cus_rank);
    void decreaseItemReturned(int value);
    void decreaseItemRented();

    // get part
    string getCusId();
    string getCusName();
    string getCusAddress();
    string getCusPhone();
    int getNumberOfRentalItem();
    string getRentalItem(int whichItem);
    string getCusRank();
    int getRewardPoint();
    int getItemReturned();

    // option function
    void deleteRentalItem(string item_id);
    void displayAllRentedItem();

    // check exist rental items
    bool isExist(string item_id);

    // get the number of rental for item to varify the input file
    int getItemRented();
};



