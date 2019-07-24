#include<fstream>
#include<ctype.h>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<iomanip>
#include<iostream>
#include<string.h>

using namespace std;
int acc_flag=0,no=0;
char acc_ind[5];

struct account
{
	char ind[5],
	 acc_no[20],
	 acc_name[20],
	 type[5],
	 deposit[10],
	 dep_amt[10];
}acc[20];

struct secind{
	char acc_name[20],
	    acc_no[20],
	    ind[20];
}sec[20],found[20];

struct index{
	char acc_no[20],ind[20];
}in[20],temp;

void sort_index()
{
	int i,j;
	for(i=0;i<no-1;i++)
	for(j=0;j<no-i-1;j++)
	if(strcmp(in[j].acc_no,in[j+1].acc_no)>0)
	{
		temp =in[j];
		in[j]=in[j+1];
		in[j+1]=temp;
	}
}

void sort_secind()
{
	int i,j;
	secind temp;
	for(i=0;i<no-1;i++)
	for(j=0;j<no-i-1;j++)
	if(strcmp(sec[j].acc_name,sec[j+1].acc_name)>0)
	{
		temp =sec[j];
		sec[j]=sec[j+1];
		sec[j+1]=temp;
	}
	else if(strcmp(sec[j].acc_name,sec[j+1].acc_name)==0)
	{
	if(strcmp(sec[j].acc_no,sec[j+1].acc_no)>0)
	{
		temp =sec[j];
		sec[j]=sec[j+1];
		sec[j+1]=temp;
	}
}
}

void ret_rec(char *ind)
{
	int flag=0;
	for(int i=0;i<no;i++)
	{
		if(strcmp(acc[i].ind,ind)==0)
		{
			strcpy(acc_ind,ind);
			acc_flag=1;
			cout<<"Account found\n";
			cout<<acc[i].acc_no<<"|"<<acc[i].acc_name<<"|"<<acc[i].type<<"|"<<acc[i].deposit<<"\n";
			flag=1;
		}
	}
	if(!flag)
	{
		cout<<"Account search failed\n";
	}
}

void search_index(char *acc_no)
{
	int flag=0;
for(int i=0;i<no;i++)
	{
		if(strcmp(in[i].acc_no,acc_no)==0)
		{	
		ret_rec(in[i].ind);
		flag=1;
       }
}
if(!flag)
	{
		cout<<"Index search failed\n";
	}
}

void search(char *acc_name)
{
	char acc_no[20];
	int flag1=0;
	int k=0,i;
	for(i=0;i<no;i++)
	{
	if(strcmp(sec[i].acc_name,acc_name)==0)
	{
		strcpy(found[k].acc_no,sec[i].acc_no);
		strcpy(found[k].acc_name,sec[i].acc_name);
		strcpy(found[k].ind,sec[i].ind);
		flag1=1;
		k++;
	}
	}
	if(!flag1)
	{
		cout<<"secondary index search failed\n Account name not found!!\n";
		return;
	}
	cout<<"\n Records matching are:";
	for(i=0;i<k;i++)
	cout<<"\n"<<found[i].acc_name<<" "<<found[i].acc_no;
	cout<<"\n Choose an account no";
	cin>>acc_no;
	flag1=0;
	for(i=0;i<k;i++)
	if(strcmp(found[i].acc_no,acc_no)==0)
	{
		search_index(acc_no);
		flag1=1;
	}
	if(!flag1)
	{
		cout<<"wrong account number!!\n search failed..\n";
	}
	}



int search_account(char *acc_no,int j)
{
	int flag=0;
for(int i=0;i<j;i++)
	{
		if(strcmp(acc[i].acc_no,acc_no)==0)
		{	
		flag=1;
		break;
        }
}
if(flag)
return 1;
else
return -1;
}

