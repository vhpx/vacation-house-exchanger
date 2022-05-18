#include "optionFile.h"

#include <iostream>
#include <string>

#define CURRENT_YEAR 2021

using namespace std;

string stringCopy(string source_string, int begin, int end) {
    int i;
    char ch[20] = {'\0'};
    // store the character of the source string into a copy string
    for (i = begin; i < end; i++) {
        ch[i - begin] = source_string[i];
    }
    return string(ch);
}

// validate user input
bool checkValidUserId(string user_input) {
    // check correct length
    if (user_input.length() != 4) {
        return false;
    }

    // check if there are any space
    for (int i = 0; i < user_input.length(); i++) {
        if (user_input[i] == ' ') return false;
    }
    // check if the first letter is correct;
    if (user_input[0] != 'C') return false;
    // check the number is digit
    for (int i = 1; i < user_input.length(); i++) {
        if (!((user_input[i] >= 48) && (user_input[i] <= 57))) {
            return false;
        }
    }
    return true;
}

// check item id format
bool checkValidItemId(string item_id) {
    if (item_id.length() != 9) return false;

    // check the first letter of item_id
    if (item_id[0] != 'I') return false;

    // check number
    for (int i = 1; i < item_id.length(); i++) {
        if (!((item_id[i] >= 48) && (item_id[i] <= 57))) {
            // if the character is difference from the digit range => check if it is -
            if (i != 4) return false;
            else {
                // check - character
                if (item_id[i] != '-') return false;
            }
        }
    }

    // check year must be before current year
    string year = stringCopy(item_id, 5, item_id.length());
    if (stoi(year) > CURRENT_YEAR) return false;
    return true;
}

bool checkValidTitle(string value) {
    // title does not have space at the end in at the beginning
    if ((value[0] == ' ') || (value[value.length() - 1] == ' ')) return false;
    return true;
}

void checkValidTitleEntered(string *value) {
    while (!checkValidTitle(*value)) {
        cout << "Wrong title format.\n";
        cout << "You have to enter name not contain whitespace at the beinning and the end.\n";
        cout << "Re-enter title: ";
        fflush(stdin);
        getline(cin, *value);
    }
}

bool checkValidRank(string value) {
    // create a list for comparing
    string rank[3] = { "Guest", "Regular", "VIP"};
    // loop through the comparing list if the input rank is matched
    for (int i = 0; i < 3; i++) {
        if (value.compare(rank[i]) == 0) return true;
    }
    return false;
}

void checkValidNameEntered(string *value) {
    // name of customer has a same algorithm to check the format with the title
    while (!checkValidTitle(*value)) {
        cout << "Wrong name format.\n";
        cout << "You have to enter name not contain whitespace at the beginning and the end.\n";
        cout << "Re-enter name: ";
        fflush(stdin);
        getline(cin, *value);
    }
}

void checkValidAddressEntered(string *value) {
    // address of customer has a same algorithm to check the format with the title
    while (!checkValidTitle(*value)) {
        cout << "Wrong address format.\n";
        cout << "You have to enter name not contain whitespace at the beginning and the end.\n";
        cout << "Re-enter address: ";
        fflush(stdin);
        getline(cin, *value);
    }
}

// process for valid id entered for customer id
void checkValidIdEntered(CusList *customers, string *value, bool is_update = false) {
    while (!checkValidUserId(*value)) {
        cout << "You enter wrong id format: ";
        fflush(stdin);
        getline(cin, *value);
    }
    // check if the id is exist
    if (!is_update) { // if add a new item =>check if customer id is exist
        while (customers->isExist(*value)) {
            cout << "Your id has been already used. Please Enter a new id: ";
            fflush(stdin);
            cin >> *value;
            // check if that this step user enter wrong user id format
            while (!checkValidUserId(*value)) {
                cout << "You enter wrong id format";
                cout << "You have to enter id in this format: Cxxx, xxx is a unique code of 3 digits (e.g. 123), eg: C001.\n";
                cout << "Re-enter id: ";
                fflush(stdin);
                getline(cin, *value);
            }
        }
    }else { // check if the customer is in customer list
        while (!customers->isExist(*value)) {
            cout << "Can not found the id. Please re-enter customer id: ";
            fflush(stdin);
            cin >> *value;
            // check if that this step user enter wrong user id format
            while (!checkValidUserId(*value)) {
                cout << "You enter wrong id format";
                cout << "You have to enter id in this format: Cxxx, xxx is a unique code of 3 digits (e.g. 123), eg: C001.\n";
                cout << "Re-enter id: ";
                fflush(stdin);
                getline(cin, *value);
            }
        }
    }
}

void checkValidIdEnteredForSearching(CusList *customers, string *value) {
    while (!checkValidUserId(*value)) {
        cout << "You enter wrong id format";
        cout << "You have to enter id in this format: Cxxx, xxx is a unique code of 3 digits (e.g. 123), eg: C001.\n";
        cout << "Re-enter id: ";
        fflush(stdin);
        getline(cin, *value);
    }
}

void checkValidIdEnteredForSearching(ItemList *items, string *value) {
    while (!checkValidItemId(*value)) {
        cout << "Your id is wrong format\n";
        cout << "Enter item id: ";
        fflush(stdin);
        getline(cin, *value);
    }
}

// process for valid id entered for item id
void checkValidIdEntered(ItemList *items, string *value, bool is_update = false) {
    // check the correct format
    while (!checkValidItemId(*value)) {
        cout << "Your id is wrong format\n";
        cout << "Enter item id: ";
        fflush(stdin);
        getline(cin, *value);
    }

    // check if the user want to update the item information => check if the item id is exist in stock
    if (is_update) {
        while (items->findId(*value) == 0) {
            cout << "Your item id is not existed in stock\n";
            cout << "Re-enter item id: ";
            fflush(stdin);
            getline(cin, *value);
            // check if input id is valid
            while (!checkValidItemId(*value)) {
                cout << "Your id is wrong format\n";
                cout << "You have to enter item in format : Ixxx-yyyy\nxxx is a unique code of 3 digits (e.g. 123)\nyyyy s the year the item was published (e.g. 1980)\neg: I001-1980\n";
                cout << "Enter item id: ";
                fflush(stdin);
                getline(cin, *value);
            }
        }
    }else {
        // if it is not update => check format only
        while (!checkValidItemId(*value)) {
            cout << "Your id is wrong format\n";
            cout << "You have to enter item in format : Ixxx-yyyy\nxxx is a unique code of 3 digits (e.g. 123)\nyyyy s the year the item was published (e.g. 1980)\neg: I001-1980\n";
            cout << "Enter item id: ";
            fflush(stdin);
            getline(cin, *value);
        }
    }
}

