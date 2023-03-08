#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

char stack[1000];
char str[1000];
int top = 0;

void push(char i) {
	if (top >= 1000)
		printf("Вне стека\n");
	else
		stack[top++] = i;
}

char pop() {
	top -= 1;
	if (top < 0) {
		printf("Вне стека\n");
	}
	return stack[top];
}

int Prior(char b) {

	int ans = 0;
	switch (b)
	{
	case '(': {ans = 0; break; }
	case ')': {ans = 1; break; }
	case '+':
	case '-':
	case '|':
	{ans = 2; break; }
	case '*':
	case'/':
	case'&': {ans = 3; break; }
	case'^': {ans = 4; break; }
	default:
		break;
	}
	return ans;
}

void OPZ(FILE* in, FILE* out, int& temp1, int& temp2, char& temp3)
{
	while (!feof(in))
	{
		fgets(str, 999, in);
		int size = strlen(str);
		for (int i = 0; i < size; ++i)
		{
			if (str[i] == '\n')
			{
				while (top > 0)
				{
					fprintf(out, "%c", pop());
				}
				fprintf(out, "\n");
			}
			else if (str[i] != '(' && str[i] != ')' && str[i] != '+' 
				&& str[i] != '-' && str[i] != '*' && str[i] != '/' 
				&& str[i] != '|' && str[i] != '&' && str[i] != '^')
				fprintf(out, "%c", str[i]);
			else
			{
				if (top == 0)
				{
					push(str[i]);
				}
				else
				{
					temp1 = Prior(str[top - 1]);
					temp2 = Prior(str[i]);
					if (str[i] == '(')
					{
						push(str[i]);
					}
					else if (str[i] == ')')
					{
						while ((temp3 = pop()) != '(')
							fprintf(out, "%c", temp3);
					}
					else {
						if (temp1 > temp2)
							push(str[i]);
						else {
							while (temp2 <= Prior(stack[top - 1]))
								fprintf(out, "%c", pop());
							push(str[i]);
						}
					}
				}
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");
	int temp1, temp2;
	char temp3;
	if (in != NULL)
	{
		printf("Файл открыт успешно\n");
	}
	else printf("Файл не удалось открыть!\n");
	if (out != NULL)
	{
		printf("Файл открыт успешно\n");
	}
	else printf("Файл не удалось открыть!\n");
	OPZ(in, out, temp1, temp2, temp3);
}