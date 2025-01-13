#include "Account.h"
#include <iostream>
using namespace std;
Account::Account(const string& id, const string& tenDangNhap, const string& matKhau,const int& vaiTro,
                 const string& name, const string& sdt,const string& membershipType,const vector<Ticket>& bookedScreenings)
    : idAccount(id),Customer(name,sdt,membershipType),VaiTro(vaiTro),TenDangNhap(tenDangNhap),MatKhau(matKhau),bookedScreenings(bookedScreenings){
	}

Account::~Account() {}

string Account::currentIdAccount="AC001";

void Account::setId(const string& id){
 	this->idAccount=id;
 };
 
string Account::getId() const {
 		return this->idAccount;
 }
 
void Account::setUserName(const string& tenDangNhap) {
    TenDangNhap = tenDangNhap;
}

string Account::getUserName() const {
    return TenDangNhap;
}

void Account::setNameUser(const string& name) {
    this->HoTen = name;
}

string Account::getNameUser()  {
    return this->HoTen;
}

void Account::setPassword(const string& matKhau) {
    MatKhau = matKhau;
}

string Account::getPassword() const {
    return MatKhau;
}

void Account::setRole(const int& vaiTro) {
    VaiTro = vaiTro;
}

int Account::getRole() const {
    return VaiTro;
}

void Account::setBookedScreenings(const vector<Ticket>& screenings) {
    bookedScreenings = screenings;
}

vector<Ticket> Account::getBookedScreenings() const {
    return bookedScreenings;
}

void Account::setMembershipType(const string& membership){
	this->membershipType=membership;
}

string Account::getMembershipType() const {
	return this->membershipType;
}

void Account::ghiFile(const char *filename) {
    FILE *f = fopen(filename, "a");
    if (!f) {
        cout << "Error opening file !" << endl;
        return;
    }
    for (auto it = bookedScreenings.begin(); it != bookedScreenings.end(); ++it) {
    	//mataikhoan , tennguoidung , idVe , id suatchieu, ngaymua
        fprintf(f, "%s,%s,%s,%s\n",this->getUserName().c_str(), 
				this->getNameUser().c_str(),
                it->getIdTicket().c_str(),
                it->getIdScreening().c_str());
    }
    fclose(f);
}

void Account::thongKeTaiKhoan(const char* filename ) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        cout << "Error opening file" << endl;
        return;
    }

    char tmp[200];
    map<string, int> ticketCount;

    while (fgets(tmp, sizeof(tmp), f) != NULL) {
        string userName, nameUser, idTicket, idScreening;
        int d = 0, m = 0, y = 0;

        char* token = strtok(tmp, ",");
        if (token != NULL) userName = token;
        token = strtok(NULL, ",");
        if (token != NULL) nameUser = token;
        token = strtok(NULL, ",");
        if (token != NULL) idTicket = token;
        token = strtok(NULL, "\n");
        if (token != NULL) idScreening = token;
        
        ticketCount[userName]++;
    }

    cout << "\nThong ke lich su dat ve cua Accounts" << endl;
    cout << string(42, '-') << endl;
    cout << "| " << left << setw(20) << "Username"
         << " | " << right << setw(15) << "So luong ve" << " |" << endl;
    cout << string(42, '-') << endl;

    for (const auto& entry : ticketCount) {
        cout << "| " << left << setw(20) << entry.first
             << " | " << right << setw(15) << entry.second << " |" << endl;
             cout << string(42, '-') << endl;
    }
    system("pause");
    fclose(f);
}



