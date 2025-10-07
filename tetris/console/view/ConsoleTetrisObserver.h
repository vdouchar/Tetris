#ifndef CONSOLETETRISOBSERVER_H
#define CONSOLETETRISOBSERVER_H

#include "../../metier/dp/Observer.h"
#include "../../metier/Tetris.h"

class Tetris;

/*!
 * \brief Observer class for observing and displaying Tetris game state on the console.
 */
class ConsoleTetrisObserver : public Observer{
    Tetris* subject_;

public:
    /*!
     * \brief Constructor for ConsoleTetrisObserver.
     * \param subject A pointer to the Tetris subject to observe.
     */
    ConsoleTetrisObserver(Tetris* subject);

    /*!
     * \brief Virtual destructor for ConsoleTetrisObserver.
     */
    virtual ~ConsoleTetrisObserver() override;

    /*!
     * \brief Implementation of the update method to display Tetris game state.
     * \param subject The subject that triggered the update.
     */
    void update() override;
};

#endif // CONSOLETETRISOBSERVER_H
