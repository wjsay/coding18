#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 65537;
bool vis[maxn];
int ronud = 0;
int dir[5] = { 4, -4, 1, -1, 0 };//上下左右中 
int rd[maxn]; //rd[i]到达状态i时，移动的次数 
int myFlip(int bit, int state) { //翻转第bit位及其周边的棋子 
	for (int i = 0; i < 5; ++i) {
		int bt = bit + dir[i];
		if (dir[i] == 1 && bt % 4 == 0 || dir[i] == -1 && bt % 4 == 3)
			continue;
		if (-1 < bt && bt < 16) { //保证 上下中 翻转的棋子没有越界 
			if ((state >> bt) & 1)
				state -= (1 << bt);
			else state += (1 << bt);
		}
	}
	return state;
}
int BFS(int state) {
	if (state == 0 || state == (1 << 16) - 1) {
		return 0;//初始化状态就已满足要求 
	}
	int round = 0;	//多少轮翻转后可以出现状态0 or (1<<16)-1
	queue<int> que;
	que.push(state);
	memset(vis, 0, sizeof(bool) * maxn);//vis[i]为1，表示状态i已存在
	vis[state] = true;
	rd[state] = 0;
	while (!que.empty()) {
		state = que.front(); //当前活节点 
		que.pop();
		for (int bit = 15; bit >= 0; --bit) {
			int st = myFlip(bit, state);
			if (!vis[st]) {
				rd[st] = rd[state] + 1; //活节点state拓展得到的节点st
				vis[st] = true;
				if (st == 0 || st == (1 << 16) - 1)
					return rd[st];
				que.push(st);
			}
		}
	}
	return -1; //不可能完成任务 
}
int main()
{
	//freopen("data.in", "r", stdin);
	char ch;
	int state0 = 0;
	for (int i = 15; i >= 0; --i) {
		scanf(" %c", &ch);
		if (ch == 'b') {
			state0 += (1 << i);
		}
	} //读入16个棋子，状态压缩，（共1<<16个状态黑色为1） 
	int round = BFS(state0);
	if (round == -1) {
		puts("Impossible");
	}
	else {
		printf("%d\n", round);
	}
	
	return 0;
}
