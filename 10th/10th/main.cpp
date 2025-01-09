#include <iostream>
#include <string>
#include <set>

using namespace std;

struct Compare {
    bool operator() (const string& a, const string& b) const {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    short N;
    string str;
    set<string, Compare> strs;
    cin >> N;

    for (short i = 0; i < N; ++i) {
        cin >> str;
        strs.insert(str);
    }

    for (string s : strs) {
        cout << s << '\n';
    }

    return 0;
}