vector<pair<string,string>> Account::AllMovieByDate( Date& ngayChieu){
	utility u ;
    ManageMovie movies;
    ManageRoom rooms;
    ManageSuatChieu screenings;
    movies.docFile("movieWriteFile.txt");
    rooms.docFile("roomWriteFile.txt");
    screenings.docFile("screeningWriteFile.txt");
    system("cls");
    u.printCentered("lICH CHIEU PHIM ", 255, 255, 0, 30);
    vector<pair<string , string>>selectionMovie;
    set<string>AddedSelectionMovie;//luu 
    int found=0;//tim thay phim ngay do
    string tmp="CAC BO PHIM DUOC CHIEU VAO NGAY "+ngayChieu.formatDate();
	u.printCentered(tmp,255,125,0,30);
	cout << endl;
		    cout << string(139, '-') << endl;
		    cout << "| " << left << setw(8) << "ID Phim"
		         << " | " << left << setw(20) << "Ten Phim"
		         << " | " << left << setw(16) << "The Loai"
		         << " | " << right << setw(12) << "Thoi Luong"
		         << " | " << right << setw(12) << "Gia Phim"
		         << " | " << left << setw(52) << "Noi Dung"
		         << " |" << endl;
		    cout << string(139, '-') << endl;
       for ( SuatChieu& screening : screenings.getScreenings()) {
       	    Movie* movie = movies.search(screening.getIdMovie());
       		if (screening.getDate()==ngayChieu){
			   found=1;		    
	    	if (AddedSelectionMovie.find(movie->getIdMovie()) == AddedSelectionMovie.end()) {
	    	//movie->display();
	    	
	    	string id = movie->getIdMovie();
	    	string tieude = movie->getTieuDe();
	    	string theloai = movie->getTheLoai();
	    	int thoiluong = movie->getThoiLuong();
	    	int giaphim = movie->getGiaPhim();
	    	string noidung = movie->getNoiDung();
	    	cout << "| " << left << setw(8) << id
		         << " | " << left << setw(20) << tieude
		         << " | " << left << setw(16) << theloai
		         << " | " << right << setw(12) << thoiluong
		        << " | " << right << setw(12) << giaphim
		   	    << " | " << left << setfill('-')<<setw(52) << noidung
		         << " |" << endl;
		    cout << string(139, '-') << endl;
	    	AddedSelectionMovie.insert(movie->getIdMovie());
			selectionMovie.push_back({movie->getIdMovie(),movie->getTieuDe()+" - "+movie->getNoiDung()});
			}
		}
		}
		if(found==0){
			cout<<"Khong co bo phim nao chieu nay "<<ngayChieu.formatDate()<<endl;
			system("pause");
			return {};
		}
		system("pause");
	return selectionMovie;	
};    
	
