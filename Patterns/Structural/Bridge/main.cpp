/**
 * This is an example of the Bridge pattern. A bridge is simply a split of a bigger, complex class into 2 separate classes where one takes role
 * of abstraction, with a higher level instructionality, and the second one takes a role of implementation the lower level methods + additional
 * complex methods related to the proper working of a class. 
 * @date 2023-09-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <string>

enum weapon
{
    bow = 0,
    oneHandSword,
    twoHandSword,
    staff
};

// Abstract implementation - interface
class EnemyClass
{
    protected:
    std::string name_;
    int health_;
    int baseStat_;
    weapon heldWeapon_;
    bool alive_;
    public:
    EnemyClass(std::string name, weapon weapon) : name_(name), heldWeapon_(weapon), health_(100), baseStat_(10), alive_(true) {} 
    virtual void setName(std::string newName)           = 0;
    virtual std::string getName()                       = 0;
    virtual bool isAlive()                              = 0;
    virtual void setAlive(bool newStatus)               = 0;
    virtual void setHealth(int health)                  = 0;
    virtual int getHealth()                             = 0;
    virtual void setWeapon(weapon newWeapon)            = 0;
    virtual weapon getWeapon()                          = 0;
    virtual void setBaseStat(int newStat)               = 0;
    virtual int getBaseStat()                           = 0;
    virtual void makeAttack()                           = 0;
    virtual void makeUltimateAttack()                   = 0;
    virtual void blockAttack()                          = 0;
    virtual void chargeEnemy(std::string enemyToCharge) = 0;
    virtual void postDeathRambling()                    = 0;
    virtual void preDeathRambling()                     = 0;
    virtual ~EnemyClass() {};
};

// Concrete implementation
class EnemyClassWarrior : public EnemyClass
{
    public:
    EnemyClassWarrior(std::string name) : EnemyClass(name, oneHandSword) {}
    void setName(std::string newName) override
    { this->name_ = newName; }
    std::string getName() override
    { return this->name_; }
    bool isAlive() override { return alive_; }
    void setAlive(bool newStatus) override { this->alive_ = newStatus; }
    void setHealth(int health) override  
    { 
        this->health_ = health;
        if(this->health_ == 0)
        {
            this->alive_ = false;
        }
    }
    int getHealth() override
    { return health_;}
    weapon getWeapon() override 
    { return heldWeapon_; }
    void setWeapon(weapon newWeapon) override 
    { 
        if(newWeapon != oneHandSword || newWeapon != twoHandSword)
        {
            std::cout << "A warrior shall not use anything exept swords!" << std::endl;
            return;
        }

        this->heldWeapon_ = newWeapon;
    }
    int getBaseStat() override
    { return this->baseStat_; }
    void setBaseStat(int newStat) override
    { this->baseStat_ = newStat; }
    void makeAttack() override
    {
        std::cout << "A warrior tries to slash you with his sword!" << std::endl;
    }
    void makeUltimateAttack() override
    {
        std::cout << "A warrior makes his way to try to behead you with his sword doing some sick sword dance" << std::endl;
    }
    void blockAttack() override
    {
        if(this->heldWeapon_ == twoHandSword)
        {
            std::cout << "The warrior is trying to use his sword to block your attack (not very effective!)" << std::endl;
        }
        else if(this->heldWeapon_ == oneHandSword)
        {
            std::cout << "The warrior is using the shiled to block your attack (effective!)" << std::endl;
        }
        else
        {
            std::cout << "The warrior scratches his head because he don't know how to use his weapon in a mean of defence (he gets hit)" << std::endl;
        }
    }
    void chargeEnemy(std::string enemyToCharge) override
    {
        std::cout << "The warrior is rushing straight towards you screamin!" << std::endl;
    }
    void postDeathRambling() override
    {
        std::cout << "I, " << this->name_ << " shalln't kneel before you!!" << std::endl;
        std::cout << "*Dies*" << std::endl;
    }
    void preDeathRambling() override
    {
        std::cout << "You thought you can kill ME?" << std::endl;
        std::cout << "*enters phase 2*" << std::endl;
    }
};

// concrete implementation
class EnemyClassMage : public EnemyClass
{
    public:
    EnemyClassMage(std::string name) : EnemyClass(name, staff) {}
    void setName(std::string newName) override
    { this->name_ = newName; }
    std::string getName() override
    { return this->name_; }
    bool isAlive() override { return alive_; }
    void setAlive(bool newStatus) override { this->alive_ = newStatus; }
    void setHealth(int health) override  
    { 
        this->health_ = health;
        if(this->health_ == 0)
        {
            this->alive_ = false;
        }
    }
    int getHealth() override
    { return health_;}
    weapon getWeapon() override 
    { return heldWeapon_; }
    void setWeapon(weapon newWeapon) override 
    { 
        if(newWeapon == twoHandSword)
        {
            std::cout << "A mage codex forbids them from using two handed swords" << std::endl;
            return;
        }

        this->heldWeapon_ = newWeapon;
    }
    int getBaseStat() override
    { return this->baseStat_; }
    void setBaseStat(int newStat) override
    { this->baseStat_ = newStat; }
    void makeAttack() override
    {
        std::cout << "The mage is using his stuff in order to cast a deadly spell!" << std::endl;
    }
    void makeUltimateAttack() override
    {
        std::cout << "The mage is shooting at you with a great fireball with a power of a nuclear warhead!" << std::endl;
    }
    void blockAttack() override
    {
        if(this->heldWeapon_ == twoHandSword)
        {
            std::cout << "The mage surrenders and accepts his fate as he broken the sacred law." << std::endl;
        }
        else
        {
            std::cout << "The mage is casting a defensive spell, which addapts to your means of weaponry! (super effective!!!)" << std::endl;
        }
    }
    void chargeEnemy(std::string enemyToCharge) 
    {
        std::cout << "The mage put out his scroll while looking at you, ready to make a move." << std::endl;
    }
    void postDeathRambling() override
    {
        std::cout << "Starts talking about the life and death and the importance of it, also trying to get your zodiac sign before death(weird)." << std::endl;
        std::cout << "*Dies*" << std::endl;
    }
    void preDeathRambling() override
    {
        std::cout << "You're a smart and shrewd boy, but enough is enough." << std::endl;
        std::cout << "*enters phase 2*" << std::endl;
    }
};

// Abstraction
class Enemy
{
    protected:
    EnemyClass* unit_;
    public:
    Enemy(EnemyClass* startingClass) : unit_(startingClass) {}
    virtual void kill()
    {
        if(unit_->isAlive())
        {
            std::cout << "A Godly force has cursed " << unit_->getName()  << ", and thus it dies." << std::endl;
            unit_->setHealth(unit_->getHealth() - unit_->getHealth());
        }
    }
    virtual void ressurect()
    { 
        if(!unit_->isAlive())
        {
            std::cout << "A Godly force has ressurected the fallen unit! " << unit_->getName() << " is back alive!" << std::endl;
            unit_->setAlive(true);
            unit_->setHealth(100);
        }
    }
    virtual void changeWeapon(weapon newWeapon)
    {
        std::cout << "Log: Changed " << unit_->getName() << " to " << newWeapon << std::endl; 
        unit_->setWeapon(newWeapon);
    }

    virtual void forceAttack(std::string target)
    {
        unit_->chargeEnemy(target);
        unit_->makeAttack();
    }
    // Hit as hit the selected unit
    virtual void hit(int hitPower)
    {
        unit_->setHealth(unit_->getHealth() - hitPower);
    }

    virtual void heal(int healPower)
    {
        unit_->setHealth(unit_->getHealth() + healPower);
    }
    virtual void makeStronger()
    {
        int currentLvl = unit_->getBaseStat();
        unit_->setBaseStat(currentLvl++);
    }
    virtual void makeWeaker()
    {
        int currentLvl = unit_->getBaseStat();
        unit_->setBaseStat(currentLvl--);
    }
    virtual void block()
    {
        unit_->blockAttack();
    }
};

// Extended abstraction
class EnemyBoss : public Enemy
{
    public:
    EnemyBoss(EnemyClass* bossClass) : Enemy(bossClass) {} 
    void ressurect() override
    {
        if(!unit_->isAlive())
        {
            unit_->preDeathRambling();
            unit_->setAlive(true);
            unit_->setHealth(100);
        }
    }
    void kill() override
    {
        if(unit_->isAlive())
        {
            unit_->postDeathRambling();
            unit_->setHealth(unit_->getHealth() - unit_->getHealth());
        }
    }
    void block() override
    { 
        unit_->blockAttack();
        attackChain();
    }
    virtual void attackChain()
    {
        unit_->makeAttack();
        unit_->makeAttack();
        unit_->makeUltimateAttack();
    }
};

void clientCode(Enemy* enemyEntity)
{
    enemyEntity->forceAttack("Player");
    enemyEntity->block();
    enemyEntity->hit(25);
    enemyEntity->heal(20);
    enemyEntity->forceAttack("Player");
    enemyEntity->kill();
    enemyEntity->ressurect();
    enemyEntity->makeStronger();
    enemyEntity->forceAttack("Player");
    enemyEntity->block();
    enemyEntity->forceAttack("Player");
    enemyEntity->kill();
}

int main()
{
    //Create 2 of the concrete fighter classes
    EnemyClass* concreteMeleeFighter = new EnemyClassWarrior("Mark");
    EnemyClass* concreteMageFighter = new EnemyClassMage("Torrent");

    // Create the abstraction
    Enemy* meleeFighter = new Enemy(concreteMeleeFighter);
    Enemy* mageFighter = new Enemy(concreteMageFighter);

    // Fight melee
    std::cout << "Warrior encounter!" << std::endl;
    clientCode(meleeFighter);

    // Fight mage
    std::cout << "Mage encounter!" << std::endl;
    clientCode(mageFighter);

    // Delete fighters
    delete meleeFighter;
    delete mageFighter;
    delete concreteMageFighter;
    delete concreteMeleeFighter;

    // Boss encounter - warrior
    EnemyClass* concreteBossMeleeFighter = new EnemyClassWarrior("Balzahar");
    Enemy* bossMelee = new EnemyBoss(concreteBossMeleeFighter);
    bossMelee->changeWeapon(twoHandSword);

     // Fight boss
    std::cout << "Warrior boss encounter!" << std::endl;     
    clientCode(bossMelee);

    // Delete Boss fighters
    delete bossMelee;
    delete concreteBossMeleeFighter;

    // Boss encounter - mage
    EnemyClass* concreteBossMageFighter = new EnemyClassMage("Merlin");
    Enemy* bossMage = new EnemyBoss(concreteBossMageFighter);

    // Fight
    std::cout << "Mage boss encounter!" << std::endl;     
    clientCode(bossMage);

    // Delete
    delete bossMage;
    delete concreteBossMageFighter;
}