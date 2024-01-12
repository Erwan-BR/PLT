#include "GameService.h"
#include <string.h>

#include <iostream>

namespace server
{
    GameService::GameService () : AbstractService("/game"),
        playersString({"","","","",""}),
        turn(""),
        phase(""),
        isClockwise(""),
        isFaceA(""),
        resourceProducing(""),
        isTestingGame("")
    {
        for(int i=0; i<150; i++)deck.push_back("");
    }

    HttpStatus GameService::get (Json::Value& jsonOut, std::string sub_url, int id) const {
        std::cout << "getting game from server" << std::endl;
        Json::Reader reader;
        bool parsing = false;

        if(strcmp(sub_url.c_str(),"players") == 0)
        {
            parsing = reader.parse(playersString[id], jsonOut);
        }

        else if(strcmp(sub_url.c_str(),"turn") == 0)
        {
            parsing = reader.parse(turn, jsonOut);
        }

        else if(strcmp(sub_url.c_str(),"phase") == 0)
        {
            parsing = reader.parse(phase, jsonOut);
        }

        else if(strcmp(sub_url.c_str(),"deck") == 0)
        {
            parsing = reader.parse(deck[id], jsonOut);
            std::cout << parsing << std::endl;
        }

        else if(strcmp(sub_url.c_str(),"isClockwise") == 0)
        {
            parsing = reader.parse(isClockwise, jsonOut);
        }

        else if(strcmp(sub_url.c_str(),"isFaceA") == 0)
        {
            parsing = reader.parse(isFaceA, jsonOut);
        }

        else if(strcmp(sub_url.c_str(),"resourceProducing") == 0)
        {
            parsing = reader.parse(resourceProducing, jsonOut);
        }

        else if(strcmp(sub_url.c_str(),"isTestingGame") == 0)
        {
            parsing = reader.parse(isTestingGame, jsonOut);
        }

        if(!parsing)
        {
            std::cout << "Failed to parse." << std::endl;
            return HttpStatus::SERVER_ERROR;
        }
        return HttpStatus::OK;
    }

    HttpStatus GameService::post (Json::Value& jsonOut, const Json::Value& jsonIn, std::string sub_url, int id) {
        std::cout << "posting game on server" << std::endl;

        if(strcmp(sub_url.c_str(),"players") == 0)
        {
            playersString[id] = jsonIn.toStyledString();
        }

        else if(strcmp(sub_url.c_str(),"turn") == 0)
        {
            turn = jsonIn.toStyledString();
            std::cout << turn << std::endl;
        }

        else if(strcmp(sub_url.c_str(),"phase") == 0)
        {
            phase = jsonIn.toStyledString();
            std::cout << phase << std::endl;
        }

        else if(strcmp(sub_url.c_str(),"deck") == 0)
        {
            deck[id] = jsonIn.toStyledString();
        }

        else if(strcmp(sub_url.c_str(),"isClockwise") == 0)
        {
            isClockwise = jsonIn.toStyledString();
            std::cout << isClockwise << std::endl;
        }

        else if(strcmp(sub_url.c_str(),"isFaceA") == 0)
        {
            isFaceA = jsonIn.toStyledString();
            std::cout << isFaceA << std::endl;
        }

        else if(strcmp(sub_url.c_str(),"resourceProducing") == 0)
        {
            resourceProducing = jsonIn.toStyledString();
            std::cout << resourceProducing << std::endl;
        }

        else if(strcmp(sub_url.c_str(),"isTestingGame") == 0)
        {
            isTestingGame = jsonIn.toStyledString();
            std::cout << isTestingGame << std::endl;
        }

        return HttpStatus::OK;
    }
}
