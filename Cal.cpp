////계산기 만들기
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <stack>
//int NUM[100];
//char source[100];
//
//void input() {
//	char s[100];
//	gets_s(s);
//	int len = strlen(s);
//		int j = 0;
//		for (int i = 0; i < len; i++) {
//	
//		if (s[i] != 32) {
//			source[j++] = s[i];
//		}
//	}
//		source[j] = '\0';
//
//	//len = strlen(source);
//}
//
//int cal() {
//	int len = strlen(source);
//	float ans = 0;
//	float num = 0;
//	float cnt = 1;
//	bool first = true;
//	int op = 0; // 1: add 2: sub 3: mul 4:div
//	for (int i = 0; i < len+1; i++) {
//
//		if (source[i] <= 57 && source[i] >= 48) {
//			cnt *= 0.1;
//			num += (int(source[i])-48) * cnt;
//		}
//		else {
//			if (first) { ans += num / cnt; first = false; num = 0; }
//			else {
//				switch (op) {
//				case 1:
//					ans += num / cnt; break;
//				case 2:
//					ans -= num / cnt; break;
//				}
//				num = 0;
//			}
//			switch (source[i]) {
//			case 43:
//				op = 1; break;
//			case 45:
//				op = 2; break;
//			case 42:
//				op = 3; break;
//			case 47:
//				op = 4; break;
//			}
//			cnt = 1;
//		}
//	}
//	return ans;
//	}
//
//int main() {
//	printf("CALCULATOR\nINPUT : ");
//	input();
//	int ans=cal();
//	printf("RESULT : %d\n", ans);
//	return 0;
//}
