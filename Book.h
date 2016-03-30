#ifndef BOOK_H
#define BOOK_H
#include <vector>
#include <string>

class Book {

    private:
        std::string              title;
        std::string              author;
        std::vector<std::string> tags;
    public:
        Book();
        Book(std::string, std::string, std::string);
        //Setters and Getters
        std::string              getTitle()  {return title;}
        std::string              getAuthor() {return author;}
        std::vector<std::string> getTags()   {return tags;}

};
#endif
