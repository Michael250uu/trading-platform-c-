
#pragma once
#ifndef _Commodity_H_
#define _Commodity_H_
#include<string>
#include<iostream>
#include"User.h"
#include"Order.h"
using namespace std;

class Cuser;
  class Ccommodity
  {
	  struct Auction
	  {
		  int s_id;
		  double offer;
		  Auction* Anext = NULL;
		  //int Year, Month, Day,Hour,Minu,Sec;
	  };
	  struct Commodity
	  {
		  int ComID;
		  string Name;
		  double Price;
		  int SellerID;
		  int Condition;
		  int num=0;
		  int Year, Month, Day;
		  string Description;
		  Commodity* next=NULL;
		  int flag=0 ;
		  Auction* Anext = NULL;
	  }Head,*Tail;
  public:
	  Ccommodity() ;//构造函数初始化
	  void AddCom( int);//表头
	  void CancelCom1(int);//表头，id(下架)(cancel user)
	  void CancelCom2();//管理员下架
	  void CancelCom_S( int);//卖家下架
	  void ModifyCom( int);//表头，id，
	  void Show_S_Com( int);//(查看发布商品)
	  void Show_B_Com(int);//(买家看商品)
	  void Show_A_Com();//(管理员查看)
	  void A_Search_Com();//(管理员搜索)
	  void BuyCom(int);//竞拍
	  void KnowCom();//(买家查看详细信息)
	  void B_Search_Com();//买家搜索
	  void CoverCom();
	  void CoverAuc(int,const Commodity*);
	  void EndAuc(Cuser& , Corder&  );

  };


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             #endif