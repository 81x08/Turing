#include <stdio.h>
#include <locale.h>
#include <windows.h>

#define MAX_BUFFER 100

typedef enum {
	Q0,
	Q1,
	Q2,
	Q3,
	Q4,
	Q5,
	Q6,
	Q7,
	Q8,
	Q9
} STATES;

int main() {
	setlocale(LC_ALL, "Russian");
	
	printf("Введите уравнение: ");
	
	char buffer[MAX_BUFFER] = {'\0'};
	
	do {
		fflush(stdin);
	} while (scanf("%s", buffer) != 1);

	int size = strlen(buffer); // Только валидные символы (само уравнение)
	
	char * symbol = strchr(buffer, '*');
	
	int countPre = symbol - buffer; // Количество единиц до * (первый множитель)
	int countPost = (size - 1) - countPre; // Количество единиц после * (второй множитель)

	int count = (2 + 1) + countPre * countPost; // Пустые места + знак равно + количество единичек справа

	char * pointer = (char *)malloc(sizeof(char) * (size + count));
	memset(pointer, ' ', (size + count));
	
	char * equation = (char *)malloc(sizeof(char) * (size + count));
	memset(equation, '_', (size + count));
	
	for (int i = 0; i < size; i++) {
		equation[i + 1] = buffer[i];
	}

	equation[0] = '_';
	equation[size + 1] = '=';
	equation[size + count] = 0;

	int pos = 0;
	
	STATES state = Q1;
	
	system("cls");

	printf("%s\n", pointer);
	printf("%s\n", equation);
	
	do {	
		pointer[pos] = ' ';
		
		switch (state) {
			case Q1: {
				switch (equation[pos]) {
					case '_': {
						state = state;
						
						equation[pos] = '_';
						
						pos++;
						
						break;
					}
					case '*': {
						state = Q9;
						
						equation[pos] = '_';
						
						pos++;
						
						break;
					}
					case '1': {
						state = Q2;
						
						equation[pos] = '_';
						
						pos++;
						
						break;
					}
				}
				
				break;
			}
			case Q2: {
				switch (equation[pos]) {
					case '*': {
						state = Q3;
						
						equation[pos] = '*';
						
						pos++;
						
						break;
					}
					case '1': {
						state = Q2;
						
						equation[pos] = '1';
						
						pos++;
						
						break;
					}
				}
				
				break;
			}
			case Q3: {
				switch (equation[pos]) {
					case '0': {
						state = Q3;
						
						equation[pos] = '0';
						
						pos++;
						
						break;
					}
					case '1': {
						state = Q4;
						
						equation[pos] = '0';
						
						pos++;
						
						break;
					}
				}
				
				break;
			}
			case Q4: {
				switch (equation[pos]) {
					case '_': {
						state = Q5;
						
						equation[pos] = '1';
						
						pos--;
						
						break;
					}
					case '=': {
						state = Q4;
						
						equation[pos] = '=';
						
						pos++;
						
						break;
					}
					case '0': {
						state = Q4;
						
						equation[pos] = '0';
						
						pos++;
						
						break;
					}
					case '1': {
						state = Q4;
						
						equation[pos] = '1';
						
						pos++;
						
						break;
					}
				}
				
				break;
			}
			case Q5: {
				switch (equation[pos]) {
					case '=': {
						state = Q6;
						
						equation[pos] = '=';
						
						pos--;
						
						break;
					}
					case '0': {
						state = Q5;
						
						equation[pos] = '0';
						
						pos--;
						
						break;
					}
					case '1': {
						state = Q5;
						
						equation[pos] = '1';
						
						pos--;
						
						break;
					}
				}
				
				break;
			}
			case Q6: {
				switch (equation[pos]) {
					case '*': {
						state = Q7;
						
						equation[pos] = '*';
						
						pos++;
						
						break;
					}
					case '0': {
						state = Q6;
						
						equation[pos] = '0';
						
						pos--;
						
						break;
					}
					case '1': {
						state = Q4;
						
						equation[pos] = '0';
						
						pos++;
						
						break;
					}
				}
				
				break;
			}
			case Q7: {
				switch (equation[pos]) {
					case '=': {
						state = Q8;
						
						equation[pos] = '=';
						
						pos--;
						
						break;
					}
					case '0': {
						state = Q7;
						
						equation[pos] = '1';
						
						pos++;
						
						break;
					}
				}
				
				break;
			}
			case Q8: {
				switch (equation[pos]) {
					case '_': {
						state = Q1;
						
						equation[pos] = '_';
						
						pos++;
						
						break;
					}
					case '*': {
						state = Q8;
						
						equation[pos] = '*';
						
						pos--;
						
						break;
					}
					case '1': {
						state = Q8;
						
						equation[pos] = '1';
						
						pos--;
						
						break;
					}
				}
				
				break;
			}
			case Q9: {
				switch (equation[pos]) {
					case '=': {
						state = Q0;
						
						equation[pos] = '_';
						
						pos = pos;
						
						break;
					}
					case '1': {
						state = Q9;
						
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
	} while (state != Q0);
	
	free(pointer);
	free(equation);
	
	system("pause");
	
	return 0;
}