#include "tabdialog.h"

#include <QLayout>
#include <QButtonGroup>
#include <QApplication>
#include <QTextStream>
#include <QTextCodec>
#include <QDir>
#include <QColorDialog>
#include <QColor>
#include <QFontDialog>
#include <QFont>
#include <QPalette>
#include <QStringList>

#include <KLocale>

TabDialog::TabDialog( QWidget *parent )
        : QWidget( parent )
{
    QVBoxLayout *mainLayout = new QVBoxLayout( this );
    tabWidget = new QTabWidget( this );
    mainLayout->addWidget( tabWidget );
    QWidget *tab1 = new QWidget( this );
    QVBoxLayout *tablay1 = new QVBoxLayout( tab1 );
    tablay1->setSpacing( 1 );

    QHBoxLayout *langbox = new QHBoxLayout;
    QLabel *lang = new QLabel( QString::fromLocal8Bit( "区域：" ),tab1 );
    language = new QComboBox( tab1 );
    language->addItem( "zh_CN.GBK" );
    language->addItem( "zh_CN.UTF-8" );
    language->addItem( "zh_CN.GB18030" );
    langbox->addWidget( lang );
    langbox->addWidget( language );
    langbox->setAlignment( Qt::AlignTop );
    tablay1->addLayout( langbox );

    QHBoxLayout *cfontbox= new QHBoxLayout;
    QLabel *cfont = new QLabel( QString::fromLocal8Bit( "中文字体：" ),tab1 );
    cfontinput = new QLineEdit( "*",tab1 );
    cfontbutton = new QPushButton( QString::fromLocal8Bit( "选择..." ),tab1 );
    cfontbox->addWidget( cfont );
    cfontbox->addWidget( cfontinput );
    cfontbox->addWidget( cfontbutton );
    QLabel *efont = new QLabel( QString::fromLocal8Bit( "英文字体：" ),tab1 );
    efontinput = new QLineEdit( "Courier New",tab1 );
    efontbutton = new QPushButton( QString::fromLocal8Bit( "选择..." ),tab1 );
    QLabel *efontsize = new QLabel( QString::fromLocal8Bit( "显示字体大小：" ),tab1 );
    efontsizeinput = new QSpinBox( /*9,32,1,*/tab1 );
    efontsizeinput->setValue( 12 );
    cfontbox->addWidget( efont );
    cfontbox->addWidget( efontinput );
    cfontbox->addWidget( efontbutton );
    cfontbox->addWidget( efontsize );
    cfontbox->addWidget( efontsizeinput );
    cfontbox->setAlignment( Qt::AlignTop );
    tablay1->addLayout( cfontbox );

    QHBoxLayout *efontbox = new QHBoxLayout;
    QLabel *mainsize = new QLabel( QString::fromLocal8Bit( "主窗口字体大小：" ),tab1 );
    cfontsizeinput = new QSpinBox( /*9,32,1,*/tab1 );
    cfontsizeinput->setValue( 12 );
    efontbox->addWidget( mainsize );
    efontbox->addWidget( cfontsizeinput );
    efontbox->addStretch();
    tablay1->addLayout( efontbox );

    QHBoxLayout *checkbox1 = new QHBoxLayout;
//     staticbox = new QCheckBox( QString::fromLocal8Bit( "静态模式" ),tab1 );
//     staticbox->setChecked( false );
//     aabox = new QCheckBox( QString::fromLocal8Bit( "使用字体 AA" ),tab1 );
//     aabox->setChecked( true );
    boldbox = new QCheckBox( QString::fromLocal8Bit( "使用粗体" ),tab1 );
    boldbox->setChecked( true );
    traybox = new QCheckBox( QString::fromLocal8Bit( "使用托盘图标" ),tab1 );
    traybox->setChecked( true );
    dbusbox = new QCheckBox( QString::fromLocal8Bit( "使用 DBus 接口" ),tab1 );
    dbusbox->setChecked( true );
//     checkbox1->addWidget( staticbox );
//     checkbox1->addWidget( aabox );
    checkbox1->addWidget( boldbox );
    checkbox1->addWidget( traybox );
    checkbox1->addWidget( dbusbox );
    checkbox1->setAlignment( Qt::AlignTop );
    tablay1->addLayout( checkbox1 );

    QLabel *notelabel = new QLabel( QString::fromLocal8Bit( "<b><font color=red>注意：如果你的 Fctix 运行正常，请不要修改上面的配置！</font></b>" ),tab1 );
    notelabel->setAlignment( Qt::AlignTop );
    tablay1->addWidget( notelabel );

    tablay1->addStretch();

    tabWidget->addTab( tab1, QString::fromLocal8Bit( "程序" ) );

    QWidget *tab2 = new QWidget( this );
    QVBoxLayout *tablay2 = new QVBoxLayout( tab2 );

    QHBoxLayout *semibox = new QHBoxLayout;
    QLabel *semi = new QLabel( QString::fromLocal8Bit( "分号键行为：" ), tab2 );
    semicombobox = new QComboBox( tab2 );
    semicombobox->addItem( QString::fromLocal8Bit( "只输入分号" ) );
    semicombobox->addItem( QString::fromLocal8Bit( "进入快速输入状态" ) );
    semicombobox->addItem( QString::fromLocal8Bit( "进入英文输入状态" ) );
    semicombobox->setCurrentIndex( 2 );
    semibox->addWidget( semi );
    semibox->addWidget( semicombobox );
    tablay2->addLayout( semibox );

    QHBoxLayout *enterbox = new QHBoxLayout;
    QLabel *enter = new QLabel( QString::fromLocal8Bit( "回车键行为：" ), tab2 );
    entercombobox = new QComboBox( tab2 );
    entercombobox->addItem( QString::fromLocal8Bit( "不处理" ) );
    entercombobox->addItem( QString::fromLocal8Bit( "清除用户输入" ) );
    entercombobox->addItem( QString::fromLocal8Bit( "用户输入内容上屏" ) );
    entercombobox->setCurrentIndex( 2 );
    enterbox->addWidget( enter );
    enterbox->addWidget( entercombobox );
    tablay2->addLayout( enterbox );

    QHBoxLayout *checkbox2 = new QHBoxLayout;
    QHBoxLayout *checkbox3 = new QHBoxLayout;
    dbcbox = new QCheckBox( QString::fromLocal8Bit( "数字后跟半角字符" ),tab2 );
    dbcbox->setChecked( false );
    capbox = new QCheckBox( QString::fromLocal8Bit( "大写字母输入英文" ),tab2 );
    capbox->setChecked( true );
    interbox = new QCheckBox( QString::fromLocal8Bit( "转换英文中的标点" ),tab2 );
    interbox->setChecked( true );
    lennobox = new QCheckBox( QString::fromLocal8Bit( "联想方式禁止翻页" ),tab2 );
    lennobox->setChecked( false );
    checkbox2->addWidget( dbcbox );
    checkbox2->addWidget( capbox );
    checkbox3->addWidget( interbox );
    checkbox3->addWidget( lennobox );
    tablay2->addLayout( checkbox2 );
    tablay2->addLayout( checkbox3 );

    tablay2->addStretch();
    tablay2->setSpacing( 1 );

    tabWidget->addTab( tab2, QString::fromLocal8Bit( "输出" ) );

    QWidget *tab3 = new QWidget( this );
    QVBoxLayout *tablay3 = new QVBoxLayout( tab3 );

    QHBoxLayout *candibox = new QHBoxLayout;
    QLabel *candidate = new QLabel( QString::fromLocal8Bit( "候选词个数：" ),tab3 );
    candinput = new QSpinBox( /*3,10,1,*/tab3 );
    candinput->setValue( 5 );
    QLabel *hidemode = new QLabel( QString::fromLocal8Bit( "主窗口隐藏模式：" ),tab3 );
    hidebox = new QComboBox( tab3 );
    hidebox->addItem( QString::fromLocal8Bit( "不显示" ) );
    hidebox->addItem( QString::fromLocal8Bit( "总在最顶层" ) );
    hidebox->addItem( QString::fromLocal8Bit( "当需要时显示" ) );
    hidebox->setCurrentIndex( 1 );
    candibox->addWidget( candidate );
    candibox->addWidget( candinput );
    candibox->addWidget( hidemode );
    candibox->addWidget( hidebox );
    tablay3->addLayout( candibox );

    QHBoxLayout *dbox = new QHBoxLayout;
    QLabel *main3d = new QLabel( QString::fromLocal8Bit( "主窗口 3D 界面：" ),tab3 );
    main3dbox = new QComboBox( tab3 );
    main3dbox->addItem( QString::fromLocal8Bit( "不使用" ) );
    main3dbox->addItem( QString::fromLocal8Bit( "凸出" ) );
    main3dbox->addItem( QString::fromLocal8Bit( "凹进" ) );
    main3dbox->setCurrentIndex( 1 );
    QLabel *input3d = new QLabel( QString::fromLocal8Bit( "输入条 3D 界面：" ),tab3 );
    input3dbox = new QComboBox( tab3 );
    input3dbox->addItem( QString::fromLocal8Bit( "不使用" ) );
    input3dbox->addItem( QString::fromLocal8Bit( "凸出" ) );
    input3dbox->addItem( QString::fromLocal8Bit( "凹进" ) );
    input3dbox->setCurrentIndex( 1 );
    dbox->addWidget( main3d );
    dbox->addWidget( main3dbox );
    dbox->addWidget( input3d );
    dbox->addWidget( input3dbox );
    tablay3->addLayout( dbox );

    QGridLayout *checkbox4 = new QGridLayout;
    vkeybox = new QCheckBox( QString::fromLocal8Bit( "显示虚拟键盘" ),tab3 );
    vkeybox->setChecked( false );
    centerbox = new QCheckBox( QString::fromLocal8Bit( "输入条居中" ),tab3 );
    centerbox->setChecked( true );
    firstbox = new QCheckBox( QString::fromLocal8Bit( "首次显示输入条" ),tab3 );
    firstbox->setChecked( true );
    pointbox = new QCheckBox( QString::fromLocal8Bit( "序号后加点" ),tab3 );
    pointbox->setChecked( true );
    verbox = new QCheckBox( QString::fromLocal8Bit( "显示版本" ),tab3 );
    verbox->setChecked( true );
    typebox = new QCheckBox( QString::fromLocal8Bit( "显示打字速度" ),tab3 );
    typebox->setChecked( false );
    checkbox4->addWidget( vkeybox,0,0 );
    checkbox4->addWidget( centerbox,0,1 );
    checkbox4->addWidget( firstbox,0,2 );
    checkbox4->addWidget( pointbox,1,0 );
    checkbox4->addWidget( verbox,1,1 );
    checkbox4->addWidget( typebox,1,2 );
    tablay3->addLayout( checkbox4 );

    QHBoxLayout *barpos = new QHBoxLayout;
    QLabel *barwidth = new QLabel( QString::fromLocal8Bit( "输入条固定宽度（0是不固定）" ),tab3 );
    QLabel *barx = new QLabel( QString::fromLocal8Bit( "输入条偏移量 X=" ),tab3 );
    QLabel *bary = new QLabel( QString::fromLocal8Bit( "输入条偏移量 Y=" ),tab3 );
    barposinput = new QSpinBox( /*0,100,1,*/tab3 );
    barxinput = new QSpinBox( /*-100,100,1,*/tab3 );
    barxinput->setValue( 0 );
    baryinput = new QSpinBox( /* -100,100,1,*/tab3 );
    baryinput->setValue( 16 );
    barpos->addWidget( barwidth );
    barpos->addWidget( barposinput );
    barpos->addWidget( barx );
    barpos->addWidget( barxinput );
    barpos->addWidget( bary );
    barpos->addWidget( baryinput );
    tablay3->addLayout( barpos );

    tablay3->addSpacing( 1 );
    QLabel *color = new QLabel( QString::fromLocal8Bit( "<b>颜色配置：</b>" ),tab3 );
    tablay3->addWidget( color );

    QGridLayout *colorlay = new QGridLayout;
    QLabel *mainw00 = new QLabel( QString::fromLocal8Bit( "<font color=blue>主窗口：</font>" ),tab3 );
    colorlay->addWidget( mainw00,0,0 );
    QLabel *input02 = new QLabel( QString::fromLocal8Bit( "<font color=blue>输入条：</font>" ),tab3 );
    colorlay->addWidget( input02,0,2 );
    QLabel *virtual04 = new QLabel( QString::fromLocal8Bit( "<font color=blue>虚拟键盘：</font>" ),tab3 );
    colorlay->addWidget( virtual04,0,6 );

    QPalette palette;
    QLabel *gbcolor = new QLabel( QString::fromLocal8Bit( "光标" ),tab3 );
    gbcolorb = new QPushButton( tab3 );
    palette.setColor( gbcolorb->backgroundRole(), QColor( 15, 9, 201 ) );
    gbcolorb->setPalette( palette );
    QLabel *bjcolor = new QLabel( QString::fromLocal8Bit( "背景" ),tab3 );
    bjcolorb = new QPushButton( tab3 );
    palette.setColor( bjcolorb->backgroundRole(), QColor( 255, 255, 255 ) );
    bjcolorb->setPalette( palette );
    QLabel *xtcolor = new QLabel( QString::fromLocal8Bit( "线条" ),tab3 );
    xtcolorb = new QPushButton( tab3 );
    palette.setColor( xtcolorb->backgroundRole(), QColor( 203, 202, 186 ) );
    xtcolorb->setPalette( palette );
    QLabel *srfcolor = new QLabel( QString::fromLocal8Bit( "输入法" ),tab3 );
    srfcolor1 = new QPushButton( tab3 );
    palette.setColor( srfcolor1->backgroundRole(), QColor( 153, 153, 153 ) );
    srfcolor1->setPalette( palette );
    srfcolor2 = new QPushButton( tab3 );
    palette.setColor( srfcolor2->backgroundRole(), QColor( 102, 159, 66 ) );
    srfcolor2->setPalette( palette );
    srfcolor3 = new QPushButton( tab3 );
    palette.setColor( srfcolor3->backgroundRole(), QColor( 56, 134, 230 ) );
    srfcolor3->setPalette( palette );
    colorlay->addWidget( gbcolor,1,0 );
    colorlay->addWidget( gbcolorb,1,1 );
    colorlay->addWidget( bjcolor,2,0 );
    colorlay->addWidget( bjcolorb,2,1 );
    colorlay->addWidget( xtcolor,3,0 );
    colorlay->addWidget( xtcolorb,3,1 );
    colorlay->addWidget( srfcolor,4,0 );
    colorlay->addWidget( srfcolor1,4,1 );
    colorlay->addWidget( srfcolor2,5,1 );
    colorlay->addWidget( srfcolor3,6,1 );
    QLabel *sgbcolor = new QLabel( QString::fromLocal8Bit( "背景" ),tab3 );
    sgbcolorb = new QPushButton( tab3 );
    palette.setColor( sgbcolorb->backgroundRole(), QColor( 240, 245, 255 ) );
    sgbcolorb->setPalette( palette );
    QLabel *stscolor = new QLabel( QString::fromLocal8Bit( "提示" ),tab3 );
    stscolorb = new QPushButton( tab3 );
    palette.setColor( stscolorb->backgroundRole(), QColor( 2, 89, 169 ) );
    stscolorb->setPalette( palette );
    QLabel *ssrcolor = new QLabel( QString::fromLocal8Bit( "输入" ),tab3 );
    ssrcolorb = new QPushButton( tab3 );
    palette.setColor( ssrcolorb->backgroundRole(), QColor( 255, 0, 132 ) );
    ssrcolorb->setPalette( palette );
    QLabel *sxhcolor = new QLabel( QString::fromLocal8Bit( "序号" ),tab3 );
    sxhcolorb = new QPushButton( tab3 );
    palette.setColor( sxhcolorb->backgroundRole(), QColor( 0, 50, 200 ) );
    sxhcolorb->setPalette( palette );
    QLabel *ssxcolor = new QLabel( QString::fromLocal8Bit( "首选" ),tab3 );
    ssxcolorb = new QPushButton( tab3 );
    palette.setColor( ssxcolorb->backgroundRole(), QColor( 0, 99, 200 ) );
    ssxcolorb->setPalette( palette );
    QLabel *syhcolor = new QLabel( QString::fromLocal8Bit( "用户词组" ),tab3 );
    QLabel *sbmcolor = new QLabel( QString::fromLocal8Bit( "提示编码" ),tab3 );
    QLabel *sqtcolor = new QLabel( QString::fromLocal8Bit( "其他文本" ),tab3 );
    QLabel *sstcolor = new QLabel( QString::fromLocal8Bit( "线条" ),tab3 );
    QLabel *sjtcolor = new QLabel( QString::fromLocal8Bit( "箭头" ),tab3 );
    syhcolorb = new QPushButton( tab3 );
    palette.setColor( syhcolorb->backgroundRole(), QColor( 0, 99, 200 ) );
    syhcolorb->setPalette( palette );
    sbmcolorb = new QPushButton( tab3 );
    palette.setColor( sbmcolorb->backgroundRole(), QColor( 255, 0, 132 ) );
    sbmcolorb->setPalette( palette );
    sqtcolorb = new QPushButton( tab3 );
    palette.setColor( sqtcolorb->backgroundRole(), QColor( 56, 134, 230 ) );
    sqtcolorb->setPalette( palette );
    sstcolorb = new QPushButton( tab3 );
    palette.setColor( sstcolorb->backgroundRole(), QColor( 203, 202, 186 ) );
    sstcolorb->setPalette( palette );
    sjtcolorb = new QPushButton( tab3 );
    palette.setColor( sjtcolorb->backgroundRole(), QColor( 15, 227, 171 ) );
    sjtcolorb->setPalette( palette );
    colorlay->addWidget( sgbcolor,1,2 );
    colorlay->addWidget( sgbcolorb,1,3 );
    colorlay->addWidget( stscolor,2,2 );
    colorlay->addWidget( stscolorb,2,3 );
    colorlay->addWidget( ssrcolor,3,2 );
    colorlay->addWidget( ssrcolorb,3,3 );
    colorlay->addWidget( sxhcolor,4,2 );
    colorlay->addWidget( sxhcolorb,4,3 );
    colorlay->addWidget( ssxcolor,5,2 );
    colorlay->addWidget( ssxcolorb,5,3 );
    colorlay->addWidget( syhcolor,1,4 );
    colorlay->addWidget( syhcolorb,1,5 );
    colorlay->addWidget( sbmcolor,2,4 );
    colorlay->addWidget( sbmcolorb,2,5 );
    colorlay->addWidget( sqtcolor,3,4 );
    colorlay->addWidget( sqtcolorb,3,5 );
    colorlay->addWidget( sstcolor,4,4 );
    colorlay->addWidget( sstcolorb,4,5 );
    colorlay->addWidget( sjtcolor,5,4 );
    colorlay->addWidget( sjtcolorb,5,5 );
    QLabel *vbjcolor = new QLabel( QString::fromLocal8Bit( "背景" ),tab3 );
    QLabel *vzmcolor = new QLabel( QString::fromLocal8Bit( "字母" ),tab3 );
    QLabel *vfhcolor = new QLabel( QString::fromLocal8Bit( "符号" ),tab3 );
    vbjcolorb = new QPushButton( tab3 );
    palette.setColor( vbjcolorb->backgroundRole(), QColor( 220, 220, 220 ) );
    vbjcolorb->setPalette( palette );
    vzmcolorb = new QPushButton( tab3 );
    palette.setColor( vzmcolorb->backgroundRole(), QColor( 80, 0, 0 ) );
    vzmcolorb->setPalette( palette );
    vfhcolorb = new QPushButton( tab3 );
    palette.setColor( vfhcolorb->backgroundRole(), QColor( 0, 0, 0 ) );
    vfhcolorb->setPalette( palette );
    colorlay->addWidget( vbjcolor,1,6 );
    colorlay->addWidget( vbjcolorb,1,7 );
    colorlay->addWidget( vzmcolor,2,6 );
    colorlay->addWidget( vzmcolorb,2,7 );
    colorlay->addWidget( vfhcolor,3,6 );
    colorlay->addWidget( vfhcolorb,3,7 );
    tablay3->addSpacing( 2 );
    tablay3->addLayout( colorlay );

    tablay3->addStretch();

    tabWidget->addTab( tab3, QString::fromLocal8Bit( "界面" ) );

    QWidget *tab4 = new QWidget( this );
    QVBoxLayout *tablay4 = new QVBoxLayout( tab4 );

    QGridLayout *keyglay = new QGridLayout;
    QLabel *conkey = new QLabel( QString::fromLocal8Bit( "打开/关闭输入法" ),tab4 );
    conkeyinput = new QLineEdit( "CTRL_SPACE",tab4 );
    QLabel *ceconv = new QLabel( QString::fromLocal8Bit( "中英文快速切换键" ),tab4 );
    ecconvbox = new QComboBox( tab4 );
    ecconvbox->addItem( "L_CTRL" );
    ecconvbox->addItem( "R_CTRL" );
    ecconvbox->addItem( "L_SHIFT" );
    ecconvbox->addItem( "R_SHIFT" );
    ecconvbox->addItem( "L_SUPER" );
    ecconvbox->addItem( "R_SUPER" );
    QLabel *gbkey = new QLabel( QString::fromLocal8Bit( "光标跟随" ),tab4 );
    gbkeyinput = new QLineEdit( "CTRL_K",tab4 );
    QLabel *hidemainwindowkey = new QLabel( QString::fromLocal8Bit( "隐藏主窗口" ),tab4 );
    hidemainwindowkeyinput = new QLineEdit( "CTRL_ALT_H",tab4 );
    QLabel *vkbkey = new QLabel( QString::fromLocal8Bit( "切换虚拟键盘" ),tab4 );
    vkbkeyinput = new QLineEdit( "CTRL_ALT_K",tab4 );
    QLabel *gbkkey = new QLabel( QString::fromLocal8Bit( "GBK 支持" ),tab4 );
    gbkkeyinput = new QLineEdit( "CTRL_M",tab4 );
    QLabel *gbkfkey = new QLabel( QString::fromLocal8Bit( "GBK 繁体切换键" ),tab4 );
    gbkfkeyinput = new QLineEdit( "CTRL_ALT_F",tab4 );
    QLabel *lenkey = new QLabel( QString::fromLocal8Bit( "联想" ),tab4 );
    lenkeyinput = new QLineEdit( "CTRL_L",tab4 );
    QLabel *pinyinkey = new QLabel( QString::fromLocal8Bit( "反查拼音" ),tab4 );
    pinyininput = new QLineEdit( "CTRL_ALT_E",tab4 );
    QLabel *dbcase = new QLabel( QString::fromLocal8Bit( "全半角切换" ),tab4 );
    dbcaseinput = new QLineEdit( "SHIFT_SPACE",tab4 );
    QLabel *cbd = new QLabel( QString::fromLocal8Bit( "中文标点" ),tab4 );
    cbdinput = new QLineEdit( "ALT_SPACE",tab4 );
    QLabel *prev = new QLabel( QString::fromLocal8Bit( "上一页" ),tab4 );
    previnput = new QLineEdit( ",",tab4 );
    QLabel *next = new QLabel( QString::fromLocal8Bit( "下一页" ),tab4 );
    nextinput = new QLineEdit( ".",tab4 );
    QLabel *sfkey = new QLabel( QString::fromLocal8Bit( "第二三候选词" ),tab4 );
    sfkeyinput = new QLineEdit( "SHIFT",tab4 );
    QLabel *savedictkey = new QLabel( QString::fromLocal8Bit( "保存词库" ),tab4 );
    savedictkeyinput = new QLineEdit( "CTRL_ALT_S",tab4 );
    QLabel *recordmodekey = new QLabel( QString::fromLocal8Bit( "记录模式" ),tab4 );
    recordmodekeyinput = new QLineEdit( "CTRL_ALT_J",tab4 );

    keyglay->addWidget( conkey,0,0 );
    keyglay->addWidget( conkeyinput,0,1 );
    keyglay->addWidget( ceconv,0,2 );
    keyglay->addWidget( ecconvbox,0,3 );
    keyglay->addWidget( gbkey,0,4 );
    keyglay->addWidget( gbkeyinput,0,5 );
    keyglay->addWidget( gbkkey,1,0 );
    keyglay->addWidget( gbkkeyinput,1,1 );
    keyglay->addWidget( gbkfkey,1,2 );
    keyglay->addWidget( gbkfkeyinput,1,3 );
    keyglay->addWidget( lenkey,1,4 );
    keyglay->addWidget( lenkeyinput,1,5 );
    keyglay->addWidget( pinyinkey,2,0 );
    keyglay->addWidget( pinyininput,2,1 );
    keyglay->addWidget( dbcase,2,2 );
    keyglay->addWidget( dbcaseinput,2,3 );
    keyglay->addWidget( cbd,2,4 );
    keyglay->addWidget( cbdinput,2,5 );
    keyglay->addWidget( prev,3,0 );
    keyglay->addWidget( previnput,3,1 );
    keyglay->addWidget( next,3,2 );
    keyglay->addWidget( nextinput,3,3 );
    keyglay->addWidget( sfkey,3,4 );
    keyglay->addWidget( sfkeyinput,3,5 );
    keyglay->addWidget( hidemainwindowkey,4,0 );
    keyglay->addWidget( hidemainwindowkeyinput,4,1 );
    keyglay->addWidget( vkbkey,4,2 );
    keyglay->addWidget( vkbkeyinput,4,3 );
    keyglay->addWidget( savedictkey,4,4 );
    keyglay->addWidget( savedictkeyinput,4,5 );
    keyglay->addWidget( recordmodekey,5,0 );
    keyglay->addWidget( recordmodekeyinput,5,1 );
    keyglay->setAlignment( Qt::AlignTop );
    tablay4->addLayout( keyglay );

    QLabel *keynote = new QLabel( QString::fromLocal8Bit( "<b><font color=red>注意：</font><font color=black>每个热健可以设置成两个，中间用空格隔开。</font></b>" ),tab4 );
    tablay4->addWidget( keynote );

    QHBoxLayout *dbclicklay = new QHBoxLayout;
    dbclickbox = new QCheckBox( QString::fromLocal8Bit( "双击切换中英文" ),tab4 );
    dbclickbox->setChecked( false );
    QLabel *clicktime = new QLabel( QString::fromLocal8Bit( "击键时间间隔：" ),tab4 );
    clicktimebox = new QSpinBox( /*100,500,10,*/tab4 );
    clicktimebox->setValue( 250 );
    dbclicklay->addWidget( dbclickbox );
    dbclicklay->addWidget( clicktime );
    dbclicklay->addWidget( clicktimebox );
    dbclicklay->addStretch();
    dbclicklay->setAlignment( Qt::AlignTop );
    tablay4->addLayout( dbclicklay );
    tablay4->addStretch();

    tabWidget->addTab( tab4, QString::fromLocal8Bit( "热键" ) );

    QWidget *tab5 = new QWidget( this );
    QVBoxLayout *tablay5 = new QVBoxLayout( tab5 );

    QHBoxLayout *pinyinbox = new QHBoxLayout;
    usepinyin = new QCheckBox( QString::fromLocal8Bit( "使用拼音" ),tab5 );
    usepinyin->setChecked( true );
    QLabel *pinyinname = new QLabel( QString::fromLocal8Bit( "拼音名称" ),tab5 );
    pinyinnameinput = new QLineEdit( QString::fromLocal8Bit( "智能拼音" ),tab5 );
    pinyinbox->addWidget( usepinyin );
    pinyinbox->addWidget( pinyinname );
    pinyinbox->addWidget( pinyinnameinput );
    pinyinbox->addStretch();
    tablay5->addLayout( pinyinbox );

    QHBoxLayout *quweibox = new QHBoxLayout;
    usequwei = new QCheckBox( QString::fromLocal8Bit( "使用区位" ),tab5 );
    usequwei->setChecked( true );
    QLabel *quweiname = new QLabel( QString::fromLocal8Bit( "区位名称" ),tab5 );
    quweinameinput = new QLineEdit( QString::fromLocal8Bit( "区位" ),tab5 );
    quweibox->addWidget( usequwei );
    quweibox->addWidget( quweiname );
    quweibox->addWidget( quweinameinput );
    quweibox->addStretch();
    tablay5->addLayout( quweibox );

    QHBoxLayout *mabox = new QHBoxLayout;
    usema = new QCheckBox( QString::fromLocal8Bit( "使用码表" ),tab5 );
    usema->setChecked( true );
    usecizu = new QCheckBox( QString::fromLocal8Bit( "提示词库中的词组" ),tab5 );
    usecizu->setChecked( true );
    mabox->addWidget( usema );
    mabox->addWidget( usecizu );
    mabox->addStretch();
    tablay5->addLayout( mabox );

    QHBoxLayout *spinbox = new QHBoxLayout;
    usespin = new QCheckBox( QString::fromLocal8Bit( "使用双拼" ),tab5 );
    QLabel *spinname = new QLabel( QString::fromLocal8Bit( "双拼名称" ),tab5 );
    spinnameinput = new QLineEdit( QString::fromLocal8Bit( "智能双拼" ),tab5 );
    QLabel *spinfa = new QLabel( QString::fromLocal8Bit( "默认双拼方案" ),tab5 );
    spinfabox = new QComboBox( tab5 );
    spinfabox->addItem( QString::fromLocal8Bit( "自然码" ) );
    spinfabox->addItem( QString::fromLocal8Bit( "微软" ) );
    spinfabox->addItem( QString::fromLocal8Bit( "紫光" ) );
    spinfabox->addItem( QString::fromLocal8Bit( "智能 ABC" ) );
    spinfabox->addItem( QString::fromLocal8Bit( "中文之星" ) );
    spinfabox->addItem( QString::fromLocal8Bit( "拼音加加" ) );
    spinbox->addWidget( usespin );
    spinbox->addWidget( spinname );
    spinbox->addWidget( spinnameinput );
    spinbox->addWidget( spinfa );
    spinbox->addWidget( spinfabox );
    spinbox->addStretch();
    tablay5->addLayout( spinbox );

    QHBoxLayout *otherimebox = new QHBoxLayout;
    QLabel *otherime = new QLabel( QString::fromLocal8Bit( "其他输入法" ),tab5 );
    otherimeinput = new QLineEdit( tab5 );// leave it empty
    otherimebox->addWidget( otherime );
    otherimebox->addWidget( otherimeinput );
    otherimebox->addStretch();
    tablay5->addLayout( otherimebox );

    tablay5->addStretch();

    tabWidget->addTab( tab5, QString::fromLocal8Bit( "输入法" ) );

    QWidget *tab6 = new QWidget( this );
    QVBoxLayout *tablay6 = new QVBoxLayout( tab6 );

    QHBoxLayout *lay61 = new QHBoxLayout;
    quanpin =new QCheckBox( QString::fromLocal8Bit( "使用全拼" ),tab6 );
    quanpin->setChecked( false );
    pinyinzuci = new QCheckBox( QString::fromLocal8Bit( "拼音自动组词" ),tab6 );
    pinyinzuci->setChecked( true );
    savezuci = new QCheckBox( QString::fromLocal8Bit( "保存自动组词" ),tab6 );
    savezuci->setChecked( true );
    lay61->addWidget( quanpin );
    lay61->addWidget( pinyinzuci );
    lay61->addWidget( savezuci );
    lay61->addStretch();
    tablay6->addLayout( lay61 );

    tablay6->addSpacing( 1 );
    QLabel *qkey = new QLabel( QString::fromLocal8Bit( "<b>快捷键：</b>" ),tab6 );
    tablay6->addWidget( qkey );

    QGridLayout *lay62 = new QGridLayout;
    QLabel *qkey1 = new QLabel( QString::fromLocal8Bit( "增加拼音常用字：" ),tab6 );
    qkey1input = new QLineEdit( "CTRL_8",tab6 );
    QLabel *qkey2 = new QLabel( QString::fromLocal8Bit( "删除拼音常用字：" ),tab6 );
    qkey2input = new QLineEdit( "CTRL_7",tab6 );
    QLabel *qkey3 = new QLabel( QString::fromLocal8Bit( "删除拼音用户词组：" ),tab6 );
    qkey3input = new QLineEdit( "CTRL_DELETE",tab6 );
    QLabel *qkey4 = new QLabel( QString::fromLocal8Bit( "拼音以词定字键：" ),tab6 );
    qkey4input = new QLineEdit( "[]",tab6 );
    lay62->addWidget( qkey1,0,0 );
    lay62->addWidget( qkey1input,0,1 );
    lay62->addWidget( qkey2,0,2 );
    lay62->addWidget( qkey2input,0,3 );
    lay62->addWidget( qkey3,1,0 );
    lay62->addWidget( qkey3input,1,1 );
    lay62->addWidget( qkey4,1,2 );
    lay62->addWidget( qkey4input,1,3 );
    tablay6->addLayout( lay62 );

    tablay6->addSpacing( 1 );
    QLabel *cm = new QLabel( QString::fromLocal8Bit( "<b>重码调整方式：</b>" ),tab6 );
    tablay6->addWidget( cm );

    QGridLayout *lay63 = new QGridLayout;
    QLabel *cm1 = new QLabel( QString::fromLocal8Bit( "拼音单字重码调整方式：" ),tab6 );
    cm1box = new QComboBox( tab6 );
    cm1box->addItem( QString::fromLocal8Bit( "不调整" ) );
    cm1box->addItem( QString::fromLocal8Bit( "快速调整" ) );
    cm1box->addItem( QString::fromLocal8Bit( "按频率调整" ) );
    cm1box->setCurrentIndex( 2 );
    QLabel *cm2 = new QLabel( QString::fromLocal8Bit( "拼音词组重码调整方式：" ),tab6 );
    cm2box = new QComboBox( tab6 );
    cm2box->addItem( QString::fromLocal8Bit( "不调整" ) );
    cm2box->addItem( QString::fromLocal8Bit( "快速调整" ) );
    cm2box->addItem( QString::fromLocal8Bit( "按频率调整" ) );
    cm2box->setCurrentIndex( 1 );
    QLabel *cm3 = new QLabel( QString::fromLocal8Bit( "拼音常用词重码调整方式：" ),tab6 );
    cm3box = new QComboBox( tab6 );
    cm3box->addItem( QString::fromLocal8Bit( "不调整" ) );
    cm3box->addItem( QString::fromLocal8Bit( "快速调整" ) );
    cm3box->addItem( QString::fromLocal8Bit( "按频率调整" ) );
    cm3box->setCurrentIndex( 1 );
    lay63->addWidget( cm1,0,0 );
    lay63->addWidget( cm1box,0,1 );
    lay63->addWidget( cm2,1,0 );
    lay63->addWidget( cm2box,1,1 );
    lay63->addWidget( cm3,2,0 );
    lay63->addWidget( cm3box,2,1 );
    tablay6->addLayout( lay63 );

    tablay6->addSpacing( 1 );
    QLabel *mh = new QLabel( QString::fromLocal8Bit( "<b>模糊音：</b>" ),tab6 );
    tablay6->addWidget( mh );

    QGridLayout *lay64 = new QGridLayout;
    mh1box = new QCheckBox( QString::fromLocal8Bit( "an 和 ang" ),tab6 );
    mh2box = new QCheckBox( QString::fromLocal8Bit( "en 和 eng" ),tab6 );
    mh3box = new QCheckBox( QString::fromLocal8Bit( "ian 和 iang" ),tab6 );
    mh4box = new QCheckBox( QString::fromLocal8Bit( "in 和 ing" ),tab6 );
    mh5box = new QCheckBox( QString::fromLocal8Bit( "ou 和 u" ),tab6 );
    mh6box = new QCheckBox( QString::fromLocal8Bit( "uan 和 uang" ),tab6 );
    mh7box = new QCheckBox( QString::fromLocal8Bit( "c 和 ch" ),tab6 );
    mh8box = new QCheckBox( QString::fromLocal8Bit( "f 和 h" ),tab6 );
    mh9box = new QCheckBox( QString::fromLocal8Bit( "l 和 n" ),tab6 );
    mh10box = new QCheckBox( QString::fromLocal8Bit( "s 和 sh" ),tab6 );
    mh11box = new QCheckBox( QString::fromLocal8Bit( "z 和 zh" ),tab6 );
    lay64->addWidget( mh1box,0,0 );
    lay64->addWidget( mh2box,0,1 );
    lay64->addWidget( mh3box,0,2 );
    lay64->addWidget( mh4box,0,3 );
    lay64->addWidget( mh5box,1,0 );
    lay64->addWidget( mh6box,1,1 );
    lay64->addWidget( mh7box,1,2 );
    lay64->addWidget( mh8box,1,3 );
    lay64->addWidget( mh9box,2,0 );
    lay64->addWidget( mh10box,2,1 );
    lay64->addWidget( mh11box,2,2 );
    tablay6->addLayout( lay64 );

    tablay6->addStretch();

    tabWidget->addTab( tab6, QString::fromLocal8Bit( "拼音" ) );

    LoadConfig();
    // connect( this,SIGNAL(applyButtonPressed()), this, SLOT( SaveConfig()));

    // NOTE: change current tab won't change the configuration, do not send this signal to configSlot(),
    // but if we do it correctly, almost every control widgets change signals will connect to configSlot(). That'll be a huge work.
    // We're lazy here....  ;)    --- nihui
    connect( tabWidget,SIGNAL( currentChanged( QWidget * ) ), this, SLOT( configSlot() ) );
    connect( cfontbutton,SIGNAL( clicked() ), this, SLOT( ChooseFontC() ) );
    connect( efontbutton,SIGNAL( clicked() ), this, SLOT( ChooseFontE() ) );

    /// TODO following codes are ugly, use qsignalmapper instead  --- nihui
    connect( gbcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor1() ) );
    connect( bjcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor2() ) );
    connect( xtcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor3() ) );
    connect( srfcolor1,SIGNAL( clicked() ), this, SLOT( ChooseColor4() ) );
    connect( srfcolor2,SIGNAL( clicked() ), this, SLOT( ChooseColor5() ) );
    connect( srfcolor3,SIGNAL( clicked() ), this, SLOT( ChooseColor6() ) );
    connect( sgbcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor7() ) );
    connect( stscolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor8() ) );
    connect( ssrcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor9() ) );
    connect( sxhcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor10() ) );
    connect( ssxcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor11() ) );
    connect( syhcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor12() ) );
    connect( sbmcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor13() ) );
    connect( sqtcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor14() ) );
    connect( sstcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor15() ) );
    connect( sjtcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor16() ) );
    connect( vbjcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor17() ) );
    connect( vzmcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor18() ) );
    connect( vfhcolorb,SIGNAL( clicked() ), this, SLOT( ChooseColor19() ) );
}

