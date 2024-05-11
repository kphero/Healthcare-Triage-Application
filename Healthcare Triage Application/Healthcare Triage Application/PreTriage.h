/* Citation and Sources...
Final Project Milestone 2
Module: PreTriage
Filename: PreTriage.h
Version 1.0
Author   Kyle Homen
Revision History
-----------------------------------------------------------
Date      Reason
2024/04/07  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/



#ifndef PRE_TRIAGE_H_
#define PRE_TRIAGE_H_

#include <iostream>
#include <fstream>
#include "Patient.h"
#include "TestPatient.h"
#include "TriagePatient.h"
#include "Utils.h"

#define MAX_PATIENTS 100

namespace seneca {
	class PreTriage {
		// Waits times
		Time m_waitC;
		Time m_waitT;
		// Pointer array of patients in line
		Patient* m_patients[MAX_PATIENTS]{};
		// Pointer to filename
		char* m_filename = nullptr;
		// Number of patients in line
		int m_numOfPatients = 0;
		// Number of test and triage patients
		int m_numC = 0;
		int m_numT = 0;
		// Returns the total estimated wait time for type of patient
		const Time getWaitTime(const Patient& patient) const;
		// Adjusts average wait time of type of patient
		void setAverageWaitTime(Patient& patient);
		// Finds the index of first patient that matches specified type
		int indexOfFirstInLine(char type);
		// Loads the average wait times and the patient records from the data file
		void load();
		// Saves data to file
		void save();
		// Registers a new patient
		void reg();
		// Admits next patient in line
		void admit();
		// Prints report on patients in lineup
		void lineup();
	public:
		// Constructor
		PreTriage(const char* filename);
		// Destructor
		~PreTriage();
		// Runs main application and displays main menu
		void run();

	};
}

#endif