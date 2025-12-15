#include <iostream>
#include <string>
#include <windows.h>
#include <cctype>
#include <array>

void inputStr(std::string&);
void checkStr(const std::string&);
void find_Max_Min_Numb(const std::string&, std::string&, std::string&, const std::array<char, 5>&);
void Restring(std::string&, const std::string&, const std::array<char, 5>&);
int isNumb(const std::string&);
void Replace_Max_Min(std::string&, const std::string&, const std::string&);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::array<char, 5> arr = { ',', '.', ';', '?', '!' };
	std::string MySring;
	inputStr(MySring);
	try
	{
		checkStr(MySring);
		std::string min;
		std::string max;
		find_Max_Min_Numb(MySring, max, min, arr);
		Replace_Max_Min(MySring, min, max);
		std::cout << MySring;
	}
	catch (const char* msq)
	{
		std::cout << msq;
	}
}
void inputStr(std::string& str)
{
	std::cout << "input string with numbers" << '\n';
	std::getline(std::cin, str);
}
void checkStr(const std::string& str)
{
	if (str.length() == 0)
	{
		throw "string is empty";
	}
}
void find_Max_Min_Numb(const std::string& str, std::string& max, std::string& min, const std::array<char, 5>& arr)
{
	size_t start = 0;
	size_t poz = 0;
	int16_t temp = 0;
	std::string strfin;
	Restring(strfin, str, arr);
	std::string tempstr;
	int16_t i_Max = INT16_MIN;
	int16_t i_Min = INT16_MAX;
	while (1)
	{
		poz = strfin.find(' ', start);
		if (poz == std::string::npos)
		{
			tempstr = strfin.substr(start);
			if (!tempstr.empty() && isNumb(tempstr))
			{
				temp = stoi(tempstr);
				if (temp > i_Max)
				{
					max = std::to_string(temp);
					i_Max = temp;
				}
				if (temp < i_Min)
				{
					min = std::to_string(temp);
					i_Min = temp;
				}
			}
			break;
		}

		tempstr = strfin.substr(start, poz - start);
		if (!tempstr.empty() && isNumb(tempstr))
		{
			temp = stoi(tempstr);
			if (temp > i_Max)
			{
				max = std::to_string(temp);
				i_Max = temp;
			}
			if (temp < i_Min)
			{
				min = std::to_string(temp);
				i_Min = temp;
			}
		}
		start = poz + 1;
	}
}
int isNumb(const std::string& str)
{
	int16_t size = str.length();
	if (size == 0)
	{
		return 0;
	}
	int16_t check = 0;
	if (str[0] == '-')
	{
		if (size == 1)
		{
			return 0;
		}
		check = 1;
	}
	for (size_t i = 0 + check; i < size; ++i)
	{
		if (!isdigit(str[i]))
		{
			return 0;
		}
	}
	return 1;
}
void Restring(std::string& strfin, const std::string& str, const std::array<char, 5>& arr)
{
	strfin = str;
	for (size_t i = 0; i < 5; ++i)
	{
		for (size_t k = 0; k < str.length(); ++k)
		{
			if (str[k] == arr[i])
			{
				strfin[k] = ' ';
			}
		}
	}
}
void Replace_Max_Min(std::string& str, const std::string& min, const std::string& max)
{
	size_t pos_max = str.find(max);
	size_t pos_min = str.rfind(min);
	if (pos_max == std::string::npos || pos_min == std::string::npos)
	{
		return;
	}
	if (pos_min > pos_max)
	{
		str.replace(pos_min, min.size(), max);
		str.replace(pos_max, max.size(), min);
	}
	else
	{
		str.replace(pos_max, max.size(), min);
		str.replace(pos_min, min.size(), max);
	}
}