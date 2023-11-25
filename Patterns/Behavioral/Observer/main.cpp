/**
 * This is an example implementation of the Observer design pattern. In this pattern classes are divided into receivers and senders - or subsribers and publishers.
 * Publishers send informations to their subsribers that are stored inside subscriber. Each concrete publisher has it's own set of subscribers. 
 * @date 2023-11-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<time.h>

// Subsriber interface
class Subscriber
{
    public:
    virtual void update(std::string message) = 0;
    virtual ~Subscriber() = default; 
};

// Concrete Subscriber
class ComputerSub : public Subscriber
{
    public:
    void update(std::string message) override
    { std::cout << "Notification pops on the monitor. It says " << message << std::endl; }
};

// Concrete subsriber
class PhoneSub : public Subscriber
{
    public:
    void update(std::string message) override
    { std::cout << "Push notification appeared, with text: " << message << std::endl; }
};

// Publisher Interface
class Service
{
    protected:
    std::vector<Subscriber*> subList_;
    public:
    virtual void addSub(Subscriber* subNew) { this->subList_.push_back(subNew); }
    virtual void removeSub(Subscriber* subRem)  
    {
        this->subList_.erase(std::remove(this->subList_.begin(), this->subList_.end(), subRem), this->subList_.end());

    }
    virtual void notify(std::string customMessage = "") = 0;
    virtual ~Service() { this->subList_.clear(); };
};

// Concrete Publisher
class Tweetch : public Service
{
    public:
    void notify(std::string customMessage = "")  override
    {
        std::string finalMessage = "Tweetch: ";
        customMessage.empty() ? finalMessage += "Someone just went live!" : finalMessage += customMessage;
        for(auto sub : this->subList_)
        {
            sub->update(finalMessage);
        }
    }

};

// Concrete Publisher - just like suberibers, publishers can also have an interface to implement and follow
class YouPipe : public Service
{
    public:
    void notify(std::string customMessage = "") override
    {
        std::string finalMessage = "YouPipe: ";
        customMessage.empty() ? finalMessage += "Someone just uploaded a new video!" : finalMessage += customMessage;
        for(auto sub : this->subList_)
        {
            sub->update(finalMessage);
        }
    }
};

// Event caller - this could (and should!) be also implemented as a interface
class ContentCreator
{
    private:
    std::string channelName_;
    Service* targetSite_;
    uint32_t subCount_;
    public:
    ContentCreator(std::string channelName, Service* targetSite) : channelName_(channelName), targetSite_(targetSite), subCount_(0) {}
    void makeContent(std::string action)
    {
        std::string channelPrefix = this->channelName_ + " ";
        targetSite_->notify(channelPrefix + action);
    }
    void giveSub(Subscriber* interesant)
    {
        ++subCount_;
        targetSite_->addSub(interesant);
    }
    void takeSub(Subscriber* interesant)
    {
        --subCount_;
        targetSite_->removeSub(interesant);
    }
    void showStats()
    { std::cout << "Channel: " << this->channelName_ << " with: " << this->subCount_ << " subsribers." << std::endl; }
};

// Client code
int main()
{
    // Initiate Services
    Service* tweetchService = new Tweetch;
    Service* youPipeService = new YouPipe;

    // Initiate Callers
    ContentCreator* channelCoolGames = new ContentCreator("CoolGames", youPipeService);
    ContentCreator* channelShassanBabi = new ContentCreator("ShassanBabi", tweetchService);

    // Initiate Subsribers 
    std::vector<Subscriber*> potentialSubs =
    {
        new PhoneSub, new ComputerSub, new ComputerSub, new PhoneSub, new ComputerSub, new ComputerSub, new PhoneSub, new PhoneSub
    };

    // Add subs
    for(auto subPos = 0; subPos < potentialSubs.size(); ++subPos)
    {
        if(subPos % 2 == 0) { channelCoolGames->giveSub(potentialSubs[subPos]);}
        else { channelShassanBabi->giveSub(potentialSubs[subPos]); }
    }

    // Check subs
    channelCoolGames->showStats();
    channelShassanBabi->showStats();

    // Notify
    channelCoolGames->makeContent("New viedo - building a botanical empire! ep.24");
    channelShassanBabi->makeContent("Goin' live with da bois!");

    // Cleanup
    for(auto subPos = 0; subPos < potentialSubs.size(); ++subPos)
    {
        if(subPos % 2 == 0) { channelCoolGames->takeSub(potentialSubs[subPos]);}
        else { channelShassanBabi->takeSub(potentialSubs[subPos]); }

        delete potentialSubs[subPos];
    }

    // Check subs
    channelCoolGames->showStats();
    channelShassanBabi->showStats();

    // Callers
    delete channelCoolGames;
    delete channelShassanBabi;

    // Publishers
    delete youPipeService;
    delete tweetchService;
}