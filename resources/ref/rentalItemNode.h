//
// Created by Hoang Phuc on 5/19/21.
//


#pragma once
#include <iostream>
#include <string>

using namespace std;

class rentalItemNode {
private:
    string item_id;
    rentalItemNode *next;
public:
    rentalItemNode();
    rentalItemNode(string item_id);
    ~rentalItemNode();
    rentalItemNode *getNext();
    void setNext(rentalItemNode *anode);
    void setItemId(string item_id);
    string getItemId();

};

