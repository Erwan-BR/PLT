/** 
 * @file ServiceException.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include <stdexcept>
#include <string>

using std::string;

#include "ServiceException.h"

namespace server
{
    ServiceException::ServiceException (HttpStatus status, string msg) 
        : httpStatus(status),msg(msg) {    
    }

    HttpStatus ServiceException::status () const {
        return httpStatus;
    }

    const char* ServiceException::what () const {
        return msg.c_str();
    }
}
