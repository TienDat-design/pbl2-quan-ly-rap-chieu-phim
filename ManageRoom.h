#pragma once
#include "Room.h"
#include "Management.h"
#include "ManageSuatChieu.h"
#include <sstream>
#include <fstream>
#include <set>
class ManageRoom:public Management{
	private :
	 vector <Room> rooms;
	 int getCharAtPos(const string& str, int pos);
     void countingSortByChar(int pos);
	public :
    ~ManageRoom();
    vector<Room> getRooms();
    void Option() ;
    void add() override;
    void add(const Room&);
    void remove(const string& ) override;
    void remove();
    
    void display() override;
    void fixInformation(const string&) override ;
    
    bool checkFile(const char*);
    void ghiFile(const char *) override;
    void docFile(const char *) override ;
    
    bool checkExist(const string&  )override;
    void sortById() override;
    Room* Search(const string& );
    void Search();
};