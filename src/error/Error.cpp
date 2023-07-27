//
// Created by Magnesium on 2023/7/16.
//

#include "../../include/error/Error.h"



namespace hdg {
    std::string buildArrow(const std::string& text, int posStart, int posEnd){
        std::string arrowStart(posStart, ' ');
        std::string arrowEnd(posEnd-posStart, '^');
        return text + "\n" + arrowStart + arrowEnd + "\n";
    }

    Error::Error(int posStart, int posEnd, const std::string& text, std::string errorName, std::string errorDetails):
        posStart(posStart),
        posEnd(posEnd),
        text(text),
        errorName(std::move(errorName)),
        errorDetails(std::move(errorDetails)){
    }

    std::ostream &operator<<(std::ostream &out, Error &error) {
        std::cout << error.errorName << ": " << error.errorDetails << std::endl << std::endl;
        std::cout << buildArrow(error.text, error.posStart, error.posEnd);
        return out;
    }
} // hdg