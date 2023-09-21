// C++ allows multiple inheritance thus it can make our software less complex
#include <iostream>

// This is just a concrete class not related to the adapter design pattern. You could do it without it.
class Plug
{
    public: 
    int boltCount_;
    Plug() : boltCount_(2) {}
};

// Target
class EuropeanSocket
{
    public:
    virtual ~EuropeanSocket() {}
    virtual void plugIn(Plug* p)
    {
        std::cout << "Plugged successfully." << std::endl; 
    }
};

// Adaptee
class BritishSocket
{
    public:
    void plugInBritish(Plug* eS)
    {
        eS->boltCount_ != 3 ? std::cout << "Your plug does not fit into the British socket!" << std::endl : std::cout << "Plugged successfully." << std::endl;
    }
};

class SocketAdapter : public BritishSocket, public EuropeanSocket
{
    public:
    SocketAdapter() {}
    void plugIn(Plug* p) override
    {
        int tmpBoltCount = p->boltCount_;
        p->boltCount_ = 3;
        plugInBritish(p);
        p->boltCount_ = tmpBoltCount;
    }
};

void clientCode(EuropeanSocket* targetSocket, Plug* p)
{
    targetSocket->plugIn(p);
}

int main()
{
    Plug* euroPlug = new Plug;

    // Interact with target
    EuropeanSocket* euroSock = new EuropeanSocket;
    std::cout << "I will try to insert european plug into the european socket." << std::endl;
    clientCode(euroSock, euroPlug);

    // Interact with adaptee
    BritishSocket* britSock = new BritishSocket;
    std::cout << "Now I will insert my european plug into the brithish socket (clueless)." << std::endl;
    britSock->plugInBritish(euroPlug);

    // User adapter
    std::cout << "Now I will try to use adapter in order to plug in the european plug into the british socket." << std::endl;
    SocketAdapter* sA = new SocketAdapter;
    clientCode(sA, euroPlug);


    delete euroPlug;
    delete euroSock;
    delete britSock;
    delete sA;
    return 0;
}
