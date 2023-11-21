#include "Observable.h"

using namespace state;

namespace state{
    Observable::Observable(){
    }

    Observable::~Observable(){

    }

    void Observable::addObserver(Observer* observerToAdd){
        this->observers.push_back(observerToAdd);
    }

    void Observable::notifyObservers() const{
        for(Observer* observer : this->observers){
            (*observer).update();
        }
    }
}

