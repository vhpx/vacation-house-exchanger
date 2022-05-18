//
// Created by Hoang Phuc on 5/19/21.
//

#include <iostream>
#include <string>
#include "itemList.h"

#define TAB_SPACE 25

using namespace std;

ItemList::ItemList() {
    this->head = new nodeItem();
    // set the next node NULL
    this->head->setNext(NULL);
}

ItemList::~ItemList() {
    delete(head);
}

void ItemList::insertNewNodeToBack() {
    nodeItem *new_node = new nodeItem();
    nodeItem *tmp = head;
    while (tmp->getNext() != NULL) {
        tmp = tmp->getNext();
    }
    tmp->setNext(new_node);
}

nodeItem *ItemList::moveToNode(int which_node) {
    nodeItem *tmp = head;
    int count_node = 1;
    while (count_node < which_node) {
        tmp = tmp->getNext();
        count_node++;
    }
    return tmp;
}

void ItemList::setNodeVal(int which_node, int which_prop, string value) {
    nodeItem *tmp = head;
    int count_node = 1;
    while (count_node < which_node) {
        tmp = tmp->getNext();
        count_node++;
    }

    // print the suitable property which match the required property
    if (which_prop == 1) tmp->setItemId(value);
    else if (which_prop == 2) tmp->setTitle(value);
    else if (which_prop == 3) tmp->setRentalType(value);
    else if (which_prop == 4) tmp->setLoanType(value);
    else if (which_prop == 5) tmp->setNumberOfCopies(stoi(value));
    else if (which_prop == 6) tmp->setRentalFee(stod(value));
    else tmp->setGenre(value);
}

void ItemList::setId(int which_node, string value) {
    nodeItem *tmp = moveToNode(which_node);
    tmp->setItemId(value);
}

void ItemList::setTitle(int which_node, string value) {
    nodeItem *tmp = moveToNode(which_node);
    tmp->setTitle(value);
}

void ItemList::setRentalType(int which_node, string value) {
    nodeItem *tmp = moveToNode(which_node);
    tmp->setRentalType(value);
}

void ItemList::setLoanType(int which_node, string value) {
    nodeItem *tmp = moveToNode(which_node);
    tmp->setLoanType(value);
}

void ItemList::setNumberOfCopies(int which_node, string value) {
    nodeItem *tmp = moveToNode(which_node);
    tmp->setNumberOfCopies(stoi(value));
}

void ItemList::setRentalFee(int which_node, string value) {
    nodeItem *tmp = moveToNode(which_node);
    tmp->setRentalFee(stod(value));
}

void ItemList::setRentalStatus(string item_id, bool is_borrowed) {
    nodeItem *tmp = this->head;
    while (tmp->getItemId() != item_id) {
        tmp = tmp->getNext();
    }
    tmp->setRentalStatus(is_borrowed);
}

void ItemList::setGenre(int which_node, string value) {
    nodeItem *tmp = moveToNode(which_node);
    tmp->setGenre(value);
}



string ItemList::getId(int which_node) {
    nodeItem *tmp = moveToNode(which_node);
    return tmp->getItemId();
}

string ItemList::getTitle(int which_node) {
    nodeItem *tmp = moveToNode(which_node);
    return tmp->getTitle();
}

string ItemList::getRentalType(int which_node) {
    nodeItem *tmp = moveToNode(which_node);
    return tmp->getRentalType();
}

string ItemList::getLoanType(int which_node) {
    nodeItem *tmp = moveToNode(which_node);
    return tmp->getLoanType();
}

int ItemList::getNumberOfCopies(int which_node) {
    nodeItem *tmp = moveToNode(which_node);
    return tmp->getNumberOfCopies();
}

double ItemList::getRentalFee(int which_node) {
    nodeItem *tmp = moveToNode(which_node);
    return tmp->getRentalFee();
}

bool ItemList::getRentalStatus(int which_node) {
    nodeItem *tmp = moveToNode(which_node);
    return tmp->getRentalStatus();
}

string ItemList::getGenre(int which_node) {
    nodeItem *tmp = moveToNode(which_node);
    return tmp->getGenre();
}

// Option function
bool ItemList::checkAvailable(string item_id) {
    nodeItem *tmp = this->head;
    while (tmp->getItemId() != item_id) {
        tmp = tmp->getNext();
    }
    if (tmp->getNumberOfCopies() > 0) {
        return true;
    }else {
        // check if it is no copies in stock => set it status immediately
        tmp->setRentalStatus("borrowed");
        return false;
    }
}