void TabDialog::LoadConfig()
{
    QString cfgpath = QDir::homePath() + "/.config/fcitx/config";
    if ( !QFile::exists( cfgpath ) ) {
        // try the default config file TODO: use FCITXDIR env, no hardcode path
        cfgpath = "/usr/share/fcitx/data/config";
    }

    QFile fconfig( cfgpath );
    if ( !fconfig.open( QIODevice::ReadOnly ) )
    {
        QMessageBox mbox( QMessageBox::Critical,
                          QString::fromLocal8Bit( "错误！" ),
                          QString::fromLocal8Bit( "无法打开配置文件！" ),
                          QMessageBox::Ok );
        mbox.exec();
        return;
    }
    QTextStream fileStream( &fconfig );
    QTextCodec *codec = QTextCodec::codecForName( "GBK" );
    fileStream.setCodec( codec );
    while ( !fileStream.atEnd() )
    {
        QString listString = fileStream.readLine();
        QString nameString = listString.section( "=",0,0 ).trimmed();
        QString valueString = listString.section( "=",1,1 ).trimmed();
        if ( valueString=="" ) valueString="=";
        int r = valueString.section( " ",0,0 ).trimmed().toInt();
        int g = valueString.section( " ",1,1 ).trimmed().toInt();
        int b = valueString.section( " ",2,2 ).trimmed().toInt();
        QPalette palette;
        //程序段
        if ( nameString==QString::fromLocal8Bit( "字体区域" ) ) { language->setCurrentIndex( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "显示字体(中)" ) ) {cfontinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "显示字体(英)" ) ) {efontinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "显示字体大小" ) ) {efontsizeinput->setValue( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "主窗口字体大小" ) ) {cfontsizeinput->setValue( valueString.toInt() );continue;}