void Account::BookTicket(){
	utility u;
	ManageMovie movies;
    ManageRoom rooms;
    ManageSuatChieu screenings;
    movies.docFile("movieWriteFile.txt");
    rooms.docFile("roomWriteFile.txt");
    screenings.docFile("screeningWriteFile.txt");
    system("cls");
    
	Date ngayChieu;
	cout<<"Lich chieu ngay : \n";
    cin>>ngayChieu;
    
	vector<pair<string , string>>selectionMovie = AllMovieByDate(ngayChieu);
	
    const string menuItems[] = {
     "HIEN THI CAC SUAT CHIEU CUA BO PHIM " , "DAT VE","THOAT"
    };
    const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);
    int currentSelection = 0;
    bool running = true;

    while (running) {
        system("cls");
        for (int i = 0; i < menuSize; i++) {
            u.gotoxy(40, 8 + i);
            if (i == currentSelection) {  
                cout << "> " << menuItems[i]; 
            } else {
                cout << "  " << menuItems[i];
            }
        }
        
        switch (_getch()) {
            case 0: 
            case 224: 
                switch (_getch()) {
                    case 72: 
                        currentSelection = (currentSelection > 0) ? currentSelection - 1 : menuSize - 1;
                        break;
                    case 80:  
                        currentSelection = (currentSelection + 1) % menuSize;
                        break;
                }
                break;
            case 13:  // Enter key
                switch (currentSelection) {
					case 0:{
						system("cls");
						int stt=1;
						int choice;
						if(selectionMovie.empty()){
							cout<<"Hien chua co bo phim duoc chieu !\n";
							return ;
						}
						for (const auto& selection:selectionMovie){
							cout<<stt++<<". "<<selection.second<<endl;
						}
						do{
						cout<<"Nhap lua chon (1-2-3...): ";
						cin>>choice;
						if (choice<=0||choice>selectionMovie.size()){
							cout<<"Lua chon khong hop le !"<<endl;
							return;
						}
					}
						while(choice<=0||choice>selectionMovie.size());
						
						string selectedIdMovie=selectionMovie[choice-1].first;
						for (SuatChieu& screening : screenings.getScreenings()) {
					    	if (screening.getIdMovie()==selectedIdMovie&&screening.getDate()==ngayChieu){
								screenings.DetailScreening(screening.getIdSuatChieu());
							}
						}
						system("pause");
						system("cls");
						break;    
					}
					 case 1:{
					 	system("cls");
						int stt=1;
						int choice;
						if(selectionMovie.empty()){
							cout<<"Hien chua co bo phim duoc chieu !\n";
							return ;
						}
						for (const auto& selection:selectionMovie){
							cout<<stt++<<". "<<selection.second<<endl;
						}
						do{
						cout<<"Nhap lua chon (1-2-3...): ";
						cin>>choice;
						if (choice<=0||choice>selectionMovie.size()){
							cout<<"Lua chon khong hop le !"<<endl;
							return ;
						}
					}
						while(choice<=0||choice>selectionMovie.size());
						set<string>allIdScreeningByDate;
						string selectedIdMovie=selectionMovie[choice-1].first;
						for (SuatChieu& screening : screenings.getScreenings()) {
					    	if (screening.getIdMovie()==selectedIdMovie && screening.getDate()==ngayChieu){
								screenings.DetailScreening(screening.getIdSuatChieu());
								allIdScreeningByDate.insert(screening.getIdSuatChieu());
								cout<<endl;
							}
						}
				
						
						cout<<"Chon ID suat chieu ban muon dat : \n";
						string idSuatChieu;
						int found=0;
						do{
						    cin>>idSuatChieu;
							for (const string id : allIdScreeningByDate) {
								if (idSuatChieu==id){
									found=1;
								}
							}
						    if(!screenings.checkExist(idSuatChieu)||found==0){
							cout<<"Khong ton tai id "<<idSuatChieu<<endl;
							cout<<"Nhap Lai : ";
							}
						}while(!screenings.checkExist(idSuatChieu));
						system("cls");
						screenings.DetailScreening(idSuatChieu);
						
						int soVe;
						cout<<"Ban muon dat bao nhieu ve : ";
						cin>>soVe;
						for (int i=0 ; i<soVe; i++){
						string idTicket=u.generateNewId(Ticket::idCurrentTicket);
						Ticket::idCurrentTicket = idTicket;
						SuatChieu* screening=screenings.search(idSuatChieu);
						char row;
						int col;
						int indexRow , indexCol;
						const vector<vector<Seat>>& seats = screening->getSeats();
						cout<<"Chon vi tri cho ngoi : \n";
						do{
						cout << "Hang (A-B-...): ";
						cin >> row;
						cout << "Vi tri ghe : ";
						cin >> col;
						
						indexRow=int(row - 'A');
						indexCol=col-1;
						if (indexCol < 0 || indexCol >= seats[0].size() || indexRow >= seats.size() || indexRow < 0) {
						    cout << "Ghe khong ton tai !\nChon lai:" << endl;
						}
						else if (screening->getSeats()[indexRow][indexCol].getIsOccupied()==true){
							cout<<"Cho ngoi nay da duoc dat ! Vui long chon vi tri khac \nChon lai: ";
						    system("pause");
						}else break;
					    }while(true);
					    
					    Seat ChoNgoi=Seat(indexRow,indexCol,true);
						Ticket ticket(idTicket,idSuatChieu,ChoNgoi);
						this->bookedScreenings.push_back(ticket);
						system("pause");
						system("cls");
				
						screening->getSeats()[indexRow][indexCol].setIsOccupied(true);
						screenings.DetailScreening(idSuatChieu);
						system("pause");
					}
					
						screenings.ghiFile("screeningWriteFile.txt");
					    cout<<"Ban da dat ve thanh cong !\n";
						system("pause");
						system("cls");
						break;
					 }
                    case 2: 
                        running = false;
                        system("cls");
                        break;
	                }
	                break;
	            case 27: // ESC
	                running = false;
	                break;
	        }
	    }  
	}

void Account::DisplayBookedScreenings(){
	utility u ;
    ManageMovie movies;
    ManageRoom rooms;
    ManageSuatChieu screenings;
    ManageNhanVien staffs;
    movies.docFile("movieWriteFile.txt");
    rooms.docFile("roomWriteFile.txt");
    screenings.docFile("screeningWriteFile.txt");
    staffs.docFile("staffWriteFile.txt");
    system("cls");
    u.printCentered("VE DA DAT ", 255, 255, 0, 30);
    int stt=1;
    Movie* movie;
    Room* room;
    NhanVien* staff;
    SuatChieu* screening;
    int tongGia=0;
	for (Ticket& ticket:bookedScreenings){
		screening=screenings.search(ticket.getIdScreening());
		movie = movies.search(screening->getIdMovie());
		room=rooms.Search(screening->getIdRoom());
		string tenPhim=movie->getTieuDe();
		int thoiLuong=movie->getThoiLuong();
		int giaPhim=movie->getGiaPhim();
		tongGia+=giaPhim;
		string tenPhong=room->getNameRoom();
		string choNgoi=ticket.getSeat().formatSeat();
		 cout << stt++ << ". ";
		 cout<<"ID ve: "<<ticket.getIdTicket()<<endl;
         cout<< "Phim: " << tenPhim << "\n"
         << "Thoi gian: " << thoiLuong << "\n"
         << "Gia: " << giaPhim << "\n"
         << "Phong: " << tenPhong << "\n"
         << "Cho ngoi: " << choNgoi << "\n";
    cout << "------------------------------------\n";  
	}
	system("pause");
}


