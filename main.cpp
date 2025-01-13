#include "LogIn.h"
#include "ManageCinema.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <string>
#include "utility.h"
#include <conio.h>
#include <limits>
using namespace std;
void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main()
{
    LogIn loginSystem;
    string userName;
    string password;
    loginSystem.docFile("accounts.txt");
    utility dohoa;
    int id;
    char filename[20];
    const string menuItems[] = {
        "DANG NHAP ", "DANG KY ","CHINH SUA THONG TIN ","THOAT"
    };
    const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

    int currentSelection = 0;
    bool running = true;

    while (running) 
    {
        system("cls");
 	
        dohoa.gotoxy(20, 1);
        SetColor(6);
        dohoa.printCentered(" ---------------------TRANG CHU ---------------------",255,255,255,20);
        SetColor(6);
        dohoa.gotoxy(20, 2);
        dohoa.printCentered( "HUONG DAN",255,255,255,20);
        dohoa.gotoxy(20, 3);
        dohoa.printCentered("Su dung 4 phim mui ten de di chuyen",255,255,255,20);
        dohoa.gotoxy(20, 4);
        dohoa.printCentered("ESC: Thoat      Enter: Chon",255,255,255,20);

        dohoa.gotoxy(5, 6);
        cout << "MENU";
        for (int i = 0; i < menuSize; i++) 
        {
            dohoa.gotoxy(5, 8 + i);
            if (i == currentSelection) 
            {
                cout << "> " << menuItems[i]; 
            } 
            else 
            {
                cout << "  " << menuItems[i];
            }
        }

        switch (_getch()) 
        {
                case 0:
                case 224: 
                    switch (_getch()) 
                    {
                        case 72:
                            currentSelection = (currentSelection > 0) ? currentSelection - 1 : menuSize - 1;
                            break;
                        case 80: 
                            currentSelection = (currentSelection + 1) % menuSize;
                            break;
                    }
                    break;
                case 13: 
                    switch (currentSelection) 
                    {
                            case 0: 
                            { 
                                system("cls");
                                cout << "Nhap ten dang nhap: ";
                                cin>>userName;
                                if(loginSystem.checkExist(userName) == true)
                                {
                                    loginSystem.logInAccount(userName);
                                }
                                else 
                                {
                                    int option;
                                    cout << "Ten dang nhap nay khong ton tai.\n";
                                    cout << "Ban co muon dang ky tai khoan nay khong\n";
                                    cout << "Co (1) hoac khong (0): ";
                                    cin >> option;
                                    switch(option)
                                    {
                                        case 1:
                                            loginSystem.add(userName);
                                            loginSystem.ghiFile("accounts.txt");  
                                            break;
                                        case 0:
                                            break;
                                        default:
                                            cout << "Lua chon khong hop le. Vui long chon lai!";
                                            break;
                                    }
                                }
                                    break;
                            }
                        
                        case 1: 
                            { 
                                system("cls");
                                cout << "Bat dau them tai khoan." << endl;
                                loginSystem.add();      
                                loginSystem.ghiFile("accounts.txt");  
                                cout << "Tai khoan da duoc them thanh cong!";
                                system("pause");
                                system("cls") ;   
                                break;
                            }
                        case 2: 
                            { 
                                cout << "Nhap ten dang nhap cua tai khoan can sua: ";
                                cin.ignore();
                                getline(cin, userName);
                                loginSystem.fixInformation(userName);
                                loginSystem.ghiFile("accounts.txt"); 
                                system("pause");
                                system("cls") ;   
                                break;
                            }
                        case 3:
                            { 
                                system("cls");
                                cout << "Thoat chuong trinh." << endl;
                                return 0;
                                break;
                            }


                    case 27: // ESC
                    running = false;
                    break;
                }
        }
    }
}