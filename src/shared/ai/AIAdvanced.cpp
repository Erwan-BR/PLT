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
                    resourcesToPay.push_back(card->getCostToBuild());
                    
                    this->chooseDraftCard(index);
                }
            }
            /*resourcesToPay.push_back(draftingCards[0]->getCostToBuild());
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
                AIAdvanced::AIUseProducedResources ();
            }
        }
    }

    void AIAdvanced::AIUseProducedResources ()
    {
        const std::vector<state::ResourceType> existingResources = {state::ResourceType::MATERIAL, state::ResourceType::ENERGY, state::ResourceType::SCIENCE, state::ResourceType::GOLD, state::ResourceType::EXPLORATION, state::ResourceType::KRYSTALLIUM, state::ResourceType::COLONEL, state::ResourceType::FINANCIER};
        std::vector<state::ResourceType> resourceToPlay;
        for (state::ResourceType resource : existingResources)
        {
            for (int i = 0; i < this->currentResources.at(resource); i++)
            {
                resourceToPlay.push_back(resource);
            }
        }
        
        
        
        for(state::ResourceType resource : resourceToPlay)
        {
            auto cardPosition = std::find(resourcesToPay.begin(), resourcesToPay.end(), resource);
            if( cardPosition == resourcesToPay.end())
            {
                this->sendResourceToEmpire(resource);
            }
            else
            {
                int cardIndex = cardPosition - resourcesToPay.begin();
                int resourceIndex = 0;
                for(std::vector<state::ResourceToPay*> cardCost : resourcesToPay)
                {
                    resourceIndex++;
                    auto resourcePosition = std::find(cardCost.begin(), cardCost.end(), resource);
                    if(resourcePosition != cardCost.end()) 
                    {
                        resourcesToPay[cardIndex].erase(resourcePosition);
                        break;
                    }
                }
                this->addResource(resource,cardIndex);
            }
        }
    }
    
    std::vector<int> AIAdvanced::findMaxVp() const
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

    std::vector<int> AIAdvanced::findMinVp() const
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

    int AIAdvanced::lowestCost() const
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

    int AIAdvanced::highestCost() const
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