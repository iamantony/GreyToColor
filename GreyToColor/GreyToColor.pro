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
	imghandler.cpp \
	IMAGES/SOURCE/PIXELS/sourceimgpixels.cpp \
	IMAGES/SOURCE/PIXELS/colorpixel.cpp \
	IMAGES/TARGET/PIXELS/targetpixel.cpp \
	IMAGES/TARGET/PIXELS/preferedcolor.cpp \
	IMAGES/COMMON/PIXELS/COLOR_SPACE/rgblab.cpp \
	IMAGES/COMMON/PIXELS/rgb.cpp \
	IMAGES/COMMON/PIXELS/pixel.cpp \
	IMAGES/COMMON/PIXELS/lab.cpp \
	IMAGES/COMMON/PIXELS/imagepixels.cpp \
	IMAGES/COMMON/image.cpp \
	SERVICE/calculatorsko.cpp \
	IMAGES/TARGET/PIXELS/targetimgpixels.cpp \
	IMAGES/CANDIDATE/candidateimage.cpp \
	SERVICE/FILES/filesservice.cpp \
	SERVICE/FILES/imgfilesservice.cpp \
	IMAGES/COMMON/processingimage.cpp \
	IMAGES/SOURCE/sourceimage.cpp \
	IMAGES/TARGET/targetimage.cpp \
	SERVICE/IMAGES/imgtransform.cpp \
	SERVICE/IMAGES/imgsearchparam.cpp \
	PARAMS/IMAGES/imgsimilarityarea.cpp \
	application.cpp \
    SERVICE/FILES/idbfilesservice.cpp

HEADERS  += \
	mainwindow.h \
	DEFINES/programstatus.h \
	DEFINES/mainwindowui.h \
	UI/statusbar.h \
	UI/scalelabel.h \
	imghandler.h \
	DEFINES/global.h \
	DEFINES/pixels.h \
	IMAGES/SOURCE/PIXELS/sourceimgpixels.h \
	IMAGES/SOURCE/PIXELS/colorpixel.h \
	IMAGES/TARGET/PIXELS/targetpixel.h \
	IMAGES/TARGET/PIXELS/preferedcolor.h \
	IMAGES/COMMON/PIXELS/COLOR_SPACE/rgblab.h \
	IMAGES/COMMON/PIXELS/rgb.h \
	IMAGES/COMMON/PIXELS/pixel.h \
	IMAGES/COMMON/PIXELS/lab.h \
	IMAGES/COMMON/PIXELS/imagepixels.h \
	IMAGES/COMMON/image.h \
	SERVICE/calculatorsko.h \
	IMAGES/TARGET/PIXELS/targetimgpixels.h \
	IMAGES/CANDIDATE/candidateimage.h \
	DEFINES/images.h \
	SERVICE/FILES/filesservice.h \
	SERVICE/FILES/imgfilesservice.h \
	DEFINES/idbs.h \
	IMAGES/COMMON/processingimage.h \
	IMAGES/SOURCE/sourceimage.h \
	IMAGES/TARGET/targetimage.h \
	SERVICE/IMAGES/imgtransform.h \
	SERVICE/IMAGES/imgsearchparam.h \
	PARAMS/IMAGES/imgsimilarityarea.h \
	application.h \
    SERVICE/FILES/idbfilesservice.h

FORMS    += \
	mainwindow.ui

RESOURCES += \
	resources_ui.qrc
