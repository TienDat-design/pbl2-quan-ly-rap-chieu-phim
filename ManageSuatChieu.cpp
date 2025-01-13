#include "ManageSuatChieu.h"
#include "conio.h"
using namespace std;
vector<SuatChieu> ManageSuatChieu::getScreenings(){
	return this->danhSachSuatChieu;
}

int ManageSuatChieu::getCharAtPos(const string& str, int pos) {
    if (pos < str.size()) {
        return str[str.size() - pos - 1];
    }
    return -1;
}

void ManageSuatChieu::countingSortByChar(int pos) {
    vector<SuatChieu> output(danhSachSuatChieu.size());
    int count[256] = {0};

    for (auto& sc : danhSachSuatChieu) {
        int charAt = getCharAtPos(sc.getIdSuatChieu(), pos);
        count[charAt + 1]++;
    }

    for (int i = 1; i < 256; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = danhSachSuatChieu.size() - 1; i >= 0; --i) {
        int charAt = getCharAtPos(danhSachSuatChieu[i].getIdSuatChieu(), pos);
        output[count[charAt + 1] - 1] = danhSachSuatChieu[i];
        count[charAt + 1]--;
    }

    danhSachSuatChieu = output;
}

void ManageSuatChieu::sortById() {
    int maxLength = 0;

    for (auto& sc : danhSachSuatChieu) {
        maxLength = max(maxLength, (int)sc.getIdSuatChieu().size());
    }

    for (int pos = 0; pos < maxLength; ++pos) {
        countingSortByChar(pos);
    }
}

void ManageSuatChieu::sortByDate() {
    int n = danhSachSuatChieu.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (danhSachSuatChieu[j].getDate() < danhSachSuatChieu[minIndex].getDate()) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            SuatChieu temp = danhSachSuatChieu[i];
            danhSachSuatChieu[i] = danhSachSuatChieu[minIndex];
            danhSachSuatChieu[minIndex] = temp;
        }
    }
}

void ManageSuatChieu::sort(){
	cout<<"1 | Sap xep theo ID\n";
	cout<<"2 | Sap xep theo ngay chieu\n";
	int choice;
	cout<<"Lua chon : ";
	do{
		cin>>choice;
		if (choice !=1&&choice!=2){
			cout<<"Nhap lai: ";
		}
	}while(choice !=1&&choice!=2);
	if (choice==1){
		this->sortById();
	}
	else {
		this->sortByDate();
	}
}


bool ManageSuatChieu::checkExistTime(const string& idRoom,const string& idMovie, const Date& date, const string& time ){
		for (SuatChieu suatchieu : danhSachSuatChieu) {
	        if (suatchieu.getIdRoom()==idRoom&&suatchieu.getIdMovie()==idMovie && suatchieu.getDate()==date && suatchieu.getTime()==time) 
			{
				return true;
			 }
		}
		return false;     	
}

void ManageSuatChieu::docFile(const char* filename) {
    ManageRoom rooms;
    rooms.docFile("roomWriteFile.txt");
    system("cls");
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong the mo tep %s\n", filename);
        return;
    }
    char tmp[200];

    while (fgets(tmp, sizeof(tmp), f) != NULL) {
        string idScreening, idRoom, idMovie, idStaff, time;
        int d = 0, m = 0, y = 0;

        char* token = strtok(tmp, ",");
        if (token != NULL) idScreening = token;
        token = strtok(NULL, ",");
        if (token != NULL) idRoom = token;

        token = strtok(NULL, ",");
        if (token != NULL) idMovie = token;

        token = strtok(NULL, ",");
        if (token != NULL) idStaff = token;

        token = strtok(NULL, "/");
        if (token != NULL) d = atoi(token);

        token = strtok(NULL, "/");
        if (token != NULL) m = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) y = atoi(token);

        token = strtok(NULL, "\n");
        if (token != NULL) time = token;

        Room* room = rooms.Search(idRoom);
        if (room == NULL) {
            cout << "Phong co id " << idRoom << " chua duoc them vao quan ly !\n";
            return ;
        }

        int rows = room->getNumRows();
        int cols = room->getNumCols();
        vector<vector<Seat>> seats(rows, vector<Seat>(cols));

        for (int i = 0; i < rows; ++i) {
            if (fgets(tmp, sizeof(tmp), f) == NULL) {
                cout << "Loi : Du lieu ghe khong du cho phong co id " << idRoom << "!\n";
                return;
            }
            token = strtok(tmp, " ");
            for (int j = 0; j < cols && token != NULL; ++j) {
                seats[i][j].setIsOccupied(strcmp(token, "1") == 0);
                token = strtok(NULL, " ");
            }
        }

        Date tmpDate(d, m, y);
        SuatChieu suatChieu(idScreening, idRoom, idMovie, idStaff, tmpDate, time, seats);
        danhSachSuatChieu.push_back(suatChieu);
    }
    this->sortById();
    SuatChieu::currentId=this->danhSachSuatChieu.back().getIdSuatChieu();
    fclose(f);
};

