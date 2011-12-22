#ifndef _FCITXCONFIG_H_
#define _FCITXCONFIG_H_

#include <KCModule>
#include <KAboutData>

#include "tabdialog.h"

class FcitxConfig : public KCModule
{
    Q_OBJECT

    public:
        FcitxConfig( QWidget *parent, const QVariantList &args );
        ~FcitxConfig();

        void load();
        void save();
        void defaults();

    public slots:
        void configChanged();

    private:
        TabDialog* m_tabdialog;
};

#endif // _FCITXCONFIG_H_
