#include "Order.h"
#include<iostream>
#include<string>
#include<fstream>
#include"common.h"
using namespace std;
Corder ::Corder()
{
	
	ifstream F("Order.txt");
	if (!F)
	{
		cout << "Error opening Order";
		exit(1);
	}
	char c;
	F >> c;
	if (F.eof()) { F.close(); return; }
	else
		F.seekg(0, ios::beg);
	Tail = &Head;
	while(!F.eof())
	{
		Order* p = new Order;
		p->next = NULL; Tail->next = p; Tail = p;
		string str;
		F >> str;
		p->OrdID = tran_ID(str);
		F >> str;
		p->ComID = tran_ID(str);
		F >> p->TraMoney;
		F >> str;
		p->Year = tran_Year(str); p->Month = tran_Month(str); p->Day = tran_Day(str);
		F >> str;
		p->BuyerID = tran_ID(str);
		F >> str;
		p->SellerID = tran_ID(str);
	}
	F.close();
   
}
void Corder::AddOrd(int c, double m, int b, int s)
{
	Order* p = new Order; p->next = NULL; p->TraMoney = m; p->BuyerID = b; p->SellerID = s; p->ComID = c; p->Year = year(); p->Month = month(); p->Day = day();
	for (Order* q = Head.next;; q = q->next)
		if (q == NULL)
		{
			p->OrdID = 1; Head.next = p; break;
		}
		else if (q->next == NULL)
		{
			p->OrdID = q->OrdID + 1; q->next = p; break;
		}
	CoverOrd();
}
void Corder::Show_A_Ord()//----------------------------------------------------------------------------------����Ա������
{
	cout << "********************************************************************************" << '\n';
	cout << "ID         ��ƷID    ���׽��    ����ʱ��         ���ID       ����ID"<<endl;
	for(Order*p=Head.next;p!=NULL;p=p->next)
		printf("T%03d       M%03d       %-10.1lf%d-%02d-%02d        U%03d         U%03d\n", p->OrdID,p->ComID, p->TraMoney,p->Year,p->Month,p->Day,p->BuyerID,p->SellerID);
	cout<< "********************************************************************************" << '\n';
	cout << "���س��ص�����Ա����...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Corder::Show_B_Ord( int a)
{
	cout << "********************************************************************************"<<endl;
	cout<<"ID         ��ƷID    ���׽��    ����ʱ��         ���ID       ����ID" << '\n';
	for(Order*p=Head.next;p!=NULL;p=p->next)
		if(p->BuyerID==a)
			printf("T%03d       M%03d       %-10.1lf%d-%02d-%02d        U%03d         U%03d\n", p->OrdID, p->ComID, p->TraMoney, p->Year, p->Month, p->Day, p->BuyerID, p->SellerID);
	cout << "********************************************************************************" << '\n';
	cout << "���س��ص�����Ա����...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Corder::Show_S_Ord(int s)
{
	cout << "********************************************************************************" << endl;
	cout << "ID         ��ƷID    ���׽��    ����ʱ��         ���ID       ����ID" << '\n';
	for (Order* p = Head.next; p != NULL; p = p->next)
		if (p->SellerID == s)
			printf("T%03d       M%03d       %-10.1lf%d-%02d-%02d        U%03d         U%03d\n", p->OrdID, p->ComID, p->TraMoney, p->Year, p->Month, p->Day, p->BuyerID, p->SellerID);
	cout << "********************************************************************************" << '\n';
	cout << "���س��ص�������...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Corder::CoverOrd()
{
	FILE* fp = fopen("Order.txt", "w+"); Order* p = Head.next;
	for (; p->next != NULL; p = p->next)
		fprintf(fp, "T%03d M%03d %.1lf %d-%02d-%02d U%03d U%03d\n", p->OrdID, p->ComID, p->TraMoney, p->Year, p->Month, p->Day, p->BuyerID, p->SellerID);
	fprintf(fp, "T%03d M%03d %.1lf %d-%02d-%02d U%03d U%03d", p->OrdID, p->ComID, p->TraMoney, p->Year, p->Month, p->Day, p->BuyerID, p->SellerID);
	fclose(fp);
}
