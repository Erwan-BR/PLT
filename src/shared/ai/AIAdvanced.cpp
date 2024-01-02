#include "./AIAdvanced.h"

namespace ai
{
    /// @brief Full constructor of AIAdvanced, with important information inside.
    /// @param name Name of the AI.
    /// @param id ID of the AI. Should be negative for engine methods.
    /// @param profilePicture Image of the profile picture of the AI.
    AIAdvanced::AIAdvanced (std::string name, int id, sf::Texture* profilePicture, state::Game* game) :
        Player(name, id, profilePicture),
        game(game),
        cardsToBuildIndexesOrdered({}),
        resourcesMissingOrdered({}),
        indexesOfCardsToKeep({})
    {
        missingResourcesToConstructAllCards[state::ResourceType::MATERIAL] = 0;
        missingResourcesToConstructAllCards[state::ResourceType::ENERGY] = 0;
        missingResourcesToConstructAllCards[state::ResourceType::SCIENCE] = 0;
        missingResourcesToConstructAllCards[state::ResourceType::GOLD] = 0;
        missingResourcesToConstructAllCards[state::ResourceType::EXPLORATION] = 0;
        missingResourcesToConstructAllCards[state::ResourceType::COLONEL] = 0;
        missingResourcesToConstructAllCards[state::ResourceType::FINANCIER] = 0;
    }
    
    /// @brief Destructor of the AIRandom class. Does not destruct anything for the moment.
    AIAdvanced::~AIAdvanced ()
    {

    }

    /// @brief Method used to implement how the AI choose it's card from the draft phase.
    void AIAdvanced::AIChooseDraftingCard()
    {
        // At turn one, the AI takes every possible cards that makes him win flatpoint.
        // For other turns, the AI takes a card only if he doesn't have any card to build left.
        if (1 == this->game->getTurn() || 0 == this->toBuildCards.size())
        {

        }
        // Taking a card only for the discard gain.
        else
        {
            // Iterating among all resources desired, by decreasing amount.
            for (const state::ResourceType resourceDesired : this->resourcesMissingOrdered)
            {
                // Iterating among all cards to try to have this resource.
                for (long unsigned int index = 0; this->draftingCards.size(); index++)
                {
                    state::ResourceType currentDiscardGain = this->draftingCards[index]->getDiscardGain();
                    if (resourceDesired == currentDiscardGain)
                    {
                        // Choose the card and specify that it won't be construct.
                        this->AIChooseCardFromIndex(index, false);
                        
                        // Update informations concerning the missing resources.
                        this->missingResourcesToConstructAllCards[currentDiscardGain] --;
                        this->updateResourcesMissingOrdered();
                        return ;
                    }
                }
            }

            // Should never be reached because cards all have discard gain, and all resources are in the vector.
            // Here only for security.
            this->AIChooseCardFromIndex(0, false);
        }
    }

    /// @brief Method used to implement how the AI choose it's card during the planification phase.
    void AIAdvanced::AIPlanification()
    {
        this->indexesOfCardsToKeep.clear();
    }

    /// @brief Method used to implement how the AI uses it's resources (during the planification with instantGains, and after each production).
    void AIAdvanced::AIUseProducedResources ()
    {
    }

    /// @brief Choose colonel if the quantity of colonel is superior or equal to the quantity of financier that the player needs.
    /// @return A boolean that indicate if the colonel is the most required.
    bool AIAdvanced::AIChooseColonelToken ()
    {
        bool isChoosingColonel = this->missingResourcesToConstructAllCards[state::ResourceType::COLONEL] > this->missingResourcesToConstructAllCards[state::ResourceType::FINANCIER];
        if (isChoosingColonel)
        {
            this->missingResourcesToConstructAllCards[state::ResourceType::COLONEL] --;
        }
        else
        {
            this->missingResourcesToConstructAllCards[state::ResourceType::FINANCIER] --;
        }
        return isChoosingColonel;
    }

    /// @brief Keep a card at a given index, and update resources needed.
    /// @param index Index of the card to keep from the draftingCards to the draftCards.
    /// @param isDesiredToBuild Boolean that state if the card is going to be construct or not.
    void AIAdvanced::AIChooseCardFromIndex (int index, bool isDesiredToBuild)
    {
        // Checking if the index is possible
        if (0 > index || this->draftingCards.size() < index)
        {
            return ;
        }

        // If the card is going to be constructed, we have to had the neede resources to the mapping and the index in the vector.
        if (isDesiredToBuild)
        {
            for (state::ResourceToPay* resourceToPay: this->draftingCards[index]->getCostToBuild())
            {
                this->missingResourcesToConstructAllCards[resourceToPay->type] ++;
            }

            // Writing the index in the vector of indexes of cards to build.
            this->indexesOfCardsToKeep.push_back(this->draftCards.size());
            
            this->updateCardsToBuildIndexesOrdered();
            this->updateResourcesMissingOrdered();
        }
        this->keepCard(index);
    }

    /// @brief 
    void AIAdvanced::updateCardsToBuildIndexesOrdered ()
    {

    }

    /// @brief 
    void AIAdvanced::updateResourcesMissingOrdered ()
    {

    }
};