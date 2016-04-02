#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <list>
#include <vector>
#include <cstdlib>
#include <cctype>
#include "Book.h"
using namespace std;

//Function Prototypes
void printMenu   ();
int  getCmd      ();
void initLoad    (list<Book> &, vector<string> &);
void showBooks   (list<Book> &);
void clearScreen ();
void pauseScreen ();
void showTags    (vector<string> &);
void addBook     (list<Book> &);

int main(int argc, char** argv) {

    char           cont;
    int            cmd;
    list<Book>     library;
    vector<string> tags;

    initLoad(library, tags);

    do {
        clearScreen();
        printMenu();
        cmd = getCmd();

        switch(cmd) {
            case 1:
                 clearScreen();
                 showBooks(library);
                 break;
            case 2:
            case 3:
                 clearScreen();
                 addBook(library);
                 break;
            case 4:
                 clearScreen();
                 showTags(tags);
                 break;
            case 0:
                 cout << "Goodbye!" << endl;
                 return EXIT_SUCCESS;
        }

        pauseScreen();
    } while(true);

    return EXIT_FAILURE;
}

void printMenu() {
    cout << "##### Welcome to your library! #####" << endl;
    cout << "     Please select your option:     " << endl;
    cout << setw(16) << right << "1"               << "    "
         << setw(16) << left  << "Show All Books"  << endl;
    cout << setw(16) << right << "2"               << "    "
         << setw(16) << left  << "Search Books"    << endl;
    cout << setw(16) << right << "3"               << "    "
         << setw(16) << left  << "Add Book"        << endl;
    cout << setw(16) << right << "4"               << "    "
         << setw(16) << left  << "Show All Tags"   << endl;
    cout << setw(16) << right << "0"               << "    "
         << setw(16) << left  << "Quit"            << endl;

}

int getCmd() {
    int cmd;

    while(true) {
        cout << "\n\nPlease select an option number: ";
        cin  >> cmd;

        if(cmd >= 0 && cmd <= 4)
            break;

        cout << "Invalid choice! Please select between 1 and 4" << endl;
    }

    return cmd;
}

void initLoad(list<Book> &bookList, vector<string> &tagVector) {
    ifstream bookData("bookData.txt");
    ifstream tagData("tagData.txt");
    char     bookCont, tagCont;
    string   tagInput, bookTitle, bookAuthor, bookTag;
    Book     temp;

    // Preps screen for running
    clearScreen();

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
            temp.clearTags(); // Resets vector for each pass of the loop
            getline(bookData, bookTitle);
            getline(bookData, bookAuthor);
            getline(bookData, bookTag);

            while(bookTag.compare(":") != 0) {
                temp.addTag(bookTag);
                getline(bookData, bookTag);
            }

            temp.setTitle(bookTitle);
            temp.setAuthor(bookAuthor);
            bookList.push_back(temp);
            bookData >> ws; //Removes any trailing whitespace
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
    vector<string> tags;

    cout << "Books in Library" << endl
         << "----------------" << endl;

    for(list<Book>::iterator i = bookList.begin(); i != bookList.end(); i++) {
        cout << "Title:  " << i->getTitle()  << endl;
        cout << "Author: " << i->getAuthor() << endl;
        cout << "Tags:   " << endl;

        tags = i->getTags();
        for(int v = 0; v != tags.size(); v++) {
            cout << "\t" << tags[v] << endl;
        }

        cout << "-----" << endl;
    }
}

void clearScreen() {
    system("clear");
}

void pauseScreen() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void showTags(vector<string> &tagVector) {
    for(int i = 0; i < tagVector.size(); i++) {
        cout << tagVector[i] << endl;
    }
}

void addBook(list<Book> &bookList) {
    Book   temp;
    string title, author;

    cout << "Enter title in quote (\"Title\"): ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter author: ";
    getline(cin, author);
    cin.putback('\n'); // Pause function relies on newline

    temp.setTitle(title);
    temp.setAuthor(author);
    bookList.push_back(temp);
};