//         if ( nameString==QString::fromLocal8Bit( "使用AA字体" ) ) {aabox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "使用粗体" ) ) {boldbox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "使用托盘图标" ) ) {traybox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "使用DBus接口" ) ) {dbusbox->setChecked( valueString.toInt() );continue;}
//         if ( nameString==QString::fromLocal8Bit( "静态模式" ) ) {staticbox->setChecked( valueString.toInt() );continue;}
        //输出段
        if ( nameString==QString::fromLocal8Bit( "数字后跟半角符号" ) ) {dbcbox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "Enter键行为" ) ) {entercombobox->setCurrentIndex( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "分号键行为" ) ) {semicombobox->setCurrentIndex( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "大写字母输入英文" ) ) {capbox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "转换英文中的标点" ) ) {interbox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "联想方式禁止翻页" ) ) {lennobox->setChecked( valueString.toInt() );continue;}
        //界面段
        if ( nameString==QString::fromLocal8Bit( "候选词个数" ) ) {candinput->setValue( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "主窗口使用3D界面" ) ) {main3dbox->setCurrentIndex( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入条使用3D界面" ) ) {input3dbox->setCurrentIndex( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "主窗口隐藏模式" ) ) {hidebox->setCurrentIndex( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "显示虚拟键盘" ) ) {vkeybox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入条居中" ) ) {centerbox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "首次显示输入条" ) ) {firstbox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入条固定宽度" ) ) {barposinput->setValue( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入条偏移量X" ) ) {barxinput->setValue( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入条偏移量Y" ) ) {baryinput->setValue( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "序号后加点" ) ) {pointbox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "显示打字速度" ) ) {typebox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "显示版本" ) ) {verbox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "光标色" ) ) {
            palette.setColor( gbcolorb->backgroundRole(), QColor( r,g,b ) ); gbcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "主窗口背景色" ) ) {
            palette.setColor( bjcolorb->backgroundRole(), QColor( r,g,b ) ); bjcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "主窗口线条色" ) ) { palette.setColor( xtcolorb->backgroundRole(), QColor( r,g,b ) ); xtcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "主窗口输入法名称色" ) ) {
            palette.setColor( srfcolor1->backgroundRole(), QColor( r,g,b ) ); srfcolor1->setPalette( palette );
            palette.setColor( srfcolor2->backgroundRole(), QColor( valueString.section( " ",3,3 ).toInt(),
                              valueString.section( " ",4,4 ).toInt(),valueString.section( " ",5,5 ).toInt() ) );
            srfcolor2->setPalette( palette );
            palette.setColor( srfcolor3->backgroundRole(), QColor( valueString.section( " ",6,6 ).toInt(),
                              valueString.section( " ",7,7 ).toInt(),valueString.section( " ",8,8 ).toInt() ) );
            srfcolor3->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入窗背景色" ) ) {
            palette.setColor( sgbcolorb->backgroundRole(), QColor( r,g,b ) ); sgbcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入窗提示色" ) ) {
            palette.setColor( stscolorb->backgroundRole(), QColor( r,g,b ) ); stscolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入窗用户输入色" ) ) {
            palette.setColor( ssrcolorb->backgroundRole(), QColor( r,g,b ) ); ssrcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入窗序号色" ) ) {
            palette.setColor( sxhcolorb->backgroundRole(), QColor( r,g,b ) ); sxhcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入窗第一个候选字色" ) ) {
            palette.setColor( ssxcolorb->backgroundRole(), QColor( r,g,b ) ); ssxcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入窗用户词组色" ) ) {
            palette.setColor( syhcolorb->backgroundRole(), QColor( r,g,b ) ); syhcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入窗提示编码色" ) ) {
            palette.setColor( sbmcolorb->backgroundRole(), QColor( r,g,b ) ); sbmcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入窗其它文本色" ) ) {
            palette.setColor( sqtcolorb->backgroundRole(), QColor( r,g,b ) ); sqtcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入窗线条色" ) ) {
            palette.setColor( sstcolorb->backgroundRole(), QColor( r,g,b ) ); sstcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "输入窗箭头色" ) ) {
            palette.setColor( sjtcolorb->backgroundRole(), QColor( r,g,b ) ); sjtcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "虚拟键盘窗背景色" ) ) {
            palette.setColor( vbjcolorb->backgroundRole(), QColor( r,g,b ) ); vbjcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "虚拟键盘窗字母色" ) ) {
            palette.setColor( vzmcolorb->backgroundRole(), QColor( r,g,b ) ); vzmcolorb->setPalette( palette );continue;}
        if ( nameString==QString::fromLocal8Bit( "虚拟键盘窗符号色" ) ) {
            palette.setColor( vfhcolorb->backgroundRole(), QColor( r,g,b ) ); vfhcolorb->setPalette( palette );continue;}
        //热键段
        if ( nameString==QString::fromLocal8Bit( "打开/关闭输入法" ) ) {conkeyinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "中英文快速切换键" ) ) {ecconvbox->setCurrentIndex( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "双击中英文切换" ) ) {dbclickbox->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "击键时间间隔" ) ) {clicktimebox->setValue( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "光标跟随" ) ) {gbkeyinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "隐藏主窗口" ) ) {hidemainwindowkeyinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "切换虚拟键盘" ) ) {vkbkeyinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "GBK支持" ) ) {gbkkeyinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "GBK繁体切换键" ) ) {gbkfkeyinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "联想" ) ) {lenkeyinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "反查拼音" ) ) {pinyininput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "全半角" ) ) {dbcaseinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "中文标点" ) ) {cbdinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "上一页" ) ) {previnput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "下一页" ) ) {nextinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "第二三候选词选择键" ) ) {sfkeyinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "保存词库" ) ) {savedictkeyinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "记录模式" ) ) {recordmodekeyinput->setText( valueString );continue;}
        //输入法段
        if ( nameString==QString::fromLocal8Bit( "使用拼音" ) ) {usepinyin->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "拼音名称" ) ) {pinyinnameinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "使用双拼" ) ) {usespin->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "双拼名称" ) ) {spinnameinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "默认双拼方案" ) ) {spinfabox->setCurrentIndex( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "使用区位" ) ) {usequwei->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "区位名称" ) ) {quweinameinput->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "使用码表" ) ) {usema->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "提示词库中的词组" ) ) {usecizu->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "其他输入法" ) ) {otherimeinput->setText( valueString );continue;}
        //拼音段
        if ( nameString==QString::fromLocal8Bit( "使用全拼" ) ) {quanpin->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "拼音自动组词" ) ) {pinyinzuci->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "保存自动组词" ) ) {savezuci->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "增加拼音常用字" ) ) {qkey1input->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "删除拼音常用字" ) ) {qkey2input->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "删除拼音用户词组" ) ) {qkey3input->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "拼音以词定字键" ) ) {qkey4input->setText( valueString );continue;}
        if ( nameString==QString::fromLocal8Bit( "拼音单字重码调整方式" ) ) {cm1box->setCurrentIndex( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "拼音词组重码调整方式" ) ) {cm2box->setCurrentIndex( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "拼音常用词重码调整方式" ) ) {cm3box->setCurrentIndex( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "模糊an和ang" ) ) {mh1box->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "模糊en和eng" ) ) {mh2box->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "模糊ian和iang" ) ) {mh3box->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "模糊in和ing" ) ) {mh4box->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "模糊ou和u" ) ) {mh5box->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "模糊uan和uang" ) ) {mh6box->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "模糊c和ch" ) ) {mh7box->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "模糊f和h" ) ) {mh8box->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "模糊l和n" ) ) {mh9box->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "模糊s和sh" ) ) {mh10box->setChecked( valueString.toInt() );continue;}
        if ( nameString==QString::fromLocal8Bit( "模糊z和zh" ) ) {mh11box->setChecked( valueString.toInt() );continue;}

    }
    fconfig.close();
}

