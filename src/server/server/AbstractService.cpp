/** 
 * @file AbstractService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "AbstractService.hpp"

using namespace std;
namespace server 
{
    AbstractService::AbstractService (const string& pattern) {
        setPattern(pattern);
    }

    AbstractService::~AbstractService() {
        
    }

    const string& AbstractService::getPattern () const {
        return pattern;
    }

    void AbstractService::setPattern (const string& pattern) {
        this->pattern = pattern;
    }

    HttpStatus AbstractService::get (Json::Value& out, int id) const {
        throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
    }

    HttpStatus AbstractService::post (const Json::Value& in, int id) {
        throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
    }

    HttpStatus AbstractService::put (Json::Value& out, const Json::Value& in) {
        throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
    }

    HttpStatus AbstractService::remove (int id) {
        throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
    }
}
