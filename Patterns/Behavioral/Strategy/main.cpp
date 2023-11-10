#include<iostream>
#include<string>

// Abstract strategy
class BattleStrategy
{
    public:
    virtual void fight() = 0;
    ~BattleStrategy() {}
};

// Concrete strategy
class AggresiveStrategy : public BattleStrategy
{
    public:
    void fight() override
    {
        std::cout << "Your army is charging:" << std::endl;
        std::cout << "Cavalery is the fist to arrive and smash enemy troops." << std::endl;
        std::cout << "After a while your infrantry arrives to kill the remained of the enemy army!" << std::endl;
    }
};

// Concrete strategy
class DefensiveStrategy : public BattleStrategy
{
    public:
    void fight() override
    {
        std::cout << "Your army is waiting for the enemy to charge:" << std::endl;
        std::cout << "Archers are shooting arrows at foes." << std::endl;
        std::cout << "In front of them your infrantryman are standing close to each other with their shields - ready to defend an attack." << std::endl; 
    }
};

class TrickyStrategy : public BattleStrategy
{
    public:
    void fight() override
    {
        std::cout << "Your army is doing an experimental tactic:" << std::endl;
        std::cout << "A small portion of your cavalery along with you are rushing to the near forest." << std::endl;
        std::cout << "That has attracted a great portion of their cavalery after your." << std::endl;
        std::cout << "The rest of your cavalery is charging the enemy, along with infrantry that ambushed your enemy from flank." << std::endl;  
    }
};

// Context
class Battle 
{
    private:
    BattleStrategy* strat_;
    public:
    // Assign default strat
    Battle() : strat_(nullptr) { this->setStrategy(new AggresiveStrategy); }
    void setStrategy(BattleStrategy* stratNew)
    {
        if(strat_) { delete strat_; }
        strat_ = stratNew;
    }
    void fightBattle()
    {
        strat_->fight();
    }

    ~Battle() { if(strat_) delete strat_; }
};

// Client ocde
int main()
{
    // Create the context
    Battle* encounter = new Battle();

    // Do something with the context
    encounter->fightBattle();

    // Change the strategy
    encounter->setStrategy(new DefensiveStrategy);
    // Do something with different strategy in mind
    encounter->fightBattle();

    delete encounter;
}