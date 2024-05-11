/* Citation and Sources...
Final Project Milestone 3
Module: Patient
Filename: Patient.cpp
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
#define _CRT_SECURE_NO_WARNINGS

#include "Patient.h"

namespace seneca {
    Patient::Patient(int ticketNo) : m_name(nullptr), m_ohipNum(0), m_ticket(ticketNo) { }

    Patient::~Patient() {
        delete[] m_name;
    }

    Patient& Patient::operator=(const Patient& rhs) {
        if (this != &rhs) {
            if (m_name) {
                delete[] this->m_name;
            }
            this->m_name = new char[strlen(rhs.m_name) + 1];
            strcpy(this->m_name, rhs.m_name);
            m_ticket = rhs.m_ticket;
            this->m_ohipNum = rhs.m_ohipNum;
        }
        return *this;
    }

    Patient::Patient(const Patient& other) : m_ticket(other.number()) {
        *this = other;
    }

    // Member functions
    bool Patient::operator==(char rhs) const {
        return this->type() == rhs;
    }

    bool Patient::operator==(const Patient& rhs) const {
        return this->type() == rhs.type();
    }

    void Patient::setArrivalTime() {
        m_ticket.resetTime();
    }

    Time Patient::time() const {
        return m_ticket.time();
    }

    int Patient::number() const {
        return m_ticket.number();
    }

    Patient::operator bool() const {
        return m_name != nullptr;
    }

    Patient::operator const char* () const {
        return m_name;
    }

    // virtual overwrites
    std::ostream& Patient::write(std::ostream& out) const {
        if (&out == &std::cout) {
            if (m_name == nullptr) {
                out << "Invalid Patient Record" << std::endl;
            }
            else {
                m_ticket.write(out);
                out << "\n" << m_name << ", OHIP: " << m_ohipNum << std::endl;
            }
        } 
        else if (&out == &std::clog) {
            if (m_name == nullptr) {
                out << "Invalid Patient Record" << std::endl;
            }
            else {
                out << std::setw(53) << std::left << std::setfill('.')
                    << m_name;

                out << std::setfill(' ') << m_ohipNum << std::setw(5) << std::right << m_ticket.number()
                    << " " << m_ticket.time();
            }
        }
        else {
            out << type() << ",";
            out << m_name << "," << m_ohipNum << ",";
            m_ticket.write(out);
        }
        
        return out;
    }

    std::istream& Patient::read(std::istream& in) {
        char nameInput[MAX_NAME_LEN + 1];
        bool validNumber = false;

        if (&in == &std::cin) {
            std::cout << "Name: ";
            in.get(nameInput, MAX_NAME_LEN);
            in.ignore(1000, '\n');

            if (m_name) {
                delete[] m_name;
            }
            m_name = new char[strlen(nameInput) + 1];
            strcpy(m_name, nameInput);

            std::cout << "OHIP: ";
            do {
                in >> m_ohipNum;

                if (m_ohipNum >= OHIP_DIGITS_MIN && m_ohipNum <= OHIP_DIGITS_MAX) {
                    validNumber = true;
                }
                else if (in.fail()) {
                    std::cout << "Bad integer value, try again: ";
                    in.clear();
                    in.ignore(1000, '\n');
                }
                else {
                    std::cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
                    in.clear();
                    in.ignore(1000, '\n');
                }
            } while (!validNumber);

        }
        else {
            in.get(nameInput, MAX_NAME_LEN + 1, ',');
            in.ignore();

            if (m_name) {
                delete[] m_name;
            }
            m_name = new char[strlen(nameInput) + 1];
            strcpy(m_name, nameInput);

            in >> m_ohipNum;
            in.ignore();

            m_ticket.read(in);
        }
        return in;
    }
}