#include "NhanVien.h"
using namespace std;
string NhanVien::currentId = "NV000";
NhanVien::NhanVien(const string& ID , const string& Ten ,const string& gioiTinh, const string& SoDienThoai , const Date& ngaySinh )
        : ID(ID), Person(Ten,SoDienThoai),GioiTinh(gioiTinh) ,ngaySinh(ngaySinh) {}

void NhanVien::setID(const string& ID)  {
       this->ID = ID;
    }
    
string NhanVien::getID() const   {
        return ID;
    }
void NhanVien::setGender( const string &GioiTinh)  {
        this->GioiTinh = GioiTinh;
    }
string NhanVien::getGender() const  {
        return GioiTinh;
    }

void NhanVien::setNgaySinh(const Date& ngaySinh ){
	this->ngaySinh=ngaySinh;
}

Date NhanVien::getNgaySinh() const {
	return this->ngaySinh;
} ;
void NhanVien::display() {
        cout <<"| " <<setw(16) << left << ID
             <<"| "<< setw(26) << left << HoTen
             <<"| "<< setw(16) << left << GioiTinh
             <<"| "<< setw(16) << left << SDT
             <<"| "<<setw(16)<<ngaySinh.formatDate()<<right<<"|"<<endl;
        cout<<string(101,'-')<<endl;
}