#pragma once
#include "Movie.h"
#include "utility.h"
#include "Management.h"
#include <vector>
#include <fstream>
#include<windows.h>
#include<conio.h>
#include <set> 
using namespace std;
class ManageMovie:public Management{
	private:
		vector<Movie>movies;	
		int getCharAtPos(const string& str, int pos);
        void countingSortByChar(int pos);	
	public:
	~ManageMovie() ;
	//vector<Movie> getMovies();
	void Option() override;
    void add() override;
    void add(const Movie& );
    void remove(const string& ) override;
    void display() override ;
    void fixInformation(const string& ) override;
    
    bool checkFile(const char*);
    void docFile(const char *) override;
    void ghiFile(const char* ) override;
    bool checkExist(const string&) override;
    void sortById() override;
    Movie* search(const string&) ;
};

