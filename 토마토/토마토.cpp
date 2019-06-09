#include<stdio.h>
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
int m, n;
int box[1000][1000];
bool visited[1000][1000];
int days[1000][1000];

queue< pair<int,int> > q;//벡터를 사용하면 시간초과남
void bfs(int x, int y) {
	
	int a[4] = { x - 1,x + 1,x,x };
	int b[4] = { y,y,y - 1,y + 1 };// x,y 안틀리게 조심!
	for (int i = 0; i < 4; i++) {
		if (a[i] >= 0 && a[i] < n && b[i]>=0 && b[i] < m) {
			if (!visited[a[i]][b[i]] && box[a[i]][b[i]] == 0) {
				visited[a[i]][b[i]] = 1;
				box[a[i]][b[i]] = 1;
				days[a[i]][b[i]] = days[x][y] + 1;
				q.push(make_pair(a[i],b[i]));
			}
		}
	}
	while (!q.empty()) {
		int sx = q.front().first;
		int sy = q.front().second;
		q.pop();
		bfs(sx, sy);
	}
}
int main() {
	scanf_s("%d", &m);
	scanf_s("%d", &n);
	for (int i = 0; i < n;i++) {
		for (int j = 0; j < m; j++) {
			scanf_s("%d", &box[i][j]);
			if (box[i][j] == 1) {
				q.push(make_pair(i,j));
			}
		}
	}

	int sx = q.front().first;
	int sy = q.front().second;
	q.pop();
	visited[sx][sy] = 1;
	bfs(sx, sy);

	int max = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (days[i][j] > max) max = days[i][j];
			if (box[i][j] == 0){
				printf("-1");
				return 0;
			}
			
		}
	}
	printf("%d", max);
	return 0;
}