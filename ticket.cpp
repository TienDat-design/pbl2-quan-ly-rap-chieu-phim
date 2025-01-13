#include "ticket.h"
#include <iostream>
using namespace std;
string Ticket::idCurrentTicket = "TK000";

Ticket::Ticket() : idTicket(""), idScreening(""), seat(0, 0, false) {}

Ticket::Ticket(const string& idTicket, const string& idScreening, const Seat& s) 
    : idTicket(idTicket), idScreening(idScreening), seat(s) {}

string Ticket::getIdTicket() const {
    return idTicket;
}

void Ticket::setIdTicket(const string& idTicket) {
    this->idTicket = idTicket;
}

string Ticket::getIdScreening() const {
    return idScreening;
}

void Ticket::setIdScreening(const string& idScreening) {
    this->idScreening = idScreening;
}

Seat Ticket::getSeat() const {
    return seat;
}

void Ticket::setSeat(const Seat& s) {
    this->seat = s;
}

void Ticket::displayTicket()  {
    cout << "ID Ve:  " << idTicket << endl;
    cout << "ID Suat Chieu: " << idScreening << endl;
    cout << "Cho ngoi : " << this->seat.formatSeat()<<endl;
}

void Ticket::docfile(const char* filename){
	utility u;
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
        Ticket::idCurrentTicket = idTicket;
		}
    fclose(f);
};