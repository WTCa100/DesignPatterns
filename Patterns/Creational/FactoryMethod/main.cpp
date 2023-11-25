/**
 * This is an example implementation implementation of a creational design pattern of factory method.
 * Each concrete class is a child of a superclass, the subclass contain a constructor inside a method,
 * thus it can alter it construction process from within one place in code. 
 * There also is a interface that is being used by the concrete subclasses to do a specific task.
 * @date 2023-09-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <cstdlib>

// Moving interface
class MoveVechicle
{
    public:
    virtual void move() = 0;
    virtual ~MoveVechicle() {}
};

// The following classes are the products
// Superclass
class Vechicle : public MoveVechicle
{
    public:
    virtual void showDetails() = 0;
    virtual void move() {}
    virtual ~Vechicle() {}
};

// Child class
class Car : public Vechicle
{
    public:
    void showDetails() override 
    { std::cout << "This is a car!\n"; }
    void move() override
    { std::cout << "Pressing the gas pedal, and gooooo!" << std::endl; }
};

// Another Child class
class Plane : public Vechicle
{
    public:
    void showDetails() override
    { std::cout << "This is a plane!\n"; }
    void move() override
    {
        std::cout << "Prepare for lift of!" << std::endl;
        system("sleep 1");
        std::cout << "Lifting!" << std::endl;
        system("sleep 1");
        std::cout << "On air, and moving." << std::endl;
    }
};

// Factory part
class Creator
{
    public:
    virtual ~Creator() {} 
    virtual Vechicle* createVechicle() = 0;

    void presentVechicle()
    { 
        Vechicle* createdVechicle = this->createVechicle();
        createdVechicle->showDetails();

        delete createdVechicle;
    }
    void changeLocation()
    {
        presentVechicle();
        Vechicle* createdVechicle = this->createVechicle();
        createdVechicle->move();

        delete createdVechicle;
    }

};

// Concrete Factory (Creator) of Cars
class CarFactory : public Creator
{
    public:
    Vechicle* createVechicle() override
    { return new Car; }
};

// Concrete Factory (Creator) of Planes
class PlaneFactory : public Creator
{
    public:
    Vechicle* createVechicle() override
    { return new Plane; }
};

int main()
{
    Creator* VCF = new CarFactory;
    VCF->changeLocation();
    Creator* VPF = new PlaneFactory;
    VPF->changeLocation();

    delete VCF;
    delete VPF;
    return 0;
}
