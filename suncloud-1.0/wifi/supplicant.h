#ifndef SUPPLICANT_H
#define SUPPLICANT_H

#include <QThread>
#include "wpasupplicant.h"

class DeamonThread:public  QThread
{
    public:
        DeamonThread(QString  _devname,QString _name)
        {
            devicename = _devname;
            filename = _name; 
        }
        void    run()
        {
            wpa_suncloud(devicename.toLocal8Bit().data(),filename.toLocal8Bit().data());
        }
    private:
        QString devicename;
        QString filename;
};

#endif /* SUPPLICANT_H */