void TabDialog::SaveConfig()
{
    QFile fconfig( QDir::homePath() + "/.config/fcitx/config" );
    if ( !fconfig.open( QIODevice::WriteOnly ) )
    {
        QMessageBox mbox( QMessageBox::Critical,
                          QString::fromLocal8Bit( "错误！" ),
                          QString::fromLocal8Bit( "无法打开或建立配置文件！" ),
                          QMessageBox::Ok );
        mbox.exec();
        return;
    }
    QTextStream fileStream(&fconfig );
    QTextCodec *codec = QTextCodec::codecForName( "GBK" );
    fileStream.setCodec( codec );

    fileStream<<QString::fromLocal8Bit( "[程序]" ) <<endl;
    //程序段
    fileStream<<QString::fromLocal8Bit( "#如果你的Fcitx工作很正常，没有必要修改下面这个设置" ) <<endl;
//     fileStream<<QString::fromLocal8Bit( "静态模式=" ) <<staticbox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "显示字体(中)=" ) <<cfontinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "显示字体(英)=" ) <<efontinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "显示字体大小=" ) <<efontsizeinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "主窗口字体大小=" ) <<cfontsizeinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "字体区域=" ) <<language->currentText() <<endl;
//     fileStream<<QString::fromLocal8Bit( "使用AA字体=" ) <<aabox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "使用粗体=" ) <<boldbox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "使用托盘图标=" ) <<traybox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "使用DBus接口=" ) <<dbusbox->isChecked() <<endl;
    fileStream<<endl;
    //输出段
    fileStream<<QString::fromLocal8Bit( "[输出]" ) <<endl;
    fileStream<<QString::fromLocal8Bit( "数字后跟半角符号=" ) <<dbcbox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "Enter键行为=" ) <<entercombobox->currentIndex() <<endl;
    fileStream<<QString::fromLocal8Bit( "分号键行为=" ) <<semicombobox->currentIndex() <<endl;
    fileStream<<QString::fromLocal8Bit( "大写字母输入英文=" ) <<capbox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "转换英文中的标点=" ) <<interbox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "联想方式禁止翻页=" ) <<lennobox->isChecked() <<endl;
    fileStream<<endl;
    //界面段
    fileStream<<QString::fromLocal8Bit( "[界面]" ) <<endl;
    fileStream<<QString::fromLocal8Bit( "候选词个数=" ) <<candinput->value() <<endl;
    fileStream<<QString::fromLocal8Bit( "主窗口使用3D界面=" ) <<main3dbox->currentIndex() <<endl;
    fileStream<<QString::fromLocal8Bit( "输入条使用3D界面=" ) <<input3dbox->currentIndex() <<endl;
    fileStream<<QString::fromLocal8Bit( "主窗口隐藏模式=" ) <<hidebox->currentIndex() <<endl;
    fileStream<<QString::fromLocal8Bit( "显示虚拟键盘=" ) <<vkeybox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "输入条是否居中=" ) <<centerbox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "首次显示输入条=" ) <<firstbox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "#输入条固定宽度(仅适用于码表输入法)，0表示不固定宽度" ) <<endl;
    fileStream<<QString::fromLocal8Bit( "输入条固定宽度=" ) <<barposinput->value() <<endl;
    fileStream<<QString::fromLocal8Bit( "输入条偏移量X=" ) <<barxinput->value() <<endl;
    fileStream<<QString::fromLocal8Bit( "输入条偏移量Y=" ) <<baryinput->value() <<endl;
    fileStream<<QString::fromLocal8Bit( "序号后加点=" ) <<pointbox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "显示打字速度=" ) <<typebox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "显示版本=" ) <<verbox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "光标色=" )
    <<gbcolorb->palette().color( gbcolorb->backgroundRole() ).red() <<" "
    <<gbcolorb->palette().color( gbcolorb->backgroundRole() ).green() <<" "
    <<gbcolorb->palette().color( gbcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "主窗口背景色=" )
    <<bjcolorb->palette().color( bjcolorb->backgroundRole() ).red() <<" "
    <<bjcolorb->palette().color( bjcolorb->backgroundRole() ).green() <<" "
    <<bjcolorb->palette().color( bjcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "主窗口线条色=" )
    <<xtcolorb->palette().color( xtcolorb->backgroundRole() ).red() <<" "
    <<xtcolorb->palette().color( xtcolorb->backgroundRole() ).green() <<" "
    <<xtcolorb->palette().color( xtcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "主窗口输入法名称色=" )
    <<srfcolor1->palette().color( srfcolor1->backgroundRole() ).red() <<" "
    <<srfcolor1->palette().color( srfcolor1->backgroundRole() ).green() <<" "
    <<srfcolor1->palette().color( srfcolor1->backgroundRole() ).blue() <<" "
    <<srfcolor2->palette().color( srfcolor2->backgroundRole() ).red() <<" "
    <<srfcolor2->palette().color( srfcolor2->backgroundRole() ).green() <<" "
    <<srfcolor2->palette().color( srfcolor2->backgroundRole() ).blue() <<" "
    <<srfcolor3->palette().color( srfcolor3->backgroundRole() ).red() <<" "
    <<srfcolor3->palette().color( srfcolor3->backgroundRole() ).green() <<" "
    <<srfcolor3->palette().color( srfcolor3->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "输入窗背景色=" )
    <<sgbcolorb->palette().color( sgbcolorb->backgroundRole() ).red() <<" "
    <<sgbcolorb->palette().color( sgbcolorb->backgroundRole() ).green() <<" "
    <<sgbcolorb->palette().color( sgbcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "输入窗提示色=" )
    <<stscolorb->palette().color( stscolorb->backgroundRole() ).red() <<" "
    <<stscolorb->palette().color( stscolorb->backgroundRole() ).green() <<" "
    <<stscolorb->palette().color( stscolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "输入窗用户输入色=" )
    <<ssrcolorb->palette().color( ssrcolorb->backgroundRole() ).red() <<" "
    <<ssrcolorb->palette().color( ssrcolorb->backgroundRole() ).green() <<" "
    <<ssrcolorb->palette().color( ssrcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "输入窗序号色=" )
    <<sxhcolorb->palette().color( sxhcolorb->backgroundRole() ).red() <<" "
    <<sxhcolorb->palette().color( sxhcolorb->backgroundRole() ).green() <<" "
    <<sxhcolorb->palette().color( sxhcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "输入窗第一个候选字色=" )
    <<ssxcolorb->palette().color( ssxcolorb->backgroundRole() ).red() <<" "
    <<ssxcolorb->palette().color( ssxcolorb->backgroundRole() ).green() <<" "
    <<ssxcolorb->palette().color( ssxcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "#该颜色值只用于拼音中的用户自造词" ) <<endl;
    fileStream<<QString::fromLocal8Bit( "输入窗用户词组色=" )
    <<syhcolorb->palette().color( syhcolorb->backgroundRole() ).red() <<" "
    <<syhcolorb->palette().color( syhcolorb->backgroundRole() ).green() <<" "
    <<syhcolorb->palette().color( syhcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "输入窗提示编码色=" )
    <<sbmcolorb->palette().color( sbmcolorb->backgroundRole() ).red() <<" "
    <<sbmcolorb->palette().color( sbmcolorb->backgroundRole() ).green() <<" "
    <<sbmcolorb->palette().color( sbmcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "#五笔、拼音中的单字/系统词组均使用该姿色" ) <<endl;
    fileStream<<QString::fromLocal8Bit( "输入窗其它文本色=" )
    <<sqtcolorb->palette().color( sqtcolorb->backgroundRole() ).red() <<" "
    <<sqtcolorb->palette().color( sqtcolorb->backgroundRole() ).green() <<" "
    <<sqtcolorb->palette().color( sqtcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "输入窗线条色=" )
    <<sstcolorb->palette().color( sstcolorb->backgroundRole() ).red() <<" "
    <<sstcolorb->palette().color( sstcolorb->backgroundRole() ).green() <<" "
    <<sstcolorb->palette().color( sstcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "输入窗箭头色=" )
    <<sjtcolorb->palette().color( sjtcolorb->backgroundRole() ).red() <<" "
    <<sjtcolorb->palette().color( sjtcolorb->backgroundRole() ).green() <<" "
    <<sjtcolorb->palette().color( sjtcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "虚拟键盘窗背景色=" )
    <<vbjcolorb->palette().color( vbjcolorb->backgroundRole() ).red() <<" "
    <<vbjcolorb->palette().color( vbjcolorb->backgroundRole() ).green() <<" "
    <<vbjcolorb->palette().color( vbjcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "虚拟键盘窗字母色=" )
    <<vzmcolorb->palette().color( vzmcolorb->backgroundRole() ).red() <<" "
    <<vzmcolorb->palette().color( vzmcolorb->backgroundRole() ).green() <<" "
    <<vzmcolorb->palette().color( vzmcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<QString::fromLocal8Bit( "虚拟键盘窗符号色=" )
    <<vfhcolorb->palette().color( vfhcolorb->backgroundRole() ).red() <<" "
    <<vfhcolorb->palette().color( vfhcolorb->backgroundRole() ).green() <<" "
    <<vfhcolorb->palette().color( vfhcolorb->backgroundRole() ).blue() <<endl;
    fileStream<<endl;
    //热键段
    fileStream<<QString::fromLocal8Bit( "#除了“中英文快速切换键”外，其它的热键都可以设置为两个，中间用空格分隔" ) <<endl;
    fileStream<<QString::fromLocal8Bit( "[热键]" ) <<endl;
    fileStream<<QString::fromLocal8Bit( "打开/关闭输入法=" ) <<conkeyinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "#中英文快速切换键 可以设置为L_CTRL R_CTRL L_SHIFT R_SHIFT L_SUPER R_SUPER" ) << endl;
    fileStream<<QString::fromLocal8Bit( "中英文快速切换键=" ) <<ecconvbox->currentText() <<endl;
    fileStream<<QString::fromLocal8Bit( "双击中英文切换=" ) <<dbclickbox->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "击键时间间隔=" ) <<clicktimebox->value() <<endl;
    fileStream<<QString::fromLocal8Bit( "光标跟随=" ) <<gbkeyinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "隐藏主窗口=" ) <<hidemainwindowkeyinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "切换虚拟键盘=" ) <<vkbkeyinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "GBK支持=" ) <<gbkkeyinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "GBK繁体切换键=" ) <<gbkfkeyinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "联想=" ) <<lenkeyinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "反查拼音=" ) <<pinyininput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "全半角=" ) <<dbcaseinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "中文标点=" ) <<cbdinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "上一页=" ) <<previnput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "下一页=" ) <<nextinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "第二三候选词选择键=" ) <<sfkeyinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "保存词库=" ) <<savedictkeyinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "记录模式=" ) <<recordmodekeyinput->text().trimmed() <<endl;
    fileStream<<endl;
    //输入法段
    fileStream<<QString::fromLocal8Bit( "[输入法]" ) <<endl;
    fileStream<<QString::fromLocal8Bit( "使用拼音=" ) <<usepinyin->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "拼音名称=" ) <<pinyinnameinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "使用双拼=" ) <<usespin->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "双拼名称=" ) <<spinnameinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "默认双拼方案=" ) <<spinfabox->currentText() <<endl;
    fileStream<<QString::fromLocal8Bit( "使用区位=" ) <<usequwei->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "区位名称=" ) <<quweinameinput->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "使用码表=" ) <<usema->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "提示词库中的词组=" ) <<usecizu->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "其他输入法=" ) <<otherimeinput->text().trimmed() <<endl;
    fileStream<<endl;
    //拼音段
    fileStream<<QString::fromLocal8Bit( "[拼音]" ) <<endl;
    fileStream<<QString::fromLocal8Bit( "使用全拼=" ) <<quanpin->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "拼音自动组词=" ) <<pinyinzuci->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "保存自动组词=" ) <<savezuci->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "增加拼音常用字=" ) <<qkey1input->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "删除拼音常用字=" ) <<qkey2input->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "删除拼音用户词组=" ) <<qkey3input->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "#拼音以词定字键，等号后面紧接键，不要有空格" ) <<endl;
    fileStream<<QString::fromLocal8Bit( "拼音以词定字键=" ) <<qkey4input->text().trimmed() <<endl;
    fileStream<<QString::fromLocal8Bit( "#重码调整方式说明：0-->不调整　1-->快速调整 2-->按频率调整" ) <<endl;
    fileStream<<QString::fromLocal8Bit( "拼音单字重码调整方式=" ) <<cm1box->currentIndex() <<endl;
    fileStream<<QString::fromLocal8Bit( "拼音词组重码调整方式=" ) <<cm2box->currentIndex() <<endl;
    fileStream<<QString::fromLocal8Bit( "拼音常用词重码调整方式=" ) <<cm3box->currentIndex() <<endl;
    fileStream<<QString::fromLocal8Bit( "模糊an和ang=" ) <<mh1box->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "模糊en和eng=" ) <<mh2box->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "模糊ian和iang=" ) <<mh3box->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "模糊in和ing=" ) <<mh4box->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "模糊ou和u=" ) <<mh5box->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "模糊uan和uang=" ) <<mh6box->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "模糊c和ch=" ) <<mh7box->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "模糊f和h=" ) <<mh8box->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "模糊l和n=" ) <<mh9box->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "模糊s和sh=" ) <<mh10box->isChecked() <<endl;
    fileStream<<QString::fromLocal8Bit( "模糊z和zh=" ) <<mh11box->isChecked() <<endl;

    fconfig.close();

    // restart fcitx to apply the changes
    QProcess *killall = new QProcess( this );
    QString killallprogram = "killall";
    QStringList killallarguments;
    killallarguments << "fcitx";
    killall->execute( killallprogram, killallarguments );
    system( "fcitx -d" );
}

