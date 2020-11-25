#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void Repeat(char**, char*, char *, int, int);

int main()
{
	char** str1 = 0, *str = 0, * str2 = 0;
	int n, m, n1, size;
	do
	{
		system("CLS");
		printf_s("Enter the number of sentences: ");
		if (!(scanf_s("%d", &n)))
		{
			rewind(stdin);
			continue;
		}
		str1 = (char**)malloc(n * sizeof(char*));
		if (!str1)
		{
			free(str1);
			continue;
		}
		printf_s("Enter the dimension of the sentences: ");
		if (!(scanf_s("%d", &m)))
		{
			rewind(stdin);
			continue;
		}
		for (int i = 0; i < n; i++)
		{
			*(str1 + i) = (char*)malloc(m * sizeof(char));
			if (!*(str1 + i))
			{
				for (int j = 0; j < i; j++)
				{
					free(*(str1 + j));
				}
				free(str1);
				str1 = 0;
				break;
			}
		}
		printf_s("Allocate memory for the second array: ");
		if (!(scanf_s("%d", &n1)))
		{
			rewind(stdin);
			continue;
		}
		str2 = (char*)malloc(n1 * sizeof(char));
		if (!str2)
		{
			free(str2);
			continue;
		}
		printf_s("Allocate memory for the additional line: ");
		scanf_s("%d", &size);
		char* str = (char*)malloc(size * sizeof(char));
		if (!str)
		{
			free(str);
			continue;
		}
	} while (!str1 && !str2 && !str);


    
	rewind(stdin);
	for (int i = 0; i < n; i++)
	{
		printf_s("Line #%d: ", i + 1);
		fgets(*(str1 + i), m, stdin);
	}
    
	Repeat(str1, str2, str, n, m);

	printf_s("%s", str2);

	free(str);
	free(str2);
	for (int i = 0; i < n; i++) free(*(str1 + i));
	free(str1);
	return 0;
}

void Repeat(char** st, char* st1, char* str, int s_str, int s_stl)
{
	int i = 0, j = 0, i1 = 0, i2 = 0, ii, jj, in, jn, ik, jk;
	int kol = 0, kol1 = 0;
	while (*(st + i) < s_str)
	{
		i1 = 0;
		while (*(*(st + i) + j) == ' ')         //цикл пропуска пробелов
		{
			j++;
		}
		in = i; jn = j;                                     //первая буква слова найдена
		while (*(*(st + i) + j) != ' ' && *(*(st + i) + j))     //цикл прохода по слову
		{
			kol++;                               //счётчик количества букв в найденном слове
			*(str + i1++) = *(*(st + i) + j);    //заполнение доп. строки символами слова из исходной строки
			j++;                                 //переход к следующему символу
		}
		*(str + i1) = '\0';
		ik = i; jk = j - 1;                      //найдена последняя буква слова
		i1 = 0;                                  //становимся в начало массива для повторного прохода по нему
		if (*(*(st + i) + j) == '\0')
		{
			i++;
			j = 0;
		}
		ii = i; jj = j;                          //запоминаем место, с которого искать повторяющиеся слова

		while (*(st + ii) < s_str)
		{
			if (*(str + i1) == *(*(st + ii) + jj))
			{
				i1++;
				kol1++;
				jj++;
			}
			if (i1 > 0)
			{
				if (*(str + i1 - 1) == *(*(st + ii) + jj - 1) && kol1 == kol)
				{
					i1 = 0;
					while (*(str + i1)) *(st1 + i2++) = *(str + i1++);
					*(st1 + i2) = ' ';
					kol1 = 0;
					break;                                             //выход из цикла, чтобы не было записи того же слова 
				}
			}
			if (*(str + i1) != *(*(st + ii) + jj))
			{
				i1 = 0;
				kol1 = 0;
				jj++;
			}

			if (*(*(st + ii) + jj) == '\0')
			{
				ii++;
				jj = 0;
			}
			if (jj >= s_stl)                         //достигнут конец строки
			{
				ii++;                                //переход к новой строке
				jj = 0;                              //становимся в начало второго предложения
			}
		}
		kol = 0; 

		if (j >= s_stl)                         //достигнут конец строки
		{
			i++;                                //переход к новой строке
			j = 0;                              //становимся в начало столбца
		}
	}

	

}