void ManageSuatChieu::ghiFile(const char* filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        cout << "Error opening file!\n";
        return;
    }
    ManageRoom rooms;
	rooms.docFile("roomWriteFile.txt");
	system("cls");
    for (auto it = danhSachSuatChieu.begin(); it != danhSachSuatChieu.end(); ++it) {
        Date tmp = it->getDate();
        fprintf(f, "%s,%s,%s,%s,%d/%d/%d,%s\n", 
                it->getIdSuatChieu().c_str(),
                it->getIdRoom().c_str(),
                it->getIdMovie().c_str(),
                it->getIdNhanVien().c_str(),
                tmp.getNgay(),
                tmp.getThang(),
                tmp.getNam(),
                it->getTime().c_str());
                
        Room* room=rooms.Search(it->getIdRoom());
	    int rows=room->getNumRows();
	    int cols=room->getNumCols();
	    const vector<vector<Seat>>seats=it->getSeats();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j <cols; ++j) {
                if (seats[i][j].getIsOccupied()) {
                    fprintf(f, "1 ");
                } else {
                    fprintf(f, "0 ");
                }
            }
            fprintf(f, "\n");
        }
    }


    fclose(f);
}

void ManageSuatChieu::add(){
	utility u ;
	ManageMovie movies;
    ManageRoom rooms;
    ManageNhanVien staffs;
    movies.docFile("movieWriteFile.txt");
    rooms.docFile("roomWriteFile.txt");
    staffs.docFile("staffWriteFile.txt");
    system("cls");
    
    int countInput = 0, choice;
    string idPhong, idPhim, idSuatChieu, idNhanVien;
    Date date;
    cout<<"Nhap ID Suat Chieu : ";
    
  do{
    	cin>>idSuatChieu;
    	if(checkExist(idSuatChieu)){
    		cout<<"ID da bi trung !\n";
    		int choiceID;
			cout<<"Nhap 1 neu ban muon ID tu dong ! hoac Nhan bat ki de tiep tuc :\n";
			cout<<"Nhap : ";
			cin>>choiceID;
			if(choiceID==1){
				idSuatChieu=u.generateNewId(SuatChieu::currentId);
				cout<<"ID suat chieu :  "<<idSuatChieu<<endl;
				break;
			}
			else {
				system("cls");
				cout<<"Nhap ID suat chieu : ";
			}
		}
	}while(checkExist(idSuatChieu));
    
    countInput = 0;
    while (true) {
        if (countInput == 3) return;
        cout << "Nhap id phong : ";
        cin>>idPhong;
        if (!rooms.checkExist(idPhong)) {
            cout << "Khong ton tai phong co id: " << idPhong << ". Vui long nhap lai!\n";
            countInput++;
        } else break;
    }

    countInput = 0;
    while (true) {
        if (countInput == 3) return;
        cout << "Nhap ID Nhan vien: ";
         cin>>idNhanVien;
        if (!staffs.checkExist(idNhanVien)) {
            cout << "Khong ton tai Nhan vien co id: " << idNhanVien << ". Vui long nhap lai!\n";
            countInput++;
        } else break;
    }

    countInput = 0;
    while (true) {
        cout << "Nhap ID Phim: ";
        cin>>idPhim;
        if (!movies.checkExist(idPhim)) {
            cout << "Khong ton tai phim co id: " << idPhim << ". Vui long nhap lai!\n";
            countInput++;
        } else break;
    }

    cin >> date;

    Movie* movie = movies.search(idPhim);
    vector<string> timeFrame = movie->getTimeFrames();
    cout << "Khung gio chieu cua phim: ";
    for (int i = 0; i < timeFrame.size(); i++) {
        cout << i + 1 << "| " << timeFrame[i] << "      ";
    }
    cout << endl;

    countInput = 0;
    while (true) {
        if (countInput == 10) {
            cout << "Ket thuc ham them suat chieu!\n";
            break;
        }
        cout << "Chon: ";
        cin >> choice;
        if (choice <= 0 || choice > timeFrame.size()) {
            cout << "Lua chon khong hop le! Vui long chon lai\n";
            countInput++;
        } else {
            string time = timeFrame[choice - 1];
            if (checkExistTime(idPhong, idPhim, date, time)) {
                cout << "Khung gio nay da duoc len lich! \nChon lai: ";
                countInput++;
            } else break;
        }
    }
    Room* room=rooms.Search(idPhong);
    if(room==NULL){
    	cout<<"Khong ton tai phong ";
	}
    int rows=room->getNumRows();
    int cols=room->getNumCols();
    vector<vector<Seat>> seats(rows, vector<Seat>(cols));
	for (int i = 0; i < rows; ++i) {
          for (int j = 0; j < cols; ++j) {
            seats[i][j]=Seat(i,j,false);
        }				
    }
     SuatChieu suatChieu(idSuatChieu, idPhong, idPhim, idNhanVien, date, timeFrame[choice - 1],seats);
    danhSachSuatChieu.push_back(suatChieu);
    cout << "Ban da them suat chieu thanh cong!\n";
}

