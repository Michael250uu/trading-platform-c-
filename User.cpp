#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<windows.h>
#include<string>
#include<fstream>
#include<iomanip>
#include"User.h"
#include"common.h"
#include"Commodity.h"
#include"Order.h"
using namespace std;



Cuser:: Cuser()
{
	
	ifstream F("User.txt");
	if(!F)
	{
		cout << "Error opening User";
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
		User* p = new User;
		p->next = NULL; Tail->next = p; Tail = p;
		string str;
		F >> str; p->UserID = tran_ID(str);
		F >> p->Name>> p->Key>> p->Phone>>p->Address>>p->Money>>p->Con;
	}F.close();
	
}
void Cuser::DelUser( Ccommodity &head2)
{
	cout << "请输入要删除用户的ID："; string str;
	getline(cin, str);
	if(check_input(str)||str.size()!=4||str[0]!='U')
	{
		cout << "*****ID格式错误!即将返回管理员菜单*****"; Sleep(1000); system("cls"); return;
	}
	for(int i=1;i<4;i++)
		if(str[i]<'0'||str[i]>'9')
		{
			cout << "*****ID格式错误!即将返回管理员菜单*****"; Sleep(1000); system("cls"); return;
		}
	int a = tran_ID(str); User* p = Head.next;
	for(;p!=NULL;p=p->next)
	if(p->UserID==a)
	{
		printf("确认要删除该用户吗\n\n****************\n用户ID：U%03d\n用户名：%s\n联系方式：%s\n****************\n\n请选择（y/n） ", p->UserID, p->Name.c_str(), p->Phone.c_str());
		break;
	}
	if(p==NULL)
	{
		cout << "*****查无此用户!即将返回管理员菜单*****"; Sleep(1000); system("cls"); return;
	}
	getline(cin, str);
	if (str != "y" &&str != "n")
	{
		cout << "*****无效操作！即将返回管理员菜单*****"; Sleep(1000); system("cls"); return;
	}
	else if (str == "n")
	{
		cout << "*****删除失败！即将返回管理员菜单*****"; Sleep(1000); system("cls"); return;
	}
	else
		p->Con = 0; Cover_User(); head2.CancelCom1( a); cout << "*****删除成功*****"; Sleep(1000); system("cls"); return;
}
void Cuser::Show_A_User()
{
	cout << "******************************************************************************"<<endl;
	cout << "用户ID    用户名              联系方式            地址             钱包余额 "<<endl;
	for (User* p = Head.next; p != NULL; p = p->next)
		if(p->Con==1)
		printf("U%03d      %-20s%-20s%-20s%.1lf\n", p->UserID, p->Name.c_str(), p->Phone.c_str(), p->Address.c_str(), p->Money);
	cout << "******************************************************************************" << endl;
	cout << "按回车回到管理员界面...";
	while (!(getchar() == '\n')) {}
	system("cls"); 
}
void Cuser::Show_U( int now)
{
	User* u = NowUser(now);
	cout << "************************" << endl;
	cout << "用户名： " << u->Name << endl;
	cout << "联系方式：" << u->Phone << endl;
	cout << "地址  ：" << u->Address << endl;
	cout << "钱包余额："<<fixed<<setprecision(1)<<u->Money<<endl;
	cout << "************************" << endl;
	cout << "按回车回到管理员界面...";
	while (!(getchar() == '\n')) {}
	std::system("cls");
}
int Cuser::Login()
{
	int U[99999] = { 0 };
	for(;;)
	{
		string name, key;
		cout << "请输入用户名:";
		getline(cin, name);
		cout << "请输入密码:";
		getline(cin, key);
		for (User* p = Head.next; p != NULL; p = p->next)
			if (name == p->Name && key == p->Key && p->Con == 1)
				return p->UserID;
			else if (name == p->Name && key != p->Key && p->Con == 1)
			{
				U[p->UserID]++;
				if(U[p->UserID]==3)
				{
					cout << "该用户名的已重复错误3次！即将返回主界面"; 
					char a[10];
					int w = 1,n=p->UserID;
					for (;; w++)
						if (n / pow(10, w) < 1)
							break;
					for (int i = 0, j = w - 1; i < w; i++, j--)
					{
						int b = n % 10;
						a[j] = (char)(b + '0');
						n = (n - b) / 10;
					}
					a[w] = '.'; a[w + 1] = 't'; a[w + 2] = 'x'; a[w + 3] = 't'; a[w + 4] = '\0';
					ofstream F(a, ios::app);
					F << "有人试图尝试登录您的账号,请注意账号安全保护！"<<endl;
					F << "                     from 简易二手交易平台团队"  << endl;
					F << "---------------" << year() << "-" << setw(2) << setfill('0') << month() << "-" << setw(2) << setfill('0') << day() << "  " << setw(2) << setfill('0') << hour() << ":" << setw(2) << setfill('0') << minute() << "---------------" << endl<<endl;
					F.close();
					Sleep(1000); system("cls"); return -1;
				}
			}
		cout << "*****账号或密码错误，请重新输入*****"; Sleep(1000); system("cls");

	}
}
void Cuser::Register()
{   string str;
	User* p = new User; p->next = NULL;
	cout << "请输入用户名：";  getline(cin, str);
	if (check_input(str))goto L;
	for(User*q=Head.next;q!=NULL;q=q->next)
		if(str==q->Name&&q->Con==1)
		{
			cout << "*****该用户名已被注册!即将返回主菜单*****";
			Sleep(1000);
			system("cls");
			return;
		}
	p->Name = str;
	cout << "请输入密码："; getline(cin, str);
	if (check_input(str))goto L;
	p->Key = str;
	cout << "请输入电话号码："; getline(cin, str);
	if (check_input(str))goto L;
	p->Phone = str;
	cout << "请输入地址："; getline(cin, str);
	if (check_input(str))goto L;
	p->Address = str;
	p->Money = 0; p->Con = 1;
	for (User* q = Head.next;; q = q->next)
		if (q == NULL)
		{
			p->UserID = 1; Head.next = p; break;
		}
		else if (q->next == NULL)
		{
			p->UserID = q->UserID + 1; q->next = p; break;
		}
	Cover_User(); cout << "*****注册成功*****"; Sleep(1000); system("cls"); return;
	L:cout << "**********输入请勿包含空格！即将返回主菜单**********";
		Sleep(1000); system("cls"); return;
}
void Cuser::Cover_User()
{
	FILE* fp = fopen("User.txt", "w+"); User* p = Head.next;
	for (; p ->next!= NULL; p = p->next)
		fprintf(fp, "U%03d %s %s %s %s %.1lf %d\n", p->UserID, p->Name.c_str(), p->Key.c_str(), p->Phone.c_str(), p->Address.c_str(), p->Money, p->Con);
	fprintf(fp, "U%03d %s %s %s %s %.1lf %d", p->UserID, p->Name.c_str(), p->Key.c_str(), p->Phone.c_str(), p->Address.c_str(), p->Money, p->Con);
	fclose(fp);
}
//void Cuser::BuyCom(Ccommodity &head1,Corder &head2,/* User head3,*/ int s)
//{
//	cout << "请输入商品ID："; string name; getline(cin, name);
//	if (check_ID(name))
//	{
//		cout << "*****ID格式错误，即将返回买家菜单*****"; Sleep(1000); system("cls"); return;
//	}int a = tran_ID(name); 
//	for(Commodity*p=head1.next;p!=NULL;p=p->next)
//		if(p->ComID==a&&p->Condition==1)
//		{
//			if (p->SellerID == b->UserID)
//			{
//				cout << "*****无法自己买自己的东西....*****"; Sleep(1000); system("cls"); return;
//			}
//			if (p->Price <= b->Money)
//			{
//				b->Money -= p->Price;
//				cout <<endl<< "*********" << endl;
//				cout << "交易提醒！" << endl;
//				cout << "交易时间："; printf("%d-%02d-%02d\n", year(), month(), day());
//				cout << "交易金额："; printf("%.1lf\n", p->Price);
//				cout << "交易状态：交易成功"<<endl;
//				cout << "余额：" <<fixed<<setprecision(1)<< b->Money << endl << "*********" << endl << "按回车返回至买家菜单...";
//				for (User* q = head3.next;; q = q->next)
//					if (q->UserID == p->SellerID)
//					{
//						q->Money += p->Price; break;
//					}
//				Cover_User(head3);
//				AddOrd(head2, p->ComID,p->Price, b->UserID, p->SellerID); p->Condition = 2; CoverCom(head1); while (getchar() != '\n') {}
//				AddOrd(head2, p->ComID,p->Price, b->UserID, p->SellerID); p->Condition = 2; CoverCom(head1); while (getchar() != '\n') {}
//				system("cls"); return;
//			}
//			else
//			{
//				cout << "*****余额不足！*****"; Sleep(1000); system("cls"); return;
//			}
//		}
//	cout << "*****查无该商品！*****"; Sleep(1000); system("cls"); return;
//		
//
//}
void Cuser::WriteLetter(int x)
{
	int  h= 1,s=x;
	for (;;h ++)
		if (s / pow(10, h) < 1)
			break;
	char b[5]; b[0] = 'U'; b[4] = '\0';
	for(int i=0,j=3;i<h;i++,j--)
	{
		int x = s % 10;
		b[j] = (char)(x+'0');
		s = (s - x) / 10;
	}
	for (int i = 1; i <= 3 - h; i++)
		b[i] = '0';
	cout << "收件人ID：";
	string str; getline(cin, str);
	if (str[0] != 'U'||str.size()!=4) { cout << "ID格式错误"; Sleep(1000); system("cls"); return; }
	for(int i=1;i<4;i++)
		if(str[i]<'0'||str[i]>'9')
		{
			cout << "ID格式错误"; Sleep(1000); system("cls"); return;
		}
	int n = tran_ID(str);
	if(n==x){cout<<"无法和自己说话！"; Sleep(1000); system("cls"); return;}
	User* p = Head.next;
	for (; p; p = p->next)
		if (p->UserID == n && p->Con == 1)
			break;
	if (p == NULL) { cout << "*****查无此用户！*****"; Sleep(1000); system("cls"); return; }
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
	a[w] = '.'; a[w + 1] = 't'; a[w + 2] = 'x'; a[w + 3] = 't'; a[w + 4] = '\0';
	ofstream F(a, ios::app);
	cout << "请输入内容：";
	string message; getline(cin, message);
	F << message<<endl;
	F << "                     from " << b <<endl;
	F << "---------------" << year() << "-" << setw(2) << setfill('0')<<month() << "-" << setw(2) << setfill('0') << day()<<"  "<< setw(2) << setfill('0') << hour()<<":"<< setw(2) << setfill('0') << minute()<<"---------------"<<endl<<endl;
	cout << "*****发送成功！*****"; Sleep(1000); system("cls");
	F.close();
}
void Cuser::ReadLetter(int n)
{
	char a[100]; int w = 1;
	for (;; w++)
		if (n / pow(10, w) < 1)
			break;
	for (int i = 0, j = w - 1; i < w; i++, j--)
	{
		int b = n % 10;
		a[j] = (char)(b + '0');
		n = (n - b) / 10;
	}
	a[w] = '.'; a[w + 1] = 't'; a[w + 2] = 'x'; a[w + 3] = 't'; a[w + 4] = '\0';
	ifstream F(a);
	if(!F)
	{
		cout << "*****还没有人给你写信哦*****";
		Sleep(1000); system("cls"); return;
	}
	while(!F.eof())
	{
		char a[100];
		F.getline(a, 100);
		cout << a<<endl;
	}F.close();
	cout << endl << endl << endl << "按回车返回...";
	while(getchar()!='\n'){}
	system("cls");
}
void Cuser::FindKey()
{
	cout << "请输入您的用户名：";
	string str; getline(cin, str);
	User* p = Head.next;
	for (; p; p = p->next)
		if (p->Name == str && p->Con == 1)
			break;
	if(p==NULL)
	{
		cout << "*****查无此用户*****"; Sleep(1000); system("cls"); return;
	}
	cout << "请选择查询方式（1.联系方式 2.地址） ";
	int c = cin_Choose();
	if(c!=1&&c!=2)
	{
		cout << "*****无效操作*****"; Sleep(1000); system("cls"); return;
	}
	switch (c)
	{
	case 1:
	{
		cout << "请输入您的联系方式：";
		string ph; getline(cin, ph);
		if(ph!=p->Phone)
		{
			cout << "*****号码不匹配！*****"; Sleep(1000); system("cls"); return;
		}
		break;
	}
	case 2: 
	{
		cout << "请输入您的地址：";
		string ph; getline(cin, ph);
		if (ph != p->Address)
		{
			cout << "*****地址不匹配！*****"; Sleep(1000); system("cls"); return;
		}
		break;
	}
	}
	system("cls");
	for (;;)
	{
		cout << "-------------------修改您的密码------------------" << endl;
		cout << "请输入修改后的密码：";
		string New;
		getline(cin, New);
		if (check_input(New))
		{
			cout << "*****输入请勿包含空格*****"; Sleep(1000); system("cls"); continue;
		}
		p->Key = New;
		Cover_User();
		cout << "*****修改成功！*****"; Sleep(1000); system("cls"); return;
	}
}
bool Cuser::FindUser(int id)
{
	for (User* p = Head.next; p; p = p->next)
		if (id == p->UserID && p->Con == 1)
			return 0;
	return 1;
}
int Cuser::GetMon(int uid)
{
	for (User* t = Head.next; t != NULL; t = t->next)
		if (t->UserID == uid)
			return t->Money;
}
void Cuser::DecMon(int uid, double mon)
{
	for (User* t = Head.next; t != NULL; t = t->next)
		if (t->UserID == uid)
		{
			t->Money -= mon; return;
		}
}
void Cuser::IncMon(int uid, double mon)
{
	for (User* t = Head.next; t != NULL; t = t->next)
		if (t->UserID == uid)
		{
			t->Money += mon; return;
		}
}
void Cuser::Modify_User( int s)
{
	User* u = NowUser(s);
	cout << "请输入修改的属性（1.用户名 2.联系方式 3.地址）";
	int c = cin_Choose();
	if(c<1||c>3)
	{
		cout << "*****无效操作*****"; Sleep(1000); system("cls"); return;
	}
	switch (c)
	{
	case 1:
	{cout << "请输入修改后的用户名：";
		string str; getline(cin, str);
		if(check_input(str))
		{
			cout << "输入请勿包含空格！"; Sleep(1000); system("cls"); return;
		}
		for (User* q = Head.next; q != NULL; q = q->next)
			if (str == q->Name && q->Con == 1)
			{
				cout << "*****该用户名已被注册!即将返回用户主界面*****";
				Sleep(1000);
				system("cls");
				return;
			}
		u->Name = str; Cover_User(); cout << "修改成功！"; Sleep(1000); system("cls"); return;
	}
	case 2:
	{
		cout << "请输入修改后的联系方式：";
	    string str; getline(cin, str);
		if (check_input(str))
		{
			cout << "输入请勿包含空格！"; Sleep(1000); system("cls"); return;
		}
		u->Phone = str; Cover_User(); cout << "修改成功！"; Sleep(1000); system("cls"); return;
	}
	case 3:
	{
		cout << "请输入修改后的地址：";
		string str; getline(cin, str);
		if (check_input(str))
		{
			cout << "输入请勿包含空格！"; Sleep(1000); system("cls"); return;
		}
		u->Address = str; Cover_User(); cout << "修改成功！"; Sleep(1000); system("cls"); return;
	}
	}
}
void Cuser::Kej_User(int s)
{
	User* u = NowUser(s);
	cout << "请输入充值数目："; string str; getline(cin, str);
	if(check_m(str))
	{
		cout << "请正确输入充值数目："; Sleep(1000); system("cls"); return;
	}
	u->Money += tran_m(str); Cover_User(); cout << "充值成功!"; Sleep(1000); system("cls"); return;
}


