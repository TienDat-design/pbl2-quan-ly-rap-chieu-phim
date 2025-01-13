#include "ManageRoom.h"
#include "utility.h"
using namespace std;

ManageRoom::~ManageRoom() {
}

int ManageRoom::getCharAtPos(const string& str, int pos)  {
    if (pos < str.size()) {
        return str[str.size() - pos - 1];  
    }
    return -1; 
}

void ManageRoom::countingSortByChar(int pos) {
    vector<Room> output(rooms.size());
    int count[256] = {0};

    for ( auto& room : rooms) {
        int charAt = getCharAtPos(room.getIdRoom(), pos);
        count[charAt + 1]++;
    }

    for (int i = 1; i < 256; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = rooms.size() - 1; i >= 0; --i) {
        int charAt = getCharAtPos(rooms[i].getIdRoom(), pos);
        output[count[charAt + 1] - 1] = rooms[i];
        count[charAt + 1]--;
    }
    rooms = output;
}

void ManageRoom::sortById() {
    int maxLength = 0;
    for ( auto& room : rooms) {
        maxLength = max(maxLength, (int)room.getIdRoom().size());
    }

    for (int pos = 0; pos < maxLength; ++pos) {
        countingSortByChar(pos);
    }
}

vector<Room> ManageRoom::getRooms(){
	return this->rooms;
};

bool ManageRoom::checkExist(const string& id){
	 for (Room& room : rooms) {
        if (room.getIdRoom() == id) return true;
		}
      return false;
};

void ManageRoom::ghiFile(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        cout << "Error opening file!" << endl;
        return;
    }

    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        fprintf(f, "%s,%s,%d,%d\n", 
                it->getIdRoom().c_str(),
                it->getNameRoom().c_str(),
                it->getNumRows(),
                it->getNumCols());
    }
    fclose(f);
}


bool ManageRoom::checkFile(const char* fileName)
{
      FILE* f = fopen(fileName, "r");
        if (f == NULL) {
            printf("Khong the mo tep %s \n", fileName);
            return false ;
        }
 
    vector<string> errorMessages;
    set<string> idRooms;
    bool hasError=false;
    int stt = 1;
    char tmp[500];
    string idRoom, nameRoom;
	int numRows,numCols;
    while (fgets(tmp, sizeof(tmp), f) != NULL) {
        Room a;
        char* token = strtok(tmp, ",");
        if (token != NULL) idRoom=token;
        
        token = strtok(NULL, ",");
        if (token != NULL) nameRoom=token;

        token = strtok(NULL, ",");
        if (token != NULL) numRows= atoi(token);
        
        token = strtok(NULL, "\n");
        if (token != NULL) numCols= atoi(token);
        
       
        if(idRooms.find(idRoom) != idRooms.end() )
        {
        	errorMessages.push_back("Loi o dong "+to_string(stt++)+" - id phong bi trung.");
            hasError = true;
            continue;
		}
        if (idRoom.empty() || nameRoom.empty())
        {
            errorMessages.push_back("Loi o dong "+to_string(stt++)+" - thieu id phong hoac ten phong.");
            hasError = true;
            continue;
        }
        if (numRows <= 0 || numCols <= 0)
        {
            errorMessages.push_back("Loi o dong "+to_string(stt++)+" - so hang hoac so cot khong hop le.");
            hasError = true;
            continue;
        }     
        
        idRooms.insert(idRoom);
    }
 
    for (const auto& errorMessage : errorMessages)
    {
        cout << errorMessage << endl;
    }

    return !hasError;
}

void ManageRoom::docFile(const char* filename) {
        FILE* f = fopen(filename, "r");
        if (f == NULL) {
            printf("Khong the mo tep %s \n", filename);
            return;
        }
        if(!checkFile(filename)){
        	return ;
		}
        char tmp[500];
        while (fgets(tmp, sizeof(tmp), f) != NULL) {
            Room a;
            char* token = strtok(tmp, ",");
            if (token != NULL) a.setIdRoom(token);
            
            token = strtok(NULL, ",");
            if (token != NULL) a.setNameRoom(token);

            token = strtok(NULL, ",");
            if (token != NULL) a.setNumRows(atoi(token));

            token = strtok(NULL, "\n");
            if (token != NULL) a.setNumCols(atoi(token));
            rooms.push_back(a);
        }
        this->sortById();
        Room::currentID=this->rooms.back().getIdRoom();
        fclose(f);
    };