void ManageSuatChieu::add(const SuatChieu& suatChieu) {
    danhSachSuatChieu.push_back(suatChieu);
};

void ManageSuatChieu::remove(const string& idSuatPhim) {
	if (!checkExist(idSuatPhim)) {
		 cout << "Khong tim thay suat chieu co ID: " << idSuatPhim << endl;
		 return ;
		}
	     for (auto it = danhSachSuatChieu.begin(); it !=danhSachSuatChieu.end(); it++) {
	        if ((*it).getIdSuatChieu() == idSuatPhim) {
	        	int choice;
	        	cout<<"Ban co dong y muon xoa Suat Chieu co id "<<idSuatPhim<<" Khong !\n";
	        	cout<<"0 - Khong     "<<"1 - Co\n";
	        	cout<<"Nhap : ";
	        	do{
	        	    cin>>choice;
	        		if(choice!=0&&choice!=1){
	        			cout<<"Lua chon khong dung !\nNhap lai : "; 
					}
				}while(choice!=0&&choice!=1);
	        	if(choice==0) return ;
	        	if (choice==1) {
	        		danhSachSuatChieu.erase(it);
	        	    cout<<"Da xoa phim co ID : "<<idSuatPhim<<" "<<"thanh cong !"<<endl;
				}
	            return; 
	        }
	    }
	}
	
void ManageSuatChieu::remove() {
	cout<<"1 | Xoa theo ID \n";
	cout<<"2 | Xoa suat chieu theo ngay\n";
	cout<<"3 | Xoa suat chieu theo phong\n";
	cout<<"4 | Xoa suat chieu theo phim \n";
	cout<<"5 | Xoa tat ca suat chieu \n";
	cout<<"0 | Ket thuc ."<<endl;
	int choice;
	do{
		cout<<"Nhap  : ";
		cin>>choice;
		if (choice<0||choice>5){
			cout<<"Lua chon khong hop le !"<<endl;
		}else break;
	}while(choice<0||choice>5);
	switch(choice){
		case 1:{
			system("cls");
			string idScreening;
			cin.ignore();
			cout<<"Nhap ma suat chieu can xoa : ";
			cin>>idScreening;
			remove(idScreening);
			system("pause");
			break;
		}
	    case 2:{
	    	int found;
	    	Date ngayXoa;
	    	cin>>ngayXoa;
	    	for (auto it = danhSachSuatChieu.begin(); it !=danhSachSuatChieu.end(); it++) {
		        if ((*it).getDate() == ngayXoa) {
		        	found=1;
		        	it=danhSachSuatChieu.erase(it);
		        	cout<<"Da xoa suat phim ngay : "<<ngayXoa<<" "<<"thanh cong !"<<endl;
		        }
		    }
		    if (found==0){
		    	cout<<"Khong tim thay suat phim ngay : "<<ngayXoa<<" "<<"thanh cong !"<<endl;
					}	
				break;
			}
		case 3:{
			string idPhong;
			cin>>idPhong;
			int found=0;
			for (auto it = danhSachSuatChieu.begin(); it !=danhSachSuatChieu.end(); it++) {
		        if ((*it).getIdRoom() == idPhong) {
		        	found=1;
		        	it=danhSachSuatChieu.erase(it);
		        	cout<<"Da xoa suat chieu phong co : "<<idPhong<<" "<<"thanh cong !"<<endl;
		        }
		    }
		    if (found==0){
		    	cout<<"Khong tim thay suat chieu phong co : "<<idPhong<<endl;
			}	
			break;
		}
	    case 4:{
	    	string idPhim;
			int found=0;
			for (auto it = danhSachSuatChieu.begin(); it !=danhSachSuatChieu.end(); it++) {
		        if ((*it).getIdMovie() == idPhim) {
		        	found=1;
		        	it=danhSachSuatChieu.erase(it);
		        	cout<<"Da xoa suat chieu phim co : "<<idPhim<<" "<<"thanh cong !"<<endl;
		        }
		    }
		    if (found==0){
		    	cout<<"Khong tim thay suat chieu phong co : "<<idPhim<<endl;
			}
			break;
		}
		case 5:{
			this->danhSachSuatChieu.clear();
			cout<<"Ban da xoa tat ca suat chieu"<<endl;
			break;
		}
		case 0:{
			cout<<"Ket thuc ham xoa !\n";
			break;
		}
	}
}



