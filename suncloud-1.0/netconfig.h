/************
*
*功能:Network Configure GUI    Class
*
*
*
**/
#ifndef NETWORKCONFIG_H
#define NETWORKCONFIG_H

#include <QDialog>
#include <QtGui>
#include <QtNetwork/QUdpSocket>
#include "ui_netconfig.h"
namespace Ui {
    class NetConfig;
}

class NetConfig : public QDialog
{
    Q_OBJECT

public:
    explicit NetConfig(QWidget *parent = 0);
    ~NetConfig();
    //void  CheckNetworkState();
    void  FillContent();
    void  GetDevicename();
    void  GetIpandNetmask();
    void  GetNetConfig();
    void  GetGateway();
    void  GetResolution();
    void  GetDNS();
    void  CheckIpType();//check ip get  by  which  style
    QString     devicename;

signals:
    void    signals_startthread(const QString &);
    void    signals_cdms(const QString &);
    void    signals_modifycdms(const QString &);
private slots:
    void  doChangStyleForGetIP();
    void  modifyIpandNetMask();
    void  modifygateway();
    void  doChangResolution();
    void  SendRegisterData();
    void  doGetCdms();

    /***************Remote Control The Box NetWork and  Resolution and  Hostname****************/
#if 0
    void    remote_doChangehostnameSlots(   const QString &);
    void    remote_doChangenetworkSlots(    const QString &);
    void    remote_doChangeresolutionSlots( const QString &);
#endif
private:
    Ui::NetConfig *ui;
    QString     iptype;
    QString     username;
    QString     password;
    QString     ip_info;
    QString     mask_info;
    QString     gateway_info;
    QString     currentResolution;
    QString     cdms_ip;
    QString     method_ip;
    QString     dns;
    QString     localhostname;
    QString     macaddress;
    QString     localnetinform;
    QString     VGAarg; 
    QStringList   resolus;
};

#endif // NETWORKCONFIG_H
