/** 
 * @file UserService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "UserService.hpp"


namespace server
{
    UserService::UserService (UserDB& userDB) : AbstractService("/user"),
        userDB(userDB) {
        
    }

    HttpStatus UserService::get (Json::Value& out, int id) const {
        throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
    }

    HttpStatus UserService::post (const Json::Value& in, int id) {
        throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
    }

    HttpStatus UserService::put (Json::Value& out,const Json::Value& in) {
        throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
    }

    HttpStatus UserService::remove (int id) {
        throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
    }
}