void ManageSuatChieu::fixInformation(const string& id) {
    utility u;
    ManageMovie movies;
    ManageRoom rooms;
    ManageNhanVien staffs;

    movies.docFile("movieWriteFile.txt");
    rooms.docFile("roomWriteFile.txt");
    staffs.docFile("staffWriteFile.txt");
    system("cls");
    int selection;

    if (!checkExist(id)) {
        cout << "Khong tim thay Suat Chieu voi ID: " << id << "!\n";
        return;
    }

    SuatChieu* fixedScreening = search(id);
    u.displayHeaderScreening();
    fixedScreening->display();

    do {
        cout << "=================== Menu Chinh Sua ===================\n";
        cout << "1. Sua ID Suat Chieu\n";
        cout << "2. Sua ID Phong\n";
        cout << "3. Sua ID Phim\n";
        cout << "4. Sua Ngay Chieu\n";
        cout << "5. Sua Thoi Gian Chieu\n";
        cout << "6. Thoat\n";
        cout << "======================================================\n";
        cout << "Nhap lua chon: ";
        cin >> selection;

        switch (selection) {
            case 1: {
                system("cls");
                string idSuatChieu;
                do {
                    cout << "Nhap ID Suat Chieu moi: ";
                    cin >> idSuatChieu;

                    if (idSuatChieu.empty()) {
                        cout << "ID khong duoc de trong!\n";
                    } else if (checkExist(idSuatChieu)) {
                        cout << "ID da ton tai. Vui long nhap lai.\n";
                    }
                } while (idSuatChieu.empty() || checkExist(idSuatChieu));

                fixedScreening->setIdSuatChieu(idSuatChieu);
                u.displayHeaderScreening();
                fixedScreening->display();
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                string tenPhong;
                do {
                    cout << "Nhap Ten Phong moi: ";
                    cin.ignore();
                    getline(cin, tenPhong);

                    if (tenPhong.empty()) {
                        cout << "Ten Phong khong duoc de trong!\n";
                    } else if (!rooms.checkExist(tenPhong)) {
                        cout << "Phong khong ton tai. Vui long kiem tra lai.\n";
                    } else if (checkExistTime(tenPhong, fixedScreening->getIdMovie(),
                                              fixedScreening->getDate(), fixedScreening->getTime())) {
                        cout << "Suat chieu nay da duoc len lich! Vui long nhap lai.\n";
                    }
                } while (tenPhong.empty() || !rooms.checkExist(tenPhong) ||
                         checkExistTime(tenPhong, fixedScreening->getIdMovie(),
                                        fixedScreening->getDate(), fixedScreening->getTime()));

                fixedScreening->setIdRoom(tenPhong);
                u.displayHeaderScreening();
                fixedScreening->display();
                system("pause");
                break;
            }
            case 3: {
                system("cls");
                string idPhim;
                do {
                    cout << "Nhap ID Phim moi: ";
                    cin >> idPhim;

                    if (idPhim.empty()) {
                        cout << "ID Phim khong duoc de trong!\n";
                    } else if (!movies.checkExist(idPhim)) {
                        cout << "Phim khong ton tai. Vui long kiem tra lai.\n";
                    } else if (checkExistTime(fixedScreening->getIdRoom(), idPhim,
                                              fixedScreening->getDate(), fixedScreening->getTime())) {
                        cout << "Suat chieu nay da duoc len lich! Vui long nhap lai.\n";
                    }
                } while (idPhim.empty() || !movies.checkExist(idPhim) ||
                         checkExistTime(fixedScreening->getIdRoom(), idPhim,
                                        fixedScreening->getDate(), fixedScreening->getTime()));

                fixedScreening->setIdMovie(idPhim);
                u.displayHeaderScreening();
                fixedScreening->display();
                system("pause");
                break;
            }
            case 4: {
                system("cls");
                Date ngayChieu;
                do {
                    cout << "Nhap Ngay Chieu moi (dd mm yyyy): ";
                    cin >> ngayChieu;

                    if (checkExistTime(fixedScreening->getIdRoom(), fixedScreening->getIdMovie(),
                                       ngayChieu, fixedScreening->getTime())) {
                        cout << "Suat chieu nay da duoc len lich! Vui long nhap lai.\n";
                    } else {
                        break;
                    }
                } while (true);

                fixedScreening->setDate(ngayChieu);
                u.displayHeaderScreening();
                fixedScreening->display();
                system("pause");
                break;
            }
            case 5: {
                system("cls");
                vector<string> timeFrame = movies.search(fixedScreening->getIdMovie())->getTimeFrames();
                int choice;

                cout << "Khung gio chieu cua phim: \n";
                for (int i = 0; i < timeFrame.size(); i++) {
                    cout << i + 1 << ". " << timeFrame[i] << "\n";
                }

                do {
                    cout << "Chon khung gio (1-" << timeFrame.size() << "): ";
                    cin >> choice;

                    if (choice <= 0 || choice > timeFrame.size()) {
                        cout << "Lua chon khong hop le! Vui long chon lai.\n";
                    } else if (checkExistTime(fixedScreening->getIdRoom(), fixedScreening->getIdMovie(),
                                              fixedScreening->getDate(), timeFrame[choice - 1])) {
                        cout << "Khung gio nay da duoc len lich! Chon lai: \n";
                    } else {
                        break;
                    }
                } while (true);

                fixedScreening->setTime(timeFrame[choice - 1]);
                u.displayHeaderScreening();
                fixedScreening->display();
                system("pause");
                break;
            }
            case 6:
                cout << "Thoat chinh sua.\n";
                break;
            default:
                system("cls");
                cout << "Lua chon khong hop le. Vui long chon lai!\n";
        }
    } while (selection != 6);

    cout << "Chinh sua thong tin Suat Chieu co ID " << id << " thanh cong!\n";
};



