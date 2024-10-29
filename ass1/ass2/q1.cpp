#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class FiniteAutomata {
private:
    vector<vector<int>> transitionTable;
    int currentState;
    vector<bool> finalStates;

public:
    FiniteAutomata() {
        transitionTable = vector<vector<int>>(4, vector<int>(2));
        
        // Transitions for input 0
        transitionTable[0][0] = 2;  // q0 -> q2
        transitionTable[1][0] = 3;  // q1 -> q3
        transitionTable[2][0] = 0;  // q2 -> q0
        transitionTable[3][0] = 1;  // q3 -> q1

        // Transitions for input 1
        transitionTable[0][1] = 1;  // q0 -> q1
        transitionTable[1][1] = 0;  // q1 -> q0
        transitionTable[2][1] = 3;  // q2 -> q3
        transitionTable[3][1] = 2;  // q3 -> q2

        finalStates = {true, true, true, false};
        currentState = 0;
    }

    bool isValidInput(const string& input) {
        for(char c : input) {
            if(c != '0' && c != '1') {
                return false;
            }
        }
        return true;
    }

    string getStateDescription(int state) {
        switch(state) {
            case 0: return "(Even 0s, Even 1s)";
            case 1: return "(Even 0s, Odd 1s)";
            case 2: return "(Odd 0s, Even 1s)";
            case 3: return "(Odd 0s, Odd 1s)";
            default: return "";
        }
    }

    bool processString(const string& input) {
        currentState = 0;
        cout << "\nTransitions:\n";
        cout << "Initial State: q" << currentState << " " << getStateDescription(currentState) << "\n";
        cout << string(50, '-') << "\n";
        cout << setw(15) << "Input Symbol" << setw(15) << "Current State" 
             << setw(15) << "Next State" << "\n";
        cout << string(50, '-') << "\n";

        for(char c : input) {
            int nextState = transitionTable[currentState][c - '0'];
            cout << setw(15) << c << setw(15) << "q" + to_string(currentState) 
                 << setw(15) << "q" + to_string(nextState) << "\n";
            currentState = nextState;
        }
        
        cout << string(50, '-') << "\n";
        cout << "Final State: q" << currentState << " " << getStateDescription(currentState) << "\n\n";
        return finalStates[currentState];
    }

    void printFormalDefinition() {
        cout << "\nFormal Definition of the Finite Automata:\n";
        cout << "States = {q0, q1, q2, q3}, where:\n";
        cout << "   q0 = (Even 0s, Even 1s)\n";
        cout << "   q1 = (Even 0s, Odd 1s)\n";
        cout << "   q2 = (Odd 0s, Even 1s)\n";
        cout << "   q3 = (Odd 0s, Odd 1s)\n\n";
        cout << "Alphabet = {0, 1}\n";
        cout << "q0 = q0 (initial state)\n";
        cout << "F = {q0, q1, q2} (final states)\n";
        cout << "   Note: These are states where either number of 0s is even OR number of 1s is even\n";
        cout << "Delta (Transition function) is shown in the table below:\n\n";
    }

    void printTransitionTable() {
        cout << setw(10) << "State" << setw(10) << "Input 0" << setw(10) << "Input 1\n";
        cout << string(30, '-') << "\n";
        
        for(int i = 0; i < 4; i++) {
            cout << setw(10) << "q" + to_string(i);
            cout << setw(10) << "q" + to_string(transitionTable[i][0]);
            cout << setw(10) << "q" + to_string(transitionTable[i][1]) << "\n";
        }
        cout << "\nDESCRIPTION:\n";
        cout << "q0 = (Even 0s, Even 1s)\n";
        cout << "q1 = (Even 0s, Odd 1s)\n";
        cout << "q2 = (Odd 0s, Even 1s)\n";
        cout << "q3 = (Odd 0s, Odd 1s)\n";
        cout << "\nFinal accepting states = {q0, q1, q2}\n";
    }
};

int main() {
    FiniteAutomata fa;
    string input;
    
    cout << "Finite Automata for strings with even number of 0s OR even number of 1s\n";
    cout << "Enter a string (containing only 0s and 1s): ";
    cin >> input;

    if (!fa.isValidInput(input)) {
        cout << "\nERROR: Invalid input! String should contain only 0s and 1s.\n";
        return 1;
    }

    bool accepted = fa.processString(input);
    cout << "String \"" << input << "\" is " 
         << (accepted ? "ACCEPTED" : "REJECTED") << "\n";

    fa.printFormalDefinition();
    fa.printTransitionTable();

    return 0;
}