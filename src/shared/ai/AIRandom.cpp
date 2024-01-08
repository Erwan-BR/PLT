#include "./AIRandom.h"

#include <random>
#include <chrono>

namespace ai
{
    /// @brief Full constructor of AIRandom, with important information inside.
    /// @param name Name of the AI.
    /// @param id ID of the AI. Should be negative for engine methods.
    AIRandom::AIRandom (std::string name, int id) :
        Player(name, id)
    {

    }

    /// @brief Full constructor of AIRandom, with important information inside.
    /// @param name Name of the AI.
    /// @param id ID of the AI. Should be negative for engine methods.
    /// @param relativePathOfTexture Relative path of the profile picture.
    AIRandom::AIRandom (std::string name, int id, std::string relativePathOfTexture) :
        Player(name, id, relativePathOfTexture)
    {

    }
    
    /// @brief Destructor of the AIRandom class. Does not destruct anything for the moment.
    AIRandom::~AIRandom ()
    {

    }

    /// @brief Method used to implement how the AI choose it's card from the draft phase. It's completely random.
    void AIRandom::AIChooseDraftingCard ()
    {
        // Time-base seed to choose if the card is choosed or not.
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine randomness(seed);
        std::uniform_int_distribution<int> distribution(0, this->draftingCards.size() - 1);
        
        // Generate a random integer.
        int randomInt = distribution(randomness);
        this->chooseDraftCard(randomInt);
    }

    /// @brief Method used to implement how the AI choose it's card during the planification phase.
    void AIRandom::AIPlanification ()
    {
        for (int cardIndex = this->draftCards.size() - 1; 0 <= cardIndex; cardIndex--)
        {
            // Time-base seed to choose if the card is choosed or not.
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::default_random_engine randomness(seed);
            std::uniform_int_distribution<int> distribution(0, 1);
            
            // Generate a random boolean (false or true).
            bool randomBoolean = distribution(randomness);

            if (randomBoolean)
            {
                this->keepCard(cardIndex);
            }
            else
            {
                this->discardCard(cardIndex, true);
            }
        }
        this->AIUseProducedResources();
    }

    /// @brief Method used to implement how the AI uses it's resources (after the planification with instantGains, and after each production).
    void AIRandom::AIUseProducedResources ()
    {
        const int numberOfCardsToBuild = (const int) this->toBuildCards.size();
        // If no card to build, put all resources on the empire.
        if (0 == numberOfCardsToBuild)
        {
            this->sendAllResourcesToEmpire();
        }

        // Time-base seed to shuffle resources.
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine randomness(seed);
        
        const std::vector<state::ResourceType> existingResources = {state::ResourceType::MATERIAL, state::ResourceType::ENERGY, state::ResourceType::SCIENCE, state::ResourceType::GOLD, state::ResourceType::EXPLORATION, state::ResourceType::KRYSTALLIUM, state::ResourceType::COLONEL, state::ResourceType::FINANCIER};
        std::vector<state::ResourceType> resourceToPlay;
        for (state::ResourceType resource : existingResources)
        {
            for (int i = 0; i < this->currentResources.at(resource); i++)
            {
                resourceToPlay.push_back(resource);
            }
        }

        std::shuffle(resourceToPlay.begin(), resourceToPlay.end(), randomness);

        // Iterating among all resources that needs to be use.
        for (state::ResourceType currentResource : resourceToPlay)
        {
            // Check if the resource is not playable, to send it directly into the empire.
            if (this->isResourcePlayable(currentResource))
            {
                this->AIUseSingleResource(currentResource, numberOfCardsToBuild);
            }
            else
            {
                this->sendResourceToEmpire(currentResource);
            }
        }
        this->endProduction();
    }

    /// @brief Use a single resource to send it to a card. Called only if the resource is Playable.
    void AIRandom::AIUseSingleResource (state::ResourceType resource, int numberOfCardsToBuild)
    {
        // Time-base seed to choose the card that will be try to receive resource first.
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine randomness(seed);

        // Here, the resource is playable. Choose a random card to try playing on it.
        std::uniform_int_distribution<int> distribution(0, numberOfCardsToBuild - 1);
        
        // Generate a random integer.
        int randomCardPosition = distribution(randomness);

        // As long as we are here, the resource is addable. We just have to iterate a certain time to add it on a card.
        // For loop to avoid any mistakes, but it could be a while(true) loop.
        for (int index = 0; index < numberOfCardsToBuild; index++)
        {
            // If the resource can be added on this card, do it and quit the loop to add the next resource.
            if (this->toBuildCards[randomCardPosition]->isResourceAddable(resource))
            {
                this->addResource(resource, randomCardPosition);
                break;
            }
            // Getting the next card position, to add it on another card. Re-initialization of the position if it exceed the size of the vector.
            randomCardPosition ++;
            if (numberOfCardsToBuild == randomCardPosition)
            {
                randomCardPosition = 0;
            }
        }
    }

    /// @brief Choose randomly a token between colonel and financier.
    /// @return Random boolean.
    bool AIRandom::AIChooseColonelToken ()
    {
        // Time-base seed to choose if the card is choosed or not.
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine randomness(seed);
        std::uniform_int_distribution<int> distribution(0, 1);
        
        // Generate a random integer.
        int randomInt = distribution(randomness);
        
        return (bool) randomInt;
    }
};