#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void Repeat(char**, char*, char *, int, int);

int main()
{
	char** str = 0;
	char *str_dop = 0, *str_res = 0;
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
		str = (char**)malloc(n * sizeof(char*));
		if (!str)
		{
			free(str);
			continue;
		}
		printf_s("Allocate memory for sentences: ");
		if (!(scanf_s("%d", &m)))
		{
			rewind(stdin);
			continue;
		}
		for (int i = 0; i < n; i++)
		{
			*(str + i) = (char*)malloc(m * sizeof(char));
			if (!*(str + i))
			{
				for (int j = 0; j < i; j++)
				{
					free(*(str + j));
				}
				free(str);
				str = 0;
				break;
			}
		}
		printf_s("Allocate memory for the final array of matched words: ");
		if (!(scanf_s("%d", &n1)))
		{
			rewind(stdin);
			continue;
		}
		str_res = (char*)malloc(n1 * sizeof(char));
		if (!str_res)
		{
			free(str_res);
			continue;
		}
		printf_s("Allocate memory for the additional line: ");
		scanf_s("%d", &size);
		str_dop = (char*)malloc(size * sizeof(char));
		if (!str_dop)
		{
			free(str);
			continue;
		}
	} while (!str && !str_dop && !str_res);
    
	rewind(stdin);
	for (int i = 0; i < n; i++)
	{
		printf_s("Line #%d: ", i + 1);
		fgets(*(str + i), m, stdin);
	}
    
	Repeat(str, str_res, str_dop, n, m);

	printf_s("The final array: ");
	printf_s("%s", str_res);

	free(str_dop);
	free(str_res);
	for (int i = 0; i < n; i++) free(*(str + i));
	free(str);
	return 0;
}

void Repeat(char** st, char* st_res, char* st_dop, int s_str, int s_stl)
{
	int i = 0, j = 0, i1 = 0, i2 = 0, ii, jj, in, jn, ik, jk;
	int kol_dop = 0, kol_org = 0;
	while (i < s_str)
	{
		i1 = 0;
		while (*(*(st + i) + j) == ' ')         //цикл пропуска пробелов
		{
			j++;
		}
		while (*(*(st + i) + j) != ' ' && *(*(st + i) + j))     //цикл прохода по слову
		{
			kol_org++;                                   //счётчик количества букв в найденном слове
			*(st_dop + i1++) = *(*(st + i) + j);         //заполнение доп. строки символами слова из исходной строки
			j++;                                         //переход к следующему символу
		}
		*(st_dop + i1) = '\0';
		i1 = 0;                                  //становимся в начало массива для повторного прохода по нему
		if (*(*(st + i) + j) == '\0')
		{
			i++;
			j = 0;
		}
		ii = i; jj = j;                          //запоминаем место, с которого искать повторяющиеся слова

		while (ii < s_str)
		{
			if (*(st_dop + i1) - *(*(st + ii) + jj) == 0)
			{
				i1++;
				kol_dop++;
				jj++;
			}
			if (i1 > 0)
			{
				if (*(st_dop + i1 - 1) - *(*(st + ii) + jj - 1) == 0 && kol_dop == kol_org)
				{
					i1 = 0;
					while (*(st_dop + i1)) *(st_res + i2++) = *(st_dop + i1++);
					*(st_res + i2) = ' ';                              //ставим пробел после слова
					i2++; *(st_res + i2) = '\0';                       //ставим нуль-символ в конец строки
					kol_dop = 0;                                       //обнуляем счётчик совпавших букв в доп. строке и в осн. строке
					break;                                             //выход из цикла, чтобы не было записи того же слова 
				}
			}
			if (*(st_dop + i1) - *(*(st + ii) + jj) != 0)
			{
				i1 = 0;
				kol_dop = 0;
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
		kol_org = 0; 

		if (j >= s_stl)                         //достигнут конец строки
		{
			i++;                                //переход к новой строке
			j = 0;                              //становимся в начало столбца
		}
	}

	

}
