//Banking Record System , C++ Project by Abhisht. 
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//---------------------------------------------------------------------------------------------------//

class Bank
{
	private:
		int account_number;
		char holder_name[50];
		int deposit;
		char type;
	public:

	void System_clear();
	void Get_Data();									
	void Write_Data();
	void deposit_withdraw(int n, int option);
	void Display_Invidual_Records(int n);
	void report() const;
	void Show_account() const;							//TO DISPALY ACCOUNT DETAILS
	void dep(int);  									//TO ADD IN DEPOSIT     
	void draw(int x);									//TO SUBTRACT FROM DEPOSIT
	int retacno() const;								//function to return account number
	int retdeposit() const;								//function to return balance amount
	char rettype() const;								//TO WITHDRAW FROM DEPOSIT			
	void Modification_data();			
};

void Bank::Get_Data(){
	cout<<"\n\n===========CREATE BANK ACCOUNT===========\n\n";
	cout<<"\nEnter the Account Number:";
	cin>>account_number;
	cout<<"\n\nEnter Account Holder Name: ";
	cin.ignore();
	cin.getline(holder_name,50);
	cout<<"\nWhich type of Account \n[S for Saving Account] (or)[C for Current Account]: ";
	cin>>type;
	type=toupper(type);
	if(type == 'S'){
		cout<<"\nEnter the Initial Amount for Saving Account [Minimum 500/-]: ";
		cin>>deposit;
		cout<<"\n\nAccount has been Created Sucessfully....";
	}
	else if(type == 'C') {
		cout<<"\nEnter the Initial Amount for Current Account [Minimum 1000/-]: ";
		cin>>deposit;
		cout<<"\n\nAccount has been Created Sucessfully....";
	}
	else{
		cout<<"\nInvalid Input";
		cout<<"\n\nAccount may Contains Conflicts...";
	}
}

void Bank::Write_Data(){
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	Get_Data();
	outFile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outFile.close();
}

