//
// Created by Hoang Phuc on 5/19/21.
//


#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "cusList.cpp"
#include "itemList.cpp"

using namespace std;

bool checkValidUserId(string user_input);
bool checkValidItemId(string item_id);
void checkValidIdEntered(CusList *customers, string *value, bool is_update);
void checkValidIdEntered(ItemList *items, string *value, bool is_update);
bool extract_file(string file_name, ItemList *items);
bool extract_file(string file_name, CusList *customers);
bool rentItem(CusList *customers, ItemList *items, int which_customer, string item_id);
void returnItem(CusList *customers, ItemList *items, int which_customer, string item_id);
bool promoteCustomer(CusList *customers, int which_customer);
string stringCopy(string source_string, int begin, int end);
void codeUI(CusList *customers, ItemList *items);
void saveFile(string file_name, ItemList *item);
void saveFile(string file_name, CusList *customer);
bool checkValidTitle(string value);
void checkValidTitleEntered(string *value);
bool checkValidRank(string value);
void checkValidNameEntered(string *value);
void checkValidAddressEntered(string *value);
bool checkValidPhoneNum(string phone_num);
void checkValidPhoneEntered(string *phone_num);
bool checkValidNumberOfCopies(string number_of_copies);
void checkValidNumberOfCopiesEntered(string *number_of_copies);
bool check_Rental_Fee(string fee);
void checkRentalFeeEntered(string *fee);
bool checkLoanType(string loan_type);
void checkValidLoanTypeEntered(string *loan_type);
bool checkValidRentalType(string rental_type);
void checkValidRentalTypeEntered(string *rental_type);
bool checkValidGenre(string genre);
void checkValidGenreEntered(string *genre);
bool checkItemFieldFormat(int status, string value, string file_name);
bool checkCustomerFieldFormat(int status, string value, string file_name);
void announceItemMissingField(int status, string file_name);
void announceCustomerMissingField(int status, string file_name);
bool checkCharactersInString(string value);
bool checkChar(string input);
void checkValidIdEnteredForSearching(CusList *customers, string *value);
void checkValidIdEnteredForSearching(ItemList *items, string *value);
void displayGroupMember();
















