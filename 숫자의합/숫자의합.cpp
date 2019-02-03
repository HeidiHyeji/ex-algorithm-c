#include<iostream>
#include<stdio.h>
using namespace std;

int main(void) {
	int T = 0,num=0,sum=0;
	cin >> T;
	for (int t = 0; t < T; t++) {
		scanf_s("%1d", &num);
		sum += num;
	}
	cout << sum << endl;
	return 0;

}