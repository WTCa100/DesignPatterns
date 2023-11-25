/**
 * This is an example implementation of a Memento design pattern. This pattern allows to save a current state of a originator class - both private and public 
 * members. This enables the ability to jump from snapshot to snapshot restoring the originator state from each saved memento. This can be easliy used
 * as a "undo" solution - similar to the command pattern but with the difference of storing entire originator class and not only the command that
 * was used on it. As we are using C++ we can directly decleare a memento class inside the originator class.
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<iostream>
#include<string>
#include<vector>

// Originator
class TextEditor
{
    private:
    // State field
    std::string content_;

    public:
    // Default contructor
    TextEditor() : content_("") {}

    void addText(std::string textAp) 
    {
        std::cout << "Adding \"" << textAp << "\"" << std::endl; 
        this->content_ += textAp;
        showState();
    }
    void removeLastChar() 
    {
        std::cout << "Removing last char \"" << content_.back() << "\"" << std::endl; 
        this->content_.pop_back(); 
        showState();
    }

    void clear()
    {
        this->content_.clear();
        showState();
    }

    void showState() { std::cout << content_ << std::endl; if(content_.empty()) std::cout << "!Empty!" << std::endl; }

    // Nested class
    class Memento
    {
        private:
        // State
        std::string content_;
        public:
        Memento(std::string currentContent) : content_(currentContent) {}
        // Get state
        std::string getStateContent()  const { return this->content_; }
    };

    Memento* save()
    {
        std::cout << "Saving current: ";
        this->showState();
        return new Memento(this->content_);
    }
    void restore(Memento* snapshot)
    {
        this->content_  = snapshot->getStateContent();
        std::cout << "Restored State: ";
        this->showState();
    }
    // Setters & Getters
    void setContent (std::string contentNew) { this->content_  = contentNew; }


    std::string getContent() const { return this->content_; }
};

// Caretaker
class Caretaker
{
    std::vector<TextEditor::Memento*> snapshotHistory_;
    TextEditor* originator_;
    public:
    Caretaker(TextEditor* org) : snapshotHistory_(), originator_(org) {}
    void addSnapshot()
    {
        snapshotHistory_.push_back(originator_->save());
    }
    void undoSnapshot()
    {
        if(snapshotHistory_.empty()) return;
        originator_->restore(snapshotHistory_.back());
        snapshotHistory_.pop_back();
    }

    void showAll()
    {
        std::cout << "+----------------------+" << std::endl;
        std::cout << "| Showing all mementos |" << std::endl;
        std::cout << "+----------------------+" << std::endl;
        for(auto snapshot : snapshotHistory_)
        {
            std::cout << "Memento state: ";
            std::cout << snapshot->getStateContent() << std::endl;
        }
        std::cout << "+----------------------+" << std::endl;
        std::cout << "|          End         |" << std::endl;
        std::cout << "+----------------------+" << std::endl;
    }

};

// Client Code
int main()
{
    // Create originator
    TextEditor* wordySoftware = new TextEditor();
    // Create caretaker
    Caretaker* vmtest = new Caretaker(wordySoftware);

    // Do something on the originator
    wordySoftware->addText("Hello world!");
    // Save
    vmtest->addSnapshot();

    // Do some more
    wordySoftware->addText(" I hate mondays!");

    // Do some more and save some more
    wordySoftware->addText(" I think I am gonna go for a walk.");
    vmtest->addSnapshot();
    wordySoftware->addText(" I enjoy bacon.");
    vmtest->addSnapshot();
    wordySoftware->addText(" I don't enjoy veggies.");
    vmtest->undoSnapshot();
    wordySoftware->addText(" I do love veggies!.");
    vmtest->addSnapshot();

    // Show all snapshots.
    vmtest->showAll();

    delete vmtest;
    delete wordySoftware;

}