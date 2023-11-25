/**
 * This is an example implementation of the Facade pattern. To put it briefly, there is a complex library - "TravelingMgt.h" that useses a lot of logic.
 * It's hard for the user to completly understand it, so a Facade comes in that simplify the usage of the library.
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>

// Part of the complex logic
class CarRentalAPI
{
    private:
    std::string location_;
    public:
    CarRentalAPI(std::string location) : location_(location) {}
    // As this is just an example of usage we will just list models with price.
    void listModelsAndPrice()
    {
        // Normaly we would use a map for that - not display it in hardcoded way.
        std::cout << "In " << location_ << " there are the following car models along with prices: " << std::endl;
        std::cout << "1. Mercedes : 642,-" << std::endl;
        std::cout << "2. Toyota : 563,-" << std::endl;
        std::cout << "3. Fiat : 596,-" << std::endl;
    }

    std::string rentCar(std::string model)
    {
        return "Rented a car: " + model;
    }

    void changeLocation(std::string newLocation) { this->location_ = newLocation; }
};

// Part of the complex logic
class HotelBookingAPI
{
    private:
    std::string location_;
    public:
    HotelBookingAPI(std::string location) : location_(location) {}
    void checkCityHotels()
    {
        std::cout << "At location " << location_ << " there are the following hotels" << std::endl;
        std::cout << "1. Big Hotel - centrum" << std::endl;
        this->checkAvailability("Big Hotel");
        std::cout << "2. Small Hotel - outskirts" << std::endl;
        this->checkAvailability("Small Hotel");
    }
    void checkAvailability(std::string cityHotel)
    {
        std::cout << cityHotel << " availability: " << std::endl;
        if(cityHotel == "Big Hotel")
        {
            std::cout << "2 rooms with queens bed. 563,-" << std::endl;
            std::cout << "3 room with one bed. 453,-" << std::endl;
            std::cout << "1 penthouse with 5 beds. 1024,-" << std::endl;
        }
        else
        {
            std::cout << "1 rooms with queens bed. 234,-" << std::endl;
            std::cout << "6 room with one bed. 121,-" << std::endl;
        }
    }
    void rentARoom(std::string room, std::string hotel)
    {
        std::cout << room << " rented at "<< hotel << "." << std::endl;
    }

    void changeLocation(std::string newLocation) { this->location_ = newLocation; }
};

// Part of the complex logic
class PlaneBookingAPI
{
    private:
    std::string location_;
    public:
    PlaneBookingAPI(std::string location) : location_(location) {}
    void checkRoutes()
    {
        std::cout << "flight to " << location_ << std::endl;
        std::cout << "1. First Class (FYI3454) - free drinking etc. 993,-" << std::endl;
        std::cout << "2. Economy CLass (FUI3312) 750,-" << std::endl;
    }
    void bookFlight(std::string flightId)
    {
        std::cout << flightId << " booked." << std::endl;
    }

    void changeLocation(std::string newLocation) { this->location_ = newLocation; }

};

// Facade
class FullTravelBooking
{
    public:
    void fullBook(std::string location, std::string priceVariant)
    {
        CarRentalAPI* CRA = new CarRentalAPI(location);
        HotelBookingAPI* HBA = new HotelBookingAPI(location);
        PlaneBookingAPI* PBA = new PlaneBookingAPI(location);
        if(priceVariant == "Cheap")
        {
            CRA->listModelsAndPrice();
            CRA->rentCar("Toyota");
            HBA->checkCityHotels();
            HBA->rentARoom("1 room with single bed", "Small Hotel");
            PBA->checkRoutes();
            PBA->bookFlight("FUI3312");
        }
        else if(priceVariant == "Expensive")
        {
            CRA->listModelsAndPrice();
            CRA->rentCar("Mercedes");
            HBA->checkCityHotels();
            HBA->rentARoom("1 penthouse", "Big Hotel");
            PBA->checkRoutes();
            PBA->bookFlight("FYI3454");
        }

        delete PBA;
        delete CRA;
        delete HBA;
    }
};

// Client code & usage
void clientCode(FullTravelBooking* FTB, std::string location, std::string pricing)
{
    FTB->fullBook(location ,pricing);
}

int main()
{
    FullTravelBooking* myTravelBook = new FullTravelBooking;
    std::cout << "Now I am traveling to London!" << std::endl;
    clientCode(myTravelBook, "London", "Cheap");
    std::cout << "Because I have saved up in London I can travel to Warsaw!" << std::endl;
    clientCode(myTravelBook, "Warsaw", "Expensive");

    delete myTravelBook;
    return 0;
}