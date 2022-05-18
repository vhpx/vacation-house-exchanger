//
// Created by Hoang Phuc on 5/19/21.
//

#include <iostream>
#include <string>
#include "cusList.h"

CusList::CusList() {
    this->head = new nodeCus();
    this->head->setNext(NULL);
}

// deconstruction
CusList::~CusList() {
    delete(head);
}

void CusList::insertNewNodeToBack() {
    nodeCus *new_node = new nodeCus();
    nodeCus *tmp = this->head;
    while (tmp->getNext() != NULL) {
        tmp = tmp->getNext();
    }
    tmp->setNext(new_node);
}

nodeCus *CusList::moveToNode(int which_node) {
    nodeCus *tmp = head;
    int count_node = 1;
    while (count_node < which_node) {
        tmp = tmp->getNext();
        count_node++;
    }
    return tmp;
}

// Setting part ------------------------------------------------------

void CusList::setNodeVal(int which_node, int which_prop, string value, int which_item, bool is_add) {
    nodeCus *tmp = moveToNode(which_node);

    // print the suitable property which match the required property
    switch (which_prop) {
        case 1:
            tmp->setCusId(value);
            break;
        case 2:
            tmp->setCusName(value);
            break;
        case 3:
            tmp->setCusAddress(value);
            break;
        case 4:
            tmp->setCusPhone(value);
            break;
        case 5:
            tmp->setItemRented(stoi(value));
            break;
        case 6:
            tmp->setCusRank(value);
            break;
        default:
            if (is_add) {
                tmp->addCusRentalItem(value);
            }else {
                tmp->setCusRentalItems(value, which_item);
            }
            break;
    }

}

void CusList::addRentalItem(int which_node, string item_id) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->addCusRentalItem(item_id);
}

void CusList::setCusId(int which_node, string id) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->setCusId(id);
}

void CusList::setCusName(int which_node, string cus_name) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->setCusName(cus_name);
}

void CusList::setCusAddress(int which_node, string address) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->setCusAddress(address);
}

void CusList::setCusPhone(int which_node, string cus_phone) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->setCusPhone(cus_phone);
}

void CusList::setCusItemRented(int which_node, int rented_item) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->setItemRented(rented_item);
}

void CusList::setCusRank(int which_node, string rank) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->setCusRank(rank);
}

// normally, this function use for setting, so the is_add wiil be false as default
void CusList::setCusRentalItem(int which_node, string item_id, int which_item, bool is_add = false) {
    nodeCus *tmp = moveToNode(which_node);
    if (is_add) {
        tmp->addRentalItemSpace();
    }
    tmp->setCusRentalItems(item_id, which_item);
}

// this function have 2 purpose 1 is set a value and 2 is reset the returned item
void CusList::setItemReturned(int which_node, int number = 0) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->setItemReturned(number);
}

void CusList::isPromoted(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->isPromoted();
}

void CusList::increaseItemRented(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->increaseItemRented();
}

void CusList::increaseItemReturned(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->increaseItemReturned();
}

void CusList::setRewardPoint(int which_node, int number_of_rental) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->addRewardPoint(number_of_rental);
}

void CusList::usedRewardPoint(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->usedRewardPoint();
}

// Getting part ------------------------------------------------------

string CusList::getCusId(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    return tmp->getCusId();
}

string CusList::getCusName(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    return tmp->getCusName();
}

string CusList::getCusAddress(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    return tmp->getCusAddress();
}

string CusList::getCusPhone(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    return tmp->getCusPhone();
}

int CusList::getCusItemRented(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    return tmp->getItemRented();
}

string CusList::getCusRank(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    return tmp->getCusRank();
}

string CusList::getCusRentalItem(int which_node, int which_item) {
    nodeCus *tmp = moveToNode(which_node);
    return tmp->getRentalItem(which_item);
}

int CusList::getItemReturned(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    return tmp->getItemReturned();
}

void CusList::deleteRentalItem(int which_node, string item_id) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->deleteRentalItem(item_id);
}

void CusList::displayRentalItem(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->displayAllRentedItem();
}

int CusList::getMaxNode() {
    int max = 0;
    nodeCus *tmp = this->head;
    while (tmp != NULL) {
        tmp = tmp->getNext();
        max++;
    }
    return max;
}

