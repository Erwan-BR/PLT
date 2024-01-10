#include "GameService.hpp"

namespace server
{
    GameService::GameService () : AbstractService("/game"),
        playersString({"","","","",""}),
        gameString("")
    {
    }

    HttpStatus GameService::get (Json::Value& jsonOut, int id) const {
        std::cout << "getting game from server" << std::endl;
        Json::Reader reader;
        bool parsing = reader.parse(playersString[id], jsonOut);
        if(!parsing)
        {
            std::cout << "Failed to parse." << std::endl;
            return HttpStatus::SERVER_ERROR;

        }
        return HttpStatus::OK;
    }

    HttpStatus GameService::post (Json::Value& jsonOut, const Json::Value& jsonIn, string sub_url, int id) {
        std::cout << "posting game on server" << std::endl;
        playersString[id] = jsonIn.toStyledString();
        return HttpStatus::OK;
    }
}
