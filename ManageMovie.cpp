#include "ManageMovie.h"
#include "ManageSuatChieu.h"
using namespace std;
ManageMovie::~ManageMovie() {};

int ManageMovie::getCharAtPos(const string& str, int pos)  {//Lấy ký tự tại một vị trí từ cuối chuỗi (dùng trong sắp xếp).
    if (pos < str.size()) {
        return str[str.size() - pos - 1];  
    }
    return -1; 
}

void ManageMovie::countingSortByChar(int pos) {
    vector<Movie> output(movies.size());
    int count[256] = {0};

    for ( auto& movie : movies) {
        int charAt = getCharAtPos(movie.getIdMovie(), pos);
        count[charAt + 1]++;
    }

    for (int i = 1; i < 256; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = movies.size() - 1; i >= 0; --i) {
        int charAt = getCharAtPos(movies[i].getIdMovie(), pos);
        output[count[charAt + 1] - 1] = movies[i];
        count[charAt + 1]--;
    }
    movies = output;
}

void ManageMovie::sortById() {
    int maxLength = 0;
    for ( auto& movie : movies) {
        maxLength = max(maxLength, (int)movie.getIdMovie().size());
    }

    for (int pos = 0; pos < maxLength; ++pos) {
        countingSortByChar(pos);
    }
}

bool ManageMovie::checkExist(const string& id){
	for (auto it = movies.begin(); it != movies.end(); it++) {
            if ((*it).getIdMovie() == id) return true;
}
    return false;
}

bool ManageMovie::checkFile(const char* fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Loi: khong the mo file nay!" << endl;
        return false;
    }

    set<string> ids, tieudes;
    string line;
    int linenumber = 0;
    bool error = false;
    vector<string> errormessages;

    while (getline(file, line)) {
        linenumber++;
        if (line.empty()) {
            errormessages.push_back("Loi o dong so " + to_string(linenumber) + " - dong trong.");
            error = true;
            continue;
        }

        istringstream check(line);
        string id, tieude, theloai, noidung;
        int thoiluong = 0, giaphim = 0;

        getline(check, id, ',');
        getline(check, tieude, ',');
        getline(check, theloai, ',');
        check >> thoiluong;
        check.ignore();
        check >> giaphim;
        check.ignore();
        getline(check, noidung);

        if (id.empty() || tieude.empty()) {
            errormessages.push_back("Loi o dong so " + to_string(linenumber) + " - tieu de hoac id khong hop le.");
            error = true;
        }
        if (thoiluong <= 0) {
            errormessages.push_back("Loi o dong so " + to_string(linenumber) + " - thoi luong khong hop le.");
            error = true;
        }
        if (giaphim <= 0) {
            errormessages.push_back("Loi o dong so " + to_string(linenumber) + " - gia khong hop le.");
            error = true;
        }
        if (ids.find(id) != ids.end()) {
            errormessages.push_back("Loi o dong so " + to_string(linenumber) + " - id trung lap.");
            error = true;
        }
        tieudes.insert(tieude);
        ids.insert(id);
    }
    if (error) {
        for (const string& err : errormessages) {
            cout << err << endl;
        }
    }
    return !error;
}

void ManageMovie::docFile(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong the mo tep %s \n", filename);
        return;
    }
    if (checkFile(filename)==false ){
    	cout<<"Doc file that bai !"<<endl;
    	return ;
	}
	
	fseek(f, 0, SEEK_END); 
    if (ftell(f) == 0) {  
        printf("Tep %s khong co du lieu.\n", filename);
        fclose(f);
        return;
    }
    rewind(f);

    char tmp[256];
    while (fgets(tmp, sizeof(tmp), f) != NULL) {
        Movie a;

        char* token = strtok(tmp, ",");
        if (token != NULL) {
            a.setIdMovie(token);
        }
        token = strtok(NULL, ",");
        if (token != NULL) {
            a.setTieuDe(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            a.setTheLoai(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            a.setThoiLuong(atoi(token));
        }
        
        token = strtok(NULL, ",");
        if (token != NULL) {
            a.setGiaPhim(atoi(token));
        }
        
        token = strtok(NULL, "\n");
        if (token != NULL) {
            a.setNoiDung(token);
        }
        this->movies.push_back(a);
    }
    if(movies.size()!=0 ) {
	this->sortById();
    Movie::currentId=this->movies.back().getIdMovie();
    }
    fclose(f);
}


void ManageMovie::ghiFile(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        cout << "Error opening file !" << endl;
        return;
    }

    for (auto it = movies.begin(); it != movies.end(); ++it) {
        fprintf(f, "%s,%s,%s,%d,%d,%s\n",
                it->getIdMovie().c_str(),
                it->getTieuDe().c_str(),
                it->getTheLoai().c_str(),
                it->getThoiLuong(),
                it->getGiaPhim(),
                it->getNoiDung().c_str());
    }

    fclose(f);
}

