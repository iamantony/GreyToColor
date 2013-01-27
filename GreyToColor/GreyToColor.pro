#-------------------------------------------------
#
# Project created by QtCreator 2013-01-09T15:25:32
#
#-------------------------------------------------

QT += core gui sql

CONFIG += warn_on
QMAKE_CXXFLAGS_WARN_ON += -Wall -Wextra -Werror

TARGET = GreyToColor
TEMPLATE = app


SOURCES += main.cpp\
	idbhandler.cpp \
	imghandler.cpp \
	COLOR_SPACE/rgblab.cpp \
	DATABASE/imgdatabase.cpp \
	IMG_ENTITY/pixelentity.cpp \
	IMG_ENTITY/imgentity.cpp \
	METHODS/imgpassport.cpp \
	METHODS/imgcolorwalshsimple.cpp \
	METHODS/imgcolorwalshneighbor.cpp \
	SERVICE/imgtransform.cpp \
	SERVICE/imgsearchparams.cpp \
	SERVICE/fileoperations.cpp \
	SERVICE/comparestuff.cpp \
    mainwindow_old.cpp \
    mainwindow.cpp \
    statusbar.cpp

HEADERS  += \
	defines.h \
	idbhandler.h \
	imghandler.h \
	COLOR_SPACE/rgblab.h \
	DATABASE/imgdatabase.h \
	IMG_ENTITY/pixelentity.h \
	IMG_ENTITY/imgentity.h \
	METHODS/imgpassport.h \
	METHODS/imgcolorwalshsimple.h \
	METHODS/imgcolorwalshneighbor.h \
	SERVICE/imgtransform.h \
	SERVICE/imgsearchparams.h \
	SERVICE/fileoperations.h \
	SERVICE/comparestuff.h \
    mainwindow_old.h \
    mainwindow.h \
    statusbar.h \
    DEFINES/programstatus.h \
    DEFINES/mainwindowui.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    uiresources.qrc
