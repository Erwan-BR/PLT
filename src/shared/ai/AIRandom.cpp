#include "./AIRandom.h"

#include <random>
#include <chrono>

namespace ai
{
    AIRandom::AIRandom () :
        Player()
    {

    }

    AIRandom::AIRandom (std::string name, int id, sf::Texture* profilePicture) :
        Player(name, id, profilePicture)
    {

    }
    AIRandom::~AIRandom ()
    {

    }

    void AIRandom::AIChooseDraftingCard ()
    {
        this->chooseDraftCard(0);
        this->state = state::PlayerState::PENDING;
    }

    void AIRandom::AIPlanification ()
    {
        for (int cardIndex = 7; 0 <= cardIndex; cardIndex++)
        {
            // Time-base seed to choose if the card is choose or not.
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
        this->state = state::PlayerState::PENDING;
    }

    void AIRandom::AIUseProducedResources ()
    {
        
    }
};