// check valid phone number and number of copies (both property must be integer)
bool checkValidPhoneNum(string phone_num) {
    // the length of phone number must be 10
    if (phone_num.length() != 10) return false;

    // check if is there any character out of range 0->9
    for(int i = 0; i < phone_num.length(); i++){
        if(!((phone_num[i] >= '0') && (phone_num[i] <= '9'))) return false;
    }
    return true;
}

// process for checking number'
void checkValidPhoneEntered(string *phone_num) {
    while (!checkValidPhoneNum(*phone_num)) {
        cout << "Wrong phone number format.\n";
        cout << "Your input must be contained only digit from 0 to 9" << endl;
        cout << "Re-enter phone number: ";
        fflush(stdin);
        getline(cin, *phone_num);
    }
}

// check valid number of copies
bool checkValidNumberOfCopies(string number_of_copies) {
    // the number of copies must be strictly integer
    for(int i = 0; i < number_of_copies.length(); i++){
        if (!((number_of_copies[i] >= '0') && (number_of_copies[i] <= '9'))) return false;
    }
    return true;
}

// process for checking entered number of copies
void checkValidNumberOfCopiesEntered(string *number_of_copies) {
    while (!checkValidNumberOfCopies(*number_of_copies)) {
        cout << "Wrong format for number of copies.\n";
        cout << "Your input must be contained digits from 0 to 9" << endl;
        cout << "Re-enter number of copies: ";
        fflush(stdin);
        getline(cin, *number_of_copies);
    }
}

// check valid rental fee
bool check_Rental_Fee(string fee){
    int count = 0;
    for(int i = 0;i < fee.length(); i++){
        if(!((fee[i] >= '0') && (fee[i] <= '9'))) {
            if(fee[i] == '.') count++;
            else return false;
            if(count == 2) return false;
        }


    }
    return true;
}

// process for checking entered rental fee
void checkRentalFeeEntered(string *fee) {
    while (!check_Rental_Fee(*fee)) {
        cout << "Wrong rental fee format.\n";
        cout << "Your input must be an integer (eg: 1, 2, 3,...) or double (eg: 1.1, 2.1, 3.2, ...).\n";
        cout << "Re-enter rental fee: ";
        fflush(stdin);
        getline(cin, *fee);
    }
}


// check valid loan type
bool checkLoanType(string loan_type) {
    if ((loan_type.length() != 5) && (loan_type.length() != 6)) {
        return false;
    }

    // if string length == 5 -> check 2-day format
    if (loan_type.length() == 5) {
        // check the first character must be 2
        if (loan_type[0] != '2') return false;

        // check the next character must be -
        if (loan_type[1] != '-') return false;

        // check the word must be day
        string check_word = stringCopy(loan_type, 2, loan_type.length());
        if (check_word.compare("day") != 0) return false;
    }else { // check 1-week format
        // check the first character must be 1
        if (loan_type[0] != '1') return false;

        // check the next character must be -
        if (loan_type[1] != '-') return false;

        // check the word must be week
        string check_word = stringCopy(loan_type, 2, loan_type.length());
        if (check_word.compare("week") != 0) return false;
    }
    return true;
}

void checkValidLoanTypeEntered(string *loan_type) {
    while (!checkLoanType(*loan_type)) {
        cout << "Wrong loan type format.\n";
        cout << "Your input muse be" <<  " 2-day" << " or " << "1-week" << " only.\n";
        cout << "Re-enter loan type: ";
        fflush(stdin);
        getline(cin, *loan_type);
    }
}

// check valid rental type
bool checkValidRentalType(string rental_type) {
    // create a type array for comparing
    string Type[3] = { "Record", "DVD", "Game"};
    // loop through the type loop if the rental type is matched
    for (int i = 0; i < 3; i++) {
        if (rental_type.compare(Type[i]) == 0) return true;
    }
    return false;
}

// process to check the entered rental type
void checkValidRentalTypeEntered(string *rental_type) {
    while (!checkValidRentalType(*rental_type)) {
        cout << "Wrong rental type format.\n";
        cout << "Your input must be " << "Record, " << "DVD or " << "Game" << " only.\n";
        cout << "Re-enter rental type format: ";
        fflush(stdin);
        getline(cin, *rental_type);
    }
}

// check valid genre
bool checkValidGenre(string genre) {
    string Type[4] = {"Comedy", "Horror", "Drama", "Action"};
    // loop from the first to the last of type array
    for (int i = 0; i < 4; i++) {
        if (genre.compare(Type[i]) == 0) return true;
    }
    return false;
}

// process to check the entered genre
void checkValidGenreEntered(string *genre) {
    while (!checkValidGenre(*genre)) {
        cout << "Wrong genre format.\n";
        cout << "Your input muse be " << "Comedy, " << "Horror, " << "Drama or " << "Action " << "only.\n";
        cout << "Re-enter genre: ";
        fflush(stdin);
        getline(cin, *genre);
    }
}

// check correct field format for item
bool checkItemFieldFormat(int status, string value, string file_name) {
    bool checking_result;
    switch (status) {
        case 1: // check id format
            checking_result = checkValidItemId(value);
            if (!checking_result) cout << "Wrong item id format in " << file_name << " file.\n";
            break;
        case 2: // check title format
            checking_result = checkValidTitle(value);
            if (!checking_result) cout << "Wrong title format in " << file_name << " file.\n";
            break;
        case 3: // check valid rental type format
            checking_result = checkValidRentalType(value);
            if (!checking_result) cout << "Wrong rental type format in " << file_name << " file.\n";
            break;
        case 4: // check valid loan type format
            checking_result = checkLoanType(value);
            if (!checking_result) cout << "Wrong loan type format in " << file_name << " file.\n";
            break;
        case 5: // check valid number of copies
            checking_result = checkValidNumberOfCopies(value);
            if (!checking_result) cout << "Wrong number of copies format in " << file_name << " file.\n";
            break;
        case 6: // check valid rental fee format
            checking_result = check_Rental_Fee(value);
            if (!checking_result) cout << "Wrong rental fee format in " << file_name << " file.\n";
            break;
        default: // check Genre format if has*
            checking_result = checkValidGenre(value);
            if (!checking_result) cout << "Wrong genre type format in " << file_name << " file.\n";
            break;
    }
    return checking_result;
}

