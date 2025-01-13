#include "ManageNhanVien.h"
using namespace std;

int ManageNhanVien::getCharAtPos(const string& str, int pos)  {
    if (pos < str.size()) {
        return str[str.size() - pos - 1];  
    }
    return -1; 
}


void ManageNhanVien::countingSortByChar(int pos) {
    vector<NhanVien> output(staffs.size());
    int count[256] = {0};

    for ( auto& nv : staffs) {
        int charAt = getCharAtPos(nv.getID(), pos);
        count[charAt + 1]++;
    }

    for (int i = 1; i < 256; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = staffs.size() - 1; i >= 0; --i) {
        int charAt = getCharAtPos(staffs[i].getID(), pos);
        output[count[charAt + 1] - 1] = staffs[i];
        count[charAt + 1]--;
    }
    staffs = output;
}

void ManageNhanVien::sortById() {
    int maxLength = 0;
    for ( auto& nv : staffs) {
        maxLength = max(maxLength, (int)nv.getID().size());
    }

    for (int pos = 0; pos < maxLength; ++pos) {
        countingSortByChar(pos);
    }
}


void ManageNhanVien::add() {
	    utility u;
        string ID;
        string HoTen;
        string GioiTinh;
        string SDT;
        Date ngaySinh;
        int choice;
        do {
            cout << "Nhap ID: ";
            cin >> ID;
            if (ID.empty()) {
                cout << "ID khong duoc de trong!\n";
            } else if (checkExist(ID)) {
                cout << "ID da ton tai. Vui long nhap lai.\n";
	            int choiceID;
				cout<<"Nhap 1 neu ban muon ID tu dong ! hoac Nhan bat ki de tiep tuc :\n";
				cout<<"Nhap : ";
				cin>>choiceID;
				if(choiceID==1){
					ID=u.generateNewId(NhanVien::currentId);
					cout<<"ID Nhan Vien :  "<<ID<<endl;
					break;
				}
				else {
					system("cls");
					cout<<"Nhap ID: ";
				}
			}
        } while (ID.empty() || checkExist(ID));

        cin.ignore();
        do {
            cout << "Nhap Ho va Ten: ";
            getline(cin, HoTen);
            if (HoTen.empty()) {
                cout << "Ho va Ten khong duoc de trong!\n";
            }
        } while (HoTen.empty());

        do {
            cout << "Nhap Gioi Tinh (0. Nam / 1. Nu): ";
            cin >> choice;
            if (choice != 0 && choice != 1) {
                cout << "Lua chon khong hop le!\n";
            }
        } while (choice != 0 && choice != 1);
        GioiTinh = (choice == 0) ? "Nam" : "Nu";

        do {
            cout << "Nhap So dien thoai: ";
            cin >> SDT;
            if (!Person::checkNumber(SDT)) {
                cout << "So dien thoai khong hop le. Vui long nhap lai (10 so).\n";
            }
        } while (!Person::checkNumber(SDT));

        cout << "Nhap ngay sinh: \n";
        cin >> ngaySinh;
        NhanVien nv(ID, HoTen, GioiTinh,SDT,ngaySinh);
        this->staffs.push_back(nv);
        cout << "Da them nhan vien moi vao danh sach." << endl;
    }


void ManageNhanVien::remove(const string& idNhanVien) {
    for ( auto it = staffs.begin(); it != staffs.end(); ++it) {
        if (it->getID()==idNhanVien) {
            staffs.erase(it);
            cout << "Da xoa nhan vien co ID: " << idNhanVien << endl;
            return;
        }
    }
    cout << "Khong tim thay nhan vien co ID: " << idNhanVien << endl;
}

bool ManageNhanVien::checkExist(const string& id){
	for (auto& nv:staffs){
		if (nv.getID()==id){
			return true;
		}
	}
	return false;
}


