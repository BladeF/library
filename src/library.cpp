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

// Function Prototypes
void printMenu      ();
int  getCmd         ();
void initLoad       (list<Book> &, vector<string> &);
void clearScreen    ();
void pauseScreen    ();
void showTags       (vector<string> &);
void deleteTag      (list<Book> &, vector<string> &);
void showBooks      (list<Book> &);
void addBook        (list<Book> &, vector<string> &);
void deleteBook     (list<Book> &);
void search         (list<Book> &, vector<string> &);
void searchByTag    (list<Book> &, vector<string> &);
void searchByTitle  (list<Book> &);
void searchByAuthor (list<Book> &);
void exitLib        (list<Book> &, vector<string> &);

// Main Function
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
                 clearScreen();
                 search(library, tags);
                 break;
            case 3:
                 clearScreen();
                 addBook(library, tags);
                 break;
            case 4:
                 clearScreen();
                 deleteBook(library);
                 break;
            case 5:
                 clearScreen();
                 showTags(tags);
                 break;
            case 6:
                 clearScreen();
                 deleteTag(library, tags);
                 break;
            case 0:
                 clearScreen();
                 exitLib(library, tags);
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
         << setw(16) << left  << "Delete Book"     << endl;
    cout << setw(16) << right << "5"               << "    "
         << setw(16) << left  << "Show All Tags"   << endl;
    cout << setw(16) << right << "6"               << "    "
         << setw(16) << left  << "Delete Tag"     << endl;
    cout << setw(16) << right << "0"               << "    "
         << setw(16) << left  << "Quit"            << endl;

}

int getCmd() {
    int cmd;

    while(true) {
        cout << "\n\nPlease select an option number: ";
        // Gets the first character from the stream
        cmd = cin.get();
        // Converts the ASCII value to the true cmd number
        cmd -= '0';
        // Ignores any extra characters entered between cmd and newline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Puts newline back in stream, as later code depends on it
        cin.putback('\n');

        if(cmd >= 0 && cmd <= 6)
            break;

        cout << "Invalid choice! Please select between 0 and 6" << endl;
    }

    return cmd;
}

void initLoad(list<Book> &bookList, vector<string> &tagVector) {
    ifstream bookData("data/bookData.txt");
    ifstream tagData ("data/tagData.txt");
    char     bookCont, tagCont;
    string   tagInput, bookTitle, bookAuthor, bookTag;
    Book     temp;

    // Preps screen for running
    clearScreen();

    // Checks if there is stored data
    if(!bookData) {
        cout << "No previous library data. Continue? (Y or N): ";
        cin  >> bookCont;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(toupper(tagCont) == 'N') {
            cout << "Now exiting" << endl;
            exit(EXIT_SUCCESS);
        }
    }
    else {
        while(!tagData.eof()) {
            getline(tagData, tagInput);
            tagVector.push_back(tagInput);
        }
    }

}

void clearScreen() {
    cout << string(100, '\n');
}

void pauseScreen() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void showTags(vector<string> &tagVector) {
    cout << "Tags in Library" << endl
         << "----------------" << endl;

    for(int i = 0; i < tagVector.size(); i++) {
        cout << tagVector[i] << endl;
    }

    cout << endl << endl; // Helps make formatting look better
}

