/* Citation and Sources...
Final Project Milestone 3
Module: Patient
Filename: Patient.h
Version 1.0
Author   Kyle Homen
Revision History
-----------------------------------------------------------
Date      Reason
2024/03/23  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#ifndef PATIENT_H_
#define PATIENT_H_

#include "IOAble.h"
#include "Ticket.h"

#define MAX_NAME_LEN 50
#define OHIP_DIGITS_MIN 100000000
#define OHIP_DIGITS_MAX 999999999

namespace seneca {
    class Patient : public IOAble {
        char* m_name = nullptr; 
        int m_ohipNum = -1;
        Ticket m_ticket;
    public:
        Patient(int ticketNo);
        ~Patient();
        Patient& operator=(const Patient& rhs);
        Patient(const Patient& other);
        // Member functions
        virtual char type() const = 0;
        bool operator==(char rhs) const;
        bool operator==(const Patient& rhs) const;
        void setArrivalTime();
        Time time() const;
        int number() const;
        operator bool() const;
        operator const char*() const;
        // virtual overwrites
        std::ostream& write(std::ostream& out) const;
        std::istream& read(std::istream& in);
    };
}
#endif // !PATIENT_H_