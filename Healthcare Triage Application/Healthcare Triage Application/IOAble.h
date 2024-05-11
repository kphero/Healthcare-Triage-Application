/* Citation and Sources...
Final Project Milestone 2
Module: IOAble
Filename: IOAble.h
Version 1.0
Author   Kyle Homen
Revision History
-----------------------------------------------------------
Date      Reason
2024/03/17  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#ifndef IOABLE_H_
#define IOABLE_H_

#include <iostream>
#include "Utils.h"

namespace seneca {
    class IOAble {
    public:
        virtual std::ostream& write(std::ostream& out) const;
        virtual std::istream& read(std::istream& in);
        virtual ~IOAble();
    };

    std::istream& operator>>(std::istream& in, IOAble& io);
    std::ostream& operator<<(std::ostream& out, const IOAble& io);
}
#endif // !IOABLE_H_