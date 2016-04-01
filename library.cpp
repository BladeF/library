#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <vector>
#include <cstdlib>
#include <cctype>
#include "Book.h"
using namespace std;

//Function Prototypes
void printMenu ();
int  getCmd    ();
void initLoad  (list<Book> &, vector<string> &);
void showBooks (list<Book> &);

int main(int argc, char** argv) {

    int            cmd;
    list<Book>     library;
    vector<string> tags;

    initLoad(library, tags);
    printMenu();
    cmd = getCmd();

    switch(cmd) {
        case 1:
             showBooks(library);
             break;
    }

    return EXIT_SUCCESS;
}

void printMenu() {
    cout << "##### Welcome to your library! #####" << endl;
    cout << "     Please select your option:     " << endl;
    cout << setw(16) << right << "1"               << "    "
         << setw(16) << left  << "Show All Books"  << endl;
    cout << setw(16) << right << "2"               << "    "
         << setw(16) << left  << "Search Books"    << endl;
    cout << setw(16) << right << "3"               << "    "
         << setw(16) << left  << "Add Book"    << endl;
    cout << setw(16) << right << "4"               << "    "
         << setw(16) << left  << "Show All Tags"    << endl;

}

int getCmd() {
    int cmd;

    while(true) {
        cout << "\n\nPlease select an option number: ";
        cin  >> cmd;

        if(cmd >= 1 && cmd <= 4)
            break;

        cout << "Invalid choice! Please select between 1 and 4" << endl;
    }

    return cmd;
}

void initLoad(list<Book> &bookList, vector<string> &tagVector) {
    ifstream bookData("bookData.txt");
    ifstream tagData("tagData.txt");
    char     bookCont, tagCont;
    string   tagInput, bookTitle, bookAuthor;
    Book     temp;

    // Checks if there is stored data
    if(!bookData) {
        cout << "No previous library data. Continue? (Y or N): ";
        cin  >> bookCont;

        // Gives user a chance to exit and find data is necessary
        if(toupper(bookCont) == 'N') {
            cout << "Now exiting" << endl;
            exit(EXIT_SUCCESS);
        }
    }
    else {
        // If data is present, loads data
        while(!bookData.eof()) {
            getline(bookData, bookTitle);
            getline(bookData, bookAuthor);

            temp.setTitle(bookTitle);
            temp.setAuthor(bookAuthor);
            bookList.push_back(temp);
            bookData.ignore();
        }
    }

    if(!tagData) {
        cout << "No previous tag data. Contiue? (Y or N): ";
        cin  >> tagCont;

        if(toupper(tagCont) == 'N') {
            cout << "Now exiting" << endl;
            exit(EXIT_SUCCESS);
        }
    }
    else {
        while(!tagData.eof()) {
            tagData >> tagInput;
            tagVector.push_back(tagInput);
        }
    }

}
 void showBooks(list<Book> &bookList) {
    for(list<Book>::iterator i = bookList.begin(); i != bookList.end(); i++) {
        cout << i->getTitle() << endl;
        cout << i->getAuthor() << endl;
    }
}
