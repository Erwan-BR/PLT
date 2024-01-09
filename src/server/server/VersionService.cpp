/** 
 * @file VersionService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "VersionService.hpp"

namespace server
{
    VersionService::VersionService () : AbstractService("/version") {
        
    }

    HttpStatus VersionService::get (Json::Value& jsonOut, int id) const {
        std::cout << "Creation of the json object" << std::endl;
        jsonOut["major"] = 1;
        jsonOut["minor"] = 0;
        return HttpStatus::OK;
    }
}
