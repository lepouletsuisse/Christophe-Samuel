#ifndef BANDITMANCHOT_H
#define BANDITMANCHOT_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

#include "bmmanager.h"


class BanditManchot : public QDialog
{
    Q_OBJECT

public:
    BanditManchot(QWidget * parent = 0, Qt::WindowFlags flags = 0);
    ~BanditManchot();

    static BanditManchot *current(){ return sm_current; }

private:
	static BanditManchot *sm_current;

    BmManager bm_manager;

	QLabel m_number[3];
	QLabel m_jackpot;
	QLabel m_messages;
	QPushButton m_clef;
	QPushButton m_stop;
	QPushButton m_piece;
	QPushButton m_vandal;
private slots:
	void keyPressEvent ( QKeyEvent * event );
	void clef();
	void stop();
	void piece();
	void vandal();
public slots:
	void setValue(int n,int value);
    void setMessage(const QString mess);
	void setJackpot(int jackpot);
};

class Sender: public QObject
{
	Q_OBJECT
	public:
		Sender(BanditManchot *dialog);
		static Sender *m_current;
        static Sender *current(){return m_current;}

	void setValue(int n,int value);
    void setMessage(const QString mess);
	void setJackpot(int jackpot);
	signals:
	void sig_setValue(int n,int value);
    void sig_setMessage(const QString mess);
	void sig_setJackpot(int jackpot);
};

#endif // BANDITMANCHOT_H
