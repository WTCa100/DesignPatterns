#include <iostream>
#include <string>
#include <time.h>
#include <vector>


// One concrete object
class Food
{
public:
    bool hasMeat_;
    bool hasCheese_;
    Food(bool hasMeat, bool hasCheese) : hasMeat_(hasMeat), hasCheese_(hasCheese) {}
    void describe()
    {
        std::cout << "A meal ";
        hasMeat_ ? std::cout << "with meat " : std::cout << "without meat ";
        hasCheese_ ? std::cout << "with cheese " : std::cout << "without cheese ";
        std::cout << "in it." << std::endl;
    }
};


// Interface handle
class CanteenHandle
{
    public:
    virtual void setNext(CanteenHandle* nextHandle) = 0;
    virtual std::string handle(Food* request) = 0;
};

// Abstract handle (Canteen component a.k.a. Employee)
class CanteenComponent : public CanteenHandle
{
    private:
    CanteenHandle* nextHandle_;
    public:
    void setNext(CanteenHandle* nextHandle) override
    {
        this->nextHandle_ = nextHandle;
    }
    std::string handle(Food* request) override
    {
        if(this->nextHandle_ != nullptr)
        {
            std::cout << "Next person approaches." << std::endl;
            return this->nextHandle_->handle(request);
        }

        return {"End of CoR\n"};
    }
};

// Concrete handle
class AmyHandler : public CanteenComponent
{
    public:
    std::string handle(Food* request) override
    {
        // Check if the handle shall proceede
        if(!request->hasMeat_ && !request->hasCheese_)
        {
            return "Amy: Om nom nom nom";
        }
        std::cout << "Amy says: I am not eating that. It has meat or cheese in it and I am a vegan!" << std::endl;
        return CanteenComponent::handle(request);
    }
};

// Concrete handle
class MattHandler : public CanteenComponent
{
    public:
    std::string handle(Food* request) override
    {
        if(request->hasMeat_)
        {
            return "Matt: Om nom nom nom";
        }
        std::cout << "Matt says: I am not eating that. It has no meat, and I NEAD MEAT TO STAY STRONG!" << std::endl;
        return CanteenComponent::handle(request);
    }
};

// Concrete handle
class PeterHandler : public CanteenComponent
{
    public:
    std::string handle(Food* request) override
    {
        if(!request->hasMeat_ && request->hasCheese_)
        {
            return "Peter: Om nom nom nom";
        }
        std::cout << "Peter says: I am not eating that. It has meat, and I am a vegetarian, or it doesn't have cheese, and I love cheese." << std::endl;
        return CanteenComponent::handle(request);
    }
};

// Client Code
void lunchBreak(CanteenHandle* firstCustomer)
{
    std::vector <Food*> foodBuffet = {new Food(true, false), new Food(false, false), new Food(false,true)};
    std::cout << "First person approaches!" << std::endl;
    for(auto tray : foodBuffet)
    {
        std::cout << "On the tray: " << std::endl;
        tray->describe();
        std::string result = firstCustomer->handle(tray);
        if(result != "End of CoR\n")
        {
            std::cout << result << std::endl;
        }
        else
        {
            std::cout << "No one has ate that!" << std::endl;
        }
    }
}

int main()
{
    CanteenHandle* amy = new AmyHandler;
    CanteenHandle* matt = new MattHandler;
    CanteenHandle* peter = new PeterHandler;

    // Set next handler
    amy->setNext(matt);
    matt->setNext(peter);

    std::cout << "/----------------------\\" << std::endl;
    std::cout << "| Amy -> Matt -> Peter |" << std::endl;
    std::cout << "\\----------------------/" << std::endl;
    lunchBreak(amy);

    // We can also start from different refference
    std::cout << "/---------------\\" << std::endl;
    std::cout << "| Matt -> Peter |" << std::endl;
    std::cout << "\\---------------/" << std::endl;
    lunchBreak(matt);

    delete amy;
    delete matt;
    delete peter;
}