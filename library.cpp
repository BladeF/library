#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "Book.h"
using namespace std;

//Function Prototypes
void printMenu();

int main(int argc, char** argv) {

    printMenu();

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
