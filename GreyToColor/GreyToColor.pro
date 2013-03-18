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
	SERVICE/FILES/idbfilesservice.cpp \
	PARAMS/IMAGES/imgpassport.cpp \
    SERVICE/IMAGES/imghistogram.cpp \
    SERVICE/IMAGES/imgpassportcreator.cpp \
    SERVICE/IMAGES/imgsubsampler.cpp \
    idbhandler.cpp \
    DATABASE/imgdatabase.cpp \
    SERVICE/IMAGES/imgpassportcomparer.cpp \
    SERVICE/IMAGES/imgfilter.cpp \
    SERVICE/KERNELS/kernelcreator.cpp \
    colormethodshandler.cpp \
    METHODS/colorizator.cpp \
    METHODS/walshsimplecolorizator.cpp \
    METHODS/walshneighborcolorizator.cpp \
    METHODS/wnnorandcolorizator.cpp \
    METHODS/wnonerandcolorizator.cpp \
    UI/DIALOGS/preferencesdialog.cpp

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
	SERVICE/FILES/idbfilesservice.h \
	PARAMS/IMAGES/imgpassport.h \
    DEFINES/imgservice.h \
    SERVICE/IMAGES/imghistogram.h \
    SERVICE/IMAGES/imgpassportcreator.h \
    SERVICE/IMAGES/imgsubsampler.h \
    idbhandler.h \
    DATABASE/imgdatabase.h \
    SERVICE/IMAGES/imgpassportcomparer.h \
    DEFINES/calcsko.h \
    SERVICE/IMAGES/imgfilter.h \
    SERVICE/KERNELS/kernelcreator.h \
    colormethodshandler.h \
    DEFINES/colorization.h \
    METHODS/colorizator.h \
    METHODS/walshsimplecolorizator.h \
    METHODS/walshneighborcolorizator.h \
    METHODS/wnnorandcolorizator.h \
    METHODS/wnonerandcolorizator.h \
    UI/DIALOGS/preferencesdialog.h

FORMS    += \
	mainwindow.ui \
    UI/DIALOGS/preferencesdialog.ui

RESOURCES += \
	resources_ui.qrc
