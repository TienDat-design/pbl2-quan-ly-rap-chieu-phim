#pragma once 
#include "Person.h"
#include "Date.h"

class NhanVien:public Person{
    private:
    	string ID;
        string GioiTinh;
	    Date ngaySinh;
	public :	
	static string currentId;
    NhanVien(const string& ID = "-1", const string& Ten = " ", const string& GioiTinh = " ", 
             const string& SoDienThoai = " ", const Date& ngaySinh = Date());
             
    void setID(const string& );
    string getID() const ;
 
    void setNgaySinh(const Date& ) ;
    Date getNgaySinh() const ;
    
    void setGender( const string &GioiTinh);
    string getGender() const  ;
    
    static bool checkNumber(const string& phone) {
        regex phonePattern("^\\d{10}$");
        return regex_match(phone, phonePattern);
     }
     
    void display() ;
};
