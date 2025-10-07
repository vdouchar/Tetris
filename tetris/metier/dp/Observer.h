#ifndef OBSERVER_H
#define OBSERVER_H

/*!
 * \brief The Observer class represents an object that observes changes in another object.
 *
 * This class provides an interface for concrete observer classes to implement.
 */
class Observer
{
public:
    /*!
    * \brief Default virtual destructor for polymorphic use.
    */
    virtual ~Observer() = default;

    /**
     * @brief Pure virtual function to be implemented by concrete observers.
     *
     * This function is called by observable objects to notify the observer of changes.
     */
    virtual void update() = 0;
};

#endif // OBSERVER_H
