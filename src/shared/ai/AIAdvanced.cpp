#include "./AIAdvanced.h"

#include "limits"

namespace ai
{
    /// @brief Full constructor of AIAdvanced, with important information inside.
    /// @param name Name of the AI.
    /// @param id ID of the AI. Should be negative for engine methods.
    AIAdvanced::AIAdvanced (std::string name, int id) :
        Player(name, id)
    {
        this->initMissingResources();
    }

    /// @brief Full constructor of AIAdvanced, with important information inside.
    /// @param name Name of the AI.
    /// @param id ID of the AI. Should be negative for engine methods.
    /// @param relativePathOfTexture Relative path of the profile picture.
    AIAdvanced::AIAdvanced (std::string name, int id, std::string relativePathOfTexture) :
        Player(name, id, relativePathOfTexture)
    {
        this->initMissingResources();
    }
    
    /// @brief Destructor of the AIRandom class. Does not destruct anything for the moment.
    AIAdvanced::~AIAdvanced ()
    {

    }

    void AIAdvanced::initMissingResources()
    {
        missingResourcesToConstructAllCards[state::ResourceType::MATERIAL] = 0;
        missingResourcesToConstructAllCards[state::ResourceType::ENERGY] = 0;
        missingResourcesToConstructAllCards[state::ResourceType::SCIENCE] = 0;
        missingResourcesToConstructAllCards[state::ResourceType::GOLD] = 0;
        missingResourcesToConstructAllCards[state::ResourceType::EXPLORATION] = 0;
        missingResourcesToConstructAllCards[state::ResourceType::COLONEL] = 0;
        missingResourcesToConstructAllCards[state::ResourceType::FINANCIER] = 0;
    }

