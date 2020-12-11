#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int Repeat(char**, char*, int, int);
int Add_Check(char**, char*, int*, int*, int, int*);

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
	} while (!str && !str_dop && !str_res);
    
	rewind(stdin);
	for (int i = 0; i < n; i++)
	{
		printf_s("Line #%d: ", i + 1);
		fgets(*(str + i), m, stdin);
	}
    

	is_matched = Repeat(str, str_res, n, m);
	if (is_matched == 0)              //не найдено совпадений
	{
		printf_s("No matching words were found.");
	}
	else
	{
		printf_s("The final array: ");
		printf_s("%s", str_res);
	}
	printf_s("\n");
	getchar();
	free(str_res);
	for (int i = 0; i < n; i++) free(*(str + i));
	free(str);
	return 0;
}


int Repeat(char** st, char* st_res, int s_str, int s_stl)
{
	int i = 0, j = 0, j_start = 0, i_start = 0, j_end = 0, jd_start = 0, id_start = 0, jd_end = 0, i_res = 0, ii, jj;
	int kol_dop = 0, kol_org = 0, match_w = 0, kol_res = 0;
	bool more_t = 0;
	while (i < s_str)
	{
		while (*(*(st + i) + j) == ' ') j++;    //цикл пропуска пробелов
		j_start = j; i_start = i;               //запоминаем начало слова 
		while (*(*(st + i) + j) != ' ' && *(*(st + i) + j) != '\n')   //цикл прохода по слову
		{
			if (i_res != 0) more_t = Add_Check(st, st_res, &i_res, &kol_org, i, &j);
			else if (i_res == 0)
			{
				kol_org++; j++;
			}
		}
		j_end = j;                                                             //запоминаем конец слова
		if (*(*(st + i) + j) == '\n')               //если достигнут символ перехода на новую строку в тексте 
		{
			i++;                                    //переход на новую строку массива строк
			j = 0;                                  //становимся в её начало
		}
		ii = i; jj = j;                            //запоминаем место, с которого искать повторяющиеся слова
		jd_start = j_start; id_start = i_start;    //запоминаем начало слова, чтобы проходить по нему во время поиска в ост. части строки

		while (ii < s_str)
		{   
		    if (j_end == jd_start) break;       //не записываем пробелы в рез. строку 
			if (more_t) break;                  //такое слово уже есть в рез. строке - выходим из цикла поиска                                                                                                 
			while (*(*(st + id_start) + jd_start) - *(*(st + ii) + jj) == 0 && *(*(st + ii) + jj) != '\n' && jd_start < j_end) //проверка на совпадение символов
			{
				if (jj > 0 && jd_start == j_start && *(*(st + ii) + jj - 1) != ' ')  //слово состоит из искомого, но не является им
				{
					jd_start = 0; kol_dop = 0; jj++;                                 //сбиваем переменные, чтобы сбить алгоритм записи в рез. строку
					continue; 
				}
				jj++; jd_start++; kol_dop++;                                         //счёт сиволов в слове, переход к след. символам

			}
			if ((*(*(st + ii) + jj) == ' ' || *(*(st + ii) + jj) == '\n') && kol_dop == kol_org)  //найдено совпадение
			{
				i_res = kol_res;                                        //ставим i_res в правильную позицию, которая мной сбивалась
				jd_start = j_start; id_start = i_start;                 //возвращаемся в начало искомого слова
				while (jd_start < j_end)
				{
					*(st_res + i_res++) = *(*(st + id_start) + jd_start++);   //заполнение рез. строки
					kol_res++;                                                //счётчик количества букв в рез. массиве для определения
				}
				*(st_res + i_res) = ' ';                                 //ставим пробел после слова
				i_res++; kol_res++; *(st_res + i_res) = '\0';            //ставим нуль-символ в конец строки
				kol_dop = 0;                                             //обнуляем счётчик совпавших букв
				match_w++;                                               //счётчик кол-ва записанных слов в рез. массив
				break;                                                   //выход из цикла, чтобы не было записи того же слова 
			}                                                            //если таковое имеется в дальнейшем в строке
			if (*(*(st + id_start) + jd_start) - *(*(st + ii) + jj) != 0)   //нет совпадения символов
			{
				jd_start = j_start;                              //становимся в начало искомого слова
				kol_dop = 0;                                     //обнуляем кол-во совпадений символов
				jj++;                                            //переход к след. символу исходной строки 
			}
			if (!*(*(st + ii) + jj))        //достигнут конец строки в массиве строк
			{
				ii++;                       //переход к след. строке
				jj = 0;                     //становимся в её начало
			}
		}
		more_t = 0; kol_org = 0;            //обнуление счётчика букв в искомом слове и переменной наличия совпавших слов в исх. и рез. строках
	}
	return match_w;                //возвращаем кол-во записанных слов в рез. строку
}

