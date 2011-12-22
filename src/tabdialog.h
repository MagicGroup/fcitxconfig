#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QTabWidget>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QProcess>
#include <QCheckBox>
#include <QListView>
#include <QMessageBox>
#include <QFile>
#include <QSpinBox>
#include <QComboBox>

class TabDialog : public QWidget
{
    Q_OBJECT

    public:
        TabDialog( QWidget *parent );
        void LoadConfig();
    public slots:
        void configSlot();

        void SaveConfig();
        void ChooseFontC();
        void ChooseFontE();
        void ChooseColor1();
        void ChooseColor2();
        void ChooseColor3();
        void ChooseColor4();
        void ChooseColor5();
        void ChooseColor6();
        void ChooseColor7();
        void ChooseColor8();
        void ChooseColor9();
        void ChooseColor10();
        void ChooseColor11();
        void ChooseColor12();
        void ChooseColor13();
        void ChooseColor14();
        void ChooseColor15();
        void ChooseColor16();
        void ChooseColor17();
        void ChooseColor18();
        void ChooseColor19();

    signals:
        void configChanged();

    private:
        QLineEdit *langinput,*cfontinput,*efontinput,*pinyinnameinput,*quweinameinput;
        QLineEdit *conkeyinput,*gbkeyinput,*hidemainwindowkeyinput,*vkbkeyinput,*gbkkeyinput,
        *gbkfkeyinput,*sfkeyinput,*spinnameinput,*savedictkeyinput,*recordmodekeyinput;
        QLineEdit *lenkeyinput,*pinyininput,*dbcaseinput,*cbdinput,*previnput,*nextinput,*otherimeinput;
        QLineEdit *qkey1input,*qkey2input,*qkey3input,*qkey4input;

        QComboBox *language,*semicombobox,*entercombobox,*hidebox,*main3dbox,*input3dbox,*ecconvbox,*spinfabox,
        *cm1box,*cm2box,*cm3box;

        QCheckBox *mh1box,*mh2box,*mh3box,*mh4box,*mh5box,*mh6box,*mh7box,*mh8box,*mh9box,*mh10box,*mh11box;
        QPushButton *cfontbutton,*efontbutton,*gbcolorb,*bjcolorb,*xtcolorb,*srfcolor1,*srfcolor2,*srfcolor3;
        QPushButton  *sgbcolorb,*stscolorb,*ssrcolorb,*sxhcolorb,*ssxcolorb,*syhcolorb,*sbmcolorb,*sqtcolorb,
        *sstcolorb,*sjtcolorb,*vbjcolorb,*vzmcolorb,*vfhcolorb;
        QSpinBox *cfontsizeinput,*efontsizeinput,*candinput,*barposinput,*barxinput,*baryinput,
        *clicktimebox;

        QCheckBox /* *staticbox,*aabox,*/*boldbox,*traybox,*dbusbox,*dbcbox,*capbox,*interbox,*lennobox,*usepinyin,*usequwei;
        QCheckBox *vkeybox,*centerbox,*firstbox,*verbox,*pointbox,*typebox,*dbclickbox,*usema,*usecizu;
        QCheckBox *usespin,*quanpin,*pinyinzuci,*savezuci;
        QProcess *startf;
        QTabWidget *tabWidget;
};

#endif // TABDIALOG_H
