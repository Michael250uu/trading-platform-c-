
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
	  Ccommodity() ;//���캯����ʼ��
	  void AddCom( int);//��ͷ
	  void CancelCom1(int);//��ͷ��id(�¼�)(cancel user)
	  void CancelCom2();//����Ա�¼�
	  void CancelCom_S( int);//�����¼�
	  void ModifyCom( int);//��ͷ��id��
	  void Show_S_Com( int);//(�鿴������Ʒ)
	  void Show_B_Com(int);//(��ҿ���Ʒ)
	  void Show_A_Com();//(����Ա�鿴)
	  void A_Search_Com();//(����Ա����)
	  void BuyCom(int);//����
	  void KnowCom();//(��Ҳ鿴��ϸ��Ϣ)
	  void B_Search_Com();//�������
	  void CoverCom();
	  void CoverAuc(int,const Commodity*);
	  void EndAuc(Cuser& , Corder&  );

  };


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             #endif