#include <stdio.h>
#include <locale.h>
#include <windows.h>

#define MAX_BUFFER 100

typedef enum {
	Q0,
	Q1,
	Q2,
	Q3,
	STOP
} STATES;

int main() {
	setlocale(LC_ALL, "Russian");
	
	printf("Введите уравнение: ");
	
	char buffer[MAX_BUFFER] = {'\0'};
	
	do {
		fflush(stdin);
	} while (scanf("%s", buffer) != 1);

	int size = strlen(buffer); // Только валидные символы (само уравнение)
	
	char * symbol = strchr(buffer, '+');
	
	int count = symbol - buffer + 2; // Пустые места + количество единичек справа

	char * pointer = (char *)malloc(sizeof(char) * (size + count));
	memset(pointer, ' ', (size + count));
	
	char * equation = (char *)malloc(sizeof(char) * (size + count));
	memset(equation, '_', (size + count));
	
	for (int i = 0; i < size; i++) {
		equation[i + 1] = buffer[i];
	}
	
	equation[size + count] = 0;
	
	printf("Лента: %s", equation);
	
	int pos = 0;
	
	STATES state = Q1;
	
	system("cls");
	
	pointer[pos] = '_';
	
	printf("%s\n", pointer);
	printf("%s\n", equation);
		
	do {	
		pointer[pos] = ' ';
		
		switch (state) {
			case Q1: {
				switch(equation[pos]) {
					case '+': {
						state = STOP;
						
						equation[pos] = '_';
						
						break;
					}
					case '1': {
						state = Q2;
						
						equation[pos] = '_';
						
						pos++;
						
						break;
					}
					case '_': {
						state = state;
						
						equation[pos] = '_';
						
						pos++;
						
						break;
					}
				}
				
				break;
			}
			case Q2: {
				switch(equation[pos]) {
					case '+': {
						state = Q2;
						
						equation[pos] = '+';
						
						pos++;
						
						break;
					}
					case '1': {
						state = Q2;
						
						equation[pos] = '1';
						
						pos++;
						
						break;
					}
					case '_': {
						state = Q3;
						
						equation[pos] = '1';
						
						pos--;
						
						break;
					}
				}
				
				break;
			}
			case Q3: {
				switch(equation[pos]) {
					case '+': {
						state = Q3;
						
						equation[pos] = '+';
						
						pos--;
						
						break;
					}
					case '1': {
						state = Q3;
						
						equation[pos] = '1';
						
						pos--;
						
						break;
					}
					case '_': {
						state = Q1;
						
						equation[pos] = '_';
						
						pos++;
						
						break;
					}
				}
				
				break;
			}
		}
		
		Sleep(250);
		
		system("cls");
		
		pointer[pos] = '_';

		printf("%s\n", pointer);
		printf("%s\n", equation);
	} while (state != STOP);

	free(pointer);
	free(equation);
	
	system("pause");
	
	return 0;
}