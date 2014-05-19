DESTDIR  = ../bin
TEMPLATE = lib
TARGET   = qtutils
CONFIG += staticlib c++11

OBJECTS_DIR = ../build/qtutils
MOC_DIR     = ../build/qtutils
UI_DIR      = ../build/qtutils
RCC_DIR     = ../build/qtutils

QT = core gui

#check Qt version
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += QtIncludes

win*{
	QMAKE_CXXFLAGS += /MP
	DEFINES += WIN32_LEAN_AND_MEAN NOMINMAX
	QMAKE_CXXFLAGS_WARN_ON = -W4
}
mac*{

}
linux*{
	QMAKE_CXXFLAGS += --std=c++11
}

include(settings/settings.pri)
include(taskbarprogress/taskbarprogress.pri)
include(utils/utils.pri)
include(settingsui/settingsui.pri)
include(mouseclickdetector/mouseclickdetector.pri)

win32*:!*msvc2012:*msvc*:!*msvc2010:*msvc* {
	QMAKE_CXXFLAGS += /FS
}

SOURCES += \
	utils/naturalsorting/naturalsorting_qt.cpp
