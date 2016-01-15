/************
*
*功能:Wifi Control Class
*
*
*
**/
#ifndef WIFI_H
#define WIFI_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QObject>
#include <QtGui>
#include "wpamsg.h"
#include "scanresults.h"

class Wifi : public QDialog
{
    Q_OBJECT

public:

    explicit Wifi(QWidget *parent = 0);
    ~Wifi();
    virtual int ctrlRequest(const char *cmd, char *buf, size_t *buflen);
	virtual void triggerUpdate();
    QString  connectedname;
signals:
    void    signals_update();//when complete
    void    siglogin(int);//when have complete emit siglogin
public slots:
	virtual void connectB();
	virtual void disconnect();
    virtual void  LinkWifiSlots();
    virtual void  addNetwork();
    virtual void  removeNetwork(const QString &sel);
    virtual void  editNetwork(const QString &sel);


	virtual void selectNetwork(const QString &sel);//connect new Ap

	virtual void updateStatus();
	virtual void updateNetworks();
	virtual void scan();
	virtual void ping();
	virtual void processMsg(char *msg);
	virtual void signalMeterUpdate();
	virtual void addInterface();
	virtual void receiveMsgs();
#ifdef CONFIG_NATIVE_WINDOWS
	virtual void startService();
	virtual void stopService();
#endif 
protected slots:
private:
    QStringList  items;
	ScanResults *scanres;
	QString wpaStateTranslate(char *state);
#ifdef CONFIG_NATIVE_WINDOWS
	bool serviceRunning();
#endif 
	QSocketNotifier *msgNotifier;
	QTimer *timer;
	int pingsToStatusUpdate;
    QTimer *signalMeterTimer;
	WpaMsgList msgs;
	int signalMeterInterval;

	int openCtrlConnection(const char *ifname);
	struct wpa_ctrl *ctrl_conn;
	char *ctrl_iface_dir;
	char *ctrl_iface;
	struct wpa_ctrl *monitor_conn;
    QLabel  *textStatus;
    //QLabel  *textBssid;
	bool networkMayHaveChanged;
    //QLineEdit  *edit;
    //QLabel  *textSsid;
    //QLabel  *textIpAddress;
    //QLabel  *textAuthentication;
    //QLabel  *textEncryption;
    QPushButton  *scanbtn;
    //QPushButton  *connectbtn;
    QPushButton  *disconnectbtn;
    //QComboBox   *networkSelect;
    QListWidget   *networkList;
    QStringList   networklist;
};

#endif // WIFI_H
