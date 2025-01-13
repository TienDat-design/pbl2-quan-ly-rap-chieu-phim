#pragma once
#include "Seat.h"
#include "utility.h"
#include <vector>
#include <regex>
#include "Date.h"
using namespace std;

class Room 
{
    private:
        string nameRoom;
        string idRoom;
        int numRows;
        int numCols;
    public:
    	Room();
        Room(const string& idRoom,const string& nameRoom, const int& numRows, const int& numCols);
        static string currentID;
        int getNumRows() const;
        int getNumCols() const ;
        
        void setNumRows(const int& numRows);
        void setNumCols(const int& numCols);

        void setNameRoom(const string&);
        string getNameRoom() const ;
        
        void setIdRoom(const string& id);
        string getIdRoom();
    
        
        void display() ;
        ~Room();

};

