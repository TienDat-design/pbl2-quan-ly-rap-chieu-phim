#include "date.h"
using namespace std;
bool Date::Nhuan(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0){
			  return true;	
			}
            else
                return false; 
        }
        return true; 
    }
    return false; 
}

bool Date::validation(int day, int month, int year) {
    if (year < 1) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;

    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (day > 31) return false;
            break;
        case 4: case 6: case 9: case 11:
            if (day > 30) return false;
            break;
        case 2:
            if (Nhuan(year)) {
                if (day > 29) return false;
            } else {
                if (day > 28) return false;
            }
            break;
        default:
            return false;  
    }
    return true;
}

Date::Date(int ngay, int thang , int nam ){
	if (validation(ngay ,thang ,nam)){
		this->ngay=ngay;
		this->thang=thang;
		this->nam=nam;
	}
	else {
		this->ngay=-1;
		this->thang=-1;
		this->nam=-1;
	}
}

Date::~Date(){};

string Date::formatDate(){
    stringstream ss;
    ss << setw(2) << setfill('0') << this->ngay << "/"
       << setw(2) << setfill('0') << this->thang << "/"
       << this->nam;
    return ss.str();
}
Date& Date::operator=(const Date& other) {
    if (!validation(other.ngay, other.thang, other.nam)) {
        this->ngay = 1;
        this->thang = 1;
        this->nam = 1;
    } else if (this != &other) { 
        this->ngay = other.ngay;
        this->thang = other.thang;
        this->nam = other.nam;
    }
    return *this;
}

bool Date::operator<(const Date& other) const {
        if (nam != other.nam) return nam < other.nam;
        if (thang != other.thang) return thang < other.thang;
        return ngay < other.ngay;
    }

ostream& operator <<(ostream& o, const Date& date){
      o <<setw(2)<<setfill('0')<<right<< date.ngay << "/" <<setw(2)<<setfill('0')<<right<< date.thang << "/"<< date.nam;
      return o;
}

istream& operator>>(istream& in, Date& date) {
    do{
    cout << "Ngay : ";
    in >> date.ngay ;
    cout << "Thang : ";
    in>>date.thang;
    cout << "Nam : ";
    in>>date.nam;
    if (!date.validation(date.ngay,date.thang,date.nam)){
    	cout<<"Nhap khong hop le ! Vui long nhap lai ....\n";
	}
    }while(!date.validation(date.ngay,date.thang,date.nam));
    return in;
}

const Date Date::operator++ (int){//freefix
        Date tmp=(*this);
        this->ngay++; 
        while (!validation(this->ngay, this->thang, this->nam)) {
            switch (this->thang) {
                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    if (this->ngay > 31) {
                        this->ngay -= 31;
                        this->thang++;
                    }
                    break;
                case 4: case 6: case 9: case 11:
                    if (this->ngay > 30) {
                        this->thang-= 30;
                        this->nam++;
                    }
                    break;
                case 2:
                    if (Nhuan(this->nam)) {
                        if (this->ngay > 29) {
                            this->ngay -= 29;
                            this->thang++;
                        }
                    } else {
                        if (this->ngay > 28) {
                            this->ngay -= 28;
                            this->thang++;
                        }
                    }
                    break;
            }
    }
     return tmp; 
   };
    
Date Date::operator++ (){
	(*this)++;
	return (*this);
};

const Date Date::operator--(int) {
        Date temp = *this; 
        this->ngay--; 
        if (ngay < 1) {
            thang--; 
            if (thang < 1) {
                thang = 12; 
                nam--;    
            }
            switch (thang) {
                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    ngay = 31; 
                    break;
                case 4: case 6: case 9: case 11:
                    ngay = 30; 
                    break;
                case 2:
                    if (Nhuan(nam)) {
                        ngay = 29; 
                    } else {
                        ngay = 28; 
                    }
                    break;
            }
        }

        return temp; 
    };
    
Date Date::operator --(){//freefix
        this->ngay--; 
        if (ngay < 1) {
            thang--; 
            if (thang < 1) {
                thang = 12; 
                nam--;    
            }
            switch (thang) {
                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    ngay = 31; 
                    break;
                case 4: case 6: case 9: case 11:
                    ngay = 30; 
                    break;
                case 2:
                    if (Nhuan(nam)) {
                        ngay = 29; 
                    } else {
                        ngay = 28; 
                    }
                    break;
            }
        }  
        return *this; 
	};
	
Date& Date::operator+=(int days) {
		int count=0;
		while(count<days){
			(*this)++;
		}
        return *this;
    }
