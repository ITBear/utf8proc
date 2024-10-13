# ----------- Config -----------
TEMPLATE        = lib
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=8325f263-d17a-4416-9522-9431fd85d202
PACKET_NAME     = utf8proc
DEFINES        += UTF8PROC_LIBRARY
_VER_MAJ        = 1
_VER_MIN        = 2
_VER_PAT        = 0
DIR_LEVEL       = ./..

include($$DIR_LEVEL/../QtGlobalPro.pri)

equals(var_link, "static") {
	CONFIG += staticlib
}

# ----------- Libraries -----------
equals(var_os, "windows") {
	LIBS += -lGpUtils$$TARGET_POSTFIX
}

equals(var_os, "linux") {
	LIBS += -lGpUtils$$TARGET_POSTFIX
}

# ----------- Sources and headers -----------
SOURCES += \
	utf8proc.cpp \
	utf8proc_data.cpp \
	utf8proc_impl.cpp

HEADERS += \
	utf8proc.hpp \
	utf8proc_data.hpp \
	utf8proc_global.hpp \
	utf8proc_impl.hpp
