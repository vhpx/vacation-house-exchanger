//
// Created by Hoang Phuc on 5/19/21.
//

#include <iostream>
#include "itemNode.h"

using namespace std;

nodeItem::nodeItem(): ItemType() {

}

nodeItem::~nodeItem() {
    delete(this->next);
}

nodeItem *nodeItem::getNext() { return this->next; }
void nodeItem::setNext(nodeItem *anode) { this->next = anode; }

void nodeItem::copyNode(nodeItem *tmp) {
	setItemId(tmp->getItemId());
	setTitle(tmp->getTitle());
	setRentalType(tmp->getRentalType());
	setLoanType(tmp->getLoanType());
	setNumberOfCopies(tmp->getNumberOfCopies());
	setRentalFee(tmp->getRentalFee());
	setGenre(tmp->getGenre());
}
