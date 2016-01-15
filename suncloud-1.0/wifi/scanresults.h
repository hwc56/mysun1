/*
 * wpa_gui - ScanResults class
 * Copyright (c) 2005-2006, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef SCANRESULTS_H
#define SCANRESULTS_H

#include <QObject>
#include <QListWidget>

class Wifi;

class ScanResults : public QObject
{
	Q_OBJECT

public:
	ScanResults(QObject *parent = 0);
	~ScanResults();
	virtual void updateResults();
	virtual void scanRequest();
public slots:
	virtual void setWpaGui(Wifi *_wpagui,QListWidget  *list,QStringList  *items);
	virtual void getResults();
	//virtual void getItem(const QString &);
	//virtual void bssSelected(QTreeWidgetItem *sel);
private:
	Wifi *wpagui;
    QListWidget  *qlist;
    QStringList  *_items;
};

#endif /* SCANRESULTS_H */
