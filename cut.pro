
CONFIG += qt

QT += gui core xml widgets

OBJECTS_DIR = .obj

MOC_DIR = .moc

TARGET = TestDynamicManeuver

SOURCES += src/main.cpp \
    src/widgets/DrawingsBDWidget.cpp \
    src/widgets/GraphicsScene_PopupMenu.cpp \
    src/widgets/ManeuverSettingsWidget.cpp \
    src/widgets/maneuverwidget.cpp \
    src/widgets/ScaleWidget.cpp \
    src/graphics/AirObjGrItem.cpp \
    src/graphics/GraphicsEngine.cpp \
    src/graphics/GraphicsScene.cpp \
    src/graphics/Icons.cpp \
    src/graphics/MapScene.cpp \
    src/graphics/PointGraphicsItem.cpp \
    src/math/FnMath.cpp \
    src/math/Position.cpp \
    src/graphics/maneuver_gritem.cpp \
    src/graphics/AirObjRouteGraphicsItem.cpp

HEADERS += src/widgets/DrawingsBDWidget.hpp \
    src/widgets/GraphicsScene_PopupMenu.h \
    src/widgets/ManeuverSettingsWidget.h \
    src/widgets/maneuverwidget.h \
    src/widgets/ScaleWidget.hpp \
    src/graphics/AirObjGrItem.hpp \
    src/graphics/GraphicsEngine.hpp \
    src/graphics/GraphicsScene.hpp \
    src/graphics/Icons.hpp \
    src/graphics/MapScene.hpp \
    src/graphics/PointGraphicsItem.hpp \
    src/math/FnMath.hpp \
    src/math/Position.hpp \
    src/graphics/maneuver_gritem.h \
    src/graphics/AirObjRouteGraphicsItem.hpp

UI_DIR += src/forms_ui

UI_HEADERS_DIR += src/forms_ui/headers

FORMS += src/forms_ui/drawingsbd_widget.ui \
         src/forms_ui/ManeuverSettingsWidget.ui \
         src/forms_ui/maneuverwidget.ui

RESOURCES += src/resources/resource.qrc
