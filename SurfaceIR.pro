######################################################################
# Automatically generated by qmake (3.0) ?? 1? 19 15:56:44 2017
######################################################################

TEMPLATE = app
TARGET = SurfaceIR
INCLUDEPATH += .
QT += core widgets gui network

include(showframe/showframe.pri)
include(network/network.pri)

# Input
HEADERS +=  mainwindow.h \
            basicwidget.h\
            flatpixmapbutton.h
SOURCES +=  main.cpp \
            mainwindow.cpp \
            basicwidget.cpp \
            flatpixmapbutton.cpp

unix:{
message("compile unix")
LIBS += /usr/local/lib/lib*.so*
INCLUDEPATH += /usr/local/include/opencv2 \
                /usr/local/include/opencv \
                /usr/local/include 
}

RESOURCES += uiimages/videoui.qrc

RC_FILE += uiimages/myapp.rc