void ManageRoom::add() {
	utility u ;
	int dem=5;
    string tenPhong,idPhong;
	int row, col;	
	
	cout << "Nhap ID Phong: ";
	do{
	cin>>idPhong;
    if (checkExist(idPhong)){
    	cout<<"Da ton tai phong co ID :"<<idPhong<<" .\n";
    	int choiceID;
			cout<<"Nhap 1 neu ban muon ID tu dong ! hoac Nhan bat ki de tiep tuc :\n";
			cout<<"Nhap : ";
			cin>>choiceID;
			if(choiceID==1){
				idPhong=u.generateNewId(Room::currentID);
				cout<<"ID Phong :  "<<idPhong<<endl;
				break;
			}
			else {
				system("cls");
				cout<<"Nhap ID: ";
			}
		}
	}while(checkExist(idPhong));
    cout << "Nhap Ten Phong: ";
    cin.ignore();
	getline(cin,tenPhong);

	do {
        cout << "So Hang: ";
        cin >> row;
        cout << "So Cot: ";
        cin >> col;
        if (row <= 0 || col <= 0) {
            cout << "Khong hop le. Vui long nhap lai so hang va so cot!" << endl;
        }
    } while (row <= 0 || col <= 0);
     
    Room newRoom(idPhong,tenPhong, row ,col); 
    rooms.push_back(newRoom); 
    cout << "Phong da duoc them thanh cong!" << endl;
}

void ManageRoom::add(const Room& room){
	this->rooms.push_back(room);
	cout<<"Them phong thanh cong !"<<endl;
}

void ManageRoom::remove(const string& idPhong) {
    ManageSuatChieu screenings;
    ManageSuatChieu newScreenings;
    screenings.docFile("screeningWriteFile.txt");
    
    if (!this->checkExist(idPhong)) {
        cout << "Khong tim thay phong co id : " << idPhong << endl;
        return;
    }
    int choice = -1;
    if (screenings.checkExistIdRoom(idPhong)) {
        cout << "Ban co dong y xoa Suat Chieu cua phong co id (" << idPhong << ") khong!" << endl;
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
            for (const auto& screening : screenings.getScreenings()) {
               if (screening.getIdRoom() != idPhong) {
                     newScreenings.add(screening); 
                 }
             }
            newScreenings.display();
            newScreenings.ghiFile("screeningWriteFile.txt");
            cout << "Da xoa cac suat chieu cua phong co ten " << idPhong << " thanh cong!" << endl;
        } 
    }

    auto it = rooms.begin();
    while (it != rooms.end()) {
        if (it->getIdRoom() == idPhong) {
            it = rooms.erase(it); 
            cout << "Phong co id " << idPhong << " da duoc xoa!" << endl;
            break;
        } else {
            ++it;
        }
    }
}

void ManageRoom::fixInformation(const string& tenPhong) {
    Room* fixedRoom = Search(tenPhong);
    if (fixedRoom == NULL) {
        cout << "Khong tim thay phong : " << tenPhong << endl;
        return;
    }

    int choice;
    cout << "Chinh sua thong tin phong  : " << endl;
    const string fixItems[] = { "1 |ID Phong","2 |Ten Phong" ,"3 | So Hang", "4 | So cot", "0 | THOAT ." };
    const int fixSize = sizeof(fixItems) / sizeof(fixItems[0]);
    for (int i = 0; i < fixSize; i++) {
        cout << fixItems[i] << endl;
    }
    cout << "Lua chon :  ";
    cin >> choice;
    switch (choice) {
        case 1: {
        	string idPhong;
        	int dem=3;
            cout << "Nhap ID Phong: ";
		    do{
		    cin.ignore();
			getline(cin,idPhong);
		    if (checkExist(idPhong)){
		    	cout<<"Da ton tai phong co ID :"<<idPhong<<" ."<<"\nNhap lai :";
		    	dem--;
			}
			if (dem=0){
				return ;
			}
			}while(checkExist(idPhong));
            fixedRoom->setIdRoom(idPhong);
            system("cls");
            cout << "Chinh sua phong thanh cong !" << endl;
            fixedRoom->display();
            break;
        }
        case 2:{
        	string tenPhong;
			cout<<"Nhap ten phong : ";
        	getline(cin,tenPhong);
        	fixedRoom->setNameRoom(tenPhong);
        	system("cls");
            cout << "Chinh sua phong thanh cong !" << endl;
            fixedRoom->display();
			break;
		}
        case 3: {
            int newRow;
            int dem = 0;
            cout << "Nhap so hang : ";
            do {
                cin >> newRow;
                if (newRow <= 0) {
                    cout << "So hang khong hop le ! Nhap lai :" << endl;
                    dem++;
                }
                if (dem == 5) {
                    return;
                }
            } while (newRow <= 0);
            fixedRoom->setNumRows(newRow);
            system("cls");
            cout << "Chinh sua phong thanh cong !" << endl;
            fixedRoom->display();
            break;
        }
        case 4: {
            int newCol;
            int dem = 0;
            cout << "Nhap so cot : ";
            do {
                cin >> newCol;
                if (newCol <= 0) {
                    cout << "So cot khong hop le ! Nhap lai :" << endl;
                    dem++;
                }
                if (dem == 5) {
                    return;
                }
            } while (newCol <= 0);
            fixedRoom->setNumCols(newCol);
            system("cls");
            cout << "Chinh sua phong thanh cong !" << endl;
            fixedRoom->display();
            break;
        }
        case 0: {
            cout << "Ket thuc CHINH SUA !" << endl;
            break;
        }
        default: {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            break;
        }
    }
    cout << "Thong tin phong da duoc cap nhat!" << endl;
}
                        