void ItemList::decreaseNumberOfCopies(string item_id) {
    nodeItem *tmp = this->head;
    while (tmp->getItemId() != item_id) {
        tmp = tmp->getNext();
    }
    tmp->decreaseNumberOfCopies();
}

void ItemList::increaseNumberOfCopies(string item_id) {
    nodeItem *tmp = this->head;
    while (tmp->getItemId() != item_id) {
        tmp = tmp->getNext();
    }
    tmp->increaseNumberOfCopies();
}

int ItemList::getMaxNode() {
    nodeItem *tmp = this->head;
    int count_node = 0;
    while (tmp != NULL) {
        count_node++;
        tmp = tmp->getNext();
    }
    return count_node;
}

void ItemList::idSorted() {
    nodeItem *current_node = this->head;
    nodeItem *tmp = this->head->getNext();
    nodeItem *tmp2; // this variable use for swapping
    // check 2 node at the start of the list
    if (current_node->getItemId().compare(tmp->getItemId()) > 0) { // if it is greater => swap
        tmp2 = tmp;
        current_node->setNext(tmp->getNext());
        this->head = tmp2;
        this->head->setNext(current_node);
        // after this step, tmp2 become head
    }
    // continue sorting from node 2
    nodeItem *prev = this->head;
    current_node = prev->getNext();
    tmp = current_node->getNext();
    while (tmp != NULL) { // the loop will end
        if (current_node->getItemId().compare(tmp->getItemId()) > 0) {
            tmp2 = tmp;
            current_node->setNext(tmp->getNext());
            prev->setNext(tmp2);
            tmp2->setNext(current_node);
            prev = tmp2;
        }else {
            prev = current_node;
            current_node = current_node->getNext();
        }
        tmp = current_node->getNext();
    }
}

void ItemList::titleSort() {
    nodeItem *current_node = this->head;
    nodeItem *tmp = this->head->getNext();
    nodeItem *tmp2; // this variable use for swapping
    // check 2 node at the start of the list
    if (current_node->getTitle().compare(tmp->getTitle()) > 0) { // if it is greater => swap
        tmp2 = tmp;
        current_node->setNext(tmp->getNext());
        this->head = tmp2;
        this->head->setNext(current_node);
        // after this step, tmp2 become head
    }
    // continue sorting from node 2
    nodeItem *prev = this->head;
    current_node = prev->getNext();
    tmp = current_node->getNext();
    while (tmp != NULL) { // the loop will end
        if (current_node->getTitle().compare(tmp->getTitle()) > 0) {
            tmp2 = tmp;
            current_node->setNext(tmp->getNext());
            prev->setNext(tmp2);
            tmp2->setNext(current_node);
            prev = tmp2;
        }else {
            prev = current_node;
            current_node = current_node->getNext();
        }
        tmp = current_node->getNext();
    }
}

bool ItemList::displayOutOfStock() {
    nodeItem *tmp = this->head;
    bool is_has = false;
    displayHeader(tmp);
    while (tmp != NULL) {
        if (tmp->getNumberOfCopies() == 0) {
            displayInformation(tmp);
            is_has = true;
        }
        tmp = tmp->getNext();
    }
    return is_has;
    delete(tmp);
}

bool ItemList::displayItemById(string item_id) {
    nodeItem *tmp = this->head;
    displayHeader(tmp);
    while (tmp != NULL) {
        string item = tmp->getItemId();
        if (item.compare(item_id) == 0) {
            displayInformation(tmp);
            return true;
        }
        tmp = tmp->getNext();
    }
    return false;
}

bool ItemList::displayItemByTitle(string title) {
    nodeItem *tmp = this->head;
    displayHeader(tmp);
    while (tmp != NULL) {
        if (tmp->getTitle().compare(title) == 0) {
            displayInformation(tmp);
            return true;
        }
        tmp = tmp->getNext();
    }
    // if the function can find the item => print not found
    return false;
}

nodeItem *ItemList::moveToTail() {
    nodeItem *tmp = this->head;
    while (tmp->getNext() != NULL) {
        tmp = tmp->getNext();
    }
    return tmp;
}
void ItemList::setId(string value) {
    nodeItem *tmp = moveToTail();
    tmp->setItemId(value);
}

void ItemList::setTitle(string value) {
    nodeItem *tmp = moveToTail();
    tmp->setTitle(value);
}

void ItemList::setRentalType(string value) {
    nodeItem *tmp = moveToTail();
    tmp->setRentalType(value);
}

void ItemList::setLoanType(string value) {
    nodeItem *tmp = moveToTail();
    tmp->setLoanType(value);
}