bool checkCustomerFieldFormat(int status, string value, string file_name) {
    bool checking_result;
    switch (status) {
        case 1: // check Id format
            checking_result = checkValidUserId(value);
            if (!checking_result) cout << "Wrong id format in " << file_name << " file.\n";
            break;
        case 2: // check name format
            checking_result = checkValidTitle(value);
            if (!checking_result) cout << "Wrong name format in " << file_name << " file.\n";
            break;
        case 3: // check address format
            checking_result = checkValidTitle(value);
            if (!checking_result) cout << "Wrong address format in " << file_name << " file.\n";
            break;
        case 4: // check phone number format
            checking_result = checkValidPhoneNum(value);
            if (!checking_result) cout << "Wrong phone number format in " << file_name << " file.\n";
            break;
        case 5: // check rentals format
            checking_result = checkValidNumberOfCopies(value); // use same method for checking number of copies
            if (!checking_result) cout << "Wrong rentals format in " << file_name << " file.\n";
            break;
        case 6: // check rank format   
            checking_result = checkValidRank(value);
            if (!checking_result) cout << "Wrong rank format in " << file_name << " file.\n";
            break;
        default: // checking rental id format
            checking_result = checkValidItemId(value);
            if (!checking_result) cout << "Wrong item id format in " << file_name << " file.\n";
            break;
    }

    return checking_result;
}

void announceItemMissingField(int status, string file_name) {
    switch (status) {
        case 1:
            cout << "Miss item id";
            break;
        case 2:
            cout << "Miss Title";
            break;
        case 3:
            cout << "Miss rental type";
            break;
        case 4:
            cout << "Miss loan type";
            break;
        case 5:
            cout << "Miss number_of_copies";
            break;
        case 6:
            cout << "Miss rental fee";
        default:
            cout << "Miss genre";
    }
    cout << " in " << file_name << " file.\n";
}

void announceCustomerMissingField(int status, string file_name) {
    switch (status) {
        case 1:
            cout << "Miss customer id";
            break;
        case 2:
            cout << "Miss customer name";
            break;
        case 3:
            cout << "Miss customer address";
            break;
        case 4:
            cout << "Miss customer phone number";
            break;
        case 5:
            cout << "Miss customer rentals";
            break;
        case 6:
            cout << "Miss customer rank";
            // no default
    }
    cout << " in " << file_name << " file.\n";
}

bool checkCharactersInString(string value) {
    // check if in that string if there is no character or digit => missing that field
    for (int i = 0; i < value.length(); i++) {
        if (value[i] != ' ') return true;
    }
    return false;
}

bool extract_file(string file_name, ItemList *items) {
    // open file as binary 
    ifstream op_file(file_name, ios::in | ios::binary);

    // check if the file is opened
    if (!op_file) {
        cerr << "Error to open file " << file_name << endl;
        
        return false;
    }

    // create a char variable to get char from the file
    char ch;

    // create string to store the field
    char word[50] = {'\0'};

    // create a status variable to access the suitable property of Item
    int status = 1; // default pointing to the item id
    int node_number = 1; // the order of customer
    // count is the order of current character in word string
    int count = 0;
    // get the first character of the file for checking
    op_file.get(ch);
    // items->insertNewNodeToBack();
    while (!op_file.eof()) {
        if ((ch == ',') || (ch == '\n')) {
            // when the ch reach the , or \n which mean it finished to store value from 1 field
            word[count] = '\0'; // close by NULL character

            // while storing, it should contain whitespace at the end, so this step is to elimiate the space at the end
            for (int i = count; i >= 0; i--) {
                // if it reach the character => assign \0 at the end
                if (((word[i] >= '0') && (word[i] <= '9')) || ((word[i] >= 'a') && (word[i] <= 'z'))) {
                    word[i+1] = '\0';
                    break;
                }
            }
            // check if the status is 1 and the word is not have any character=> missing line
            if (status == 1) {
                if (!checkCharactersInString(string(word))) {
                    cout << "Missing line in file" << endl;
                    return false;
                }else if (word[0] == '\n') {
                    cout << "Missing line in file" << endl;
                    return false;
                }
            }

            // check if the string are field ?
            if (!checkCharactersInString(string(word))) {
                announceItemMissingField(status, file_name);
                return false;
            }

            // if the field has wrong format => quit the program and announce user which field is wrong
            if (!checkItemFieldFormat(status, string(word), file_name)) {
                return false;
            }

            // set the item node by the order of item by node_number and the property by status
            items->setNodeVal(node_number, status, string(word));

            // when 1 property is store, move to next property
            status++;

            // reset the word string
            count = 0;

            // if the last character is \n => start storing new item
            if (ch == '\n') {
                // create new node for storing new item
                items->insertNewNodeToBack();

                // increase the order of item
                node_number++;

                // reset the status to start storing at the first property
                status = 1;
            }

            // store the next character to escape the \n character or ','
            op_file.get(ch);

            // check if the next character is ',' => missing that field
            if (ch == ',') {
                announceItemMissingField(status, file_name);
                return false;
            }
        }
        word[count] = ch;
        count++;
        op_file.get(ch);
    }
    // this step use for the last word before the loop was end before the last word is completed
    word[count] = '\0';
    items->setNodeVal(node_number, status, word);
    op_file.close();
    return true;
}

