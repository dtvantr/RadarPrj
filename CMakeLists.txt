cmake_minimum_required(VERSION 3.16)

project(RadarApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS
    Quick
    Network
    Concurrent
    Location
    Positioning)

qt_standard_project_setup(REQUIRES 6.4)

qt_add_executable(appRadarApp
    main.cpp
)

qt_add_qml_module(appRadarApp
    URI RadarApp
    QML_FILES
            Main.qml


        SOURCES
            target.h
            target.cpp

            radarmodel.h
            radarmodel.cpp

            radarlogic.h
            radarlogic.cpp

            networkmanager.h
            networkmanager.cpp
            RESOURCES
            SOURCES processmanager.h processmanager.cpp
            QML_FILES GeneratorWindow.qml MapView.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appRadarApp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appRadarApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appRadarApp
    PRIVATE Qt6::Quick
    Qt6::Network
    Qt6::Concurrent
    Qt6::Location
    Qt6::Positioning
)

install(TARGETS appRadarApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