//void Cuser::SearchOrder(Corder &head2)
//{
//	for (;;)
//	{
//		cout << "请输入想查询的用户ID：";
//		string str; getline(cin, str);
//		if (check_UID(str))
//		{
//			cout << "*****ID格式错误*****"; Sleep(1000); system("cls"); continue;
//		}
//		int id = tran_ID(str);
//		if (FindUser(id))
//		{
//			cout << "*****查无此用户*****"; Sleep(1000); system("cls"); continue;
//		}
//		system("cls");
//		cout << "作为卖家："<<endl;
//		int flag1 = 0,flag2=0;
//		for (Order* p = head2.next; p != NULL; p = p->next)
//			if(p->SellerID==id)
//			{
//				flag1 = 1; break;
//			}
//		if (flag1 == 0)
//			cout << "  暂无"<<endl<<endl;
//		else
//		{
//			cout << "********************************************************************************" << '\n';
//			cout << "  ID       商品ID    交易金额    交易时间         买家ID       卖家ID" << endl;
//			for (Order* p = head2.next; p != NULL; p = p->next)
//				if (p->SellerID==id)
//					printf("T%05d     M%05d     %-10.1lf%d-%02d-%02d        U%05d       U%05d\n", p->OrdID, p->ComID, p->TraMoney, p->Year, p->Month, p->Day, p->BuyerID, p->SellerID);
//			cout << "********************************************************************************" << '\n'<<endl;
//		}
//		cout << "作为买家："<<endl;
//		for (Order* p = head2.next; p != NULL; p = p->next)
//			if (p->BuyerID == id)
//			{
//				flag2 = 1; break;
//			}
//		if (flag2 == 0)
//			cout << "  暂无" << endl << endl;
//		else
//		{
//			cout << "********************************************************************************" << '\n';
//			cout << "  ID       商品ID    交易金额    交易时间         买家ID       卖家ID" << endl;
//			for (Order* p = head2.next; p != NULL; p = p->next)
//				if (p->BuyerID == id)
//					printf("T%05d     M%05d     %-10.1lf%d-%02d-%02d        U%05d       U%05d\n", p->OrdID, p->ComID, p->TraMoney, p->Year, p->Month, p->Day, p->BuyerID, p->SellerID);
//			cout << "********************************************************************************" << '\n' << endl;
//		}
//		cout << "按回车返回管理员界面...";
//		while (getchar() != '\n') {}system("cls"); return;
//	}
//}
//