void ItemList::setNumberOfCopies(string value) {
    nodeItem *tmp = moveToTail();
    tmp->setNumberOfCopies(stoi(value));
}
void ItemList::setRentalFee(string value) {
    nodeItem *tmp = moveToTail();
    tmp->setRentalFee(stod(value));
}

void ItemList::setRentalStatus(bool is_borrowed) {
    nodeItem *tmp = moveToTail();
    tmp->setRentalStatus(false); // automatically true because new item should be borrowed at the insert time
}
void ItemList::setGenre(string value) {
    nodeItem *tmp = moveToTail();
    tmp->setGenre(value);
}

void ItemList::printAllItem() {
    nodeItem *tmp = this->head;
    displayHeader(tmp);
    while (tmp != NULL) {
        displayInformation(tmp);
        tmp = tmp->getNext();
    }
}

void ItemList::displayItemBySort(int which_sort) {
    int max_node = getMaxNode();
    for (int i = 0; i < max_node; i++) {
        switch (which_sort) {
            case 1:
                idSorted();
                break;
            case 2:
                titleSort();
                break;
            default:
                break;
        }
    }
    printAllItem();
}

int ItemList::maxTitleLength() {
    nodeItem *tmp = this->head;
    int max = tmp->getTitle().length();
    tmp = tmp->getNext();
    while (tmp != NULL) {
        if (tmp->getTitle().length() > max) max = tmp->getTitle().length();
        tmp = tmp->getNext();
    }
    return max;
}

void ItemList::displayHeader(nodeItem *tmp) {
    cout.width(tmp->getItemId().length() + 5);
    cout << left << "ID";
    cout.width(maxTitleLength() + 5);
    cout << "TITLE" << left;
    cout.width(20);
    cout << "RENTAL TYPE" << left;
    cout.width(15);
    cout << "LOAN TYPE" << left;
    cout.width(25);
    cout << "NUMBER OF COPIES" << left;
    cout.width(20);
    cout << "RENTAL FEE" << left;
    cout.width(10);
    cout << "GENRE" << endl;
}

void ItemList::displayInformation(nodeItem *tmp) {
    cout.width(tmp->getItemId().length() + 5);
    cout << left << tmp->getItemId();
    cout.width(maxTitleLength() + 5);
    cout << tmp->getTitle() << left;
    cout.width(20);
    cout << tmp->getRentalType() << left;
    cout.width(15);
    cout << tmp->getLoanType() << left;
    cout.width(25);
    cout << tmp->getNumberOfCopies() << left;
    cout.width(20);
    cout << tmp->getRentalFee() << left;
    cout.width(10);
    cout << tmp->getGenre() << endl;
}

void ItemList::displayAvailableItem() {
    nodeItem *tmp = this->head;
    displayHeader(tmp);
    while (tmp != NULL) {
        if (tmp->getNumberOfCopies() > 0) {
            displayInformation(tmp);
        }
        tmp = tmp->getNext();
    }
}

int ItemList::findId(string id) {
    nodeItem *tmp = this->head;
    int num_node = 1;
    while (tmp != NULL) {
        if (tmp->getItemId().compare(id) == 0) {
            return num_node;
        }
        num_node++;
        tmp = tmp->getNext();
    }
    return 0;
}

void ItemList::deleteItem(string id) {
    nodeItem *tmp = this->head;
    // check if the head is matched
    if (tmp->getItemId().compare(id) == 0) {
        this->head = tmp->getNext();
        return;
    }

    nodeItem *prev = tmp;
    tmp = tmp->getNext();
    while (tmp != NULL) {
        if (tmp->getItemId().compare(id) == 0) {
            prev->setNext(tmp->getNext());
            delete tmp;
            return;
        }
        prev = tmp;
        tmp = tmp->getNext();
    }
}

double ItemList::getPaid(string id) {
    nodeItem *tmp = this->head;
    int num_node = 1;
    while (tmp != NULL) {
        if (tmp->getItemId().compare(id) == 0) {
            return tmp->getRentalFee();
        }
        tmp = tmp->getNext();
    }
    return 0.0;
}

void ItemList::copyNode(nodeItem *tmp) {
    nodeItem *tmp_ = this->head;
    while (tmp_->getNext() != NULL) {

        tmp_ = tmp_->getNext();
    }
    tmp_->copyNode(tmp);
}

ItemList *ItemList::copyList() {

    ItemList *new_list = new ItemList();

    new_list->copyNode(this->head); // copy the head to list

    nodeItem *tmp = this->head->getNext();

    while (tmp != NULL) {
        new_list->insertNewNodeToBack();
        new_list->copyNode(tmp);
        tmp = tmp->getNext();
    }
    return new_list;

}










