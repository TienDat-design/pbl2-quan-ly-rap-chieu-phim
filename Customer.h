#include"Person.h"
#pragma once

class Customer : public Person
{
	protected :
		string membershipType;
    public:
    	Customer( const string& Ten=" ",const string& SoDienThoai=" ",const string& = "standard");
        
       	static string currentID;
        ~Customer();
};
