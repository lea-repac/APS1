#include <bits/stdc++.h>
using namespace std;

// Funkcija preveri, ali niz s ujemajo z vzorcem p
bool is_match(const string &s, const string &p) {
    int n = s.size();
    int m = p.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;

    // inicializacija za zvezdico na začetku vzorca
    for (int j = 1; j <= m; ++j) {
        if (p[j-1] == '*') dp[0][j] = dp[0][j-1];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (p[j-1] == s[i-1] || p[j-1] == '?')
                dp[i][j] = dp[i-1][j-1];
            else if (p[j-1] == '*')
                dp[i][j] = dp[i][j-1] || dp[i-1][j];
        }
    }

    return dp[n][m];
}

// Funkcija poišče prvi neprazni podniz, ki ustreza vzorcu
pair<int,int> match_pattern(const string &s, const string &t) {
    int n = s.size();
    for (int start = 0; start < n; ++start) {
        for (int end = start; end < n; ++end) {
            string sub = s.substr(start, end - start + 1);
            if (is_match(sub, p)) {
                return {start, end};
            }
        }
    }
    return {-1, -1};
}

int main() {
    //pohitri branje in pisanje
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string S, T;

    for (int i = 0; i < t; ++i) {
        cin >> S >> T;
        pair<int,int> res = match_pattern(S, T);
        if (res.first == -1)
            cout << -1 << endl;
        else
            cout << res.first << " " << res.second << endl;
    }
    return 0;
}
