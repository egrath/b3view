CONFIG -= qt
DESTDIR = build
OBJECTS_DIR = tmp
SOURCES += main.cpp \
    Engine.cpp \
    EventHandler.cpp \
    UserInterface.cpp \
    Debug.cpp \
    View.cpp \
    Utils.cpp \
    extlib/CGUITTFont.cpp
HEADERS += Engine.h \
    EventHandler.h \
    UserInterface.h \
    Debug.h \
    View.h \
    Utils.h \
    extlib/CGUITTFont.h
CONFIG += warn_off

# Irrlicht
IRRLICHTBASE = /home/er/tmp/irrlicht/trunk
INCLUDEPATH += $$IRRLICHTBASE/include
LIBS += -L$$IRRLICHTBASE/lib/Linux \
    -lIrrlicht \
    -lX11 \
    -lGL \
    -lXxf86vm \
    -lXcursor

# Freetype
INCLUDEPATH += /usr/include/freetype2
LIBS += -lfreetype
