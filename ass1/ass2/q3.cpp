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
    const int TOTAL_STATES = 5;  // q0 to q4 (including trap state)

public:
    FiniteAutomata() {
        // Initialize transition table (same as before)
        transitionTable = vector<vector<int>>(TOTAL_STATES, vector<int>(2, -1));
        
        // Initialize transitions
        transitionTable[0][0] = 1;  // q0 --0--> q1
        transitionTable[0][1] = 1;  // q0 --1--> q1
        transitionTable[1][0] = 2;  // q1 --0--> q2
        transitionTable[1][1] = 2;  // q1 --1--> q2
        transitionTable[2][0] = 3;  // q2 --0--> q3
        transitionTable[2][1] = 3;  // q2 --1--> q3
        transitionTable[3][0] = 4;  // q3 --0--> q4 (trap)
        transitionTable[3][1] = 4;  // q3 --1--> q4 (trap)
        transitionTable[4][0] = 4;  // q4 --0--> q4
        transitionTable[4][1] = 4;  // q4 --1--> q4

        finalStates = vector<bool>(TOTAL_STATES, false);
        finalStates[3] = true;  // Only q3 is final state
        
        currentState = 0;
    }

    // Other helper functions remain the same
    bool isValidInput(const string& input) {
        if(input.empty()) {
            cout << "\nERROR: Input string cannot be empty!\n";
            return false;
        }
        for(char c : input) {
            if(c != '0' && c != '1') {
                cout << "\nERROR: Input string must contain only 0's and 1's!\n";
                return false;
            }
        }
        return true;
    }

    string getStateDescription(int state) {
        switch(state) {
            case 0: return "(Initial State)";
            case 1: return "(One Digit Read)";
            case 2: return "(Two Digits Read)";
            case 3: return "(Three Digits Read - Final)";
            case 4: return "(Trap State - More than 3 digits)";
            default: return "";
        }
    }

    string getTransitionArrow(char input, int fromState, int toState) {
        return "q" + to_string(fromState) + " --" + input + "--> q" + to_string(toState);
    }

    int getInputIndex(char c) {
        return (c == '0') ? 0 : 1;
    }

    bool processString(const string& input) {
        currentState = 0;
        cout << "\nDetailed Transition Path:\n";
        cout << string(60, '=') << "\n";
        cout << "Start: q0 " << getStateDescription(0) << "\n\n";

        string currentPath = "Path: q0";
        for(char digit : input) {
            int inputIdx = getInputIndex(digit);
            int nextState = transitionTable[currentState][inputIdx];
            
            // Show transition arrow and state information
            cout << getTransitionArrow(digit, currentState, nextState) << "\n";
            cout << "Current configuration: " << currentPath << "\n";
            cout << "Reading: " << digit << "\n";
            cout << "Moving to: q" << nextState << " " << getStateDescription(nextState) << "\n";
            cout << string(40, '-') << "\n";
            
            currentState = nextState;
            currentPath += " -> q" + to_string(nextState);
        }
        
        cout << "\nFinal Path: " << currentPath << "\n";
        cout << "Ended in: q" << currentState << " " << getStateDescription(currentState) << "\n";
        cout << string(60, '=') << "\n\n";
        
        return finalStates[currentState];
    }

    void printFormalDefinition() {
        cout << "\nFormal Definition of the Finite Automata:\n";
        cout << string(50, '=') << "\n";
        cout << "Q = {q0, q1, q2, q3, q4}, where:\n";
        for(int i = 0; i < TOTAL_STATES; i++) {
            cout << "   q" << i << " = " << getStateDescription(i) << "\n";
        }
        cout << "\n Sigma (alphabet) = {0, 1}\n";
        cout << "q0 = Initial state\n";
        cout << "F = {q3} (final state)\n";
        cout << "Delta (Transition function) defined below\n";
    }

    void printTransitionTable() {
        cout << "\nTransition Table:\n";
        cout << string(70, '=') << "\n";
        
        // Header
        cout << left << setw(8) << "State" 
             << setw(35) << "Description"
             << setw(12) << "Input 0"
             << setw(12) << "Input 1" << "\n";
        cout << string(70, '-') << "\n";
        
        // Table content
        for(int i = 0; i < TOTAL_STATES; i++) {
            cout << left << setw(8) << ("q" + to_string(i))
                 << setw(35) << getStateDescription(i)
                 << setw(12) << ("q" + to_string(transitionTable[i][0]))
                 << setw(12) << ("q" + to_string(transitionTable[i][1]))
                 << "\n";
        }
        
        cout << string(70, '-') << "\n\n";
        
        // Additional information
        cout << "Valid transitions for each state:\n";
        for(int i = 0; i < TOTAL_STATES; i++) {
            cout << "From q" << i << ": ";
            cout << getTransitionArrow('0', i, transitionTable[i][0]) << ", ";
            cout << getTransitionArrow('1', i, transitionTable[i][1]) << "\n";
        }
    }

    int getDecimalValue(const string& binary) {
        if(binary.length() == 3) {
            return stoi(binary, nullptr, 2);
        }
        return -1;
    }
};

int main() {
    FiniteAutomata fa;
    string input;
    
    cout << "===== Finite Automata for 3-digit Binary Numbers =====\n";
    cout << "This FA accepts ONLY 3-digit binary numbers.\n";
    cout << "Strings longer than 3 digits will enter trap state.\n\n";
    
    cout << "Enter a binary number: ";
    cin >> input;

    if (!fa.isValidInput(input)) {
        return 1;
    }

    bool accepted = fa.processString(input);
    cout << "Result: String \"" << input << "\" is " << (accepted ? "ACCEPTED" : "REJECTED") << "\n";
    
    if (accepted) {
        cout << "Decimal value: " << fa.getDecimalValue(input) << "\n";
    }

    fa.printFormalDefinition();
    fa.printTransitionTable();

    return 0;
}