#include "Movie.h"
#include "utility.h"
using namespace std;
string Movie::currentId = "MV000";
Movie::Movie(const string& id ,const string& tieude ,const string& noidung ,const string& theloai ,const int& thoiluong, const int& giaPhim){
	this->setIdMovie(id);
	this->setNoiDung(noidung);
	this->setTheLoai(theloai);
	this->setTieuDe(tieude);
	this->setThoiLuong(thoiluong);
	this->giaPhim=giaPhim;
}
Movie::~Movie() {}

    string Movie::getTieuDe() { return this->tieuDe; }
    string Movie::getNoiDung() { return this->noiDung; }
    string Movie::getTheLoai() { return this->theLoai; }
    string Movie::getIdMovie() { return this->id; }
    int Movie::getThoiLuong() { return this->thoiLuong; }
    int Movie::getGiaPhim(){
    	return this->giaPhim;
	}

    void Movie::setTieuDe(const string& tieuDe) { this->tieuDe = tieuDe; }
    void Movie::setNoiDung(const string& noiDung) { this->noiDung = noiDung; }
    void Movie::setTheLoai(const string& theloai) { this->theLoai = theloai; }
    void Movie::setIdMovie(const string& id) { this->id = id; }
    void Movie::setThoiLuong(const int& thoiLuong) { this->thoiLuong = thoiLuong; }
    void Movie::setGiaPhim(const int& giaPhim){
    	this->giaPhim=giaPhim;
	}
	
vector<string> Movie::getTimeFrames() {
        int gioBatDau = 9, phutBatDau = 0;
        vector<string> timeFrames;

        while (gioBatDau < 24) {
            string timeFrame = to_string(gioBatDau) + ":" + to_string(phutBatDau);
            timeFrames.push_back(timeFrame);

            int tmp = phutBatDau + getThoiLuong();
            gioBatDau += tmp / 60;
            phutBatDau = tmp % 60 + 20;

            if (phutBatDau >= 60) {
                gioBatDau++;
                phutBatDau %= 60;
            }
        }
        return timeFrames;
};

void Movie::display() {
    cout << "| " << left << setw(8) << this->getIdMovie()
         << " | " << left << setw(20) << this->getTieuDe()
         << " | " << left << setw(16) << this->getTheLoai()
         << " | " << right << setw(12) << this->getThoiLuong()
         << " | " << right << setw(12) << this->getGiaPhim()
         << " | " << left << setfill('-')<<setw(52) << this->getNoiDung()<<" |" << "\n";
         cout << string(139, '-')<<endl;
}
