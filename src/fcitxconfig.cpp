#include "fcitxconfig.h"

#include <QVBoxLayout>

#include <KGenericFactory>
#include <KLocale>
#include <KGlobal>
#include <KDialog>

K_PLUGIN_FACTORY( FcitxConfigFactory, registerPlugin<FcitxConfig>(); )
K_EXPORT_PLUGIN( FcitxConfigFactory( "kcmfcitxconfig", "kcm_fcitxconfig" ) )

FcitxConfig::FcitxConfig( QWidget *parent, const QVariantList &args )
        : KCModule( FcitxConfigFactory::componentData(), parent, args )
{
    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->setMargin( 0 );
    layout->setSpacing( KDialog::spacingHint() );

    m_tabdialog = new TabDialog( this );

    connect( m_tabdialog, SIGNAL( configChanged() ), this, SLOT( configChanged() ) );
    layout->addWidget( m_tabdialog );
    m_tabdialog->show();

    KAboutData* about =
        new KAboutData( "Fcitx Configure", 0, ki18n( "Magic Linux Fcitx Configure Module" ), "1.5.3",
                        ki18n( "Magic Linux Fcitx Configure Control Panel Module" ),
                        KAboutData::License_GPL,
                        ki18n( "(c) 2008-2009 Magic Group" ) );
    about->addAuthor( ki18n( "Liu Di" ), ki18n( "QT Edition" ), "liudidi@gmail.com" );
    about->addAuthor( ki18n( "lovewilliam" ), ki18n( "Port QT edition to kcm module" ), "lovewilliam@gmail.com" );
    about->addAuthor( ki18n( "Ni Hui" ), ki18n( "Port to cmake, Port to Qt4/KDE4, Port to new kpluginfactory" ), "shuizhuyuanluo@126.com" );
    setAboutData( about );
}

FcitxConfig::~FcitxConfig()
{
    delete m_tabdialog;
}

void FcitxConfig::load()
{
    // insert your loading code here...
}

void FcitxConfig::defaults()
{
    // insert your default settings code here...
    emit changed( true );
}

void FcitxConfig::save()
{
    m_tabdialog->SaveConfig();
    emit changed( true );
}

void FcitxConfig::configChanged()
{
    // insert your saving code here...
    emit changed( true );
}

#include "fcitxconfig.moc"
