#include <iostream>
#include <string>

// Abstract template
// Template consists of methods that can be overridden, however they have a basic functionaliy alredy presence.
class Sandwitch
{
    public:
    void assamble()
    {
        this->prepareBread();
        this->addCore();
        this->addVegetables();
        this->addExtras();
        this->addSauce();
        this->addSpices();
    }
    
    virtual void prepareBread() { std::cout << "Adding plain white bread." << std::endl; }
    virtual void addVegetables() { std::cout << "Adding some lettuce and onion." << std::endl; }
    virtual void addCore()  = 0;
    virtual void addSauce() = 0;
    virtual void addExtras() { std::cout << "No extras were added." << std::endl; }
    void addSpices() { std::cout << "Adding pepper and oregano." << std::endl;}

    virtual ~Sandwitch(){}
};

// Concrete template
class TeriaykiChickenSandwitch : public Sandwitch
{
    public:
    // Concrete templates must override the pure virtual functions.
    void addCore() override { std::cout << "Adding some fried chicken." << std::endl; }
    void addSauce() override { std::cout << "Adding Teriaki sauce along sauce." << std::endl; }
};

// Concrete template
class VeganSandwitch : public Sandwitch
{
    public:
    // Concrete templates can override other virtual functions.
    void prepareBread() override { std::cout << "Adding whole grain bread." << std::endl; }
    void addCore() override { std::cout << "Adding humus with Tofu." << std::endl; }
    void addSauce() override { std::cout << "Adding vegan mayo on top." << std::endl;}
};

// Concrete template
class FrenchSandwitch : public Sandwitch
{
    public: 
    // Concrete templates can override all virtual functions.
    void prepareBread() override { std::cout << "Adding a small baguettee." << std::endl;}
    void addVegetables() override { std::cout << "Adding lettuce and tomatoes." << std::endl; }
    void addCore() override { std::cout << "Adding eggs." << std::endl; }
    void addSauce() override { std::cout << "Adding olive oil." << std::endl; }
    void addExtras() override { std::cout << "Adding sliced camembert cheese." << std::endl;}
    void addSpices() { std::cout << "Adding white pepper." << std::endl; }
};

// Client code
int main()
{
    std::cout << "#1 order: Teriayki Chicken Sandwitch" << std::endl;
    Sandwitch* tcs = new TeriaykiChickenSandwitch;
    tcs->assamble();

    std::cout << "#2 order: Veggie Sandwitch" << std::endl;
    Sandwitch* veggie = new VeganSandwitch();
    veggie->assamble();

    std::cout << "#3 order: French Sandwitch" << std::endl;
    Sandwitch* french = new FrenchSandwitch();
    french->assamble();


    delete tcs;
    delete veggie;
    delete french;
}