bool extract_file(string file_name, CusList *customers) {
    // open file for reading as binary
    ifstream op_file(file_name, ios::in | ios::binary);

    // check if the file was opened
    if (!op_file) {
        cerr << "error to open " << file_name << endl;
        return -1;
    }

    // create char variable to store character from file
    char ch;

    // create a string to store value from each field in the file
    char word[50] = {'\0'};

    // create a status variable to access the suitable property of Item
    int status = 1; // default pointing to the item id

    // node_customer represent for the order of customer in the list
    int node_number = 0;

    // the position of current character in the word string
    int count = 0;

    // the order of rental item in customer node
    int which_item = 1;

    // to identify if the program is storing the first customer => store to the head
    // otherwise, create a new node for storing customer
    int line = 1;

    // get the fist character in the file
    op_file.get(ch);
    while (!op_file.eof()) {
        // when the program reach the \n or , => finished one field
        if ((ch == ',') || (ch == '\n')) {
            // ch == 'C' mean it reach new customer
            if (word[0] == 'C') {
                status = 1;
                // check if there is any customer was fully field -> varify the number of rental item
                if (node_number > 1) {
                    // varify rentals
                    customers->setCusItemRented(node_number, customers->getCusItemRented(node_number));
                }
                // if one customer was field => increase to next customer
                node_number++;

                // reset the order of rental item of customer
                which_item = 1;
                // if the program is pointing to the first customer => no need to create a space for next customer
                if (line == 1) {
                    line++;
                }else {
                    // create a space for storing next customer data
                    customers->insertNewNodeToBack();
                }
            }
            word[count] = '\0';

            // this step to eliminate the \n character at the end of last word
            for (int i = count; i >= 0; i--) {
                // if it reach the character => assign \0 at the end
                if (((word[i] >= '0') && (word[i] <= '9')) || ((word[i] >= 'a') && (word[i] <= 'z')) || (word[i] == 'P')) {
                    word[i+1] = '\0';
                    break;
                }
            }

            // check if the status is 1 and the word is not have any character=> missing line
            if (status == 1) {
                if (!checkCharactersInString(string(word))) {
                    cout << "Missing line in file" << endl;
                    return false;
                }else if (word[0] == '\n') {
                    cout << "Missing line in file" << endl;
                    return false;
                }
            }

            // check the feild of customer
            if (!checkCharactersInString(string(word))) {
                // when the status equal 7 => the program is in storing rental item id, so if the status is 7 and no character in the string => missing line
                if (status < 7) announceCustomerMissingField(status, file_name);
                else cout << "Missing line in file " << file_name << endl;
                return false;
            }
            if (!checkCustomerFieldFormat(status, string(word), file_name)) {
                cout << word;
                // check the data in that field if it has correct format
                return false;
            }

            // check if the ch move to the rental item list
            // the item list which contain words which has a letter 'I' at the beginning
            if (status >= 7) {
                // when the status is greater or equal 7 => store the rental item id of customer
                customers->addRentalItem(node_number, string(word));
                which_item++;
                count = 0;
            }else {
                // when the the status is less than 7 => storing the information of customer
                customers->setNodeVal(node_number, status, string(word));
                status++;
                count = 0;
            }
            // get the next character to skip the , or \n
            op_file.get(ch);

            // if the next character is ',' => missing field
            if (ch == ',') {
                announceCustomerMissingField(status, file_name);
                return false;
            }
        }

        // store data by character
        word[count] = ch;
        count++;
        op_file.get(ch);
    }
    // it has a same purpose with the item list extracting
    word[count] = '\0';
    // this checking step means it will check is the last word is an item or a customer rank.
    if (word[0] == 'I') {
        customers->setNodeVal(node_number, status, string(word), which_item);
    }else {
        customers->setNodeVal(node_number, status, string(word));
    }

    // varify the number of rental item for last customer
    customers->setCusItemRented(node_number, customers->getCusItemRented(node_number));
    op_file.close();
    return true;
}

void saveFile(string file_name, ItemList *item) {
    ofstream op_file(file_name);
    // get the maximum items which is the maximum node in the item list
    int max_item = item->getMaxNode();
    // loop until the last item
    for (int i = 1; i <= max_item; i++) {
        // loop to write the item information into item file
        int max_loop;
        // check if that item is Game => loop to 6 element only
        if (item->getRentalType(i).compare("Game") == 0) max_loop = 6;
        else max_loop = 7;
        for (int j = 1; j <= max_loop; j++) {
            // using insertion operator for writting
            switch (j) {
                case 1: // write item id
                    op_file << item->getId(i) << ",";
                    break;
                case 2: // write title
                    op_file << item->getTitle(i) << ",";
                    break;
                case 3: // write rental type
                    op_file << item->getRentalType(i) << ",";
                    break;
                case 4: // write loan type
                    op_file << item->getLoanType(i) << ",";
                    break;
                case 5: // write number of copies
                    op_file << item->getNumberOfCopies(i) << ",";
                    break;
                case 6: // write rental fee
                    // check if this is a last element => print endline
                    if (max_loop == 6) {
                        // check if last item => not print enline
                        if (i == max_item) op_file << item->getRentalFee(i);
                        else op_file << item->getRentalFee(i) << endl;
                    }
                    else op_file << item->getRentalFee(i) << ",";
                    break;
                default: // write genre
                    // check if last item => not print enline
                    if (i == max_item) op_file << item->getGenre(i);
                    else op_file << item->getGenre(i) << endl;
            }
        }
    }
    op_file.close();
}