void del(char *acc_name)
{
	acc_flag=0;
	int fr=0;
	search(acc_name);
	if(!acc_flag)
	{
		cout<<"Deletion of account failed\n";
		return;
	}
	for(int i=0;i<no;i++)
	{
	if(strcmp(acc[i].ind,acc_ind)==0)
	{
		fr=i;
		break;
	}
}
	for(int i=fr;i<no-1;i++)
	{
	acc[i]=acc[i+1];
	char str[3];
	sprintf(str,"%d",i);
	strcpy(acc[i].ind,str);
	}
	no--;
	
	fstream f1,f2,f3;
	f1.open("account00.txt",ios::out);
	f2.open("index00.txt",ios::out);
	f3.open("secind00.txt",ios::out);
	for(int i=0;i<no;i++)
	{
		strcpy(sec[i].acc_name,acc[i].acc_name);
		strcpy(sec[i].acc_no,acc[i].acc_no);
		strcpy(in[i].acc_no,acc[i].acc_no);
		strcpy(sec[i].ind,acc[i].ind);
		strcpy(in[i].ind,acc[i].ind);
	}
	sort_index();
	sort_secind();
	for(int i=0;i<no;i++)
	{
	 f1<<acc[i].ind<<"|"<<acc[i].acc_no<<"|"<<acc[i].acc_name<<"|"<<acc[i].type<<"|"<<acc[i].deposit<<"\n";
	 f2<<in[i].acc_no<<"|"<<in[i].ind<<"\n";
	 f3<<sec[i].acc_name<<"|"<<sec[i].acc_no<<"|"<<sec[i].ind<<"\n";
	}
	f1.close();
	f2.close();
	f3.close();
	cout<<"\ndeletion successful!!\n";
	}
	
	void createaccount()
	{
		
                	int choice,i,flag1,flag;
	fstream file1,file2,file3;
	char ind[10],
	     acc_no[20],
	     acc_name[20],
	     type[5],
	     deposit[10];
		
				file3.open("index00.txt",ios::out|ios::app);
				file1.open("account00.txt",ios::app|ios::out);
				file2.open("secind00.txt",ios::out);
				int n;
				cout<<"\nEnter no of accounts to be created\n";
				cin>>n;
				for(int i=no;i<no+n;i++)
				{
				  label:  cout<<"\nENTER "<<i+1<<" ACCOUNT DETAILS:\n\n";
					cout<<"Enter Acc Number:"; cin>>acc[i].acc_no;
					cout<<"Enter Acc Name:"; cin>>acc[i].acc_name;
					cout<<"Enter Type(S for Savings|C for Current):"; cin>>acc[i].type;
					cout<<"Enter Deposit:(>=1000 for C|>=1500 for S)"; cin>>acc[i].deposit;
					
				int	q= search_account(acc[i].acc_no,i);
					if(q==1)
					{
						cout<<"Duplicate entry, Enter again\n";
					goto label;
					}
					file1<<i<<"|"<<acc[i].acc_no<<"|"<<acc[i].acc_name<<"|"<<acc[i].type<<"|"<<acc[i].deposit<<"\n";
				}
				file1.close();
				no=no+n;
				file1.open("account00.txt",ios::in);
				for(int i=0;i<no;i++)
				{
					file1.getline(ind,10,'|');
					file1.getline(acc_no,20,'|');
					file1.getline(acc_name,20,'|');
					file1.getline(type,5,'|');
					file1.getline(deposit,10,'\n');
					
					strcpy(acc[i].ind,ind);
					strcpy(sec[i].ind,ind);
					strcpy(in[i].ind,ind);
					strcpy(sec[i].acc_name,acc_name);
					strcpy(sec[i].acc_no,acc_no);
					strcpy(in[i].acc_no,acc_no);
				}
				sort_index();
				sort_secind();
				cout<<"\nThe sorted secondary index contents are:\n";
				for(i=0;i<no;i++)
				 cout<<sec[i].acc_name<<" "<<sec[i].acc_no<<" "<<sec[i].ind<<endl;
				cout<<"\nThe sorted index contents are:\n";
				for(i=0;i<no;i++)
				 cout<<in[i].acc_no<<" "<<in[i].ind<<endl;			 
				for(int i=0;i<no;i++)
				{
				
				 file2<<sec[i].acc_name<<"|"<<sec[i].acc_no<<"|"<<sec[i].ind<<"\n";
				 file3<<in[i].acc_no<<"|"<<in[i].ind<<"\n";			 
			}
				file1.close();
				file2.close();
				file3.close();
			
    			}
	
	void display()
	{
		fstream file1;
		char ind[10],
	     acc_no[20],
	     acc_name[20],
	     type[5],
	     deposit[10];
file1.open("account00.txt",ios::in);
cout<<"ACC_NO\tNAME\tTYPE\tDEPOSIT\n";
while(!file1.eof())
{
file1.getline(ind,5,'|');
file1.getline(acc_no,20,'|');
file1.getline(acc_name,20,'|');
file1.getline(type,10,'|');
file1.getline(deposit,10,'\n');
cout<<acc_no<<"\t"<<acc_name<<"\t"<<type<<"\t"<<deposit<<"\n";
}
file1.close();

	}

	

