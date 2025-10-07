/*!
* \file Observable.cpp
*/

#include "Observable.h"
#include "Observer.h"

void Observable::registerObserver(Observer * observer)
{
    _observers.insert(observer);
}

void Observable::unregisterObserver(Observer * observer)
{
    _observers.erase(observer);
}

void Observable::notifyObservers() const noexcept
{
    for (Observer * observer : _observers)
    {
        observer->update();
    }
}
