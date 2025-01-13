#pragma once
#include <windows.h>
#include<string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
class utility{
	public :
		void gotoxy(int = 0, int = 0);
		void printCentered(const string& text, int , int , int,int );
		string generateNewId(const string& currentId);
		void displayHeaderMovie();
		void displayHeaderStaff();
		void displayHeaderScreening();	
		void displayHeader();
		string calculateEndTime(const string& startTime, int totalMinutes);
};