void ManageSuatChieu::DetailScreening( const string& idScreening){
	utility u;
    ManageMovie movies;
    ManageRoom rooms;
    ManageNhanVien staffs;

    movies.docFile("movieWriteFile.txt");
    rooms.docFile("roomWriteFile.txt");
    staffs.docFile("staffWriteFile.txt");
	SuatChieu* screening=search(idScreening);
	Room* room=rooms.Search(screening->getIdRoom());
	Movie* movie=movies.search(screening->getIdMovie());
	NhanVien* staff=staffs.Search(screening->getIdNhanVien());
	cout<<"ID suat chieu : "<<screening->getIdSuatChieu()<<endl;
	cout<<"Ten Phong : "<<room->getNameRoom()<<endl;
	cout<<"Ten Phim : "<<movie->getTieuDe()<<endl;
	cout<<"Thoi gian chieu : "<<screening->getTime()<<endl;
	int rows=room->getNumRows();
	int cols=room->getNumCols();
	u.printCentered("THONG TIN CHO NGOI",255,215,0,30);
	char hang ='A';
	cout<<setfill(' ') << setw(37)<<" ";
	for (int col=1 ; col<cols+1; col++) cout<<col<<"     ";
    cout<<endl;
	for (int i = 0; i < rows; ++i) {
		cout<<setfill(' ') << setw(33)<<" ";
    	cout<<hang++<<" ";
    for (int j = 0; j < cols; ++j) {
	    if (!screening->getSeats()[i][j].getIsOccupied()) {	
	     cout << "\033[38;2;124;252;0m[ O ]\033[0m ";
	    } else {                           
	        cout << "\033[38;2;255;0;0m[ X ]\033[0m ";
	    }                                
	}
		cout<<endl<<endl;
    }
};

void ManageSuatChieu::display() {
	ManageRoom rooms;
	rooms.docFile("roomWriteFile.txt");
	utility u;
    for ( SuatChieu& suatChieu : danhSachSuatChieu) {
    	u.displayHeaderScreening();
    	suatChieu.display();
    	
		Room* room=rooms.Search(suatChieu.getIdRoom());
		int rows=room->getNumRows();
		int cols=room->getNumCols();
		u.printCentered("THONG TIN CHO NGOI",255,215,0,30);
		char hang ='A';
		cout<<setfill(' ') << setw(37)<<" ";
		for (int col=1 ; col<cols+1; col++) cout<<col<<"     ";
        cout<<endl;
		for (int i = 0; i < rows; ++i) {
			cout<<setfill(' ') << setw(33)<<" ";
        	cout<<hang++<<" ";
        for (int j = 0; j < cols; ++j) {
			    if (!suatChieu.getSeats()[i][j].getIsOccupied()) {
			        cout << "\033[38;2;124;252;0m[ O ]\033[0m ";
			    } else {
			        cout << "\033[38;2;255;0;0m[ X ]\033[0m ";
			    }
			}
			cout<<endl<<endl;
    }
    cout << endl<<endl;  
    }
};

