/**
 * In this program we will take a closer look into a prototype design pattern. A prototype gives the client the ability to clone desired concrete objects
 * with all of it's fields being identical (including the private ones).
 * In this situation we are also using factory method that will be store the preset of certain class combinations, and used as a cloner later on.
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 */
#include <iostream>
#include <string>
#include <vector>
#include <map>

enum LivestockType
{
    LTCow = 0,
    LTSheep
};

// Consider using the preset colors
enum LivestockColor
{
    LCBlack = 0,
    LCBrown,
    LCWhite
};

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

class AnimalFactory
{
    private:
    std::map<LivestockType, std::map<LivestockColor, Animal*>> livestockPreset_;
    public:
    // Constructor
    AnimalFactory() 
    {
        // Handle cows
        livestockPreset_[LivestockType::LTCow][LCBlack] = new Cow("Black");
        livestockPreset_[LivestockType::LTCow][LCBrown] = new Cow("Brown");
        livestockPreset_[LivestockType::LTCow][LCWhite] = new Cow("White");

        // Handle sheeps
        livestockPreset_[LivestockType::LTSheep][LCBlack] = new Sheep("Black");
        livestockPreset_[LivestockType::LTSheep][LCBrown] = new Sheep("Brown");
        livestockPreset_[LivestockType::LTSheep][LCWhite] = new Sheep("White");
    }

    // Factory method
    Animal* CreateAnimal(LivestockType animalType, LivestockColor animalColor)
    {
        return livestockPreset_[animalType][animalColor]->clone();
    }

    ~AnimalFactory() 
    {
        for(auto animalType : livestockPreset_)
        {
            for(auto animalColor : animalType.second)
            {
                delete animalColor.second;
            }
        }
    }
};

void clienCode(AnimalFactory* factory)
{
    std::vector<Animal*> animalFarm;
    // No need to create the initial objects as they are preset inside factory method
    std::cout << "Clone 5 white cows, 3 black and 6 brown sheep." << std::endl;
    std::cout << "Cows" << std::endl;
    for(int i = 0; i < 5; i++)
    {
        animalFarm.push_back(factory->CreateAnimal(LivestockType::LTCow, LivestockColor::LCWhite));
    }

    std::cout << "Sheep black" << std::endl;
    for(int i = 0; i < 3; i++)
    {
        animalFarm.push_back(factory->CreateAnimal(LivestockType::LTSheep, LivestockColor::LCBlack));
    }

    std::cout << "Sheep white" << std::endl;
    for(int i = 0; i < 6; i++)
    {
        animalFarm.push_back(factory->CreateAnimal(LivestockType::LTSheep, LivestockColor::LCWhite));
    }

    // Display animals
    std::cout << "Looking at farm." << std::endl;
    for(auto livestock : animalFarm)
    {
        livestock->show();
    }

    // delete animals
    for(auto livestock : animalFarm)
    {
        delete livestock;
    }
}

int main()
{       
    AnimalFactory* aFactory = new AnimalFactory();
    clienCode(aFactory);
    delete aFactory;
    return 0;
}