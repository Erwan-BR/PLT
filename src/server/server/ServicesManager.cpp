/** 
 * @file ServicesManager.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "ServicesManager.hpp"
#include <string.h>

using namespace std;

namespace server
{
    void ServicesManager::registerService (unique_ptr<AbstractService> service) {
        this->services.push_back(std::move(service));
    }

    AbstractService* ServicesManager::findService (const string& url) const {
        for(auto& service : services)
        {
            const string& pattern(service->getPattern());
            if(url.find(pattern) != 0)continue;
            if(url.size() > pattern.size() && url[pattern.size()] != '/')continue;
            return service.get();
        }
        return nullptr;
    }

    HttpStatus ServicesManager::queryService (string& out, const string& in, const string& url, const string& method) {
        AbstractService* service = this->findService(url);
        if(!service)
            throw ServiceException(HttpStatus::NOT_FOUND,"Error 404: Page not found");
        const string& pattern(service->getPattern());
        int id = 0;

        if(url.size() > pattern.size())
        {
            string end = url.substr(pattern.size());
            if(end[0] != '/')throw ServiceException(HttpStatus::BAD_REQUEST,"Wrong URL, try <service>/<id>");
            end = end.substr(1);
            if(end.empty())throw ServiceException(HttpStatus::BAD_REQUEST,"Wrong URL, try <service>/<id>");
            try
            {
                size_t pos = 0;
                id = stoi(end, &pos);
                if(pos != end.size())throw ServiceException(HttpStatus::BAD_REQUEST,"You may have used a wrong id, try <service>/<id>");
            }
            catch(...)
            {
                throw ServiceException(HttpStatus::BAD_REQUEST,"You may have used a wrong id, try <service>/<id>");
            }
            

        }

        if(method == "GET")
        {
            cerr << "GET request " << pattern << " with id = " << id << endl;
            Json::Value jsonOut;
            HttpStatus status = service->get(jsonOut, id);

            out = jsonOut.toStyledString();
            return status;
        }

        if(method == "POST")
        {
            cerr << "POST request " << pattern << " with data: " << in << endl;
            Json::Reader jsonReader;
            Json::Value jsonIn;
            Json::Value jsonOut;
            if(!jsonReader.parse(in, jsonIn))
                throw ServiceException(HttpStatus::BAD_REQUEST,"Invalid data sent: "+jsonReader.getFormatedErrorMessages());
            HttpStatus status = service->post(jsonOut, jsonIn, id);
            
            out = jsonOut.toStyledString();
            return status;
        }

        if(method == "PUT")
        {
            cerr << "PUT request " << pattern << " with data: " << in << endl;
            Json::Reader jsonReader;
            Json::Value jsonIn;
            Json::Value jsonOut;
            if(!jsonReader.parse(in, jsonIn))
                throw ServiceException(HttpStatus::BAD_REQUEST,"Invalid data sent: "+jsonReader.getFormatedErrorMessages());
            HttpStatus status = service->put(jsonOut, jsonIn);

            out = jsonOut.toStyledString();
            return status;
        }

        if(method == "DELETE")
        {
            cerr << "DELETE request " << endl;
            HttpStatus status = service->remove(id);
            return status;
        }

        return HttpStatus::BAD_REQUEST;
    }
}