void ManageMovie::add() {
	utility u;
    int dem=5;
    string tieuDe, noiDung, theLoai;
    int thoiLuong,giaPhim;
    string id;
    cout<<"Nhap ID Phim : ";
    do{
    	cin>>id;
    	if(checkExist(id)){
    		cout<<"ID da bi trung !\n";
    		int choiceID;
			cout<<"Nhap 1 neu ban muon ID tu dong ! hoac Nhan bat ki de tiep tuc :\n";
			cout<<"Nhap : ";
			cin>>choiceID;
			if(choiceID==1){
				id=u.generateNewId(Movie::currentId);
				cout<<"ID phim :  "<<id<<endl;
				break;
			}
			else {
				system("cls");
				cout<<"Nhap ID: ";
			}
		}
	}while(checkExist(id));
	
	
    do {
        cout << "Nhap Tieu De ( Toi da 30 ky tu): ";
        cin.ignore();
        getline(cin, tieuDe);
        if (tieuDe.length() > 30) {
            cout << "Tieu de qua dai ! Vui long nhap lai :";
        }
    } while (tieuDe.length() > 30);
    
    do {
        cout << "Nhap The Loai (toi da 30 ky tu): ";
//        cin.ignore();
        getline(cin, theLoai);
        if (theLoai.length() > 30) {
            cout << "The loai qua dai.\n Vui long nhap lai: " << endl;
        }
    } while (theLoai.length() > 30);
    
    do {
        cout << "Nhap Gia Phim: ";
        cin >> giaPhim;
        if (cin.fail() || giaPhim <= 0) {
            cout << "Gia phim phai la mot so nguyen duong!\nVui long nhap lai: " << endl;
            cin.clear();  
            cin.ignore();
        }
    } while (cin.fail() || giaPhim <= 0);
    
    do {
        cout << "Nhap Thoi Luong (phut): ";
        cin >> thoiLuong;
        
        if (cin.fail() || thoiLuong <= 0)  {
            cout << "Thoi luong phai la mot so duong !.\n Vui long nhap lai : " << endl;
            cin.clear();
            cin.ignore();
        }
    } while (cin.fail() || thoiLuong <= 0);
	cin.ignore();
	cout << "Nhap Noi Dung: ";
    getline(cin, noiDung);
    
    Movie movie(id, tieuDe, noiDung, theLoai, thoiLuong,giaPhim);
    movies.push_back(movie);
    cout << "Them phim thanh cong!" << endl;
    }
    
    
void ManageMovie::add(const Movie& movie){
	this->movies.push_back(movie);
	cout<<"Them phong thanh cong !"<<endl;
}

void ManageMovie::remove(const string& id) {
	ManageSuatChieu screenings;
    ManageSuatChieu newScreenings;
    screenings.docFile("screeningWriteFile.txt");

    if (!checkExist(id)) {
    		 cout << "Khong tim thay phim co ID: " << id << endl;
    		 return ;
		}
    
    int choice = -1;
    if (screenings.checkExistIdMovie(id)) {
        cout << "Ban co dong y xoa Suat Chieu cua Phim co ma (" << id << ") khong!" << endl;
        do {
            cout << "0. Khong    1. Co\n";
            cout << "Chon: ";
            cin >> choice;
        } while (choice != 1 && choice != 0);
        
        if (choice == 0) {
            cout << "Ket thuc xoa phong!" << endl;
            return;
        }
        if (choice == 1) {
            for (const SuatChieu& suatChieu:screenings.getScreenings()) {
                if (suatChieu.getIdMovie() != id) {
                    newScreenings.add(suatChieu);
                }
            }
            cout<<"DANH SACH SUAT CHIEU SAU KHI XOA \n";
		    newScreenings.display();
            newScreenings.ghiFile("screeningWriteFile.txt");
            cout << "Da xoa cac suat chieu cua Phim co ma " << id << " thanh cong!" << endl;
        } 
    }

        for (auto it = movies.begin(); it != movies.end(); it++) {
            if ((*it).getIdMovie() == id) {
            	it = movies.erase(it);
            	cout<<"Da xoa phim co ID : "<<id<<" "<<"thanh cong !"<<endl;
                return; 
            }
    }
}
    
Movie* ManageMovie::search(const string& id){
    for (auto& movie : movies) {
        if (movie.getIdMovie() == id) {
            return &movie;  
        }
    }
    return NULL;
}

void ManageMovie::display() {
    utility u;
    int stt = 1;

    if (movies.empty()) {
        cout << "Danh sach phim rong!" << endl << endl;
        return;
    }

    u.printCentered("Danh sach phim:\n", 255, 255, 255, 30);
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

    for (auto& movie : movies) {
        movie.display();
    }
}

