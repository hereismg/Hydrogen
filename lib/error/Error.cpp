//
// Created by Magnesium on 2023/7/16.
//

#include "Error.h"

#include <utility>

namespace hdg {
    Error::Error(int posStart, int posEnd, std::string errorName, std::string errorDetails):
        posStart(posStart), posEnd(posEnd), errorName(std::move(errorName)), errorDetails(std::move(errorDetails)){
    }

    std::ostream &operator<<(std::ostream &out, Error &error) {
        std::cout << error.errorName << ": " << error.errorDetails;
        return out;
    }
} // hdg