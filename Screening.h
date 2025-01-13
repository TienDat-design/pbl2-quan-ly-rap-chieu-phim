#pragma once
#include "Date.h"
#include <string>
#include <conio.h>
#include <iomanip>
#include <vector>
#include "Seat.h"
using namespace std;
class SuatChieu {
  private:
    string idSuatChieu;
    string idRoom;
    string idMovie;
    string idNhanVien;
    Date date;
    string time;
    vector<vector<Seat>> seats;
    
  public:
  	~SuatChieu() {};
    SuatChieu();
    static string currentId;
    SuatChieu(const string&, const string&, const string&, const string&, const Date&, const string& ,const vector<vector<Seat>>&);
    
    string getIdRoom() const ;
    void setIdRoom(const string& id);

    string getIdMovie()const  ;
    void setIdMovie(const string& id);

    Date getDate() ;
    void setDate(const Date&);

    string getIdSuatChieu() const  ;
    void setIdSuatChieu(const string& id);
    
    string getTime() const;
    void setTime(const string&);
    
    string getIdNhanVien() const ;
    void setIdNhanVien(const string& idNhanVien);
    
    vector<vector<Seat>>& getSeats() ;
    void setSeats(const vector<vector<Seat>>& seats);
    
    int countBookedSeats();
    
    SuatChieu& operator=(const SuatChieu& other) {
    if (this != &other) {
        this->idMovie = other.idMovie;
        this->idRoom = other.idRoom;
        this->idSuatChieu = other.idSuatChieu;
        this->idNhanVien = other.idNhanVien;
        this->date = other.date;
        this->seats = other.seats;
        this->time = other.time; 
    }
    return *this;
}

bool operator<(const SuatChieu& other) const {
    if (this->date == other.date) { 
        if (this->time != other.time) {
            return this->time < other.time;
        }
        return this->idSuatChieu < other.idSuatChieu; 
    }
    return this->date < other.date; 
}


void display();
};