void  ManageNhanVien::fixInformation(const string& idNhanVien) {
	utility u;
	NhanVien* fixedStaff=Search(idNhanVien);
	if (fixedStaff==NULL){
		 cout << "Khong tim thay nhan vien co ID: " << idNhanVien << endl;
         return ;
     }
     int selection;
     u.displayHeaderStaff();
     fixedStaff->display();
    do {
                    cout << "1. ID Nhan vien " << endl;
                    cout << "2. Ten" << endl;
                    cout << "3. Gioi tinh" << endl;
                    cout << "4. SDT" << endl;
                    cout << "5. Ngay sinh" << endl;
                    cout << "6. Thoat" << endl;
                    cout << "Nhap : ";
                    cin >> selection;
                    cin.ignore(); 
                    switch (selection) {
                    case 1: {
                    	system("cls");
                        string newID;
                        cout << "Nhap ID moi : ";
                        do{
							getline(cin, newID);
	                        if (checkExist(newID)){
	                        	cout<<"ID da bi trung !\nNhap lai: ";
						}
	                    }while(checkExist(newID));
	                    fixedStaff->setID(newID);
                        
                        u.displayHeaderStaff();
                        fixedStaff->display();
                        system("pause");
                        break;
                    }
                    case 2: {
                    	system("cls");
                        string newTen;
                        cout << "Nhap Ten: ";
                        getline(cin, newTen);
                        fixedStaff->setName(newTen);
                        u.displayHeaderStaff();
                        fixedStaff->display();
                        system("pause");
                        break;
                    }
                    case 3: {
                    	system("cls");
                        int choice;
                        cout << "Gioi tinh: ";
                        cout << "Nhap Gioi Tinh (0. Nam/1. Nu): ";
					    do{
					    	cout<<"Nhap : ";
					    	cin>>choice;
					    	if(choice!=0&&choice!=1){
					    		cout<<"Lua chon khong hop le !\n";	
							}
						}
						while(choice!=0&&choice!=1);
						if (choice==0){ fixedStaff->setGender("Nam");
						}
						else {
							 fixedStaff->setGender("Nu");
						}
                        u.displayHeaderStaff();
                        fixedStaff->display();
                        system("pause");
                        break;
                    }
                    case 4: {
                    	system("cls");
                    	string newSDT;
                        do{
				        cout << "Nhap so dien thoai moi (10 chu so): ";
				        getline(cin, newSDT);
				        if (!newSDT.empty()) {
				            if (regex_match(newSDT, regex("^\\d{10}$"))) {
				                 fixedStaff->setPhoneNumber(newSDT);
				            } else {
				               cout << "So dien thoai phai bao gom 10 chu so.\n";
				             }
					        }
					    }while(!regex_match(newSDT, regex("^\\d{10}$")));
					    fixedStaff->setPhoneNumber(newSDT);
                        u.displayHeaderStaff();
                        fixedStaff->display();
                        system("pause");
                        break;
                    }
                    case 5:{
                    	system("cls");
                    	Date newDate;
				        cout << "Nhap ngay sinh moi: ";
				        cin>>newDate;
				        fixedStaff->setNgaySinh(newDate);
                    	u.displayHeaderStaff();
                        fixedStaff->display();
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
                } while (selection != 6);
                cout << "Chinh sua thong tin Nhan Vien co ID " << fixedStaff->getID() << " thanh cong" << endl;
    }


NhanVien* ManageNhanVien::Search(const string& idNhanVien) {
	NhanVien* nv;
    for (auto &nv : staffs) {
        if (nv.getID() == idNhanVien) {
            return &nv;  
        }
    }  
	return NULL;
}

void ManageNhanVien::display()  {
	utility u ;
	cout<<"Danh sach nhan vien \n";
	u.displayHeaderStaff();
    for ( auto nv : staffs) {
        nv.display();  
    }
}





bool ManageNhanVien::checkFile(const char* fileName)
{
    ifstream file(fileName);
    if(!file.is_open())
    {
        cout <<"Loi: khong the mo duoc file nay!"<<endl;
        return false;
    }
    set<string>ids;
    set<string>phonenumbers;
    string line;
    int linenumber;
    bool error = false;
    vector<string> errormessages;
    while(getline(file,line))
    {
        istringstream check(line);
        string id,hoten,gioitinh,sdt;
        Date ngaysinh;
        int d,m,y;

        getline(check,id,',');
        getline(check,hoten,',');
        getline(check,gioitinh,',');
        getline(check,sdt,',');
        check>>d;
        check.ignore(1,'/');
        check>>m;
        check.ignore(1,'/');
        check>>y;
        check.ignore('\n');

        if(id.empty() || hoten.empty())
        {
            errormessages.push_back("Loi o dong so: "+ to_string(linenumber) +" - id hoac ho ten khong hop le.");
            error = true;
        }
        if(ids.find(id) != ids.end())
        {
            errormessages.push_back("Loi o dong so: "+ to_string(linenumber) +" - id bi trung lap.");
            error = true;
        }
        if(sdt.length() != 10 || !all_of(sdt.begin(), sdt.end(), ::isdigit))
        {
            errormessages.push_back("Loi o dong so: "+ to_string(linenumber) + " - so dien thoai khong hop le.");
            error = true;
        }
        if(phonenumbers.find(sdt) != phonenumbers.end())
        {
           errormessages.push_back("Loi o dong so: "+ to_string(linenumber) + " - so dien thoai trung lap.");
           error = true;
        }

        if(ngaysinh.validation(d,m,y) == false)
        {
            errormessages.push_back("Loi o dong " + to_string(linenumber)+ " - ngay sinh ko hop le.");
            error = true;
        }

        ids.insert(id);
        phonenumbers.insert(sdt);
        linenumber++;
    }

    for(const auto& errormessage : errormessages)
    {
        cout << errormessage <<endl;
    }

    return !error;
}
void ManageNhanVien::docFile(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong the mo tep %s \n", filename);
        fclose(f);
        return;
    }
    if(!checkFile(filename)){
    	cout<<"File co loi du lieu"<<endl;
    	return ;
	}
    char tmp[200];
    int y , m , d;
    while (fgets(tmp, sizeof(tmp), f) != NULL) {
    	NhanVien a ; 
        char* token = strtok(tmp, ",");
        if (token != NULL) a.setID(token);
        
        token = strtok(NULL, ",");
        if (token != NULL) a.setName(token);
        
        token = strtok(NULL, ",");
        if (token != NULL) a.setGender(token);
        
        token = strtok(NULL, ",");
        if (token != NULL) a.setPhoneNumber(token);
        
        //Date
        token = strtok(NULL, "/");
        if (token != NULL) d = atoi(token);
        
        token = strtok(NULL, "/");
        if (token != NULL) m = atoi(token);
        
        token = strtok(NULL, "\n"); 
        if (token != NULL) y = atoi(token);
        
        Date tmp(d,m,y);
        a.setNgaySinh(tmp);
        this->staffs.push_back(a);
    }
    this->sortById();
    NhanVien::currentId=this->staffs.back().getID();
    fclose(f);
}

void ManageNhanVien::ghiFile(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        cout << "Error opening file!" << endl;
        fclose(f);
        return;
    }
    for (auto it = staffs.begin(); it != staffs.end(); ++it) {
        fprintf(f, "%s,%s,%s,%s,%d/%d/%d\n",
                it->getID().c_str(),
                it->getName().c_str(),
                it->getGender().c_str(),
                it->getPhoneNumber().c_str(),
                it->getNgaySinh().getNgay(),
                it->getNgaySinh().getThang(),
                it->getNgaySinh().getNam()
				);
    }
	    fclose(f);
}


