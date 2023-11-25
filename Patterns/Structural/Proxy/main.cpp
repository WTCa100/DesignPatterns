/**
 * This is an example implementation of the "Proxy" deisgn pattern. This design will provide the user access to the proxy of a given server library.
 * The user instead of operaiting on a real server will ask the proxy to querry an request, this proxy will then do the logic and ask
 * the real server for a specific request if conditions are met.
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include <set>

// Interface
class ServerLib
{
    protected:
    std::set<std::pair<std::string, int>> db_; 
    public:
    virtual void showEntry(std::string name) = 0;
    virtual void addEntry(std::string name, int age) = 0;
    virtual void showAll() = 0;
    int getDbSize() { return db_.size(); }
    ~ServerLib() {}
};

// Concrete real server class
class Server : public ServerLib
{
    public:
    void showEntry(std::string name) override
    {
        for(auto entry : db_)
        {
            if(entry.first.compare(name.c_str()) == 0)
            {
                std::cout << entry.first << ":" << entry.second << std::endl;
            }
        }
    }
    void addEntry(std::string name, int age) override
    {
        try
        {
            db_.insert(std::make_pair(name, age));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    void showAll() override
    {
        uint16_t iterator = 0;
        for(auto entry : db_)
        {
            std::cout <<iterator << ":=" << entry.first << " : " << entry.second << std::endl;
            ++iterator;
        }
    }
};

// Concrete proxy server class
// Proxy handles the necessary logic and decides if it can pass the request to a real server.
class ServerProxy : public ServerLib
{
private: 
    ServerLib* serviceProvider_;
public:
    ServerProxy(ServerLib* service) : serviceProvider_(service) {}
    bool isEntryGood(std::string name, int age) { return (!(name.empty()) && (age > 2 && age < 10));}
    void showEntry(std::string name)
    {
        if(name.size() > 0)
        {
            serviceProvider_->showEntry(name);
        }
        else
        {
            std::cout << "Entry has to have a name!" << std::endl;
        }
    }
    void addEntry(std::string name, int age)
    {
        // Check entry Eligibility
        if(isEntryGood(name, age))
        {
            serviceProvider_->addEntry(name, age);
        }
        else
        {
            std::cout << "Provided arguments are invalid!" << std::endl;
        }
    }
    void showAll()
    {
        if(serviceProvider_->getDbSize() != 0)
        {
            serviceProvider_->showAll();
        }
        else
        {
            std::cout << "Database is empty." << std::endl;
        }
    }
    ~ServerProxy() { delete serviceProvider_; }
};

// Application that contains server library interface but connects to it via proxy.
// It will never make an call to a real server.
class KidsManager
{
    private:
    ServerLib* coreServ_;
    void preamble()
    {
        std::cout << "Thank you for choosing KidsManager - your handy tool for event manager, now for kids!" << std::endl;
    }
    void postamble()
    {
        std::cout << "See you next time!" << std::endl;
    }
    public:
    KidsManager(ServerLib* coreServer) : coreServ_(coreServer) { preamble(); }
    void addAtendee(std::string name, int age) 
    {
        std::cout << "Will try to add " << name << " : " << age << std::endl;
        coreServ_->addEntry(name, age);
    }
    void showAtendeeInfo(std::string name) 
    {
        std::cout << "Will try to show " << name << std::endl;
        coreServ_->showEntry(name);
    }
    void showAtendeeAll()
    {
        std::cout << "Showing all entries." << std::endl;
        coreServ_->showAll();
    }
    ~KidsManager() { delete coreServ_; postamble(); }
};

int main()
{
    // Initialize the concrete server
    ServerLib* realServer = new Server();
    // Initialize the proxy
    ServerProxy* proxyServer = new ServerProxy(realServer);
    // Initialize the client code part
    KidsManager* eventAtendeeHanlder = new KidsManager(proxyServer);
    // Do some operations
    eventAtendeeHanlder->addAtendee("Mark", 9);
    eventAtendeeHanlder->addAtendee("Twain", 3);
    eventAtendeeHanlder->addAtendee("Mary", 12);
    eventAtendeeHanlder->addAtendee("John", 5);
    eventAtendeeHanlder->showAtendeeInfo("Mary");
    eventAtendeeHanlder->showAtendeeInfo("Mark");
    eventAtendeeHanlder->showAtendeeAll();

    delete eventAtendeeHanlder;
    delete realServer;
    return 0;
}