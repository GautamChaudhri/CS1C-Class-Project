/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *RenderArea;
    QLabel *label;
    QGroupBox *groupBox;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QMenu *menuSettings;
    QMenu *menuLogin;
    QMenu *menuContact;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1500, 1000);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        MainWindow->setPalette(palette);
        QFont font;
        font.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font.setPointSize(10);
        font.setBold(false);
        font.setUnderline(false);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        RenderArea = new QFrame(centralwidget);
        RenderArea->setObjectName("RenderArea");
        RenderArea->setGeometry(QRect(50, 80, 1000, 850));
        QPalette palette1;
        QBrush brush1(QColor(176, 176, 176, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush1);
        QBrush brush2(QColor(91, 91, 91, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        QBrush brush3(QColor(209, 209, 209, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush3);
        QBrush brush4(QColor(49, 49, 49, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush4);
        RenderArea->setPalette(palette1);
        RenderArea->setAcceptDrops(false);
        RenderArea->setAutoFillBackground(true);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 40, 1000, 30));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font1.setPointSize(21);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(true);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        label->setFont(font1);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(1090, 80, 360, 850));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setUnderline(true);
        groupBox->setFont(font2);
        groupBox->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);
        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(30, 50, 300, 24));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font3.setPointSize(11);
        font3.setBold(false);
        font3.setUnderline(false);
        comboBox->setFont(font3);
        comboBox->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        comboBox->setEditable(false);
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 820, 111, 24));
        pushButton->setFont(font);
        pushButton->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(230, 820, 121, 24));
        pushButton_2->setFont(font);
        pushButton_2->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1500, 23));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName("menuSettings");
        menuLogin = new QMenu(menubar);
        menuLogin->setObjectName("menuLogin");
        menuContact = new QMenu(menubar);
        menuContact->setObjectName("menuContact");
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuLogin->menuAction());
        menubar->addAction(menuContact->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "2D Graphics Modeler", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Render Area", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Shape Properties", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Shape Type", nullptr));
        comboBox->setItemText(1, QString());

#if QT_CONFIG(tooltip)
        comboBox->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        comboBox->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(accessibility)
        comboBox->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        comboBox->setCurrentText(QCoreApplication::translate("MainWindow", "Shape Type", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Add Shape", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Remove Shape", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuLogin->setTitle(QCoreApplication::translate("MainWindow", "Login", nullptr));
        menuContact->setTitle(QCoreApplication::translate("MainWindow", "Contact", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