SuatChieu* ManageSuatChieu::search(const string& id) {
    for ( SuatChieu& suatChieu : danhSachSuatChieu) {
        if (suatChieu.getIdSuatChieu() == id) {
            return &suatChieu; 
        }
    }
    cout << "Suat chieu khong tim thay!" << endl;
    return NULL;
};

bool ManageSuatChieu::checkExistIdRoom(const string& idRoom){
	for (auto& suatChieu : danhSachSuatChieu) {
        if (suatChieu.getIdRoom()==idRoom) {
        	return true;
        }
		}
		return false;
	}
	
bool ManageSuatChieu::checkExistIdMovie(const string& idMovie){
	for (auto& suatChieu : danhSachSuatChieu) {
        if (suatChieu.getIdMovie()==idMovie) {
        	return true;
        }
		}
		return false;
	}	
	
bool ManageSuatChieu::checkExist(const string& id){
	 	for (auto it = danhSachSuatChieu.begin(); it != danhSachSuatChieu.end(); it++) {
            if ((*it).getIdSuatChieu() == id) return true;
        }
    return false;
};



void ManageSuatChieu::ThongKeTheoNgay(Date& date)
{
	utility u ;
    set<SuatChieu> listScreeningDay;
    
    ManageMovie movies;
    movies.docFile("movieWriteFile.txt");
    
    for (SuatChieu& screening : danhSachSuatChieu) 
    {
        if (screening.getDate() == date)
        {
            listScreeningDay.insert(screening);
        }
    }

    cout << string(60, '-') << "Ngay " << date.formatDate() << string(60, '-') << endl;

    cout << "| " << setw(16) << left << "Suat chieu"
         << "| " << setw(16) << left << "Phim"
         << "| " << setw(16) << left << "Bat dau"
         << "| " << setw(16) << left << "Ket thuc"
         << "| " << setw(20) << left << "Gia tien "
         << "| " << setw(20) << left << "So ve phat hanh"
         << "| " << setw(17) << left << "So ve da dat "
         << "| " << endl;
    cout << string(136, '-') << endl;

    int countBookedSeats = 0;
    int countSeats = 0;
    int totalPrice=0;
    for (auto it = listScreeningDay.begin(); it != listScreeningDay.end(); ++it)
    {
        SuatChieu screening = (*it);
        Movie* movie = movies.search(screening.getIdMovie());
        
        int totalTicket = screening.getSeats().size() * screening.getSeats()[0].size();
        int bookedSeats = screening.countBookedSeats();

        string startTime = screening.getTime();
        int thoiLuong = movie->getThoiLuong();
        int giaTien = movie->getGiaPhim(); 
        int extraTime = 20; 
        string endTime = u.calculateEndTime(startTime, thoiLuong); 

        cout << "| " << setw(16) << left << screening.getIdSuatChieu()
             << "| " << setw(16) << left << movie->getTieuDe()
             << "| " << setw(16) << left << startTime
             << "| " << setw(16) << left << endTime
             << "| " << setw(20) << left << giaTien
             << "| " << setw(20) << left << totalTicket
             << "| " << setw(17) << left << bookedSeats
             << "| " << endl;

        cout << string(136, '-') << endl;
        countBookedSeats += bookedSeats;
        countSeats += totalTicket;
        totalPrice+=bookedSeats*giaTien;
    }

    cout << "\033[33m\nTong cong: " << countSeats << " ve phat hanh" << "\033[0m" << endl;
    cout << "\033[33mSo ve da ban trong ngay: " << countBookedSeats << "\033[0m" << endl << endl;
     cout << "\033[33mDoanh thu trong ngay : " << totalPrice<< "VND"<<"\033[0m" << endl << endl;
}

