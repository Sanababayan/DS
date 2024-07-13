#include <bits/stdc++.h>
using namespace std;

#define INF 1000000000
#define MAX_SIZE 255026
typedef pair<int, int> pii;

int n, m;
char grid[1005][1005];
bool vis[1005][1005];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int getDistance(char c){
    if( c == '.' || c == 'A'){
        return 0;
    }

    if( c == 'B' || c =='C'){
        return 255026;
    }

    if( c == '*'){
        return 1;
    }

    if(c == '#'){
        return INF;
    }
    return 0;
}
void dijkstra(int sx, int sy, vector<int>& dist, vector<int>& parent) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push(make_pair(0, sx * m + sy));
    dist[sx * m + sy] = 0;
    parent[sx * m + sy] = -1;
    while (!pq.empty()) {
        int x = pq.top().second / m;
        int y = pq.top().second % m;
        pq.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

            int nd  = dist[x * m + y] + getDistance(grid[nx][ny]);

            if (nd < dist[nx * m + ny]) {
                dist[nx * m + ny] = nd;
                parent[nx * m + ny] = x * m + y;
                pq.push({nd, nx * m + ny});
            }
        }
    }
}

void makePath(int src, vector<int>& parent){
    if(src == -1){
        return;
    }
    if(grid[src / m][src % m] == '*'){
        grid[src / m][src % m] = 'o';
    }
    src = parent[src];
    makePath(src, parent);
}


int main() {
    cin >> n >> m;
    int Ax, Ay, Bx, By, Cx, Cy;
    vector<int> A(MAX_SIZE,INF);
    vector<int> B(MAX_SIZE,INF);
    vector<int> C(MAX_SIZE,INF);
    vector<int> AP(MAX_SIZE,-1);
    vector<int> BP(MAX_SIZE,-1);
    vector<int> CP(MAX_SIZE,-1);


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'A') {
                Ax = i;
                Ay = j;
            } else if (grid[i][j] == 'B') {
                Bx = i;
                By = j;
            }else if (grid[i][j] == 'C') {
                Cx = i;
                Cy = j;
            }
        }
    }

    dijkstra(Ax, Ay, A, AP);
    dijkstra(Bx, By, B, BP);
    dijkstra(Cx, Cy, C, CP);

    int result = INF;
    int temp;
    int goodIndex = -1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int index = i * m + j;
            if( grid[i][j] == 'B' || grid[i][j] == 'C'){
                continue;
            }
            if(AP[index] == INF || BP[index] == INF || CP[index] == INF) {
                continue;
            }
            int nd = getDistance(grid[i][j]);
            temp = A[index] + B[index] + C[index] - 2 * nd;
            if(temp > 0 && temp < result && AP[index] != BP[index] && BP[index] != CP[index] && CP[index] != AP[index]){
                result = temp;
                goodIndex = index;
            }
        }
    }

    if(result == INF){
        cout << "CHRISTMAS RUINED!";
    } else {
        makePath(goodIndex, AP);
        makePath(goodIndex, BP);
        makePath(goodIndex, CP);

        cout << result << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << grid[i][j];
            }
            cout << "\n";
        }
    }
    return 0;
}
