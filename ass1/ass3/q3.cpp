#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#define MAX_LEN 100

using namespace std;

string buffer;
int zz = 0;

// Structure to store DFA states and their status
struct DFA {
    string states;
    int count;
};

int last_index = 0;
int symbols;

// Reset the hash map
void reset(vector<int>& ar) {
    fill(ar.begin(), ar.end(), 0);
}

// Check which States are present in the e-closure
void check(vector<int>& ar, const string& S) {
    for(char c : S) {
        int j = c - '0';  // Changed from 'A' to '0'
        ar[j]++;
    }
}

// To find new Closure States
void state(const vector<int>& ar, string& S) {
    S.clear();
    for(int j = 0; j < ar.size(); j++) {
        if(ar[j] != 0) {
            S += to_string(j);  // Changed from 'A'+j to to_string(j)
        }
    }
}

// To pick the next closure from closure set
int closure(const vector<int>& ar) {
    for(int i = 0; i < ar.size(); i++) {
        if(ar[i] == 1) return i;
    }
    return 100;
}

// Check if new DFA states can be entered in DFA table
int indexing(vector<DFA>& dfa) {
    for(int i = 0; i < last_index; i++) {
        if(dfa[i].count == 0) return 1;
    }
    return -1;
}

// Display epsilon closure
void Display_closure(int states, vector<int>& closure_ar,
                    vector<string>& closure_table,
                    vector<vector<string>>& NFA_TABLE,
                    vector<vector<string>>& DFA_TABLE) {
    for(int i = 0; i < states; i++) {
        reset(closure_ar);
        closure_ar[i] = 2;

        if(NFA_TABLE[i][symbols] != "-") {
            buffer = NFA_TABLE[i][symbols];
            check(closure_ar, buffer);
            int z = closure(closure_ar);

            while(z != 100) {
                if(NFA_TABLE[z][symbols] != "-") {
                    buffer = NFA_TABLE[z][symbols];
                    check(closure_ar, buffer);
                }
                closure_ar[z]++;
                z = closure(closure_ar);
            }
        }

        cout << "\n e-Closure (" << i << ") :\t";  // Changed from 'A'+i to i
        buffer.clear();
        state(closure_ar, buffer);
        closure_table[i] = buffer;
        cout << closure_table[i] << endl;
    }
}

// Check New States in DFA
int new_states(vector<DFA>& dfa, const string& S) {
    for(int i = 0; i < last_index; i++) {
        if(dfa[i].states == S) return 0;
    }

    dfa[last_index].states = S;
    dfa[last_index].count = 0;
    last_index++;
    return 1;
}

// Transition function from NFA to DFA
void trans(const string& S, int M, vector<string>& clsr_t, int st,
           vector<vector<string>>& NFT, string& TB) {
    vector<int> arr(st, 0);
    string temp, temp2;

    for(char c : S) {
        int j = c - '0';  // Changed from 'A' to '0'
        temp = NFT[j][M];

        if(temp != "-") {
            for(char g : temp) {
                int k = g - '0';  // Changed from 'A' to '0'
                temp2 = clsr_t[k];
                check(arr, temp2);
            }
        }
    }

    state(arr, temp);
    TB = (temp.empty() ? "-" : temp);
}

// Display DFA transition state table
void Display_DFA(int last_index, vector<DFA>& dfa_states,
                vector<vector<string>>& DFA_TABLE) {
    cout << "\n\n********************************************************\n\n";
    cout << "\t\t DFA TRANSITION STATE TABLE \t\t \n\n";
    cout << "\n STATES OF DFA :\t\t";

    for(int i = 1; i < last_index; i++)
        cout << dfa_states[i].states << ", ";
    cout << "\n";
    cout << "\n GIVEN SYMBOLS FOR DFA: \t";

    for(int i = 0; i < symbols; i++)
        cout << (char)('a' + i) << ", ";  // Changed from i to 'a'+i
    cout << "\n\n";
    cout << "STATES\t";

    for(int i = 0; i < symbols; i++)
        cout << "|" << (char)('a' + i) << "\t";  // Changed from i to 'a'+i
    cout << "\n";

    cout << "--------+-----------------------\n";
    for(int i = 0; i < zz; i++) {
        cout << dfa_states[i + 1].states << "\t";
        for(int j = 0; j < symbols; j++) {
            cout << "|" << DFA_TABLE[i][j] << " \t";
        }
        cout << "\n";
    }
}

