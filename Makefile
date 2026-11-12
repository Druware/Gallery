## Haiku Gallery - makefile-engine build file.

NAME = HaikuGallery
TYPE = APP
APP_MIME_SIG = application/x-vnd.Druware-HaikuGallery

SRCS = \
	src/App.cpp \
	src/MainWindow.cpp \
	src/NavigationList.cpp \
	src/PageRegistry.cpp \
	src/pages/AlertPage.cpp \
	src/pages/BoxPage.cpp \
	src/pages/ButtonPage.cpp \
	src/pages/CardLayoutPage.cpp \
	src/pages/CheckBoxPage.cpp \
	src/pages/ColorControlPage.cpp \
	src/pages/FilePanelPage.cpp \
	src/pages/GalleryPage.cpp \
	src/pages/GridLayoutPage.cpp \
	src/pages/GroupLayoutPage.cpp \
	src/pages/HomePage.cpp \
	src/pages/ListViewPage.cpp \
	src/pages/MenuBarPage.cpp \
	src/pages/MenuFieldPage.cpp \
	src/pages/OptionPopUpPage.cpp \
	src/pages/OutlineListViewPage.cpp \
	src/pages/PopUpMenuPage.cpp \
	src/pages/RadioButtonPage.cpp \
	src/pages/ScrollViewPage.cpp \
	src/pages/SeparatorViewPage.cpp \
	src/pages/SliderPage.cpp \
	src/pages/SplitViewPage.cpp \
	src/pages/StatusBarPage.cpp \
	src/pages/StringViewPage.cpp \
	src/pages/TabViewPage.cpp \
	src/pages/TextControlPage.cpp \
	src/pages/TextViewPage.cpp \
	src/pages/ToolTipPage.cpp

RDEFS = HaikuGallery.rdef
RSRCS =

LIBS = be tracker $(STDCPPLIBS)
LIBPATHS =
SYSTEM_INCLUDE_PATHS =
LOCAL_INCLUDE_PATHS = src src/pages

OPTIMIZE := FULL
LOCALES =
DEFINES =
WARNINGS = ALL
SYMBOLS :=
DEBUGGER :=
COMPILER_FLAGS = -std=c++17
LINKER_FLAGS =
APP_VERSION :=
DRIVER_PATH =

## Include the makefile-engine
DEVEL_DIRECTORY := \
	$(shell findpaths -r "makefile_engine" B_FIND_PATH_DEVELOP_DIRECTORY)
include $(DEVEL_DIRECTORY)/etc/makefile-engine
