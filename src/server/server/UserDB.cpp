  /** 
 * @file UserDB.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "UserDB.hpp"

namespace server
{
    UserDB::UserDB() : idseq(1) {
        
    }

    const User* UserDB::getUser (int id) const {
        auto ite = users.find(id);
        if (ite == users.cend())
            return nullptr;
        return ite->second.get();
    }

    int UserDB::addUser (unique_ptr<User> user) {
        int id = idseq++;
        users.insert(std::make_pair(id,std::move(user)));
        return id;
    }

    void UserDB::setUser (int id, unique_ptr<User> user) {
        users[id] = std::move(user);
        if (id > idseq) {
            idseq = id;
        }
    }

    void UserDB::removeUser (int id) {
        auto ite = users.find(id);
        if (ite == users.end())
            return;
        users.erase(ite);
    }
}
