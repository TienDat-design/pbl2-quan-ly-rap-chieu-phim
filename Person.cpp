#include"Person.h"
#include "utility.h"
using namespace std;

Person::Person(  const string& HoTen, const string& SoDienThoai):HoTen(HoTen),SDT(SoDienThoai)
{}

Person::~Person(){}
void Person::setName( const string &HoTen)
    {
        this->HoTen = HoTen;
    }
string Person::getName() const 
    {
        return HoTen;
    }

void Person::setPhoneNumber( const string& SoDienThoai)
    {
        this->SDT = SoDienThoai;
    }
    
string Person::getPhoneNumber() const
    {
        return  this->SDT;
    }

void Person::display() 
{
    cout << "Ho ten: " << this->getName() << endl;
    cout << "So dien thoai: " << this->getPhoneNumber() << endl;
  
}

