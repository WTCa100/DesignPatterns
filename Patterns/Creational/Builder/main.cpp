/**
 * This is an example implementation of the build pattern. This approach is intended mainly in software with large objects with a complex
 * construction mechanism. Here we will put our building components inside a method into the superclass and have a director that will
 * automatically set in what order a specific part of the objec has to be done.
 * @date 2023-09-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include <map>

// Concrete product 1 
class Phone
{
    public:
    // Essential information
    std::string brand;
    std::string model;
    int ramCount;
    int cameraPixelCount;
    int batteryCapacity;
    // Additional information
    std::map<std::string, std::string> additionalInfo;

    // Methods
    void showBasic()
    {
        std::cout << "Phone " << brand << " " << model << " with specs: " << std::endl;
        std::cout << "RAM: " << ramCount << "GB" << std::endl;
        std::cout << "Back camera pixel count: " << cameraPixelCount << "MP" << std::endl;
        std::cout << "Battery cappacity: " << batteryCapacity << "mAh" << std::endl; 
    }
    
    void showExtened()
    {
        if(additionalInfo.size() > 0)
        {
            std::cout << "Additional phone information: " << std::endl;
            for(auto entry : additionalInfo)
            {
                std::cout << entry.first << ": " << entry.second << std::endl;
            }
        }
    }
};

// Inteface builder
class Builder
{
    public:
    virtual void reset() = 0;
    virtual void setBrand(std::string phoneBrand) = 0;
    virtual void setModel(std::string phoneModel) = 0;
    virtual void setRamCount(int count) = 0;
    virtual void setBackCameraPixelCount(int count) = 0;
    virtual void setBatteryCapacity(int capacity) = 0;
    virtual void setWaterproof(bool isWaterproof) = 0;
    virtual void setHasFrontCamera(bool hasCameraFront) = 0;
    virtual ~Builder() {}
};

// Concrete builder
class PhoneBuilder : public Builder
{
    Phone* initPhone;
    public:
    void reset() override
    { this->initPhone = new Phone; }
    void setBrand(std::string phoneBrand) override
    { this->initPhone->brand = phoneBrand; }
    void setModel(std::string phoneModel) override
    { this->initPhone->model = phoneModel; }
    void setRamCount(int count) override
    { this->initPhone->ramCount = count; }
    void setBackCameraPixelCount(int count) override
    { this->initPhone->cameraPixelCount = count; }
    void setBatteryCapacity(int capacity) override
    { this->initPhone->batteryCapacity = capacity; }
    void setWaterproof(bool isWaterproof) override
    { isWaterproof ? this->initPhone->additionalInfo.insert(std::make_pair("Waterproof", "Yes")) : this->initPhone->additionalInfo.insert(std::make_pair("Waterproof", "No")); }
    void setHasFrontCamera(bool hasCameraFront) override
    { hasCameraFront ? this->initPhone->additionalInfo.insert(std::make_pair("Camera - front ", "Yes")) : this->initPhone->additionalInfo.insert(std::make_pair("Camera -front ", "No")); }
    Phone* getProduct()
    {
        Phone* productPhone = initPhone;
        this->reset();
        return productPhone;
    }

    PhoneBuilder() { this->reset(); }
    ~PhoneBuilder()
    { if(initPhone) { delete initPhone; } }
};

class Director
{
    private:
    Builder* concreteCreator;
    public:
    void changeBuilder(Builder* newBuilder)
    { this->concreteCreator = newBuilder; }
    void createMePhone()
    {
        this->concreteCreator->setBrand("Pear");
        this->concreteCreator->setModel("MePhone 11");
        this->concreteCreator->setRamCount(8);
        this->concreteCreator->setBackCameraPixelCount(12);
        this->concreteCreator->setBatteryCapacity(12500);
    }
    void createMePhonePro()
    {
        this->concreteCreator->setBrand("Pear");
        this->concreteCreator->setModel("MePhone 11 Pro");
        this->concreteCreator->setRamCount(12);
        this->concreteCreator->setBackCameraPixelCount(16);
        this->concreteCreator->setBatteryCapacity(12500);
        this->concreteCreator->setWaterproof(true);
        this->concreteCreator->setHasFrontCamera(true);
    }
};

void clientCode(Director* director)
{
    // Decleare builder
    PhoneBuilder* phoneSpammingMachine = new PhoneBuilder;
    // Apply it in the Director
    director->changeBuilder(phoneSpammingMachine);
    // Build the phone
    director->createMePhone();
    Phone* mePhoneNormal = phoneSpammingMachine->getProduct();

    // Interact with the product
    mePhoneNormal->showBasic();
    mePhoneNormal->showExtened();

    // Cleanup
    delete mePhoneNormal;

    // Create another phone - builder is ready to create another instance
    director->createMePhonePro();
    Phone* mePhonePro = phoneSpammingMachine->getProduct();

    // Interact again
    mePhonePro->showBasic();
    mePhonePro->showExtened();

    // Cleanup
    delete mePhonePro;

    // Creation of mePhoneNormal without director
    Phone* mePhoneNormalNoDirector; 
    phoneSpammingMachine->setBrand("Pear");
    phoneSpammingMachine->setModel("MePhone 12");
    phoneSpammingMachine->setRamCount(10);
    phoneSpammingMachine->setBackCameraPixelCount(14);
    phoneSpammingMachine->setBatteryCapacity(10250);
    mePhoneNormalNoDirector = phoneSpammingMachine->getProduct();

    mePhoneNormalNoDirector->showBasic();
    mePhoneNormalNoDirector->showExtened();

    // Delete phone object
    delete mePhoneNormalNoDirector;
    // Builders are no longer needed
    delete phoneSpammingMachine;
}

int main(int argc, char const *argv[])
{
    Director* concreteCreator = new Director;
    clientCode(concreteCreator);
    delete concreteCreator;
    return 0;
}
