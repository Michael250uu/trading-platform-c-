#include<iostream>
#include<windows.h>
#include<iostream>
#include"Commodity.h"
#include"common.h"
#include"Order.h"
#include"User.h"
using namespace std;
int main()
{
	Ccommodity commodity;
	
	Corder order;
	
	Cuser user; 
	
	for (;;)
	{
		cout << "============================================================"<<'\n';
		cout << "1.�û���¼  2.�û�ע��  3.����Ա��¼  4.�˳����� 5.��������"<<'\n';
	    cout << "============================================================"<<'\n';
		cout << "���������";
		int main_choose=cin_Choose();
		if (main_choose < 1 || main_choose>5)
		{
			cout << "*****��Ч����*****";
			Sleep(1000);
		}
		else if(main_choose==4)
		{
			cout << "*****�����˳�����...*****";
			Sleep(1000);
			system("cls");
			break;
		}
		system("cls");
		switch (main_choose)
		{
		case 1: //-----------------------------------------�������û�����--------------------------------------------------
		{
			int Nowid = user.Login();
			if (Nowid == -1)
				break;
			cout << "*****��½�ɹ�*****";
			Sleep(1000);
			system("cls");
			for (;;)
			{
				cout << "======================================================================" << endl;
				cout << "1.ע����¼ 2.������� 3.�������� 4.������Ϣ���� 5.��Ҫд�� 6.�ҵ�����" << endl;
				cout << "======================================================================" << endl;
				cout << "�������:";
				int U_choose = cin_Choose();
				if (U_choose == 1)
				{
					cout << "*****�����������˵�*****";
					Sleep(1000);
					system("cls");
					break;
				}else if(U_choose<1||U_choose>6)
				{
					cout << "*****��Ч����*****";
					Sleep(1000);
				}system("cls");
				switch(U_choose)
				{
				case 2: 
					for(;;)
					{
						cout << "========================================================================================" << endl;
						cout << "1.�鿴��Ʒ�б� 2.ȥ���� 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.�����û�������" << endl;
						cout << "========================================================================================" << endl;
						cout << "�������:";
						int b_choose = cin_Choose();
						if(b_choose==6)
						{
							cout << "*****���������û�������*****";
							Sleep(1000);
							system("cls");
							break;
						}
						else if(b_choose<1||b_choose>6)
						{
							cout << "*****��Ч����*****"; Sleep(1000); 
						}
						system("cls");
						switch(b_choose)
						{
						case 1:commodity.Show_B_Com( Nowid); break;
						case 2:commodity.BuyCom(Nowid);	break; 
						case 3:commodity.B_Search_Com(); break;
						case 4:order.Show_B_Ord( Nowid); break;
						case 5:commodity.KnowCom(); break;
						}
					}
					break;
				case 3:
					for (;;)
					{
						cout << "====================================================================================="<<endl;
						cout << "1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.�¼���Ʒ 5.�鿴��ʷ���� 6.�����û������� " << endl;
						cout << "=====================================================================================" << endl;
						cout << "���������";
						int s_choose = cin_Choose();
						if(s_choose==6)
						{
							cout << "*****���������û�������*****";
							Sleep(1000);
							system("cls");
							break;
						}
						else if (s_choose < 1 || s_choose>6)
						{
							cout << "*****��Ч����*****"; Sleep(1000);
						}
						system("cls");
						switch(s_choose)
						{
						case 1:commodity.AddCom( Nowid); break;
						case 2:commodity.Show_S_Com(Nowid); break;
						case 3:commodity.ModifyCom(Nowid); break;
						case 4:commodity.CancelCom_S( Nowid); break;
						case 5:order.Show_S_Ord( Nowid); break;
						
						}
					}
					break;
				case 4:
					for(;;)
					{
						cout << "================================================"<<endl;
						cout << "1.�����û������� 2.�޸���Ϣ 3.�鿴��Ϣ 4.��ֵ"<<endl;
						cout << "================================================" << endl;
						cout << "�������:";
						int k = cin_Choose();
						if(k==1)
						{
							cout << "*****���������û�������*****";
							Sleep(1000);
							system("cls");
							break;
						}
						if (k < 1 || k>4)
						{
							cout << "*****��Ч����*****"; Sleep(1000);
						}
						system("cls");
						switch(k)
						{
						case 2:user.Modify_User( Nowid); break;
						case 3:user.Show_U( Nowid); break;
						case 4: user.Kej_User(Nowid); break;
						}
					}
					break;
				case 5:user.WriteLetter(Nowid); break;
				case 6:user.ReadLetter(Nowid); break;
				}
			}
			break;
		}
		case 2: {user.Register();
			break; }
		case 3://-------------------------------------------�����ǹ���Ա�Ĳ���----------------------------------------------
		{
			string name; string key;
			cout << "���������Ա������";
			getline(cin, name);
			cout << "���������룺";
			getline(cin, key);
			if (key != "123456" || name != "admin")
			{
				cout << "*****��¼ʧ��!�����������˵�...*****";
				Sleep(1000);
				system("cls");
				break;
			}
			cout << "*****��¼�ɹ�*****";
			Sleep(1000);
			system("cls");
			for (;;)
			{
				cout << "=========================================================================================================" << endl;
				cout << "1.�鿴������Ʒ 2.������Ʒ 3.�鿴���ж��� 4.�鿴�����û� 5.ɾ���û� 6.�¼���Ʒ 7.ע�� 8.����ָ����Ʒ�ľ��� " << endl;
				cout << "=========================================================================================================" << endl;
				cout << "���������";
				int A_choose = cin_Choose();
				if (A_choose < 1 || A_choose>8)
				{
					cout << "*****��Ч����*****";
					Sleep(1000);
				}
				else if (A_choose == 7)
				{
					cout << "*****�����������˵�*****";
					Sleep(1000);
					system("cls");
					break;
				}
				system("cls");
				switch (A_choose)
				{
				case 1:commodity.Show_A_Com(); break;                                          //����Ա�鿴��Ʒ
				case 2:commodity.A_Search_Com(); break;                                            //����Ա����
				case 3:order.Show_A_Ord(); break;                                             //����Ա������
				case 4:user.Show_A_User(); break;                 //����Ա����
				case 5: user.DelUser(commodity); break;
				case 6: commodity.CancelCom2(); break;
				case 8:commodity.EndAuc(user,order);break;
				
				}
			}
			break;
		}
		case 5:user.FindKey(); break;
		}
	}
}

