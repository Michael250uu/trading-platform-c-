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
	cout << "������Ҫɾ���û���ID��"; string str;
	getline(cin, str);
	if(check_input(str)||str.size()!=4||str[0]!='U')
	{
		cout << "*****ID��ʽ����!�������ع���Ա�˵�*****"; Sleep(1000); system("cls"); return;
	}
	for(int i=1;i<4;i++)
		if(str[i]<'0'||str[i]>'9')
		{
			cout << "*****ID��ʽ����!�������ع���Ա�˵�*****"; Sleep(1000); system("cls"); return;
		}
	int a = tran_ID(str); User* p = Head.next;
	for(;p!=NULL;p=p->next)
	if(p->UserID==a)
	{
		printf("ȷ��Ҫɾ�����û���\n\n****************\n�û�ID��U%03d\n�û�����%s\n��ϵ��ʽ��%s\n****************\n\n��ѡ��y/n�� ", p->UserID, p->Name.c_str(), p->Phone.c_str());
		break;
	}
	if(p==NULL)
	{
		cout << "*****���޴��û�!�������ع���Ա�˵�*****"; Sleep(1000); system("cls"); return;
	}
	getline(cin, str);
	if (str != "y" &&str != "n")
	{
		cout << "*****��Ч�������������ع���Ա�˵�*****"; Sleep(1000); system("cls"); return;
	}
	else if (str == "n")
	{
		cout << "*****ɾ��ʧ�ܣ��������ع���Ա�˵�*****"; Sleep(1000); system("cls"); return;
	}
	else
		p->Con = 0; Cover_User(); head2.CancelCom1( a); cout << "*****ɾ���ɹ�*****"; Sleep(1000); system("cls"); return;
}
void Cuser::Show_A_User()
{
	cout << "******************************************************************************"<<endl;
	cout << "�û�ID    �û���              ��ϵ��ʽ            ��ַ             Ǯ����� "<<endl;
	for (User* p = Head.next; p != NULL; p = p->next)
		if(p->Con==1)
		printf("U%03d      %-20s%-20s%-20s%.1lf\n", p->UserID, p->Name.c_str(), p->Phone.c_str(), p->Address.c_str(), p->Money);
	cout << "******************************************************************************" << endl;
	cout << "���س��ص�����Ա����...";
	while (!(getchar() == '\n')) {}
	system("cls"); 
}
void Cuser::Show_U( int now)
{
	User* u = NowUser(now);
	cout << "************************" << endl;
	cout << "�û����� " << u->Name << endl;
	cout << "��ϵ��ʽ��" << u->Phone << endl;
	cout << "��ַ  ��" << u->Address << endl;
	cout << "Ǯ����"<<fixed<<setprecision(1)<<u->Money<<endl;
	cout << "************************" << endl;
	cout << "���س��ص�����Ա����...";
	while (!(getchar() == '\n')) {}
	std::system("cls");
}
int Cuser::Login()
{
	int U[99999] = { 0 };
	for(;;)
	{
		string name, key;
		cout << "�������û���:";
		getline(cin, name);
		cout << "����������:";
		getline(cin, key);
		for (User* p = Head.next; p != NULL; p = p->next)
			if (name == p->Name && key == p->Key && p->Con == 1)
				return p->UserID;
			else if (name == p->Name && key != p->Key && p->Con == 1)
			{
				U[p->UserID]++;
				if(U[p->UserID]==3)
				{
					cout << "���û��������ظ�����3�Σ���������������"; 
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
					F << "������ͼ���Ե�¼�����˺�,��ע���˺Ű�ȫ������"<<endl;
					F << "                     from ���׶��ֽ���ƽ̨�Ŷ�"  << endl;
					F << "---------------" << year() << "-" << setw(2) << setfill('0') << month() << "-" << setw(2) << setfill('0') << day() << "  " << setw(2) << setfill('0') << hour() << ":" << setw(2) << setfill('0') << minute() << "---------------" << endl<<endl;
					F.close();
					Sleep(1000); system("cls"); return -1;
				}
			}
		cout << "*****�˺Ż������������������*****"; Sleep(1000); system("cls");

	}
}
void Cuser::Register()
{   string str;
	User* p = new User; p->next = NULL;
	cout << "�������û�����";  getline(cin, str);
	if (check_input(str))goto L;
	for(User*q=Head.next;q!=NULL;q=q->next)
		if(str==q->Name&&q->Con==1)
		{
			cout << "*****���û����ѱ�ע��!�����������˵�*****";
			Sleep(1000);
			system("cls");
			return;
		}
	p->Name = str;
	cout << "���������룺"; getline(cin, str);
	if (check_input(str))goto L;
	p->Key = str;
	cout << "������绰���룺"; getline(cin, str);
	if (check_input(str))goto L;
	p->Phone = str;
	cout << "�������ַ��"; getline(cin, str);
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
	Cover_User(); cout << "*****ע��ɹ�*****"; Sleep(1000); system("cls"); return;
	L:cout << "**********������������ո񣡼����������˵�**********";
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
//	cout << "��������ƷID��"; string name; getline(cin, name);
//	if (check_ID(name))
//	{
//		cout << "*****ID��ʽ���󣬼���������Ҳ˵�*****"; Sleep(1000); system("cls"); return;
//	}int a = tran_ID(name); 
//	for(Commodity*p=head1.next;p!=NULL;p=p->next)
//		if(p->ComID==a&&p->Condition==1)
//		{
//			if (p->SellerID == b->UserID)
//			{
//				cout << "*****�޷��Լ����Լ��Ķ���....*****"; Sleep(1000); system("cls"); return;
//			}
//			if (p->Price <= b->Money)
//			{
//				b->Money -= p->Price;
//				cout <<endl<< "*********" << endl;
//				cout << "�������ѣ�" << endl;
//				cout << "����ʱ�䣺"; printf("%d-%02d-%02d\n", year(), month(), day());
//				cout << "���׽�"; printf("%.1lf\n", p->Price);
//				cout << "����״̬�����׳ɹ�"<<endl;
//				cout << "��" <<fixed<<setprecision(1)<< b->Money << endl << "*********" << endl << "���س���������Ҳ˵�...";
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
//				cout << "*****���㣡*****"; Sleep(1000); system("cls"); return;
//			}
//		}
//	cout << "*****���޸���Ʒ��*****"; Sleep(1000); system("cls"); return;
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
	cout << "�ռ���ID��";
	string str; getline(cin, str);
	if (str[0] != 'U'||str.size()!=4) { cout << "ID��ʽ����"; Sleep(1000); system("cls"); return; }
	for(int i=1;i<4;i++)
		if(str[i]<'0'||str[i]>'9')
		{
			cout << "ID��ʽ����"; Sleep(1000); system("cls"); return;
		}
	int n = tran_ID(str);
	if(n==x){cout<<"�޷����Լ�˵����"; Sleep(1000); system("cls"); return;}
	User* p = Head.next;
	for (; p; p = p->next)
		if (p->UserID == n && p->Con == 1)
			break;
	if (p == NULL) { cout << "*****���޴��û���*****"; Sleep(1000); system("cls"); return; }
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
	cout << "���������ݣ�";
	string message; getline(cin, message);
	F << message<<endl;
	F << "                     from " << b <<endl;
	F << "---------------" << year() << "-" << setw(2) << setfill('0')<<month() << "-" << setw(2) << setfill('0') << day()<<"  "<< setw(2) << setfill('0') << hour()<<":"<< setw(2) << setfill('0') << minute()<<"---------------"<<endl<<endl;
	cout << "*****���ͳɹ���*****"; Sleep(1000); system("cls");
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
		cout << "*****��û���˸���д��Ŷ*****";
		Sleep(1000); system("cls"); return;
	}
	while(!F.eof())
	{
		char a[100];
		F.getline(a, 100);
		cout << a<<endl;
	}F.close();
	cout << endl << endl << endl << "���س�����...";
	while(getchar()!='\n'){}
	system("cls");
}
void Cuser::FindKey()
{
	cout << "�����������û�����";
	string str; getline(cin, str);
	User* p = Head.next;
	for (; p; p = p->next)
		if (p->Name == str && p->Con == 1)
			break;
	if(p==NULL)
	{
		cout << "*****���޴��û�*****"; Sleep(1000); system("cls"); return;
	}
	cout << "��ѡ���ѯ��ʽ��1.��ϵ��ʽ 2.��ַ�� ";
	int c = cin_Choose();
	if(c!=1&&c!=2)
	{
		cout << "*****��Ч����*****"; Sleep(1000); system("cls"); return;
	}
	switch (c)
	{
	case 1:
	{
		cout << "������������ϵ��ʽ��";
		string ph; getline(cin, ph);
		if(ph!=p->Phone)
		{
			cout << "*****���벻ƥ�䣡*****"; Sleep(1000); system("cls"); return;
		}
		break;
	}
	case 2: 
	{
		cout << "���������ĵ�ַ��";
		string ph; getline(cin, ph);
		if (ph != p->Address)
		{
			cout << "*****��ַ��ƥ�䣡*****"; Sleep(1000); system("cls"); return;
		}
		break;
	}
	}
	system("cls");
	for (;;)
	{
		cout << "-------------------�޸���������------------------" << endl;
		cout << "�������޸ĺ�����룺";
		string New;
		getline(cin, New);
		if (check_input(New))
		{
			cout << "*****������������ո�*****"; Sleep(1000); system("cls"); continue;
		}
		p->Key = New;
		Cover_User();
		cout << "*****�޸ĳɹ���*****"; Sleep(1000); system("cls"); return;
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
	cout << "�������޸ĵ����ԣ�1.�û��� 2.��ϵ��ʽ 3.��ַ��";
	int c = cin_Choose();
	if(c<1||c>3)
	{
		cout << "*****��Ч����*****"; Sleep(1000); system("cls"); return;
	}
	switch (c)
	{
	case 1:
	{cout << "�������޸ĺ���û�����";
		string str; getline(cin, str);
		if(check_input(str))
		{
			cout << "������������ո�"; Sleep(1000); system("cls"); return;
		}
		for (User* q = Head.next; q != NULL; q = q->next)
			if (str == q->Name && q->Con == 1)
			{
				cout << "*****���û����ѱ�ע��!���������û�������*****";
				Sleep(1000);
				system("cls");
				return;
			}
		u->Name = str; Cover_User(); cout << "�޸ĳɹ���"; Sleep(1000); system("cls"); return;
	}
	case 2:
	{
		cout << "�������޸ĺ����ϵ��ʽ��";
	    string str; getline(cin, str);
		if (check_input(str))
		{
			cout << "������������ո�"; Sleep(1000); system("cls"); return;
		}
		u->Phone = str; Cover_User(); cout << "�޸ĳɹ���"; Sleep(1000); system("cls"); return;
	}
	case 3:
	{
		cout << "�������޸ĺ�ĵ�ַ��";
		string str; getline(cin, str);
		if (check_input(str))
		{
			cout << "������������ո�"; Sleep(1000); system("cls"); return;
		}
		u->Address = str; Cover_User(); cout << "�޸ĳɹ���"; Sleep(1000); system("cls"); return;
	}
	}
}
void Cuser::Kej_User(int s)
{
	User* u = NowUser(s);
	cout << "�������ֵ��Ŀ��"; string str; getline(cin, str);
	if(check_m(str))
	{
		cout << "����ȷ�����ֵ��Ŀ��"; Sleep(1000); system("cls"); return;
	}
	u->Money += tran_m(str); Cover_User(); cout << "��ֵ�ɹ�!"; Sleep(1000); system("cls"); return;
}


//void Cuser::SearchOrder(Corder &head2)
//{
//	for (;;)
//	{
//		cout << "���������ѯ���û�ID��";
//		string str; getline(cin, str);
//		if (check_UID(str))
//		{
//			cout << "*****ID��ʽ����*****"; Sleep(1000); system("cls"); continue;
//		}
//		int id = tran_ID(str);
//		if (FindUser(id))
//		{
//			cout << "*****���޴��û�*****"; Sleep(1000); system("cls"); continue;
//		}
//		system("cls");
//		cout << "��Ϊ���ң�"<<endl;
//		int flag1 = 0,flag2=0;
//		for (Order* p = head2.next; p != NULL; p = p->next)
//			if(p->SellerID==id)
//			{
//				flag1 = 1; break;
//			}
//		if (flag1 == 0)
//			cout << "  ����"<<endl<<endl;
//		else
//		{
//			cout << "********************************************************************************" << '\n';
//			cout << "  ID       ��ƷID    ���׽��    ����ʱ��         ���ID       ����ID" << endl;
//			for (Order* p = head2.next; p != NULL; p = p->next)
//				if (p->SellerID==id)
//					printf("T%05d     M%05d     %-10.1lf%d-%02d-%02d        U%05d       U%05d\n", p->OrdID, p->ComID, p->TraMoney, p->Year, p->Month, p->Day, p->BuyerID, p->SellerID);
//			cout << "********************************************************************************" << '\n'<<endl;
//		}
//		cout << "��Ϊ��ң�"<<endl;
//		for (Order* p = head2.next; p != NULL; p = p->next)
//			if (p->BuyerID == id)
//			{
//				flag2 = 1; break;
//			}
//		if (flag2 == 0)
//			cout << "  ����" << endl << endl;
//		else
//		{
//			cout << "********************************************************************************" << '\n';
//			cout << "  ID       ��ƷID    ���׽��    ����ʱ��         ���ID       ����ID" << endl;
//			for (Order* p = head2.next; p != NULL; p = p->next)
//				if (p->BuyerID == id)
//					printf("T%05d     M%05d     %-10.1lf%d-%02d-%02d        U%05d       U%05d\n", p->OrdID, p->ComID, p->TraMoney, p->Year, p->Month, p->Day, p->BuyerID, p->SellerID);
//			cout << "********************************************************************************" << '\n' << endl;
//		}
//		cout << "���س����ع���Ա����...";
//		while (getchar() != '\n') {}system("cls"); return;
//	}
//}
//
