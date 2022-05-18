//
// Created by Hoang Phuc on 5/19/21.
//


#pragma once
#include <iostream>
#include <string>
#include "CustomerType.cpp"

using namespace std;

class nodeCus: public CusType {
private:
    nodeCus *next;
public:
    nodeCus();
    ~nodeCus();
    nodeCus *getNext();
    void setNext(nodeCus *anode);
    void copyData(nodeCus *tmp);
};


