//虽然路径不唯一，但使用A*算法得出结果和样例一样。而且这种人工智能在线算法，即快有省时
#include <iostream> 
#include <string>
#include <queue>
#include <cstring>
using namespace std;
struct State {
	int f, g, h; //A*算法
	int ary[9], pos;
	int hash;
	bool operator < (State tmp) const {
		return f == tmp.f ? g > tmp.g : f > tmp.f;
	} //重载小于运算符，用于优先队列
};
int fac[9] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 };
int cantor(int ary[], int n) {
	int hash = 0;
	for (int i = 0; i < n; ++i) {
		int k = 0;
		for (int j = i + 1; j < n; ++j)
			if (ary[j] < ary[i]) ++k;
		hash += k * fac[n - 1 - i];
	}
	return hash; //不加1，hash值范围为 0:n! - 1
}
const int N = 362880, des = 0;//123456789的康拓展开值
const char op[5] = "udlr"; 
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
bool vis[N]; int pre[N]; char ch[N];
int get_h(int ary[]) { //状态中每个数字到正确位置的欧式距离和作为估计值
	int res = 0;
	for (int i = 0; i < 3; ++i) //行
		for (int j = 0; j < 3; ++j) //列
			res += abs((ary[i*3+j] - 1) / 3 - i) + abs((ary[i*3+j] - 1) % 3 - j);
	return res;
}
void print(int x) {
	if (pre[x] == -1) return;
	print(pre[x]);
	cout << ch[x];
}
void Astar(State st) {
	if (st.hash == des) { cout << endl; return; }
	memset(vis, 0, sizeof vis);
	priority_queue<State> pq;
	pq.push(st);
	vis[st.hash] = true;
	pre[st.hash] = -1;
	while (!pq.empty()) {
		st = pq.top(); pq.pop();
		int x = st.pos / 3, y = st.pos % 3;
		for (int i = 0; i < 4; ++i) {			
			int xx = x + dir[i][0], yy = y + dir[i][1];
			if (xx < 0 || xx > 2 || yy < 0 || yy > 2) continue;
			State tmp = st;
			tmp.pos = xx * 3 + yy;
			swap(tmp.ary[st.pos], tmp.ary[tmp.pos]);
			tmp.hash = cantor(tmp.ary, 9);
			if (vis[tmp.hash]) continue;
			pre[tmp.hash] = st.hash;
			ch[tmp.hash] = op[i];
			vis[tmp.hash] = true;
			if (tmp.hash == des) {
				print(0); cout << endl; return;
			}
			tmp.g++;
			tmp.h = get_h(tmp.ary);
			tmp.f = tmp.g + tmp.h;
			pq.push(tmp);
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	char str[9];
	while (cin >> str[0]) {
		for (int i = 1; i < 9; ++i)
			cin >> str[i];
		State s;
		for (int i = 0; i < 9; ++i) {
			if (str[i] == 'x') {
				s.pos = i;
				s.ary[i] = 9;
			}
			else s.ary[i] = str[i] - '0';
		}
		s.g = 0; s.h = get_h(s.ary);
		s.f = s.g + s.h;
		s.hash = cantor(s.ary, 9);
		int k = 0; //通过逆序数的奇偶判断是否可解
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < i; ++j) //求第i个数前有几个大于ary[i]的数
				if (s.ary[j] != 9 && s.ary[i] < s.ary[j])
					++k; //勉强可以理解，移动一下，逆序数改变偶数值
		if(k & 1) cout << "unsolvable" << endl;
		else Astar(s);
	}

	return 0;
}