// Function to get valid state input
string getStateInput(int states) {
    string input;
    bool valid;
    do {
        valid = true;
        cin >> input;
        if(input != "-") {
            for(char c : input) {
                if(c < '0' || c > ('0' + states - 1)) {
                    valid = false;
                    cout << "Invalid state! States should be between 0 and " 
                         << (states - 1) << endl;  // Changed from 'A'+states-1 to states-1
                    cout << "Enter again: ";
                    break;
                }
            }
        }
    } while(!valid);
    return input;
}

int main() {
    int states;
    cout << "Enter number of states: ";
    cin >> states;

    cout << "Enter number of input symbols: ";
    cin >> symbols;

    // Initialize NFA table
    vector<vector<string>> NFA_TABLE(states, vector<string>(symbols + 1));
    vector<vector<string>> DFA_TABLE(MAX_LEN, vector<string>(symbols));

    cout << "\nEnter the transition table:" << endl;
    cout << "Use '-' for no transition and numbers for states (e.g., '012' for multiple states)" << endl;
    cout << "Format: \nFor each state and symbol combination, enter the states it transitions to." << endl;
    cout << "The last column is for epsilon transitions." << endl << endl;

    // Display header
    cout << "STATE\t";
    for(int i = 0; i < symbols; i++) {
        cout << "SYMBOL " << (char)('a' + i) << "\t";  // Changed from i to 'a'+i
    }
    cout << "EPSILON\n";

    // Input transition table
    for(int i = 0; i < states; i++) {
        cout << i << "\t";  // Changed from 'A'+i to i
        for(int j = 0; j <= symbols; j++) {
            NFA_TABLE[i][j] = getStateInput(states);
        }
    }

    cout << "\n NFA STATE TRANSITION TABLE \n\n";
    cout << "STATES\t";

    for(int i = 0; i < symbols; i++)
        cout << "|" << (char)('a' + i) << "\t";  // Changed from i to 'a'+i
    cout << "eps\n";

    cout << "--------+------------------------------------\n";
    for(int i = 0; i < states; i++) {
        cout << i << "\t";  // Changed from 'A'+i to i
        for(int j = 0; j <= symbols; j++) {
            cout << "|" << NFA_TABLE[i][j] << " \t";
        }
        cout << "\n";
    }

    vector<int> closure_ar(states);
    vector<string> closure_table(states);
    vector<DFA> dfa_states(MAX_LEN);

    Display_closure(states, closure_ar, closure_table, NFA_TABLE, DFA_TABLE);

    dfa_states[last_index].states = "-";
    dfa_states[last_index].count = 1;
    last_index++;

    buffer = closure_table[0];
    dfa_states[last_index].states = buffer;
    last_index++;

    int Sm = 1, ind = 1;
    int start_index = 1;
    string T_buf;

    while(ind != -1) {
        dfa_states[start_index].count = 1;
        Sm = 0;
        
        for(int i = 0; i < symbols; i++) {
            trans(buffer, i, closure_table, states, NFA_TABLE, T_buf);
            DFA_TABLE[zz][i] = T_buf;
            Sm += new_states(dfa_states, T_buf);
        }
        
        ind = indexing(dfa_states);
        if(ind != -1)
            buffer = dfa_states[++start_index].states;
        zz++;
    }

    Display_DFA(last_index, dfa_states, DFA_TABLE);

    return 0;
}