#include "./AIAdvanced.h"

namespace ai
{
    /// @brief Empty construtor of AIAdvanced. Should never be used.
    AIAdvanced::AIAdvanced () :
        Player("AIAdvanced", -1, new sf::Texture())
    {

    }

    /// @brief Full constructor of AIAdvanced, with important information inside.
    /// @param name Name of the AI.
    /// @param id ID of the AI. Should be negative for engine methods.
    /// @param profilePicture Image of the profile picture of the AI.
    AIAdvanced::AIAdvanced (std::string name, int id, sf::Texture* profilePicture, state::Game* game) :
        Player(name, id, profilePicture),
        game(game)
    {

    }
    
    /// @brief Destructor of the AIRandom class. Does not destruct anything for the moment.
    AIAdvanced::~AIAdvanced ()
    {

    }

    /// @brief Method used to implement how the AI choose it's card from the draft phase.
    void AIAdvanced::AIChooseDraftingCard()
    {
        std::vector<state::ResourceType> resourcesUnitToPay;
        if(1 == this->game->getTurn())
        {
            bool isACardFound = false;
            for(long unsigned int index = 0; index < this->draftingCards.size(); index++)
            {
                state::DevelopmentCard* card = this->draftingCards[index];
                
                // Checking if card allows to win flatpoint only
                if(((int) state::CardType::NONETYPE == card->getVictoryPoints()->cardOrResourceType) && (0 < card->getVictoryPoints()->numberOfPoints))
                {
                    for (state::ResourceToPay* resourceToPay : card->getCostToBuild())
                    {
                        state::ResourceType resource = resourceToPay->type;
                        resourcesUnitToPay.push_back(resource);
                    }
                    
                    this->chooseDraftCard(index);

                    isACardFound = true;
                }
            }

            if (! isACardFound)
            {
                for (state::ResourceToPay* resourceToPay : this->draftingCards[0]->getCostToBuild())
                {
                    state::ResourceType resource = resourceToPay->type;
                    resourcesUnitToPay.push_back(resource);
                }
                this->chooseDraftCard(0);
            }
        }
        else
        {   
            for(long unsigned int index = 0; index < this->draftingCards.size(); index++)
            {
                state::DevelopmentCard* card = this->draftingCards[index];
                state::ResourceType resource = card->getDiscardGain();
                if(std::find(resourcesUnitToPay.begin(), resourcesUnitToPay.end(), resource) < resourcesUnitToPay.end())
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

    /// @brief Method used to implement how the AI choose it's card during the planification phase.
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

    /// @brief Method used to implement how the AI uses it's resources (during the planification with instantGains, and after each production).
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
            auto resourcePosition = std::find(resourceToPlay.begin(), resourceToPlay.end(), resource);
            if(resourceToPlay.end() == resourcePosition)
            {
                this->sendResourceToEmpire(resource);
            }
            else
            {
                // Non-sense in the following code, the index of the card is searched from the position of the resource in the vector ?
                // To correct.
                
                /*int cardIndex = resourcePosition - resourcesToPay.begin();
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
                this->addResource(resource,cardIndex);*/
            }
        }
    }
    
    std::vector<int> AIAdvanced::findMaxVp() const
    {
        int max = this->draftingCards[0]->getVictoryPoints()->numberOfPoints;
        int index = 0;

        for (long unsigned int i = 1; i < draftingCards.size(); ++i)
        {
            if (this->draftingCards[i]->getVictoryPoints()->numberOfPoints > max)
            {
                max = this->draftingCards[i]->getVictoryPoints()->numberOfPoints;
                index = i;
            }
        }
        std::vector<int> returnedValue = {max, index};
        return returnedValue;
    }

    std::vector<int> AIAdvanced::findMinVp() const
    {
        int min = this->draftingCards[0]->getVictoryPoints()->numberOfPoints;
        int index = 0;

        for (long unsigned int i = 1; i < draftingCards.size(); ++i)
        {
            if (this->draftingCards[i]->getVictoryPoints()->numberOfPoints < min)
            {
                min = this->draftingCards[i]->getVictoryPoints()->numberOfPoints;
                index = i;
            }
        }
        std::vector<int> returnedValue = {min, index};
        return returnedValue;
    }

    int AIAdvanced::lowestCost() const
    {
        long unsigned int cost = this->draftingCards[0]->getCostToBuild().size();
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
        long unsigned int cost = this->draftingCards[0]->getCostToBuild().size();
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