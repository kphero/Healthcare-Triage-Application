/* Citation and Sources...
Final Project Milestone 4
Module: TriagePatient
Filename: TriagePatient.cpp
Version 1.0
Author   Kyle Homen
Revision History
-----------------------------------------------------------
Date      Reason
2024/03/31  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

#include "TriagePatient.h"

namespace seneca {
	// Global variable that will keep track of ticket number
	int nextTriageTicket = 1;

	// Destructor to handle deleting m_symptons dynamic memory
	TriagePatient::~TriagePatient() {
		delete[] m_symptoms;
	}

	// Return type for TriagePatient
	char TriagePatient::type() const {
		return 'T';
	}

	// Override for Patient write function
	std::ostream& TriagePatient::write(std::ostream& out) const {
		// If using cout, write header and symptons along with Patient
		if (&out == &std::cout) {
			out << "TRIAGE" << std::endl;
			Patient::write(out);
			out << "Symptoms: " << m_symptoms << std::endl;
		}
		// Adds comma and symptons to clog write
		else if (&out != &std::clog) {
			Patient::write(out);
			out << "," << m_symptoms;
		}
		// Just original function without additional functionality
		else {
			Patient::write(out);
		}
		// Return
		return out;
	}

	// Override for Patient read function
	std::istream& TriagePatient::read(std::istream& in) {
		// Temporary string to hold up to 512 characters worth of symptons
		char symptomInput[MAX_SYMPTONS + 1];
		// Delete symptons if already allocated
		if (m_symptoms != nullptr) {
			delete[] m_symptoms;
		}
		// Read in via cin or file
		Patient::read(in);	
		// If via cin, additional prompt for user inputted symptons
		if (&in == &std::cin) {
			in.ignore(1000, '\n');
			std::cout << "Symptoms: ";
			in.get(symptomInput, MAX_SYMPTONS);
			in.ignore(1000, '\n');
		}
		// If via file, ignore comma and read in symptons
		// Update ticket number accordingly
		else {
			in.ignore();
			in.get(symptomInput, MAX_SYMPTONS, '\n');
			nextTriageTicket = number() + 1;
		}
		// Allocate memory for symptons and copy from temp string
		m_symptoms = new char[strlen(symptomInput) + 1];
		strcpy(m_symptoms, symptomInput);
		// If anything fails, deallocated and set to null
		if (in.fail()) {
			if (m_symptoms != nullptr) {
				delete[] m_symptoms;
				m_symptoms = nullptr;
			}
		}
		// Return
		return in;
	}
}