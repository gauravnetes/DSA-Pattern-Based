#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct State {
    int r, c, d;
    bool operator==(const State& other) const {
        return r == other.r && c == other.c && d == other.d;
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int M, N;
    if (!(cin >> M >> N)) return 0;
    
    if (M == 0 || N == 0) {
        cout << "Impossible\n";
        return 0;
    }
    
    vector<string> grid(M, string(N, ' '));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }
    
    int min_lr = M, max_lr = -1, min_lc = N, max_lc = -1;
    int min_Lr = M, max_Lr = -1, min_Lc = N, max_Lc = -1;
    int K = 0;
    
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 'l') {
                min_lr = min(min_lr, i);
                max_lr = max(max_lr, i);
                min_lc = min(min_lc, j);
                max_lc = max(max_lc, j);
                K++;
            }
            if (grid[i][j] == 'L') {
                min_Lr = min(min_Lr, i);
                max_Lr = max(max_Lr, i);
                min_Lc = min(min_Lc, j);
                max_Lc = max(max_Lc, j);
            }
        }
    }
    
    if (K == 0) {
        cout << "Impossible\n";
        return 0;
    }
    
    State start, target;
    if (min_lr == max_lr) {
        start = {min_lr, min_lc, 0};
    } else {
        start = {min_lr, min_lc, 1};
    }
    
    if (min_Lr == max_Lr) {
        target = {min_Lr, min_Lc, 0};
    } else {
        target = {min_Lr, min_Lc, 1};
    }
    
    auto is_free = [&](int r, int c) {
        if (r < 0 || r >= M || c < 0 || c >= N) return false;
        return grid[r][c] != 'B';
    };
    
    auto is_valid = [&](State s) {
        if (s.d == 0) { 
            if (s.r < 0 || s.r >= M || s.c < 0 || s.c + K > N) return false;
            for (int k = 0; k < K; ++k) {
                if (!is_free(s.r, s.c + k)) return false;
            }
        } else {  
            if (s.r < 0 || s.r + K > M || s.c < 0 || s.c >= N) return false;
            for (int k = 0; k < K; ++k) {
                if (!is_free(s.r + k, s.c)) return false;
            }
        }
        return true;
    };
    
    auto check_square = [&](int top_r, int left_c) {
        if (top_r < 0 || top_r + K > M || left_c < 0 || left_c + K > N) return false;
        for (int i = 0; i < K; ++i) {
            for (int j = 0; j < K; ++j) {
                if (!is_free(top_r + i, left_c + j)) return false;
            }
        }
        return true;
    };
    
    bool visited[20][20][2] = {false};
    queue<pair<State, int>> q;
    
    q.push({start, 0});
    visited[start.r][start.c][start.d] = true;
    
    while (!q.empty()) {
        auto [u, dist] = q.front();
        q.pop();
        
        if (u == target) {
            cout << dist << "\n";
            return 0;
        }
        
        vector<State> next_states;
        
        // 1. Orthogonal Translations
        if (u.d == 0) {
            next_states.push_back({u.r - 1, u.c, 0});
            next_states.push_back({u.r + 1, u.c, 0});
            next_states.push_back({u.r, u.c - 1, 0});
            next_states.push_back({u.r, u.c + 1, 0});
        } else {
            next_states.push_back({u.r - 1, u.c, 1});
            next_states.push_back({u.r + 1, u.c, 1});
            next_states.push_back({u.r, u.c - 1, 1});
            next_states.push_back({u.r, u.c + 1, 1});
        }
        
        for (auto v : next_states) {
            // Short-circuit evaluating `v.r` preventing potential out of bounds checking in visited array 
            if (is_valid(v) && !visited[v.r][v.c][v.d]) {
                visited[v.r][v.c][v.d] = true;
                q.push({v, dist + 1});
            }
        }
        
        if (u.d == 0) {
            for (int j = 0; j < K; ++j) {
                int i1 = j;
                int i2 = K - 1 - j;
                for (int i : {i1, i2}) {
                    State v = {u.r - i, u.c + j, 1};
                    if (is_valid(v) && check_square(u.r - i, u.c)) {
                        if (!visited[v.r][v.c][v.d]) {
                            visited[v.r][v.c][v.d] = true;
                            q.push({v, dist + 1});
                        }
                    }
                }
            }
        } else {
            for (int i = 0; i < K; ++i) {
                int j1 = i;
                int j2 = K - 1 - i;
                for (int j : {j1, j2}) {
                    State v = {u.r + i, u.c - j, 0};
                    if (is_valid(v) && check_square(u.r, u.c - j)) {
                        if (!visited[v.r][v.c][v.d]) {
                            visited[v.r][v.c][v.d] = true;
                            q.push({v, dist + 1});
                        }
                    }
                }
            }
        }
    }
    
    cout << "Impossible\n";
    return 0;
}