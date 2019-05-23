#-------------------------------------------------
#
# Project created by QtCreator 2018-12-28T14:32:39
#
#-------------------------------------------------

QT       -= gui

TARGET = Qtfy
TEMPLATE = lib
CONFIG += staticlib c++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

## VS 2012 Compiler Flag additions. all pro files should be implemented these lines
win32:CONFIG(debug, debug|release|profile): QMAKE_CXXFLAGS += /GS /W3 /Gm /Od /sdl /WX- /Zc:forScope /RTC1 /Gd /Oy- /D "_DEBUG"
else:win32:CONFIG(release, debug|release|profile): QMAKE_CXXFLAGS += /GS /GL /analyze- /Gm- /W3 /Gy /Ox /D"NDEBUG" /sdl /Gd /Oy- /Oi
else:win32:CONFIG(profile, debug|release|profile): QMAKE_CXXFLAGS += /GS /GL /analyze- /Gm- /W3 /Gy /Ox /D"NDEBUG" /sdl /Gd /Oy- /Oi
win32:CONFIG(debug, debug|release|profile): QMAKE_LFLAGS +=
else:win32:CONFIG(release, debug|release|profile): QMAKE_LFLAGS += /SAFESEH /LTCG
else:win32:CONFIG(profile, debug|release|profile): QMAKE_LFLAGS += /SAFESEH /LTCG


INCLUDEPATH += .

SOURCES += \
    Rh/RhTimerState.cpp \
    Rh/RhConditionState.cpp \
    Rh/RhState.cpp \
    Rh/QRhapsodyInitializer.cpp

HEADERS += \
    oxf/event.h \
    oxf/omreactive.h \
    oxf/omthread.h \
    oxf/oxf.h \
    oxf/state.h \
    Rh/RhState.h \
    Rh/RhTimerState.h \
    Rh/RhConditionState.h \
    Rh/RhTransitions.hpp \
    qtfy.hpp \
    Rh/QRhapsodyInitializer.h
