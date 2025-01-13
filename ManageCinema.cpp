#include "ManageCinema.h"
using namespace std;
void CinemaManagement::menu() {
	utility dohoa;
    int id;
    char filename[20];
    const string menuItems[] = {
        "QUAN LY PHONG CHIEU ", "QUAN LY PHIM ", "QUAN LY SUAT PHIM ", 
        "QUAN LY NHAN VIEN ","THONG KE","THOAT"
    };
    const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

    int currentSelection = 0;
    bool running = true;

    while (running) {
        system("cls");
        dohoa.gotoxy(20, 1);
        cout << " ---------------------QUAN LY RAP CHIEU PHIM ---------------------";
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
                        system("cls");
                        ManageRoom manageRoom;
                        manageRoom.Option();  
                        system("pause");
                        break;
                    }
                    case 1: { 
                        system("cls");
						ManageMovie manageMovie;
                        manageMovie.Option();
                        system("pause");
                        break;
                    }
                    case 2: { 
                        system("cls");
		                ManageSuatChieu manageScreening;
                        manageScreening.Option();
                        system("pause");
                        break;
                    }
                    case 3: {
                        system("cls");
		                ManageNhanVien manageStaff;
                        manageStaff.Option(); 
                        system("pause");
                        break;
                    }
                    case 4:{
                    	system("cls");
                    	ManageSuatChieu manageScreenings;
                    	manageScreenings.docFile("screeningWriteFile.txt");
                    	manageScreenings.ThongKe();
                    	system("pause");
						break;
					}
                    case 5:
                        running = false;
                        system("cls");
                        break;
                }
                break;
            case 27: 
                running = false;
                break;
        }
    }
};