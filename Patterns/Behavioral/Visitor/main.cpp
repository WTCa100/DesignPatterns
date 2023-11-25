/**
 * This is an example implementation of the Visitor design pattern. In this pattern we have 2 classes - a visitor, it's only job is to perform a task in a given object.
 * It's functionality is called from the object itself, thus the it does not need to know what type called it from. A visitor have a method for each
 * possible object that it needs to visit. That way it is easier to extend it's functionality for different methods.
 * @date 2023-11-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <string>
#include <vector>

// Abstract visitor
class GovVisitor
{
    public:
    // A visitor shall have a handle for each object type it will be called from.
    virtual void visitKingdom(class Kingdom* visiting) = 0;
    virtual void visitRepublic(class Republic* visiting) = 0;
    virtual void visitTribe(class Tribe* visiting) = 0;
    virtual ~GovVisitor() {}
};

// Abstract element
class Goverment
{
    protected:
    int rulerAge_;
    std::string name_;
    public:
    // Visitor is called from the object itself so thata the type is always well known for it.
    virtual void accept(GovVisitor* gV) = 0;
    virtual void handleSuccession() = 0;

    Goverment(int rulerAge, std::string blobName) : rulerAge_(rulerAge), name_(blobName) {}

    int getRulerAge() const { return this->rulerAge_; }
    std::string getBlobName() const { return this->name_; }
    void setRulerAge(int ageNew) { this->rulerAge_ = ageNew; }
    virtual ~Goverment() {}
};

// Concrete element
class Kingdom : public Goverment
{
    public:
    Kingdom(int rulerAge, std::string blobName) : Goverment(rulerAge, blobName) {}
    void accept(GovVisitor* gV) override
    {
        gV->visitKingdom(this);
    }
    void handleSuccession() override { std::cout << "King has died! Kingdoms' heir is a new king!" << std::endl; this->rulerAge_ = 35; } 
};

// Concrete element
class Republic : public Goverment
{
    public:
    Republic(int rulerAge, std::string blobName) : Goverment(rulerAge, blobName) {}
    void accept(GovVisitor* gV) override
    {
        gV->visitRepublic(this);
    }
    void handleSuccession() override { std::cout << "The Doge is dead! A new election has started." << std::endl; this->rulerAge_ = 40; }
};

// Concrete element
class Tribe : public Goverment
{
    public:
    Tribe(int rulerAge, std::string blobName) : Goverment(rulerAge, blobName) {}
    void accept(GovVisitor* gV) override
    {
        gV->visitTribe(this);
    }
    void handleSuccession() override { std::cout << "Our Chief has died! The strongest will take the lead now!" << std::endl; this->rulerAge_ = 21; }
};

// Concrete Visitor
class rulerKill : public GovVisitor
{
    void visitKingdom(Kingdom* visiting) override
    {
        std::cout << "Visiting kingdom: " << visiting->getBlobName() << " Ruler age: " <<  visiting->getRulerAge() << std::endl;
        if(visiting->getRulerAge() > 65)
        {
            visiting->handleSuccession();
        }
        else
        {
            std::cout << "Not killing king in " << visiting->getBlobName() << std::endl;
        }
    }
    void visitRepublic(Republic* visiting) override
    {
        std::cout << "Visiting republic/merchent republic: " << visiting->getBlobName() << " Ruler age: " << visiting->getRulerAge() << std::endl;
        if(visiting->getRulerAge() > 70)
        {
            visiting->handleSuccession();
        }
        else
        {
            std::cout << "Not killing doge in " << visiting->getBlobName() << std::endl;
        }
    }
    void visitTribe(Tribe* visiting) override
    {
        std::cout << "Visiting Chiefdom/High Chiefdom: " << visiting->getBlobName() << " Ruler age: " << visiting->getRulerAge() << std::endl;
        if(visiting->getRulerAge() > 54)
        {
            visiting->handleSuccession();
        }
        else
        {
            std::cout << "Not killing chief in " << visiting->getBlobName() << std::endl;
        }
    }
};

// Client code
int main()
{
    // Declear an array of goverments [elements]
    std::vector<Goverment*> countryBlobs =  {new Republic(45, "Venice"), new Tribe(60, "Helensky"), new Kingdom(68, "Tchwabia")};
    // Declear visitor 
    GovVisitor* rulerDeath = new rulerKill();
    // Visit
    for(auto blob : countryBlobs)
    {
        blob->accept(rulerDeath);
    }
    // Teardown
    for(auto blob : countryBlobs)
    {
        delete blob;
    }
    delete rulerDeath;
}