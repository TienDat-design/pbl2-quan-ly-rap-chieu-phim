#include "utility.h"
#include "Date.h"
#include <regex>
#pragma once
using namespace std;
class Person
{
    protected:
        string HoTen;
        string SDT;
    public:
        Person( const string& ID = "", const string& SoDienThoai=" ");
        ~Person();
        
        static bool checkNumber(const string& phone) {
            regex phonePattern("^\\d{10}$");
            return regex_match(phone, phonePattern);
         }

        void setName( const string &Ten);
        string getName() const ;

        void setPhoneNumber( const string& SoDienThoai);
        string getPhoneNumber()const;
        
        
        void display() ;
};