#include "banditmanchot.h"
#include <QVBoxLayout>
#include "bmmanager.h"
#include <QMessageBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QKeyEvent>


BanditManchot *BanditManchot::sm_current=0;

Sender *theSender;

BanditManchot::BanditManchot(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    sm_current=this;
	this->setWindowTitle("Bandit Manchot");

	theSender=new Sender(this);
	QVBoxLayout *layout=new QVBoxLayout(this);
	QHBoxLayout *layoutRouleau=new QHBoxLayout();
	for(int i=0;i<3;i++)
	{
		QGroupBox *groupBox = new QGroupBox(QString("Rouleau %1").arg(i+1));

		QHBoxLayout *hbox = new QHBoxLayout();
		hbox->addStretch();
		hbox->addWidget(&m_number[i]);
		hbox->addStretch();
		groupBox->setLayout(hbox);
		layoutRouleau->addWidget(groupBox);
	}
	layout->addLayout(layoutRouleau);

	layout->addWidget(&m_jackpot);
	layout->addWidget(&m_messages);

	QHBoxLayout *layoutBoutons=new QHBoxLayout();
	layoutBoutons->addWidget(&m_piece);
	layoutBoutons->addWidget(&m_stop);
//	layoutBoutons->addWidget(&m_clef);
//	layoutBoutons->addWidget(&m_vandal);
	layout->addLayout(layoutBoutons);

	m_clef.setText("Clef");
	m_stop.setText("Stop");
	m_piece.setText("Piece");
	m_vandal.setText("Vandalisme");

	// Initialement, le jackpot est à 0
	setJackpot(0);
	// La machine est prête à fonctionner
	setMessage("Prêt");

	// Connexion des signaux pour les 4 boutons
	connect(&m_clef,SIGNAL(pressed()),this,SLOT(clef()));
	connect(&m_stop,SIGNAL(pressed()),this,SLOT(stop()));
	connect(&m_vandal,SIGNAL(pressed()),this,SLOT(vandal()));
	connect(&m_piece,SIGNAL(pressed()),this,SLOT(piece()));

	// Initialisation de la partie responsable de la gestion du système
    bm_manager.start();
}

void BanditManchot::keyPressEvent (QKeyEvent * event )
{
	switch(event->key())
	{
        case Qt::Key_P: bm_manager.pieceIntroduite();return;
        case Qt::Key_S: bm_manager.boutonStop();return;
        //case Qt::Key_V: bm_manager.vandalisme();return;
        //case Qt::Key_C: bm_manager.clefOperateur();return;
		default:return;
	}
}

void BanditManchot::clef()
{
//    bm_manager.clefOperateur();
}

void BanditManchot::stop()
{
    bm_manager.boutonStop();
}

void BanditManchot::vandal()
{
//    bm_manager.vandalisme();
}

void BanditManchot::piece()
{
    bm_manager.pieceIntroduite();
}

void BanditManchot::setValue(int n,int value)
{
	if ((n>2)||(n<0))
	{
		QMessageBox::warning(0,0,"Le numéro de rouleau n'est pas correct");
		return;
	}
	m_number[n].setText(QString("%1").arg(value));
}

void BanditManchot::setMessage(const QString mess)
{
    m_messages.setText(mess);
}

void BanditManchot::setJackpot(int jackpot)
{
	m_jackpot.setText(QString("Jackpot: %1").arg(jackpot));
}

BanditManchot::~BanditManchot()
{
    bm_manager.end();
}

Sender::Sender(BanditManchot *BanditManchot)
{
	m_current=this;
	connect(this,SIGNAL(sig_setValue(int,int)),BanditManchot,SLOT(setValue(int,int)));
    connect(this,SIGNAL(sig_setMessage(const QString)),BanditManchot,SLOT(setMessage(const QString)));
	connect(this,SIGNAL(sig_setJackpot(int)),BanditManchot,SLOT(setJackpot(int)));
}

void Sender::setValue(int n,int value)
{
	emit sig_setValue(n,value);
}

void Sender::setMessage(const QString mess)
{
	emit sig_setMessage(mess);
}

void Sender::setJackpot(int jackpot)
{
	emit sig_setJackpot(jackpot);
}

void setValeurRouleau(int rouleau,int valeur)
{
	Sender::current()->setValue(rouleau,valeur);
}

void setMessage(const QString mess)
{
	Sender::current()->setMessage(mess);
}

void setJackpot(int jackpot)
{
	Sender::current()->setJackpot(jackpot);
}

Sender *Sender::m_current=0;
