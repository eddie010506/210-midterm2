#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
    bool isEmpty(){ // checking if list empty
        return head == nullptr;
    }
    int getSize(){// getting the number of node on the list
        int count = 0;
        Node* temp = head;
        while (temp!=nullptr){
            count++;
            temp = temp->next;
        }
        return count;

    }
    string getFront(){
        if (!isEmpty()){
            return head->data;
        }
        return "";// returning empty if the list is empty
    }
    string getBack(){
        if (!isEmpty()){
            return tail->data;
        }
        return "";// returning empty if the list is empty
    }
};
string getRandomName(const vector<string>& names){// function for getting random names
    if (names.empty()) {
        return "DefaultName";
    }
    int randomIndex = rand() % names.size();
    return names[randomIndex];
}
int main() {
    srand(time(nullptr));//getting random seed
    vector<string> names;//getting file
    ifstream nameFile("names.txt");
    string name;

    // getting each name from the file into the vector
    while (getline(nameFile, name)) {
        names.push_back(name);
    }
    nameFile.close();

    DoublyLinkedList line;

    cout << "store opens:"<<endl;

    for (int i = 0; i < 5; ++i) {
        string newCustomer = getRandomName(names);
        cout << newCustomer << " joins the line" << endl;
        line.push_back(newCustomer);
    }
    cout << "Resulting line:" << endl;
    line.print();
    cout << "-------------------------" << endl;

    for (int i =1; i<=20; ++i){
        cout << "Time step#"<< i << ":"<< endl;

        //event 1 customer is served by 40% chance
        if (!line.isEmpty() && (rand() % 100 < 40)) {
            cout << line.getFront() << " is served" << endl;
            line.pop_front();
        }
        // event 2 new customer joins the line by 60% chance
        if (rand() % 100 < 60) {
            string newCustomer = getRandomName(names);
            cout << newCustomer << " joins the line" << endl;
            line.push_back(newCustomer);
        }
        //event 3 the last customer leaves by 20% chance
        if (!line.isEmpty() && (rand() % 100 < 20)) {
            cout << line.getBack() << " (at the rear) left the line" << endl;
            line.pop_back();
        }
        //event 4 VIP customer joins the front by 10% chance
        if (rand() % 100 < 10) {
            string vipCustomer = getRandomName(names);
            cout << vipCustomer << " (VIP) joins the front of the line" << endl;
            line.push_front(vipCustomer);
        }
    }
    return 0;
}