    /// @brief Method used to implement how the AI choose it's card from the draft phase.
    void AIAdvanced::AIChooseDraftingCard()
    {
        // If it's the first draft from a turn, we have to substract the production gain from the resources to obtain. 
        if (0 == this->currentIndexOfDraft)
        {
            this->substractProductionGainToNeededResources();
            this->gameTurn ++;
        }

        // At turn one, the AI takes every possible cards that makes him win flatpoint.
        // For other turns, the AI takes a card only if he doesn't have any card to build left.
        if (1 == this->gameTurn || 0 == this->toBuildCards.size())
        {
            int indexOfCardToKeep = 0;
            long unsigned int costOfCardToBuid = std::numeric_limits<long unsigned int>::max();
            bool isDesiredCard = false;
            
            // Iterating among all cards to find the one that will earn flat points (without condition), an d which is the less expensive.
            for (long unsigned int index = 0; this->draftingCards.size() > index; index ++)
            {
                state::CardVictoryPoint* currentVictoryPoints = this->draftingCards[index]->getVictoryPoints();
                
                // Searching a card that earns flat points.
                if ((0 < currentVictoryPoints->numberOfPoints) && (0 == (int) currentVictoryPoints->cardOrResourceType))
                {
                    // Changing card only if it cost less to build.
                    if (this->draftingCards[index]->getCostToBuild().size() < costOfCardToBuid)
                    {
                        indexOfCardToKeep = index;
                        costOfCardToBuid = this->draftingCards[index]->getCostToBuild().size();
                        isDesiredCard = true;
                    }
                }
            }

            // After all iterations, we can keep the selected card, and store the information in the associated vector.
            this->AIKeepCardFromIndex(indexOfCardToKeep, isDesiredCard);
            if (isDesiredCard)
            {
                this->indexesOfCardsToKeep.push_back(this->currentIndexOfDraft);
            }
            else
            {
                this->indexesOfCardsToDiscard.push_back(this->currentIndexOfDraft);
            }

            this->currentIndexOfDraft ++;
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
                        this->AIKeepCardFromIndex(index, false);
                        
                        // Update informations concerning the missing resources.
                        this->missingResourcesToConstructAllCards[currentDiscardGain] --;
                        this->updateResourcesMissingOrdered();

                        // Note the card to discard.
                        this->indexesOfCardsToDiscard.push_back(this->currentIndexOfDraft);
                        this->currentIndexOfDraft ++;
                        return ;
                    }
                }
            }

            // Should never be reached because cards all have discard gain, and all resources are in the vector.
            // Here only for security.
            this->AIKeepCardFromIndex(0, false);
            this->indexesOfCardsToDiscard.push_back(this->currentIndexOfDraft);
            this->currentIndexOfDraft ++;
        }
    }

    /// @brief Method used to implement how the AI choose it's card during the planification phase.
    void AIAdvanced::AIPlanification()
    {
        this->currentIndexOfDraft = 0;

        // Keeping cards that are written as 'to keep'
        for (int cardToKeep : this->indexesOfCardsToKeep)
        {
            this->keepCard(cardToKeep);
        }
        this->indexesOfCardsToKeep.clear();

        // Keeping cards that are written as 'to discard'
        for (int cardToKeep : this->indexesOfCardsToDiscard)
        {
            this->discardCard(cardToKeep, true);
            this->AIUseProducedResources();
        }
        this->indexesOfCardsToDiscard.clear();

        this->endPlanification();
    }

    /// @brief Method used to implement how the AI uses it's resources (during the planification with instantGains, and after each production).
    void AIAdvanced::AIUseProducedResources ()
    {
        // Iterating among all resources that needs to be used.
        for (const auto& pair : this->currentResources)
        {
            // Iterating among all resources of the current type.
            for (int resourceIndex = 0; pair.second > resourceIndex; resourceIndex++)
            {
                // Checking if the resource can be played. If the resource is playable, play it on the most needed card.
                if (this->isResourcePlayable(pair.first))
                {
                    for (long unsigned int index = 0; this->toBuildCards.size() > index ; index ++)
                    {
                        // Taking the first card that needs this resource.
                        if (this->toBuildCards[index]->isResourceAddable(pair.first))
                        {
                            this->addResource(pair.first, (int)index);
                            this->updateCardsToBuildIndexesOrdered();
                            break;
                        }
                    }
                }
                else
                {
                    this->sendResourceToEmpire(pair.first);
                }
            }
        }
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

        // Update resources needed.
        this->updateResourcesMissingOrdered();

        return isChoosingColonel;
    }

    /// @brief Keep a card at a given index, and update resources needed.
    /// @param index Index of the card to keep from the draftingCards to the draftCards.
    /// @param isDesiredToBuild Boolean that state if the card is going to be construct or not.
    void AIAdvanced::AIKeepCardFromIndex (int index, bool isDesiredToBuild)
    {
        // Checking if the index is possible
        if ((0 > index) || (this->draftingCards.size() < (long unsigned int) index))
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
        }
        // Not desired to build : we will receive one resource by discarding this card. 
        else
        {
            this->missingResourcesToConstructAllCards[this->draftingCards[index]->getDiscardGain()] --;
        }
        // Update resources needed.
        this->updateCardsToBuildIndexesOrdered();
        this->updateResourcesMissingOrdered();
        this->keepCard(index);
    }

    /// @brief Update the order of the card to build to know which caard the AI should try to construct first.
    void AIAdvanced::updateCardsToBuildIndexesOrdered ()
    {
        this->cardsToBuildIndexesOrdered.clear();

        for (long unsigned int index = 0; this->toBuildCards.size() < index; index++)
        {
            this->cardsToBuildIndexesOrdered.push_back(index);
        }
        
        // Sorting values
        // Sort indices based on AICompareDevelopmentCards using the custom comparison function
        std::sort(this->cardsToBuildIndexesOrdered.begin(), this->cardsToBuildIndexesOrdered.end(), [&](size_t i, size_t j) {
            return this->AICompareDevelopmentCards(*(this->toBuildCards[i]), *(this->toBuildCards[j]));
        });
    }

    /// @brief Update the resource vector that states which resources are the most needed.
    void AIAdvanced::updateResourcesMissingOrdered ()
    {
        this->resourcesMissingOrdered.clear();

        const std::vector<state::ResourceType> resourceToSort = {state::ResourceType::MATERIAL, state::ResourceType::ENERGY, state::ResourceType::SCIENCE, state::ResourceType::GOLD, state::ResourceType::EXPLORATION, state::ResourceType::COLONEL, state::ResourceType::FINANCIER};

        // Iterating among all resources to sort.
        for (state::ResourceType resource : resourceToSort)
        {
            bool isPlaced = false;
            // Iterating among all sorted resourceS.
            for (long unsigned int index = 0; this->resourcesMissingOrdered.size() > index; index++)
            {
                // If an ordered resources is less needed than the one we are looking, it's the moment to place the new resource.
                if (this->resourcesMissingOrdered[index] < missingResourcesToConstructAllCards.at(resource))
                {
                    this->resourcesMissingOrdered.insert(this->resourcesMissingOrdered.begin() + index, resource);
                    isPlaced = true;
                    break;
                }
            }
            // If the resource is not placed, it means that it is less required than every other resources.
            if (! isPlaced)
            {
                this->resourcesMissingOrdered.push_back(resource);
            }
        }
    }

    /// @brief Substract to the needed resources the quantity that is produced by the AI. Use at the beginning of each draft to avoid taking a token that will be produced anyway.
    void AIAdvanced::substractProductionGainToNeededResources ()
    {
        for (const auto& pair : this->resourcesProduction)
        {
            this->missingResourcesToConstructAllCards[pair.first] = this->missingResourcesToConstructAllCards[pair.first] - pair.second;
        }

        // Update resources needed.
        this->updateCardsToBuildIndexesOrdered();
        this->updateResourcesMissingOrdered();
    }

    // Function use to compare how to choose which developmentCard is to build first. Can be customize as wanted.
    bool AIAdvanced::AICompareDevelopmentCards (const state::DevelopmentCard& card1, const state::DevelopmentCard& card2) const
    {
        return card1.getQuantityResourcesMissing() > card2.getQuantityResourcesMissing();
    }
};