void TabDialog::ChooseFontC()
{
    bool ok;
    QFont font = QFontDialog::getFont( &ok,this );
    if ( ok )
        cfontinput->setText( font.family() );
}

void TabDialog::ChooseFontE()
{
    bool ok;
    QFont font = QFontDialog::getFont( &ok,this );
    if ( ok )
        efontinput->setText( font.family() );
}

void TabDialog::ChooseColor1()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( gbcolorb->backgroundRole(), cdialog->getColor() );
    gbcolorb->setPalette( palette );
}

void TabDialog::ChooseColor2()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( bjcolorb->backgroundRole(), cdialog->getColor() );
    bjcolorb->setPalette( palette );
}

void TabDialog::ChooseColor3()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( xtcolorb->backgroundRole(), cdialog->getColor() );
    xtcolorb->setPalette( palette );
}

void TabDialog::ChooseColor4()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( srfcolor1->backgroundRole(), cdialog->getColor() );
    srfcolor1->setPalette( palette );
}

void TabDialog::ChooseColor5()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( srfcolor2->backgroundRole(), cdialog->getColor() );
    srfcolor2->setPalette( palette );
}

void TabDialog::ChooseColor6()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( srfcolor3->backgroundRole(), cdialog->getColor() );
    srfcolor3->setPalette( palette );
}

