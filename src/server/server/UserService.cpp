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
        userDB(userDB) 
    {
    }

    HttpStatus UserService::get (Json::Value& jsonOut, int id) const {
        const User* user = userDB.getUser(id);
        if(!user)
            throw ServiceException(HttpStatus::NOT_FOUND,"Id not specified or wrong id");
        jsonOut["Age"] = user->age;
        jsonOut["Name"] = user->name;
        return HttpStatus::OK;
    }

    HttpStatus UserService::post (Json::Value& jsonOut, const Json::Value& jsonIn, int id) {
        const User* user = userDB.getUser(id);
        if(!user && id != 0)
            throw ServiceException(HttpStatus::NOT_FOUND,"Id not specified or wrong id");

        if(id == 0)
        {
            jsonOut["Id"] = userDB.addUser(make_unique<server::User>(jsonIn["Name"].asString(),jsonIn["Age"].asInt()));
        }
        else
        {
            unique_ptr<User> userMod(new User(*user));

            if(jsonIn.isMember("Age"))
                userMod->age = jsonIn["Age"].asInt();

            if(jsonIn.isMember("Name"))
                userMod->name = jsonIn["Name"].asString();

            userDB.setUser(id, std::move(userMod));
        }
        return HttpStatus::OK;
    }

    HttpStatus UserService::put (Json::Value& jsonOut,const Json::Value& jsonIn) {
        jsonOut["Id"] = userDB.addUser(make_unique<server::User>(jsonIn["Name"].asString(),jsonIn["Age"].asInt()));
        return HttpStatus::OK;
    }

    HttpStatus UserService::remove (int id) {
        const User* user = userDB.getUser(id);
        if(!user)
            throw ServiceException(HttpStatus::NOT_FOUND,"Id not specified or wrong id");
        userDB.removeUser(id);
        return HttpStatus::OK;
    }
}
