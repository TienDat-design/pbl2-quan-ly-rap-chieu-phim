#pragma once
#include <regex>
#include<iostream>
#include <conio.h>
#include "utility.h"
#include "NhanVien.h"
#include "Management.h"
#include <fstream>
#include <set>
using namespace std;

class ManageNhanVien: public Management{
	private :
		vector<NhanVien>staffs;
		int getCharAtPos(const string& str, int pos);
        void countingSortByChar(int pos);
	public :
	void Option();
	
	void add() override ;
    void remove(const string& ) override;

    void fixInformation(const string&  ) override;
    
    bool checkExist(const string& )override;
    NhanVien* Search(const string& );
    void sortById() override;
    
    bool checkFile(const char* file);
    void docFile(const char*) override; 
    void ghiFile(const char*) override;
    void display() override;
    
}; 
	