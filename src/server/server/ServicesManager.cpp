/** 
 * @file ServicesManager.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "ServicesManager.hpp"

using namespace std;

namespace server
{
    void ServicesManager::registerService (unique_ptr<AbstractService> service) {
        throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
    }

    AbstractService* ServicesManager::findService (const string& url) const {
        throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
    }

    HttpStatus ServicesManager::queryService (string& out, const string& in, const string& url, const string& method) { 
        if(url == "/version" && method == "GET")
        {
            Json::Value jsonObject;
            jsonObject["major"] = 1;
            jsonObject["minor"] = 0;

            Json::FastWriter fastWriter;
            out = fastWriter.write(jsonObject);
            return HttpStatus::OK;
        }
        else
        {
            throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Error 404: Page not found");
        }
    }
}
