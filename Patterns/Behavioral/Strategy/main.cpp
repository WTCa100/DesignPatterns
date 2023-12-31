/**
 * This is an example implementation of the Strategy pattern. In this pattern, an object that has received a request will choose how it will handle it.
 * The strategy will be choosen depending on buisness logic.
 * @date 2023-11-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<iostream>
#include<string>

// Some buisness logic
enum class CommanderTraits
{
    aggresiveLeader = 0,
    defensiveLeader,
    trickster
};

class LeadingCommander
{
    private:
    std::string name_;
    CommanderTraits trait_;
    public:
    LeadingCommander(std::string commanderName, CommanderTraits dominantTrait) : name_(commanderName), trait_(dominantTrait) {}
    
    // Getters
    CommanderTraits getTrait() const { return this->trait_; }
    std::string getName() const {return this->name_; }
    // Setters
    void setTrait(CommanderTraits traitNew) { this->trait_ = traitNew; }
    void setName(std::string nameNew) { this->name_ = nameNew; } 
};

struct Army
{
    uint16_t size_;
    LeadingCommander* leader_;

    Army(uint16_t size, LeadingCommander* leader) : size_(size), leader_(leader) {}
};

// Abstract strategy
class BattleStrategy
{
    public:
    virtual void fight() = 0;
    virtual ~BattleStrategy() {}
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
    Army* playerArmy_;
    public:
    // Assign default strat
    Battle(Army* playerArmy) : strat_(nullptr), playerArmy_(playerArmy)  { this->setStrategy(new AggresiveStrategy); }
    void setStrategy(BattleStrategy* stratNew)
    {
        if(strat_) { delete strat_; }
        strat_ = stratNew;
    }
    void fightBattle()
    {
        std::cout << playerArmy_->leader_->getName() << " entered a battle with " << playerArmy_->size_ << " man" << std::endl;
        switch (playerArmy_->leader_->getTrait())
        {
        case CommanderTraits::aggresiveLeader:
            setStrategy(new AggresiveStrategy);
            break;
        case CommanderTraits::defensiveLeader:
            setStrategy(new DefensiveStrategy);
            break;
        case CommanderTraits::trickster:
            setStrategy(new TrickyStrategy);
            break;
        }
        // After strategy set, context will call the concrete strategy implementation.
        strat_->fight();
    }

    ~Battle() { if(strat_) delete strat_; }
};

// Client ocde
int main()
{

    // Buisness logic
    LeadingCommander* genericLeader = new LeadingCommander("Jonathan Smith", CommanderTraits::defensiveLeader);
    Army* mainArmy = new Army(13200, genericLeader);
    // Create the context
    Battle* encounter = new Battle(mainArmy);

    // Do something with the context - change of the strategy will apply here
    std::cout << "<-= First handle of the strategy =->" << std::endl;
    encounter->fightBattle();

    // Change of the strategy condition occurs
    std::cout << "<-= Strategy condition changed =->" << std::endl;
    genericLeader->setTrait(CommanderTraits::trickster);
    // A different type of strategy will be applied in context
    std::cout << "<-= First handle with different strategy =->" << std::endl;
    encounter->fightBattle();

    delete encounter;
    delete mainArmy;
    delete genericLeader;
}