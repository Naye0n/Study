//���� �����(����/������ ���)
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// isdigit() �Լ� ����� ���� �߰�
#include <ctype.h>
// __debugbreak() �Լ� ����� ���� �߰�
#include <intrin.h>

// ������� ���� �Ʒ��� ���� ����� �����. assert() ���� �Լ��� ���� ����� ������
#ifdef _DEBUG
#define EXIT	__debugbreak()
#else
#define EXIT	exit(-1)
#endif

// C++������ bool���� ���(true/false)�� ����. TRUE(!=0)/FALSE(=0)�� ������ �����Ѵ�
#if 0
#define TRUE 1
#define FALSE 0
#endif

// ���������� �� �ʿ��� ��Ȳ�� �ƴϸ� ������� �ʴ´�
// NUM�� ���� ������ ���� ������. ���� �ڵ带 �������־�� ��
#if 0
int NUM[100];
char source[100];
#endif

// �����ڸ� 1,2,3,4 ���ڷ� �����ߴµ� �� ������ �ǹ̸� ȥ���ϰų� ��Ÿ�� ���� ���� �߻� �����ϴ�
// �̷� ������ ���� ���� �������� ����ϰų�
// #define OP_ADD 1 ... �̷� ������ ��ũ�λ���� ������ �� �ڵ忡�� ��Ī�� ����ϵ��� �Ѵ�
enum Operator
{
	OP_UNDEFINED, OP_ADD, OP_SUBTRACT, OP_MULTIPLY, OP_DIVIDE
};

#if 0
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
#endif

// �迭 ������ ������ ������ ũ�⿡ ���� ����� �ؾ� �Ѵ�.
// �������� �м��Ͽ� �迭 �ε����� �ִ밪�� �и��� ������ �� �ִ밪�� �迭 ũ��� ����ϰ�
// �׷��� ���� ������ ������� ���࿡ ������ ���� ���� ũ�⸦ �����Ѵ�
// �迭 ũ��� �ݵ�� #define(�Ǵ� const int) ������ ������ ��Ī�� ����ϰ�
// ���ǵ� ũ�⸦ �Ѿ�� ������ �߻����� �ʴ��� Ȯ���ϴ� �ڵ带 �����Ͽ��� �Ѵ�
#define MAX_STACK_SIZE		100

// ��ü���� ���α׷���(C++) ������� ���� ������ ������
// ���� C++ STL(Standard Template Library)�� ���� �����ϰ�, std::stack�� ����غ� ��
template<typename TYPE> class CalculatorStack
{
public:
	CalculatorStack()
	{
		// ��� ��������� �׻� �����ڿ��� �ʱⰪ�� �����ش�
		m_nTopIndex = -1;
	}

	// Ŭ������ ��������� �����ų ���� ���� ����Լ�(Ư�� ���̳� ���¸� ��ȸ�ϴ� �Լ�)�� const �Լ��� �����Ѵ�.
	// �̴� �Լ� ���� �ۼ� �� ������� ���� �����Ű�� �ڵ带 �ִ� �Ǽ��� �������ش�
	bool IsEmpty() const
	{
		return m_nTopIndex < 0;
	}

	void Push(TYPE value)
	{
		// �迭�� ũ�⸦ �Ѿ�� ������ �����ϴ� �ڵ�� �׻� �ʿ��ϴ�
		if (m_nTopIndex == MAX_STACK_SIZE - 1)
		{
			printf("error : stack overflow\n");
			EXIT;
		}
		m_data[++m_nTopIndex] = value;
	}

	TYPE Pop()
	{
		if (IsEmpty())
		{
			printf("error : stack underflow\n");
			EXIT;
		}
		return m_data[m_nTopIndex--];
	}

protected:
	// �������� ������ ���� Hungarian Notation�� ���� ����. ���� ����-> https://namu.wiki/w/%ED%97%9D%EA%B0%80%EB%A6%AC%EC%95%88%20%ED%91%9C%EA%B8%B0%EB%B2%95
	int m_nTopIndex;
	TYPE m_data[MAX_STACK_SIZE];
};

class Calculator
{
public:
	double Calculate(const char* pExpression);

protected:
	CalculatorStack<Operator> m_ops;
	CalculatorStack<double> m_values;
};

#if 0
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
#endif

// �������� �����ϰ� ��������/�Լ����� ó���ϵ��� ����
void Input(char* pszInput, int nMaxInput)
{
	char s[100];
	gets_s(s);
	int nLen = strlen(s);
	int j = 0;
	for (int i = 0; i < nLen; i++)
	{
		if (s[i] != ' ')
		{
			pszInput[j++] = s[i];

			// ����ó�� �߰�
			if (j == nMaxInput)
			{
				printf("error : too long input string\n");
				EXIT;
			}
		}
	}
	pszInput[j] = 0;
}

#if 0
float cal(CStack* pstack) {
	int len = strlen(source);
	float ans = 0;
	float num = 0;
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
		if (pstack->op[pstack->topIdx - 1])ans -= Pop(pstack);
		else ans += Pop(pstack);
	}
	return ans;
}
#endif

double Calculator::Calculate(const char* pExpression)
{
	// Ư���� �޸� ��뷮�� ������ �ִ� ��츦 �����ϸ� �ε��Ҽ��� ��꿡�� double���� ����Ѵ�.
	double fNumber = 0., fAnswer = 0.;
	bool bFirst = true;
	Operator op = OP_UNDEFINED;
	char ch;
	for (;; pExpression++)
	{
		ch = *pExpression;
		if (isdigit(ch))
			fNumber = fNumber * 10. + (ch - '0');
		else
		{
			if (bFirst)
			{
				m_ops.Push(OP_ADD);
				m_values.Push(fNumber);
				bFirst = false;
				fNumber = 0.;
			}
			else
			{
				switch (op)
				{
				case OP_ADD:
				case OP_SUBTRACT:
					m_ops.Push(op);
					m_values.Push(fNumber);
					break;
				case OP_MULTIPLY:
					m_values.Push(m_values.Pop() * fNumber);
					break;
				case OP_DIVIDE:
					// ����ó�� �߰�
					if (fNumber == 0.)
					{
						printf("error : divide by zero\n");
						EXIT;
					}
					m_values.Push(m_values.Pop() / fNumber);
					break;
				}
			}
			if (ch == 0)
				break;
			switch (ch)
			{
			case '+':	op = OP_ADD;		break;
			case '-':	op = OP_SUBTRACT;	break;
			case '*':	op = OP_MULTIPLY;	break;
			case '/':	op = OP_DIVIDE;		break;
				// ����ó�� �߰�
			default:
				printf("error : invalid expression\n");
				EXIT;
			}

			fNumber = 0.;
		}
	}

	while (!m_values.IsEmpty())
	{
		switch (m_ops.Pop())
		{
		case OP_ADD:
			fAnswer += m_values.Pop();
			break;
		case OP_SUBTRACT:
			fAnswer -= m_values.Pop();
			break;
		default:
			printf("error : internal error\n");
			EXIT;
		}
	}
	return fAnswer;
}

int main()
{
	while (1)
	{
		printf("CALCULATOR\nINPUT : ");

#define MAX_SOURCE_SIZE		100
		char szSource[MAX_SOURCE_SIZE];
		Input(szSource, sizeof(szSource));
		if (szSource[0] == 0)
			break;

		Calculator calc;;
		double fAnswer = calc.Calculate(szSource);
		printf("RESULT : %f\n", fAnswer);
	}
	printf("EXIT\n");
	return 0;
}
