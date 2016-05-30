/******************************************************************************
  \file mainwindow.h
  \author Yann Thoma
  \date 05.05.2011

  Fichier faisant partie du labo vélo.
  ****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QDockWidget>
#include "display.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(unsigned int nbConsoles,unsigned int nbSite,
               QWidget *parent = 0);
    ~MainWindow();

    QDockWidget **m_docks;
    QTextEdit **m_consoles;
    BikeDisplay *m_display;

    void setConsoleTitle(unsigned int consoleId,QString title);

protected:
    unsigned int m_nbConsoles;

public slots:
    void consoleAppendText(unsigned int consoleId,QString text);
    void setBikes(unsigned int site,unsigned int nbBike);
    void setPerson(unsigned int site, unsigned int personID);
    void travel(unsigned int personId,unsigned int site1, unsigned int site2,unsigned int ms);
    void vanTravel(unsigned int site1, unsigned int site2,unsigned int ms);

};

#endif // MAINWINDOW_H
