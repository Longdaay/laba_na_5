// Лабораторная работа на поиск подстроки в строке
// Реализовать 3 алгоритма - Прямой поиск, Кнута-Морриса-Пратта, Бойера-Мура

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#include <chrono>

const int NotUsed = system("color 70"); // для изменения цвета консоли

void SetColor(int text, int bg) //Функция смены цвета
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

int chSearch(std::string& first, std::string& second) // Алгоритм прямого поиска
{
	int sdvig = 0;
	int i = 0;
	while (i != second.size())
	{
		if (first[i + sdvig] == second[i])
			i++;
		else
		{
			sdvig++;
			i = 0;
		}
		if (sdvig == first.size())
			return -1;
	}
	return sdvig;
}

int kmpSearch(std::string& first, std::string& second) // Алгоритм Кнута-Морриса-Пратта
{
	int sdvig = 0;
	int i = 0;
	int perenos = -1;
	while (i != second.size())
	{
		if (first[i + sdvig] == second[i])
		{
			i++;
			perenos++;
		}
		else
		{
			if (perenos == -1)
				sdvig = sdvig + perenos + 2;
			else
				sdvig = sdvig + perenos + 1;
			perenos = -1;
			i = 0;
		}
		if (sdvig == first.size())
			return -1;
	}
	return sdvig;
}

std::map<char, int> vec_prefix(std::string substr) // функция для создания таблицы смещений
{
	std::map<char, int> prefix;
	std::vector<int> vec;
	int i;
	
	for (i = 0; i < substr.size(); i++)
	{
		vec.push_back(substr[i]);
	}
	int m = 0;
	prefix[vec[vec.size() - 1]] = vec.size();
	for (i = vec.size() - 1; i >= 0; i--)
	{
		for (auto item : prefix)
		{
			if (item.first == vec[i])
			{
				m = 1;
				break;
			}
		}
		if (m != 1)
			prefix[vec[i]] = vec.size() - i - 1;
		else
			m = 0;
	}
	return prefix;
}

int bmSearch(std::string& first, std::string& second) // алгоритм Бойера-Мура
{
	int sdvig = second.size() - 1;
	int i = second.size() - 1;
	int parametr = 1;
	std::map <char, int> prefix_tab;
	prefix_tab = vec_prefix(second); // создаем таблицу смещений 

	if (second.size() == 1) // если подстрока состоит из одного символа
	{
		while (parametr)
		{
			if (first[sdvig] == second[i])
			{
				parametr = 0;
			}
			else
			{
				if (prefix_tab[first[sdvig]] == 0)
					sdvig += second.size();
				else
					sdvig += prefix_tab[first[sdvig]];
			}
			if (sdvig == first.size())
				return -1;
		}
		return sdvig;
	}
	else
	{
		while (i != 0)
		{
			if (first[sdvig] == second[i])
			{
				i--;
				sdvig--;
			}
			else
			{
				if (prefix_tab[first[sdvig]] == 0)
					sdvig += second.size();
				else
					sdvig += prefix_tab[first[sdvig]];
				i = second.size() - 1;
			}
			if (sdvig == first.size())
				return -1;
		}
		return sdvig;
	}
}

void print_lab() // вывод шапки
{
	std::cout << "----------------------------------------------" << std::endl;
	std::cout << "Лабораторная работа - поиск подстроки в строке" << std::endl;
	std::cout << "----------------------------------------------" << std::endl << std::endl;
}

void printSubstr_find(const std::string& str, const int& position, const int& substr_size) // вывод найденной подстроки
{
	std::cout << "Найденая подстрока: ";
	int i = 0;
	while (i != str.size())
	{
		if (position <= i and i < position + substr_size)
		{
			SetColor(6, 7);
			std::cout << str[i];
			SetColor(0, 7);
		}
		else
			std::cout << str[i];
		i++;
	}
	std::cout << std::endl << std::endl;
}

