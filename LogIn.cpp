#include"LogIn.h"
#include<iomanip>
#include<fstream>
#include<sstream>
#include<vector>
#include<math.h>

using namespace std;
//
//LogIn::LogIn(const string& ID, const string& HoTen,const string& GioiTinh,
//        const string& SDT,const string& TenDangNhap,
//        const string& MatKhau,const int& VaiTro )
//        :Account(ID,HoTen,GioiTinh,SDT,TenDangNhap,MatKhau,VaiTro){}
LogIn::~LogIn(){}

bool LogIn::checkExist(const string& TenDangNhap)
{
    for(const auto& account : accountList)
    {
        if(account.getUserName() == TenDangNhap)
        {
            return true;
        }

    }
    return false;
}

void LogIn::docFile(const char* fileName)
{
    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "Khong the mo file => File nay ko ton tai!\n";
        return;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ','))
        {
            tokens.push_back(token);
        }
        string id = tokens[0];
        string tendangnhap = tokens[1];
        string matkhau = tokens[2];
        int vaitro = stoi(tokens[3]);
        string hoten = tokens[4];
        string sodienthoai = tokens[5];
        string membershipType = tokens[6];
        Account::currentIdAccount = id ;
        Account acc(id, tendangnhap, matkhau, vaitro, hoten, sodienthoai, membershipType);
        accountList.push_back(acc);
    }
    file.close();
}

void LogIn::ghiFile(const char *fileName) 
{
    ofstream file(fileName, ios::out);//cho phep ghi de
    if(!file.is_open())
    {
        cout<<"Khong the mo file => File khong ton tai!";
        return;
    } 
    for(const auto& account:accountList)
    {
        file<<account.getId()<<","<<account.getUserName()<<","<<account.getPassword()<<","<<account.getRole()<<","<<account.getName() <<","<<account.getPhoneNumber()<<","
		<<account.getMembershipType();
		file<<endl;
    }
    file.close();
    cout<<"Da ghi file thanh cong"<<endl;
}

void LogIn::logInAccount(const string& TenDangNhap) 
{   
    
    string MatKhau;
    string sodienthoai;
    Account* it = nullptr;
    for (auto& account : accountList) 
    {
        if (account.getUserName() == TenDangNhap) 
        {
            it = &account; 
            break;
        } 
    }

    if(it == nullptr) 
    {
        cout<<"Tai khoan nay khong ton tai"; 
        return;
    }
    
    int count = 0; 
    char ch;
    while (count < 5) 
    {
        cout << "Mat khau: ";
        cin>>MatKhau;
        if (it->getPassword() == MatKhau) 
        {
            if(it->getRole() == 0)
            {
                cout<<"Day la tai khoan Admin."<<endl;
                CinemaManagement quanly;
                quanly.menu();
            }
            if(it->getRole() == 1)
            {
                cout<<"Day la tai khoan User."<<endl;
      
                it->Option();
            }
            return; 
        } 
        else 
        {
            cout << "Mat khau sai!." << endl;
            cout <<"Quen mat khau? (y/n): ";
            cin>>ch;
            if( ch == 'y' || ch == 'Y')
            {
                cout<<"Nhap so dien thoai de xac nhan nguoi dung: ";
                cin>>sodienthoai;
                if(it->getPhoneNumber() != sodienthoai)
                {
                    cout<<"So dien thoai khong dung!"<<endl;
                }
                else 
                {
                    cout<<"Xac nhan thanh cong."<<endl;
                    cout << "So dien thoai nhap vao: " << sodienthoai << endl;
                    cout<<"Dat lai mat khau."<<endl;
                    cout<<"Mat khau: ";
                    cin.ignore();
                    getline(cin,MatKhau);
                    it->setPassword(MatKhau);
                    cout<<"Dat lai mat khau thanh cong";
                    return;
                }
            }
            cout<<"Nhap lai mat khau"<<endl; cout<<endl;
            count++;
            if (count >= 5) 
            {
                cout << "Nhap sai qua so lan cho phep!"<<endl;
                return; 
            }
        }
    } 
}

