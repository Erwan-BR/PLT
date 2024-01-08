#include "Observer.h"

namespace state{

    /// @brief Update the content of the observer (usefull for rendering). Has to be override.
    void Observer::update ()
    {
        return;
    }

    /// @brief Destructor of the observor class. Has to be override.
    Observer::~Observer()
    {
        return;
    }
}