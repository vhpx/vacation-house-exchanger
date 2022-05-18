#include <iostream>
#include <string>
#include <fstream>
#include "optionFile.cpp"

using namespace std;
// get database file from the command line
// 1 find is customer file
// 2 file is item file
int main(int argc, const char *argv[]) {
    // if the input argument is not equal to 3
    // quit file
    if (argc != 3) {
        cerr << "You should enter in format ./execute_file " << " <database file 1> " << "<database file 2>" << endl;
        return -1;
    }

    // check correct file and format
    // open the first file and check the first character of it
    ifstream op_file(string(argv[1]), ios::in | ios::binary);
    // check if the file can opened
    if (!op_file) {
        cerr << "Can not open " << argv[1] << "file.\n";
        return -1;
    }

    // get the first character in file to compare
    char ch;
    op_file.get(ch);
    string customers_file;
    string item_file;
    if (ch == 'I') { 
        // assign that file is item database file and other file is customer file
        customers_file = string(argv[2]);
        item_file = string(argv[1]);
    }else if (ch == 'C') {
        // assign that file is customer file and other file is item file
        customers_file = string(argv[1]);
        item_file = string(argv[2]);
    }else {
        // wrong format file => quit the program
        cerr << "Wrong file format" << endl;
    }
    op_file.close();

    // create item and customer list
    ItemList item;
    CusList customer;

    // get data from file and check if the file was opened
    // if it was nor opened => the program will return error and quit immediately
    if (!extract_file(item_file, &item)) {
        return -1;
    }
    if (!extract_file(customers_file, &customer)) {
        return -1;
    }
    
    // present the user interface
    codeUI(&customer, &item);

    // save data back to the database
    saveFile(item_file, &item);
    saveFile(customers_file, &customer);

    // display group members
    displayGroupMember();
    return 0;
}
