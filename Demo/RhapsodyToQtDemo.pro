QT -= gui

CONFIG += console c++11
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    kroki/IKrokiBilgiServisi.cpp \
    kroki/IKrokiYoneticisi.cpp \
    kroki/KrokiBilgiServisi.cpp \
    kroki/KrokiYoneticisi.cpp \
    kroki/CompositeInterfaceClass.cpp \
    main.cpp \
    kroki/ISoyutHaberlesmeYoneticisi.cpp \
    kroki/HaberlesmeYoneticisi.cpp \
    kroki/IHaberlesmeYoneticisi.cpp

HEADERS += \
    kroki/IKrokiBilgiServisi.h \
    kroki/IKrokiYoneticisi.h \
    kroki/KrokiBilgiServisi.h \
    kroki/KrokiYoneticisi.h \
    kroki/icompositeinterface.h \
    kroki/CompositeInterfaceClass.h \
    commonfiles.h \
    kroki/olaypaketi.h \
    kroki/ISoyutHaberlesmeYoneticisi.h \
    kroki/HaberlesmeYoneticisi.h \
    kroki/IHaberlesmeYoneticisi.h

win32:CONFIG(release, debug|release|profile): LIBS += -L$(QTFY_DIR)/release/ -lQtfy
else:win32:CONFIG(debug, debug|release|profile): LIBS += -L$(QTFY_DIR)/debug/ -lQtfy
else:win32:CONFIG(profile, debug|release|profile): LIBS += -L$(QTFY_DIR)/release/ -lQtfy

DEPENDPATH += $(QTFY_DIR)/debug

INCLUDEPATH += $(QTFY_DIR) .