void fillstr(std::string& str, std::string& substr) // ввод строки и подстроки
{
	std::cout << "Введите строку латинскими буквами: ";
	std::getline(std::cin, str);

	std::cout << "Введите подстроку латинскими буквами: ";
	std::getline(std::cin, substr);
}

void print_position(const int& position) // вывод позиции подстроки в строке
{
	if (position == -1)
		std::cout << "Строка не найдена!" << std::endl;
	else
		std::cout << "Подстрока находится на позиции " << position << std::endl;
}

void print_str(const std::string& str, const std::string& substr) // вывод строки и подстроки 
{
	std::cout << "Строка, в которой ищем подстроку: " << str << std::endl;
	std::cout << "Искомая подстрока: " << substr << std::endl;
}

void choose_search(std::string& str, std::string& substr) // выбор алгоритма
{
	system("cls");
	std::string value; // переменная, которая хранит выбранное значение
	int position;
	std::chrono::steady_clock sc;   // create an object of `steady_clock` class
	double seconds; // переменная, которая хранит в себе время исполнения события

	print_lab();
	std::cout << "С помощью какого из ниже перечисленных алгоритма Вы хотите найти подстроку в строке?" << std::endl;
	std::cout << "1 - Алгоритм прямого поиска" << std::endl;
	std::cout << "2 - Алгоритм Кнута, Морриса, Пратта (КМП-поиск)" << std::endl;
	std::cout << "3 - Алгоритм Бойера-Мура (БМ-поиск)" << std::endl << std::endl;
	std::cout << "Выберите один из предложенных вариантов: ";

	std::getline(std::cin, value); // считываем выбранное значение
	if (value.size() == 1) // проверяем количество введенных символов. Если много, то просим ввести еще раз, иначе проверям дальше
	{
		switch (value[0]) // проверям, взяв первый символ переменной value
		{
		case '1': // посимвольный поиск
		{
			std::cout << std::endl << "Посимвольный поиск подстроки в строке" << std::endl;
			print_str(str, substr);
			auto start = sc.now();
			position = chSearch(str, substr);
			auto end = sc.now();
			print_position(position);
			auto time_span = static_cast<std::chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
			std::cout << "Затраченное время на поиск строки: " << time_span.count() << " секунд" << std::endl;
			break;
		}
		case '2': // КМП
		{
			std::cout << std::endl << "Алгоритм КМП" << std::endl;
			print_str(str, substr);
			auto start_1 = sc.now();
			position = kmpSearch(str, substr);
			auto end_1 = sc.now();
			print_position(position);
			auto time_span_1 = static_cast<std::chrono::duration<double>>(end_1 - start_1);   // высчитываем время, затраченное на событие
			std::cout << "Затраченное время на поиск строки: " << time_span_1.count() << " секунд" << std::endl;
			break;
		}
		case '3': // БМ
		{
			std::cout << std::endl << "Алгоритм БМ" << std::endl;
			print_str(str, substr);
			auto start_2 = sc.now();
			position = bmSearch(str, substr);
			auto end_2 = sc.now();
			print_position(position);
			auto time_span_2 = static_cast<std::chrono::duration<double>>(end_2 - start_2);   // высчитываем время, затраченное на событие
			std::cout << "Затраченное время на поиск строки: " << time_span_2.count() << " секунд" << std::endl;
			break;
		}
		default: // если число не подходит ни к одному из
			std::cout << "Число введено неверно. Введите заново" << std::endl;
			system("pause");
			system("cls");
			choose_search(str,substr);
		}
	}
	else // если введено символов больше необходимого
	{
		std::cout << "Необходимо ввести один символ. Попробуйте ввести заново" << std::endl;
		system("pause");
		system("cls");
		choose_search(str, substr);
	}
	if (position != -1) // если подстрока найдена и известна позиция, выводим строку с подсветкой подстроки
		printSubstr_find(str, position, substr.size());
}


int main()
{
	setlocale(0, "");
	std::string str, substr;

	print_lab();
	fillstr(str, substr);
	choose_search(str, substr);

	system("pause");
	return 0;
}