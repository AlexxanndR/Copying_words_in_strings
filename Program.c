#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int Repeat(char**, char*, char *, int, int);

int main()
{
	char** str = 0;
	char *str_dop = 0, *str_res = 0;
	int n, m, n1, size, is_matched = 0;
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
    
	rewind(stdin);
	is_matched = Repeat(str, str_res, str_dop, n, m);
	if (is_matched == 0)
	{
		printf_s("No matching words were found.");
	}
	else
	{
		printf_s("The final array: ");
		printf_s("%s", str_res);
	}
	free(str_dop);
	free(str_res);
	for (int i = 0; i < n; i++) free(*(str + i));
	free(str);
	return 0;
}

int Repeat(char** st, char* st_res, char* st_dop, int s_str, int s_stl)
{
	int i = 0, j = 0, i_dp = 0, i2 = 0, ii, jj, in, jn, ik, jk;
	int kol_dop = 0, kol_org = 0, match_w = 0;
	while (i < s_str)
	{
		i_dp = 0;
		while (*(*(st + i) + j) == ' ')         //цикл пропуска пробелов
		{
			j++;
		}
		while (*(*(st + i) + j) != ' ' && *(*(st + i) + j))   //цикл прохода по слову
		{
			kol_org++;                                       //счётчик количества букв в найденном слове
			*(st_dop + i_dp++) = *(*(st + i) + j);           //заполнение доп. строки символами слова из исходной строки
			j++;                                             //переход к следующему символу
		}
		*(st_dop + i_dp) = '\0';
		i_dp = 0;                                   //становимся в начало массива для повторного прохода по нему
		if (*(*(st + i) + j) == '\0')               //если достигнут нуль-символ
		{
			kol_org -= 1;
			i++;                                    //переход на новую строку массива строк
			j = 0;                                  //становимся в её начало
		}
		ii = i; jj = j;                            //запоминаем место, с которого искать повторяющиеся слова

		while (ii < s_str)
		{
			while (*(st_dop + i_dp) - *(*(st + ii) + jj) == 0 && *(st_dop + i_dp) && *(st_dop + i_dp) != '\n')
			{
				if (jj > 0 && i_dp == 0 && *(st_dop + i_dp))
				{
					if (*(st_dop + i_dp) - *(*(st + ii) + jj - 1) != 0 && *(*(st + ii) + jj - 1) != ' ') //если есть слово, в составе которого найдено
					{                                                                                    //сопадение с искомым словом, то обнуляем 
						kol_dop = 0;                                                                     //счётчик количества совпавших символов
						i_dp++;                                                                          //чтобы его сбить 
						jj++;
					}
				}
				i_dp++;
				kol_dop++;
				jj++;
			}
			if (*(*(st + ii) + jj) == '\0') kol_dop -= 1;
			if (i_dp > 0)
			{
				if (*(*(st + ii) + jj) == ' ' && kol_dop == kol_org)
				{
					i_dp = 0;
					while (*(st_dop + i_dp)) *(st_res + i2++) = *(st_dop + i_dp++);
					*(st_res + i2) = ' ';                              //ставим пробел после слова
					i2++; *(st_res + i2) = '\0';                       //ставим нуль-символ в конец строки
					kol_dop = 0;                                       //обнуляем счётчик совпавших букв в доп. строке и в осн. строке
					match_w++;                                         //кол-во совпавших слов
					break;                                             //выход из цикла, чтобы не было записи того же слова 
				}
				else if (*(*(st + ii) + jj + 1) == '\0' && kol_dop == kol_org)
				{
					i_dp = 0;
					while (*(st_dop + i_dp)) *(st_res + i2++) = *(st_dop + i_dp++);
					*(st_res + i2) = ' ';                              //ставим пробел после слова
					i2++; *(st_res + i2) = '\0';                       //ставим нуль-символ в конец строки
					kol_dop = 0;                                       //обнуляем счётчик совпавших букв в доп. строке и в осн. строке
					match_w++;                                         //кол-во совпавших слов
					break;

				}
			}
			if (*(st_dop + i_dp) - *(*(st + ii) + jj) != 0)
			{
				i_dp = 0;
				kol_dop = 0;
				jj++;
			}

			if (!*(*(st + ii) + jj))
			{
				ii++;
				jj = 0;
			}
		}
		kol_org = 0;                //сброс счётчика букв в основной строке 
	}
	return match_w;
 
	

}