void ManageNhanVien::Option() {
	staffs.clear();
	this->docFile("staffWriteFile.txt");
	utility dohoa;
    int id;
    char filename[20];
    const string menuItems[] = {
        "THEM NHAN VIEN ", "XOA NHAN VIEN ","CHINH SUA THONG TIN NHAN VIEN  ", 
        "HIEN THI NHAN VIEN ", "TIM KIEM NHAN VIEN ","SAP XEP THEO ID ", "DOC FILE ","GHI FILE","THOAT"
    };
    const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

    int currentSelection = 0;
    bool running = true;

    while (running) {
        system("cls");
        dohoa.gotoxy(20, 1);
        dohoa.printCentered(" ---------------------QUAN LY NHAN VIEN  ---------------------",255,255,255,20);
        dohoa.gotoxy(20, 2);
        dohoa.printCentered( "HUONG DAN",255,255,255,20);
        dohoa.gotoxy(20, 3);
        dohoa.printCentered("Su dung 4 phim mui ten de di chuyen",255,255,255,20);
        dohoa.gotoxy(20, 4);
        dohoa.printCentered("ESC: Thoat      Enter: Chon",255,255,255,20);

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
                        system("cls");
                        this->add();
                        this->ghiFile("staffWriteFile.txt");
                        cin.ignore();
                        system("pause");
                        break;
                    }
                    case 1: { 
                        system("cls");
                        string id;
                        cout << "Nhap ID nhan vien can xoa: ";
                        getline(cin,id);
                        this-> remove(id);
                         this->ghiFile("staffWriteFile.txt");
                        system("pause");
                        break;
                    }
                    case 2: { 
                        system("cls");
		                cout << "Nhap ID nhan vien can sua: ";
		                string id;
		                getline(cin,id);
		                this->fixInformation(id);
		                this->ghiFile("staffWriteFile.txt");
                        system("pause");
                        break;
                    }
                    case 3: { 
                        system("cls");
                        this->display();
                        system("pause");
                        break;
                    }
                    case 4: { 
                        system("cls");
                         string id;
		                cout << "Nhap ID nhan vien can tim: ";
		                getline(cin,id);
		                NhanVien* nv = Search(id);
		                if (nv != nullptr) {
		                	dohoa.displayHeaderStaff();
		                    nv->display();
		                } else {
		                    cout << "Khong tim thay nhan vien co ID: " << id << endl;
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
	                case 6:{
		                system("cls");
					    char filename[20];
						cout<<"Nhap file doc : ";
						cin>>filename;
                        this->docFile(filename);
                        this->ghiFile("staffWriteFile.txt");
                        system("pause");
						break;
						}
	                case 7:{
	                	system("cls");
					    char filename[20];
						cout<<"Nhap file ghi : ";
						cin>>filename;
                        this->docFile(filename);
                        this->ghiFile("staffWriteFile.txt");
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
}