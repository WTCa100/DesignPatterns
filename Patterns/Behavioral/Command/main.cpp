/**
 * This is an example of the Command pattern. In this pattern a request resolver (a command receiver) will get request via different request senders (invokres).
 * Each command leaves a footprint, and it's action is being stored inside a "command history" that allows the user to "undo" it's actions later on.
 * The user shall not operate directly on the receiver but rather use the invokers.
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<iostream>
#include<vector>
#include<string>
// This is an example of Command design pattern of an text editor.
// Command receiver
class TextEditor
{
    public: 
    std::string text_;
    TextEditor() { text_ = ""; }
    void deleteSegment(std::string segment)
    {
        size_t isInText = text_.find(segment);
        if(isInText != std::string::npos)
        {
            text_.erase(isInText, segment.size());
        }
        else
        {
            std::cout << "No \"" << segment << "\" in text" << std::endl;
        }
    }
    void addSegment(std::string segment)
    {
        text_ += segment;
    }
};

// Interface command
class Command
{
    protected:
    TextEditor* currentEditor_;
    std::string text_;
    public:
    Command(TextEditor* editor, std::string optionalText = "") : currentEditor_(editor), text_(optionalText) {}
    virtual bool execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

// The following are the concrete commands.
// The concrete command does not do the logic inside them, they mostly execute a different methods/functions
class CutCommand : public Command
{
    public:
    CutCommand(TextEditor* editor, std::string optionalText = "") : Command(editor, optionalText) {}
    bool execute() override
    {
        currentEditor_->deleteSegment(Command::text_);
        return 1;
    }
    void undo() override
    {
        currentEditor_->addSegment(Command::text_);
    }
};

// Another concrete command
class InsertCommand : public Command
{
    public:
    InsertCommand(TextEditor* editor, std::string optionalText = "") : Command (editor, optionalText) {}
    bool execute() override
    {
        currentEditor_->addSegment(Command::text_);
        return 1;
    }
    void undo() override
    {
        currentEditor_->deleteSegment(Command::text_);
    }
};

// This will be a storage used for undo.
class CommandHistory
{
    private:
    std::vector<Command*> listOfCommands_;
    public:
    void push(Command* newCommand) { listOfCommands_.push_back(newCommand); }
    Command* pop() 
    {
        if(listOfCommands_.empty())
        {
            return nullptr;
        }

        Command* lastCommand = listOfCommands_[listOfCommands_.size() - 1];
        listOfCommands_.pop_back(); 
        return lastCommand;
    }
    void clear() { listOfCommands_.clear(); }
};

// Command invoker 
class Button
{
    private:
    Command* buttonType_;
    public:
    Button(Command* commandType) : buttonType_(commandType) {}
    void setButton(Command* newCommand) { buttonType_ = newCommand; } 
    Command* press() { return buttonType_; }
};

// Client code
class Application
{
    public:
    TextEditor* editor_;
    CommandHistory* pastCommands_;
    Application()
    {
        editor_ = new TextEditor;
        pastCommands_ = new CommandHistory;
    }
    void executeCommand(Command* com)
    {
        if(com->execute())
        {
            pastCommands_->push(com);
        }
    }

    inline Command* lastOperation(){ return pastCommands_->pop(); }
    void run()
    {
        editor_->text_ = "Hello wordl!"; 
        std::cout << "Text: " << editor_->text_ << std::endl;
        // Create a command
        Command* cut = new CutCommand(editor_, "wordl!");
        Command* add = new InsertCommand(editor_, "world!");

        // Setup buttons
        Button* addButton = new Button(add);
        Button* cutButton = new Button(cut);
        Button* undoButton = new Button(lastOperation());

        // Execute a command
        executeCommand(addButton->press());
        executeCommand(cutButton->press());

        std::cout << "Text: " << editor_->text_ << std::endl;

        // Create another command - with bunch of text
        Command* addHistory = new InsertCommand(editor_, " Once upon a time in a lovely mountains in somewhereville...");
        addButton->setButton(addHistory);
        executeCommand(addButton->press());

        std::cout << "Text: "  << editor_->text_ << std::endl;

        // Misstake? Undo the last command
        undoButton->setButton(lastOperation());
        executeCommand(undoButton->press());

        std::cout << "Text: " << editor_->text_ << std::endl;
        
        // Deallocate
        delete cut;
        delete add;
        delete addHistory;
        delete addButton;
        delete cutButton;
        delete undoButton;
        pastCommands_->clear();
    }

    ~Application() { delete editor_; delete pastCommands_; }
};

int main()
{
    Application* software = new Application();
    software->run();
    delete software;
}