void Account::Payment(){
	ManageMovie movies;
	movies.docFile("movieWriteFile.txt");
	ManageSuatChieu screenings;
	screenings.docFile("screeningWriteFile.txt");
	int tongGia=0;
	for (Ticket& ticket:bookedScreenings){
		SuatChieu* screening=screenings.search(ticket.getIdScreening());
		Movie* movie = movies.search(screening->getIdMovie());
	    int giaPhim=movie->getGiaPhim();
	    cout<<"ID Ve: "<<ticket.getIdTicket()<<"-"<<movie->getTieuDe()<<"-"<<movie->getGiaPhim()<<"VND"<<endl;
		tongGia+=giaPhim;
	}
	cout<<"Tong Gia Ca : "<<tongGia<<" VND"<<endl;
	this->ghiFile("bookedScreenings.txt");
	bookedScreenings.clear();
}

void Account::deleteTicket(){
	ManageSuatChieu screenings;
	screenings.docFile("screeningWriteFile.txt");
	DisplayBookedScreenings();
	string idTicket;
	cout<<"Nhap ID ve ban muon xoa : ";
	cin>>idTicket;
	//check
	int indexRow, indexCol;
	int found=0;
	SuatChieu* screening;
	for (auto it=this->bookedScreenings.begin();it!=this->bookedScreenings.end(); it++){
		if (it->getIdTicket()==idTicket){
			found=1;
			indexRow=it->getSeat().getRow();
			indexCol=it->getSeat().getColumn();
			screening = screenings.search(it->getIdScreening());
			bookedScreenings.erase(it);
			cout<<"Ban da huy ve co ID "<<idTicket<<" Thanh cong !"<<endl;
			break ;
		}
	}
	if (found==1){
			screening->getSeats()[indexRow][indexCol].setIsOccupied(false);
			screenings.ghiFile("screeningWriteFile.txt");
	}		
}

void Account::Option() {
	utility dohoa;
    int id;
    Ticket tickets;
	tickets.docfile("bookedScreenings.txt");
    char filename[20];
    const string menuItems[] = {
        "DAT VE", "HIEN THI CAC VE DAT DAT ","HUY VE ","THANH TOAN" ,"THOAT"
    };
    const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

    int currentSelection = 0;
    bool running = true;

    while (running) {
        system("cls");
        dohoa.gotoxy(20, 1);
        cout << " ---------------------HE THONG DAT VE ---------------------";
        dohoa.gotoxy(20, 2);
        cout << "HUONG DAN";
        dohoa.gotoxy(20, 3);
        cout << "Su dung 4 phim mui ten de di chuyen";
        dohoa.gotoxy(20, 4);
        cout << "ESC: Thoat      Enter: Chon";

        dohoa.gotoxy(5, 6);
        cout << "MENU";
        for (int i = 0; i < menuSize; i++) {
            dohoa.gotoxy(5, 8 + i);
            if (i == currentSelection) {
                cout << "> " << menuItems[i]; 
            } else {
                cout << "  " << menuItems[i];
            }
        }

        switch (_getch()) {
            case 0: 
            case 224: 
                switch (_getch()) {
                    case 72: 
                        currentSelection = (currentSelection > 0) ? currentSelection - 1 : menuSize - 1;
                        break;
                    case 80: 
                        currentSelection = (currentSelection + 1) % menuSize;
                        break;
                }
                break;
            case 13: 
                switch (currentSelection) {
					case 0:
						system("cls");
						this->BookTicket();
						system("pause");
						break;
					case 1:
						system("cls");
					    DisplayBookedScreenings();
						system("pause");
						break;
					case 2:{
						deleteTicket();
						system("pause");
						break;
					}
					case 3:{
						Payment();
						system("pause");
						break;
					}
                    case 4: 
                        running = false;
                        system("cls");
                        break;
                }
                break;
            case 27: // ESC
                running = false;
                break;
        }
    }
};
