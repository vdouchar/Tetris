#include "Color.h"

QColor Color::getColor(int n) {
    switch(n) {
        case 1: return QColor(Red);
        case 2: return QColor(Green);
        case 3: return QColor(Blue);
        case 4: return QColor(Yellow);
        case 5: return QColor(Purple);
        case 6: return QColor(Cyan);
        case 7: return QColor(Orange);
        default: return Qt::white; // default color
    }
}
