#include<iostream>
#include<algorithm>
using namespace std;

int dp[100] = { 0 };
int t[16];
int p[16];
int N;
int main(void) {
	cin >> N;

	int m = 0;
	for (int i = 1; i <= N; i++) {//배열 초기화
		cin >> t[i];
		cin >> p[i];
	}

	for (int i = N; i >= 1; i--) {
		if (i <= N && (i + t[i] > N + 1)) {
			dp[i] = m;
		}
		else {
			dp[i] = max(dp[i + 1], p[i] + dp[i + t[i]]);
		}
		m = max(m, dp[i]);
	}
	m = 0;
	for (int i = 1; i <= N; i++) {
		//cout << dp[i] << endl;
		m = max(m, dp[i]);
	}
	cout << m << endl;
	return 0;
}