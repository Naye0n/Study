//계산기 만들기(곱셈/나눗셈 기능)
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// isdigit() 함수 사용을 위해 추가
#include <ctype.h>
// __debugbreak() 함수 사용을 위해 추가
#include <intrin.h>

// 디버깅을 위해 아래와 같은 방식을 사용함. assert() 같은 함수도 많이 사용을 권장함
#ifdef _DEBUG
#define EXIT	__debugbreak()
#else
#define EXIT	exit(-1)
#endif

// C++에서는 bool형을 사용(true/false)이 권장. TRUE(!=0)/FALSE(=0)은 가급적 자제한다
#if 0
#define TRUE 1
#define FALSE 0
#endif

// 전역변수는 꼭 필요한 상황이 아니면 사용하지 않는다
// NUM은 실제 사용되지 않은 변수임. 자주 코드를 정리해주어야 함
#if 0
int NUM[100];
char source[100];
#endif

// 연산자를 1,2,3,4 숫자로 구분했는데 각 숫자의 의미를 혼동하거나 오타로 인해 오류 발생 가능하다
// 이럴 때에는 위와 같이 열거형을 사용하거나
// #define OP_ADD 1 ... 이런 식으로 매크로상수로 정의한 후 코드에는 명칭을 사용하도록 한다
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

// 배열 변수를 선언할 때에는 크기에 대해 고민을 해야 한다.
// 논리적으로 분석하여 배열 인덱스의 최대값이 분명할 때에는 그 최대값을 배열 크기로 사용하고
// 그렇지 않을 때에는 통상적인 실행에 문제가 없을 만한 크기를 산정한다
// 배열 크기는 반드시 #define(또는 const int) 등으로 정의한 명칭을 사용하고
// 정의된 크기를 넘어서는 접근이 발생하지 않는지 확인하는 코드를 포함하여야 한다
#define MAX_STACK_SIZE		100

// 객체지향 프로그래밍(C++) 방식으로 구현 내용을 변경함
// 향후 C++ STL(Standard Template Library)에 대해 공부하고, std::stack을 사용해볼 것
template<typename TYPE> class CalculatorStack
{
public:
	CalculatorStack()
	{
		// 모든 멤버변수는 항상 생성자에서 초기값을 정해준다
		m_nTopIndex = -1;
	}

	// 클래스의 멤버변수를 변경시킬 일이 없는 멤버함수(특히 값이나 상태를 조회하는 함수)는 const 함수로 정의한다.
	// 이는 함수 내용 작성 중 멤버변수 값을 변경시키는 코드를 넣는 실수를 방지해준다
	bool IsEmpty() const
	{
		return m_nTopIndex < 0;
	}

	void Push(TYPE value)
	{
		// 배열의 크기를 넘어서는 접근을 방지하는 코드는 항상 필요하다
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
	// 변수명을 결정할 때는 Hungarian Notation을 많이 쓴다. 참조 내용-> https://namu.wiki/w/%ED%97%9D%EA%B0%80%EB%A6%AC%EC%95%88%20%ED%91%9C%EA%B8%B0%EB%B2%95
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

// 전역변수 삭제하고 지역변수/함수인자 처리하도록 변경
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

			// 예외처리 추가
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
	// 특별히 메모리 사용량에 제한이 있는 경우를 제외하면 부동소수점 계산에는 double형을 사용한다.
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
					// 예외처리 추가
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
				// 예외처리 추가
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
