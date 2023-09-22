/**
 * Example implementation of composite design pattern. A composite pattern allows to split the code into a tree structure and treat each individual leaf uniformally.
 * This only works when provided hierarchy can be devided into tree structure.
 * @date 2023-09-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Common interface
class CompanyMember
{
    public:
    virtual void presentSelf() = 0;
    virtual void work() = 0;
    virtual void takeBreak() = 0;
    virtual ~CompanyMember() {}
};

class CEO : public CompanyMember
{
    protected:
    std::string startingDate_;
    int salary_;
    public:
    std::string name_;
    CEO(std::string name, std::string startDate, int salary) : name_(name), startingDate_(startDate), salary_(salary) {}
    void presentSelf() override
    {
        std::cout << "I am " << this->name_ << ". I am a CEO of this company since " << this->startingDate_ << std::endl;
    }
    void work() override
    {
        std::cout << this->name_ << " points towards the direction of where the company is going. - He has a lot of meetings developing a new strategies " << std::endl;
    }
    void takeBreak() override
    {
        std::cout << this->name_ << " goes on a trip to a tropical island of Janmayen, to refresh his mind." << std::endl;
    }
};

class HeadOfDepartament : public CEO
{
    protected:
    std::string departamentAssigned_;
    public:
    HeadOfDepartament(std::string name, std::string startDate, int salary, std::string departament) : CEO(name, startDate, salary), departamentAssigned_(departament) {}
    void presentSelf() override 
    {
        std::cout << "My name is " << this->name_ << ". I am head of the " << departamentAssigned_ << " departament. I work here since " << startingDate_ << std::endl;
    }
    void work() override
    {
        std::cout << this->name_ << " tries to develop the best strategy in departament of " << departamentAssigned_ << " in order to aquire the best quaterly result. " << std::endl;
    }
    void takeBreak() override
    {
        std::cout << this->name_ << " spends some time with his colleagues on a golf club! " << std::endl;
    }

};

class SectorManager : public HeadOfDepartament
{
    protected:
    std::string sectorAssigned_;
    public:
    SectorManager(std::string name, std::string startDate, int salary, std::string departament, std::string sector) :
    HeadOfDepartament(name, startDate, salary, departament), sectorAssigned_(sector) {}
    void presentSelf() override
    {
        std::cout << this->name_ << " here. I am a manager at " << this->sectorAssigned_ << "sector, in " << this->departamentAssigned_ <<". I work here since " << this->startingDate_ << std::endl;
    }
    void work() override
    {
        std::cout << this->name_ << " cooridinates team leaders in his sector so that each feature/service will be delivered on time." << std::endl;
    }
    void takeBreak() override
    {
        std::cout << this->name_ << " travles into a different country via plane or train." << std::endl;
    }
};

class TeamLeader : public SectorManager
{
    protected: 
    std::string teamAssigned_;
    public:
    TeamLeader(std::string name, std::string startDate, int salary, std::string departament, std::string sector, std::string team) : SectorManager(name, startDate, salary, departament, sector), teamAssigned_(team) {}
    void presentSelf() override
    {
        std::cout << "Hi! My name is " << this->name_ << " lead my team to deliver the best quality feature! I work in team " << this->teamAssigned_ << " at sector " << this->sectorAssigned_ << " in " << this->departamentAssigned_ << " departament. I also work here since " << this->startingDate_ << std::endl; 
    }
    void work() override
    {
        std::cout << this->name_ << " organizes meeting for his team, as well as helping them to maintain the best atmosphere around." << std::endl;
    }
    void takeBreak() override
    {
        std::cout << this->name_ << " loves to have a good in a movie theater, and travel from time to time." << std::endl;
    }
};

// Composite
class MembersMonitor : public CompanyMember
{
    private:
    std::vector<CompanyMember*> members_;
    public:
    // Manipulate data container.
    void add(CompanyMember* newMember) { members_.push_back(newMember); }
    void remove(CompanyMember* removeMember) 
    { 
        //Find member
        auto it = std::find(members_.begin(), members_.end(), removeMember);
        // Remove if present
        if(it != members_.end())
        {
            members_.erase(members_.begin());
            return;
        }
    }

    void removeAll()
    {
        members_.clear();
    }
    // Force every employee from within members_ to do specific task
    void presentSelf() override
    {
        for(auto member : members_)
        {
            member->presentSelf();
        }
    }
    void work() override
    {
        for(auto member : members_)
        {
            member->work();
        }
    }
    void takeBreak() override
    {
        for(auto member : members_)
        {
            member->takeBreak();
        }
    }
};

// Client code
class ClientClass
{
    public:
    MembersMonitor* companySurvailanceProgram_;

    ClientClass(MembersMonitor* csp) : companySurvailanceProgram_(csp) {}

    void loadCompany(std::vector<CompanyMember*> loadMembers)
    {
        for(auto member : loadMembers)
        {
            companySurvailanceProgram_->add(member);
        }
    }

    void survailance()
    {
        std::cout << "From January untill June & September to December this year: " << std::endl;
        companySurvailanceProgram_->work();
        std::cout << "Remainder of this year" << std::endl;
        companySurvailanceProgram_->takeBreak();
    }

    void combineCompanySelection(std::vector<CompanyMember*> newCompany)
    {
        MembersMonitor* advancedCSP = new MembersMonitor;
        for(auto member : newCompany)
        {
            advancedCSP->add(member);
            companySurvailanceProgram_->remove(member); 
        }
        
        companySurvailanceProgram_->add(advancedCSP);
        companySurvailanceProgram_->presentSelf();
        delete advancedCSP;
        
        // Here is a little work around - so we can keep the original newCopmany vector values after advancedCSP has been removed
        delete companySurvailanceProgram_;
        companySurvailanceProgram_ = new MembersMonitor;
        this->loadCompany(newCompany);
    }

    ~ClientClass() { std::cout << "Deleting client Class" << std::endl; delete companySurvailanceProgram_; }
};

const std::vector<CompanyMember*> pearCompany = 
{
    new CEO              ("Pierce Morgan",   "10-04-2011", 3253200),
    new HeadOfDepartament("Mark Cucumber",   "25-02-2010", 654000, "Innovation"),
    new HeadOfDepartament("Melinda Brown",   "28-02-2001", 654000, "Development"),
    new SectorManager    ("Rajesh Mulvai",   "13-04-2015", 243320, "Innovation",  "Future product interation"),
    new SectorManager    ("Betty Wise",      "16-07-2019", 243320, "Innovation",  "AI functionality"),
    new SectorManager    ("Berta Buldga",    "20-01-2022", 251320, "Development", "Maintnance"),
    new SectorManager    ("Henry Yugene",    "30-06-2021", 235630, "Development", "Improvement"),
    new TeamLeader       ("George Beaver",   "12-08-2020", 154240, "Innovation",  "Future product iteration", "Fast Foxes"),
    new TeamLeader       ("Dora Cheems",     "10-02-2001", 201240, "Innovation",  "AI functionality",         "Artificial Hamster"),
    new TeamLeader       ("Benjamin Oakley", "14-02-2005", 193050, "Innovation",  "AI functionality",         "Hardy Tortoise"),
    new TeamLeader       ("Veronica Blank",  "20-12-2009", 180320, "Development", "Maintanance",              "Pedantic Cat"),
    new TeamLeader       ("Mathew White",    "02-06-2010", 179900, "Development", "Improvement",              "Robotic Pigeon"),
    new TeamLeader       ("Alex Twain",      "05-03-2000", 202150, "Development", "Improvement",              "Bumble Bee")
};

int main()
{
    MembersMonitor* compositeMonitor = new MembersMonitor;
    ClientClass* secPlus = new ClientClass(compositeMonitor);

    // Fraction of company - by sector
    std::vector<CompanyMember*> pearCompanyTeamSector;
    pearCompanyTeamSector.insert(pearCompanyTeamSector.end(), pearCompany.begin() + 3, pearCompany.end());

    // operate on the sector
    std::cout << "-=========================-" << std::endl;
    std::cout << "Load the company resources." << std::endl;
    std::cout << "-=========================-" << std::endl;
    secPlus->loadCompany(pearCompanyTeamSector);
    std::cout << "-=========================-" << std::endl;
    std::cout << "Check copmany worker status" << std::endl;
    std::cout << "-=========================-" << std::endl;
    secPlus->survailance();

    // merge sector with the rest of the copmany
    std::cout << "-=========================-" << std::endl;
    std::cout << "Extend the company resources." << std::endl;    
    std::cout << "-=========================-" << std::endl;
    secPlus->combineCompanySelection(pearCompany);
    std::cout << "-=========================-" << std::endl;
    std::cout << "Check copmany worker status" << std::endl;
    std::cout << "-=========================-" << std::endl;
    secPlus->survailance();

    // Cleanup
    delete secPlus;

    for(auto member : pearCompany)
    {
        if(member)
        {
            delete member;
        }
    }
}