#include "CreateJSONFormatStructures.h"

namespace state
{
    Json::Value CreateJSONFormatStructures::jsonOfResourceToPay (const ResourceToPay resourceToPay) const
    {
        Json::Value jsonRepresentationOfResourceToPay;
        
        jsonRepresentationOfResourceToPay["type"] = static_cast<int>(resourceToPay.type);
        jsonRepresentationOfResourceToPay["isPaid"] = resourceToPay.isPaid;
        
        return jsonRepresentationOfResourceToPay;
    }

    Json::Value CreateJSONFormatStructures::jsonOfResourceToProduce (const ResourceToProduce resourceToProduce) const
    {
        Json::Value jsonRepresentationOfResourceToProduce;
        
        jsonRepresentationOfResourceToProduce["type"] = static_cast<int>(resourceToProduce.type);
        jsonRepresentationOfResourceToProduce["quantity"] = resourceToProduce.quantity;
        jsonRepresentationOfResourceToProduce["cardType"] = static_cast<int>(resourceToProduce.cardType);
        
        return jsonRepresentationOfResourceToProduce;
    }

    Json::Value CreateJSONFormatStructures::jsonOfCardVictoryPoint (const CardVictoryPoint victoryPoints) const
    {
        Json::Value jsonRepresentationOfCardVictoryPoint;
        
        jsonRepresentationOfCardVictoryPoint["numberOfPoints"] = victoryPoints.numberOfPoints;
        jsonRepresentationOfCardVictoryPoint["cardOrResourceType"] = victoryPoints.cardOrResourceType;
        
        return jsonRepresentationOfCardVictoryPoint;
    }

    ResourceToPay* CreateJSONFormatStructures::resourceToPayFromJSON (const Json::Value jsonInput) const
    {
        ResourceToPay* resourceToPay = new ResourceToPay{};

        resourceToPay->type = static_cast<ResourceType>(jsonInput["type"].asInt());
        resourceToPay->isPaid = jsonInput["isPaid"].asBool();

        return resourceToPay;
    }

    ResourceToProduce* CreateJSONFormatStructures::resourceToProduceFromJSON (const Json::Value jsonInput) const
    {
        ResourceToProduce* resourceToProduce = new ResourceToProduce{};

        resourceToProduce->type = static_cast<ResourceType>(jsonInput["type"].asInt());
        resourceToProduce->quantity = jsonInput["quantity"].asInt();
        resourceToProduce->cardType = static_cast<CardType>(jsonInput["cardType"].asInt());

        return resourceToProduce;
    }

    CardVictoryPoint* CreateJSONFormatStructures::cardVictoryPointFromJSON (const Json::Value jsonInput) const
    {
        CardVictoryPoint* cardVictoryPoint = new CardVictoryPoint{};

        cardVictoryPoint->numberOfPoints = jsonInput["numberOfPoints"].asInt();
        cardVictoryPoint->cardOrResourceType = jsonInput["cardOrResourceType"].asInt();

        return cardVictoryPoint;
    }
}