void deleteTag(list<Book> &bookList, vector<string> &tagVector) {
    char                     cont;
    int                      index       = 0,
                             tagInput;
    string                   delTag;
    vector<string>           tags;
    vector<string>::iterator it          = tagVector.begin();

    if(tagVector.size() == 0) {
        cout << "No tags. Returning to main menu." << endl;
        return;
    }

    cout << "Tags in Library" << endl
         << "----------------" << endl;

    for(int i = 0; i < tagVector.size(); i++) {
        cout << (i + 1) << "\t" << tagVector[i] << endl;
    }

    cout << "\n\nEnter number of tag you wish to delete: ";
    cin  >> tagInput;
    tagInput--; // Adjust the displayed number to match the index
    cout << "Delete " << tagVector[tagInput] << "? (Y or N): ";
    cin  >> cont;

    if(tolower(cont) == 'n') {
        cout << "Returning to main menu" << endl;
        return;
    }

    delTag = tagVector[tagInput];
    advance(it, tagInput);
    tagVector.erase(it);

    for(list<Book>::iterator bookIt = bookList.begin(); bookIt != bookList.end(); bookIt++) {
        tags       = bookIt->getTags();

        for(int i = 0; i < tags.size(); i++) {
            if(tags[i].compare(delTag) == 0) {
                bookIt->deleteTag(i);
            }
        }// end tags for
    }// end book for

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

    cout << endl << endl; // Helps formatting look better
}

void addBook(list<Book> &bookList, vector<string> &tagVector) {
    bool   found = false;
    string title, author, tag = "";
    Book   temp;

    cout << "Enter title in quote (\"Title\"): ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter author: ";
    getline(cin, author);
    cout << "Enter new or existing tag. If no tag desired, just enter Q." << endl;
    cout << "Existing tags:" << endl;
    for(int k = 0; k < tagVector.size(); k++) {
        cout << "\t" << tagVector[k] << endl;
    }

    // Loop for processing multiple tags
    while(true) {
        cout << "Enter tag or Q to quit: ";

        getline(cin, tag);
        for(int i = 0; i < tag.length(); i++) {
            tag[i] = tolower(tag[i]);
        }

        if(tag.compare("q") == 0)
            break;

        for(int k = 0; k < tagVector.size(); k++) {
            if(tagVector[k].compare(tag) == 0)
                found = true;
        }

        temp.addTag(tag);

        if(!found)
            tagVector.push_back(tag);

        found = false;
    }

    cin.putback('\n'); // Pause function relies on newline

    temp.setTitle(title);
    temp.setAuthor(author);
    bookList.push_back(temp);
}

void deleteBook(list<Book> &bookList) {
    int                   counter = 1,
                          input;
    char                  confirm;
    list<Book>::iterator del     = bookList.begin();

    if(bookList.size() == 0) {
        cout << "No books in library. Returning to main menu." << endl;
        return;
    }

    for(list<Book>::iterator i = bookList.begin(); i != bookList.end(); i++) {
        cout << counter      << endl
             << "\tTitle:  " << i->getTitle()  << endl
             << "\tAuthor: " << i->getAuthor() << endl
             << "\t-----"    << endl;

        counter++;
    }

    cout << "Enter the number of the book to delete: ";
    cin  >> input;

    advance(del, (input - 1)); // Zero based, so need to subtract 1 to reach true node

    cout << endl
         << "\tTitle:  " << del->getTitle()  << endl
         << "\tAuthor: " << del->getAuthor() << endl;

    cout << "Delete this book? (Y or N): ";
    cin  >> confirm;

    if(toupper(confirm) == 'Y') {
        bookList.erase(del);
        cout << "Book successfully erased" << endl;
    }
    else
        cout << "Returning to main menu" << endl;
}

void search(list<Book> &bookList, vector<string> &tagVector) {
    int input;

    cout << "Search by book tag, title, or author?" << endl
         << "\t1\ttag"                                << endl
         << "\t2\ttitle"                              << endl
         << "\t3\tauthor"                             << endl
         << endl << endl
         << "Enter number of choice: ";
    cin  >> input;

    switch(input) {
        case 1:
             clearScreen();
             searchByTag(bookList, tagVector);
             break;
        case 2:
             clearScreen();
             searchByTitle(bookList);
             break;
        case 3:
             clearScreen();
             searchByAuthor(bookList);
             break;
        default:
             cout << "Invalid choice. Returning to main menu." << endl;
    }
}