void ManageMovie::fixInformation(const string& id) {
	utility u;
        Movie* fixedMovie=search(id);
        if (fixedMovie==NULL){
        	cout<<"Khong tim thay phim co id : "<<id<<endl;
        	return ;
		}
		int choice;
		cout<<string(139,'-')<<endl;
        cout << "| " << left << setw(8) << "ID Phim"
        << " | " << left << setw(20) << "Tieu De"
        << " | " << left << setw(16) << "The Loai"
        << " | " << right << setw(12) << "Thoi Luong"
        << " | " << right << setw(12) << "Gia Phim"
        << " | " << left << setw(50) << "Noi Dung"
        << " |\n";
        cout<<string(139,'-')<<endl;
        fixedMovie->display();
                do {
                    cout << "1. Tieu De" << endl;
                    cout << "2. The Loai" << endl;
                    cout << "3. Thoi Luong" << endl;
                    cout << "4. Noi Dung" << endl;
                    cout << "5. Gia Tien" << endl;
                    cout << "6. Thoat" << endl;
                    cout << "Nhap : ";
                    cin >> choice;
                    cin.ignore(); 
                    switch (choice) {
                    case 1: {
                        string newTieuDe;
                        cout << "Nhap Tieu De moi: ";
                        getline(cin, newTieuDe);
                        fixedMovie->setTieuDe(newTieuDe);
                        system("cls");
                        u.displayHeaderMovie();
                        fixedMovie->display();
                        system("pause");
                        break;
                    }
                    case 2: {
                        string newTheLoai;
                        cout << "Nhap The Loai moi: ";
                        getline(cin, newTheLoai);
                        fixedMovie->setTheLoai(newTheLoai);
                        system("cls");
                        u.displayHeaderMovie();
                        fixedMovie->display();
                        system("pause");
                        break;
                    }
                    case 3: {
                        int newThoiLuong;
                        cout << "Nhap Thoi Luong moi: ";
                        cin>>newThoiLuong;
                        fixedMovie->setThoiLuong(newThoiLuong);
                        system("cls");
                        u.displayHeaderMovie();
                        fixedMovie->display();
                        break;
                    }
                    case 4: {
                        string newNoiDung;
                        cout << "Nhap Noi Dung moi: ";
                        getline(cin, newNoiDung);
                        fixedMovie->setNoiDung(newNoiDung);
                        system("cls");
                        u.displayHeaderMovie();
                        fixedMovie->display();
                        system("pause");
                        break;
                    }
                    case 5:{
                    	int newGiaPhim;
                    	cout << "Nhap Gia Phim moi: ";
                    	cin>>newGiaPhim;
                    	fixedMovie->setGiaPhim(newGiaPhim);
                    	system("cls");
                    	u.displayHeaderMovie();
                        fixedMovie->display();
                    	system("pause");
						break;
					}
                    case 6:
                        cout << "Thoat chinh sua." << endl;
                        break;
                    default:
                    	system("cls");
                        cout << "Lua chon khong hop le. Vui long chon lai ! " << endl;
                    }
                } while (choice != 6);
                cout << "Chinh sua thong tin phim co ID " << fixedMovie->getIdMovie() << " thanh cong" << endl;
                return;       
}

void ManageMovie::Option() {
	movies.clear();
	this->docFile("movieWriteFile.txt");
	utility u ;
	utility dohoa;
    string id;
    char filename[20];
    const string menuItems[] = {
        "THEM PHIM", "XOA PHIM", "SUA PHIM", "XEM DANH SACH PHIM", 
        "TIM KIEM PHIM","SAP XEP THEO ID", "DOC FILE ","GHI FILE" , "THOAT"
    };
    const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

    int currentSelection = 0;
    bool running = true;

    while (running) {
        system("cls");
        dohoa.gotoxy(20, 1);
        cout << " ---------------------QUAN LI MOVIE ---------------------";
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
                        ManageMovie::add();
                        this->ghiFile("movieWriteFile.txt");
                        system("pause");
                        break;
                    case 1: 
                        system("cls");
                        cout << "Nhap ma phim can xoa: ";
                        getline(cin,id);
                        ManageMovie::remove(id);
                        this->ghiFile("movieWriteFile.txt");
						system("pause");
                        break;
                    case 2: 
                        system("cls");
                        cout << "Nhap ma phim can chinh sua: ";
                        cin >> id;
                        ManageMovie::fixInformation(id);
                        this->ghiFile("movieWriteFile.txt");
                        system("pause");
                        break;
                    case 3: 
                        system("cls");
                        ManageMovie::display();
                        system("pause");
                        break;
                    case 4: {
                    	 string id;
                    	 system("cls");
                        cout << "Nhap ma phim can tim kiem: ";
                        getline(cin,id);
                        Movie* movie = ManageMovie::search(id);
                        if (movie == NULL) {
                            cout << "Khong tim thay phim." << endl;
                        } else {
                        	u.displayHeaderMovie();
                            movie->display();
                        }
                        system("pause");
						break;
					}
					 case 5:{
		            	this->sortById();
		            	this->display();
		            	system("pause");
						break;
					}
                    case 6: {
					  system("cls");
					  char filename[20];
						cout<<"Nhap file doc : ";
						cin>>filename;
                        ManageMovie::docFile(filename);
                        this->ghiFile("movieWriteFile.txt");
                        system("pause");
                        break;
					}
					case 7: {
						system("cls");
						char filename[20];
						cout<<"Nhap file ghi : ";
						cin>>filename;
                        ManageMovie::ghiFile(filename);
                        this->display();
                        system("pause");
						break;
					}
                    case 8: 
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

































