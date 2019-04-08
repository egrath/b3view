CONFIG -= qt
TARGET = b3view
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
#IRRLICHTBASE = /home/er/tmp/irrlicht/trunk
#INCLUDEPATH += $$IRRLICHTBASE/include
#LIBS += -L$$IRRLICHTBASE/lib/Linux \
#    -lIrrlicht \
#    -lX11 \
#    -lGL \
#    -lXxf86vm \
#    -lXcursor

LIBS += -lIrrlicht \
    -lX11 \
    -lGL \
    -lXxf86vm \
    -lXcursor

# <experimental/filesystem>:
LIBS += -lstdc++fs

# Freetype
INCLUDEPATH += /usr/include/freetype2
LIBS += -lfreetype
