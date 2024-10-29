#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>

using namespace std;

class FiniteAutomaton {
private:
    int numStates;
    int numSymbols;
    vector<vector<set<int>>> transitions;  // Using set to store multiple transitions
    int startState;
    set<int> acceptStates;

    bool isValidState(int state) const {
        return state >= 0 && state < numStates;
    }

public:
    FiniteAutomaton(int states, int symbols) : 
        numStates(states), 
        numSymbols(symbols),
        transitions(states, vector<set<int>>(symbols)) {}

    void inputTransitions() {
        cout << "\nEnter the start state (0 to " << numStates - 1 << "): ";
        cin >> startState;
        
        int numAcceptStates;
        cout << "Enter the number of accept states: ";
        cin >> numAcceptStates;
        
        cout << "Enter the accept states: ";
        for (int i = 0; i < numAcceptStates; i++) {
            int state;
            cin >> state;
            if (isValidState(state)) {
                acceptStates.insert(state);
            }
        }

        cout << "\nEnter transitions for each state and symbol combination." << endl;
        cout << "For each transition, enter the number of target states followed by the states." << endl;
        cout << "Enter -1 for no transition." << endl;

        for (int i = 0; i < numStates; i++) {
            for (int j = 0; j < numSymbols; j++) {
                cout << "From state " << i << " with symbol '" 
                     << static_cast<char>('a' + j) << "': ";
                
                int numTargets;
                cin >> numTargets;

                if (numTargets == -1) continue;

                for (int k = 0; k < numTargets; k++) {
                    int target;
                    cin >> target;
                    if (isValidState(target)) {
                        transitions[i][j].insert(target);
                    }
                }
            }
        }
    }

    void displayTransitionTable() const {
        cout << "\nTransition Table:\n";
        cout << "State\t";
        
        // Print symbol headers
        for (int i = 0; i < numSymbols; i++) {
            cout << static_cast<char>('a' + i) << "\t";
        }
        cout << "Accept?\n";

        // Print horizontal line
        cout << string(50, '-') << endl;

        // Print transitions
        for (int i = 0; i < numStates; i++) {
            cout << i << (i == startState ? "(S)" : "") << "\t";
            
            for (int j = 0; j < numSymbols; j++) {
                if (transitions[i][j].empty()) {
                    cout << "-\t";
                } else {
                    cout << "{";
                    bool first = true;
                    for (int state : transitions[i][j]) {
                        if (!first) cout << ",";
                        cout << state;
                        first = false;
                    }
                    cout << "}\t";
                }
            }
            
            cout << (acceptStates.count(i) ? "Yes" : "No") << endl;
        }
    }

    bool isDFA() const {
        // Check if each state has exactly one transition for each symbol
        for (int i = 0; i < numStates; i++) {
            for (int j = 0; j < numSymbols; j++) {
                if (transitions[i][j].size() != 1) {
                    return false;
                }
            }
        }
        return true;
    }

    void analyzeAutomaton() const {
        cout << "\nAutomaton Analysis:\n";
        cout << string(50, '-') << endl;
        
        if (isDFA()) {
            cout << "This is a Deterministic Finite Automaton (DFA) because:\n";
            cout << "- Each state has exactly one transition for each input symbol\n";
        } else {
            cout << "This is a Non-deterministic Finite Automaton (NFA) because:\n";
            for (int i = 0; i < numStates; i++) {
                for (int j = 0; j < numSymbols; j++) {
                    if (transitions[i][j].size() != 1) {
                        cout << "- State " << i << " with symbol '" 
                             << static_cast<char>('a' + j) << "' has "
                             << (transitions[i][j].empty() ? "no" : 
                                 "multiple") << " transitions\n";
                    }
                }
            }
        }
    }
};

int main() {
    cout << "Finite Automaton Analyzer\n";
    cout << string(50, '=') << endl;

    int numStates, numSymbols;
    
    cout << "Enter number of states: ";
    cin >> numStates;
    
    cout << "Enter number of input symbols: ";
    cin >> numSymbols;

    FiniteAutomaton fa(numStates, numSymbols);
    fa.inputTransitions();
    fa.displayTransitionTable();
    fa.analyzeAutomaton();

    return 0;
}