/**
 * This is an exampel implementation of the Prototype pattern. A prototype gives the client the ability to clone desired concrete objects
 * with all of it's fields being identical (including the private ones). Each prototype has a built-in "clone" method that will return
 * the new object with the same attributes as the calling instance.
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 */
#include <iostream>
#include <string>
#include <vector>

// Prototype interface
class Animal
{
    protected:
    /// @note this is a name of the spiecies not individual animal per se.
    std::string animalName_;
    public:

    // Constructor
    Animal() {}
    Animal(std::string name) : animalName_(name) {}

    // Cloning
    virtual Animal* clone() const = 0;
    virtual void show() const = 0;
    virtual ~Animal() {}
};

// Concrete prototype 1
class Cow : public Animal
{
    private:
    // Additional attributes related to the concrete prototype
    std::string patchesColor_;
    public:
    // Creation
    Cow(std::string patchesColor) : Animal("Cow"), patchesColor_(patchesColor) {}
    // Cloning
    Animal* clone() const override
    { return new Cow(*this); }
    // Additional methods  
    void show() const override 
    { std::cout << "This is a " << animalName_ << " with " << patchesColor_ << " patches" << std::endl; }
};

// Concrete prototype 2
class Sheep : public Animal
{
    private:
    std::string woolColor_;
    public:
    Sheep(std::string woolColor) : Animal("Sheep"), woolColor_(woolColor) {}
    Animal* clone() const override
    { return new Sheep(*this); }
    void show() const override
    { std::cout << "This is a " << woolColor_ << " " << animalName_ << std::endl; }
};

void clienCode()
{
    std::vector<Animal*> animalFarm;

    std::cout << "Initial creation of black cow, brown cow, and white sheep. " << std::endl;
    Animal* cowBrown = new Cow("brown");
    Animal* cowBlack = new Cow("black");
    Animal* sheepWhite = new Sheep("white");

    animalFarm.push_back(cowBrown);
    animalFarm.push_back(cowBlack);
    animalFarm.push_back(sheepWhite);

    // Clone 3 brown cows, 5 black and 10 sheeps
    std::cout << "Cloning 3 brown cows, 5 black cows and 10 sheeps." << std::endl;
    for(int i = 0; i < 3 ; i++)
    {
        animalFarm.push_back(cowBrown->clone());
    }

    for(int i = 0; i < 5 ; i++)
    {
        animalFarm.push_back(cowBlack->clone());
    }

    for(int i = 0; i < 10 ; i++)
    {
        animalFarm.push_back(sheepWhite->clone());
    }    

    // Display animals
    for(auto livestock : animalFarm)
    {
        livestock->show();
    }

    // Remove animals
    // Prototype removal is clients' responsiblity.    
    for(auto livestock : animalFarm)
    {
        delete livestock;
    }
}

int main()
{
    clienCode();
    return 0;
}