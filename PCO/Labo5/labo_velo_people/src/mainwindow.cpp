/******************************************************************************
  \file mainwindow.cpp
  \author Yann Thoma
  \date 05.05.2011

  Fichier faisant partie du labo vélo.
  ****************************************************************************/


#include "mainwindow.h"

#define min(a,b) ((a<b)?(a):(b))

MainWindow::MainWindow(unsigned int nbConsoles,unsigned int nbSite,
                       QWidget *parent)
    : QMainWindow(parent)
{
    m_nbConsoles=nbConsoles;
    m_consoles=new QTextEdit*[nbConsoles];
    for(unsigned int i=0;i<nbConsoles;i++) {
        m_consoles[i]=new QTextEdit(this);
        m_consoles[i]->setMinimumWidth(200);
    }
    m_docks=new QDockWidget*[nbConsoles];
    for(unsigned int i=0;i<nbConsoles;i++) {
        m_docks[i]=new QDockWidget(this);
        m_docks[i]->setWidget(m_consoles[i]);
    }
    for(unsigned int i=0;i<nbConsoles/2;i++) {
        this->addDockWidget(Qt::LeftDockWidgetArea,m_docks[i]);
    }
    for(unsigned int i=nbConsoles/2;i<nbConsoles;i++) {
        this->addDockWidget(Qt::RightDockWidgetArea,m_docks[i]);
    }

    for(unsigned int i=0;i<nbConsoles;i++)
        setConsoleTitle(i,QString("Console number : %1").arg(i));
    m_display=new BikeDisplay(nbSite,this);
    setCentralWidget(m_display);
}


void MainWindow::setConsoleTitle(unsigned int consoleId,QString title)
{
    if (consoleId>=m_nbConsoles)
        return;
    m_docks[consoleId]->setWindowTitle(title);
}

void MainWindow::consoleAppendText(unsigned int consoleId,QString text)
{
    if (consoleId>=m_nbConsoles)
        return;
    m_consoles[consoleId]->append(text);
}


void MainWindow::setBikes(unsigned int site,unsigned int nbBike)
{
    m_display->setBikes(site,nbBike);
}


void MainWindow::setPerson(unsigned int site, unsigned int personID)
{
    m_display->setPerson(site,personID);
}

void MainWindow::travel(unsigned int personId,unsigned int site1, unsigned int site2,unsigned int ms)
{
    m_display->travel(personId,site1,site2,ms);
}

void MainWindow::vanTravel(unsigned int site1, unsigned int site2,
                           unsigned int ms)
{
    m_display->vanTravel(site1,site2,ms);
}

MainWindow::~MainWindow()
{

}
