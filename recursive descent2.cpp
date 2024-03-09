#include <iostream>
#include <string>
#include <cctype> // For isalpha and isdigit

using namespace std;

/* Grammar:
E  -> TE'
E' -> +TE' | -TE' | ε
T  -> FT'
T' -> *FT' | /FT' | ε
F  -> id | num | (E)
*/

int count = 0; // Global counter to track our position in the input string
void E();
void Ed();
void T();
void Td();
void F();

string expr; // Input expression

int main() {
    cout << "Enter an expression: ";
    cin >> expr;
    expr += "$"; // Adding end marker
    E(); // Start parsing

    if (expr[count] == '$') { // If we've consumed all input correctly, count should be at the end marker
        cout << "Accepted" << endl;
    } else {
        cout << "Rejected" << endl;
    }
}

void E() {
    cout << "E->TE'" << endl;
    T();
    Ed();
}

void Ed() {
    if (expr[count] == '+') {
        count++;
        cout << "E'->+TE'" << endl;
        T();
        Ed();
    } else if (expr[count] == '-') {
        count++;
        cout << "E'->-TE'" << endl;
        T();
        Ed();
    } else {
        // epsilon transition, do nothing for E'
        cout << "E'->null" << endl;
    }
}

void T() {
    cout << "T->FT'" << endl;
    F();
    Td();
}

void Td() {
    if (expr[count] == '*') {
        count++;
        cout << "T'->*FT'" << endl;
        F();
        Td();
    } else if (expr[count] == '/') {
        count++;
        cout << "T'->/FT'" << endl;
        F();
        Td();
    } else {
        // epsilon transition, do nothing for T'
        cout << "T'->null" << endl;
    }
}

void F() {
    if (isalpha(expr[count])) { // Checking for identifier
        count++;
        cout << "F->id" << endl;
    } else if (isdigit(expr[count])) { // Checking for digit
        count++;
        cout << "F->digit" << endl;
    } else if (expr[count] == '(') {
        count++;
        cout << "F->(E)" << endl;
        E();
        if (expr[count] == ')') {
            count++;
        } else {
            cout << "Rejected" << endl;
            exit(0);
        }
    } else {
        cout << "Rejected" << endl;
        exit(0);
    }
}