//функция поиска в рез. строке такого же слова, что и слово для поиска совпадений в исх. строке
int Add_Check(char** st, char* st_res, int* i_res, int* kol_org, int i, int* j)
{
	int more_t = 0, tempN_j = 0, tempN_res = 0;
	tempN_j = (*j), (*i_res) = 0;
	while (*(st_res + *i_res))
	{
		while (*(st_res + *i_res) == ' ') (*i_res)++;                     //пропуск пробелов в рез. строки
		while (*(*(st + i) + *j) != ' ' && *(*(st + i) + *j) != '\n')     //проход по слову, которое в последующем будет искаться в строке
		{                                                                 //если совпадений в рез. строке найдено не будет
			if (*(st_res + *i_res) == *(*(st + i) + *j))                  //проверка на нахождение в исх. массиве слова из рез. строки
			{
				if ((*i_res) == 0 && *(*(st + i) + (*j) - 1) != ' ') more_t = 0;        //слово включает в себе слово из рез. строки, но им не является
				if (*(st_res + *i_res + 1) == ' ' && (*(*(st + i) + (*j) + 1) == ' ' || *(*(st + i) + (*j) + 1) == '\n')) //все символы совпали
				{                                                                       //значит, в исх. строке есть ещё одно слово из рез. строки
					more_t = 1;                                                         //переменная наличия полностью совпашего слова
				}
			}
			(*j)++;
			if (*(st_res + *i_res) != ' ' && *(st_res + *i_res) != '\0') (*i_res)++;    //движение по рез. строке до пробела, чтобы не пойти по другому слову из неё
			if (*(st_res + *i_res) == ' ' && *(*(st + i) + *j) != ' ' && *(*(st + i) + *j) != '\n') //в рез. строке встречен пробел - слово закончено
			{
				while (*(*(st + i) + (*j)) != ' ' && *(*(st + i) + (*j)) != '\n') (*j)++;           //тогда переходим в конец слова из исх. строки
			}
			else if (*(st_res + *i_res) == '\0') break;                                             //встречен конец рез. строки - выход из цикла
		}
		if (more_t) break;                              //найдено одинаковое слово - выход из цикла по строке
		else if (*(st_res + *i_res) == '\0') break;     //достигнут конец рез. строки - выход из цикла по строке 
		if (*kol_org == 0)                              //измеряем длинну слова для поиска совпадений (один раз) 
		{
			if (*(*(st + i) + *j) == ' ' || *(*(st + i) + *j) == '\n') *kol_org = (*j) - tempN_j;
			if (*(st_res + (*i_res) + 1) == '\0') break;                                          //след. символ строки нулевой - выход из цикла
		}
		if (*(st_res + *i_res) == ' ' && (*(*(st + i) + *j) == ' ' || *(*(st + i) + *j) == '\n')) (*j) = tempN_j; 
		else if (*(st_res + *i_res) != ' ' && (*(*(st + i) + (*j)) == ' ' || *(*(st + i) + (*j)) == '\n'))
		{
			(*j) = tempN_j;
			while (*(st_res + *i_res) != ' ') (*i_res)++;
		}
	}
	return more_t;
}