void TabDialog::ChooseColor7()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( sgbcolorb->backgroundRole(), cdialog->getColor() );
    sgbcolorb->setPalette( palette );
}

void TabDialog::ChooseColor8()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( stscolorb->backgroundRole(), cdialog->getColor() );
    stscolorb->setPalette( palette );
}

void TabDialog::ChooseColor9()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( ssrcolorb->backgroundRole(), cdialog->getColor() );
    ssrcolorb->setPalette( palette );
}

void TabDialog::ChooseColor10()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( sxhcolorb->backgroundRole(), cdialog->getColor() );
    sxhcolorb->setPalette( palette );
}

void TabDialog::ChooseColor11()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( ssxcolorb->backgroundRole(), cdialog->getColor() );
    ssxcolorb->setPalette( palette );
}

void TabDialog::ChooseColor12()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( syhcolorb->backgroundRole(), cdialog->getColor() );
    syhcolorb->setPalette( palette );
}

void TabDialog::ChooseColor13()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( sbmcolorb->backgroundRole(), cdialog->getColor() );
    sbmcolorb->setPalette( palette );
}

void TabDialog::ChooseColor14()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( sqtcolorb->backgroundRole(), cdialog->getColor() );
    sqtcolorb->setPalette( palette );
}

void TabDialog::ChooseColor15()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( sstcolorb->backgroundRole(), cdialog->getColor() );
    sstcolorb->setPalette( palette );
}

void TabDialog::ChooseColor16()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( sjtcolorb->backgroundRole(), cdialog->getColor() );
    sjtcolorb->setPalette( palette );
}

void TabDialog::ChooseColor17()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( vbjcolorb->backgroundRole(), cdialog->getColor() );
    vbjcolorb->setPalette( palette );
}

void TabDialog::ChooseColor18()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( vzmcolorb->backgroundRole(), cdialog->getColor() );
    vzmcolorb->setPalette( palette );
}

void TabDialog::ChooseColor19()
{
    QColorDialog *cdialog;

    QPalette palette;
    palette.setColor( vfhcolorb->backgroundRole(), cdialog->getColor() );
    vfhcolorb->setPalette( palette );
}

void TabDialog::configSlot()
{
    emit configChanged();
}
