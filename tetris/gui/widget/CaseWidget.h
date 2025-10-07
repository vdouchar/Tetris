#ifndef CASEWIDGET_H
#define CASEWIDGET_H

#include <QWidget>

/**
 * @brief The CaseWidget class represents a widget for displaying a colored case.
 *
 * This class inherits from QWidget and provides functionality to set and display a color.
 */
class CaseWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a CaseWidget object with the given parent.
     * @param parent The parent widget.
     */
    explicit CaseWidget(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the CaseWidget class.
     */
    ~CaseWidget();

    /**
     * @brief Sets the color of the case.
     * @param color The color to set.
     */
    void setColor(const QColor &color);

protected:
    /**
     * @brief Paints the case widget with the assigned color.
     * @param event The paint event.
     */
    void paintEvent(QPaintEvent *event) override;

private:
    QColor m_color; /**< The color of the case. */
};

#endif // CASEWIDGET_H
