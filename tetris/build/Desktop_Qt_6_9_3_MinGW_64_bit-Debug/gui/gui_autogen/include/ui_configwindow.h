/********************************************************************************
** Form generated from reading UI file 'configwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGWINDOW_H
#define UI_CONFIGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigWindow
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lvlLabel;
    QLineEdit *lvlEdit;
    QLabel *lvlErr;
    QLabel *rowLabel;
    QLineEdit *rowEdit;
    QLabel *rowErr;
    QLabel *colLabel;
    QLineEdit *colEdit;
    QLabel *colErr;
    QRadioButton *fillGrid;
    QPushButton *submitBtn;
    QLabel *configLabel;

    void setupUi(QDialog *ConfigWindow)
    {
        if (ConfigWindow->objectName().isEmpty())
            ConfigWindow->setObjectName("ConfigWindow");
        ConfigWindow->resize(400, 300);
        verticalLayoutWidget = new QWidget(ConfigWindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 30, 381, 261));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lvlLabel = new QLabel(verticalLayoutWidget);
        lvlLabel->setObjectName("lvlLabel");

        verticalLayout->addWidget(lvlLabel);

        lvlEdit = new QLineEdit(verticalLayoutWidget);
        lvlEdit->setObjectName("lvlEdit");
        lvlEdit->setAutoFillBackground(false);

        verticalLayout->addWidget(lvlEdit);

        lvlErr = new QLabel(verticalLayoutWidget);
        lvlErr->setObjectName("lvlErr");

        verticalLayout->addWidget(lvlErr);

        rowLabel = new QLabel(verticalLayoutWidget);
        rowLabel->setObjectName("rowLabel");

        verticalLayout->addWidget(rowLabel);

        rowEdit = new QLineEdit(verticalLayoutWidget);
        rowEdit->setObjectName("rowEdit");

        verticalLayout->addWidget(rowEdit);

        rowErr = new QLabel(verticalLayoutWidget);
        rowErr->setObjectName("rowErr");

        verticalLayout->addWidget(rowErr);

        colLabel = new QLabel(verticalLayoutWidget);
        colLabel->setObjectName("colLabel");

        verticalLayout->addWidget(colLabel);

        colEdit = new QLineEdit(verticalLayoutWidget);
        colEdit->setObjectName("colEdit");

        verticalLayout->addWidget(colEdit);

        colErr = new QLabel(verticalLayoutWidget);
        colErr->setObjectName("colErr");

        verticalLayout->addWidget(colErr);

        fillGrid = new QRadioButton(verticalLayoutWidget);
        fillGrid->setObjectName("fillGrid");

        verticalLayout->addWidget(fillGrid);

        submitBtn = new QPushButton(verticalLayoutWidget);
        submitBtn->setObjectName("submitBtn");

        verticalLayout->addWidget(submitBtn);

        configLabel = new QLabel(ConfigWindow);
        configLabel->setObjectName("configLabel");
        configLabel->setGeometry(QRect(10, 10, 131, 21));

        retranslateUi(ConfigWindow);

        QMetaObject::connectSlotsByName(ConfigWindow);
    } // setupUi

    void retranslateUi(QDialog *ConfigWindow)
    {
        ConfigWindow->setWindowTitle(QCoreApplication::translate("ConfigWindow", "Dialog", nullptr));
        lvlLabel->setText(QCoreApplication::translate("ConfigWindow", "A quelle niveau souhaitez vous commencez le jeu ?", nullptr));
        lvlErr->setText(QCoreApplication::translate("ConfigWindow", "TextLabel", nullptr));
        rowLabel->setText(QCoreApplication::translate("ConfigWindow", "Combien de lignes voulez vous ?", nullptr));
        rowErr->setText(QCoreApplication::translate("ConfigWindow", "TextLabel", nullptr));
        colLabel->setText(QCoreApplication::translate("ConfigWindow", "Combien de colonnes voulez vous ?", nullptr));
        colErr->setText(QCoreApplication::translate("ConfigWindow", "TextLabel", nullptr));
        fillGrid->setText(QCoreApplication::translate("ConfigWindow", "Voulez vous remplir partiellement la grille ?", nullptr));
        submitBtn->setText(QCoreApplication::translate("ConfigWindow", "Commencer", nullptr));
        configLabel->setText(QCoreApplication::translate("ConfigWindow", "Configuration du jeu :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigWindow: public Ui_ConfigWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGWINDOW_H
