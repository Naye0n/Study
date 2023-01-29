//°è»ê±â ¸¸µé±â(°ö¼À/³ª´°¼À ±â´É)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
int NUM[100];
char source[100];

typedef struct _CalculatorStack {
	float arr[100];
	int topIdx;
	int op[100] = { 0 };
}CStack;

void StackInit(CStack* pstack) {
	pstack->topIdx = -1;
}

int SIsEmpty(CStack* pstack) {
	if (pstack->topIdx < 0)return TRUE;
	else return FALSE;
}

void Push(CStack* pstack, float data) {
	pstack->topIdx++;
	pstack->arr[pstack->topIdx] = data;
}

float Pop(CStack* pstack) {
	if (SIsEmpty(pstack)) { printf("error"); exit(-1); }
	return pstack->arr[pstack->topIdx--];
}

void input() {
	char s[100];
	gets_s(s);
	int len = strlen(s);
	int j = 0;
	for (int i = 0; i < len; i++) {

		if (s[i] != 32) {
			source[j++] = s[i];
		}
	}
	source[j] = '\0';
}

float cal(CStack* pstack) {
	int len = strlen(source);
	double ans = 0;
	double num = 0;
	bool first = true;
	int op = 0;
	// op 1: add 2: sub 3: mul 4:div
	for (int i = 0; i < len + 1; i++) {

		if (source[i] <= 57 && source[i] >= 48) {
			num *= 10;
			num += int(source[i]) - 48;
		}
		else {
			if (first) { 
				Push(pstack, num);
				first = false; num = 0; 
			}
			else {
				switch (op) {
				case 1://add
					Push(pstack, num);
					break;
				case 2://sub
					pstack->op[pstack->topIdx] = 1;
					Push(pstack, num);
					break;
				case 3://mul
					num = Pop(pstack) * num;
					Push(pstack, num);
					break;
				case 4://div
					num = Pop(pstack) / num;
					Push(pstack, num);
					break;
				}
			}

			switch (source[i]) {
			case 43:
				op = 1; break;
			case 45:
				op = 2; break;
			case 42:
				op = 3; break;
			case 47:
				op = 4; break;
			}
				num = 0;
			}

		}
	while (!SIsEmpty(pstack)) {
		if (pstack->op[pstack->topIdx-1])ans -= Pop(pstack);
		else ans += Pop(pstack);
	}
	return ans;
}

int main() {
	printf("CALCULATOR\nINPUT : ");
	input();
	CStack stack;
	StackInit(&stack);
	float ans= cal(&stack);
	printf("RESULT : %f\n", ans);
	return 0;
}
