#include "Account.h"
#include <vector>
#include "ManageCinema.h"
#pragma once
class LogIn {
private:
    vector<Account> accountList;
public:
    ~LogIn();
    bool checkExist(const string&) ;
    void docFile(const char *fileName) ;
    void ghiFile(const char *fileName) ;
    void add() ;
    void add(const string&);
    void fixInformation(const string&) ;                
    void logInAccount(const string&);
};
