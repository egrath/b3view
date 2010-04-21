CONFIG -= qt
DESTDIR = build
OBJECTS_DIR = tmp
SOURCES += main.cpp \
    Engine.cpp \
    EventHandler.cpp \
    UserInterface.cpp \
    Debug.cpp \
    View.cpp \
    Utils.cpp
HEADERS += Engine.h \
    EventHandler.h \
    UserInterface.h \
    Debug.h \
    View.h \
    Utils.h
CONFIG += warn_off

# Irrlicht
# it's tailored to use svn on linux, and the stable build on windows
unix {
    IRRLICHTBASE = /home/er/tmp/irrlicht/trunk
}
win32 {
    IRRLICHTBASE = d:/libs/irrlicht-1.7.1
}
INCLUDEPATH += $$IRRLICHTBASE/include

unix {
    LIBS += -L$$IRRLICHTBASE/source/Irrlicht \
        -lIrrlicht \
        -lX11 \
        -lGL \
        -lXxf86vm
}

win32 {
    LIBS += -L$$IRRLICHTBASE/lib/Win32-gcc \
         -lIrrlicht
}
