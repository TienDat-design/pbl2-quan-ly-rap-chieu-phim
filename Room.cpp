#include "Room.h"
using namespace std;
Room::~Room(){};
string Room::currentID ="RM000";
Room::Room() : idRoom(""),nameRoom(""), numRows(0), numCols(0) {};

Room::Room( const string& idRoom ,const string& nameRoom,const int& numRows, const int& numCols)
    : idRoom(idRoom),nameRoom(nameRoom),numRows(numRows), numCols(numCols) { };
    
    void Room::setIdRoom(const string& id){
    	this->idRoom=id;
	}
	string Room::getIdRoom(){
		return this->idRoom;
	}
    void Room::setNameRoom(const string& nameRoom){
    	this->nameRoom=nameRoom;
	}
	
	string Room::getNameRoom() const {
		return this->nameRoom;
	}
    
    void Room::setNumRows(const int& numRows) {
        this->numRows = numRows;
    }

    void Room::setNumCols(const int& numCols) {
        this->numCols = numCols;
    }
    
    int Room::getNumRows() const {
        return numRows;
    }

    int Room::getNumCols() const {
        return numCols;
    }
    
    void Room::display()  {
        cout << "+-------------------+---------------------+\n";
        cout << "| Room:            | " << setw(20) << left << nameRoom << " |\n";
        cout << "+-------------------+---------------------+\n";
        cout << "| ID:              | " << setw(20) << left << idRoom << " |\n";
        cout << "+-------------------+---------------------+\n";
        cout << "| Size:            | " << left << numRows << " rows x " << numCols << " columns  |\n";
        cout << "+-------------------+---------------------+\n";
    }
    
