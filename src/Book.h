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
        //Constructors
        Book();
        Book(std::string, std::string, std::string);
        //Setters and Getters
        std::string              getTitle  () {return title;}
        std::string              getAuthor () {return author;}
        std::vector<std::string> getTags   () {return tags;}
        void                     setTitle  (std::string);
        void                     setAuthor (std::string);
        void                     addTag    (std::string);
        void                     deleteTag (int);
        void                     clearTags () {tags.clear();}

};
#endif
