include(MacroLibrary)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(${QT_INCLUDES} ${KDE4_INCLUDES})

########### next target ###############

set(kcm_fcitxconfig_SRCS
    fcitxconfig.cpp
    tabdialog.cpp)

kde4_add_plugin(kcm_fcitxconfig ${kcm_fcitxconfig_SRCS})

target_link_libraries(kcm_fcitxconfig ${KDE4_KIO_LIBS} ${QT_LIBRARY})

########### install files ###############

install(TARGETS kcm_fcitxconfig DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES fcitxconfig.desktop DESTINATION ${SERVICES_INSTALL_DIR})
kde4_install_icons(${ICON_INSTALL_DIR})
