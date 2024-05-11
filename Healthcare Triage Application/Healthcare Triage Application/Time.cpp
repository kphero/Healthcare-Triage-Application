/* Citation and Sources...
Final Project Milestone 1
Module: Time
Filename: Time.cpp
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

#include "Time.h"

namespace seneca{
	// This method resets the `Time` object to the current time using the `U.getTime()` method,
//  which is available in the Utils module. It then returns a reference to the current object.
	Time& Time::reset() {
		minutes = U.getTime();

		return *this;
	}
	// This constructor initializes a `Time` object. It sets the number of minutes held in the object
	//  to the value provided in the min parameter. If no value is provided, it defaults to zero,
	//  effectively setting the time to zero.
	Time::Time(unsigned int min) {
		minutes = min;
	}
	// This method writes the time into ostream in the `HH:MM` format. 
	// If the hours or minutes are single-digit numbers, it pads them with a leading zero. 
	// For example, it formats the times as `03:02`, `16:55`, and `234:06`.
	std::ostream& Time::write(std::ostream& ostr)const {
		ostr << std::setfill('0');
		ostr << std::setw(2) << minutes / MINS_IN_HOUR;
		ostr << ":";
		ostr << std::setw(2) << minutes % MINS_IN_HOUR;
		ostr << std::setfill(' ');

		return ostr;
	}
	// This method reads the time from istream in the `H:M` format. 
	// It ensures that the two integers (hours and minutes) are separated by a colon (`:`). 
	// If they are not, it sets the istream object to a failure state.
	std::istream& Time::read(std::istream& istr) {
		int hours, mins = 0;
		char colon;
		/*istr >> hours;

		// Check if the next character is a colon
		if (istr.get(colon) && colon != ':') {
			// If not a colon, set failstate
			istr.setstate(std::ios::failbit);
			return istr;
		}

		istr >> mins;
		*/

		if (istr >> hours) {
			if (istr.peek() == '\n') {
				istr.setstate(std::ios::failbit);
				return istr;
			}
			else {
				if (istr.get(colon) && colon != ':') {
					// If not a colon, set failstate
					istr.setstate(std::ios::failbit);
					return istr;
				}
				else {
					istr >> mins;
				}
			}
		}

		minutes = hours * 60 + mins;
		return istr;
	}
	// This operator overloads the cast to `unsigned int` for the `Time` class. 
	// If a `Time` object is cast to an unsigned integer, it will return the number of minutes held in the object.
	Time::operator unsigned int()const {
		return minutes;
	}

	Time& Time::operator*= (int val) {
		minutes = minutes * val;

		return *this;
	}

	Time& Time::operator-= (const Time& D) {
		int hours = (this->minutes / MINS_IN_HOUR) - (D.minutes / MINS_IN_HOUR);
		int mins = (this->minutes % MINS_IN_HOUR) - (D.minutes % MINS_IN_HOUR);
		
		if (hours < 0) {
			hours += HOURS_IN_DAY;
		}

		this->minutes = hours * MINS_IN_HOUR + mins;

		return *this;
	}

	Time Time::operator-(const Time& T)const {
		Time timeDiff(minutes);

		timeDiff -= T;

		return timeDiff;
	}

	std::ostream& operator<<(std::ostream& ostr, const Time& time) {
		return time.write(ostr);
	}

	std::istream& operator>>(std::istream& istr, Time& time) {
		return time.read(istr);
	}
}
