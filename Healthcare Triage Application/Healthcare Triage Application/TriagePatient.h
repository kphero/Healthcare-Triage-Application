/* Citation and Sources...
Final Project Milestone 4
Module: TriagePatient
Filename: TriagePatient.h
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

#ifndef TRIAGE_PATIENT_H_
#define TRIAGE_PATIENT_H_

#include "Patient.h"

#define MAX_SYMPTONS 512

namespace seneca {
	// Global variable that will keep track of ticket number
	extern int nextTriageTicket;

	class TriagePatient : public Patient {
		char* m_symptoms;
	public:
		// Default constructor will increment test ticket 
		// each time patient is created, and set m_symptons to null
		TriagePatient() : Patient(nextTriageTicket++) { m_symptoms = nullptr; };
		// Destructor to handle deleting m_symptons dynamic memory
		~TriagePatient();
		// Return type for TriagePatient
		char type() const override;
		// Override for Patient write function
		std::ostream& write(std::ostream& out) const override;
		// Override for Patient read function
		std::istream& read(std::istream& in) override;
	};
}
#endif // !TRIAGE_PATIENT_H_