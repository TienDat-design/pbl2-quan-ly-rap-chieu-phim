#include "Screening.h"
using namespace std;
string SuatChieu::currentId="SC001";
SuatChieu::SuatChieu(): idSuatChieu(""), idRoom(""), idMovie(""), idNhanVien(""), date(Date()), time(""), seats() {}
SuatChieu::SuatChieu(const string& id, const string& r, const string& m, const string& nv, const Date& d, const string& time,
const vector<vector<Seat>>& seats) : idSuatChieu(id), idRoom(r), idMovie(m), idNhanVien(nv), date(d),time(time),seats(seats) {
}

string SuatChieu::getIdRoom() const{
    return idRoom;
}

void SuatChieu::setIdRoom(const string& id) {
    idRoom = id;
}

string SuatChieu::getIdMovie() const  {
    return idMovie;
}

void SuatChieu::setIdMovie(const string& id)  {
    idMovie = id;
}

Date SuatChieu::getDate() {
    return this->date;
}

void SuatChieu::setDate(const Date& date) {
    this->date.setNgay(date.getNgay());
    this->date.setThang(date.getThang());
    this->date.setNam(date.getNam());
}

string SuatChieu::getIdSuatChieu()  const {
    return idSuatChieu;
}

void SuatChieu::setIdSuatChieu(const string& id) {
    idSuatChieu = id;
}

string SuatChieu::getIdNhanVien() const  {
    return this->idNhanVien;
}

void SuatChieu::setIdNhanVien(const string& idNhanVien) {
    this->idNhanVien = idNhanVien;
}

string SuatChieu::getTime() const{
	return this->time;
};

void SuatChieu::setTime(const string& time){
	this->time=time;
};

void SuatChieu::setSeats(const vector<vector<Seat>>& seats) {
        this->seats = seats;
    }
    
vector<vector<Seat>>& SuatChieu::getSeats() {
        return this->seats;
    }

int SuatChieu::countBookedSeats() {
    int count = 0;
    for (int i = 0; i < seats.size(); ++i) {                  
        for (int j = 0; j < seats[i].size(); ++j) {           
            if (seats[i][j].getIsOccupied()) {              
                count++;
            }
        }
    }
    return count;
}

void SuatChieu::display()  {
    cout <<"|  " <<left << setw(15) << idSuatChieu
         <<"|  " <<setw(15) << idRoom
         <<"|  " <<setw(15) << idMovie
         <<"|  " <<setw(15) << idNhanVien
         <<"|  " <<setw(15) << date.formatDate()
         <<"|  " <<setw(5)<<this->time<<"|"<<endl;
    cout<<string(100,'-')<<endl;
    
};