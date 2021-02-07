//
// Created by blockost on 2/6/19.
//

#include "InvalidLevelException.h"


InvalidLevelException::InvalidLevelException(const std::string &message) : message(message) {}

InvalidLevelException::InvalidLevelException(const std::stringstream &ss) : message(ss.str()) {}

const std::string &InvalidLevelException::getMessage() const {
    return message;
}
