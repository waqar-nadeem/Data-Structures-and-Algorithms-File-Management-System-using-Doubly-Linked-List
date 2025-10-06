#include<iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    string type; 
    int size;    
    string location;
    Node* prev;
    Node* next;

    Node(string name, string type, int size, string location)
        : name(name), type(type), size(size), location(location), prev(nullptr), next(nullptr) {}
};

class FileSystem {
private:
    Node* head;
    Node* tail;

public:
    FileSystem() : head(nullptr), tail(nullptr) {}

    void addItem(string name, string type, int size, string location) {
        Node* newItem = new Node(name, type, size, location);
        if (!head) {
            head = tail = newItem;
        } else {
            tail->next = newItem;
            newItem->prev = tail;
            tail = newItem;
        }
        cout << "Added " << type << ": " << name << " at location " << location << endl;
    }

    void removeItem(string name) {
        Node* temp = head;
        while (temp) {
            if (temp->name == name) {
                if (temp->prev) temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                if (temp == head) head = temp->next;
                if (temp == tail) tail = temp->prev;
                delete temp;
                cout << "Removed item: " << name << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Item not found: " << name << endl;
    }

    void navigateToNext() {
        if (head && head->next) {
            head = head->next;
            cout << "Navigated to: " << head->name << endl;
        } else {
            cout << "No more items to navigate next." << endl;
        }
    }

    void navigateToPrevious() {
        if (tail && tail->prev) {
            tail = tail->prev;
            cout << "Navigated to: " << tail->name << endl;
        } else {
            cout << "No more items to navigate previous." << endl;
        }
    }

    void displayItems() {
        if (!head) {
            cout << "No items in the system." << endl;
            return;
        }
        Node* temp = head;
        cout << "Items in the system:\n";
        while (temp) {
            cout << "Name: " << temp->name << ", Type: " << temp->type 
                 << ", Size: " << temp->size << " bytes, Location: " << temp->location << endl;
            temp = temp->next;
        }
    }
};

int main() {
    FileSystem fs;
    int choice;

    while (true) {
        cout << "\nFile Management System Menu:\n";
        cout << "1. Add File/Directory\n";
        cout << "2. Remove File/Directory\n";
        cout << "3. Navigate to Next Item\n";
        cout << "4. Navigate to Previous Item\n";
        cout << "5. Display All Files/Directories\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string name, type, location;
        int size;

        switch (choice) {
            case 1:
                cout << "Enter name of the file/directory: ";
                cin >> name;
                cout << "Enter type (file or directory): ";
                cin >> type;
                cout << "Enter size in bytes (0 for directories): ";
                cin >> size;
                cout << "Enter location: ";
                cin >> location;
                fs.addItem(name, type, size, location);
                break;
            case 2:
                cout << "Enter name of the file/directory to remove: ";
                cin >> name;
                fs.removeItem(name);
                break;
            case 3:
                fs.navigateToNext();
                break;
            case 4:
                fs.navigateToPrevious();
                break;
            case 5:
                fs.displayItems();
                break;
            case 6:
                cout << "Exiting File Management System.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
