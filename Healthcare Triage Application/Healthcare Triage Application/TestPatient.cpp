/* Citation and Sources...
Final Project Milestone 4
Module: TestPatient
Filename: TestPatient.cpp
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

#include "TestPatient.h"

namespace seneca {
	// Global variable that will keep track of ticket number
	int nextTestTicket = 1;

	// Return type for TestPatient
	char TestPatient::type() const {
		return 'C';
	}

	// Override for Patient write function
	std::ostream& TestPatient::write(std::ostream& out) const {
		// Only writes header if using cout
		if (&out == &std::cout) {
			out << "Contagion TEST" << std::endl;
		}
		Patient::write(out);
		return out;
	}

	// Override for Patient read function
	std::istream& TestPatient::read(std::istream& in) {
		Patient::read(in);
		// If reading from cin we need to ignore newline
		if (&in == &std::cin) {
			in.ignore(1000, '\n');
		}
		// If reading from file we need to add ticket numbers accordingly
		else if (&in != &std::cin) {
			nextTestTicket = number() + 1;
		}

		return in;
	}
}
