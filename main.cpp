#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<iomanip>
#include<string.h>
#include<windows.h>
#define SIZE 1000
using namespace std;
class Account
{
    int acc_no;
    char name[20];
    double balance;
    char acc_tp;
    class Passbook
                {
                    int passacc;
                    char sub[15];
                    double amt,bal;
                public:
                    void addpass(int n,char s[],double a,double b)
                    {
                        passacc=n;
                        strcpy(sub,s);
                        amt=a;
                        bal=b;
                    }
                    void writepass()
                    {
                        ofstream fout("Passbook.dat",ios::app|ios::binary);
                        fout.write((char*)this,sizeof(*this));
                        fout.close();
                    }
                    void deletepass(int num)
                    {
                        ifstream fin;
                        ofstream fout;
                        fin.open("Passbook.dat",ios::in|ios::binary);
                        if(!fin)
                            cout<<"\nFile Not found"<<endl;
                        else
                        {
                            fout.open("tmp.dat",ios::out|ios::binary);
                            fin.read((char*)this,sizeof(*this));
                            while(!fin.eof())
                            {
                                if(num!=passacc)
                                {
                                    fout.write((char*)this,sizeof(*this));
                                }
                                fin.read((char*)this,sizeof(*this));
                            }
                            fin.close();
                            fout.close();
                            remove("Passbook.dat");
                            rename("tmp.dat","Passbook.dat");
                        }
                    }
                    void printpass(int l)
                    {
                            ifstream fin;
                            fin.open("Passbook.dat",ios::in|ios::binary);
                            if(!fin)
                                cout<<"File not found"<<endl;
                            else
                            {
                                int i=0;
                                fin.read((char*)this,sizeof(*this));
                                cout<<setw(15)<<"Index"<<setw(15)<<"Subject"<<setw(15)<<"Transaction"<<setw(15)<<"Balance"<<endl;

                                while(!fin.eof())
                                {
                                    if(passacc==l)
                                    {
                                        cout<<setw(15)<<++i<<setw(15)<<sub<<setw(15)<<amt<<setw(15)<<bal<<setw(15)<<endl;
                                    }
                                    fin.read((char*)this,sizeof(*this));
                                }
                                fin.close();
                            }
                    }
                };
private:
    int getnumber();
public:
    void creat_acc();
    void writefile();
    void allcust();
    void print()
    {
        cout<<setw(15)<<acc_no<<setw(15)<<name<<setw(15)<<acc_tp<<setw(15)<<balance<<endl;
    }
    void inquriy(int);
    void deleteacc(int);
    void deposit(int,int);
    int withdrawal(int,int);
    int valid(int);
    void printpassbook(int);
    void changedetails(int);
};
int Account::getnumber()
{
    int tmp=0;
    ifstream fin;
    fin.open("File.dat",ios::in|ios::binary);
    if(!fin)
    {
         return ++tmp;
    }
    else
    {
            fin.read((char*)this,sizeof(*this));
            while(!fin.eof())
            {
                tmp=acc_no;
                fin.read((char*)this,sizeof(*this));
            }
            fin.close();
    }
    return ++tmp;
}
void Account::creat_acc()
{
    Passbook p;
    acc_no=getnumber();
    cout<<"Account No :"<<acc_no<<endl;
    cout<<"Enter Details :"<<endl;
    cout<<"Enter Full Name(First Middle Last) :"<<endl;
    cin.ignore();
    cin.getline(name,19);
    T:
    cout<<"Enter Account type (C/S) :"<<endl;
    cin>>acc_tp;
    if(acc_tp=='C'||acc_tp=='c')
    {
        cout<<"For current account balance muse be >=10000"<<endl;
        balance=1000;
    }
    else if(acc_tp=='S'||acc_tp=='s')
    {
        cout<<"For saving account balance muse be >=500"<<endl;
        balance=500;
    }
    else
    {
        cout<<"Invalid!!!\nReenter..."<<endl;
        goto T;
    }
    p.addpass(acc_no,"New Account",balance,balance);
    p.writepass();
}
void Account::writefile()
{
    ofstream fout("File.dat",ios::app|ios::binary);
    fout.write((char*)this,sizeof(*this));
    fout.close();
}
void Account::inquriy(int acc)
{
        int flag=0;
        ifstream fin;
        fin.open("File.dat",ios::in|ios::binary);
        if(!fin)
            cout<<"File not found"<<endl;
        else
        {
            fin.read((char*)this,sizeof(*this));
            while(!fin.eof())
            {
                if(acc_no==acc)
                {
                    flag=1;
                    cout<<setw(15)<<"Acc No"<<setw(15)<<"Name"<<setw(15)<<"A/c Type"<<setw(15)<<"Balance"<<endl;
                    print();
                    break;
                }
                fin.read((char*)this,sizeof(*this));
            }
            fin.close();
        }
        if(flag==0)
            cout<<"Account not found."<<endl;
}
void Account::allcust()
{
    ifstream fin;
        fin.open("File.dat",ios::in|ios::binary);
        if(!fin)
            cout<<"File not found"<<endl;
        else
        {
            fin.read((char*)this,sizeof(*this));
            cout<<setw(15)<<"Acc No"<<setw(15)<<"Name"<<setw(15)<<"A/c Type"<<setw(15)<<"Balance"<<endl;
            while(!fin.eof())
            {
                print();
                fin.read((char*)this,sizeof(*this));
            }
            fin.close();
        }
}
void Account::deleteacc(int num)
{
        Passbook p;
        ifstream fin;
        ofstream fout;
        int flag=0;
        fin.open("File.dat",ios::in|ios::binary);
        if(!fin)
            cout<<"\nFile Not found"<<endl;
        else
        {
            fout.open("tmp.dat",ios::out|ios::binary);
            fin.read((char*)this,sizeof(*this));
            while(!fin.eof())
            {
                if(num!=acc_no)
                {
                    fout.write((char*)this,sizeof(*this));
                }
                else
                {
                    flag=1;
                }
                fin.read((char*)this,sizeof(*this));
            }
            fin.close();
            fout.close();
            remove("File.dat");
            rename("tmp.dat","File.dat");
        }
        if(flag==1)
        {
            p.deletepass(num);
        }
}
void Account::deposit(int ac,int bal)
{
    Passbook p;
    int flag=0;

    fstream f;
        f.open("File.dat",ios::in|ios::out|ios::ate|ios::binary);
        if(!f)
            cout<<"\nAccount not found"<<endl;
        else
        {
            f.seekg(0);
            f.read((char*)this,sizeof(*this));
            while(!f.eof())
            {
                if(ac==acc_no)
                {
                    flag=1;
                    balance+=bal;
                    f.seekp(f.tellp()-sizeof(*this));
                    f.write((char*)this,sizeof(*this));
                    break;
                }
                f.read((char*)this,sizeof(*this));
            }
            f.close();
        }
        if(flag==1)
        {
            p.addpass(ac,"Deposit",bal,balance);
            p.writepass();
        }
        else
        {
         cout<<"\nAccount not found"<<endl;
        }
}
int Account::withdrawal(int ac,int bal)
{
    int flag=0;
    Passbook p;
    fstream f;
        f.open("File.dat",ios::in|ios::out|ios::ate|ios::binary);
        if(!f)
            cout<<"\nAccount not found"<<endl;
        else
        {
            f.seekg(0);
            f.read((char*)this,sizeof(*this));
            while(!f.eof())
            {
                if(ac==acc_no)
                {
                    if((balance-bal)<1000)
                        cout<<"Fail!!!"<<endl;
                    else
                        {
                            flag=1;
                            balance-=bal;
                            f.seekp(f.tellp()-sizeof(*this));
                            f.write((char*)this,sizeof(*this));
                            break;
                        }
                }
                f.read((char*)this,sizeof(*this));
            }
            f.close();
        }
         if(flag==1)
        {
            p.addpass(ac,"Withdrawal",bal,balance);
            p.writepass();
            return 1;
        }
        else
        {
         cout<<"\nAccount not found"<<endl;
         return 0;
        }
}
int Account::valid(int acc)
{
    int tmp=0;
    ifstream fin;
        fin.open("File.dat",ios::in|ios::binary);
        if(!fin)
            return tmp;
        else
        {

            fin.read((char*)this,sizeof(*this));
            while(!fin.eof())
            {
                if(acc==acc_no)
                {
                    tmp=1;
                    break;
                }
                fin.read((char*)this,sizeof(*this));
            }
            fin.close();
            return tmp;
        }
}
void Account::printpassbook(int an)
{
    Passbook p;
    p.printpass(an);
}
void Account::changedetails(int acc)
{
    int flag=0;
    fstream f;
        f.open("File.dat",ios::in|ios::out|ios::ate|ios::binary);
        if(!f)
            cout<<"\nAccount not found"<<endl;
        else
        {
            f.seekg(0);
            f.read((char*)this,sizeof(*this));
            while(!f.eof())
            {
                if(acc==acc_no)
                {
                    flag=1;
                    char str[15];
                    cout<<"Enter New Name :"<<endl;
                    cin.ignore();
                    cin.getline(str,14);
                    strcpy(name,str);
                    f.seekp(f.tellp()-sizeof(*this));
                    f.write((char*)this,sizeof(*this));
                    break;
                }
                f.read((char*)this,sizeof(*this));
            }

        }
            f.close();
            if(flag==0)
            {
                cout<<"Account Not Found."<<endl;
            }
}

