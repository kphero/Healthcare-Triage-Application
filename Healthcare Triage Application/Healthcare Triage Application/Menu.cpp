/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.cpp
Version 1.0
Author   Kyle Homen
Revision History
-----------------------------------------------------------
Date      Reason
2024/03/11  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"

namespace seneca {
	Menu::Menu(const char* menuContent, int numberOfTabs) : m_text(new char[strlen(menuContent) + 1]) {
		strcpy(m_text, menuContent);

		m_options = 0;
		m_tabs = numberOfTabs;

		for (int i = 0; m_text[i] != '\0'; i++) {
			if (m_text[i] == '\n') {
				m_options++;
			}
		}
	}
	Menu::~Menu() {
		delete[] m_text;
	}

	void Menu::display() {
		char* split;
		Menu copy(m_text);
		split = strtok(copy.m_text, "\n");

		for (int i = 0; i <= m_options; i++) {
			displayTabs();
			std::cout << split << std::endl;
			split = strtok(NULL, "\n");
		}

		displayTabs();
		std::cout << "0- Exit" << std::endl;

		displayTabs();
		std::cout << "> ";
	}

	void Menu::displayTabs() {
		if (m_tabs > 0) {
			for (int i = 0; i < m_tabs; i++) {
				std::cout << "   ";
			}
		}
	}

	int& Menu::operator>>(int& Selection) {
		display();
		bool valid = false;

		while (!valid) {
			std::cin >> Selection;

			if (std::cin.fail()) {
				std::cout << "Bad integer value, try again: ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			} 
			else if (std::cin.get() != '\n') {
				std::cout << "Only enter an integer, try again: ";
			}
			else if (Selection < 0 || Selection > m_options) {
				std::cout << "Invalid value enterd, retry[0 <= value <= " << m_options << "]: ";
			}
			else {
				valid = true;
			}
		}

		return Selection;
	}
}