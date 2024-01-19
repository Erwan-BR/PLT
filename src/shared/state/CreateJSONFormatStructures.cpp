#include "CreateJSONFormatStructures.h"

namespace state
{
    Json::Value CreateJSONFormatStructures::jsonOfResourceToPay (const ResourceToPay resourceToPay)
    {
        Json::Value jsonRepresentationOfResourceToPay;
        
        jsonRepresentationOfResourceToPay["type"] = static_cast<int>(resourceToPay.type);
        jsonRepresentationOfResourceToPay["isPaid"] = resourceToPay.isPaid;
        
        return jsonRepresentationOfResourceToPay;
    }

    Json::Value CreateJSONFormatStructures::jsonOfResourceToProduce (const ResourceToProduce resourceToProduce)
    {
        Json::Value jsonRepresentationOfResourceToProduce;
        
        jsonRepresentationOfResourceToProduce["type"] = static_cast<int>(resourceToProduce.type);
        jsonRepresentationOfResourceToProduce["quantity"] = resourceToProduce.quantity;
        jsonRepresentationOfResourceToProduce["cardType"] = static_cast<int>(resourceToProduce.cardType);
        
        return jsonRepresentationOfResourceToProduce;
    }

    Json::Value CreateJSONFormatStructures::jsonOfCardVictoryPoint (const CardVictoryPoint victoryPoints)
    {
        Json::Value jsonRepresentationOfCardVictoryPoint;
        
        jsonRepresentationOfCardVictoryPoint["numberOfPoints"] = victoryPoints.numberOfPoints;
        jsonRepresentationOfCardVictoryPoint["cardOrResourceType"] = victoryPoints.cardOrResourceType;
        
        return jsonRepresentationOfCardVictoryPoint;
    }

    constants::resourcePayPtr CreateJSONFormatStructures::resourceToPayFromJSON (const Json::Value jsonInput)
    {
        constants::resourcePayPtr resourceToPay = std::make_shared<ResourceToPay>();

        resourceToPay->type = static_cast<ResourceType>(jsonInput["type"].asInt());
        resourceToPay->isPaid = jsonInput["isPaid"].asBool();

        return resourceToPay;
    }

    constants::resourceProdPtr CreateJSONFormatStructures::resourceToProduceFromJSON (const Json::Value jsonInput)
    {
        constants::resourceProdPtr resourceToProduce = std::make_shared<ResourceToProduce>();

        resourceToProduce->type = static_cast<ResourceType>(jsonInput["type"].asInt());
        resourceToProduce->quantity = jsonInput["quantity"].asInt();
        resourceToProduce->cardType = static_cast<CardType>(jsonInput["cardType"].asInt());

        return resourceToProduce;
    }

    constants::victoryPointsPtr CreateJSONFormatStructures::cardVictoryPointFromJSON (const Json::Value jsonInput)
    {
        constants::victoryPointsPtr cardVictoryPoint = std::make_shared<CardVictoryPoint>();

        cardVictoryPoint->numberOfPoints = jsonInput["numberOfPoints"].asInt();
        cardVictoryPoint->cardOrResourceType = jsonInput["cardOrResourceType"].asInt();

        return cardVictoryPoint;
    }
}