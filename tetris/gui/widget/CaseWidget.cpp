#include <iostream>
#include "CaseWidget.h"
#include <QPainter>

CaseWidget::CaseWidget(QWidget *parent) : QWidget(parent)
{
    m_color = Qt::white; // Default color
}

void CaseWidget::setColor(const QColor &color)
{
    m_color = color;
    update(); // Update view
}

void CaseWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), m_color); // Apply color on widget
}

CaseWidget::~CaseWidget()
{
    //Case widget destroyed at the end of the program
    std::cout << "Destruct case" << std::endl;
}
