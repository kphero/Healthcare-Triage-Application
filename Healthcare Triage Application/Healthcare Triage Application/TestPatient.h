/* Citation and Sources...
Final Project Milestone 4
Module: TestPatient
Filename: TestPatient.h
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

#include "Patient.h"

#ifndef TEST_PATIENT_H_
#define TEST_PATIENT_H_

namespace seneca {
	// Global variable that will keep track of ticket number
	extern int nextTestTicket;

	class TestPatient : public Patient {
	public:
		// Default constructor will increment test ticket 
		// each time patient is created
		TestPatient() : Patient(nextTestTicket++) { };
		// Return type for TestPatient
		char type() const override;
		// Override for Patient write function
		std::ostream& write(std::ostream& out) const override;
		// Override for Patient read function
		std::istream& read(std::istream& in) override;
	};
}
#endif // !TEST_PATIENT_H_