void Bank::Modification_data()
{
	cout<<"\nAccount No: "<<account_number;
	cout<<"\nModify Account Holder Name: ";
	cin.ignore();
	cin.getline(holder_name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Total Balance Amount : ";
	cin>>deposit;
}

void Bank::Display_Invidual_Records(int n){
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\n\nError Occurred";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (this), sizeof(*this)))
	{
		if(retacno()==n)
		{
			Show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccounts Details not Found...";
}


void Bank::report() const
{
	cout<<account_number<<setw(10)<<" "<<holder_name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

void Bank::dep(int x)
{
	deposit =deposit + x;
}

void Bank::draw(int x)
{
	deposit-=x;
}

void Bank::Show_account() const
{
	cout<<"\nAccount No: "<<account_number;
	cout<<"\nAccount Holder Name: ";
	cout<<holder_name;
	if( type == 'S'){cout<<"\nType of Account: Saving ";}
	else{cout<<"\nType of Account: Current ";}
	cout<<"\nTotal Balance: "<<deposit;
}

int Bank::retacno() const
{
	return account_number;
}

int Bank::retdeposit() const
{
	return deposit;
}

char Bank::rettype() const
{
	return type;
}

void Bank::System_clear(){
	system("cls");
}

//-------------------------------------------------------------------------------------------------------//


void Delete_Account(int);
void system_clear(){system("cls");}
void Get_All_Data();
void Deposit_Withdraw(int,int);
void Credit();
void Account_Modification(int);
int main()
{
	char my_url;
	char choice;
	int account_number;
	Bank call;
	Credit();
	do
	{
		system_clear();
		cout<<"\n===========================";
		cout<<"\n  BANKING RECORD SYSTEM";
		cout<<"\n===========================\n\n";
		cout<<"\n\n01. CREATE NEW ACCOUNT";
		cout<<"\n\n02. MODIFY AN ACCOUNT";	
		cout<<"\n\n03. BALANCE ENQUIRY OF ACCOUNT";
		cout<<"\n\n04. DEPOSIT IN ACCOUNT";
		cout<<"\n\n05. WITHDRAW FROM ACCOUNT";
		cout<<"\n\n06. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n07. CLOSE AN ACCOUNT";
		cout<<"\n\n08. EXIT FROM PROGRAM";
		cout<<"\n\nSELECT THE OPTION: ";
		cin>>choice;
		system_clear();
		switch(choice)
		{
		case '1':
			call.Write_Data(); 
			break;
		case '2':
			cout<<"\n\n\tAccount No: "; cin>>account_number;
			Account_Modification(account_number);
			break;
		case '3':
			cout<<"\n\nAccount No: "; cin>>account_number;
			call.Display_Invidual_Records(account_number);
			break;
		case '4':
		    cout<<"\n\nAccount No: "; cin>>account_number;
			Deposit_Withdraw(account_number, 1);
			break; 
			
		case '5':
		    cout<<"\n\nAccount No: "; cin>>account_number;
			Deposit_Withdraw(account_number, 2);
			break;
			
		case '6':
		    Get_All_Data();
			break;
			
		case '7':
		    cout<<"\n\nAccount No: "; cin>>account_number;
			Delete_Account(account_number);
			break;
			
		case '8':
			cout<<"\n\n\tThanks for using Bank Record System.\n\n\tFor more cool Stuffs, visit https//github.com/imabhisht";
			cout<<"\n\n\n\n\n\tDo you want to visit my Website [Y/N]: ";
			cin>>my_url;
			my_url=toupper(my_url);
			if(my_url == 'Y')
			{ 
			    system("start https://github.com/imabhisht");
			}
			break;
		default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
        system_clear();
	}while(choice!='8');
}


//-------------------------------------------------------------------------------------------------------//


void Get_All_Data()
{
	Bank call;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Error Occurred!!";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"================================================================\n";
	cout<<"A/C NO.      	NAME           	Type        	Balance\n";
	cout<<"================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&call), sizeof(Bank)))
	{
		call.report();
	}
	inFile.close();
}

void Deposit_Withdraw(int n,int option){    
	int amt;
    Bank call;
	bool found=false;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Error Occurred...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&call), sizeof(Bank));
		if(call.retacno()==n)
		{
			call.Show_account();
			if(option==1)
			{
				cout<<"\n\n===========DEPOSITE TO ACCOUNT===========";
				cout<<"\n\nEnter the Amount: ";
				cin>>amt;
				call.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n===========WITHDRAW FROM ACCOUNT===========";
				cout<<"\n\nEnter the Amount: ";
				cin>>amt;
				int bal=call.retacno()-amt;
				if((bal<500 && call.rettype()=='S') || (bal<1000 && call.rettype()=='C'))
					cout<<"\nInsufficience Balance. Please check your Balance.";
				else
					call.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(call));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&call), sizeof(Bank));
			cout<<"\n\nAccount Records Updated Sucessfully...";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\nAccount Records not Found...";
}

void Delete_Account(int n)
{
	Bank call;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Error Occurred...";
		return;
	}
	outFile.open("account_temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&call), sizeof(Bank)))
	{
		if(call.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&call), sizeof(Bank));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("account_temp.dat","account.dat");
	cout<<"\n\nRecord has been Deleted...";
}

void Account_Modification(int n)
{
	Bank call;
	bool found=false;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Error Occurred...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&call), sizeof(Bank));
		if(call.retacno()==n)
		{
			call.Show_account();
			cout<<"\n\n===========MODIFY ACCOUNT===========";
			cout<<"\nNew Details of the Account: "<<endl;
			call.Modification_data();
			int pos=(-1)*static_cast<int>(sizeof(Bank));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&call), sizeof(Bank));
			cout<<"\n\nRecord Updated...";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void Credit(){system_clear(); cout<<"\n\nBanking Record System Project by Abhisht Chouhan."<<"\nWritten on C++.";}

