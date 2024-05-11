/* Citation and Sources...
Final Project Milestone 2
Module: IOAble
Filename: IOAble.cpp
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

#include "IOAble.h"

namespace seneca {
    std::ostream& IOAble::write(std::ostream& out) const {
        return out;
    }

    std::istream& IOAble::read(std::istream& in) {
        return in;
    }

    IOAble::~IOAble() {
        // Empty
    }

    std::istream& operator>>(std::istream& in, IOAble& io) {
        return io.read(in);
    }

    std::ostream& operator<<(std::ostream& out, const IOAble& io) {
        return io.write(out);
    }
}