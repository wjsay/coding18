#define _CRT_SECURE_NO_WARNINGS  
#include <iostream>  
#include <string>  
#include <queue>  
#include <cstring>
using namespace std;
#define FF 0xFFFFFFFF  
typedef pair<int, int> type;
int state = 0, des, len;
bool vis[16777216];//2^24  
int BFS(int st, int dep) {
	if (st == des) return dep;
	queue<type> q;
	q.push(make_pair(st, dep));
	memset(vis, 0, sizeof vis);
	vis[st] = true;
	while (!q.empty()) {
		type sta = q.front(); q.pop();
		st = sta.first;
		for (int i = 1; i < len; ++i) { //7 6 5 4 3 2 1 0//i是截取位  
			int x = 0x3f << (i - 1) * 3;//6个1  
										//cout << oct << x << endl;  
			x = (x & st) >> (i - 1) * 3;//截取6位  
			long long high = st >> (i + 1) * 3 << (i + 1) * 3;//剩余高位  
			int low = (int)(((long long)st << (32 - (i - 1) * 3) & FF) >> (32 - (i - 1) * 3)); //想要的溢出  
																							   //cout << i << " " << oct << st << " " << oct << x << " " << oct << high << " " << oct << low << endl;//debug  
			for (int in = 0; in <= len; ++in) { //in是插入位  
				if (in == i + 1 || in == i || in == i - 1) continue; //在三个位置插入没意义  
				int stat;
				if (in < i) {
					int lower = (int)(((long long)low << (32 - in * 3) & FF) >> (32 - in * 3));
					//cout << oct << lower << endl;  
					stat = low >> in * 3 << in * 3 + 6; // cout << oct << stat << endl;  
					stat |= high; // cout << oct << stat << endl;  
					stat |= x << in * 3; // cout << oct << stat << endl;  
					stat |= lower;
				}
				else { // in > i 在左边插入  
					int lower = (int)((high << (32 - in * 3) & FF) >> (38 - in * 3));
					//cout << oct << lower << endl;//需要的是逻辑右移  
					stat = high >> in * 3 << in * 3;
					stat |= x << (in - 2) * 3;
					stat |= lower;
					stat |= low;
				}
				//cout << oct << stat << endl;  
				if (!vis[stat]) {
					if (stat == des) return sta.second + 1;
					vis[stat] = true;
					q.push(make_pair(stat, sta.second + 1));
				}
			}
		}
	}
	return -1;
}
int main()
{
	//freopen("D:/coding/Dev/data.in", "r", stdin);  
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		string str;
		cin >> str;
		len = str.length();
		state = des = 0;
		for (int i = 0; i < len; ++i) {
			state |= (str[len - 1 - i] - '1') << (i * 3);
			des |= i << ((len - 1 - i) * 3);
		}
		//cout << oct << state << " " << oct << des << endl;//debug       
		cout << BFS(state, 0) << endl;
	}

	return 0;
}
