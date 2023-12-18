#include "./AIAdvanced.h"

namespace ai
{
    AIAdvanced::AIAdvanced () :
        Player("AIAdvanced", 20, new sf::Texture())
    {

    }

    AIAdvanced::AIAdvanced (std::string name, int id, sf::Texture* profilePicture, state::Game* game) :
        Player(name, id, profilePicture),
        game(game)
    {

    }
    AIAdvanced::~AIAdvanced ()
    {

    }

    void AIAdvanced::AIChooseDraftingCard()
    {
        if(1 == this->game->getTurn())
        {   
            for(long unsigned int index = 0; index < this->draftingCards.size(); index++)
            {
                state::DevelopmentCard* card = this->draftingCards[index];
                if(card->getVictoryPoints()->cardOrResourceType == state::NONETYPE and 0 < card->getVictoryPoints()->numberOfPoints)
                {
                    for(state::ResourceToPay* resource : card->getCostToBuild())
                    {
                        resourcesToPay.push_back(resource);
                    }
                    this->chooseDraftCard(index);
                }
            }
            /*for(state::ResourceToPay* resource : this->draftingCards[0]->getCostToBuild())
                {
                    resourcesToPay.push_back(resource);
                }*/
            this->chooseDraftCard(0);
        }
        else
        {   
            for(long unsigned int index = 0; index<this->draftingCards.size();index++)
            {
                state::DevelopmentCard* card = this->draftingCards[index];
                state::ResourceType resource = card->getDiscardGain();
                if(std::find(resourcesToPay.begin(), resourcesToPay.end(), resource) < resourcesToPay.end())
                {
                    this->chooseDraftCard(index);
                }
                else
                {
                    this->chooseDraftCard(0);
                }
            }
        }

    }

    void AIAdvanced::AIPlanification()
    {
        for(long unsigned int index = 0; index<this->draftingCards.size();index++)
        {
            if(1 == game->getTurn())
            {
                this->keepCard(index);
            }
            else
            {
                this->discardCard(index,true);
            }
        }
    }

    void AIAdvanced::AIUseProducedResources ()
    {
        /*for(state::ResourceType resource : this->currentResources)
        {
            auto resourcePosition = std::find(resourcesToPay.begin(), resourcesToPay.end(), resource);

            this->addResource(resource,resourcePosition);
        }*/
    }
    
    std::vector<int> AIAdvanced::findMaxVp()
    {
        int max = this->draftingCards[0]->getVictoryPoints()->numberOfPoints;
        int index = 0;

        for (int i = 1; i < draftingCards.size(); ++i) {
            if (this->draftingCards[i]->getVictoryPoints()->numberOfPoints > max) {
                max = this->draftingCards[i]->getVictoryPoints()->numberOfPoints;
                index = i;
            }
        }
        return (std::vector(max, index));
    }

    std::vector<int> AIAdvanced::findMinVp()
    {
        int min = this->draftingCards[0]->getVictoryPoints()->numberOfPoints;
        int index = 0;

        for (int i = 1; i < draftingCards.size(); ++i) {
            if (this->draftingCards[i]->getVictoryPoints()->numberOfPoints < min) {
                min = this->draftingCards[i]->getVictoryPoints()->numberOfPoints;
                index = i;
            }
        }
        return (std::vector(min, index));
    }

    int AIAdvanced::lowestCost()
    {
        int cost = this->draftingCards[0]->getCostToBuild().size();
        int index,counter = 0;
        for(state::DevelopmentCard* card : this->draftingCards)
        {
            counter++;
            if(card->getCostToBuild().size() < cost)
            {
                index = counter;
            }
        }
        return index;
    }

    int AIAdvanced::highestCost()
    {
        int cost = this->draftingCards[0]->getCostToBuild().size();
        int index,counter = 0;
        for(state::DevelopmentCard* card : this->draftingCards)
        {
            counter++;
            if(card->getCostToBuild().size() > cost)
            {
                index = counter;
            }
        }
        return index;
    }
};