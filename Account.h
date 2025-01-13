#pragma once
#include <string>
#include <vector>
#include "map.h"
#include "ManageSuatChieu.h"
#include "Customer.h"
#include "ticket.h"
#include<map>
using namespace std;
class Account:public Customer
{
private:
    string idAccount;
    string TenDangNhap;
    string MatKhau;
    int VaiTro;
    vector<Ticket> bookedScreenings;
    

public:
	static string currentIdAccount;
    Account(const string& id = "0000", const string& tenDangNhap = "default", const string& matKhau = "123456", const int& vaiTro = 1, const string& name = "Guest",
        const string& sdt = "0000000000", const string& membershipType = "standard", const vector<Ticket>& tickets = {});

    ~Account();
    
    void setId(const string&);
    string getId() const ;
    void setUserName(const string&);
    string getUserName() const;

    void setPassword(const string&);
    string getPassword() const;

    void setRole(const int&);
    int getRole() const;

    void setNameUser(const string&);
    string getNameUser();

    void setBookedScreenings(const vector<Ticket>&);
    vector<Ticket> getBookedScreenings() const;
    
    void setMembershipType(const string&);
    string getMembershipType() const;
    
    void Option();
    void Payment();
	void deleteTicket();
	vector<pair<string , string>>AllMovieByDate( Date&);
	void DisplayBookedScreenings();
	void BookTicket();
	
	void ghiFile(const char*);
	void docFile(const char*);	
	
	void thongKeTaiKhoan(const char*);
		//thong ke lich su dat ve cua tai khoan de khuyen mai
};
