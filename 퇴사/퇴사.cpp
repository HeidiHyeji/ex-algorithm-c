//#include<iostream>
//#include<algorithm>
//using namespace std;
//
//int T[16] = {0};
//int P[16] = {0};
//int N = 0;
//
//int re(int i) {
//	int m = 0;
//	if (i + T[i] > N+1) return 0;
//	for (int k = i; k <= N; k++ ) {
//		int reV = re(k + T[k]);
//		if ((k+T[k]<=N+1) && (m < P[k] + reV)) {
//			m = P[k] + reV;
//		}
//	}
//	return m;
//}
//int main(void) {
//
//	cin >> N;
//
//	int m = 0;
//	for (int t = 1; t <= N; t++) {//배열 초기화
//		cin >> T[t];
//		cin >> P[t];
//	}
//
//	for (int i = 1; i <= N; i++) {
//		int v=re(i);
//		m = max(m, v);
//	}
//	cout << m << endl;
//	return m;
//
//}