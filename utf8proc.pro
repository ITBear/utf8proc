TEMPLATE        = lib
#CONFIG         += staticlib
VER_MAJ		    = 0
VER_MIN		    = 1
VER_PAT		    = 1
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=8325f263-d17a-4416-9522-9431fd85d202
QMAKE_CXXFLAGS += -DGP_TYPE_SYSTEM_STATIC_ADD_TO_MANAGER
DEFINES		   += UTF8PROC_LIBRARY
PACKET_NAME     = utf8proc
DIR_LEVEL       = .

include(../QtGlobalPro.pri)

#------------------------------ LIBS BEGIN ---------------------------------
os_windows{
	GP_CORE_LIB_V = 2
}

os_linux{
}

LIBS += -lGpCore2$$TARGET_POSTFIX$$GP_CORE_LIB_V
#------------------------------ LIBS END ---------------------------------

SOURCES += \
	utf8proc.cpp \
	utf8proc_data.cpp \
	utf8proc_impl.cpp

HEADERS += \
	utf8proc.hpp \
	utf8proc_data.hpp \
	utf8proc_global.hpp \
	utf8proc_impl.hpp
