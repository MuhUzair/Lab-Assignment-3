#include <iostream>
using namespace std;

const int MAX = 100; // Maximum size of the Symbol Table

// Node class represents each record in the symbol table
class Node {
    string identifier, scope, type; // Properties of a record
    int lineNo; // Line number in the source code
    Node* next; // Pointer to the next node in the same bucket

public:
    Node() {
        next = NULL;
    }

    // Constructor to initialize a node with given properties
    Node(string key, string value, string type, int lineNo) {
        this->identifier = key;
        this->scope = value;
        this->type = type;
        this->lineNo = lineNo;
        next = NULL;
    }

    // Function to print a node's information
    void print() {
        cout << "Identifier's Name:" << identifier
             << "\nType:" << type
             << "\nScope: " << scope
             << "\nLine Number: " << lineNo << endl;
    }

    // Granting access to private members to SymbolTable class
    friend class SymbolTable;
};

// SymbolTable class represents the symbol table
class SymbolTable {
    Node* head[MAX]; // Array of pointers to Nodes

public:
    // Constructor initializes each head pointer to NULL
    SymbolTable() {
        for (int i = 0; i < MAX; i++)
            head[i] = NULL;
    }

    // Hash function to calculate hash value
    int hashf(string id);

    // Functions to insert, find, delete, and modify records
    bool insert(string id, string scope, string Type, int lineno);
    string find(string id);
    bool deleteRecord(string id);
    bool modify(string id, string scope, string Type, int lineno);
};

// Function to modify an identifier
bool SymbolTable::modify(string id, string s, string t, int l) {
    int index = hashf(id);
    Node* start = head[index];

    if (start == NULL)
        return false; // If the bucket is empty, return false

    while (start != NULL) {
        if (start->identifier == id) {
            // Update the record with new values
            start->scope = s;
            start->type = t;
            start->lineNo = l;
            return true; // Modification successful
        }
        start = start->next; // Move to the next node in the chain
    }

    return false; // Identifier not found
}

// Function to delete an identifier
bool SymbolTable::deleteRecord(string id) {
    int index = hashf(id);
    Node* tmp = head[index];
    Node* par = NULL; // Parent node pointer

    // If the bucket is empty, return false
    if (tmp == NULL) {
        return false;
    }

    // Check if the node to be deleted is the first node
    if (tmp->identifier == id) {
        head[index] = tmp->next; // Update the head to the next node
        delete tmp; // Free the deleted node
        return true;
    }

    // Search for the node to delete and keep track of the parent node
    while (tmp != NULL && tmp->identifier != id) {
        par = tmp;
        tmp = tmp->next;
    }

    // If the node was not found, return false
    if (tmp == NULL) {
        return false;
    }

    // Node found, update the parent's next pointer and delete the node
    par->next = tmp->next;
    delete tmp;
    return true;
}

// Function to find an identifier
string SymbolTable::find(string id) {
    int index = hashf(id);
    Node* start = head[index];

    // If the bucket is empty, identifier is not present
    if (start == NULL)
        return "-1";

    // Traverse the chain to find the identifier
    while (start != NULL) {
        if (start->identifier == id) {
            start->print(); // Print the record information
            return start->scope; // Return the scope of the identifier
        }
        start = start->next; // Move to the next node in the chain
    }

    return "-1"; // Identifier not found
}

// Function to insert an identifier
bool SymbolTable::insert(string id, string scope, string Type, int lineno) {
    int index = hashf(id); // Calculate the hash value
    Node* p = new Node(id, scope, Type, lineno); // Create a new node

    // If the bucket is empty, insert the new node as the first node
    if (head[index] == NULL) {
        head[index] = p;
        cout << "\n" << id << " inserted";
        return true;
    } else {
        // Traverse to the end of the chain and insert the new node
        Node* start = head[index];
        while (start->next != NULL)
            start = start->next;

        start->next = p;
        cout << "\n" << id << " inserted";
        return true;
    }

    return false; // Insertion failed (should not reach here)
}

// Hash function to calculate hash value
int SymbolTable::hashf(string id) {
    int asciiSum = 0;

    for (int i = 0; i < id.length(); i++) {
        asciiSum = asciiSum + id[i];
    }

    return (asciiSum % MAX); // Use modulo MAX to ensure within array bounds
}

// Driver code
int main() {
    SymbolTable st;
    string check;
    cout << "**** SYMBOL_TABLE ****\n";

    // insert 'if'
    if (st.insert("if", "local", "keyword", 4))
        cout << " -successfully";
    else
        cout << "\nFailed to insert.\n";

    // insert 'number'
    if (st.insert("number", "global", "variable", 2))
        cout << " -successfully\n\n";
    else
        cout << "\nFailed to insert\n";

    // find 'if'
    check = st.find("if");
    if (check != "-1")
        cout << "Identifier Is present\n";
    else
        cout << "\nIdentifier Not Present\n";

    // delete 'if'
    if (st.deleteRecord("if"))
        cout << "if Identifier is deleted\n";
    else
        cout << "\nFailed to delete\n";

    // modify 'number'
    if (st.modify("number", "global", "variable", 3))
        cout << "\nNumber Identifier updated\n";

    // find and print 'number'
    check = st.find("number");
    if (check != "-1")
        cout << "Identifier Is present\n";
    else
        cout << "\nIdentifier Not Present";

    return 0;
}
