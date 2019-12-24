// ������������ ������ �� ����� ��������� � ������
// ����������� 3 ��������� - ������ �����, �����-�������-������, ������-����

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#include <chrono>

const int NotUsed = system("color 70"); // ��� ��������� ����� �������

void SetColor(int text, int bg) //������� ����� �����
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

int chSearch(std::string& first, std::string& second) // �������� ������� ������
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

int kmpSearch(std::string& first, std::string& second) // �������� �����-�������-������
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

std::map<char, int> vec_prefix(std::string substr) // ������� ��� �������� ������� ��������
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

int bmSearch(std::string& first, std::string& second) // �������� ������-����
{
	int sdvig = second.size() - 1;
	int i = second.size() - 1;
	int parametr = 1;
	std::map <char, int> prefix_tab;
	prefix_tab = vec_prefix(second); // ������� ������� �������� 

	if (second.size() == 1) // ���� ��������� ������� �� ������ �������
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

void print_lab() // ����� �����
{
	std::cout << "----------------------------------------------" << std::endl;
	std::cout << "������������ ������ - ����� ��������� � ������" << std::endl;
	std::cout << "----------------------------------------------" << std::endl << std::endl;
}

void printSubstr_find(const std::string& str, const int& position, const int& substr_size) // ����� ��������� ���������
{
	std::cout << "�������� ���������: ";
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

void fillstr(std::string& str, std::string& substr) // ���� ������ � ���������
{
	std::cout << "������� ������ ���������� �������: ";
	std::getline(std::cin, str);

	std::cout << "������� ��������� ���������� �������: ";
	std::getline(std::cin, substr);
}

void print_position(const int& position) // ����� ������� ��������� � ������
{
	if (position == -1)
		std::cout << "������ �� �������!" << std::endl;
	else
		std::cout << "��������� ��������� �� ������� " << position << std::endl;
}

void print_str(const std::string& str, const std::string& substr) // ����� ������ � ��������� 
{
	std::cout << "������, � ������� ���� ���������: " << str << std::endl;
	std::cout << "������� ���������: " << substr << std::endl;
}

void choose_search(std::string& str, std::string& substr) // ����� ���������
{
	system("cls");
	std::string value; // ����������, ������� ������ ��������� ��������
	int position;
	std::chrono::steady_clock sc;   // create an object of `steady_clock` class
	double seconds; // ����������, ������� ������ � ���� ����� ���������� �������

	print_lab();
	std::cout << "� ������� ������ �� ���� ������������� ��������� �� ������ ����� ��������� � ������?" << std::endl;
	std::cout << "1 - �������� ������� ������" << std::endl;
	std::cout << "2 - �������� �����, �������, ������ (���-�����)" << std::endl;
	std::cout << "3 - �������� ������-���� (��-�����)" << std::endl << std::endl;
	std::cout << "�������� ���� �� ������������ ���������: ";

	std::getline(std::cin, value); // ��������� ��������� ��������
	if (value.size() == 1) // ��������� ���������� ��������� ��������. ���� �����, �� ������ ������ ��� ���, ����� �������� ������
	{
		switch (value[0]) // ��������, ���� ������ ������ ���������� value
		{
		case '1': // ������������ �����
		{
			std::cout << std::endl << "������������ ����� ��������� � ������" << std::endl;
			print_str(str, substr);
			auto start = sc.now();
			position = chSearch(str, substr);
			auto end = sc.now();
			print_position(position);
			auto time_span = static_cast<std::chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
			std::cout << "����������� ����� �� ����� ������: " << time_span.count() << " ������" << std::endl;
			break;
		}
		case '2': // ���
		{
			std::cout << std::endl << "�������� ���" << std::endl;
			print_str(str, substr);
			auto start_1 = sc.now();
			position = kmpSearch(str, substr);
			auto end_1 = sc.now();
			print_position(position);
			auto time_span_1 = static_cast<std::chrono::duration<double>>(end_1 - start_1);   // ����������� �����, ����������� �� �������
			std::cout << "����������� ����� �� ����� ������: " << time_span_1.count() << " ������" << std::endl;
			break;
		}
		case '3': // ��
		{
			std::cout << std::endl << "�������� ��" << std::endl;
			print_str(str, substr);
			auto start_2 = sc.now();
			position = bmSearch(str, substr);
			auto end_2 = sc.now();
			print_position(position);
			auto time_span_2 = static_cast<std::chrono::duration<double>>(end_2 - start_2);   // ����������� �����, ����������� �� �������
			std::cout << "����������� ����� �� ����� ������: " << time_span_2.count() << " ������" << std::endl;
			break;
		}
		default: // ���� ����� �� �������� �� � ������ ��
			std::cout << "����� ������� �������. ������� ������" << std::endl;
			system("pause");
			system("cls");
			choose_search(str,substr);
		}
	}
	else // ���� ������� �������� ������ ������������
	{
		std::cout << "���������� ������ ���� ������. ���������� ������ ������" << std::endl;
		system("pause");
		system("cls");
		choose_search(str, substr);
	}
	if (position != -1) // ���� ��������� ������� � �������� �������, ������� ������ � ���������� ���������
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