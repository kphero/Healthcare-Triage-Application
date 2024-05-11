/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.h
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

#ifndef SENECA_MENU_H_
#define SENECA_MENU_H_
#include <iostream>
#include <string.h>
#include <cstring>
#include "Utils.h"
namespace seneca {
	class Menu {
		char* const m_text;
		int m_options;
		int m_tabs;

	public:
		Menu(const char* menuContent, int numberOfTabs = 0);
		~Menu();
		// Makes sure the Menu can not be copied or assigned to another Menu object.
		Menu(const Menu&);
		void display();
		int& operator>>(int& Selection);
		void displayTabs();
	};
}
#endif // !SENECA_MENU_H_