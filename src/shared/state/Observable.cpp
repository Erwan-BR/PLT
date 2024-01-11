#include "Observable.h"

namespace state{
    
    /// @brief Construct an Observable with an empty vector
    Observable::Observable()
    {
    }

    /// @brief Destructor of the observable class. Delete nothing for the moment because pointers can be shared.
    Observable::~Observable()
    {
    }

    /// @brief Add an observer to this observable object.
    /// @param observerToAdd Observer to add to the vector.
    void Observable::addObserver(Observer* observerToAdd)
    {
        this->observers.push_back(observerToAdd);
    }

    /// @brief Notify all observers that the current Observable has a significant change.
    void Observable::notifyObservers(long flags) const
    {
        for(Observer* observer : this->observers)
        {
            observer->update(flags);
        }
    }
}