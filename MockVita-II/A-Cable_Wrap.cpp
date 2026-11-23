#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std; 

int N, M; 
int netWinding = 0; 
vector<vector<int>> dir{{-1, 0}, {0, -1}, {1, 0}, {0, 1}}; 

void dfs(vector<string> &grid, int r, int c, vector<vector<bool>> &vis, bool isRodHorizontal, int rodIdx) {
    vis[r][c] = true; 
    for(auto &d : dir) {
        int _r = r + d[0]; 
        int _c = c + d[1]; 

        if(_r >= 0 && _r < N && _c >= 0 && _c < M) {
            if(isRodHorizontal && (r == rodIdx || _r == rodIdx) && d[0] == 0) continue; 
            if(!isRodHorizontal && (c == rodIdx || _c == rodIdx) && d[1] == 0) continue; 

            char cell = grid[_r][_c]; 
            if(!vis[_r][_c] && (cell == 'C' || cell == 'R')) {
                if(cell == 'R') {
                    if(isRodHorizontal && _r != rodIdx) continue; 
                    if(!isRodHorizontal && _c != rodIdx) continue; 
                }

                if(isRodHorizontal && _r == rodIdx) {
                    int dirMod = d[0]; 
                    int layerMod = (cell == 'C') ? 1 : -1; 
                    netWinding += (dirMod * layerMod); 
                } else if(!isRodHorizontal && _c == rodIdx) {
                    int dirMod = d[1]; 
                    int layerMod = (cell == 'C') ? 1 : -1; 
                    netWinding += (dirMod * layerMod); 
                }

                dfs(grid, _r, _c, vis, isRodHorizontal, rodIdx); 
                return; 
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 

    if(!(cin >> N >> M)) return 0;
    
    vector<string> grid(N, string(M, ' ')); 
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> grid[i][j]; 
        }
    }

    bool isRodHorizontal = false; 
    int rodIdx = -1; 

    for(int i = 0; i < N; i++) {
        int rodCnt = 0, dotCnt = 0; 
        for(int j = 0; j < M; j++) {
            if(grid[i][j] == 'R') rodCnt++; 
            if(grid[i][j] == '.') dotCnt++; 
        }
        if(rodCnt >= 1 && dotCnt == 0) {
            isRodHorizontal = true; 
            rodIdx = i; 
            break; 
        }
    }

    if(!isRodHorizontal) {
        for(int j = 0; j < M; j++) {
            int rodCnt = 0, dotCnt = 0; 
            for(int i = 0; i < N; i++) {
                if(grid[i][j] == 'R') rodCnt++; 
                if(grid[i][j] == '.') dotCnt++; 
            }
            if(rodCnt >= 1 && dotCnt == 0) {
                isRodHorizontal = false; 
                rodIdx = j; 
                break; 
            }
        }
    }

    auto isEnd = [&](int r, int c) {
        int deg = 0; 
        for(auto &d : dir) {
            int nr = r + d[0], nc = c + d[1]; 
            if(nr >= 0 && nr < N && nc >= 0 && nc < M) {
                if(isRodHorizontal && (r == rodIdx || nr == rodIdx) && d[0] == 0) continue; 
                if(!isRodHorizontal && (c == rodIdx || nc == rodIdx) && d[1] == 0) continue; 
                if(grid[nr][nc] == 'C' || (grid[nr][nc] == 'R' && ((isRodHorizontal && nr == rodIdx) || (!isRodHorizontal && nc == rodIdx)))) {
                    deg++; 
                }
            }
        }
        return deg == 1; 
    };

    int sr = -1, sc = -1; 
    for(int j = 0; j < M; j++) {
        if(grid[0][j] == 'C' && (!isRodHorizontal || rodIdx != 0) && (isRodHorizontal || rodIdx != j) && isEnd(0, j)) {
            sr = 0; 
            sc = j; 
        }
        if(grid[N-1][j] == 'C' && (!isRodHorizontal || rodIdx != N-1) && (isRodHorizontal || rodIdx != j) && isEnd(N-1, j)) {
            sr = N-1; 
            sc = j; 
        }
    }

    for(int i = 0; i < N; i++) {
        if(grid[i][0] == 'C' && (isRodHorizontal || rodIdx != 0) && (!isRodHorizontal || rodIdx != i) && isEnd(i, 0)) {
            sr = i; 
            sc = 0; 
        }
        if(grid[i][M-1] == 'C' && (isRodHorizontal || rodIdx != M-1) && (!isRodHorizontal || rodIdx != i) && isEnd(i, M-1)) {
            sr = i; 
            sc = M-1; 
        }
    }

    vector<vector<bool>> vis(N, vector<bool>(M, false)); 
    if(sr != -1) 
        dfs(grid, sr, sc, vis, isRodHorizontal, rodIdx); 

    cout << abs(netWinding) / 2 << "\n";
    
    return 0; 
}