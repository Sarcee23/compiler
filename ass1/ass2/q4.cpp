#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Function to compute union of two sets
vector<string> computeUnion(const vector<string>& A, const vector<string>& B) {
    vector<string> result;
    result.insert(result.end(), A.begin(), A.end());
    result.insert(result.end(), B.begin(), B.end());
    
    // Remove duplicates if any
    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());
    return result;
}

// Function to compute concatenation of two sets
vector<string> computeConcatenation(const vector<string>& A, const vector<string>& B) {
    vector<string> result;
    for(const auto& a : A) {
        for(const auto& b : B) {
            result.push_back(a + b);
        }
    }
    return result;
}

// Function to compute (BA)* up to n iterations
vector<string> computeBAstar(const vector<string>& B, const vector<string>& A, int n) {
    vector<string> result = {""};  // Empty string is always part of Kleene star
    vector<string> BA = computeConcatenation(B, A);
    
    vector<string> current = BA;
    for(int i = 1; i <= n; i++) {
        // Add current iteration to result
        result.insert(result.end(), current.begin(), current.end());
        
        // Compute next iteration
        vector<string> next;
        for(const auto& str : current) {
            for(const auto& ba : BA) {
                next.push_back(str + ba);
            }
        }
        current = next;
    }
    return result;
}

// Function to print a set with proper formatting
void printSet(const string& setName, const vector<string>& set) {
    cout << setName << " = { ";
    for(size_t i = 0; i < set.size(); i++) {
        cout << set[i];
        if(i < set.size() - 1) cout << ", ";
    }
    cout << " }" << endl;
}

int main() {
    // Define sets A and B
    vector<string> A = {"big", "small"};
    vector<string> B = {"long", "short"};
    
    // Print original sets
    cout << "\nOriginal Sets:" << endl;
    cout << "-------------" << endl;
    printSet("A", A);
    printSet("B", B);
    
    // i) Compute and print A U B
    cout << "\ni) A U B (Union):" << endl;
    cout << "----------------" << endl;
    vector<string> unionResult = computeUnion(A, B);
    printSet("A U B", unionResult);
    
    // ii) Compute and print A o B (Concatenation)
    cout << "\nii) A o B (Concatenation):" << endl;
    cout << "------------------------" << endl;
    vector<string> concatResult = computeConcatenation(A, B);
    printSet("A o B", concatResult);
    
    // iii) Compute and print (BA)*
    cout << "\niii) (BA)* Kleene Star Operation: (Enter number of iterations):" << endl;
    cout << "------------------------------------" << endl;
    int n;
    cout << "Enter the number of iterations for (BA)*: ";
    cin >> n;
    
    vector<string> baStarResult = computeBAstar(B, A, n);
    cout << "\nComputing (BA)* up to " << n << " iterations:" << endl;
    printSet("(BA)*", baStarResult);
    
    return 0;
}