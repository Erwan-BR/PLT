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
        throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
    }
}
