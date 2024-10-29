#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
using namespace std;

// Structure to represent a DFA
struct DFA {
    int states;
    int symbols;
    vector<vector<int>> transitions;
    set<int> finalStates;
    int initialState;
};

// Function to get reachable states from initial state
set<int> getReachableStates(const DFA& dfa) {
    set<int> reachable;
    queue<int> q;
    
    q.push(dfa.initialState);
    reachable.insert(dfa.initialState);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        for (int symbol = 0; symbol < dfa.symbols; symbol++) {
            int next = dfa.transitions[current][symbol];
            if (next != -1 && reachable.find(next) == reachable.end()) {
                reachable.insert(next);
                q.push(next);
            }
        }
    }
    
    return reachable;
}

// Function to check if two states are distinguishable
bool areDistinguishable(int s1, int s2, const DFA& dfa, const vector<vector<bool>>& distinguished) {
    // If one is final and other is not, they are distinguishable
    bool s1_final = dfa.finalStates.find(s1) != dfa.finalStates.end();
    bool s2_final = dfa.finalStates.find(s2) != dfa.finalStates.end();
    
    if (s1_final != s2_final) return true;
    
    // Check if they go to distinguishable states on any input
    for (int symbol = 0; symbol < dfa.symbols; symbol++) {
        int next1 = dfa.transitions[s1][symbol];
        int next2 = dfa.transitions[s2][symbol];
        
        if (next1 != next2 && distinguished[next1][next2]) {
            return true;
        }
    }
    
    return false;
}

// Function to minimize DFA
DFA minimizeDFA(const DFA& input_dfa) {
    // Step 1: Remove unreachable states
    set<int> reachable = getReachableStates(input_dfa);
    
    // Create mapping for new state numbers
    map<int, int> stateMap;
    int newStateCount = 0;
    for (int state : reachable) {
        stateMap[state] = newStateCount++;
    }
    
    // Step 2: Find distinguishable states
    vector<vector<bool>> distinguished(input_dfa.states, vector<bool>(input_dfa.states, false));
    bool changed;
    
    do {
        changed = false;
        for (int s1 = 0; s1 < input_dfa.states; s1++) {
            for (int s2 = s1 + 1; s2 < input_dfa.states; s2++) {
                if (!distinguished[s1][s2] && !distinguished[s2][s1]) {
                    if (areDistinguishable(s1, s2, input_dfa, distinguished)) {
                        distinguished[s1][s2] = distinguished[s2][s1] = true;
                        changed = true;
                    }
                }
            }
        }
    } while (changed);
    
    // Step 3: Combine equivalent states
    vector<int> stateClass(input_dfa.states, -1);
    int classCount = 0;
    
    for (int s = 0; s < input_dfa.states; s++) {
        if (reachable.find(s) == reachable.end()) continue;
        
        if (stateClass[s] == -1) {
            stateClass[s] = classCount;
            for (int t = s + 1; t < input_dfa.states; t++) {
                if (reachable.find(t) != reachable.end() && 
                    !distinguished[s][t] && !distinguished[t][s]) {
                    stateClass[t] = classCount;
                }
            }
            classCount++;
        }
    }
    
    // Create minimized DFA
    DFA min_dfa;
    min_dfa.states = classCount;
    min_dfa.symbols = input_dfa.symbols;
    min_dfa.transitions = vector<vector<int>>(classCount, vector<int>(input_dfa.symbols));
    min_dfa.initialState = stateClass[input_dfa.initialState];
    
    // Set transitions for minimized DFA
    for (int s = 0; s < input_dfa.states; s++) {
        if (reachable.find(s) == reachable.end()) continue;
        
        int oldClass = stateClass[s];
        for (int symbol = 0; symbol < input_dfa.symbols; symbol++) {
            int next = input_dfa.transitions[s][symbol];
            if (next != -1) {
                min_dfa.transitions[oldClass][symbol] = stateClass[next];
            } else {
                min_dfa.transitions[oldClass][symbol] = -1;
            }
        }
        
        if (input_dfa.finalStates.find(s) != input_dfa.finalStates.end()) {
            min_dfa.finalStates.insert(stateClass[s]);
        }
    }
    
    return min_dfa;
}

// Function to display DFA transition table
void displayDFA(const DFA& dfa) {
    cout << "\nDFA Transition Table:\n";
    cout << "State\t";
    for (int i = 0; i < dfa.symbols; i++) {
        cout << (char)('a' + i) << "\t";
    }
    cout << "Final?\n";
    
    for (int i = 0; i < dfa.states; i++) {
        cout << i << "\t";
        for (int j = 0; j < dfa.symbols; j++) {
            if (dfa.transitions[i][j] == -1) {
                cout << "-\t";
            } else {
                cout << dfa.transitions[i][j] << "\t";
            }
        }
        cout << (dfa.finalStates.find(i) != dfa.finalStates.end() ? "Yes" : "No");
        cout << "\n";
    }
}

int main() {
    DFA dfa;
    
    // Input DFA specifications
    cout << "Enter number of states: ";
    cin >> dfa.states;
    
    cout << "Enter number of symbols: ";
    cin >> dfa.symbols;
    
    // Initialize transition table
    dfa.transitions = vector<vector<int>>(dfa.states, vector<int>(dfa.symbols));
    
    // Input transitions
    cout << "\nEnter transitions (-1 for no transition):\n";
    for (int i = 0; i < dfa.states; i++) {
        cout << "For state " << i << ":\n";
        for (int j = 0; j < dfa.symbols; j++) {
            cout << "On input " << (char)('a' + j) << ": ";
            cin >> dfa.transitions[i][j];
        }
    }
    
    // Input final states
    int numFinal;
    cout << "\nEnter number of final states: ";
    cin >> numFinal;
    cout << "Enter final states: ";
    for (int i = 0; i < numFinal; i++) {
        int state;
        cin >> state;
        dfa.finalStates.insert(state);
    }
    
    // Input initial state
    cout << "Enter initial state: ";
    cin >> dfa.initialState;
    
    cout << "\nOriginal DFA:";
    displayDFA(dfa);
    
    // Minimize DFA
    DFA minimized_dfa = minimizeDFA(dfa);
    
    cout << "\nMinimized DFA:";
    displayDFA(minimized_dfa);
    
    return 0;
}