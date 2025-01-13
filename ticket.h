#include <string>
#include "Seat.h" 
#pragma once
using namespace std;
class Ticket {
private:
    string idTicket;
    string idScreening;
    Seat seat;

public:
    static string idCurrentTicket; 
    Ticket(); 
    Ticket(const string& idTicket, const string& idScreening, const Seat& s); 
    string getIdTicket() const;
    void setIdTicket(const string& idTicket);
    string getIdScreening() const;
    void setIdScreening(const string& idScreening);
    Seat getSeat() const;
    void setSeat(const Seat& s);
    void displayTicket();  
    
    void docfile(const char*);
};