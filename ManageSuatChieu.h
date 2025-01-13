#pragma once
#include "utility.h"
#include "Management.h"
#include "ManageRoom.h"
#include "ManageMovie.h"
#include "ManageNhanVien.h"
#include "Screening.h"
#include "Account.h"
#include "set.h"
using namespace std;

class ManageSuatChieu:public Management{
	private :
		vector<SuatChieu>danhSachSuatChieu;
		int getCharAtPos(const string& str, int pos);
        void countingSortByChar(int pos);
	public :
		  vector<SuatChieu> getScreenings();
		  void Option() ;     
		  void add() override;  
		  void add(const SuatChieu&);                 
          void fixInformation(const string&) override;   
          
          void remove(const string&) override;  
          void remove();
          
          void DetailScreening( const string&);
          void display() override;  
          void displayCustomer(const char* );

          void docFile(const char *fileName) override; 
          void ghiFile(const char* fileName) override;
          
          bool checkExist(const string& ) override ;
          bool checkExistIdRoom(const string&);
          bool checkExistIdMovie(const string&);
          bool checkExistTime(const string&,const string& , const Date& ,const string&);//check trung thoi gian
          
          void sortById() override;
          void sortByDate();
          void sort();
          SuatChieu* search(const string&) ;
          
          
          void ThongKeTheoNgay(Date&);
          void ThongKeTheoThang(int thang , int nam);
          void ThongKeTheoNam(const int&);
          void ThongKe();
      };
          