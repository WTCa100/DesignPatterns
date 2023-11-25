/**
 * This is an example implementation of the Decorator pattern. The core idea here is to allow changing the concrete classes during the runtime. 
 * Because the base decorator interface contains the refference to a core concrete object it can manipulate on what it does depening what type of 
 * decorator is calling concrete class methods.
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>

// Interface
class Dog
{
    public:
    virtual std::string play() = 0;
    virtual std::string retrieve(int distance) = 0;
    virtual ~Dog() {}
};

// Concrete class
class ConcreteDog : public Dog
{
    public:
    std::string play() override { return "The dog is playing with his favorite toy! Cute!"; }
    std::string retrieve(int distance) override { return "The dog runs for the stick! Distance thrown is: " + std::to_string(distance) + " meters."; }
};

// Base decorator
class DogDecorator : public Dog
{
    private:
    Dog* coreDog_;
    public:
    DogDecorator(Dog* sourceDog) : coreDog_(sourceDog) {}
    virtual std::string play()
    { return "Let's play with the doggie!"; }
    virtual std::string retrieve(int distance)
    { return "Let's play some retrieving with our doggie! You threw the stick " + std::to_string(distance) + " meters."; }
};

// Concrete decorator
class CircusDogDecorator : public DogDecorator
{
    public:
    CircusDogDecorator(Dog* sourceDog) : DogDecorator(sourceDog) {}
    std::string play() override
    { return DogDecorator::play() + " The Circus dog is doing some crazy acrobations!"; }
    std::string retrieve(int distance) override
    { return DogDecorator::retrieve(distance) + " The circus dog is jumping and acrobaiting while fetching your stick!"; }
};

// Concrete decorator
class HuntingDogDecorator : public DogDecorator
{
    public:
    HuntingDogDecorator(Dog* sourceDog) : DogDecorator(sourceDog) {}
    std::string play() override
    { return DogDecorator::play() + " The hunting dog rushes to the forest in order to catch it's prey!"; }
    std::string retrieve(int distance) override
    { return DogDecorator::retrieve(distance) + " Whoa, the hunting dog just got the stick and it's on your feet!"; }

};

// Client code
void clientCode(Dog* doggo)
{
    std::cout << "~!Playing part!~" << std::endl;
    std::cout << doggo->play() << std::endl;
    std::cout << "~!Retrivieng part!~" << std::endl;
    std::cout << doggo->retrieve(50) << std::endl;
}

int main()
{
    // Create the first default Dog
    Dog* fafik = new ConcreteDog;
    clientCode(fafik);


    // Create the decorated dog
    Dog* maniek = new HuntingDogDecorator(fafik);
    clientCode(maniek);
    delete maniek;

    // Create the decorated dog
    Dog* bazyl = new CircusDogDecorator(fafik);
    clientCode(bazyl);
    delete bazyl;

    // Delete the concrete dog source
    delete fafik;
}