#ifndef OBSERVABLE_H
#define OBSERVABLE_H


#include <set>

// Forward declaration
class Observer;

/*!
 * \brief The Observable class represents an object that can be observed by other objects.
 *
 * This class provides functionality for managing a list of observers and notifying them when
 * changes occur in the observed object.
 */
class Observable
{
public:
    /*!
    \brief Default virtual destructor for polymorphic use.
    */
    virtual ~Observable() = default;

    /*!
    \brief Method for an observer to register as a listener of the subject of observation.
    \param observer A pointer to the candidate observer.
    */
    void registerObserver(Observer * observer);

    /*!
    \brief Method for an observer to unregister from the list of patent listeners of the subject of observation.
    \param observer The address of the disinterested observer.
    */
    void unregisterObserver(Observer * observer);

    /*!
     * \brief Method responsible for notifying observers of a change in the state of the subject of observation, by invoking their Observer::update() method.
     *
     * \sa Observer::update(const Subject *).
     */
    void notifyObservers() const noexcept;

private:
    /*!
     * \brief The set of registered observers.
     */
    std::set<Observer *> _observers;
};


#endif // OBSERVABLE_H
