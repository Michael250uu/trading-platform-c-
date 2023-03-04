#include<iostream>
#include<string>
#include<math.h>
#include<windows.h>
#include"common.h"
#include<time.h>
using namespace std;
int tran_ID(string str)
{
	int a;
	a = (str[1] - 48) * 100 + (str[2] - 48) * 10 + (str[3] - 48) ;
	return a;
}
int tran_Year(string str)
{
	int a;
	a = (str[0] - 48) * 1000 + (str[1] - 48) * 100 + (str[2] - 48) * 10 + str[3] - 48;
	return a;
}
int tran_Month(string str)
{
	int a;
	a = (str[5] - 48) * 10 + str[6] - 48;
	return a;
}
int tran_Day(string str)
{
	int a;
	a = (str[8] - 48) * 10 + (str[9] - 48);
	return a;
}
int cin_Choose()
{
	string str; 
	getline(cin, str);
	int len = str.size();
	if (len > 1)
		return 0;
	else if (str[0] < 48 || str[0]>57)
		return 0;
	else
		return str[0] - 48;
}
bool check_input(string str)
{
	for (int i = 0; i < str.size(); i++)
		if (str[i] == ' ')
			return 1;
	return 0;
}
bool check_ID(string str)
{
	if (str.size() != 4 || str[0] != 'M')
		return 1;
	for (int i = 1; i < 4; i++)
		if (str[i] < '0' || str[i]>'9')
			return 1;
	return 0;
}
int year()
{
	time_t t= time(NULL);
	tm* tp = localtime(&t);
	return tp->tm_year+1900;
}
int month()
{
	time_t t = time(NULL);
	tm* tp = localtime(&t);
	return tp->tm_mon + 1;
}
int day()
{
	time_t t = time(NULL);
	tm* tp = localtime(&t);
	return tp->tm_mday;
}
int hour()
{
	time_t t = time(NULL);
	tm* tp = localtime(&t);
	return tp->tm_hour;
}
int minute()
{
	time_t t = time(NULL);
	tm* tp = localtime(&t);
	return tp->tm_min;
}
int second()
{
	time_t t = time(NULL);
	tm* tp = localtime(&t);
	return tp->tm_sec;
}
bool check_m(string str)
{
	if (str.size()<3)
		return 1;
	if (str[str.size() - 2] != '.'||str[str.size()-1]>'9'|| str[str.size() - 1] < '0')
		return 1;
	for (int i = 0; i < str.size() - 2; i++)
		if (str[str.size() - 1] > '9' || str[str.size() - 1] < '0')
			return 1;
	return 0;
}
double tran_m(string str)
{
	double a = 0;
	for (int i = 0, j = str.size() - 3; i <= str.size() - 3; i++, j--)
		a += (str[i]-'0') * pow(10, j);
	a += 0.1 * (str[str.size() - 1] - '0');
	return a;
}

bool check_UID(string str)
{
	if (str.size() != 4 || str[0] != 'U')
		return 1;
	for (int i = 1; i < 4; i++)
		if (str[i] < '0' || str[i]>'9')
			return 1;
	return 0;
}

bool check_num(string str)
{
	for (int i = 0; i < str.size(); i++)
		if (str[i] < '0' || str[i]>'9')
			return 1;
	return 0;
}

