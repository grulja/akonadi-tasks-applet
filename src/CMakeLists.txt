set(plasma_akonaditasks_SRCS
   model.cpp
   modelitem.cpp
   sortfiltermodel.cpp
   qmlplugins.cpp
)

kde4_add_library(plasmaakonaditasksplugins SHARED ${plasma_akonaditasks_SRCS})

target_link_libraries(plasmaakonaditasksplugins
    ${QT_QTDECLARATIVE_LIBRARY}
    ${KDE4_KCALCORE_LIBS}
    ${KDE4_KIO_LIBS}
    ${KDE4_PLASMA_LIBS}
    ${KDEPIMLIBS_KABC_LIBS}
    ${KDEPIMLIBS_AKONADI_LIBS})

install(TARGETS plasmaakonaditasksplugins DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/akonaditasks)
install(FILES qmldir DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/akonaditasks)

add_subdirectory(applet)
