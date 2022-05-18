//
// Created by Hoang Phuc on 5/19/21.
//

#include <iostream>
#include <string>
#include "rentalItemNode.h"

using namespace std;

rentalItemNode::rentalItemNode() {
    this->item_id = " ";
}

rentalItemNode::rentalItemNode(string item_id) {
    this->item_id = item_id;
}

rentalItemNode::~rentalItemNode() {

}

rentalItemNode *rentalItemNode::getNext() {
    return this->next;
}

void rentalItemNode::setNext(rentalItemNode *anode) {
    this->next = anode;
}

void rentalItemNode::setItemId(string item_id) {
    this->item_id = item_id;
}

string rentalItemNode::getItemId() {
    return this->item_id;
}

