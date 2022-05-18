//
// Created by Hoang Phuc on 5/19/21.
//



#pragma once
#include <iostream>
#include "itemType.cpp"

using namespace std;

// Inherit all properties from ItemType class
class nodeItem: public ItemType {
private:
    nodeItem *next;
public:
    nodeItem();
    ~nodeItem();

    void copyNode(nodeItem *tmp);

    // create node property which contain data and the linking
    nodeItem *getNext();
    void setNext(nodeItem *anode);
};