void accountsearch()
{
 
    char acc_name[20];
				cout<<"\nEnter the account name to be searched\n";
				cin>>acc_name;
				search(acc_name);
				cout<<endl<<"     PRESS ANY KEY TO CONTINUE";
}

void deleteaccount()
{
	
     char acc_name[20];
				cout<<"\nEnter the account name to be deleted\n";
				cin>>acc_name;
				del(acc_name);
					
}

/*void dep(char *acc_name)
{  

	acc_flag=0;
	int i;
	
	//char acc_name[20];
	char dep_amt[10];
	
	search(acc_name);
	if(!acc_flag)
	{
		cout<<"Deposit of account failed\n";
		return;
	}
	for(int i=0;i<no;i++)
		{
		
	 if(strcmp(acc[i].ind,acc_ind)==0)
	 {
	 	cout<<"current deposited amount in the account is:\t"<<acc[i].deposit;
	 	cout<<"\n enter the amount to be deposited:\n";
	 	cin>>acc[i].dep_amt;
	 	acc[i].deposit=acc[i].deposit+acc[i].dep_amt;
	 	break;
	 }
}
//fstream f1;
//f1.open("account00.txt",ios::out);

}

/*void deposit_amt()
  {
	char acc_name[20];
	cout<<"enter the Account name\n";
	cin>>acc_name;
	dep(acc_name);
	cout<<endl<<"     PRESS ANY KEY TO CONTINUE";
  }


    */

void check_balance()
{
	char acc_name[20];
	cout<<"enter the Account name\n";
	cin>>acc_name;
		acc_flag=0;
	int i;
	
	search(acc_name);
	if(!acc_flag)
	{
		cout<<"Deposit of account failed\n";
		return;
	}
	for(int i=0;i<no;i++)
		{
		
	 if(strcmp(acc[i].ind,acc_ind)==0)
	 {
	 	cout<<"Current Balance of the Account Holder "<<acc[i].acc_name<<" is: "<<acc[i].deposit<<" in "<<acc[i].type<<" account\n";
		break;
}
}
}


int main()
{

		int choice;
		
		cout<<"\n\n                                                       BANK MANAGEMENT\n";
		cout<<"                       ********************************************************************************************\n";
		for(;;)
		{
		
		cout<<"\n\t\t\t\t\t\t\t1.Create Account\n\t\t\t\t\t\t\t2.Search Account \n\t\t\t\t\t\t\t3.Delete Account\n\t\t\t\t\t\t\t4.Display Account Holders List \n\t\t\t\t\t\t\t5.Balance Enquiry \n\t\t\t\t\t\t\t6.Exit \n";
		cout<<"                       ********************************************************************************************\n";
		cout<<"\t\t\t\t\t\tPlease Enter your choice(1-6)\n";
		cin>>choice;
		switch(choice)
		{
		case 1:
			createaccount();
			break;
			
		case 2:{
			    accountsearch();
				break;
				
			}
		case 3:{
			    deleteaccount();
				break;
		}
		case 4:{
			 display();
			break;
		
		}
		
case 5:
	{
		check_balance();
		break;
	}
	case 6:{
		cout<<"          ************BANK MANAGEMENT********** \n";
		cout<<"              Thank You\n";
		exit(0);
		break;
	}

	default:
	cout<<"Invalid Choice!!!\n";
	 cout<<"     ENTER VALID CHOICE"<<endl;
                cout<<"     ";cin>>choice;
	break;		
}
}
};



  
