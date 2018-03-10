#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int N = 107, inf = 0x3f3f3f3f;
struct Node {
    int a, b;
    Node (int a = inf, int b = 0):a(a), b(b){}
};
struct State {
    int x, y, t;
    State(int x, int y, int t):x(x), y(y), t(t){}
};
int n, m;
vector <vector<Node> > v;
void init() {
    v.clear(); v.resize(n + 1);
    for (int i = 1; i<= n; ++i) {
        v[i].resize(m + 1);
    }
}
int dir[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
bool vis[N][N][N * N];
int bfs(int x, int y) {
    if(x == n && y == m) return 0;
    queue<State> q;
    State st = State(x, y, 0);
    q.push(st);
    memset(vis, 0, sizeof vis);
    vis[x][y][0] = 1;
    while(!q.empty()) {
        st = q.front(); q.pop();
        for(int i = 0; i< 4; ++i) {
            x = st.x + dir[i][0], y = st.y + dir[i][1];
            if(x == n && y == m) return st.t + 1;
            if(1 <= x && x <= n && 1 <= y && y <= m && !vis[x][y][st.t + 1] &&
            (st.t + 1 < v[x][y].a || st.t + 1 > v[x][y].b)) {
                vis[x][y][st.t + 1] = 1;
                q.push(State(x, y, st.t + 1));
            }
        }
    }
    return inf;
}
int main()
{
    int t;
    while(~scanf("%d%d%d", &n, &m, &t)) {
        init();
        int x, y, a, b;
        while(t-- > 0) {
            scanf("%d%d%d%d", &x, &y, &a, &b);
            v[x][y] = Node(a, b);
        }
        printf("%d\n", bfs(1, 1));
    }

    return 0;
}

