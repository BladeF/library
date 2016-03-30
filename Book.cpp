#include "Book.h"
using namespace std;

Book::Book() {
    title  = "";
    author = "";
}

Book::Book(string title, string author, string tag) {
    this->title  = title;
    this->author = author;
    tags.push_back(tag);
}
