/**
 * This is a example implementation of Abstract factory, which is a more complicated but in the same time more flexible version of
 * normal Factory method, exept this time we use a subset of abstract products, with their respected constructions being present
 * in different factories.
 * @date 2023-09-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

// Abstraction of Pistol
class Pistol
{
    public:
    virtual void shoot() = 0;
    virtual void present() = 0;
    virtual ~Pistol() {}
};

// Concrete product of Pistol
class ModernPistol : public Pistol
{
    public:
    void shoot() override
    { std::cout << "*pew* *pew*" << std::endl; }
    void present() override
    { std::cout << "This is a modern pistol." << std::endl; }
};

// Concrete product of Pistol
class VintagePistol : public Pistol
{
    public:
    void shoot() override
    { std::cout << "*pew* (chamber moves) *pew* (chamber moves)" << std::endl; }
    void present() override
    { std::cout << "This is a vintage pistol." << std::endl; }
};

// Abstration of Rifle
class Rifle
{
    public:
    virtual void shoot() = 0;
    virtual void present() = 0;
    virtual ~Rifle() {}
};

// Concrete product of Rifle
class ModernRifle : public Rifle
{
    void shoot() override
    { std::cout << "*PEW* *PEW* *PEW* *PEW*" << std::endl; }
    void present() override
    { std::cout << "This a modern rifle" << std::endl; }
};

// Concrete product of Rifle
class VintageRifle : public Rifle
{
    void shoot() override
    { std::cout << "*pew* *tsch-tschink*" << std::endl; }
    void present() override
    { std::cout << "This is a vintage rifle" << std::endl; }
};

// Factories:
// Abstract factory
class FirearmFactory
{
    public:
    // Create weaponry
    virtual Pistol* createPistol() = 0;
    virtual Rifle* createRifle() = 0;

    // User weaponry
    virtual void presentFirearm() = 0;

    virtual ~FirearmFactory() {}
};

// Concrete vintage firearms factory
class VintageFirearmFactory : public FirearmFactory
{
    Pistol* createPistol() override
    { return new VintagePistol; }
    Rifle* createRifle() override
    { return new VintageRifle; }

    void presentFirearm() override
    {
        Pistol* concretePistol = createPistol();
        Rifle* concreteRifle = createRifle();

        concretePistol->present();
        concretePistol->shoot();

        concreteRifle->present();
        concreteRifle->shoot();

        delete concretePistol;
        delete concreteRifle;
    }
};

// Concrete modern firearms factory
class ModernFirearmFactory : public FirearmFactory
{
    Pistol* createPistol() override
    { return new ModernPistol; }
    Rifle* createRifle() override
    { return new ModernRifle; }

    void presentFirearm() override
    {
        Pistol* concretePistol = createPistol();
        Rifle* concreteRifle = createRifle();

        concretePistol->present();
        concretePistol->shoot();

        concreteRifle->present();
        concreteRifle->shoot();

        delete concretePistol;
        delete concreteRifle;
    }
};

void client_code(FirearmFactory* factoryType)
{
    std::cout << "Hmm.. Today I will create weapons" << std::endl;
    factoryType->presentFirearm();
    std::cout << "Nice!" << std::endl;
}


int main()
{
    FirearmFactory* VF = new VintageFirearmFactory();
    FirearmFactory* MF = new ModernFirearmFactory();

    client_code(VF);
    client_code(MF);

    delete VF;
    delete MF;
    return 0;
}
