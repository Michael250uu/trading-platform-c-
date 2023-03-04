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

Ccommodity ::Ccommodity()//-------------------------------------------------------------------������Ʒ����
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
		if (str == "���¼�")
			p->Condition = 0;
		else if (str == "������")
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
	cout << "�������¼���Ʒ��ID��"; string str;
	getline(cin, str);
	if (check_ID(str))
	{
		cout << "*****ID��ʽ����!�������ع���Ա�˵�*****"; Sleep(1000); system("cls"); return;
	}
	
	int a = tran_ID(str); Commodity* p = Head.next;
	for (; p != NULL; p = p->next)
		if (p->ComID == a&&p->Condition==1)
		{
			printf("ȷ��Ҫ�¼ܸ���Ʒ��\n\n****************\n");
			cout << "ID          ����           �۸�           �ϼ�ʱ��         ����           ����id         ��Ʒ״̬" << '\n';
			printf("M%03d        ", p->ComID);
			printf("%-15s", p->Name.c_str());
			printf("%-15.1lf", p->Price);
			printf("%d-%02d-%02d       ", p->Year, p->Month, p->Day);
			printf("%-15d", p->num);
			printf("U%03d        ", p->SellerID);
			printf("������\n");
			cout << "****************";
		}
	if (p == NULL)
	{
		cout << "*****���޴���Ʒ!�������ع���Ա�˵�*****"; Sleep(1000); system("cls"); return;
	}
	getline(cin, str);
	if (str != "y" && str != "n")
	{
		cout << "*****��Ч�������������ع���Ա�˵�*****"; Sleep(1000); system("cls"); return;
	}
	else if (str == "n")
	{
		cout << "*****ɾ��ʧ�ܣ��������ع���Ա�˵�*****"; Sleep(1000); system("cls"); return;
	}
	else
	{
		p->Condition = 0; p->flag = 0; CoverCom(); cout << "*****ɾ���ɹ�*****"; Sleep(1000); system("cls"); return;
	}
}
void Ccommodity::CancelCom_S( int s)
{
	cout << "�������¼���ƷID:"; string str; getline(cin, str);
	if(check_ID(str))
	{
		cout << "*****ID��ʽ���󣬼�������*****"; Sleep(1000); system("cls"); return;
	}
	int c = tran_ID(str);
	for (Commodity* p = Head.next; p != NULL; p = p->next)
		if (p->ComID == c && p->SellerID == s && p->Condition == 1)
		{
			cout << "��ȷ��Ҫ�¼ܸ���Ʒ��" << endl<<endl;
			cout<<"*******************************"<<endl;
			cout << "ID          ����           �۸�           �ϼ�ʱ��         ����           ����id         ��Ʒ״̬" << '\n';
			printf("M%03d        ", p->ComID);
			printf("%-15s", p->Name.c_str());
			printf("%-15.1lf", p->Price);
			printf("%d-%02d-%02d       ", p->Year, p->Month, p->Day);
			printf("%-15d", p->num);
			printf("U%03d        ", p->SellerID);
			printf("������\n");
			cout << "*******************************" << endl;
			cout << "��ѡ��y/n�� "; getline(cin, str);
			if(str!="y"&&str!="n")
			{
				cout << "*****��Ч����*****"; Sleep(1000); system("cls"); return;
			}
			if(str=="n")
			{
				cout << "������ȡ����"; Sleep(1000); system("cls"); return;
			}
			else
			{
				p->Condition = 0; p->flag = 0; CoverCom(); cout << "�¼ܳɹ���"; Sleep(1000); system("cls"); return;
			}
		}
	cout << "*****�޷����иò���*****"; Sleep(1000); system("cls"); return;
}
void Ccommodity::Show_S_Com(int s)
{
	cout << endl;
	cout << "����������Ʒ�嵥����" << endl;
	cout << "***************************************************************************************"<<endl;
	cout << "ID          ����           �۸�           ����           �ϼ�ʱ��           ��Ʒ״̬" << '\n';
	for (Commodity* p = Head.next; p != NULL; p = p->next)
	if(p->SellerID==s)
	{
		printf("M%03d        ", p->ComID);
		printf("%-15s", p->Name.c_str());
		printf("%-15.1lf", p->Price);
		printf("%-15d", p->num);
		printf("%d-%02d-%02d         ", p->Year, p->Month, p->Day);
		if (p->Condition == 1)
			printf("������\n");
		else if (p->Condition == 0)
			printf("���¼�\n");
		else
			printf("���۳�\n");
	}
	cout << "***************************************************************************************"<<endl;
	cout << "���س��ص����ҽ���...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Ccommodity::Show_B_Com( int a)
{
	cout << "************************************************************************************" << '\n';
	cout << "ID          ����           �۸�           ����           �ϼ�ʱ��           ����ID" << '\n';
	for (Commodity* p = Head.next; p != NULL; p = p->next)
		if (p->Condition == 1 )
			printf("M%03d        %-15s%-15.1lf%-15d%d-%02d-%02d         U%03d\n", p->ComID, p->Name.c_str(), p->Price, p->num, p->Year, p->Month, p->Day, p->SellerID);
	cout << "************************************************************************************" << '\n';
	cout << "���س��ص�������...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Ccommodity::Show_A_Com()//---------------------------------------------------------------------------------------------------������Ա����Ʒ
{
	cout << "*******************************************************************************************************"<<'\n';
	cout << "ID          ����           �۸�           �ϼ�ʱ��           ����ID            ����           ��Ʒ״̬"<<'\n';
	for(Commodity*p=Head.next;p!=NULL;p=p->next)
	{
		printf("M%03d        ", p->ComID);
		printf("%-15s", p->Name.c_str());
		printf("%-15.1lf", p->Price);
		printf("%d-%02d-%02d         ", p->Year, p->Month, p->Day);
		printf("U%03d               ", p->SellerID);
		printf("%-15d", p->num);
		if (p->Condition == 1)
			printf("������\n");
		else if (p->Condition == 0)
			printf("���¼�\n");
		else
			printf("���۳�\n");
	}
	cout << "*******************************************************************************************************" << '\n';
	cout << "���س��ص�����Ա����...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Ccommodity::A_Search_Com()//----------------------------------------------------------------------------------------����Ա����
{
	cout << "��������Ʒ����:";
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
		cout <<'\n'<< "                        δ�ҵ�������������Ʒ��" << endl<<endl;
		cout << "********************************************************************************************************" << '\n';
	}
	else 
	{
		cout << "ID          ����           �۸�           �ϼ�ʱ��           ����ID            ����           ��Ʒ״̬" << '\n';
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
					printf("������\n");
				else if (p->Condition == 0)
					printf("���¼�\n");
				else
					printf("���۳�\n");
			}
		cout << "********************************************************************************************************" << '\n';
	}
	cout << "���س��ص�����Ա����...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Ccommodity::BuyCom(int u)
{
	cout << "���������뾺�ĵ���Ʒid:";
	string str;
	getline(cin, str);
	if (check_ID(str))
	{
		cout << "*****ID��ʽ���󣬼���������Ҳ˵�*****"; Sleep(1000); system("cls"); return;
	}
	int a = tran_ID(str), flag = 0; cout << "******************" << endl;
	for (Commodity* p = Head.next; p != NULL; p = p->next)
		if (p->ComID == a && p->Condition == 1)
		{
			flag = 1; break;
		}
	if (flag == 0)
	{
		cout << '\n' << "δ�ҵ����뾺�ĵ���Ʒ����������" << endl << endl;
		cout << "******************" << '\n';
		Sleep(1000); system("cls"); return;
	}
	else
	{
		Commodity* p = Head.next;
		for (; p != NULL; p = p->next)
			if (p->ComID == a)
			{
				cout << "���ƣ�    " << p->Name << endl;
				cout << "������    " << p->Description << endl;
				printf("�ϼ�ʱ�䣺%d-%02d-%02d\n", p->Year, p->Month, p->Day);
				printf("��Ʒ������%d\n", p->num);
				printf("�۸�    %.1lf\n", p->Price);
				printf("����ID��  U%03d\n", p->SellerID); break;
			}
		cout << "******************" << endl<<"��Ʒ��Ϣ����...\n\n\n";
		cout << "���������ı���:";
		getline(cin, str);
		if(check_m(str))
		{
			cout << "���������󣬼�������..."; Sleep(1000); system("cls"); return;
		}
		double temp= tran_m(str);
		if (temp < p->Price)
		{
			cout << "���۵�����͸����۸񣬼�������..."; Sleep(1000); system("cls"); return;
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
			cout << "\n���۳ɹ�����������..."; Sleep(1000); system("cls"); return;
		}
		else
		{
			for (Auction* tp = p->Anext; ; tp = tp->Anext)
				if (tp->Anext == NULL)
				{
					tp->Anext = a; break;
				}
			CoverAuc(p->ComID,p);
			cout << "\n���۳ɹ�����������..."; Sleep(1000); system("cls"); return;
		}

	}
	
}
void Ccommodity:: CoverCom()
{
	FILE* fp = fopen("Commodity.txt", "w+"); Commodity* p = Head.next;
	for (; p->next != NULL; p = p->next)
	{
		fprintf(fp, "M%03d %s %.1lf %s U%03d %d-%02d-%02d %d %d ", p->ComID, p->Name.c_str(), p->Price, p->Description.c_str(), p->SellerID, p->Year, p->Month, p->Day,p->num,p->flag);
		if (p->Condition == 0)fprintf(fp, "���¼�\n");
		else if (p->Condition == 1)fprintf(fp, "������\n");
		else fprintf(fp, "���۳�\n");
	}
	fprintf(fp, "M%03d %s %.1lf %s U%03d %d-%02d-%02d %d %d ", p->ComID, p->Name.c_str(), p->Price, p->Description.c_str(), p->SellerID, p->Year, p->Month, p->Day,p->num,p->flag);
	if (p->Condition == 0)fprintf(fp, "���¼�");
	else if (p->Condition == 1)fprintf(fp, "������");
	else fprintf(fp, "���۳�");
	fclose(fp);
}

void Ccommodity::KnowCom()
{
	cout << "��������Ʒ��ID��";
	string str; getline(cin, str);
	if(check_ID(str))
	{
		cout << "*****ID��ʽ���󣬼���������Ҳ˵�*****"; Sleep(1000); system("cls"); return;
	}
	int a = tran_ID(str),flag=0; cout << "******************" << endl;
	for (Commodity* p = Head.next; p != NULL; p = p->next)
		if (p->ComID == a&&p->Condition==1)
		{
			flag = 1; break;
		}
	if (flag == 0)
	{
		cout << '\n' << "δ�ҵ�������������Ʒ��" << endl << endl;
		cout << "******************" << '\n';
	}
	else
	{
		for (Commodity* p = Head.next; p != NULL; p = p->next)
			if (p->ComID == a)
			{
				cout << "���ƣ�    " << p->Name << endl;
				cout << "������    " << p->Description << endl;
				printf("�ϼ�ʱ�䣺%d-%02d-%02d\n", p->Year, p->Month, p->Day);
				printf("��Ʒ������%d\n", p->num);
				printf("�۸�    %.1lf\n", p->Price);
				printf("����ID��  U%03d\n", p->SellerID); break;
			}
		cout << "******************"<<endl;
	}
	cout << "���س��ص�������...";
	while (!(getchar() == '\n')) {}
	system("cls");
}
void Ccommodity::AddCom(int s)
{
	Commodity* p = new Commodity; p->next = NULL;
	string str;
	cout << "��������Ʒ���ƣ�";
	getline(cin, str);
	if (check_input(str)) 
	{ 
		cout << "*****������������ո񣡼����������Ҳ˵�*****"; Sleep(1000); system("cls"); return; 
	}
	p->Name = str;
	cout << "��������Ʒ��"; getline(cin, str);
	if (check_m(str))
	{
		cout << "*****����ȷ����������������Ҳ˵�*****"; Sleep(1000); system("cls"); return;
	}
	p->Price = tran_m(str);

	cout << "��������Ʒ������"; getline(cin, str);
	if (check_num(str))
	{
		cout << "*****����ȷ���������������������Ҳ˵�*****"; Sleep(1000); system("cls"); return;
	}
	p->num = atoi(str.c_str());

	cout << "��������Ʒ������"; getline(cin, str);
	if (check_input(str)) 
	{ 
		cout << "*****������������ո񣡼����������Ҳ˵�*****"; Sleep(1000); system("cls"); return; 
	}
	p->Description = str;
	cout << endl << "��ȷ�Ϸ�����Ʒ��Ϣ����" << endl;
	cout << "***********************"<<endl;
	cout << "��Ʒ���ƣ�" << p->Name<<endl;
	cout << "��Ʒ��" << p->Price << endl;
	cout << "��Ʒ������" << p->num << endl;
	cout << "��Ʒ������" << p->Description << endl;
	cout << "***********************"<<endl<<endl;
	cout << "��ȷ��Ҫ��������Ʒ�� ��y/n�� ";
	getline(cin, str);
	if(str!="y"&&str!="n")
	{
		cout << "*****��Ч�����������������Ҳ˵�*****"; Sleep(1000); system("cls"); return;
	}
	else if(str=="n")
	{
		cout << "*****������ȡ������������*****"; Sleep(1000); system("cls"); return;
	}
	else
	{
		p->Condition = 1; p->Year = year(); p->Month = month(); p->Day = day(); p->SellerID = s;
		for (Commodity* q = Head.next;; q = q->next)
			if(q==NULL)
			{ 
				p->ComID = 1; Head.next = p; CoverCom();
				cout << "������Ʒ�ɹ���"; Sleep(1000); system("cls"); return;
			}
			else if (q->next == NULL)
			{
				p->ComID = q->ComID + 1; 
				q->next = p; CoverCom();
				cout << "������Ʒ�ɹ���"; Sleep(1000); system("cls"); return;
			}
	}


}
void Ccommodity::ModifyCom(int s)
{
	cout << "��������ƷID��";
	string str; getline(cin, str);
	if (check_ID(str))
	{
		cout << "*****ID��ʽ���󣬼�������*****"; Sleep(1000); system("cls"); return;
	}
	Commodity* p = Head.next;
	for(;p!=NULL;p=p->next)
		if(p->ComID==tran_ID(str)&&p->Condition==1&&p->SellerID==s)
		{
			cout << "��������Ʒ�޸����ԣ�1.�۸� 2.������ "; int c = cin_Choose();
			if(c<1||c>2)
			{
				cout << "*****��Ч����*****"; Sleep(1000); system("cls"); return;
			}
			else if(c==1)
			{
				cout << "�������޸ĺ�ļ۸�";
				getline(cin, str);
				if(check_m(str))
				{
					cout << "*****����ʽ����*****"; Sleep(1000); system("cls"); return;
				}
				double m = tran_m(str); cout <<endl<< "��ȷ���޸ĺ����Ʒ��Ϣ"<<endl;
				cout << "**********************************"<<endl;
				cout << "��ƷID��  "; printf("M%03d\n", p->ComID);
				cout << "��Ʒ���ƣ�" << p->Name<<endl;
				cout << "��Ʒ�۸�" <<fixed<<setprecision(1)<< m<<endl;
				cout << "��Ʒ������" << p->Description<<endl;
				cout << "**********************************" << endl;
				cout << "ȷ���޸ģ�y/n�� "; getline(cin, str);
				if(str!="y"&&str!="n")
				{
					cout << "��Ч������"; Sleep(1000); system("cls"); return;
				}
				else if(str=="n")
				{
					cout << "������ȡ����"; Sleep(1000); system("cls"); return;
				}
				else
				{
					p->Price = m; CoverCom(); cout << "�޸ĳɹ���"; Sleep(1000); system("cls"); return;
				}
			}
			else
			{
				cout << "�������޸ĺ���Ʒ��������";
				getline(cin, str);
				if (check_input(str))
				{
					cout << "��������ո�"; Sleep(1000); system("cls"); return;
				}
				cout << endl << "��ȷ���޸ĺ����Ʒ��Ϣ" << endl;
				cout << "**********************************" << endl;
				cout << "��ƷID�� "; printf("M%03d\n", p->ComID);
				cout << "��Ʒ���ƣ�" << p->Name << endl;
				cout << "��Ʒ�۸�" << fixed << setprecision(1) << p->Price<< endl;
				cout << "��Ʒ������" << str << endl;
				cout << "**********************************" << endl;
				cout << "ȷ���޸ģ�y/n�� "; string str_; getline(cin, str_);
				if (str_ != "y" && str_ != "n")
				{
					cout << "��Ч������"; Sleep(1000); system("cls"); return;
				}
				else if (str_ == "n")
				{
					cout << "������ȡ����"; Sleep(1000); system("cls"); return;
				}
				else
				{
					p->Description = str; CoverCom(); cout << "�޸ĳɹ���"; Sleep(1000); system("cls"); return;
				}
			}
		}
	cout << "*****�޷����иò���*****"; Sleep(1000); system("cls"); return;

}

void Ccommodity::B_Search_Com()
{
	for (;;)
	{
		cout << "��ѡ��������ʽ��1.���� 2.�۸�Χ 3.���� ��";
		int choose = cin_Choose();
		if (choose < 1 || choose>3)
		{
			cout << "��Ч������"; Sleep(1000); system("cls"); continue;
		}system("cls");
		switch (choose)
		{
		case 1:
		{
			cout << "��������Ʒ����:";
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
				cout << '\n' << "                        δ�ҵ�������������Ʒ��" << endl << endl;
				cout << "********************************************************************************" << '\n';
			}
			else
			{
				cout << "ID          ����           �۸�           �ϼ�ʱ��           ����           ����ID" << '\n';
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
			cout << "���س��ص���ҽ���...";
			while (!(getchar() == '\n')) {}system("cls"); return;
		}
		case 2:
		{
			for (;;)
			{
				cout << "������۸��½磺";
				string str; getline(cin, str);
				if (check_m(str))
				{
					cout << "����ʽ����"; Sleep(1000); system("cls"); continue;
				}
				double min = tran_m(str);
				cout << "������۸��Ͻ磺";
				getline(cin, str);
				if (check_m(str))
				{
					cout << "����ʽ����"; Sleep(1000); system("cls"); continue;
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
					cout << '\n' << "                        δ�ҵ�������������Ʒ��" << endl << endl;
					cout << "********************************************************************************" << '\n';
				}
				else
				{
					cout << "ID          ����           �۸�           �ϼ�ʱ��           ����           ����ID" << '\n';
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
				cout << "���س��ص���ҽ���...";
				while (!(getchar() == '\n')) {}system("cls"); return;
			}
		}
		case 3:
		{
			cout << "��������Ʒ����:";
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
				cout << '\n' << "                        δ�ҵ�������������Ʒ��" << endl << endl;
				cout << "********************************************************************************" << '\n';
			}
			else
			{
				cout << "ID          ����           �۸�           �ϼ�ʱ��           ����           ����ID" << '\n';
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
			cout << "���س��ص���ҽ���...";
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
	cout << "��������������ĵ���Ʒid:";
	string str;
	getline(cin, str);
	if (check_ID(str))
	{
		cout << "\nid��ʽ���󣬼�������......";
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
		cout << '\n' << "�޷�ִ�иò�����" << endl << endl;
		
		Sleep(1000); system("cls"); return;
	}
	cout << "\n\n\n������Ϣ���£�\n";
	cout << "****************************\n";
	cout << "�û�id           ����\n";
	for (Auction* t = p->Anext; t != NULL; t = t->Anext)
	{ 
		printf("U%03d            %.1lf\n", t->s_id, t->offer);
	}
	cout << "****************************\n";
	cout << "��ȷ��Ҫ��������ѡ��y/n�� "; getline(cin, str);
	if (str != "y" && str != "n")
	{
		cout << "��Ч��������������......";
		Sleep(1000); system("cls"); return;
	}
	else if (str == "n")
	{
		cout << "ȡ���ɹ�����������......";
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
			cout << "���˻�ø���Ʒ...";
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
		printf("�û�U%03d���¸���Ʒ��", st->s_id);
		Sleep(2000); system("cls"); return;
	}



}
