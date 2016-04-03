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

void Book::setTitle(string title) {
    this->title = title;
}

void Book::setAuthor(string author) {
    this->author = author;
}

void Book::addTag(string tag) {
    tags.push_back(tag);
}
