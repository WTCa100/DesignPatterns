/**
 * This is an example implementation of adapter structural design pattern. Here an adapter class will be used in order to make 2 incompatible classes
 * copmatible again.
 * @date 2023-09-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <time.h>

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
    void plugIn(Plug* eS)
    {
        eS->boltCount_ != 3 ? std::cout << "Your plug does not fit into the British socket!" << std::endl : std::cout << "Plugged successfully." << std::endl;
    }
};

// Adapter
class SocketAdapter : public EuropeanSocket
{
    private:
    BritishSocket* socketAdaptee_;
    public:
    SocketAdapter(BritishSocket* adaptee) : socketAdaptee_(adaptee) {} 
    void plugIn(Plug* p)
    {
        // Tmp store value of the bolts count
        int tmpBoltCount = p->boltCount_;
        // Insert a adapter onto socket and increase the bolt count
        ++p->boltCount_;
        // Insert
        socketAdaptee_->plugIn(p);
        // Remove adapter after working
        p->boltCount_ = tmpBoltCount;
    }
};

void clientCode(EuropeanSocket* socket, Plug* plug)
{
    socket->plugIn(plug);
}

int main()
{
    Plug* euroPlug = new Plug;
    EuropeanSocket* euroSock = new EuropeanSocket;
    BritishSocket* britSock = new BritishSocket;

    std::cout << "I will try to insert european plug into the european socket." << std::endl;
    clientCode(euroSock, euroPlug);

    std::cout << "Now I will insert my european plug into the brithish socket (clueless)." << std::endl;
    britSock->plugIn(euroPlug);

    std::cout << "Now I will try to use adapter in order to plug in the european plug into the british socket." << std::endl;
    SocketAdapter* sA = new SocketAdapter(britSock);
    clientCode(sA, euroPlug);

    delete euroPlug;
    delete euroSock;
    delete britSock;
    delete sA;
    return 0;
}