void searchByTag(list<Book> &bookList, vector<string> &tagVector) {
    bool           found = false;
    char           cont;
    int            tagInput;
    string         tag;
    vector<string> tags;

    do {
        clearScreen();
        cout << "Tags in Library" << endl
             << "----------------" << endl;

        for(int i = 0; i < tagVector.size(); i++) {
            cout << (i + 1) << "\t" << tagVector[i] << endl;
        }

        cout << "\n\nEnter number of tag you wish to search: ";
        cin  >> tagInput;
        tagInput--;
        tag = tagVector[tagInput];

        for(list<Book>::iterator i = bookList.begin(); i != bookList.end(); i++) {
            tags = i->getTags();

            for(int k = 0; k < tags.size(); k++) {
                if(tag.compare(tags[k]) == 0) {
                    cout << "Title:  " << i->getTitle()  << endl
                         << "Author: " << i->getAuthor() << endl
                         << "-----"    << endl;

                    found = true;
                }
            }

            tags.clear();
        }// end for

        if(!found)
            cout << "\nNo results found...\n";

        cout << "\nSearch again? (Y or N): ";
        cin  >> cont;
        cont = tolower(cont);
    } while(cont == 'y');
}

void searchByTitle(list<Book> &bookList) {
    bool   found = false;
    char   cont;
    string searchInput, bookTitle;

    do {
        clearScreen();
        cout << "Enter title to search: ";
        cin  >> searchInput;
        cout << endl;

        for(int k = 0; k < searchInput.length(); k++)
            searchInput[k] = tolower(searchInput[k]);

        for(list<Book>::iterator i = bookList.begin(); i != bookList.end(); i++) {
            bookTitle = i->getTitle();

            for(int c = 0; c < bookTitle.length(); c++)
                bookTitle[c] = tolower(bookTitle[c]);



            if(bookTitle.find(searchInput) != string::npos) {
                cout << "Title:  " << i->getTitle()  << endl
                     << "Author: " << i->getAuthor() << endl
                     << "-----"    << endl;

                found = true;
            }
        }// end for

        if(!found)
            cout << "\nNo results found...\n";

        cout << "\nSearch again? (Y or N): ";
        cin  >> cont;
        cont = tolower(cont);
    } while(cont == 'y');

}

void searchByAuthor(list<Book> &bookList) {
    bool   found = false;
    char   cont;
    string searchInput, bookAuthor;

    do {
        clearScreen();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter author name: ";
        getline(cin, searchInput);
        for(int c = 0; c < searchInput.length(); c++)
            searchInput[c] = tolower(searchInput[c]);

        for(list<Book>::iterator it = bookList.begin(); it != bookList.end(); it++) {
            bookAuthor = it->getAuthor();
            for(int i = 0; i < bookAuthor.length(); i++)
                bookAuthor[i] = tolower(bookAuthor[i]);

            if(bookAuthor.find(searchInput) != string::npos) {
                cout << "Title:  " << it->getTitle()  << endl
                     << "Author: " << it->getAuthor() << endl
                     << "-----"    << endl;

                found = true;
            }
        }// end for

        if(!found)
            cout << "\nNo results found...\n";

        cout << "\nSearch again? (Y or N): ";
        cin  >> cont;
        cont = tolower(cont);
    } while(cont == 'y');
}

void exitLib(list<Book> &bookList, vector<string> &tagVector) {
    ofstream       bookData("data/bookOutput.txt"),
                   tagData ("data/tagOutput.txt");
    vector<string> tags;

    for(list<Book>::iterator i = bookList.begin(); i != bookList.end(); i++) {
        bookData << i->getTitle()  << endl
                 << i->getAuthor() << endl;

        tags = i->getTags();
        for(int v = 0; v != tags.size(); v++) {
            bookData << tags[v] << endl;
        }

        bookData << ":" << endl;
    }

    for(int k = 0; k < tagVector.size(); k++) {
        if((k + 1) != tagVector.size())
            tagData << tagVector[k] << endl;
        else
            tagData << tagVector[k];
    }
}
