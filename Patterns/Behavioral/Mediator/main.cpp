/**
 * This is an example implementation of the Mediator pattern. This pattern limits the communication between given set of classes to a single mediator that
 * maintain the request / response to / from them. This allows the code to be less prone to complex dependencies.
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
#include <map>

enum rideType
{
    wfw    = 0,
    casual = 1,
    pet    = 2,
    none   = 3
};

enum requestType
{
    locationChange = 10,
    rideRequest    = 11,
    rideCancel     = 12
};

class Passenger;
class Driver;

// Interface mediator
// Generally there can be more than one mediator that derrivers from the parent class. Each mediator can handle different types of requests.
class Mediator
{
    protected:
    std::vector<Driver*> driversList_;
    public:
    // The method notify is the communicative core of a mediator.
    virtual void notify(Passenger* sender, requestType reqType) = 0;
    virtual void addDriver(Driver* driverNew) = 0;
    virtual void removeDriver(Driver* driverDelete) = 0;
    void clearDriverList(){ driversList_.clear(); }
    virtual ~Mediator() = default;
};

// Component family - passenger
// Component parent
// Each component can contact only it's mediator.
class Passenger
{
    protected:
    Mediator* applicationMediator_;
    std::string name_;
    std::string location_;
    rideType rideSpecificInfo_;
    bool hasRequested_;
    public:
    Passenger(Mediator* mediator, std::string senderName, std::string senderLocation, rideType specificRequest) :
    applicationMediator_(mediator), name_(senderName), location_(senderLocation), rideSpecificInfo_(specificRequest), hasRequested_(false)
    {
        this->requestRide();
    }

    // Methods
    void requestRide()
    {
        if(!hasRequested_)
        {
            applicationMediator_->notify(this, requestType::rideRequest);
            hasRequested_ = true;
        }
        else
        {
            std::cout << name_ << ": Ride already requested!" << std::endl;
        }
    }

    void cancelRide()
    {
        if(hasRequested_)
        {
            applicationMediator_->notify(this, requestType::rideCancel);
            hasRequested_ = false;
        }
        else
        {
            std::cout << name_ << ": No ride to cancel!" << std::endl;
        }
    }

    void changePickup(std::string locationNew)
    {
        if(hasRequested_)
        {
            location_ = locationNew;
            applicationMediator_->notify(this, requestType::locationChange);
        }
        else
        {
            std::cout << name_ << ": No ride was requested!" << std::endl;
        }
    }

    // Getters
    std::string getName() const { return name_; }
    std::string getLocation() const { return location_; }
    rideType getRideType() const { return rideSpecificInfo_; }
};

// Component children
class FemalePassager : public Passenger
{
    public:
    FemalePassager(Mediator* mediator, std::string senderName, std::string senderLocation) : 
    Passenger(mediator, senderName, senderLocation, rideType::wfw) {}
};

class PetPassager : public Passenger
{
    public:
    PetPassager(Mediator* mediator, std::string senderName, std::string senderLocation) : 
    Passenger(mediator, senderName, senderLocation, rideType::pet) {}
};

class CasualPassager : public Passenger
{
    public:
    CasualPassager(Mediator* mediator, std::string senderName, std::string senderLocation) : 
    Passenger(mediator, senderName, senderLocation, rideType::casual) {}
};

// Component Family (driver)
class Driver
{
    private: 
    uint16_t generateDistance() { return rand() % 16; }    
    protected:
        Mediator* applicationMediator_;
        std::string name_;
        bool isFree_;
        uint16_t distanceFromTarget_; // In miles
        rideType driverSpeciality_;
    public:
        Driver(Mediator* mediator, std::string driverName, rideType type) :
        applicationMediator_(mediator), name_(driverName), driverSpeciality_(type), isFree_(true), distanceFromTarget_(generateDistance()) 
        {
            signIn();
        }

        // Methods
        void signIn()
        {
            applicationMediator_->addDriver(this);
        }
        void gotoLocation(std::string location)
        {
            std::cout << "Radio: \"Move to " << location << " to get the passager\"" << std::endl;
        }
        void signOff()
        {
            applicationMediator_->removeDriver(this);
        }

        // Setters
        void setFreeStatus(bool newStatus) { this->isFree_ = newStatus; } 
        // Getters
        std::string getName() const { return name_; }
        uint16_t getDistance() const { return distanceFromTarget_; }
        bool getFreeStatus() const { return isFree_; }
        rideType getDriverSpeciality() const { return driverSpeciality_; }
};

// Concrete Driver
class FemaleDriver : public Driver
{
    public:
    FemaleDriver(Mediator* mediator, std::string driverName) :
    Driver(mediator, driverName, rideType::wfw) {}
};

class PetDriver : public Driver
{
    public:
    PetDriver(Mediator* mediator, std::string driverName) :
    Driver(mediator, driverName, rideType::pet) {}
};

class CasualDriver : public Driver
{
    public:
    CasualDriver(Mediator* mediator, std::string driverName) :
    Driver(mediator, driverName, rideType::casual) {}
};

// Concrete mediator
class RideMediator : public Mediator
{
    private:
    std::string getRideTypeStr(rideType type)
    {
        switch (type)
        {
        case rideType::casual:
            return {"Casual"};
        case rideType::pet:
            return {"Pet transport"};
        case rideType::wfw:
            return {"Women for Women"};
        case rideType::none:
        default:
            return {"Bad Request"};
        }
    }
    void giveJob(Driver* taker, Passenger* orderer)
    {
        std::cout << "Driver " << taker->getName() << " assigned to take " << orderer->getName() << " from " << orderer->getLocation() << std::endl;
        std::cout << "The driver is " << taker->getDistance() << " miles away." << std::endl;
        this->activeJobs_.insert(std::make_pair(orderer, taker));
        taker->gotoLocation(orderer->getLocation());
        taker->setFreeStatus(false);
    }
    void takeJob(Driver* giver, Passenger* orderer)
    {
        std::cout << "Driver " << giver->getName() << " removed job from " << orderer->getName() << " from " << orderer->getLocation() << std::endl;
        std::cout << "Driver is free to dispatch again." << std::endl;
        activeJobs_.erase(orderer);
        giver->setFreeStatus(true); 
    }
    std::map<Passenger*, Driver*> activeJobs_;

    public:
    RideMediator() { activeJobs_ = {}; }
    void addDriver(Driver* driverNew) override
    {
        std::cout << "Will add new driver. " << driverNew->getName() << std::endl;
        this->driversList_.push_back(driverNew);
    }
    void removeDriver(Driver* driverDelete) override
    {
        std::cout << "Will try to delete driver " << driverDelete->getName() << std::endl;
        // Find driver
        if(!driverDelete->getFreeStatus())
        {
            std::cout << "Cannot remove driver with unhandled job." << std::endl;
            return;
        }
        this->driversList_.erase(std::remove(this->driversList_.begin(), this->driversList_.end(), driverDelete), this->driversList_.end());
        std::cout << "Successfully deleted " << driverDelete->getName() << " from active drivers! See you soon!" << std::endl; 
    }

    // The notify method does the necessary logic as well as handles communication between classes.
    void notify(Passenger* sender, requestType reqType)
    {
        std::string senderName = sender->getName();
        std::string senderLocation = sender->getLocation();
        std::string senderRideType = getRideTypeStr(sender->getRideType());

        switch (reqType)
        {
        case requestType::locationChange:
            std::cout << senderName << " changed location to " << senderLocation << std::endl;
            std::cout << "Changing the " << senderRideType << " driver pick-up destination." << std::endl;
            this->activeJobs_[sender]->gotoLocation(senderLocation);
            break;
        case requestType::rideCancel:
            std::cout << senderName << " canceled ride from " << senderLocation << std::endl;
            std::cout << senderRideType << " driver freed and ready for new dispatch." << std::endl;
            takeJob(this->activeJobs_[sender], sender);
            break;
        case requestType::rideRequest:
            {
                std::cout << senderName << " requested a new ride - pickup from " << senderLocation << std::endl;
                std::cout << "Looking for " << senderRideType << " driver to dispatch." << std::endl;
                bool driverFound = false;
                for(auto candidate : this->driversList_)
                {
                    if((sender->getRideType() == candidate->getDriverSpeciality()) && sender->getRideType() != rideType::casual && candidate->getFreeStatus())
                    {
                        std::cout << "Found a driver with specific request!" << std::endl;
                        giveJob(candidate, sender);
                        driverFound = true;
                        break;
                    }
                    else if(sender->getRideType() == rideType::casual)
                    {
                        std::cout << "Found a driver!" << std::endl;
                        giveJob(candidate, sender);
                        driverFound = true; 
                        break;
                    }
                }
                if(!driverFound) { std::cout << "Hang in there, we are still looking!" << std::endl; }
                break;
            }
        default:
            std::cout << senderName << " at: " << senderLocation << " skipped. Reason " << senderRideType << std::endl;
            break;
        }
    }

    ~RideMediator()
    { 
        this->activeJobs_.clear();
        this->clearDriverList();
    }
};

// Client code goes here
int main()
{
    // First we declare the mutual mediator
    Mediator* superApp = new RideMediator();
    // Here are the components from one family
    Driver* John = new CasualDriver(superApp, "John");
    Driver* Natalie = new FemaleDriver(superApp, "Natalie");
    Driver* Todd = new PetDriver(superApp, "Todd");
    Driver* Amanda = new FemaleDriver(superApp, "Amanda");

    // Here are the components from second family
    Passenger* Laura = new FemalePassager(superApp, "Laura", "Main St. 52");
    Passenger* Mark = new PetPassager(superApp, "Mark", "Industrail St. 23");
    Passenger* Fyodor = new CasualPassager(superApp, "Fyodor", "Russian St. 1");
    Passenger* Bogdan = new CasualPassager(superApp, "Bogdan", "Frog Ave. 13B");

    // Passagers only communicate via mediator
    // They send a request straight to the concrete mediator and it is there taht it gets handled
    Laura->cancelRide();
    Mark->changePickup("Industrial St. 23");
    Fyodor->requestRide();
    Bogdan->cancelRide();
    Bogdan->cancelRide();

    // Drivers follows the same principle
    Todd->signOff();
    Natalie->signOff();
    /* 30 minute passes */
    Natalie->signIn();
    Laura->requestRide();

    // Cleanup
    delete Laura;
    delete Mark;
    delete Fyodor;
    delete John,
    delete Natalie,
    delete Todd,
    delete Amanda;
    delete Bogdan;
    delete superApp;
}