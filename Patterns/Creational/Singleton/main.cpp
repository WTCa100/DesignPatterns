/**
 * This is an example of the Singleton implementation. In such pattern the class can have only 1 instance of itself with global access point to it.
 * @note This is not a thread safe code.
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <map>

// An example of an application element that can be only one within the software.
class Configuration
{
    private:
    std::map<std::string, std::string> configValues_;
    protected:
    // Creation process
    static Configuration* globalConfig_;
    Configuration(std::pair<std::string, std::string> headerFields) : configValues_() { configValues_.insert(headerFields); }
    public:
    // Core Singleton functionality.
    static Configuration* getInstance()
    {
        if(globalConfig_ == nullptr)
        {
            std::cout << "No config found. Creating new one." << std::endl;
            globalConfig_ = new Configuration(std::make_pair("ConfigCreated", "true"));
        }
        else
        {
            std::cout << "Returning existing config" << std::endl;
        }

        return globalConfig_;
    }

    // Method related to function class
    void addConfig(std::string field, std::string value)
    {
        if(globalConfig_ == nullptr)
        {
            std::cout << "Cannot add config! Configuration instance is null." << std::endl;
            return;
        }
        
        globalConfig_->configValues_.insert(std::make_pair(field, value));
        std::cout << "Added " << field << " with value of " << value  << " to the config." << std::endl;
    }

    void show()
    {
        if(globalConfig_ == nullptr)
        {
            std::cout << "Cannot show config! Configuration instance is null." << std::endl;
            return;
        }

        std::cout << "Format:" << std::endl;        
        for(auto entry : globalConfig_->configValues_) 
        { 
            std::cout << entry.first << ": " << entry.second << std::endl;
        }        
    }

    // Allows for destruction of singleton pointer
    void resetInstance()
    { 
        delete globalConfig_;
        globalConfig_ = nullptr;
    }
};

Configuration* Configuration::globalConfig_ = nullptr;

void clientCode(Configuration* config)
{
    // Trying to add to config into an empty instance
    config->addConfig("WindowSize", "25px");

    // Getting the instance
    config->getInstance(); // Will create a new one

    // Get the instance again
    config->getInstance(); // Will return existing one

    // Add new configuration
    config->addConfig("WindowSize", "25px");

    // Check config
    config->show();
}

int main()
{
    Configuration* mainAppConfig = Configuration::getInstance();
    clientCode(mainAppConfig);
    mainAppConfig->resetInstance();
    return 0;
}
