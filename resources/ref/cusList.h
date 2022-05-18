//
// Created by Hoang Phuc on 5/19/21.


#pragma once
#include <iostream>
#include <string>
#include "cusNode.cpp"

using namespace std;

class CusList {
private:
    nodeCus *head;
public:
    CusList();
    ~CusList();
    void insertNewNodeToBack();
    nodeCus *moveToNode(int which_node);
    nodeCus *moveToTail();

    /*
    which_prop definition:
    1: id
    2: name
    3: address
    4: phone
    5: Number of ItemRented
    6: Rank
    7: ItemRented
    */
    // if user need to set or add rental item, they need to fill in the last 2 parameters
    void setNodeVal(int which_node, int which_prop, string value, int which_item = 0, bool is_add = true);

    // set single property
    void setCusId(int which_node, string id);

    void setCusName(int which_node, string name);

    void setCusAddress(int which_node, string address);

    void setCusPhone(int which_node, string cus_phone);

    void setCusRank(int which_node, string cus_rank);

    void setCusRentalItem(int which_node, string item_id, int which_item, bool is_add);

    void addRentalItem(int which_node, string item_id);

    void increaseItemRented(int which_node);

    void setCusItemRented(int which_node, int rented_item);

    void setRewardPoint(int which_node, int number_of_rental);
    void usedRewardPoint(int which_node);

    void setItemReturned(int which_node, int number);

    void increaseItemReturned(int which_node);
    void decreaseItemReturned(int which_node, int value);
    void decreaseItemRented(int which_node);
    void isPromoted(int which_node);

    // get single property
    string getCusId(int which_node);
    string getCusName(int which_node);
    string getCusAddress(int which_node);
    string getCusPhone(int which_node);
    int getNumberOfRentalItem(int which_node);
    string getCusRank(int which_node);
    string getCusRentalItem(int which_node, int which_item);
    int getItemReturned(int which_node);
    int getRewardPoint(int which_node);

    // if the users doesn't need to get the rental item, they need not to insert the item id
    string getNodeVal(int which_node, int which_prop, int which_item);
    // delete rentalItem
    void deleteRentalItem(int which_node, string item_id);
    void displayRentalItem(int which_node);
    nodeCus *findCustomer(int which_node);
    // which sort is the choice of customer, 0: non-sorted, 1: id-sorted, 2: name-sorted
    void displayAllCus(int which_sorted);
    int getMaxNode();
    void nameSorted();
    void idSorted();
    void printAllName();

    // function display group member
    void displayGroupMember(int which_member); // 1: Guest, 2: Regular, 3: VIP

    // display customer by order
    bool displayCustomerById(string id);
    bool displayCustomerByName(string name);
    void printAllId();
    void displayAllCusId();
    void printAllCusInfo();
    void displayAllCusInfo(int which_sorted);
    // create check if the input id is existed
    bool isExist(string id);

    // functions for entering new customer information
    void setCusId(string id);

    void setCusName(string name);

    void setCusAddress(string address);

    void setCusPhone(string cus_phone);

    void setCusRank();

    void setCusItemRented();

    // find user id in list
    int findId(string id);

    // check exist rental item
    bool existRentalItem(string item_id, int which_node);

    // get the number of rental item for varifying
    int getCusItemRented(int which_node);

    void displayHeader(nodeCus *tmp);
    void displayInformation(nodeCus *tmp);
    // use for formatting
    int maxNameLength();
    int maxAddressLength();

    // find item is exist in all customer rental list
    bool isExistItem(string item_id);

    void copyNode(nodeCus *tmp);
    CusList *copyList();
};