void LogIn::add()
{  
    utility u;
    Account newAccount;
    int id;
    string hoten;
    string gioitinh;
    Date date;
    string diachi; 
    string userName;
    string Password;
    string sodienthoai;
    int vaitro;
    int count = 0;
    bool condition = true;
    
    cin.ignore();
    cout<<"Ho ten: ";
    getline(cin,hoten);
    newAccount.setNameUser(hoten);
    int option;
     string idAccount=u.generateNewId(Account::currentIdAccount);
     newAccount.setId(idAccount);
    do 
    {
        cout<<"Ten dang nhap: ";
        cin>>userName;
        if(checkExist(userName))
        { 
            cout<<"Ten dang nhap nay da ton tai!"<<endl; 
            cout<<"Nhap lai ten dang nhap."<<endl;
            cout<<endl;
            count++;
        }
        if(count >= 5)
        {
            cout<<"Da nhap sai qua nhieu lan!"<<endl;
            return;
        }

    } while(checkExist(userName) == true && count < 5);

    newAccount.setUserName(userName);
    cout<<"Mat khau: ";
    cin.ignore();
    cin>>Password;
    newAccount.setPassword(Password);
    do
    {
        cout<<"So dien thoai: ";
        cin>>sodienthoai;
        if(sodienthoai.size() != 10)
        {
            cout<<"So dien thoai khong hop le!"<<endl;
            cout<<"Nhap lai so dien thoai!"<<endl;
            count++;
        }
        if(count >= 5)
        {
            cout<<"Da nhap sai qua nhieu lan!"<<endl;
            return;
        }
    } while(sodienthoai.size() !=10 && count < 5);

    newAccount.setPhoneNumber(sodienthoai);

    newAccount.setRole(1);
    accountList.push_back(newAccount);
    cout<<"Da dang ky thanh cong."<<endl;
           
} 
void LogIn::add(const string& userName)
{
    Account newAccount;
    int id;
    string hoten;
    string gioitinh;
    Date date;
    string diachi; 
    string Password;
    string sodienthoai;
    int vaitro;
    int count = 0;
    bool condition = true;

    cout<<"Ban dang dang ky tai khoan:"<<endl;
    if(checkExist(userName))
    { 
        cout<<"Ten dang nhap nay da ton tai!"; 
        return;
    }

    cout<<"Ho ten: ";
    cin.ignore();
    getline(cin,hoten);
    newAccount.setNameUser(hoten);
    int option;
 
    newAccount.setUserName(userName);
    
    cout<<"Mat khau: ";
    cin.ignore();
    getline(cin,Password);
    newAccount.setPassword(Password);
    do
    {
        cout<<"So dien thoai: ";
        cin>>sodienthoai;
        if(sodienthoai.size() != 10)
        {
            cout<<"So dien thoai khong hop le!"<<endl;
            cout<<"Nhap lai so dien thoai!"<<endl;
            cout<<endl;
            count++;
        }
        if(count >= 5)
        {
            cout<<"Da nhap sai qua nhieu lan!"<<endl;
            return;
        }
    } while(sodienthoai.size() !=10 && count < 5);
    
    newAccount.setPhoneNumber(sodienthoai);
    newAccount.setRole(1);
    accountList.push_back(newAccount);
    cout<<"Da dang ky thanh cong."<<endl;
}

void LogIn::fixInformation(const string& TenDangNhap) 
{
    Account* it = nullptr;
    for(auto& account:accountList)
    {
        if(account.getUserName() == TenDangNhap)
        {
            it = &account;
            break;
        }
    }
    if(it == nullptr)
    {
        cout<<"Ten dang nhap nay khong ton tai!";
        return;
    }

    string MatKhau;
    string sodienthoai;
    int count = 0; 
    char ch;
    while (count < 5) 
    {
        cout << "Mat khau: ";
        cin>>MatKhau;
        if (it->getPassword() == MatKhau) 
        {
            cout << "Dang nhap thanh cong!" << endl;
            if(it->getRole() == 0)
            {
                cout<<"Day la tai khoan Admin."<<endl;
            }
            if(it->getRole() == 1)
            {
                cout<<"Day la tai khoan User."<<endl;
            }
            break;    
        } 
        else 
        {
            cout << "Mat khau sai!." << endl;
            cout <<"Quen mat khau? (y/n): ";
            cin>>ch;
            if( ch == 'y' || ch == 'Y')
            {
                cout<<"Nhap so dien thoai de xac nhan nguoi dung: ";
                cin>>sodienthoai;
                if(it->getPhoneNumber() != sodienthoai)
                {
                    cout<<"So dien thoai khong dung!"<<endl;
                }
            }
            cout<<endl;
            cout<<"Nhap lai mat khau"<<endl;
            count++;
            if (count >= 5) 
            {
                cout << "Nhap sai qua so lan cho phep!"<<endl;
                return; 
            }
        }
    } 

        cout<<"Bat dau chinh sua: "<<endl;
        
        string hoten;
        string gioitinh;
        Date date;
        string diachi; 
        string userName;
        string Password;
       
        

        cout<<"Ho ten: ";
        cin.ignore();
        getline(cin,hoten);
        it->setNameUser(hoten);

        int option;
        bool condition = true;
        do 
        {
            cout<<"Ten dang nhap: ";
            cin>>userName;
            if(checkExist(userName))
            { 
                cout<<"Ten dang nhap nay da ton tai!"; 
                count++;
            }
            if(count >= 5)
            {
                cout<<"Da nhap sai qua nhieu lan!"<<endl;
                return;
            }
        } while(checkExist(userName) == true && count < 5);

        it->setUserName(userName);

        cout<<"Mat khau: ";
        cin.ignore();
        getline(cin,Password);
        it->setPassword(Password);

        do
        {
            cout<<"So dien thoai: ";
            cin>>sodienthoai;
            if(sodienthoai.size() != 9)
            {
                cout<<"So dien thoai khong hop le!"<<endl;
                cout<<"Nhap lai so dien thoai!"<<endl;
                count++;
            }
            if(count >= 5)
            {
                cout<<"Da nhap sai qua nhieu lan!"<<endl;
                return;
            }
        } while(sodienthoai.size() !=9 && count < 5);

        it->setRole(1);
        cout<<"Da chinh sua thanh cong."<<endl;
                     
}   
