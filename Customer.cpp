#include"Customer.h"

Customer::Customer( const string& Ten,const string& SoDienThoai,const string& membershipType):Person(Ten,SoDienThoai),membershipType(membershipType){};
        
Customer::~Customer()
{};