void saveFile(string file_name, CusList *customer) {
    ofstream op_file(file_name);
    // get the maximum customer which is the maximum node in the customer list
    int max_customer = customer->getMaxNode();
    // loop until the last customer
    for (int i = 1; i <= max_customer; i++) {
        // loop to write the item information into customer file
        int max_loop;
        // loop to 6 information of that customer, then store the rental item
        for (int j = 1; j <= 6; j++) {
            // j represent for status which is same as the extracting step
            switch (j) {
                case 1: // write customer id
                    op_file << customer->getCusId(i) << ",";
                    break;
                case 2: // write customer name
                    op_file << customer->getCusName(i) << ",";
                    break;
                case 3:
                    op_file << customer->getCusAddress(i) << ",";
                    break;
                case 4: // write customer phone number
                    op_file << customer->getCusPhone(i) << ",";
                    break;
                case 5: // write customer rentals
                    op_file << customer->getCusItemRented(i) << ",";
                    break;
                default: // write customer rank
                    // check if that is a last customer in list and does not have any rental item => not printing endline
                    if ((i == customer->getMaxNode()) && (customer->getCusItemRented(i) == 0)) op_file << customer->getCusRank(i);
                    else op_file << customer->getCusRank(i) << endl;
            }
        }
        // store the rental item
        // loop through the rental item list of customer
        for (int z = 1; z <= customer->getNumberOfRentalItem(i); z++) {
            // check if that is last item of last customer => not printing endline
            if ((i == customer->getMaxNode()) && (z == customer->getNumberOfRentalItem(i))) {
                op_file << customer->getCusRentalItem(i, z);
            }else {
                op_file << customer->getCusRentalItem(i, z) << endl;
            }
        }
    }
    op_file.close();
}
// automatically when the customer rent an item they would rent at least 1 item
bool rentItem(CusList *customers, ItemList *items, int which_customer, string item_id) {
    // if the guest account => the program need to check
    if (customers->getCusRank(which_customer).compare("Guest") == 0) {
        // the the number of rental items they have rented
        if (!(customers->getCusItemRented(which_customer) < 2)) {
            cout << "You are a Guest member, so you can not borrow over 2 Video items." << endl;
            return false;
        // check the type of rental they rent => if 2-day video => can not borrow
        }else if (items->getLoanType(items->findId(item_id)).compare("2-day") == 0) {
            cout << "You are a Guest Member, so you can not borrow 2-day video.\n";
            return false;
        }
    }

    // if they are available to borrow => check if the item in stock
    if (items->checkAvailable(item_id)) {
        // increase the number of rental items in their list
        customers->increaseItemRented(which_customer);

        // add that item id to customer rental item list
        customers->addRentalItem(which_customer, item_id);

        // if they can borrow => decrease the number of copies of that items
        items->decreaseNumberOfCopies(item_id);
    }else {
        // announce them that their item is out of stock
        cout << "Item " << item_id << "is out of stock." << endl;
        return false;
    }
    return true;
}

// the parameter for the returning is the same with the rentItem
void returnItem(CusList *customers, ItemList *items, int which_customer, string item_id) {
    // delete item id in their rental item list
    customers->deleteRentalItem(which_customer, item_id);

    // this step use for promote customer
    if ((customers->getCusRank(which_customer).compare("Guest") == 0) || (customers->getCusRank(which_customer).compare("Regular")) == 0) {
        customers->increaseItemReturned(which_customer);
    }else {
        customers->increaseItemReturned(which_customer);
        customers->setRewardPoint(which_customer, customers->getItemReturned(which_customer));
    }
    customers->decreaseItemRented(which_customer);
    items->increaseNumberOfCopies(item_id);
}

bool promoteCustomer(CusList *customers, int which_customer) {
    if (customers->getCusRank(which_customer).compare("Guest") == 0) {
        // up to regular
        // check if they have enough condition
        if (customers->getItemReturned(which_customer) >= 3) {
            // upgrade their rank
            customers->setCusRank(which_customer, "Regular");
            // subtract their returned item
            customers->isPromoted(which_customer);
            return true;
        }
    }else if (customers->getCusRank(which_customer).compare("Regular") == 0) {
        if (customers->getItemReturned(which_customer) >= 3) {
            // upgrade their rank
            customers->setCusRank(which_customer, "VIP");
            // subtract their returned item
            customers->isPromoted(which_customer);
            return true;
        }
    }
    return false;
}

// check if the input has character
bool checkChar(string input) {
    // check if the user enter a digit input, however if it contains character => avoid the failure of stoi
    for (int i = 0; i < input.length(); i++) {
        if (!((input[i] >= '0') && (input[i] <= '9'))) {
            return true;
        }
    }
    return false;
}

