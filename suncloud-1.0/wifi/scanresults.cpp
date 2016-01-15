/*
 * wpa_gui - ScanResults class
 * Copyright (c) 2005-2006, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include <cstdio>

#include "scanresults.h"
#include "wifi.h"
//#include "networkconfig.h"


ScanResults::ScanResults(QObject *parent)
	: QObject(parent)
{


	wpagui = NULL;
	qlist = NULL;
    _items = NULL;
}


ScanResults::~ScanResults()
{
}


void ScanResults::setWpaGui(Wifi *_wpagui,QListWidget  *list,QStringList  *items)
{
	wpagui = _wpagui;
    qlist = list;
    _items = items;
    scanRequest();
	updateResults();
}


void ScanResults::updateResults()
{
	char reply[2048];
	size_t reply_len;
	int index;
	char cmd[20];

	//scanResultsWidget->clear();
	qlist->clear();
	_items->clear();

	index = 0;
	while (wpagui) {
		snprintf(cmd, sizeof(cmd), "BSS %d", index++);
		if (index > 1000)
			break;

		reply_len = sizeof(reply) - 1;
		if (wpagui->ctrlRequest(cmd, reply, &reply_len) < 0)
			break;
		reply[reply_len] = '\0';

		QString bss(reply);
		if (bss.isEmpty() || bss.startsWith("FAIL"))
			break;

		QString ssid, bssid, freq, signal, flags;

		QStringList lines = bss.split(QRegExp("\\n"));
		for (QStringList::Iterator it = lines.begin();
		     it != lines.end(); it++) {
			int pos = (*it).indexOf('=') + 1;
			if (pos < 1)
				continue;

			if ((*it).startsWith("bssid="))
				bssid = (*it).mid(pos);
			else if ((*it).startsWith("freq="))
				freq = (*it).mid(pos);
			else if ((*it).startsWith("level="))
				signal = (*it).mid(pos);
			else if ((*it).startsWith("flags="))
				flags = (*it).mid(pos);
			else if ((*it).startsWith("ssid="))
				ssid = (*it).mid(pos);
		}
        if(ssid.length() <= 0)
            continue;
#if 1
             int m = ssid.indexOf("\\x");
             int n = ssid.lastIndexOf("\\x");
            if(m >= 0)
            {
                QString code = ssid.mid(m,n-m+4);
                QStringList  hzlist = code.split("\\x");
                int v[hzlist.size()-1];
                char  buffer[hzlist.size()];
                memset(buffer,0,sizeof(buffer));
                for(int i=0;i<hzlist.size()-1;i++)
                {
                    sscanf(hzlist.at(i+1).toLocal8Bit().data(),"%2X",&v[i]);
                } 
                for(int i=0;i<hzlist.size()-1;i++)
                    buffer[i] = (char)v[i];
                qDebug()<<"***buffer:"<<tr(buffer);
                ssid.replace(m,n-m+4,tr(buffer));
            }
#endif
    int   id = 1;
    int   signalvalue = signal.toInt(); 
#if 1
    if(signalvalue >= -60)
        id = 1;
    else if(signalvalue >= -70)
        id = 2;
    else if(signalvalue >= -80)
        id = 3;
    else if(signalvalue > -90)
        id = 4;
    else
        id = 5;
#endif
    QString   imagefile="";
    switch(id)
    {
        case    1:imagefile="./images/wifi_1.png";break;
        case    2:imagefile="./images/wifi_2.png";break;
        case    3:imagefile="./images/wifi_3.png";break;
        case    4:imagefile="./images/wifi_4.png";break;
        case    5:imagefile="./images/wifi_5.png";break;
    }
 
		qlist->addItem(new  QListWidgetItem(QIcon(imagefile),ssid));
        _items->push_back(ssid+"\t"+bssid+"\t"+flags);
		if (bssid.isEmpty())
			break;
	}

}
#if 0
void ScanResults::getItem(const QString &m)
{
    NetworkConfig *nc = new NetworkConfig();
	if (nc == NULL)
		return;
	nc->setWpaGui(wpagui);
	//nc->paramsFromScanResults(sel);
	nc->show();
	nc->exec();

}
#endif
void ScanResults::scanRequest()
{
	char reply[10];
	size_t reply_len = sizeof(reply);
    
	if (wpagui == NULL)
		return;
    
	wpagui->ctrlRequest("SCAN", reply, &reply_len);
    getResults();
}


void ScanResults::getResults()
{
	updateResults();
}

#if 0
void ScanResults::bssSelected(QTreeWidgetItem *sel)
{
	NetworkConfig *nc = new NetworkConfig();
	if (nc == NULL)
		return;
	nc->setWpaGui(wpagui);
	nc->paramsFromScanResults(sel);
	nc->show();
	nc->exec();
}
#endif

