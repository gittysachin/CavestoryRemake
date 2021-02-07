//
// Created by blockost on 2/6/19.
//

#ifndef CAVESTORY_INVALIDLEVELEXCEPTION_H
#define CAVESTORY_INVALIDLEVELEXCEPTION_H

#include <string>
#include <exception>
#include <sstream>

class InvalidLevelException : std::exception {

public:

    /**
     * Constructor taking a std::string.
     */
    explicit InvalidLevelException(const std::string &message);

    /**
     * Constructor taking a std::stringstream.
     */
    explicit InvalidLevelException(const std::stringstream &ss);

    const std::string &getMessage() const;

private:
    std::string message;
};


#endif //CAVESTORY_INVALIDLEVELEXCEPTION_H
