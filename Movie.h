#pragma once
#include <string>
#include <vector>
using namespace std;

class Movie{
	private :
		string tieuDe;
		string noiDung;
		string theLoai;
		string id ;
		int thoiLuong;
		int giaPhim;
	public:
		static string currentId;
		Movie(const string& =" "  , const string& = " " , const string& = " ", const string& = " ", const int& = -1, const int& = 0);
		
		~Movie();
		
		string getTieuDe();
		string getNoiDung();
		string getTheLoai();
		string getIdMovie();
		int getThoiLuong();
		int getGiaPhim();
		
		void setTieuDe(const string& );
		void setNoiDung(const string& );
		void setTheLoai(const string& );
		void setIdMovie(const string& );
		void setThoiLuong(const int& );
		void setGiaPhim(const int&);
		
		vector<string> getTimeFrames();
		void display();
};