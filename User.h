#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef _User_H_
#define _User_H_
#include <string>
#include"Commodity.h"
#include"Order.h"

class Ccommodity;
class Cuser
{
private:
	struct User
	{
		int UserID;
		string Key;
		string Name;
		string Phone;
		string Address;
		double Money;
		bool Con;
		User* next=NULL;
	}Head, * Tail;
	User* NowUser(int s)//返回当前用户指针
	{
		for (User* p = Head.next; p != NULL; p = p->next)
			if (p->UserID == s)
				return p;
	}
public:
	Cuser();
	int Login();
	void Register();
	
	void DelUser( Ccommodity&);
	void Show_A_User();
	void Show_U(int);
	void Modify_User(int);
	void Kej_User(int);
	void Cover_User();
	//void BuyCom(Ccommodity&, Corder&, int);//(购买)
	void WriteLetter(int);
	void ReadLetter(int);
	void FindKey();
	bool FindUser(int);
	int GetMon(int);
	void DecMon(int, double);
	void IncMon(int, double);
	//void SearchOrder( Corder&);
};

#endif 