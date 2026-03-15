#include <bits/stdc++.h>
using namespace std;

struct Item {
    string lhs;
    string rhs;
};

vector<pair<string, string>> productions;
set<string> nonTerminals;

// Function to print items
void printItems(set<string> items) {
    for (auto &it : items)
        cout << it << endl;
}

// Closure function
set<string> closure(set<string> I) {
    set<string> result = I;
    bool added;

    do {
        added = false;
        set<string> temp = result;

        for (auto &item : temp) {
            int dotPos = item.find('.');
            if (dotPos == string::npos || dotPos == item.length() - 1)
                continue;

            char next = item[dotPos + 1];

            if (isupper(next)) { // Non-terminal
                for (auto &prod : productions) {
                    if (prod.first[0] == next) {
                        string newItem = prod.first + "->." + prod.second;
                        if (result.find(newItem) == result.end()) {
                            result.insert(newItem);
                            added = true;
                        }
                    }
                }
            }
        }
    } while (added);

    return result;
}

// GOTO function
set<string> gotoFunc(set<string> I, char X) {
    set<string> J;

    for (auto &item : I) {
        int dotPos = item.find('.');
        if (dotPos == string::npos || dotPos == item.length() - 1)
            continue;

        if (item[dotPos + 1] == X) {
            string moved = item;
            swap(moved[dotPos], moved[dotPos + 1]);
            J.insert(moved);
        }
    }

    return closure(J);
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (e.g., S->AA):\n";
    for (int i = 0; i < n; i++) {
        string p;
        cin >> p;

        string lhs = p.substr(0, p.find("->"));
        string rhs = p.substr(p.find("->") + 2);

        productions.push_back({lhs, rhs});
        nonTerminals.insert(lhs);
    }

    // Augmented grammar
    string start = productions[0].first;
    string newStart = start + "'";
    productions.insert(productions.begin(), {newStart, start});

    cout << "\nAugmented Grammar:\n";
    for (auto &p : productions)
        cout << p.first << " -> " << p.second << endl;

    // Initial item
    set<string> startSet;
    startSet.insert(newStart + "->." + start);

    vector<set<string>> C;
    C.push_back(closure(startSet));

    bool added;

    do {
        added = false;
        vector<set<string>> temp = C;

        for (auto &I : temp) {
            for (char X = 'A'; X <= 'Z'; X++) {
                set<string> g = gotoFunc(I, X);
                if (!g.empty() && find(C.begin(), C.end(), g) == C.end()) {
                    C.push_back(g);
                    added = true;
                }
            }
            for (char X = 'a'; X <= 'z'; X++) {
                set<string> g = gotoFunc(I, X);
                if (!g.empty() && find(C.begin(), C.end(), g) == C.end()) {
                    C.push_back(g);
                    added = true;
                }
            }
        }
    } while (added);

    // Print LR(0) items
    cout << "\nLR(0) Item Sets:\n";
    for (int i = 0; i < C.size(); i++) {
        cout << "\nI" << i << ":\n";
        printItems(C[i]);
    }

    return 0;
}