void ManageSuatChieu::ThongKeTheoThang(int thang , int nam)
{
    set<SuatChieu> listScreeningMonth;
    ManageMovie movies;
    ManageRoom rooms;
    movies.docFile("movieWriteFile.txt");
    rooms.docFile("roomWriteFile.txt");
    for (SuatChieu& screening : danhSachSuatChieu) 
    {
        if (screening.getDate().getThang() == thang &&  screening.getDate().getNam() == nam )
        {
            listScreeningMonth.insert(screening);
        }
    }


    int countBookedSeats = 0;
    int countSeats = 0;
    int totalPrice = 0;    
    
    cout << string(60, '-') << "Thang " << thang<<"/"<<nam << string(60, '-') << endl;

    for ( const SuatChieu& tmp : listScreeningMonth) {
    	SuatChieu screening = tmp;
        Movie* movie = movies.search(screening.getIdMovie());

        if (!movie) {
            cout << "Khong tim thay phim voi ID: " << screening.getIdMovie() << endl;
            continue;
        }

        int totalTicket = screening.getSeats().size() * screening.getSeats()[0].size();
        int bookedSeats = screening.countBookedSeats();
        int giaTien = movie->getGiaPhim();

        countBookedSeats += bookedSeats;
        countSeats += totalTicket;
        totalPrice += giaTien * bookedSeats;
    }
    cout << "\033[33m\nTong cong: " << countSeats << " ve phat hanh" << "\033[0m" << endl;
    cout << "\033[33mSo ve da ban trong thang: " << countBookedSeats << "\033[0m" << endl << endl;
    cout << "\033[33mDoanh thu trong thang: " << totalPrice<<"VND"<< "\033[0m" << endl << endl;
};

void ManageSuatChieu::ThongKeTheoNam(const int& year) {
    set<SuatChieu> listScreeningYear;
    ManageMovie movies;
    ManageRoom rooms;
    movies.docFile("movieWriteFile.txt");
    rooms.docFile("roomWriteFile.txt");

    for ( SuatChieu& screening : danhSachSuatChieu) {
        if (screening.getDate().getNam() == year) {
            listScreeningYear.insert(screening);
        }
    }

    cout << string(30, '-') << " THONG KE NAM: " << year << " " << string(30, '-') << endl;

    int countBookedSeats = 0;
    int countSeats = 0;
    int totalPrice = 0;

    for ( const SuatChieu& tmp : listScreeningYear) {
    	SuatChieu screening = tmp;
        Movie* movie = movies.search(screening.getIdMovie());

        if (!movie) {
            cout << "Khong tim thay phim voi ID: " << screening.getIdMovie() << endl;
            continue;
        }

        int totalTicket = screening.getSeats().size() * screening.getSeats()[0].size();
        int bookedSeats = screening.countBookedSeats();
        int giaTien = movie->getGiaPhim();

        countBookedSeats += bookedSeats;
        countSeats += totalTicket;
        totalPrice += giaTien * bookedSeats;
    }

    cout << "\nTong cong: " << countSeats << " ve phat hanh" << endl;
    cout << "So ve da ban trong nam " << year << ": " << countBookedSeats << endl;
    cout << "Doanh thu trong nam " << year << ": " << totalPrice << " VND" << endl<<endl;
};


void ManageSuatChieu::ThongKe() {
    utility dohoa;

    set<Date> listScreeningDay;
    map<int , int > listScreeningMonth;
    set<int> listScreeningYear;
    
    for (SuatChieu& screening : danhSachSuatChieu) {
        listScreeningDay.insert(screening.getDate());
    }
    
   for (SuatChieu& screening : danhSachSuatChieu) {
	    int month = screening.getDate().getThang();  
	    int year = screening.getDate().getNam();     
	    listScreeningMonth.insert({month ,year});
	}

    for (SuatChieu& screening : danhSachSuatChieu) {
        listScreeningYear.insert(screening.getDate().getNam());
    }

    const string menuItems[] = {
        "NGAY", "THANG ", "NAM", "THOAT"
    };
    const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

    int currentSelection = 0;
    bool running = true;

    while (running) {
        system("cls");
        dohoa.gotoxy(20, 1);
        cout << " ---------------------THONG KE---------------------";
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
                        for (const Date& date : listScreeningDay) {
                        	Date tmp=date;
                            this->ThongKeTheoNgay(tmp);
                        } 
						system("pause");
                        break;
                    case 1: 
                    system("cls");
                    for (auto it = listScreeningMonth.begin(); it != listScreeningMonth.end(); ++it) {
                    	this->ThongKeTheoThang(it->first,it->second);
                       }
                        system("pause");
                        break;
                    case 2:
                    	system("cls");
                        for (const int& year : listScreeningYear) {
                            this->ThongKeTheoNam(year);
                        }
                         system("pause");
                        break;
                    case 3: 
                        running = false;
                        break;
                }
                break;
            case 27: 
                running = false;
                break;
        }
    }
}

