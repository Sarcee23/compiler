#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

// Print horizontal line separator
void printLine(int width) {
    for(int i = 0; i < width; i++) cout << "-";
    cout << "\n";
}

// Get transition input with validation
string getTransition(int numStates) {
    string input;
    while(true) {
        cin >> input;
        if(input == "-") return input;
        
        bool valid = true;
        for(char c : input) {
            if(c < '0' || c >= '0' + numStates) {
                valid = false;
                break;
            }
        }
        if(valid) return input;
        cout << "Invalid input! Use states 0 to " << numStates - 1 << " or '-': ";
    }
}

// Get next DFA state for given NFA states and input symbol
string getNextState(const string& currentStates, int symbol, 
                   const vector<vector<string>>& nfa) {
    set<char> nextStates;
    for(char state : currentStates) {
        int stateNum = state - '0';
        if(nfa[stateNum][symbol] != "-") {
            for(char c : nfa[stateNum][symbol]) {
                nextStates.insert(c);
            }
        }
    }
    
    if(nextStates.empty()) return "-";
    
    string result;
    for(char state : nextStates) {
        result += state;
    }
    return result;
}

int main() {
    // Get NFA details
    int numStates, numSymbols;
    cout << "Enter number of states: ";
    cin >> numStates;
    cout << "Enter number of input symbols: ";
    cin >> numSymbols;
    
    // Initialize NFA table
    vector<vector<string>> nfa(numStates, vector<string>(numSymbols));
    
    // Get NFA transitions
    cout << "\nEnter NFA Transition Table:\n";
    cout << "Use '-' for no transition and string of states (e.g., '012') for transitions\n\n";
    
    // Print header
    cout << "State\t";
    for(int i = 0; i < numSymbols; i++) 
        cout << (char)('a' + i) << "\t";
    cout << "\n";
    printLine(40);
    
    // Get transitions
    for(int i = 0; i < numStates; i++) {
        cout << i << "\t";
        for(int j = 0; j < numSymbols; j++) {
            nfa[i][j] = getTransition(numStates);
        }
    }
    
    // Print NFA table
    cout << "\nNFA Transition Table:\n";
    cout << "State\t";
    for(int i = 0; i < numSymbols; i++) 
        cout << (char)('a' + i) << "\t";
    cout << "\n";
    printLine(40);
    
    for(int i = 0; i < numStates; i++) {
        cout << i << "\t";
        for(int j = 0; j < numSymbols; j++) {
            cout << nfa[i][j] << "\t";
        }
        cout << "\n";
    }
    
    // Convert NFA to DFA
    vector<string> dfaStates;
    vector<vector<string>> dfa;
    queue<string> unprocessedStates;
    
    // Start with initial state
    dfaStates.push_back("0");
    unprocessedStates.push("0");
    
    // Process all states
    while(!unprocessedStates.empty()) {
        string currentState = unprocessedStates.front();
        unprocessedStates.pop();
        
        vector<string> transitions;
        
        // Find transitions for each symbol
        for(int symbol = 0; symbol < numSymbols; symbol++) {
            string nextState = getNextState(currentState, symbol, nfa);
            transitions.push_back(nextState);
            
            // Add new state if not already present
            if(nextState != "-" && 
               find(dfaStates.begin(), dfaStates.end(), nextState) == dfaStates.end()) {
                dfaStates.push_back(nextState);
                unprocessedStates.push(nextState);
            }
        }
        
        dfa.push_back(transitions);
    }
    
    // Print DFA table
    cout << "\nResulting DFA Transition Table:\n";
    cout << "State\t";
    for(int i = 0; i < numSymbols; i++) 
        cout << (char)('a' + i) << "\t";
    cout << "\n";
    printLine(40);
    
    for(size_t i = 0; i < dfaStates.size(); i++) {
        cout << dfaStates[i] << "\t";
        for(int j = 0; j < numSymbols; j++) {
            cout << dfa[i][j] << "\t";
        }
        cout << "\n";
    }
    
    return 0;
}