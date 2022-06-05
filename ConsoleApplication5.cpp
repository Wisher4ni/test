#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include <algorithm>
#pragma warning(disable : 4996)
using namespace std;

int n, m;
#define N 200000
#define M 2000000
int head[N], edgenum;
int low[N], dfn[N], Stack[N << 1], instack[N], add_block[N], indexx, top, iscut[N], block_cnt;
struct node
{
	int to;
	int next;
}edge[M];
void add(int u, int v)
{
	edge[edgenum].to = v;
	edge[edgenum].next = head[u];
	head[u] = edgenum++;
}
void tarjin(int u, int pre)
{
	int i, v;
	low[u] = dfn[u] = ++indexx;
	Stack[top++] = u;
	int son = 0;
	for (i = head[u]; i != -1; i = edge[i].next)
	{
		v = edge[i].to;
		if (v == pre)
			continue;
		if (!dfn[v])
		{
			son++;
			tarjin(v, u);
			if (low[u] > low[v])
				low[u] = low[v];
			if (u != pre && low[v] >= dfn[u])
			{
				iscut[u] = 1;
				add_block[u]++;
			}
		}
		else if (low[u] > dfn[v])
			low[u] = dfn[v];
	}
	if (u == pre)add_block[u] = son - 1;
	if (u == pre && son > 1)iscut[u] = 1;
}
void find_bcc(int n) {
	memset(dfn, 0, sizeof(dfn));
	memset(instack, 0, sizeof(instack));
	memset(add_block, 0, sizeof(add_block));
	memset(iscut, 0, sizeof(iscut));
	indexx = top = 0;
	block_cnt = 0;
	for (int i = 0; i < n; i++)
		if (!dfn[i])
		{
			tarjin(i, i);
			block_cnt++;
		}

}

bool cmp2(pair<int, int>a, pair<int, int>b)
{
	return a.second > b.second;
}

int main() {
	int u, v;
	cin >> n >> m;
	memset(head, -1, sizeof(head)); edgenum = 0;
	int dou = 0;
	int count = 0;
	vector<pair<int, int>> ans;
	while (cin >> u >> v)
	{
		if (u == -1 && v == -1)
			break;
		if (u == v)
			continue;
		add(u, v), add(v, u);
	}
		

	find_bcc(n);

	for (int i = 0; i < n; i++)
	if (iscut[i])
	{
		ans.emplace_back(i, block_cnt + add_block[i]);
		count++;
	}
	if(count<m)
		for(int i=0;i<n&&count<=m;i++)
			if (!iscut[i])
			{
				count++;
				ans.emplace_back(i, block_cnt + add_block[i]);
			}
	sort(ans.begin(), ans.end(), cmp2);
	for (int i=0; i<m; i++)
	{
		cout <<ans[i].first << " " << ans[i].second << endl;
	}
	return 0;
}