void CusList::nameSorted() {
    nodeCus *current_node = this->head;
    nodeCus *tmp = this->head->getNext();
    nodeCus *tmp2; // this variable use for swapping
    // check 2 node at the start of the list
    if (current_node->getCusName().compare(tmp->getCusName()) > 0) { // if it is greater => swap
        tmp2 = tmp;
        current_node->setNext(tmp->getNext());
        this->head = tmp2;
        this->head->setNext(current_node);
        // after this step, tmp2 become head
    }
    // continue sorting from node 2
    nodeCus *prev = this->head;
    current_node = prev->getNext();
    tmp = current_node->getNext();
    while (tmp != NULL) { // the loop will end
        if (current_node->getCusName().compare(tmp->getCusName()) > 0) {
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

int CusList::getRewardPoint(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    return tmp->getRewardPoint();
}

void swap(nodeCus *node1, nodeCus *node2) {
    nodeCus *tmp = node1;
    node1 = node2;
    node2 = tmp;
}

void CusList::idSorted() {
    nodeCus *current_node = this->head;
    nodeCus *tmp = this->head->getNext();
    nodeCus *tmp2; // this variable use for swapping
    // check 2 node at the start of the list
    if (current_node->getCusId().compare(tmp->getCusId()) > 0) { // if it is greater => swap
        tmp2 = tmp;
        current_node->setNext(tmp->getNext());
        this->head = tmp2;
        this->head->setNext(current_node);
        // after this step, tmp2 become head
    }
    // continue sorting from node 2
    nodeCus *prev = this->head;
    current_node = prev->getNext();
    tmp = current_node->getNext();
    while (tmp != NULL) { // the loop will end
        if (current_node->getCusId().compare(tmp->getCusId()) > 0) {
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

void CusList::printAllName() {
    nodeCus *tmp = this->head;
    while (tmp != NULL) {
        cout << tmp->getCusName() << endl;
        tmp = tmp->getNext();
    }
}

void CusList::printAllId() {
    nodeCus *tmp = this->head;
    while (tmp != NULL) {
        cout << tmp->getCusId() << endl;
        tmp = tmp->getNext();
    }
}

void CusList::displayAllCus(int which_sorted) {
    int max_node = getMaxNode();
    for (int i = 0; i < max_node; i++) {
        switch (which_sorted) {
            case 1:
                idSorted();
                break;
            case 2:
                nameSorted();
                break;
            default:
                break;
        }
    }
    printAllName();
}

void CusList::displayAllCusId() {
    int max_node = getMaxNode();
    idSorted();
    printAllId();
}

void CusList::printAllCusInfo() {
    nodeCus *tmp = this->head;
    displayHeader(tmp);
    while (tmp != NULL) {
        displayInformation(tmp);
        tmp = tmp->getNext();
    }
}

void CusList::displayAllCusInfo(int which_sorted){
    int max_node = getMaxNode();
    for (int i = 0; i < max_node; i++) {
        switch (which_sorted) {
            case 1:
                idSorted();
                break;
            case 2:
                nameSorted();
                break;
            default:
                break;
        }
    }
    printAllCusInfo();
}

void CusList::displayGroupMember(int which_member) {
    nodeCus *tmp = this->head;
    displayHeader(tmp);
    while (tmp != NULL) {
        switch (which_member) {
            case 1:
                if (tmp->getCusRank().compare("Guest") == 0) displayInformation(tmp);
                break;
            case 2:
                if (tmp->getCusRank().compare("Regular") == 0) displayInformation(tmp);
                break;
            case 3:
                if (tmp->getCusRank().compare("VIP") == 0) displayInformation(tmp);
                break;
            default:
                cerr << "wrong input";
        }
        tmp = tmp->getNext();
    }
}

bool CusList::displayCustomerById(string id) {
    nodeCus *tmp = this->head;
    displayHeader(tmp);
    while (tmp != NULL) {
        if (tmp->getCusId().compare(id) == 0) {
            displayInformation(tmp);
            return true;
        }
        tmp = tmp->getNext();
    }
    return false;
}

bool CusList::displayCustomerByName(string name) {
    nodeCus *tmp = this->head;
    displayHeader(tmp);
    while (tmp != NULL) {
        if (tmp->getCusName().compare(name) == 0) {
            displayInformation(tmp);
            return true;
        }
        tmp = tmp->getNext();
    }
    // if the function can find that customer => return false
    return false;
}

bool CusList::isExist(string input) {
    nodeCus *tmp = this->head;
    while (tmp != NULL) {
        if (tmp->getCusId().compare(input) == 0) {
            return true;
        }
        tmp = tmp->getNext();
    }
    return false;
}

// functions for adding new customer
nodeCus *CusList::moveToTail() {
    nodeCus *tmp = this->head;
    nodeCus *tmp2 = new nodeCus();
    while (tmp->getNext() != NULL) {
        tmp = tmp->getNext();
    }
    return tmp;
}

void CusList::setCusId(string id) {
    nodeCus *tmp = moveToTail();
    tmp->setCusId(id);
}

void CusList::setCusName(string name) {
    nodeCus *tmp = moveToTail();
    tmp->setCusName(name);
}

void CusList::setCusAddress(string address) {
    nodeCus *tmp = moveToTail();
    tmp->setCusAddress(address);
}

void CusList::setCusPhone(string cus_phone) {
    nodeCus *tmp = moveToTail();
    tmp->setCusPhone(cus_phone);
}

void CusList::setCusRank() {
    nodeCus *tmp = moveToTail();
    tmp->setCusRank("Guest"); // new customer is always set as a guest member
}

void CusList::setCusItemRented() {
    nodeCus *tmp = moveToTail();
    tmp->setItemRented(0); // new customer did not rent anything
}

int CusList::findId(string id) {
    nodeCus *tmp = this->head;
    int num_cus = 1;
    while (tmp != NULL) {
        if (tmp->getCusId().compare(id) == 0) {
            return num_cus;
        }
        num_cus++;
        tmp = tmp->getNext();
    }
    return 0; // if it doesnot have
}

bool CusList::existRentalItem(string item_id, int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    return tmp->isExist(item_id);
}

int CusList::getNumberOfRentalItem(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    return tmp->getNumberOfRentalItem();
}

int CusList::maxNameLength() {
    nodeCus *tmp = this->head;
    int max = tmp->getCusName().length();
    tmp = tmp->getNext();
    while (tmp != NULL) {
        max = (tmp->getCusName().length() > max) ? tmp->getCusName().length() : max;
        tmp = tmp->getNext();
    }
    return max;
}
int CusList::maxAddressLength() {
    nodeCus *tmp = this->head;
    int max = tmp->getCusAddress().length();
    tmp = tmp->getNext();
    while (tmp != NULL) {
        max = (tmp->getCusAddress().length() > max) ? tmp->getCusAddress().length() : max;
        tmp = tmp->getNext();
    }
    return max;
}

void CusList::displayHeader(nodeCus *tmp) {
    cout.width(tmp->getCusId().length() + 5);
    cout << left << "ID";
    cout.width(maxNameLength() + 5);
    cout << "NAME" << left;
    cout.width(maxAddressLength() + 3);
    cout << "ADDRESS" << left;
    cout.width(15);
    cout << "PHONE NUMBER" << left;
    cout.width(12);
    cout << "RENTALS" << left;
    cout.width(20);
    cout << "RANK" << endl;
}

void CusList::displayInformation(nodeCus *tmp) {
    cout.width(tmp->getCusId().length() + 5);
    cout << left << tmp->getCusId();
    cout.width(maxNameLength() + 5);
    cout << tmp->getCusName() << left;
    cout.width(maxAddressLength() + 3);
    cout << tmp->getCusAddress() << left;
    cout.width(15);
    cout << tmp->getCusPhone() << left;
    cout.width(12);
    cout << tmp->getNumberOfRentalItem() << left;
    cout.width(10);
    cout << tmp->getCusRank() << endl;
}

bool CusList::isExistItem(string item_id) {
    nodeCus *tmp = this->head;
    // check all customer in the list if any customer are borrowing item => can not delete
    while (tmp != NULL) {
        if (tmp->isExist(item_id)) return true;
        tmp = tmp->getNext();
    }
    return false;
}

void CusList::decreaseItemReturned(int which_node, int value) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->decreaseItemReturned(value);
}

void CusList::decreaseItemRented(int which_node) {
    nodeCus *tmp = moveToNode(which_node);
    tmp->decreaseItemRented();
}

void CusList::copyNode(nodeCus *tmp) {
    nodeCus *tmp_ = this->head;
    while (tmp_->getNext() != NULL) {

        tmp_ = tmp_->getNext();
    }
    tmp_->copyData(tmp);
}

CusList *CusList::copyList() {

    CusList *new_list = new CusList();

    new_list->copyNode(this->head); // copy the head to list

    nodeCus *tmp = this->head->getNext();

    while (tmp != NULL) {
        new_list->insertNewNodeToBack();
        new_list->copyNode(tmp);
        tmp = tmp->getNext();
    }
    return new_list;

}









