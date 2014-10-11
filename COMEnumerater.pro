QT += core gui widgets axcontainer
TARGET = COMEnumerater
TEMPLATE = app


SOURCES += \
    main.cpp\
    mainwindow.cpp

HEADERS  += \
    mainwindow.h

FORMS    += \
    mainwindow.ui

OTHER_FILES += \
    resource.rc \
    tools.ico

RC_FILE  += \
    resource.rc
