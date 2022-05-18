//
// Created by Hoang Phuc on 5/19/21.
//

#include <iostream>
#include "cusNode.h"

using namespace std;

nodeCus::nodeCus() : CusType() { }

nodeCus::~nodeCus() {
	delete(this->next);
}

nodeCus *nodeCus::getNext() {
    return this->next;
}

void nodeCus::setNext(nodeCus *anode) { this->next = anode; }

void nodeCus::copyData(nodeCus *tmp) {
	this->setCusId(tmp->getCusId());
    this->setCusName(tmp->getCusName());
    this->setCusAddress(tmp->getCusAddress());
    this->setCusPhone(tmp->getCusPhone());
    this->setItemRented(tmp->getItemRented());
    this->setCusRank(tmp->getCusRank());
}
