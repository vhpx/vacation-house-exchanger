//
// Created by Hoang Phuc on 5/19/21.
//

#include <iostream>
#include <string>
#include "rentalItemList.h"

using namespace std;

rentalItemList::rentalItemList() {
    this->head = new rentalItemNode();
    this->head->setNext(NULL);
}

rentalItemList::~rentalItemList() {
}

void rentalItemList::insertItem() {
    rentalItemNode *tmp = this->head;
    rentalItemNode *new_item = new rentalItemNode();

    while (tmp->getNext() != NULL) {

        tmp = tmp->getNext();
    }
    tmp->setNext(new_item);
}

void rentalItemList::addItem(string item_id) {
    rentalItemNode *tmp = this->head;
    rentalItemNode *new_item = new rentalItemNode(item_id);
    // add to head first
    if (head->getItemId() == " ") {
        head = new_item;
    }else {
        while (tmp->getNext() != NULL) {
            tmp = tmp->getNext();
        }
        tmp->setNext(new_item);
        tmp = tmp->getNext();
    }
    tmp->setNext(NULL);
}

void rentalItemList::setItem(string item_id, int which_item) {
    rentalItemNode *tmp = head;
    int count_node = 0;
    while (count_node < which_item) {
        tmp = tmp->getNext();
        count_node++;
    }
    tmp->setItemId(item_id);
}

string rentalItemList::getItem(int which_item) {
    rentalItemNode *tmp = head;
    int count_node = 1;
    while (count_node < which_item) {
        tmp = tmp->getNext();
        count_node++;
    }

    return tmp->getItemId();
}

void rentalItemList::deleteItem(string item_id) {
    rentalItemNode *tmp = this->head;
    // check if the number of items is 1 => set the item id = " " to avoid the lost of the list
    if (getNumberOfItem() == 1) {
        this->head->setItemId(" ");
        return;
    }
    // when tmp has been saved => move it to the next node
    // check the first node which is pre
    if (head->getItemId().compare(item_id) == 0) {
        head = head->getNext();
        delete tmp;
        // the program would be end immediately after file a suitable node
        return;
    }else {
        rentalItemNode *prev = new rentalItemNode();
        while (tmp !=  NULL) {
            if (tmp->getItemId().compare(item_id) == 0) {
                break;
            }
            prev = tmp;
            tmp = tmp->getNext();
        }
        prev->setNext(tmp->getNext());
        delete tmp;
    }
}

void rentalItemList::showAllItem() {
    rentalItemNode *tmp = this->head;
    while (tmp != NULL) {
        cout << tmp->getItemId() << endl;
        tmp = tmp->getNext();
    }
    delete(tmp);
}

bool rentalItemList::isExist(string item_id) {
    rentalItemNode *tmp = this->head;
    while (tmp != NULL) {
        if (tmp->getItemId().compare(item_id) == 0) {
            return true;
        }
        tmp = tmp->getNext();
    }
    return false;
}

int rentalItemList::getNumberOfItem() {
    rentalItemNode *tmp = this->head;
    if (this->head->getItemId() == " ") return 0;
    int count = 0;
    while (tmp != NULL) {
        count++;
        tmp = tmp->getNext();
    }
    return count;
}







