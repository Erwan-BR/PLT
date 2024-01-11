#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Observable.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstObservableTest)
{
  {
    Observable* myFirstObservable = new Observable();

    Observer* testObserver = new Observer();
    myFirstObservable->addObserver(testObserver);
    myFirstObservable->notifyObservers(0);

    delete myFirstObservable;
  }
}

/* vim: set sw=2 sts=2 et : */