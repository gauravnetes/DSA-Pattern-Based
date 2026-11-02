// Problem Title: Secret Santa Gift Sequence
// Description
// A group of up to 26 friends (represented by uppercase English letters) are participating in a structured Secret Santa gift exchange. Every gift is uniquely associated with the person who bought it.

// You are given a set of mappings in the format X:Y, which means the gift bought by Person X must ultimately be given to Person Y. All the bought gifts are placed on a table in a specific ordered sequence.

// The rules of the exchange are as follows:

// Person A always starts first.

// On a person's turn, they pick the first available gift from the front of the table's sequence.

// The picked gift is immediately given to the person specified by the gift owner's original mapping.

// The receiver of that gift becomes the next person to take a turn.

// This process continues until the table is completely empty.

// The Objective
// A person is said to have "given their own bought gift" if, during their specific turn, the gift they pick up from the front of the table happens to be the exact gift they originally bought.

// Your task is to track the simulation and find all instances where this happens.

// Input Format
// The input consists of two distinct lines:

// Line 1: A space-separated string of mappings in the format X:Y (e.g., A:D B:C).

// Line 2: A space-separated string of characters representing the sequence of gifts on the table from front to back.

// Output Format

// Return a single continuous string containing the characters of all the people who picked their own bought gift, in the exact chronological order the events occurred.

// If no one picks their own gift, return an empty string or nothing.

// Constraints

// The number of participants (and gifts) is bounded by the 26 uppercase English letters (A to Z).

// Each person buys exactly one gift, and each gift must finally be given to one different person (no unresolved mappings).

// Example
// Input:

// Plaintext
// A:D B:C C:B D:E E:A
// B C D A E
// Output:

// Plaintext
// C
// Explanation of Example:

// Turn 1: A starts. Picks B from table. A != B. Gift B's mapping is B:C. C is next.

// Turn 2: C takes turn. Picks C from table. C == C. Match! (Output: 'C'). Gift C's mapping is C:B. B is next.

// Turn 3: B takes turn. Picks D from table. B != D. Gift D's mapping is D:E. E is next.

// Turn 4: E takes turn. Picks A from table. E != A. Gift A's mapping is A:D. D is next.

// Turn 5: D takes turn. Picks E from table. D != E. Gift E's mapping is E:A. A is next. Table is now empty. Final string is "C".


#include <iostream>
#include <unordered_map> 
#include <queue>
#include <string>
#include <sstream> 

using namespace std; 

void solve(string &res, char currPerson, unordered_map<char, char> &mappings, queue<char> &table) {
    while(!table.empty()) {
        char pickedGift = table.front();  
        table.pop(); 
        
        if(currPerson == pickedGift)    
            res += currPerson; 
        
        currPerson = mappings[pickedGift]; 
    }
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

    int t; 
    cin >> t; 

    string dummy; 
    getline(cin, dummy); 

    while(t--) {

        unordered_map<char, char> mappings; 
        queue<char> table; 
        
        string mapLine, tableLine, s; 
        
        getline(cin, mapLine); 
        getline(cin, tableLine); 
        
        stringstream ssMap(mapLine); 
        while (ssMap >> s) {
            mappings[s[0]] = s[2]; 
        }

        stringstream ssTable(tableLine); 
        while (ssTable >> s) {
            table.push(s[0]); 
        }
        
        string res = ""; 
        char currPerson = 'A'; 
        
        solve(res, currPerson, mappings, table); 
        
        if(res.empty()) {
            cout << "Output: (None)\n"; 
        } else {
            cout << "Output: " << res << "\n"; 
        }
        
    }
    return 0; 
}