Room* ManageRoom::Search(const string& MaPhong) {
    for ( auto& room : rooms) {
        if (room.getIdRoom() == MaPhong) { 
            return &room;
        }
    }
    return NULL;
}

void ManageRoom::Search(){
	cout<<"1 | Tim kien theo ID"<<endl;
	cout<<"2 | Tim kiem theo Ten phong"<<endl;
	int choice ;
	cout<<"Nhap :";
	do{
		cin>>choice;
		if (choice!=1&&choice!=2){
			cout<<"Lua chon khong hop le "<<endl;
			cout<<"Nhap lai : ";
		}
	}
		while(choice!=1&&choice!=2);
	switch(choice){
		case 1:{
			string id;
			cout<<"Nhap ID phong :";
			cin>>id;
			Room* room = Search(id);
			if (room==NULL){
				cout<<"Khong tim thay phong co ID : "<<id<<endl;
				return;
			}
			else {
				room->display();
			}
			break;
		}
		case 2:{
			string nameRoom;
			int found=0;
			cout<<"Nhap ten phong : ";
			cin.ignore();  
            getline(cin, nameRoom);
			for (auto it=rooms.begin();it!=rooms.end(); it++){
				if (it->getNameRoom()==nameRoom){
					found=1;
					Room* room = &(*it);
					room->display();
					cout<<endl;
				}
			}
			if (found==0) cout<<"Khong tim thay phong co ten "<<nameRoom<<endl;
			break;
		}
		default:
			cout<<"Lua chon khong hop le !\n";
	}
};

void ManageRoom::display(){
	if (rooms.size()==0) {
		cout<<"Danh sach phong rong !"<<endl;
		return ;
	}
	utility u;
	u.printCentered("THONG TIN PHONG",255,215,0,30);
    for ( auto it=rooms.begin();it!=rooms.end();it++) {
        it->display();
	 }
}
	
void ManageRoom::Option() {
	rooms.clear();
	this->docFile("roomWriteFile.txt");
	utility dohoa;
    string id;
    char filename[20];
    const string menuItems[] = {
        "THEM PHONG", "XOA PHONG","CHINH SUA " ,"XEM CHI TIET PHONG", 
         "HIEN THI TAT CA PHONG","SAP XEP PHONG THEO ID","DOC FILE ", "GHI FILE", "THOAT"
    };
    const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);
    int currentSelection = 0;
    bool running = true;

    while (running) {
        system("cls");
        dohoa.gotoxy(20, 1);
        dohoa.printCentered(" ---------------------QUAN LI ROOM ---------------------",255,255,255,30);
        dohoa.gotoxy(20, 2);
        dohoa.printCentered("HUONG DAN",255,255,255,0);
        dohoa.gotoxy(20, 3);
        dohoa.printCentered("Su dung 4 phim mui ten de di chuyen",255,255,255,0);
        dohoa.gotoxy(20, 4);
       dohoa.printCentered("ESC: Thoat      Enter: Chon",255,255,255,0);

        dohoa.gotoxy(5, 6);
         dohoa.printCentered("---------MENU---------",255,255,255,0);
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
                        system("cls");
                        ManageRoom::add();
                        this->ghiFile("roomWriteFile.txt");
                        system("pause");
                        break;
                    }
                    case 1: { 
                        system("cls");
                        cout << "Nhap ma phong can xoa: ";
                        cin>>id;
                        ManageRoom::remove(id);
                        this->ghiFile("roomWriteFile.txt");
                        system("pause");
                        break;
                    }
                    case 2:{
                    	system("cls");
                        cout << "Nhap ma phong can chinh sua : ";
                        cin >> id;
                        ManageRoom::fixInformation(id);
                        this->ghiFile("roomWriteFile.txt");
                        system("pause");
						break;
					}
                    case 3: { 
                        system("cls");
                        this->Search();
                        system("pause");
                        break;
                    }
                    case 4: { 
                        system("cls");
                        ManageRoom::display();
                        system("pause");
                        break;
                    }
                     case 5:{
		            	this->sortById();
		            	this->display();
		            	system("pause");
						break;
					}
                    case 6:{
                    	system("cls");
                    	char filename[20];
                    	cout<<"Nhap file doc : ";
                    	cin>>filename;
                        ManageRoom::docFile(filename);
                        this->ghiFile("roomWriteFile.txt");
                        cout<<"Doc file du lieu phong thanh cong !"<<endl;
                        system("pause");
						break;
					}
					case 7:{
						system("cls");
						char filename[20];
                    	cout<<"Nhap file ghi : ";
                    	cin>>filename;
                        ManageRoom::ghiFile(filename);
                        system("pause");
						break;
					}
                    case 8: 
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
