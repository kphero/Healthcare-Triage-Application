/* Citation and Sources...
Final Project Milestone 1
Module: Time
Filename: Time.h
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

#ifndef SENECA_TIME_H_
#define SENECA_TIME_H_
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>

#include "Utils.h"

#define MINS_IN_HOUR 60
#define HOURS_IN_DAY 24

namespace seneca {
	class Time {
		int minutes;

	public:
		// This method resets the `Time` object to the current time using the `U.getTime()` method,
		//  which is available in the Utils module. It then returns a reference to the current object.
		Time& reset();
		// This constructor initializes a `Time` object. It sets the number of minutes held in the object
		//  to the value provided in the min parameter. If no value is provided, it defaults to zero,
		//  effectively setting the time to zero.
		Time(unsigned int min = 0u);
		// This method writes the time into ostream in the `HH:MM` format. 
		// If the hours or minutes are single-digit numbers, it pads them with a leading zero. 
		// For example, it formats the times as `03:02`, `16:55`, and `234:06`.
		std::ostream& write(std::ostream& ostr = std::cout)const;
		// This method reads the time from istream in the `H:M` format. 
		// It ensures that the two integers (hours and minutes) are separated by a colon (`:`). 
		// If they are not, it sets the istream object to a failure state.
		std::istream& read(std::istream& istr = std::cin);
		// This operator overloads the cast to `unsigned int` for the `Time` class. 
		// If a `Time` object is cast to an unsigned integer, it will return the number of minutes held in the object.
		operator unsigned int()const;
		Time& operator*= (int val);
		Time& operator-= (const Time& D);
		Time operator-(const Time& T)const;
	};

	std::ostream& operator<<(std::ostream& ostr, const Time& time);
	std::istream& operator>>(std::istream& istr, Time& time);
}
#endif // !SENECA_TIME_H_