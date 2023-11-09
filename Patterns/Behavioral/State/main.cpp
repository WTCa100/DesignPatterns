#include <iostream>
#include <string>

// Context prototype
class Car;

// Abstract state
class State
{
    protected:
    Car* context_;
    public:
    State() : context_(nullptr) {}

    // Request handles
    virtual void turnOn()    = 0;
    virtual void turnOff()   = 0;
    virtual void drive()     = 0;
    virtual void openHood() = 0;

    void setContext(Car* contextNew) { this->context_ = contextNew; }

    virtual ~State() {}
};

// Concrete classes prototypes
// Concrete state
class StateOn : public State
{
    public:
    StateOn() : State() {}
    void turnOn() override { std::cout << "Already running." << std::endl; }
    void drive() override { std::cout << "*wrrrrm* *wrrrrrm*" << std::endl; }
    void openHood() override { std::cout << "Turn off your car befre opening the hood!" << std::endl; }
    void turnOff() override;
};

// Concrete state
class StateOff : public State
{
    public:
    StateOff() : State() {}
    void turnOn() override;
    void drive() override { std::cout << "Turn on your car in order to start it!" << std::endl; }
    void openHood() override { std::cout << "*tshk* - hood opens." << std::endl; }
    void turnOff() override { std::cout << "Already not running." << std::endl; }
};

// Context impl
class Car
{
    private:
    State* carState_;
    public:
    Car() : carState_(nullptr) { changeState(new StateOff); }
    void checkHood()
    {
        std::cout << "I have to check what's under the hood." << std::endl;
        carState_->openHood();
    }
    void travel(std::string dest)
    {
        std::cout << "I need to get to " << dest << std::endl;
        carState_->drive();
    }

    void changeState(State* statusNew)
    {
        if(this->carState_ != nullptr) { delete this->carState_; }
        carState_ = statusNew;
        carState_->setContext(this);
    }

    void turnOn() { carState_->turnOn(); }
    void turnOff() { carState_->turnOff(); }

    ~Car() { delete carState_; }
};



void StateOn::turnOff()
{
    std::cout << "Turning the engine off." << std::endl;
    std::cout << "oldState: On -> newState: Off" << std::endl; 
    this->context_->changeState(new StateOff);
}

void StateOff::turnOn()
{

    std::cout << "Turning the car on." << std::endl;
    std::cout << "oldState: Off -> newState: On" << std::endl;
    this->context_->changeState(new StateOn);
}


// Client Code
int main()
{
    // Create context
    Car* Tojeta = new Car();

    // Operate on context - change in state will happen inside the class logic
    Tojeta->turnOn();
    Tojeta->travel("Berlin");
    Tojeta->turnOff();
    Tojeta->checkHood();
    Tojeta->travel("Prague");
    Tojeta->turnOn();
    Tojeta->travel("Prague");
    Tojeta->checkHood();
    Tojeta->turnOff();

    delete Tojeta;
}