void askUserEnterInRange(int min, int max, string *user_input, int which_layout) {
    // if the main layout => check Exit input, otherwise, check in range only
    if (which_layout == 0) {
        // if the input is a string => check exit
        // or check for options
        bool isChar = checkChar(*user_input);
        bool condition = (isChar) ? (!(user_input->compare("Exit") == 0)) : (!((stoi(*user_input) >= min) && (stoi(*user_input) <= max)));
        while (condition) {
            if (checkChar(*user_input)) {
                cout << "Wrong input format.\n";
                cout << "Re-enter your option: ";
                fflush(stdin);
                getline(cin, *user_input);
            }else {
                cout << "Wrong input format. You must enter from " << min << " to " << max << ".\n";
                cout << "Re-enter your option: ";
                fflush(stdin);
                getline(cin, *user_input);
            }
            condition = (checkChar(*user_input)) ? (!(user_input->compare("Exit") == 0)) : (!((stoi(*user_input) >= min) && (stoi(*user_input) <= max)));
        }

    }else {
        // ask user to enter an integer
        while (checkChar(*user_input)) {
            cout << "Wrong format.\n";
            cout << "Enter option from " << min << " to " << max << ": ";
            fflush(stdin);
            getline(cin, *user_input);
        }
        while (!((stoi(*user_input) >= min) && (stoi(*user_input) <= max))) {
            cout << "Wrong input format. You must enter from " << min << " to " << max << ".\n";
            cout << "Re-enter your option: ";
            fflush(stdin);
            getline(cin, *user_input);
            // recheck the format
            while (checkChar(*user_input)) {
                cout << "Wrong format.\n";
                cout << "Enter option from " << min << " to " << max << ": ";
                fflush(stdin);
                getline(cin, *user_input);
            }
        }
    }
}
void codeUI(CusList *customers, ItemList *items) {
    string user_input = " ";
    int layout = 0; // 0 show main layout
    // the program will convert the user input to lower case
    while (user_input.compare("Exit") != 0) {
        switch (layout) {
            case 0:
                cout << "Welcome to Genie’s video store" << endl;
                cout << "Enter an option below." << endl;
                cout << "1. Add a new item, update or delete an existing item" << endl;
                cout << "2. Add new customer or update an existing customer" << endl;
                cout << "3. Promote an existing customer" << endl;
                cout << "4. Rent an item" << endl;
                cout << "5. Return an item" << endl;
                cout << "6. Display all items" << endl;
                cout << "7. Display out-of-stock items" << endl;
                cout << "8. Display all customers" << endl;
                cout << "9. Display group of customers" << endl;
                cout << "10. Search items or customers" << endl;
                cout << "Exit" << endl;
                cout << "Enter an option (eg. 1, 2, 3, ... 10): ";
                fflush(stdin);
                getline(cin, user_input);
                // check valid input from 1 to 10 pr exit
                askUserEnterInRange(1, 10, &user_input, layout);
                if (user_input.compare("Exit") == 0) break;
                // check if option entered in the range from 1 to 10
                layout = stoi(user_input);
                break;
            case 2:
            {
                // create a line between each layout
                cout << "---------------------------------------------------------------" << endl;
                // int case1_option = 0;
                cout << "which option do you want: " << endl;
                cout << "1. Add" << endl;
                cout << "2. Update" << endl;
                cout << "Enter your option: ";
                fflush(stdin);
                getline(cin, user_input);
                // check valid input from 1 to 2
                askUserEnterInRange(1, 2, &user_input, layout);
                cout << "---------------------------------------------------------------" << endl;
                int option = stoi(user_input);
                switch(option) {
                    case 1: {
                        // Enter id
                        customers->insertNewNodeToBack();
                        cout << "Enter id (Cxxx, xxx is a unique code of 3 digits (e.g. 123), eg C001: ";
                        string value;
                        fflush(stdin);
                        getline(cin, value);
                        // chek valid id
                        checkValidIdEntered(customers, &value);

                        // check if the item id is Exit in stock => increase number of copies
                        // Setting customer information
                        customers->setCusId(value);

                        // Enter Name
                        cout << "Enter name: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid name format
                        checkValidNameEntered(&value);
                        customers->setCusName(value);

                        // Enter address
                        cout << "Enter address: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid address format
                        checkValidAddressEntered(&value);
                        customers->setCusAddress(value);

                        //Enter phone
                        cout << "Enter phone: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid customer phone number
                        checkValidPhoneEntered(&value);
                        customers->setCusPhone(value);
                        // Rental items and rank is automatically set
                        // because new customer was not rent any item and actually they are initialized as Guest memeber
                        customers->setCusRank();
                        customers->setCusItemRented();
                        break;
                    }
                    case 2: {
                        string value;
                        customers->displayAllCusId(); // id-sorting
                        cout << "Enter user id to update: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid input
                        checkValidIdEntered(customers, &value, true); // set the update argument to true

                        // find the customer order in the customer list
                        int cus = customers->findId(value);

                        // setting customer information
                        customers->setCusId(cus, value);
                        // Enter Name
                        cout << "Enter name: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid name format
                        checkValidNameEntered(&value);
                        customers->setCusName(cus, value);

                        // Enter address
                        cout << "Enter address: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid address format
                        checkValidAddressEntered(&value);
                        customers->setCusAddress(cus, value);

                        //Enter phone
                        cout << "Enter phone: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid phone number entered
                        checkValidPhoneEntered(&value);
                        customers->setCusPhone(cus, value);
                        break;
                    }
                }
                cout << "---------------------------------------------------------------" << endl;
                layout = 0;
                // Pause for customer to recheck their renting
                cout << "Press Enter to return to main menu";
                fflush(stdin);
                getline(cin, user_input);
                break;
            }
            case 1:
            {
                // create a line between each layout
                cout << "---------------------------------------------------------------" << endl;
                // int case1_option = 0;
                cout << "which option do you want: " << endl;
                cout << "1. Add" << endl;
                cout << "2. Update" << endl;
                cout << "3. Delete" << endl;
                cout << "Enter your option: ";
                fflush(stdin);
                getline(cin, user_input);
                // check valid input from 1 to 3
                askUserEnterInRange(1, 3, &user_input, layout);
                cout << "---------------------------------------------------------------" << endl;
                string value;
                int option = stoi(user_input);
                switch(option) {
                    case 1:
                    {
                        cout << "Enter id (Ixxx-yyyy)\nxxx is a unique code of 3 digits (e.g. 123)\nyyyy s the year the item was published (e.g. 1980)\neg: I001-1980\n";
                        cout << "Enter item id here: ";
                        fflush(stdin);
                        getline(cin, value);

                        // check valid input id
                        checkValidIdEntered(items, &value);

                        if (items->findId(value) != 0) {
                            items->increaseNumberOfCopies(value);
                            cout << "The number of copies of item " << value << " is increased.\n";
                        }else {
                            items->insertNewNodeToBack();
                            // setting item information
                            items->setId(value);

                            cout << "Enter title: ";
                            fflush(stdin);
                            getline(cin, value);
                            // check valid title format
                            checkValidTitleEntered(&value);
                            items->setTitle(value);

                            cout << "Enter rental type: ";
                            string rental_type;
                            fflush(stdin);
                            getline(cin, value);
                            // check valid rental type
                            checkValidRentalTypeEntered(&value);
                            items->setRentalType(value);
                            rental_type = value;

                            cout << "Enter Loan Type: ";
                            fflush(stdin);
                            getline(cin, value);
                            // check valid loan type
                            checkValidLoanTypeEntered(&value);
                            items->setLoanType(value);

                            cout << "Enter number of copies: ";
                            fflush(stdin);
                            getline(cin, value);
                            
                            // check valid number of copies entered
                            checkValidNumberOfCopiesEntered(&value);

                            items->setNumberOfCopies(value);


                            cout << "Enter rental fee: ";
                            fflush(stdin);
                            getline(cin, value);
                            
                            // check valid rental fee format
                            checkRentalFeeEntered(&value);

                            items->setRentalFee(value);

                            // rental status automatically false because new item surely no customer borrowed
                            items->setRentalStatus(false);

                            if (rental_type.compare("Game") != 0) {
                                cout << "Enter genre: ";
                                fflush(stdin);
                                getline(cin, value);
                                // check valid genre
                                checkValidGenreEntered(&value);
                                items->setGenre(value);
                            }
                        }
                        break;
                    }
                    case 2:
                    {
                        items->displayItemBySort(0); // non-sorting display
                        cout << "Enter item id to update: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid item id
                        checkValidIdEntered(items, &value, true); // set update argument to true

                        // find the order of item
                        int item = items->findId(value);

                        // set item information
                        cout << "Enter title: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid title format
                        checkValidTitleEntered(&value);
                        items->setTitle(item, value);

                        cout << "Enter rental type: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid rental type
                        checkValidRentalTypeEntered(&value);
                        items->setRentalType(item, value);

                        cout << "Enter Loan Type: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid loan type
                        checkValidLoanTypeEntered(&value);
                        items->setLoanType(item, value);

                        cout << "Enter number of copies: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid number of copies entered
                        checkValidNumberOfCopiesEntered(&value);
                        items->setNumberOfCopies(item, value);

                        cout << "Enter rental fee: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid rental fee format
                        checkRentalFeeEntered(&value);
                        items->setRentalFee(item, value);

                        items->setRentalStatus(false);

                        if (items->getRentalType(item).compare("Game") != 0) {
                            cout << "Enter genre: ";
                            fflush(stdin);
                            getline(cin, value);
                            // check valid genre
                            checkValidGenreEntered(&value);
                            items->setGenre(item, value);
                        }else {
                            items->setGenre(" ");
                        }

                        // string value;
                        break;

                    }
                    case 3:
                    {
                        items->displayItemBySort(0); // non-sorting display
                        cout << "Enter item id to delete: ";
                        fflush(stdin);
                        getline(cin, value);
                        // check the valid id
                        checkValidIdEntered(items, &value, true); // set the update argument to true

                        // check if any customer are borrowing => can not delete
                        if (customers->isExistItem(value)) {
                            cout << "There are some customers borrowing this item, so you can not delete.\n";
                            break;
                        }
                        items->deleteItem(value);
                    }
                }
                // Pause for customer to recheck their renting
                cout << "Press Enter to return to main menu";
                fflush(stdin);
                getline(cin, value);
                cout << "---------------------------------------------------------------" << endl;
                layout = 0;

                break;
            }
            case 3:
            {
                cout << "---------------------------------------------------------------" << endl;
                string value;
                customers->displayAllCusId();
                cout << "Enter customer id for promoting: ";
                fflush(stdin);
                getline(cin, value);
                checkValidIdEntered(customers, &value, true); // set update argument to true

                // find the order of customer in list
                int cus = customers->findId(value);

                // check if the customer qualified to promote
                bool is_promoted = promoteCustomer(customers, cus);

                // if customer was qualified => notice they arwe promoted
                // otherwise, promote then not promoted
                if (is_promoted) cout << "Customer " << customers->getCusId(cus) << " is promoted to " << customers->getCusRank(cus) << endl;
                else cout << "Customer " << customers->getCusId(cus) << " is not promoted.\n ";
                layout = 0;
                // Pause for customer to recheck their renting
                cout << "Press Enter to return to main menu";
                fflush(stdin);
                getline(cin, value);
                cout << "---------------------------------------------------------------" << endl;
                break;
            }
            case 4:
            {
                string value;
                cout << "There are customer ids in database.\n";
                customers->displayAllCusId();
                cout << "Enter customer id: ";
                fflush(stdin);
                getline(cin, value);
                // check valid customer id
                checkValidIdEntered(customers, &value, true); // set update argument to true

                // find the order of customer in list
                int cus = customers->findId(value);

                // display the available item in stock
                items->displayAvailableItem();

                // ask them to enter the item id to rent
                cout << "Enter item id to rent: ";
                fflush(stdin);
                getline(cin, value);
                // check valid item id
                checkValidIdEntered(items, &value, true); // set update argument to true to check if that id is exist in stock

                // exxecute renting function
                if (rentItem(customers, items, cus, value)) {
                    if (!(customers->getCusRank(cus).compare("VIP") == 0)) {
                        cout << "You have to pay " << items->getPaid(value) << "$" << endl;
                    }else {
                        // if the VIP member has over 100 point => free this items
                        if (customers->getRewardPoint(cus) >= 100) {
                            cout << "You can rent free item\n";
                            customers->decreaseItemReturned(cus, 10); // decrease the number of returned by 10 to update the reward point
                            // update the reward point
                            customers->setRewardPoint(cus, customers->getItemReturned(cus));

                        }else {
                            cout << "You have to pay " << items->getPaid(value) << "$" << endl;
                        }
                    }
                }

                // Pause for customer to recheck their renting
                cout << "Press Enter to return to main menu";
                fflush(stdin);
                getline(cin, value);
                cout << "---------------------------------------------------------------" << endl;
                layout = 0;
                break;
            }
            case 5:
            {
                cout << "---------------------------------------------------------------" << endl;
                string value;
                customers->displayAllCusId();
                cout << "Enter customer id: ";
                fflush(stdin);
                getline(cin, value);

                // check valid user id
                checkValidIdEntered(customers, &value, true); // set the update argument to true to check if the customer id is extisted in customer list

                // find the order of customer in list
                int cus = customers->findId(value);
                // check if the customer does not rent any item
                if (customers->getCusItemRented(cus) == 0) {
                    cout << "No rental item in list\n";
                    layout = 0; // return to main menu
                    cout << "---------------------------------------------------------------" << endl;
                    break;
                }

                cout << "---------------------------------------------------------------" << endl;
                cout << "These are your rental items." << endl;
                // show the list of customers' reantal items
                customers->displayRentalItem(cus);
                // ask them to enter the item id to return
                cout << "Enter returning item id: ";
                fflush(stdin);
                string item;
                getline(cin, item);

                // check valid item id format
                while (!checkValidItemId(item)) {
                    cout << "Wrong item id format\n";
                    cout << "Re-enter item id: ";
                    fflush(stdin);
                    getline(cin, item);
                }

                // check if the customer rented that item
                while (!customers->existRentalItem(item, cus)) {
                    cout << "Can not find this item id in rental list\n";
                    cout << "Re-enter item id: ";
                    fflush(stdin);
                    getline(cin, item);
                    // check valid item id format
                    while (!checkValidItemId(item)) {
                        cout << "Wrong item id format\n";
                        cout << "Re-enter item id: ";
                        fflush(stdin);
                        getline(cin, item);
                    }
                }

                // execute returning function
                returnItem(customers, items, cus, item);
                layout = 0;
                // Pause for customer to recheck their renting
                cout << "Press Enter to return to main menu";
                fflush(stdin);
                getline(cin, value);
                cout << "---------------------------------------------------------------" << endl;
                break;
            }
            case 6:
            {
                cout << "---------------------------------------------------------------" << endl;
                string value;
                cout << "Which type of sort do you prefer.\n";
                cout << "0. non-sorting" << endl;
                cout << "1. sort by id" << endl;
                cout << "2. sort by title" << endl;
                cout << "Enter sorting method: ";
                ItemList *sorted_list = items->copyList();
                fflush(stdin);
                getline(cin, value);
                // check valid input from 0 to 2
                askUserEnterInRange(0, 2, &value, layout);

                // display items information
                sorted_list->displayItemBySort(stoi(value));
                // Pause for customer to recheck their renting
                cout << "Press Enter to return to main menu";
                fflush(stdin);
                getline(cin, value);
                cout << "---------------------------------------------------------------" << endl;
                layout = 0;

                // deconstruct sorted list
                delete(sorted_list);
                break;
            }
            case 7:
            {
                cout << "---------------------------------------------------------------" << endl;
                if (!items->displayOutOfStock()) {
                    cout << "No out of stock item" << endl;
                }
                // Pause for customer to recheck their renting
                string value;
                cout << "Press Enter to return to main menu";
                fflush(stdin);
                getline(cin, value);
                cout << "---------------------------------------------------------------" << endl;
                layout = 0;
                break;
            }
            case 8:
            {
                cout << "---------------------------------------------------------------" << endl;
                string value;
                cout << "Which type of sort do you prefer.\n";
                cout << "0. non-sorting" << endl;
                cout << "1. sort by id" << endl;
                cout << "2. sort by name" << endl;
                cout << "Enter sorting method: ";
                fflush(stdin);
                getline(cin, value);
                // check valid input from 0 to 2
                askUserEnterInRange(0, 2, &value, layout);
                // copying customer list to sorted list to avoid the changing order in the original list
                CusList *sorted_list = customers->copyList();
                sorted_list->displayAllCusInfo(stoi(value));
                // Pause for customer to recheck their renting
                cout << "Press Enter to return to main menu";
                fflush(stdin);
                getline(cin, value);
                cout << "---------------------------------------------------------------" << endl;
                layout = 0;
                // deconstruct sorted list
                delete(sorted_list);
                break;
            }
            case 9:
            {
                cout << "---------------------------------------------------------------" << endl;
                string value;
                cout << "Select the group below\n";
                cout << "1. Guest" << endl;
                cout << "2. Regular" << endl;
                cout << "3. VIP" << endl;
                cout << "Enter the group to display (eg 1, 2, 3): ";
                fflush(stdin);
                getline(cin, value);
                // check valid input from 1 to 3
                askUserEnterInRange(1, 3, &value, layout);
                customers->displayGroupMember(stoi(value));
                layout = 0;
                // Pause for customer to recheck their renting
                cout << "Press Enter to return to main menu";
                fflush(stdin);
                getline(cin, value);
                cout << "---------------------------------------------------------------" << endl;
                break;
            }
            case 10:
            {
                cout << "---------------------------------------------------------------" << endl;
                string value;
                cout << "Select which category to search\n";
                cout << "1. items" << endl;
                cout << "2. customers" << endl;
                cout << "Enter the category (eg: 1, 2): ";
                fflush(stdin);
                getline(cin, value);
                // check valid input from 1 to 2
                askUserEnterInRange(1, 2, &value, layout);
                switch(stoi(value)) {
                    case 1:
                    {
                        string value;
                        cout << "Select type of searching\n";
                        cout << "1. title" << endl;
                        cout << "2. id" << endl;
                        cout << "Enter the type(eg 1, 2): ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid input from 1 to 2
                        askUserEnterInRange(1, 2, &value, layout);
                        string option;
                        if (stoi(value) == 1) {
                            cout << "Enter items title: ";
                            fflush(stdin);
                            getline(cin, option);
                            // check valid title entered
                            checkValidTitleEntered(&option);

                            if (!items->displayItemByTitle(option)) {
                                cout << "Can find title: " << option << endl;
                            }
                        }else {
                            cout << "Enter items id: ";
                            fflush(stdin);
                            getline(cin, option);

                            // check valid item id format
                            checkValidIdEnteredForSearching(items, &option);

                            // display the item information
                            if (!items->displayItemById(option)) {
                                cout << "Can not find item " << option << endl;
                            }
                        }
                        break;
                    }
                    default:
                    {
                        string value;
                        cout << "Select type of searching\n";
                        cout << "1. name" << endl;
                        cout << "2. id" << endl;
                        cout << "Enter the type(eg 1, 2): ";
                        fflush(stdin);
                        getline(cin, value);
                        // check valid input from 1 to 2
                        askUserEnterInRange(1, 2, &value, layout);
                        string option;
                        if (stoi(value) == 1) {
                            cout << "Enter customers name: ";
                            fflush(stdin);
                            getline(cin, option);
                            // check valid name input'
                            checkValidNameEntered(&option);
                            if (!customers->displayCustomerByName(option)) {
                                cout << "Can find customer name: " << option << endl;
                            }
                        }else {
                            cout << "Enter customers id: ";
                            fflush(stdin);
                            getline(cin, option);

                            // check the valid customer id
                            checkValidIdEnteredForSearching(customers, &option);

                            if (!customers->displayCustomerById(option)) {
                                cout << "Can not find customer " << option << endl;
                            }
                        }
                        break;
                    }

                }
                // Pause for customer to recheck their renting
                cout << "Press Enter to return to main menu";
                fflush(stdin);
                getline(cin, value);
                layout = 0;
                cout << "---------------------------------------------------------------" << endl;
                break;
            }
        }
    }
}

void displayGroupMember() {
    cout << endl;
    cout << "ASSIGNMENT 2 GROUP 19" << endl;
    cout << "s3879362, s3879362@rmit.edu.vn, Phuc, Hoang" << endl;
    cout << "s3879366, s3879366@rmit.edu.vn, Long, Pham" << endl;
    cout << "s3741303, s3741303@rmit.edu.vn, Huy, Nguyen" << endl;
    cout << "s3881006, s3881006@rmit.edu.vn, Cuong, Nguyen" << endl;
}











