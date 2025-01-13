#pragma once
#include "utility.h"
class Management{
	public:         
		virtual void Option() =0;  
	    virtual void add() =0;              
	    virtual void fixInformation(const string&) = 0;   
	    virtual bool checkExist(const string& )=0;
	    virtual void remove(const string&) = 0;          
	    virtual void display() = 0;          
	    virtual void docFile(const char *fileName) = 0; 
	    virtual void ghiFile(const char *fileName) = 0;
	    virtual void sortById() = 0;
};