#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;


typedef unordered_map<char, int> Transition;
typedef unordered_map<int, Transition> TransitionTable;

int main() {
 
    int numStates;
    int initialState;
    vector<int> acceptingStates;
    int numSymbols;
    cout<<"Enter Number of Symbols";
    cin>>numSymbols;

   
    cout << "Enter the number of states: ";
    cin >> numStates;
    cout << "Enter the initial state: ";
    cin >> initialState;

    
    int numAcceptingStates;
    cout << "Enter the number of accepting states: ";
    cin >> numAcceptingStates;
    cout << "Enter the accepting states: ";
    for (int i = 0; i < numAcceptingStates; ++i) {
        int state;
        cin >> state;
        acceptingStates.push_back(state);
    }
     
   
    TransitionTable transitionTable;
    int numTransitions=numStates*numSymbols;
    cout << "Enter transitions in the format <current_state> <input_symbol> <next_state>:\n";
    for (int i = 0; i < numTransitions; ++i) {
        int currentState, nextState;
        char symbol;
        cin >> currentState >> symbol >> nextState;
        transitionTable[currentState][symbol] = nextState;
    }

  
    string input;
    cout << "Enter the input string: ";
    cin >> input;

    int currentState = initialState;

    for (char symbol : input) {
        if (transitionTable[currentState].count(symbol) == 0) {
            cout << "Rejected: Invalid input symbol \"" << symbol << "\"." << endl;
            return 0;
        }
        currentState = transitionTable[currentState][symbol];

    }

   
   if (find(acceptingStates.begin(), acceptingStates.end(), currentState) != acceptingStates.end())  
 {
        cout << "Accepted" << endl;
    } else {
        cout << "Rejected" << endl;
    }

    return 0;
}