void ManageSuatChieu::displayCustomer(const char* filename){
	//doc file du lieu khach hang xong r hien thi
	FILE *f = fopen(filename, "r");
    if (!f) {
        cout << "Error opening file !" << endl;
        return;
    }
    char tmp[200];

    while (fgets(tmp, sizeof(tmp), f) != NULL) {
        string userName, nameUser , idTicket , idScreening;
        int d = 0, m = 0, y = 0;

        char* token = strtok(tmp, ",");
        if (token != NULL) userName = token;
        token = strtok(NULL, ",");
        if (token != NULL) nameUser = token;

        token = strtok(NULL, ",");
        if (token != NULL) idTicket = token;

        token = strtok(NULL, "\n");
        if (token != NULL) idScreening = token;
        
        cout << "| " << left << setw(20) << userName
		         << " | " << left << setw(20) << nameUser
		         << " | " << left << setw(10) << idTicket
		         << " | " << right << setw(19) << idScreening<<"|"<<endl;
		cout<<string(80,'-')<<endl;
		}
		system("pause");
    fclose(f);	
}

void ManageSuatChieu::Option() {
	//doc file du lieu dau vao 
	ManageMovie movies;
	ManageRoom rooms;
	ManageNhanVien staffs;
	movies.docFile("movieWriteFile.txt");
	rooms.docFile("roomWriteFile.txt");
	staffs.docFile("staffWriteFile.txt");
	system("cls");
	utility dohoa;
    int id;
    char filename[20];
    const string menuItems[] = {
        "THEM SUAT CHIEU", "XOA SUAT CHIEU ", "SUA SUAT CHIEU", 
        "HIEN THI CAC SUAT CHIEU ", "TIM KIEM SUAT CHIEU ","SAP XEP SUAT CHIEU ","DOC FILE ","GHI FILE" ,
        "HIEN THI DANH SACH KHACH HANG","THONG KE THEO LICH SU TAI KHOAN","THOAT",
    };
    const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

    int currentSelection = 0;
    bool running = true;

    while (running) {
        system("cls");
        dohoa.gotoxy(20, 1);
        cout << " ---------------------QUAN LI SUAT CHIEU---------------------";
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
                    case 0: { 
                        add();
                        ghiFile("screeningWriteFile.txt");
                        system("pause");
                        system("cls");
                        break;
                    }
                    case 1: { 
                        system("cls");
		                this->remove();
		                ghiFile("screeningWriteFile.txt");
                        system("pause");
                        break;
                    }
                    case 2: { 
                        system("cls");
                       string idSuatChieu;
                       cout << "Nhap ma suat chieu: ";
		                getline(cin,idSuatChieu);
		                fixInformation(idSuatChieu);
		                ghiFile("screeningWriteFile.txt");
                        system("pause");
                        break;
                    }
                    case 3: { 
                        system("cls");
                        display();
                        system("pause");
                        break;
                    }
                    case 4: { 
                        system("cls");
                        string maSuatChieu;
                        cout << "Nhap ma suat chieu: ";
                        cin.ignore();
                        getline(cin,maSuatChieu);
                        SuatChieu* screening = search(maSuatChieu);
                        if (screening==NULL){
                        	cout<<"Khong tim thay suat chieu nay !"<<endl;
                        	return ;
						}
                        DetailScreening(screening->getIdSuatChieu());
                        system("pause");
                        break;
                    }
                    case 5:{
                    	system("cls");
                    	sort();
                    	this->display();
                    	system("pause");
						break;
				}
                     case 6: { 
                        system("cls");
                        char filename[20];
						cout<<"Nhap file doc : ";
						cin>>filename;
                        this->docFile(filename);
                        cout<<"Doc file du lieu "<<filename<<" thanh cong!\n";
                        system("pause");
                        ghiFile("screeningWriteFile.txt");
                        break;
                    }
                     case 7: { 
                        system("cls");
                        char filename[20];
						cout<<"Nhap file ghi : ";
						cin>>filename;
                        ghiFile(filename);
                        break;
                    }
                    case 8 :
                    	{//HIEN THI DANH SACH KHACH HANG
                    	system("cls");
                    	cout<<string(80,'-')<<endl;
                    	cout << "| " << left << setw(20) << "userName"
				         << " | " << left << setw(20) << "nameUser"
				         << " | " << left << setw(10) << "idTicket"
				         << " | " << right << setw(19) << "idScreening"<<"|"<<endl;
				         cout<<string(80,'-')<<endl;
				         this->displayCustomer("bookedScreenings.txt");
				         break;
						};
					case 9:{
						system("cls");	
				        Account accounts;
				        accounts.thongKeTaiKhoan("bookedScreenings.txt");
						break;
					}
					case 10:
                        running = false;
                        break;
                }
                break;
            case 27: // ESC
                running = false;
                break;
        }
    }
};