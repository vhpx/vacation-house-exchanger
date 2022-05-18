//
// Created by Hoang Phuc on 5/19/21.
//


#pragma once
#include <iostream>
#include <string>
#include "rentalItemNode.cpp"

using namespace std;

class rentalItemList {
private:
    rentalItemNode *head;
public:
    rentalItemList();
    ~rentalItemList();
    // insert in the back
    void insertItem();
    void addItem(string item_id);
    void setItem(string item_id, int which_item);
    string getItem(int which_item);
    int getNumberOfItem();

    // option function
    void deleteItem(string item_id);
    void showAllItem();

    // check the item id exist in list
    bool isExist(string item_id);
};


