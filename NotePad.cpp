#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>
using namespace std;

// Node structure representing each character in a line
struct Node
{
    char data;
    Node* next;
    Node* prev;
    Node(char ch) : data(ch), next(nullptr), prev(nullptr) {}
};

// LinkedList class representing a line of text
class LinkedList 
{
private:
    Node* head;
    Node* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void insertChar(char ch) 
    {
        Node* newNode = new Node(ch);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data;
            temp = temp->next;
        }
    }

    Node* getHead() { return head; }
    Node* getTail() { return tail; }
};

class TextEditor 
{
private:
    vector<LinkedList> lines;
    int currentLine;
    Node* charCursor;
    bool insertMode;

public:
    TextEditor() : currentLine(0), charCursor(nullptr), insertMode(false) {
        lines.emplace_back();
    }

    void insertChar(char ch) 
    {
        if (lines[currentLine].getHead() == nullptr) {
            lines[currentLine].insertChar(ch);
            charCursor = lines[currentLine].getTail();
        }
        else if (charCursor == nullptr) {
            lines[currentLine].insertChar(ch);
            charCursor = lines[currentLine].getTail();
        }
        else {
            Node* newNode = new Node(ch);
            newNode->next = charCursor->next;
            newNode->prev = charCursor;
            if (charCursor->next != nullptr) {
                charCursor->next->prev = newNode;
            }
            charCursor->next = newNode;
            charCursor = newNode;
        }
    }

    void moveRight() 
    {
        if (charCursor && charCursor->next != nullptr) 
        {
            charCursor = charCursor->next;
        }
    }

    void moveLeft() 
    {
        if (charCursor && charCursor->prev != nullptr)
        {
            charCursor = charCursor->prev;
        }
    }

    void moveUp() 
    {
        if (currentLine > 0) 
        {
            currentLine--;
            charCursor = lines[currentLine].getTail();
        }
    }

    void moveDown() 
    {
        if (currentLine < lines.size() - 1) 
        {
            currentLine++;
            charCursor = lines[currentLine].getTail();
        }
    }

    void displayHelp() 
    {
        cout << "---------------- EDITOR COMMANDS ---------------\n";
        cout << "|| Normal Mode:                                ||\n";
        cout << "||  i   - Enter Insert Mode                    ||\n";
        cout << "||  n    - Create New Line                     ||\n";
        cout << "||  q    - Quit Editor                         ||\n";
        cout << "|| arrows keys - Move Cursor                   ||\n";
        cout << "||                                             ||\n";
        cout << "|| Insert Mode:                                ||\n";
        cout << "||   ESC  - Exit to Normal Mode                ||\n";
        cout << "||  arrows keys - Move Cursor                  ||\n";
        cout << "||   Any other key - Insert character          ||\n";
        cout << "------------------------------------------------\n\n";
    }

    void display() 
    {
        system("cls");
        displayHelp();

        cout << "........... EDITOR WINDOW ..............\n";
        for (int i = 0; i < lines.size(); i++) 
        {
          
            if (i == currentLine) 
            {
                Node* temp = lines[i].getHead();
                while (temp != nullptr) 
                {
                    if (charCursor == temp) 
                    {
                        cout << "|"; // Cursor
                    }
                    cout << temp->data;
                    temp = temp->next;
                }
                if (charCursor == nullptr)
                {
                   cout << "|";
                }
            }
            else {
                lines[i].display();
            }
            cout << endl;
        }
        cout << ".........................................\n";
        cout << (insertMode ? "-- INSERT MODE --" : "-- NORMAL MODE --") << endl;
    }

    void newLine() {
        lines.emplace(lines.begin() + currentLine + 1, LinkedList());
        currentLine++;
        charCursor = nullptr;
    }

    void enterInsertMode() { insertMode = true; }
    void exitInsertMode() { insertMode = false; }
    bool isInsertMode() const { return insertMode; }
};

int getChar() {
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
        case 72: return 65; // Up arrow
        case 80: return 66; // Down arrow
        case 77: return 67; // Right arrow
        case 75: return 68; // Left arrow
        default: return ch + 256;
        }
    }
    return ch;
}

int main() {
    TextEditor editor;
    int command;

    while (true) {
        editor.display();
        command = getChar();

        if (command == 27) {
            editor.exitInsertMode();
            continue;
        }

        if (editor.isInsertMode()) 
        {
            switch (command) {
            case 65: editor.moveUp(); break;
            case 66: editor.moveDown(); break;
            case 67: editor.moveRight(); break;
            case 68: editor.moveLeft(); break;
            default: editor.insertChar(static_cast<char>(command)); break;
            }
        }
        else {
            switch (command) 
            {
            case 'i': editor.enterInsertMode(); break;
            case 67: editor.moveRight(); break;
            case 68: editor.moveLeft(); break;
            case 65: editor.moveUp(); break;
            case 66: editor.moveDown(); break;
            case 'n': editor.newLine(); break;
            case 'q': return 0;
            }
        }
    }
    return 0;
}