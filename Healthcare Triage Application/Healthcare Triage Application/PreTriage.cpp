/* Citation and Sources...
Final Project Milestone 2
Module: PreTriage
Filename: PreTriage.cpp
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
#define _CRT_SECURE_NO_WARNINGS

#include "PreTriage.h"

namespace seneca {
	// Constructor
	PreTriage::PreTriage(const char* filename) 
		: m_waitC(15), m_waitT(5) {
		if (filename) {
			m_filename = new char[strlen(filename) + 1];
			strcpy(m_filename, filename);
		}
		else {
			m_filename = nullptr;
			for (int i = 0; i < MAX_PATIENTS; i++) {
				m_patients[i] = nullptr;
			}
		}
		// Loads file on construction
		load();
	}

	// Destructor
	PreTriage::~PreTriage() {
		// Saves file on destruction
		save();

		for (int i = 0; i < m_numOfPatients; i++) {
			delete m_patients[i];
		}
		delete[] m_filename;
	}

	// Returns the total estimated wait time for type of patient
	const Time PreTriage::getWaitTime(const Patient& patient) const {
		int numPatients = 0;
		Time time = patient.type() == 'C' ? m_waitC : m_waitT;

		for (int i = 0; i < m_numOfPatients; i++) {
			if (m_patients[i]->type() == patient.type()) {
				numPatients++;
			}
		}
		// Returns product of the average time and the number of patients matching type
		return time * numPatients;
	}

	// Adjusts average wait time of type of patient
	void PreTriage::setAverageWaitTime(Patient& patient) {
		int ct = U.getTime();
		int ptt = patient.time();
		int ptn = patient.number();

		if (patient.type() == 'C') {
			m_waitC = ((ct - ptt) + (m_waitC * (ptn - 1))) / ptn;
		}
		else {
			m_waitT = ((ct - ptt) + (m_waitT * (ptn - 1))) / ptn;
		}
	}

	// Finds the index of first patient that matches specified type
	int PreTriage::indexOfFirstInLine(char type) {
		for (int i = 0; i < m_numOfPatients; i++) {
			if (m_patients[i]->type() == type) {
				return i;
			}
		}
		// If no patient matches type
		return -1;
	}

	// Loads the average wait times and the patient records from the data file
	void PreTriage::load() {
		char type;
		// Create temporary patient pointer
		Patient* temp = nullptr;
		// Attempts to open file
		std::ifstream file(m_filename);

		std::cout << "Loading data..." << std::endl;

		if (file.is_open()) {
			// Takes average wait times from file
			file >> m_waitC;
			file.ignore();
			file >> m_waitT;
			file.ignore(1000, '\n');
			// Peeks to see if file is empty
			if (file.peek() != EOF) {
				// Loop through patients
				for (int i = 0; i < MAX_PATIENTS && file.peek() != EOF; i++) {
					// Extract type char
					type = file.get();
					// Create patient corrosponding to char
					if (type == 'C') {
						temp = new TestPatient;
						m_numC++;
					}
					else if (type == 'T') {
						temp = new TriagePatient;
						m_numT++;
					}
					// Extract rest of data to temp and assign pointer to patient array
					if (temp) {
						file.ignore();
						file >> *temp;
						file.ignore(1000, '\n');
						m_patients[i] = temp;
						m_numOfPatients++;
					}
				}
			}
			
		}
		// Statements
		if (m_numOfPatients >= MAX_PATIENTS) {
			std::cout << "Warning: number of records exceeded " << MAX_PATIENTS << std::endl;
		}

		if (m_numOfPatients == 0) {
			std::cout << "No data or bad data file!\n" << std::endl;
		}
		else {
			std::cout << m_numOfPatients << " Records imported...\n" << std::endl;
		}
		// Close file
		file.close();
	}

	// Saves data to file
	void PreTriage::save() {
		std::cout << "Saving lineup..." << std::endl;
		// Opens file for saving
		std::ofstream file(m_filename);
		// Inserts the average wait times
		file << m_waitC << ',' << m_waitT << std::endl;
		// Loops through and inserts each patient
		if (file.is_open()) {
			for (int i = 0; i < m_numOfPatients && m_patients[i]; i++) {
				m_patients[i]->write(file);
				file << std::endl;
			}
		}
		// Number of patients saved statement
		std::cout << m_numC << " Contagion Tests and " << m_numT << " Triage records were saved!" << std::endl;
		// Close file
		file.close();

	}

	// Registers a new patient
	void PreTriage::reg() {
		int input, validInput = 1;

		if (m_numOfPatients >= MAX_PATIENTS) {
			std::cout << "Line up full!" << std::endl;
		}
		else {
			do {
				std::cout << "   Select Type of Registration:" << std::endl;
				std::cout << "   1- Contagion Test" << std::endl;
				std::cout << "   2- Triage" << std::endl;
				std::cout << "   0- Exit" << std::endl;
				std::cout << "   > ";

				std::cin >> input;
				std::cin.ignore(1000, '\n');

				if (input == 0) {
					// Do nothing
				}
				else if (input == 1 || input == 2) {
					if (input == 1) {
						m_patients[m_numOfPatients] = new TestPatient;
						m_numC++;
					}
					else {
						m_patients[m_numOfPatients] = new TriagePatient;
						m_numT++;
					}
					// Set patients arrival time
					m_patients[m_numOfPatients]->setArrivalTime();
					// Extract patient input from cin
					std::cout << "Please enter patient information: " << std::endl;
					std::cin >> *m_patients[m_numOfPatients];
					std::cout << std::endl;
					// Print ticket
					std::cout << "******************************************" << std::endl;
					std::cout << *m_patients[m_numOfPatients];
					std::cout << "Estimated Wait Time: ";
					std::cout << getWaitTime(*m_patients[m_numOfPatients]);
					std::cout << std::endl;
					std::cout << "******************************************" << std::endl << std::endl;
					// Increase lineup size
					m_numOfPatients++;
				}
				else {
					std::cout << "Invalid choice. Must be an integer between 0 and 2" << std::endl;
					validInput = 0;
				}
			} while (!validInput);
		}
	}

	// Admits next patient in line
	void PreTriage::admit() {
		int input, index, validInput = 1;
		char type;
		Time time;

		do {
			// Print sub-menu with indentation
			std::cout << "   Select Type of Admittance:" << std::endl;
			std::cout << "   1- Contagion Test" << std::endl;
			std::cout << "   2- Triage" << std::endl;
			std::cout << "   0- Exit" << std::endl;
			std::cout << "   > ";
			// Get user input for menu selection and ignore newline
			std::cin >> input;
			std::cin.ignore(1000, '\n');
			// Validate
			if (input != 1 && input != 2 && input != 0) {
				std::cout << "Invalid choice. Must be an integer between 0 and 2" << std::endl;
				validInput = 0;
			}
		} while (!validInput);

		if (input == 0) {
			// Do nothing
		}
		else {
			// Determine type based on input
			if (input == 1) {
				type = 'C';
			}
			else {
				type = 'T';
			}
			// Call index of next in line based on type
			index = indexOfFirstInLine(type);
			// If no patient found, terminate
			if (index < 0) {
				std::cout << "Lineup is empty!\n";
			}
			else {
				std::cout << "\n******************************************\n";
				std::cout << "Call time: [";
				std::cout << time.reset();
				std::cout << "]\n";
				std::cout << "Calling at for ";
				m_patients[index]->write(std::cout);
				std::cout << "******************************************\n\n";

				setAverageWaitTime(*m_patients[index]);
				U.removeDynamicElement(m_patients, index, m_numOfPatients);
				(type == 'C') ? m_numC-- : m_numT--;
			}
		}
	}

	// Prints report on patients in lineup
	void PreTriage::lineup() {
		int input, count = 1, validInput = 1;

		do {
			// Print sub-menu with indentation
			std::cout << "   Select The Lineup:" << std::endl;
			std::cout << "   1- Contagion Test" << std::endl;
			std::cout << "   2- Triage" << std::endl;
			std::cout << "   0- Exit" << std::endl;
			std::cout << "   > ";
			// Get user input for menu selection and ignore newline
			std::cin >> input;
			std::cin.ignore(1000, '\n');
			// Validate
			if (input != 1 && input != 2 && input != 0) {
				std::cout << "Invalid choice. Must be an integer between 0 and 2" << std::endl;
				validInput = 0;
			}
		} while (!validInput);

		if (input == 0) {
			// Do nothing
		}
		else {
			// Print header before displaying lineup
			std::cout << "Row - Patient name"
				<< "                                          "
				<< "OHIP     Tk #  Time" << std::endl;
			std::cout << "---------------------------------------------------"
				<< "----------------------------" << std::endl;
			// Iterate through lineup
			if (m_patients != nullptr) {
				for (int i = 0; i < m_numOfPatients; i++) {
					if (input == 1 && m_patients[i]->type() == 'C') {
						std::clog << count << "   - ";
						m_patients[i]->write(std::clog);
						std::clog << std::endl;

						count++;
					}
					else if (input == 2 && m_patients[i]->type() == 'T') {
						std::clog << count << "   - ";
						m_patients[i]->write(std::clog);
						std::clog << std::endl;

						count++;
					}
				}
				std::cout << "---------------------------------------------------"
					<< "----------------------------" << std::endl;
			}
			else {
				std::cout << "Line up is empty!\n";
			}
		}
	}

	// Runs main application and displays main menu
	void PreTriage::run() {
		int input, exit = 1;

		// Loop until exit (0) is chosen
		do {
			// Display main menu
			std::cout << "General Healthcare Facility Pre-Triage Application" << std::endl;
			std::cout << "1- Register" << std::endl;
			std::cout << "2- Admit" << std::endl;
			std::cout << "3- View Lineup" << std::endl;
			std::cout << "0- Exit" << std::endl;
			std::cout << "> ";
			// Get user input for menu
			std::cin >> input;
			std::cin.ignore(1000, '\n');
			// Run the corrosponding menu function, exit, or display error message
			switch (input) {
			case (0):
				exit = 0;
				break;
			case (1):
				reg();
				break;
			case (2):
				admit();
				break;
			case (3):
				lineup();
				break;
			default:
				std::cout << "Invalid choice. Must be an integer between 0 and 3" << std::endl;
			}
		} while (exit);	
	}
}
