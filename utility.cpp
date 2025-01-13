#include "utility.h"
using namespace std;
void utility::gotoxy(int x , int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void utility::printCentered(const string& text, int R, int G, int B, int fontSize) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int padding = (screenWidth - text.length()) / 2;

    COORD coord;
    coord.X = padding;
    coord.Y = csbi.dwCursorPosition.Y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    cout << "\033[38;2;" << R << ";" << G << ";" << B << "m";
    cout << text << endl;

    cout << "\033[0m";

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    cfi.dwFontSize.X = fontSize;
    cfi.dwFontSize.Y = fontSize;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

string utility::generateNewId(const string& currentId) {
    string prefix = currentId.substr(0, 2);  
    string numberStr = currentId.substr(2);  

    int number = stoi(numberStr);

    number++;

    stringstream newId;
    newId << prefix << setw(3) << setfill('0') << number;

    return newId.str();
}

void utility::displayHeaderMovie(){
cout<<string(139,'-')<<endl;
    cout << "| " << left << setw(12) << "\033[38;2;255;140;0mID Phim\033[0m"
              << " | " << left << setw(20) << "Tieu De"
              << " | " << left << setw(16) << "The Loai"
              << " | " << right << setw(8) << "Thoi Luong"
              << " | " << right << setw(12) << "Gia Phim"
              << " | " << left << setw(50) << "Noi Dung"
              << " |\n";
    cout<<string(139,'-')<<endl;
}

void utility::displayHeaderStaff(){
		cout<<string(101,'-')<<endl;
        cout << "| " << left << setw(15) << "ID Nhan Vien "
        << " | " << left <<setw(25) << "Ho va Ten"
        << " | " << left << setw(15) << "Gioi tinh "
        << " | " << left << setw(15) << "SDT"
        << " | " << left << setw(15) << "Ngay Sinh"
        << " |\n";
        cout<<string(101,'-')<<endl;
}

void utility::displayHeaderScreening(){
	cout << setfill('-') << setw(99) << "-" << setfill(' ') << endl;
	   cout <<"|  "<< left << setw(15) << "ID Suat Chieu" 
         <<"|  "<< setw(15) << "ID Room" 
         <<"|  "<< setw(15) << "ID Movie" 
         <<"|  "<< setw(15) << "ID Nhan Vien" 
         <<"|  "<< setw(15) << "Date" 
         <<"|  "<< setw(10) << "Time |" << endl;
   cout << setfill('-') << setw(99) << "-" << setfill(' ') << endl;
}

void utility::displayHeader(){
		cout << setfill('-') << setw(129) << "-" << setfill(' ') << endl;
	   cout <<"|  "<< left << setw(15) << "Ten Phong" 
         <<"|  "<< setw(15) << "Ten Phim" 
         <<"|  "<< setw(15) << "The Loai" 
         <<"|  "<< setw(15) << "Thoi Luong" 
         <<"|  "<< setw(10) << "Gia Phim " 
		 <<"|  "<< setw(40) << "Noi Dung" <<"|"<< endl;
   	cout << setfill('-') << setw(129) << "-" << setfill(' ') << endl;
}


string utility::calculateEndTime(const string& startTime, int totalMinutes)
{
    int hours, minutes;
    sscanf(startTime.c_str(), "%d:%d", &hours, &minutes); 

    int endMinutes = minutes + totalMinutes;
    hours += endMinutes / 60;
    minutes = endMinutes % 60;

    if (hours >= 24) hours -= 24; 

    char buffer[6];
    sprintf(buffer, "%02d:%02d", hours, minutes); 
    return string(buffer);
}