int printmenu();
int main()
{
    Account ac;
    while(1)
    {
            switch(printmenu())
            {
                case 1:
                    {
                        ac.creat_acc();
                        ac.writefile();
                        cout<<"Thank You For Opening Account !!!\nVisit Again !!!"<<endl;
                        break;
                    }
                case 2:
                    {
                        ac.allcust();
                        break;
                    }
                case 3:
                    {
                        int tmp;
                        cout<<"Enter A/C Number :"<<endl;
                        cin>>tmp;
                        ac.deleteacc(tmp);
                        break;
                    }
                case 4:
                    {
                        int tmp,bal;
                        cout<<"Enter A/C Number :"<<endl;
                        cin>>tmp;
                        cout<<"Enter Amount :"<<endl;
                        cin>>bal;
                        ac.deposit(tmp,bal);
                        break;
                    }
                case 5:
                    {
                        int tmp,bal;
                        cout<<"Enter A/C Number :"<<endl;
                        cin>>tmp;
                        cout<<"Enter Amount :"<<endl;
                        cin>>bal;
                        ac.withdrawal(tmp,bal);
                        break;
                    }
                case 6:
                    {
                        int tmp;
                        cout<<"Enter A/C Number :"<<endl;
                        cin>>tmp;
                        ac.inquriy(tmp);
                        break;
                    }
                case 7:
                    {
                        int tmp,tmp1,bal;
                        cout<<"Enter your A/c Number :"<<endl;
                        cin>>tmp;
                        if(ac.valid(tmp))
                        {
                            cout<<"Enter A\C number you want to Transfer"<<endl;
                            cin>>tmp1;
                            cout<<"Enter Amount"<<endl;
                            cin>>bal;
                            if(ac.valid(tmp1))
                            {
                                if(ac.withdrawal(tmp,bal))
                                    ac.deposit(tmp1,bal);
                            }
                            else
                            cout<<"Account Not Found"<<endl;
                        }
                        else
                            cout<<"Account Not found"<<endl;
                        break;
                    }
                case 8:
                    {
                        remove("File.dat");
                        remove("Passbook.dat");
                        break;
                    }
                case 9:
                    {
                        int tmp;
                        cout<<"Enter Account no"<<endl;
                        cin>>tmp;
                        ac.printpassbook(tmp);
                        break;
                    }
                case 10:
                    {
                        int tmp;
                        cout<<"Enter your A/c Number :"<<endl;
                        cin>>tmp;
                        ac.changedetails(tmp);
                        break;
                    }
                case 11:
                    {
                        exit(0);
                        break;
                    }
                default:
                    {
                     cout<<"Wrong Choice!!!!!!!!!!!"<<endl;
                     break;
                    }
            }
            cout<<"\n\t\t\tWait 5 Second"<<endl;
            Sleep(5000);
        }
    return 0;
}
int printmenu()
{
    int ch;
    system("cls");
    cout<<"\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1"<<endl;
    cout<<"1.Crete New Account\n2.All Customer\n3.Delete Account\n4.Deposit\n5.Withdrawal\n6.Balance Inquiry\n7.Money Transfer\n8.Delete All Account\n9.Passbook\n10.Update Details"<<endl;
    cout<<"\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1"<<endl;
    cin>>ch;
    return ch;
}
