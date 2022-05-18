//
// Created by Hoang Phuc on 5/19/21.
//


#pragma once
#include <iostream>
#include <string>
#include "itemNode.cpp"

using namespace std;

class ItemList {
private:
    nodeItem *head;
public:
    ItemList();
    ~ItemList();
    // create function to extend the list length
    void insertNewNodeToBack();
    nodeItem *moveToNode(int which_node);

    // access to the node which need to be set
    // which_prop means to set the specific property
    /*
        1: item id
        2: title
        3: rental type
        4: loan type
        5: number of copies
        6: rental fee
        7: rental status
        8: genre (for movie and DVD)
     */
    // value is the value to set the property
    void setNodeVal(int which_node, int which_prop, string value);

    // single set
    void setId(int which_node, string value);
    void setTitle(int which_node, string value);
    void setRentalType(int which_node, string value);
    void setLoanType(int which_node, string value);
    void setNumberOfCopies(int which_node, string value);
    void setRentalFee(int which_node, string value);
    void setRentalStatus(string item_id, bool is_borrowed);
    void setGenre(int which_node, string value);

    string getId(int which_node);
    string getTitle(int which_node);
    string getRentalType(int which_node);
    string getLoanType(int which_node);
    int getNumberOfCopies(int which_node);
    double getRentalFee(int which_node);
    bool getRentalStatus(int which_node);
    string getGenre(int which_node);

    // build option
    bool checkAvailable(string item_id);
    void decreaseNumberOfCopies(string item_id);
    void increaseNumberOfCopies(string item_id);

    // functions for sorting
    int getMaxNode();
    void idSorted();
    void titleSort();

    // display item by order
    bool displayItemById(string item_id);
    bool displayItemByTitle(string title);

    // set for new items
    void setId(string value);
    void setTitle(string value);
    void setRentalType(string value);
    void setLoanType(string value);
    void setNumberOfCopies(string value);
    void setRentalFee(string value);
    void setRentalStatus(bool is_borrowed);
    void setGenre(string value);

    void printAllItem();
    void displayItemBySort(int which_sort);
    void displayAvailableItem();
    // display out of stock items
    bool displayOutOfStock();

    // find the order of id in the list
    int findId(string id);

    // delete item in item list
    void deleteItem(string id);
    double getPaid(string id);

    // find max title length
    int maxTitleLength();

    // display header
    void displayHeader(nodeItem *tmp);

    // display information
    void displayInformation(nodeItem *tmp);

    // use for move to the end of the list
    nodeItem *moveToTail();

    // copy list
    void copyNode(nodeItem *tmp);
    ItemList *copyList();
};



