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
		cout << "1.用户登录  2.用户注册  3.管理员登录  4.退出程序 5.忘记密码"<<'\n';
	    cout << "============================================================"<<'\n';
		cout << "输入操作：";
		int main_choose=cin_Choose();
		if (main_choose < 1 || main_choose>5)
		{
			cout << "*****无效操作*****";
			Sleep(1000);
		}
		else if(main_choose==4)
		{
			cout << "*****即将退出程序...*****";
			Sleep(1000);
			system("cls");
			break;
		}
		system("cls");
		switch (main_choose)
		{
		case 1: //-----------------------------------------以下是用户操作--------------------------------------------------
		{
			int Nowid = user.Login();
			if (Nowid == -1)
				break;
			cout << "*****登陆成功*****";
			Sleep(1000);
			system("cls");
			for (;;)
			{
				cout << "======================================================================" << endl;
				cout << "1.注销登录 2.我是买家 3.我是卖家 4.个人信息管理 5.我要写信 6.我的信箱" << endl;
				cout << "======================================================================" << endl;
				cout << "输入操作:";
				int U_choose = cin_Choose();
				if (U_choose == 1)
				{
					cout << "*****即将返回主菜单*****";
					Sleep(1000);
					system("cls");
					break;
				}else if(U_choose<1||U_choose>6)
				{
					cout << "*****无效操作*****";
					Sleep(1000);
				}system("cls");
				switch(U_choose)
				{
				case 2: 
					for(;;)
					{
						cout << "========================================================================================" << endl;
						cout << "1.查看商品列表 2.去竞拍 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面" << endl;
						cout << "========================================================================================" << endl;
						cout << "输入操作:";
						int b_choose = cin_Choose();
						if(b_choose==6)
						{
							cout << "*****即将返回用户主界面*****";
							Sleep(1000);
							system("cls");
							break;
						}
						else if(b_choose<1||b_choose>6)
						{
							cout << "*****无效操作*****"; Sleep(1000); 
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
						cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面 " << endl;
						cout << "=====================================================================================" << endl;
						cout << "输入操作：";
						int s_choose = cin_Choose();
						if(s_choose==6)
						{
							cout << "*****即将返回用户主界面*****";
							Sleep(1000);
							system("cls");
							break;
						}
						else if (s_choose < 1 || s_choose>6)
						{
							cout << "*****无效操作*****"; Sleep(1000);
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
						cout << "1.返回用户主界面 2.修改信息 3.查看信息 4.充值"<<endl;
						cout << "================================================" << endl;
						cout << "输入操作:";
						int k = cin_Choose();
						if(k==1)
						{
							cout << "*****即将返回用户主界面*****";
							Sleep(1000);
							system("cls");
							break;
						}
						if (k < 1 || k>4)
						{
							cout << "*****无效操作*****"; Sleep(1000);
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
		case 3://-------------------------------------------以下是管理员的操作----------------------------------------------
		{
			string name; string key;
			cout << "请输入管理员姓名：";
			getline(cin, name);
			cout << "请输入密码：";
			getline(cin, key);
			if (key != "123456" || name != "admin")
			{
				cout << "*****登录失败!即将返回主菜单...*****";
				Sleep(1000);
				system("cls");
				break;
			}
			cout << "*****登录成功*****";
			Sleep(1000);
			system("cls");
			for (;;)
			{
				cout << "=========================================================================================================" << endl;
				cout << "1.查看所有商品 2.搜索商品 3.查看所有订单 4.查看所有用户 5.删除用户 6.下架商品 7.注销 8.结束指定商品的竞拍 " << endl;
				cout << "=========================================================================================================" << endl;
				cout << "输入操作：";
				int A_choose = cin_Choose();
				if (A_choose < 1 || A_choose>8)
				{
					cout << "*****无效操作*****";
					Sleep(1000);
				}
				else if (A_choose == 7)
				{
					cout << "*****即将返回主菜单*****";
					Sleep(1000);
					system("cls");
					break;
				}
				system("cls");
				switch (A_choose)
				{
				case 1:commodity.Show_A_Com(); break;                                          //管理员查看商品
				case 2:commodity.A_Search_Com(); break;                                            //管理员搜索
				case 3:order.Show_A_Ord(); break;                                             //管理员看订单
				case 4:user.Show_A_User(); break;                 //管理员看人
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

