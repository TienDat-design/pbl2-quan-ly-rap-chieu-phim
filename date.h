#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
class Date{
	private :
		int ngay ;
		int thang ;
		 int nam;
    public :
    Date(int = -1, int = -1 , int = -1 );
    ~Date();  
  
    void setNgay(int d) { ngay = d; }
    void setThang(int m) { thang = m; }
    void setNam(int y) { nam = y; }
    int getNgay() const { return ngay;}
    int getThang() const { return thang;}
    int getNam() const { return nam;}   
    
    string formatDate();
	bool validation(int , int , int);
	bool Nhuan(int);
	
	friend istream& operator >>(istream&, Date&);
    friend ostream& operator <<(ostream&, const Date&);
    
    Date& operator+=(int days);
    bool operator<(const Date& other) const ;
    Date& operator=(const Date& other);
    const  Date operator++ (int);//postfix
    Date operator++ ();//freefix
    const Date operator --(int);//postfix
    Date operator --();//freefix
    bool operator==(const Date& other) const {
    return (ngay == other.ngay && thang == other.thang && nam == other.nam);
}
};
  