/**
 * This is an example implementation of the Iterator pattern. This pattern simply allows the user to traverse a given container without exposing it's underlying
 * structure. It's used via iterators with a specific behaviour in mind - like filtering specific components by their members.
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include <vector>

// Collection item
struct Book
{
    std::string genere_;
    std::string title_;
    Book(std::string genere, std::string title) : genere_(genere), title_(title) {}
};


// Abstract Iterator
class Iterator
{
    public:
    virtual void goNext() = 0;
    virtual Book* getCurrent() = 0;
    virtual bool isLast() = 0;
    virtual ~Iterator() {}

};
// Concrete Iterator
class LiteratureIterator : public Iterator
{
    private:
    class Bookshelf* collection_;
    int currentIndex_;

    public:
    LiteratureIterator(class Bookshelf* collection) : collection_(collection), currentIndex_(0) {}
    void goNext() override;
    Book* getCurrent() override;
    bool isLast() override; 
};

// Concrete iterator
class GeneralIterator : public Iterator
{
    private:
    Bookshelf* collection_;
    int currentIndex_;
    public:
    GeneralIterator(Bookshelf* collection) : collection_(collection), currentIndex_(0) {}
    void goNext() override;
    Book* getCurrent() override;
    bool isLast() override;
};

// Abstract collection
class Bookshelf
{
    public:
    virtual Iterator* createLiteratureIterator() = 0;
    virtual Iterator* createGeneralIterator() = 0;
    virtual Book* getBookById(size_t id) = 0;
    virtual int getCollectionSize() = 0;
    virtual ~Bookshelf() {}
};
// Concrete Collection
class GeneralBookShelf : public Bookshelf
{
    private:
    std::vector<Book*> shelfContent_;
    public:
    GeneralBookShelf(std::vector<Book*> initialBook) : shelfContent_(initialBook) {}
    Iterator* createLiteratureIterator() override { return new LiteratureIterator(this); }
    Iterator* createGeneralIterator() override { return new GeneralIterator(this); }
    Book* getBookById(size_t id) override
    {
        if(id >= shelfContent_.size())
        {
            return nullptr;
        }
        return shelfContent_[id];
    }
    int getCollectionSize() override { return this->shelfContent_.size(); }
};

// Concrete iterator impl
void LiteratureIterator::goNext()
{
    ++currentIndex_;
}

Book* LiteratureIterator::getCurrent()
{
    if(isLast()) { return nullptr; }
    Book* currentBook = this->collection_->getBookById(this->currentIndex_);
    if(currentBook)
    {
        if(currentBook->genere_ == "Literature")
        {
            return currentBook;
        }
        else
        {
            this->goNext();
        }
    }
    return nullptr;
}

bool LiteratureIterator::isLast()
{
    return this->currentIndex_ == this->collection_ ->getCollectionSize();
}

void GeneralIterator::goNext()
{
    ++currentIndex_;
}

bool GeneralIterator::isLast()
{
    return this->currentIndex_ >= this->collection_ ->getCollectionSize();
}

Book* GeneralIterator::getCurrent()
{
    if(!isLast()) { return this->collection_->getBookById(this->currentIndex_); }
    return nullptr;
}

// Client Code
int main()
{
    // Decleare all of the items here
    std::cout << "Declearing items" << std::endl;
    std::vector<Book*> initBooks = { 
        new Book("Fantasy", "Lord of the Things"),
        new Book("Literature", "A men of spite"),
        new Book("Literature", "Amaizing Paradise"),
        new Book("Philosophy", "Holy City"),
        new Book("Biography", "That's me: Pilon Tusk")};
    
    // Decleare collection
    std::cout << "Declearing collection" << std::endl;
    Bookshelf* initCollection = new GeneralBookShelf(initBooks);

    // Decleare iterator
    std::cout << "Declearing Iterator" << std::endl;
    Iterator* litIt = initCollection->createLiteratureIterator();
    Iterator* genIt = initCollection->createGeneralIterator();

    // Iterate with first iterator
    std::cout << "Iteraiting first iterator" << std::endl;
    while(!litIt->isLast())
    {
        Book* currentBook = litIt->getCurrent();
        if(currentBook)
        {
            std::cout << "Book Title: " << currentBook->title_ << " Genere: " << currentBook->genere_ << std::endl;
            litIt->goNext();
        }
    }

    // Iterate with second iterator
    std::cout << "Iteraiting second iterator" << std::endl;
    while(!genIt->isLast())
    {
        Book* currentBook = genIt->getCurrent();
        if(currentBook)
        {
            std::cout << "Book Title: \"" << currentBook->title_ << "\" Genere: " << currentBook->genere_ << std::endl;
            genIt->goNext();
        }
    }

    // Cleanup
    std::cout << "Cleanup" << std::endl;
    delete genIt;
    delete litIt;
    delete initCollection;
    for(auto item : initBooks) { delete item; }
}