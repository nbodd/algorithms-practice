#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> subsets(const string& str, int index, vector<string>& sets) {
    if (index == str.size() - 1) {
        sets.push_back("");
        sets.push_back(string(&str[index]));
    } else {

        subsets(str, index+1, sets);
        int size = (int) sets.size();
        for (int j = 0; j<size; ++j) {
            sets.insert(sets.end(), str[index] + sets[j]);
        }

    }
    return sets;
}

void combinations_recurse() {
    string str = "abcdef";
    vector<string> sets;
    subsets(str, 0, sets);
    for (auto s : sets) {
        cout << s << endl;
    }
    
    cout << sets.size() << endl;
}

void combinations_backtracking(string& str, string result, int index, bool include, vector<string>& subsets) {
    if ( index < str.size()) {
        if (include) {
            result += str[index];
        }
        
        if (index == str.size() - 1) {
            subsets.push_back(result);
            return;
        }
        
        combinations_backtracking(str, result, index + 1, true, subsets);
        combinations_backtracking(str, result, index + 1, false, subsets);
    }
}

void combinations_backtracking() {
    string str = "abcde";
    vector<string> sets;
    combinations_backtracking(str, "", 0, true, sets);
    combinations_backtracking(str, "", 0, false, sets);
    
    for (auto s : sets) {
        cout << s << endl;
    }
    
    cout << sets.size() << endl;
}

vector<string> getPerms(string& str, int index) {
    vector<string> perms;
    if (index == str.size() - 1) {
        perms.push_back(&str[index]);
    } else if (index < str.size()) {
        
        vector<string> subPerms = getPerms(str, index + 1);
        char s = str[index];
        for (auto& perm : subPerms) {
            for (int i=0; i<=perm.size(); ++i) {
                string temp = perm;
                temp.insert(temp.begin() + i, s);
                perms.push_back(temp);
            }
        }
    }
    return perms;
}

void permutations() {
    string str = "abcde";
    
    vector<string> perms = getPerms(str, 0);
    for (auto& p: perms) {
        cout << p << endl;
    }
    
    cout << perms.size() << endl;
}

int main() {
    //combinations_recurse();
    //combinations_backtracking();
    permutations();
    return 0;
}