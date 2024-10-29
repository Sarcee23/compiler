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
    const int TOTAL_STATES = 6;  // q0 to q5

public:
    FiniteAutomata() {
        // Initialize transition table
        transitionTable = vector<vector<int>>(TOTAL_STATES, vector<int>(2, -1));  // -1 indicates invalid transition
        
        // Transitions for input 'a' (index 0) and 'b' (index 1)
        // First character transitions
        transitionTable[0][0] = 1;  // q0 --a--> q1 (First char is 'a')
        transitionTable[0][1] = 2;  // q0 --b--> q2 (First char is 'b')

        // Second character transitions
        transitionTable[1][0] = 3;  // q1 --a--> q3 (Read "aa")
        transitionTable[1][1] = 4;  // q1 --b--> q4 (Read "ab")
        transitionTable[2][0] = 4;  // q2 --a--> q4 (Read "ba")
        transitionTable[2][1] = 3;  // q2 --b--> q3 (Read "bb")

        // Third character transitions
        for(int i = 3; i <= 4; i++) {
            transitionTable[i][0] = transitionTable[i][1] = i;  // Stay in same state, just remember position
        }

        finalStates = vector<bool>(TOTAL_STATES, false);
        finalStates[5] = true;  // Only q5 is final state
        
        currentState = 0;
    }

    bool isValidInput(const string& input) {
        if(input.length() != 4) {
            cout << "\nERROR: Input string must be exactly 4 characters long!\n";
            return false;
        }
        for(char c : input) {
            if(c != 'a' && c != 'b') {
                return false;
            }
        }
        return true;
    }

    string getStateDescription(int state) {
        switch(state) {
            case 0: return "(Initial State)";
            case 1: return "(Read 'a')";
            case 2: return "(Read 'b')";
            case 3: return "(Read aa/bb)";
            case 4: return "(Read ab/ba)";
            case 5: return "(Final - Palindrome)";
            default: return "";
        }
    }

    int getInputIndex(char c) {
        return (c == 'a') ? 0 : 1;
    }

    bool processFinalCharacter(const string& input) {
        // Check if last two characters match the pattern for palindrome
        if(currentState == 3) {  // Read aa or bb
            if(input[0] == input[3] && input[1] == input[2]) {
                currentState = 5;
                return true;
            }
        }
        else if(currentState == 4) {  // Read ab or ba
            if(input[0] == input[3] && input[1] == input[2]) {
                currentState = 5;
                return true;
            }
        }
        return false;
    }

    bool processString(const string& input) {
        currentState = 0;
        cout << "\nTransitions:\n";
        cout << "Initial State: q" << currentState << " " << getStateDescription(currentState) << "\n";
        cout << string(50, '-') << "\n";
        cout << setw(15) << "Input Symbol" << setw(15) << "Current State" 
             << setw(15) << "Next State" << "\n";
        cout << string(50, '-') << "\n";

        // Process first three characters
        for(int i = 0; i < 3; i++) {
            int inputIdx = getInputIndex(input[i]);
            int nextState = transitionTable[currentState][inputIdx];
            
            if(nextState == -1) {
                cout << "Invalid transition encountered!\n";
                return false;
            }

            cout << setw(15) << input[i] << setw(15) << "q" + to_string(currentState) 
                 << setw(15) << "q" + to_string(nextState) << "\n";
            currentState = nextState;
        }

        // Process last character
        bool isAccepted = processFinalCharacter(input);
        cout << setw(15) << input[3] << setw(15) << "q" + to_string(currentState) 
             << setw(15) << "q" + to_string(isAccepted ? 5 : currentState) << "\n";
        
        cout << string(50, '-') << "\n";
        cout << "Final State: q" << currentState << " " << getStateDescription(currentState) << "\n\n";
        
        return isAccepted;
    }

    void printFormalDefinition() {
        cout << "\nFormal Definition of the Finite Automata:\n";
        cout << "Q = {q0, q1, q2, q3, q4, q5}, where:\n";
        for(int i = 0; i < TOTAL_STATES; i++) {
            cout << "   q" << i << " = " << getStateDescription(i) << "\n";
        }
        cout << "\nSigma(alphabet) = {a, b}\n";
        cout << "q0 = q0 (initial state)\n";
        cout << "F = {q5} (final state)\n";
        cout << "   Note: Accepts palindromes of length 4 over {a,b}\n";
        cout << "Delta (Transition function) is shown in the table below:\n\n";
    }

    void printTransitionTable() {
        cout << setw(10) << "State" << setw(10) << "Input a" << setw(10) << "Input b\n";
        cout << string(30, '-') << "\n";
        
        for(int i = 0; i < TOTAL_STATES; i++) {
            cout << setw(10) << "q" + to_string(i);
            for(int j = 0; j < 2; j++) {
                if(transitionTable[i][j] == -1)
                    cout << setw(10) << "-";
                else
                    cout << setw(10) << "q" + to_string(transitionTable[i][j]);
            }
            cout << "\n";
        }
        cout << "\nLegend:\n";
        for(int i = 0; i < TOTAL_STATES; i++) {
            cout << "q" << i << " = " << getStateDescription(i) << "\n";
        }
        cout << "\nFinal state = {q5}\n";
    }
};

int main() {
    FiniteAutomata fa;
    string input;
    
    cout << "Finite Automata for palindromes of length 4 over alphabet {a,b}\n";
    cout << "Enter a string of length 4 (using only a and b): ";
    cin >> input;

    if (!fa.isValidInput(input)) {
        cout << "\nERROR: Invalid input! String should contain only 'a' and 'b' and be exactly 4 characters long.\n";
        return 1;
    }

    bool accepted = fa.processString(input);
    cout << "String \"" << input << "\" is " << (accepted ? "ACCEPTED" : "REJECTED") << "\n";

    fa.printFormalDefinition();
    fa.printTransitionTable();

    return 0;
}
