#ifndef COLOR_H
#define COLOR_H

#include <QColor>

/**
 * @brief The Color class provides methods for obtaining QColor objects representing specific colors.
 *
 * This class contains static methods to retrieve QColor objects for predefined colors used in the application.
 */
class Color {
private:
    /**
     * @brief Pre-defined constant for the Red color.
     */
    static constexpr QRgb Red = 0xFF0000;

    /**
     * @brief Pre-defined constant for the Green color.
     */
    static constexpr QRgb Green = 0x00FF00;

    /**
     * @brief Pre-defined constant for the Blue color.
     */
    static constexpr QRgb Blue = 0x0000FF;

    /**
     * @brief Pre-defined constant for the Yellow color.
     */
    static constexpr QRgb Yellow = 0xFFFF00;

    /**
     * @brief Pre-defined constant for the Purple color.
     */
    static constexpr QRgb Purple = 0x800080;

    /**
     * @brief Pre-defined constant for the Cyan color.
     */
    static constexpr QRgb Cyan = 0x00FFFF;

    /**
     * @brief Pre-defined constant for the Orange color.
     */
    static constexpr QRgb Orange = 0xFFA500;
public:
    /**
     * @brief Gets the QColor object corresponding to the specified color index.
     *
     * @param n The index of the color to retrieve.
     * @return The QColor object representing the specified color.
     */
    static QColor getColor(int n);
};

#endif // COLOR_H
