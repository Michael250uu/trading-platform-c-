#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include"Commodity.h"
#include"common.h"
#include<windows.h>
#include"User.h"
#include"Order.h"
#include<iomanip>
using namespace std;

Ccommodity ::Ccommodity()//-------------------------------------------------------------------创建商品链表
{
	
	ifstream F("Commodity.txt");
	if(!F)
	{
		cout << "Error opening Commodity";
		exit(1);
	}
	char c;
	F >> c;
	if (F.eof()) { F.close(); return; }
	else
		F.seekg(0, ios::beg);
	
	  Tail=&Head;
	while(!F.eof())
	{
		
		Commodity* p = new Commodity;
		Tail->next = p; p->next = NULL; Tail = p;
		string str;
		F >> str; 
		p->ComID = tran_ID(str);
		F >>p->Name ;
		F>>p->Price;
		F >> p->Description;
		F>>str;
		p->SellerID = tran_ID(str);
		F >> str;
		p->Year = tran_Year(str); p->Month = tran_Month(str); p->Day = tran_Day(str);
		F >> p->num;
		F >> p->flag;
		if (p->flag == 1)
		{
			int n = p->ComID;
			int w = 1;
			for (;; w++)
				if (n / pow(10, w) < 1)
					break;
			char a[100];
			for (int i = 0, j = w - 1; i < w; i++, j--)
			{
				int b = n % 10;
				a[j] = (char)(b + '0');
				n = (n - b) / 10;
			}
			a[w] = 'a'; a[w + 1] = '.'; a[w + 2] = 't'; a[w + 3] = 'x'; a[w + 4] = 't'; a[w + 5] = '\0';
			ifstream ft(a);Auction* t=NULL;
			while (!ft.eof())
			{
				
				Auction* q = new Auction;
				ft >> q->s_id >> q->offer; q->Anext = NULL;
				if (p->Anext == NULL)
				{
					p->Anext = q; t = q;
				}
				else
				{
					t->Anext = q; t = q;
				}
			}
			ft.close();
		}
		F >> str;
		if (str == "已下架")
			p->Condition = 0;
		else if (str == "销售中")
			p->Condition = 1;
		else
			p->Condition = 2;
		
		
	}F.close();
	
}
void Ccommodity::CancelCom1( int a)
{
	for (Commodity* p = Head.next; p != NULL; p = p->next)
		if (a == p->SellerID && p->Condition == 1)
		{
			p->Condition = 0;
			p->flag = 0;
		}
	CoverCom();
}
void Ccommodity::CancelCom2()
{
	cout << "请输入下架商品的ID："; string str;
	getline(cin, str);
	if (check_ID(str))
	{
		cout << "*****ID格式错误!即将返回管理员菜单*****"; Sleep(1000); system("cls"); return;
	}
	
	int a = tran_ID(str); Commodity* p = Head.next;
	for (; p != NULL; p = p->next)
		if (p->ComID == a&&p->Condition==1)
		{
			printf("确认要下架该商品吗？\n\n****************\n");
			cout << "ID          名称           价格           上架时间         数量           卖家id         商品状态" << '\n';
			printf("M%03d        ", p->ComID);
			printf("%-15s", p->Name.c_str());
			printf("%-15.1lf", p->Price);
			printf("%d-%02d-%02d       ", p->Year, p->Month, p->Day);
			printf("%-15d", p->num);
			printf("U%03d        ", p->SellerID);
			printf("销售中\n");
			cout << "****************";
		}
	if (p == NULL)
	{
		cout << "*****查无此商品!即将返回管理员菜单*****"; Sleep(1000); system("cls"); return;
	}
	getline(cin, str);
	if (str != "y" && str != "n")
	{
		cout << "*****无效操作！即将返回管理员菜单*****"; Sleep(1000); system("cls"); return;
	}
	else if (str == "n")
	{
		cout << "*****删除失败！即将返回管理员菜单*****"; Sleep(1000); system("cls"); return;
	}
	else
	{
		p->Condition = 0; p->flag = 0; CoverCom(); cout << "*****删除成功*****"; Sleep(1000); system("cls"); return;
	}
}
void Ccommodity::CancelCom_S( int s)
{
	cout << "请输入下架商品ID:"; string str; getline(cin, str);
	if(check_ID(str))
	{
		cout << "*****ID格式错误，即将返回*****"; Sleep(1000); system("cls"); return;
	}
	int c = tran_ID(str);
	for (Commodity* p = Head.next; p != NULL; p = p->next)
		if (p->ComID == c && p->SellerID == s && p->Condition == 1)
		{
			cout << "您确认要下架该商品吗？" << endl<<endl;
			cout<<"*******************************"<<endl;
			cout << "ID          名称           价格           上架时间         数量           卖家id         商品状态" << '\n';
			printf("M%03d        ", p->ComID);
			printf("%-15s", p->Name.c_str());
			printf("%-15.1lf", p->Price);
			printf("%d-%02d-%02d       ", p->Year, p->Month, p->Day);
			printf("%-15d", p->num);
			printf("U%03d        ", p->SellerID);
			printf("销售中\n");
			cout << "*******************************" << endl;
			cout << "请选择（y/n） "; getline(cin, str);
			if(str!="y"&&str!="n")
			{
				cout << "*****无效操作*****"; Sleep(1000); system("cls"); return;
			}
			if(str=="n")
			{
				cout << "操作已取消！"; Sleep(1000); system("cls"); return;
			}
			else
			{
				p->Condition = 0; p->flag = 0; CoverCom(); cout << "下架成功！"; Sleep(1000); system("cls"); return;
			}
		}
	cout << "*****无法进行该操作*****"; Sleep(1000); system("cls"); return;
}
void Ccommodity::Show_S_Com(int s)
{
	cout << endl;
	cout << "您发布的商品清单如下" << endl;
	cout << "***************************************************************************************"<<endl;
	cout << "ID          名称           价格           数量           上架时间           商品状态" << '\n';
	for (Commodity* p = Head.next; p != NULL; p = p->next)
	if(p->SellerID==s)
	{
		printf("M%03d        ", p->ComID);
		printf("%-15s", p->Name.c_str());
		printf("%-15.1lf", p->Price);
		printf("%-15d", p->num);
		printf("%d-%02d-%02d         ", p->Year, p->Month, p->Day);
		if (p->Condition == 1)
			printf("销售中\n");
		else if (p->Condition == 0)
			printf("已下架\n");
		else
			printf("已售出\n");
	}
	cout << "***************************************************************************************"<<endl;
	cout << "按回车回到卖家界面...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Ccommodity::Show_B_Com( int a)
{
	cout << "************************************************************************************" << '\n';
	cout << "ID          名称           价格           数量           上架时间           卖家ID" << '\n';
	for (Commodity* p = Head.next; p != NULL; p = p->next)
		if (p->Condition == 1 )
			printf("M%03d        %-15s%-15.1lf%-15d%d-%02d-%02d         U%03d\n", p->ComID, p->Name.c_str(), p->Price, p->num, p->Year, p->Month, p->Day, p->SellerID);
	cout << "************************************************************************************" << '\n';
	cout << "按回车回到主界面...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Ccommodity::Show_A_Com()//---------------------------------------------------------------------------------------------------给管理员看商品
{
	cout << "*******************************************************************************************************"<<'\n';
	cout << "ID          名称           价格           上架时间           卖家ID            数量           商品状态"<<'\n';
	for(Commodity*p=Head.next;p!=NULL;p=p->next)
	{
		printf("M%03d        ", p->ComID);
		printf("%-15s", p->Name.c_str());
		printf("%-15.1lf", p->Price);
		printf("%d-%02d-%02d         ", p->Year, p->Month, p->Day);
		printf("U%03d               ", p->SellerID);
		printf("%-15d", p->num);
		if (p->Condition == 1)
			printf("销售中\n");
		else if (p->Condition == 0)
			printf("已下架\n");
		else
			printf("已售出\n");
	}
	cout << "*******************************************************************************************************" << '\n';
	cout << "按回车回到管理员界面...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Ccommodity::A_Search_Com()//----------------------------------------------------------------------------------------管理员搜索
{
	cout << "请输入商品名称:";
	string str; getline(cin, str);
	cout << "******************************************************************************************" << '\n';
	
	int flag=0;
	for (Commodity* p = Head.next; p != NULL; p = p->next)
		if (p->Name.find(str) != string::npos)
		{
			flag = 1; break;
		}
	if (flag == 0)
	{
		cout <<'\n'<< "                        未找到你想搜索的商品！" << endl<<endl;
		cout << "********************************************************************************************************" << '\n';
	}
	else 
	{
		cout << "ID          名称           价格           上架时间           卖家ID            数量           商品状态" << '\n';
		for (Commodity* p = Head.next; p != NULL; p = p->next)
			if (p->Name.find(str) != string::npos)
			{
				flag = 1;
				printf("M%03d        ", p->ComID);
				printf("%-15s", p->Name.c_str());
				printf("%-15.1lf", p->Price);
				printf("%d-%02d-%02d         ", p->Year, p->Month, p->Day);
				printf("U%03d               ", p->SellerID);
				printf("%-15d", p->num);
				if (p->Condition == 1)
					printf("销售中\n");
				else if (p->Condition == 0)
					printf("已下架\n");
				else
					printf("已售出\n");
			}
		cout << "********************************************************************************************************" << '\n';
	}
	cout << "按回车回到管理员界面...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Ccommodity::BuyCom(int u)
{
	cout << "请输入您想竞拍的商品id:";
	string str;
	getline(cin, str);
	if (check_ID(str))
	{
		cout << "*****ID格式有误，即将返回买家菜单*****"; Sleep(1000); system("cls"); return;
	}
	int a = tran_ID(str), flag = 0; cout << "******************" << endl;
	for (Commodity* p = Head.next; p != NULL; p = p->next)
		if (p->ComID == a && p->Condition == 1)
		{
			flag = 1; break;
		}
	if (flag == 0)
	{
		cout << '\n' << "未找到你想竞拍的商品！即将返回" << endl << endl;
		cout << "******************" << '\n';
		Sleep(1000); system("cls"); return;
	}
	else
	{
		Commodity* p = Head.next;
		for (; p != NULL; p = p->next)
			if (p->ComID == a)
			{
				cout << "名称：    " << p->Name << endl;
				cout << "描述：    " << p->Description << endl;
				printf("上架时间：%d-%02d-%02d\n", p->Year, p->Month, p->Day);
				printf("商品数量：%d\n", p->num);
				printf("价格：    %.1lf\n", p->Price);
				printf("卖家ID：  U%03d\n", p->SellerID); break;
			}
		cout << "******************" << endl<<"商品信息如上...\n\n\n";
		cout << "请输入您的报价:";
		getline(cin, str);
		if(check_m(str))
		{
			cout << "金额输入错误，即将返回..."; Sleep(1000); system("cls"); return;
		}
		double temp= tran_m(str);
		if (temp < p->Price)
		{
			cout << "报价低于最低给定价格，即将返回..."; Sleep(1000); system("cls"); return;
		}
		Auction* a = new Auction;
		a->offer =temp;
		a->s_id = u;
		a->Anext = NULL;
		if (p->Anext == NULL)
		{
			p->Anext = a;
			p->flag = 1;
			CoverCom();
			CoverAuc(p->ComID, p);
			cout << "\n报价成功！即将返回..."; Sleep(1000); system("cls"); return;
		}
		else
		{
			for (Auction* tp = p->Anext; ; tp = tp->Anext)
				if (tp->Anext == NULL)
				{
					tp->Anext = a; break;
				}
			CoverAuc(p->ComID,p);
			cout << "\n报价成功！即将返回..."; Sleep(1000); system("cls"); return;
		}

	}
	
}
void Ccommodity:: CoverCom()
{
	FILE* fp = fopen("Commodity.txt", "w+"); Commodity* p = Head.next;
	for (; p->next != NULL; p = p->next)
	{
		fprintf(fp, "M%03d %s %.1lf %s U%03d %d-%02d-%02d %d %d ", p->ComID, p->Name.c_str(), p->Price, p->Description.c_str(), p->SellerID, p->Year, p->Month, p->Day,p->num,p->flag);
		if (p->Condition == 0)fprintf(fp, "已下架\n");
		else if (p->Condition == 1)fprintf(fp, "销售中\n");
		else fprintf(fp, "已售出\n");
	}
	fprintf(fp, "M%03d %s %.1lf %s U%03d %d-%02d-%02d %d %d ", p->ComID, p->Name.c_str(), p->Price, p->Description.c_str(), p->SellerID, p->Year, p->Month, p->Day,p->num,p->flag);
	if (p->Condition == 0)fprintf(fp, "已下架");
	else if (p->Condition == 1)fprintf(fp, "销售中");
	else fprintf(fp, "已售出");
	fclose(fp);
}

void Ccommodity::KnowCom()
{
	cout << "请输入商品的ID：";
	string str; getline(cin, str);
	if(check_ID(str))
	{
		cout << "*****ID格式有误，即将返回买家菜单*****"; Sleep(1000); system("cls"); return;
	}
	int a = tran_ID(str),flag=0; cout << "******************" << endl;
	for (Commodity* p = Head.next; p != NULL; p = p->next)
		if (p->ComID == a&&p->Condition==1)
		{
			flag = 1; break;
		}
	if (flag == 0)
	{
		cout << '\n' << "未找到你想搜索的商品！" << endl << endl;
		cout << "******************" << '\n';
	}
	else
	{
		for (Commodity* p = Head.next; p != NULL; p = p->next)
			if (p->ComID == a)
			{
				cout << "名称：    " << p->Name << endl;
				cout << "描述：    " << p->Description << endl;
				printf("上架时间：%d-%02d-%02d\n", p->Year, p->Month, p->Day);
				printf("商品数量：%d\n", p->num);
				printf("价格：    %.1lf\n", p->Price);
				printf("卖家ID：  U%03d\n", p->SellerID); break;
			}
		cout << "******************"<<endl;
	}
	cout << "按回车回到主界面...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Ccommodity::AddCom(int s)
{
	Commodity* p = new Commodity; p->next = NULL;
	string str;
	cout << "请输入商品名称：";
	getline(cin, str);
	if (check_input(str)) 
	{ 
		cout << "*****输入请勿包含空格！即将返回卖家菜单*****"; Sleep(1000); system("cls"); return; 
	}
	p->Name = str;
	cout << "请输入商品金额："; getline(cin, str);
	if (check_m(str))
	{
		cout << "*****请正确输入金额！即将返回卖家菜单*****"; Sleep(1000); system("cls"); return;
	}
	p->Price = tran_m(str);

	cout << "请输入商品数量："; getline(cin, str);
	if (check_num(str))
	{
		cout << "*****请正确输入数量！即将返回卖家菜单*****"; Sleep(1000); system("cls"); return;
	}
	p->num = atoi(str.c_str());

	cout << "请输入商品描述："; getline(cin, str);
	if (check_input(str)) 
	{ 
		cout << "*****输入请勿包含空格！即将返回卖家菜单*****"; Sleep(1000); system("cls"); return; 
	}
	p->Description = str;
	cout << endl << "请确认发布商品信息无误" << endl;
	cout << "***********************"<<endl;
	cout << "商品名称：" << p->Name<<endl;
	cout << "商品金额：" << p->Price << endl;
	cout << "商品数量：" << p->num << endl;
	cout << "商品描述：" << p->Description << endl;
	cout << "***********************"<<endl<<endl;
	cout << "您确认要发布该商品吗 （y/n） ";
	getline(cin, str);
	if(str!="y"&&str!="n")
	{
		cout << "*****无效操作！即将返回卖家菜单*****"; Sleep(1000); system("cls"); return;
	}
	else if(str=="n")
	{
		cout << "*****操作已取消，即将返回*****"; Sleep(1000); system("cls"); return;
	}
	else
	{
		p->Condition = 1; p->Year = year(); p->Month = month(); p->Day = day(); p->SellerID = s;
		for (Commodity* q = Head.next;; q = q->next)
			if(q==NULL)
			{ 
				p->ComID = 1; Head.next = p; CoverCom();
				cout << "发布商品成功！"; Sleep(1000); system("cls"); return;
			}
			else if (q->next == NULL)
			{
				p->ComID = q->ComID + 1; 
				q->next = p; CoverCom();
				cout << "发布商品成功！"; Sleep(1000); system("cls"); return;
			}
	}


}
void Ccommodity::ModifyCom(int s)
{
	cout << "请输入商品ID：";
	string str; getline(cin, str);
	if (check_ID(str))
	{
		cout << "*****ID格式错误，即将返回*****"; Sleep(1000); system("cls"); return;
	}
	Commodity* p = Head.next;
	for(;p!=NULL;p=p->next)
		if(p->ComID==tran_ID(str)&&p->Condition==1&&p->SellerID==s)
		{
			cout << "请输入商品修改属性（1.价格 2.描述） "; int c = cin_Choose();
			if(c<1||c>2)
			{
				cout << "*****无效操作*****"; Sleep(1000); system("cls"); return;
			}
			else if(c==1)
			{
				cout << "请输入修改后的价格：";
				getline(cin, str);
				if(check_m(str))
				{
					cout << "*****金额格式错误*****"; Sleep(1000); system("cls"); return;
				}
				double m = tran_m(str); cout <<endl<< "请确认修改后的商品信息"<<endl;
				cout << "**********************************"<<endl;
				cout << "商品ID：  "; printf("M%03d\n", p->ComID);
				cout << "商品名称：" << p->Name<<endl;
				cout << "商品价格：" <<fixed<<setprecision(1)<< m<<endl;
				cout << "商品描述：" << p->Description<<endl;
				cout << "**********************************" << endl;
				cout << "确认修改（y/n） "; getline(cin, str);
				if(str!="y"&&str!="n")
				{
					cout << "无效操作！"; Sleep(1000); system("cls"); return;
				}
				else if(str=="n")
				{
					cout << "操作已取消！"; Sleep(1000); system("cls"); return;
				}
				else
				{
					p->Price = m; CoverCom(); cout << "修改成功！"; Sleep(1000); system("cls"); return;
				}
			}
			else
			{
				cout << "请输入修改后商品的描述：";
				getline(cin, str);
				if (check_input(str))
				{
					cout << "请勿输入空格！"; Sleep(1000); system("cls"); return;
				}
				cout << endl << "请确认修改后的商品信息" << endl;
				cout << "**********************************" << endl;
				cout << "商品ID： "; printf("M%03d\n", p->ComID);
				cout << "商品名称：" << p->Name << endl;
				cout << "商品价格：" << fixed << setprecision(1) << p->Price<< endl;
				cout << "商品描述：" << str << endl;
				cout << "**********************************" << endl;
				cout << "确认修改（y/n） "; string str_; getline(cin, str_);
				if (str_ != "y" && str_ != "n")
				{
					cout << "无效操作！"; Sleep(1000); system("cls"); return;
				}
				else if (str_ == "n")
				{
					cout << "操作已取消！"; Sleep(1000); system("cls"); return;
				}
				else
				{
					p->Description = str; CoverCom(); cout << "修改成功！"; Sleep(1000); system("cls"); return;
				}
			}
		}
	cout << "*****无法进行该操作*****"; Sleep(1000); system("cls"); return;

}

void Ccommodity::B_Search_Com()
{
	for (;;)
	{
		cout << "请选择搜索方式（1.名称 2.价格范围 3.描述 ）";
		int choose = cin_Choose();
		if (choose < 1 || choose>3)
		{
			cout << "无效操作！"; Sleep(1000); system("cls"); continue;
		}system("cls");
		switch (choose)
		{
		case 1:
		{
			cout << "请输入商品名称:";
			string str; getline(cin, str);
			cout << "********************************************************************************" << '\n';

			int flag = 0;
			for (Commodity* p = Head.next; p != NULL; p = p->next)
				if (p->Name.find(str) != string::npos && p->Condition == 1)
				{
					flag = 1; break;
				}
			if (flag == 0)
			{
				cout << '\n' << "                        未找到你想搜索的商品！" << endl << endl;
				cout << "********************************************************************************" << '\n';
			}
			else
			{
				cout << "ID          名称           价格           上架时间           数量           卖家ID" << '\n';
				for (Commodity* p = Head.next; p != NULL; p = p->next)
					if (p->Name.find(str) != string::npos && p->Condition == 1)
					{
						flag = 1;
						printf("M%03d        ", p->ComID);
						printf("%-15s", p->Name.c_str());
						printf("%-15.1lf", p->Price);
						printf("%d-%02d-%02d         ", p->Year, p->Month, p->Day);
						printf("%-15d", p->num);
						printf("U%03d\n", p->SellerID);

					}
				cout << "********************************************************************************" << '\n';
			}
			cout << "按回车回到买家界面...";
			while (!(getchar() == '\n')) {}system("cls"); return;
		}
		case 2:
		{
			for (;;)
			{
				cout << "请输入价格下界：";
				string str; getline(cin, str);
				if (check_m(str))
				{
					cout << "金额格式错误！"; Sleep(1000); system("cls"); continue;
				}
				double min = tran_m(str);
				cout << "请输入价格上界：";
				getline(cin, str);
				if (check_m(str))
				{
					cout << "金额格式错误！"; Sleep(1000); system("cls"); continue;
				}
				double max = tran_m(str);
				cout << "********************************************************************************" << '\n';
				int flag = 0;
				for (Commodity* p = Head.next; p != NULL; p = p->next)
					if (p->Price >= min && p->Price <= max && p->Condition == 1)
					{
						flag = 1; break;
					}
				if (flag == 0)
				{
					cout << '\n' << "                        未找到你想搜索的商品！" << endl << endl;
					cout << "********************************************************************************" << '\n';
				}
				else
				{
					cout << "ID          名称           价格           上架时间           数量           卖家ID" << '\n';
					for (Commodity* p = Head.next; p != NULL; p = p->next)
						if (p->Price >= min && p->Price <= max && p->Condition == 1)
						{
							flag = 1;
							printf("M%03d        ", p->ComID);
							printf("%-15s", p->Name.c_str());
							printf("%-15.1lf", p->Price);
							printf("%d-%02d-%02d         ", p->Year, p->Month, p->Day);
							printf("%-15d", p->num);
							printf("U%03d\n", p->SellerID);

						}
					cout << "********************************************************************************" << '\n';
				}
				cout << "按回车回到买家界面...";
				while (!(getchar() == '\n')) {}system("cls"); return;
			}
		}
		case 3:
		{
			cout << "请输入商品描述:";
			string str; getline(cin, str);
			cout << "********************************************************************************" << '\n';
			int flag = 0;
			for (Commodity* p = Head.next; p != NULL; p = p->next)
				if (p->Description.find(str) != string::npos && p->Condition == 1)
				{
					flag = 1; break;
				}
			if (flag == 0)
			{
				cout << '\n' << "                        未找到你想搜索的商品！" << endl << endl;
				cout << "********************************************************************************" << '\n';
			}
			else
			{
				cout << "ID          名称           价格           上架时间           数量           卖家ID" << '\n';
				for (Commodity* p = Head.next; p != NULL; p = p->next)
					if (p->Description.find(str) != string::npos && p->Condition == 1)
					{
						flag = 1;
						printf("M%03d        ", p->ComID);
						printf("%-15s", p->Name.c_str());
						printf("%-15.1lf", p->Price);
						printf("%d-%02d-%02d         ", p->Year, p->Month, p->Day);
						printf("%-15d", p->num);
						printf("U%03d\n", p->SellerID);

					}
				cout << "********************************************************************************" << '\n';
			}
			cout << "按回车回到买家界面...";
			while (!(getchar() == '\n')) {}system("cls"); return;
		}


		}
	}

}

void Ccommodity::CoverAuc(int cid,const Commodity*p)
{
	int n = cid;
	int w = 1;
	for (;; w++)
		if (n / pow(10, w) < 1)
			break;
	char a[100];
	for (int i = 0, j = w - 1; i < w; i++, j--)
	{
		int b = n % 10;
		a[j] = (char)(b + '0');
		n = (n - b) / 10;
	}
	a[w] = 'a'; a[w+1] = '.'; a[w + 2] = 't'; a[w + 3] = 'x'; a[w + 4] = 't'; a[w + 5] = '\0';
	ofstream F(a);
	for (Auction* tp = p->Anext; tp != NULL; tp = tp->Anext)
		F << ' ' << tp->s_id << ' ' << tp->offer;
	F.close();

}

void Ccommodity::EndAuc(Cuser& user, Corder& order)
{
	cout << "输入您想结束竞拍的商品id:";
	string str;
	getline(cin, str);
	if (check_ID(str))
	{
		cout << "\nid格式错误，即将返回......";
		Sleep(1000); system("cls"); return;
	}
	int a = tran_ID(str), flag = 0; 
	Commodity* p = Head.next;
	for (; p != NULL; p = p->next)
		if (p->ComID == a && p->Condition == 1&&p->flag==1)
		{
			flag = 1; break;
		}
	if (flag == 0)
	{
		cout << '\n' << "无法执行该操作！" << endl << endl;
		
		Sleep(1000); system("cls"); return;
	}
	cout << "\n\n\n竞拍信息如下：\n";
	cout << "****************************\n";
	cout << "用户id           报价\n";
	for (Auction* t = p->Anext; t != NULL; t = t->Anext)
	{ 
		printf("U%03d            %.1lf\n", t->s_id, t->offer);
	}
	cout << "****************************\n";
	cout << "您确定要结束吗，请选择（y/n） "; getline(cin, str);
	if (str != "y" && str != "n")
	{
		cout << "无效操作！即将返回......";
		Sleep(1000); system("cls"); return;
	}
	else if (str == "n")
	{
		cout << "取消成功！即将返回......";
		Sleep(1000); system("cls"); return;
	}
	else
	{
		
		Auction* st = p->Anext;
		for (; st != NULL; st = st->Anext)
		{
			int uid = st->s_id;
			if (user.GetMon(uid) >= st->offer)
				break;
		}
		if (st == NULL)
		{
			p->Anext = NULL; p->flag = 0;
			//CoverAuc(p->ComID,p);
			CoverCom();
			cout << "无人获得该商品...";
			Sleep(1000); system("cls"); return;
		}
		for (Auction* p = st->Anext; p != NULL; p = p->Anext)
			if (user.GetMon(p->s_id) >= st->offer)
				if (p->offer > st->offer)
					st = p;
		user.DecMon(st->s_id, st->offer);
		user.IncMon(p->SellerID, st->offer);
		user.Cover_User();
		order.AddOrd(p->ComID, st->offer, st->s_id, p->SellerID);
		p->flag = 0; p->Anext = NULL; p->num--;
		if (p->num == 0)
			p->Condition = 2;
		CoverCom();
		printf("用户U%03d拍下该商品！", st->s_id);
		Sleep(2000); system("cls"); return;
	}



}
