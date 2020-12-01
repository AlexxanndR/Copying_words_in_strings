#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int Repeat(char**, char*, char *, int, int);
void delete_other(char*, int);

int main()
{
	char** str = 0;
	char *str_dop = 0, *str_res = 0;
	int n, m, n1, size, is_matched = 0;
	do                             //цикл пока не будет выделена память под строки
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
		str_res = (char*)malloc(n1 * sizeof(char));      //выделяем память под результирующую строку
		if (!str_res)
		{
			free(str_res);
			continue;
		}
		printf_s("Allocate memory for the additional line: ");
		scanf_s("%d", &size);
		str_dop = (char*)malloc(size * sizeof(char));   //выделяем память под дополнительную строк для записи в неё
		if (!str_dop)                                   //слов для дальнейшего поиска их совпадений 
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
	if (is_matched == 0)              //не найдено совпадений
	{
		printf_s("No matching words were found.");
	}
	else
	{
		printf_s("The final array: ");
		printf_s("%s", str_res);
	}
	free(str_dop);                                    //освобождаем выделенную память
	free(str_res);
	for (int i = 0; i < n; i++) free(*(str + i));
	free(str);
	return 0;
}


int Repeat(char** st, char* st_res, char* st_dop, int s_str, int s_stl)
{
	int i = 0, j = 0, i_dp = 0, i_res = 0, ii, jj, in, jn, ik, jk;
	int kol_dop = 0, kol_org = 0, match_w = 0, kol_res = 0;
	while (i < s_str)
	{
		i_dp = 0;                               //становимся в начало доп. строки
		while (*(*(st + i) + j) == ' ')         //цикл пропуска пробелов
		{
			j++;
		}
		i_res = 0;                              //обнуляем переменнную прохода по результирующей строке 
		while (*(*(st + i) + j) != ' ' && *(*(st + i) + j) != '\n')   //цикл прохода по слову
		{
			kol_org++;                                       //счётчик количества букв в найденном слове
			*(st_dop + i_dp++) = *(*(st + i) + j);           //заполнение доп. строку символами слова из исходной строки
			j++;                                             //переход к следующему символу в исх. строке
			if (*(st_dop + i_dp - 1) == *(st_res + i_res) && kol_res > 0) //найдено больще 2 одинаковых слов в строке
			{
				if (i_dp - 2 > 0)             //проверка на то, что это не слово, которое включает в себя слово из рез. строки
				{                             //если да, то
					i_dp = 0;                 //обнуляем переменную движения по доп. строке 
				}
				i_res++;                            //переход к след. символу в рез. строке 
				if (i_res == kol_res - 1 && (*(st_res + i_dp) == ' ' || *(st_res + i_dp) == '\n')) //все символы в строках совпали
				{                                         //значит, совпавших в исходной строке больше двух
					i_dp = 0;                             //обнуляем переменную движения по доп. строке
				} 
			}
		}
		*(st_dop + i_dp) = '\0';                    //ставим нуль-символ в конец строки
		i_dp = 0;                                   //становимся в начало доп. строки для повторного прохода по нему
		if (*(*(st + i) + j) == '\n')               //если достигнут символ перехода на новую строку в тексте 
		{
			i++;                                    //переход на новую строку массива строк
			j = 0;                                  //становимся в её начало
		}
		ii = i; jj = j;                            //запоминаем место, с которого искать повторяющиеся слова

		while (ii < s_str)
		{
			if (*(st_dop + i_dp) == '\0' && i_dp == 0)  //в строке 2 и более раза повторяется одно слов
			{                                           //тогда выходим из цикла поиска
				break;                                  //чтобы не записывать в рез. строку слово, которое
			}                                           //в ней уже есть
			while (*(st_dop + i_dp) - *(*(st + ii) + jj) == 0 && *(st_dop + i_dp) && *(*(st + ii) + jj) != '\n')
			{
				if (jj > 0 && i_dp == 0 && *(st_dop + i_dp))
				{
					if (*(*(st + ii) + jj - 1) != ' ')  //если есть слово, в составе которого есть искомое слово
					{                                   //то обнуляем счётчик количества совпавших символов
						kol_dop = 0;                    //чтобы его сбить 
						i_dp++;                         
						jj++;
					}
				}
				i_dp++;            //переход к след. символу в доп. строке
				kol_dop++;         //счётчик совпадений символа из доп. строки с символом в исходной строке
				jj++;              //переход к след. символу с исходной строке
			}
			if (i_dp > 0)
			{
				if ((*(*(st + ii) + jj) == ' ' || *(*(st + ii) + jj) == '\n') && kol_dop == kol_org)
				{
					i_res = kol_res;
					i_dp = 0;
					while (*(st_dop + i_dp))
					{
						*(st_res + i_res++) = *(st_dop + i_dp++);
						kol_res++;                                          //счётчик количества букв в рез. массиве
					}
					*(st_res + i_res) = ' ';                                //ставим пробел после слова
					i_res++; kol_res++; *(st_res + i_res) = '\0';           //ставим нуль-символ в конец строки
					kol_dop = 0;                                            //обнуляем счётчик совпавших букв
					match_w++;                                              //счётчик кол-ва записанных одинаковых слов
					break;                                                  //выход из цикла, чтобы не было записи того же слова 
				}                                                           //если таковое имеется в дальнейшем в строке
			}
			if (*(st_dop + i_dp) - *(*(st + ii) + jj) != 0)       //нет совпадений символов
			{ 
				i_dp = 0;                                        //становимся в начало доп. строки
				kol_dop = 0;                                     //обнуляем кол-во совпадений символов
				jj++;                                            //переход к след. символы исходной строки 
			}

			if (!*(*(st + ii) + jj))        //достигнут конец строки в массиве строк
			{
				ii++;                       //переход к след. строке
				jj = 0;                     //становимся в её начало
			}
		}
		kol_org = 0;                //сброс счётчика букв искомого слова
	}
	return match_w;
 
	

}
