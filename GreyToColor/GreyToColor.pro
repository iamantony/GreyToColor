#-------------------------------------------------
#
# Project created by QtCreator 2013-01-09T15:25:32
#
#-------------------------------------------------

QT += core gui sql

CONFIG += warn_on
QMAKE_CXXFLAGS_WARN_ON += -Werror -Wformat=2 -Wuninitialized -Winit-self -Wmissing-include-dirs -Wswitch-enum \
	-Wundef -Wpointer-arith -Wdisabled-optimization -Wcast-align -Wcast-qual

TARGET = GreyToColor
TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp \
	UI/statusbar.cpp \
	UI/scalelabel.cpp \
	IMAGES/image.cpp \
	imghandler.cpp \
	IMAGES/COLOR_SPACE/rgblab.cpp \
    IMAGES/PIXELS/PIXEL/rgb.cpp \
    IMAGES/PIXELS/PIXEL/pixel.cpp \
    IMAGES/PIXELS/PIXEL/lab.cpp \
    IMAGES/PIXELS/colorpixel.cpp \
    IMAGES/PIXELS/preferedcolor.cpp \
    IMAGES/PIXELS/targetpixel.cpp \
    IMAGES/PIXELS/imagepixels.cpp

HEADERS  += \
	mainwindow.h \
	DEFINES/programstatus.h \
	DEFINES/mainwindowui.h \
	UI/statusbar.h \
	UI/scalelabel.h \
	IMAGES/image.h \
	imghandler.h \
	IMAGES/COLOR_SPACE/rgblab.h \
	DEFINES/global.h \
    IMAGES/PIXELS/PIXEL/rgb.h \
    IMAGES/PIXELS/PIXEL/pixel.h \
    IMAGES/PIXELS/PIXEL/lab.h \
    IMAGES/PIXELS/colorpixel.h \
    IMAGES/PIXELS/preferedcolor.h \
    IMAGES/PIXELS/targetpixel.h \
    IMAGES/PIXELS/imagepixels.h

FORMS    += \
	mainwindow.ui

RESOURCES += \
	resources_ui.qrc
