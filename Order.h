#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef _Order_H_
#define _Order_H_
#include<string>
using namespace std;
class Corder 
{
struct Order
{
	int OrdID;
	int ComID;
	double TraMoney;
	int Year, Month, Day;
	int SellerID, BuyerID;
	Order* next=NULL;
}Head,*Tail;

public:
  Corder ();
  void AddOrd(int, double, int, int);
  void Show_A_Ord();
  void Show_B_Ord( int);
  void Show_S_Ord(int);
  void CoverOrd( );
};

#endif