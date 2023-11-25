/**
 * This is an example implementation of the "Flyweight" deisgn pattern. It reduced the ammount of RAM that each object consumes.
 * This is done by separating some of the concrete class members into a mutable class and the rest into a not mutable class.
 * This later allows to create a multiple objects with the same instance of repetetive characteristics.
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include <vector>

enum ItemStyle
{
    artDeco = 0,
    vintage = 1,
    modern  = 2
};

// Unique state - mutable
class ItemType
{
    public:
    std::string name_;    // Or we can add a unique name to it
    std::string texture_; // We can change texture of a given item
    int value_;
    ItemType(std::string name, std::string texture, int value) : name_(name), value_(value), texture_(texture) {}
    void displayDetails()
    {
        std::cout << "This is " << this->name_ << ". It has " << this->texture_ << " texture. Cost: " << this->value_ << std::endl;
    }
};

// Object creator
class ItemFactory
{
    std::vector<ItemType*> listOfItems_;
    public:
    ItemFactory()
    {
        listOfItems_.push_back(new ItemType("Couch", "Comb", 250));
        listOfItems_.push_back(new ItemType("Bed", "Cozy", 420));
        listOfItems_.push_back(new ItemType("TV", "Smooth", 2400));
        listOfItems_.push_back(new ItemType("Chair", "Sand Swirl", 25));
        listOfItems_.push_back(new ItemType("Table", "Sand Swirl", 100));
        listOfItems_.push_back(new ItemType("Plant", "Coarse", 10));
        listOfItems_.push_back(new ItemType("Shelf", "Comb", 125));
        listOfItems_.push_back(new ItemType("Door", "Smooth", 130));
        listOfItems_.push_back(new ItemType("Desk", "Comb", 155));
    }
    ItemType* getItemType(std::string name) 
    {
        for( auto concreteItem : listOfItems_)
        {
            if(concreteItem->name_ == name)
            {
                return concreteItem;
            }
        }

        std::cout << "No such item was found!" << std::endl;
        return nullptr;
    }
    ~ItemFactory()
    {
        for(auto destroyItem : listOfItems_)
        { delete destroyItem; }
    }
};

// Repetetive state - not mutable
class Item
{
    private:
    int x_, y_;         // Once an item is placed it cannot be moved.
    ItemStyle style_;   // If a style is choosen, no other style can be assign to this specific object.
    ItemType* conItem_; // Gives refference to a unique item state
    public:
    Item(int coordX, int coordY, ItemStyle style, ItemType* type) : x_(coordX), y_(coordY), style_(style), conItem_(type) {}
    void display()
    {
        std::cout <<"Location: " << this->x_ << ":" << this->y_ << std::endl;
        std::cout <<"In style: ";
        switch (this->style_)
        {
        case ItemStyle::artDeco:
            std::cout << "art deco.";
            break;
        case ItemStyle::vintage:
            std::cout << "vintage.";
            break;
        case ItemStyle::modern:
            std::cout << "modern.";
            break;
        } 
        std::cout<<std::endl;
        this->conItem_->displayDetails();
    }
};

class ClientCodeRoom
{
    private:
    std::vector<Item*> roomItems_;
    ItemFactory* itemCreator_;
    public:
    ClientCodeRoom(ItemStyle entranceStyle)
    {
        itemCreator_ = new ItemFactory;
        roomItems_.push_back(new Item(0, 0, entranceStyle, itemCreator_->getItemType("Door")));
    }

    void addItem(int cX, int cY, ItemStyle style, std::string itemType)
    {
        ItemType* newItem = itemCreator_->getItemType(itemType);
        if(newItem)
        {
            roomItems_.push_back(new Item(cX, cY, style, newItem));
        }
        else
        {
            std::cout << "Please provide a valid item instance" << std::endl;
        }
    }

    void showRoom()
    {
        std::cout << "!!!Notify: Displaying room:" << std::endl; 
        for(auto itemEntry : roomItems_)
        {
            itemEntry->display();
        }
    }

    ~ClientCodeRoom()
    {
        if(itemCreator_)
        { delete itemCreator_; }

        for(auto roomElement : roomItems_)
        {
            delete roomElement;
        }
    }
};

int main()
{
    std::cout << "Today I will setup my room!" << std::endl;
    ClientCodeRoom *myRoom = new ClientCodeRoom(ItemStyle::modern);
    std::cout << "Ok, so first thing first, let's put a bed!" << std::endl;
    myRoom->addItem(12, 10, ItemStyle::artDeco, "Bed");
    std::cout << "Now, lets get myself a new desk!" << std::endl;
    myRoom->addItem(20, 10, ItemStyle::vintage, "Desk");
    std::cout << "Of course I needd a chair to work on my desk." << std::endl;
    myRoom->addItem(20, 9, ItemStyle::artDeco, "Chair");
    std::cout << "I shall have some shelves so I can put my clothes somewhere." << std::endl;
    myRoom->addItem(10, -10, ItemStyle::modern, "Shelf");
    myRoom->addItem(10, -10, ItemStyle::modern, "Shelf");
    myRoom->addItem(10, -10, ItemStyle::modern, "Shelf");
    std::cout << "Lastly, I've always wanted a TV in my room!" << std::endl;
    myRoom->addItem(25, 0, ItemStyle::modern, "TV");
    std::cout << "I love this, let's see how my room looks like!" << std::endl;
    myRoom->showRoom();

    delete myRoom;
}