/** 
 * @file ServicesManager.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include <json/json.h>
#include <iostream>

#include "ServiceException.h"
#include <stdexcept>
#include <string>

using std::string;
#include "AbstractService.h"

#include <memory>
#include <iostream>
#include <vector>

using std::vector;
using std::unique_ptr;

template<class T,typename ... Args>
std::unique_ptr<T> make_unique(Args ... args) {
    return std::unique_ptr<T>(new T(args ...));
}

#include "ServicesManager.h"
#include <string.h>
#include <unistd.h>

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
        string sub_url = ""; 
        int id = 0;

        std::cout << url << std::endl;

        if(url.size() > pattern.size())
        {
            sub_url = url.substr(pattern.size());
            if(sub_url[0] != '/')throw ServiceException(HttpStatus::BAD_REQUEST,"Wrong URL, try <service>/<id>");
            sub_url = sub_url.substr(1);
            if(sub_url.empty())throw ServiceException(HttpStatus::BAD_REQUEST,"Wrong URL, try <service>/<sub_service>(/id)");

            string ssub_url = sub_url;
            while((ssub_url[0] != '/') && (ssub_url.size() != 0))ssub_url = ssub_url.substr(1);
            
            if(ssub_url.empty())id=0;
            else
            {
                while(sub_url[sub_url.size()-1] != '/')sub_url = sub_url.substr(0,sub_url.size()-1);
                sub_url = sub_url.substr(0,sub_url.size()-1);
                ssub_url = ssub_url.substr(1);
                if(ssub_url.empty())throw ServiceException(HttpStatus::BAD_REQUEST,"Wrong URL, try <service>/<sub_service>(/id)");
                id = atoi(ssub_url.c_str());
            }
            std::cout << sub_url << std::endl;
            std::cout << ssub_url << std::endl;
  
            std::cout << id << std::endl;        
        }

        if(method == "GET")
        {
            cerr << "GET request " << pattern << endl;
            Json::Value jsonOut;
            HttpStatus status = service->get(jsonOut, id);

            out = jsonOut.toStyledString();
            return status;
        }

        if(method == "POST")
        {
            cerr << "POST request " << pattern << endl;
            Json::Reader jsonReader;
            Json::Value jsonIn;
            Json::Value jsonOut;
            if(!jsonReader.parse(in, jsonIn))
                throw ServiceException(HttpStatus::BAD_REQUEST,"Invalid data sent: "+jsonReader.getFormatedErrorMessages());
            HttpStatus status = service->post(jsonOut, jsonIn, sub_url, id);
            
            out = jsonOut.toStyledString();
            return status;
        }

        if(method == "PUT")
        {
            cerr << "PUT request " << pattern << endl;
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

        else std::cout << method << std::endl;

        return HttpStatus::BAD_REQUEST;
    }
}
