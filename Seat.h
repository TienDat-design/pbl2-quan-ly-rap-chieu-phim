#pragma once 
#include "utility.h"
class Seat {
	private:
	    int row;    
	    int column; 
	    bool isOccupied; 
	public : 
	Seat() : row(0), column(0), isOccupied(false) {}

    Seat( int row, int column, bool isOccupied)
        : row(row), column(column), isOccupied(isOccupied) {}

    int getRow()  {
        return row;
    }

    int getColumn()  {
        return column;
    }

    bool getIsOccupied() const {
        return isOccupied;
    }

    void setRow(const int& row) {
        this->row = row;
    }

    void setColumn(const int& column) {
        this->column = column;
    }

    void setIsOccupied(bool isOccupied) {
        this->isOccupied = isOccupied;
    }
    string formatSeat(){
    	char hang = 'A' + (this->row); 
        return string(1, hang) + to_string(column+1);
	}
	void displaySeat() const {
        char hang='A'+(this->row);
        cout << "Hang: " << hang << endl;
        cout << "Ghe so : " << this->column+1 << endl;
        cout << "Trang thai: " << (this->isOccupied ? "Da duoc dat" : "Trong") << endl;
}
};