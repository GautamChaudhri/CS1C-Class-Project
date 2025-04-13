# ===============================
# Project and Build Configuration
# ===============================
cmake_minimum_required(VERSION 3.16)

project(2D-Graphics-Engine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===============================
# Qt Package Finding
# ===============================
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Network)

# ===============================
# Frontend Configuration
# ===============================

# Frontend source files
set(PROJECT_srcS
    src/frontend/main.cpp
    src/frontend/mainwindow.cpp
    src/frontend/mainwindow.h
    src/frontend/mainwindow.ui
    src/frontend/renderarea.cpp
    src/frontend/renderarea.h

    # Objects / shapes
    src/objects/shapes/all_shapes.h
    src/objects/shapes/circle.cpp
    src/objects/shapes/circle.h
    src/objects/shapes/ellipse.cpp
    src/objects/shapes/ellipse.h
    src/objects/shapes/line.cpp
    src/objects/shapes/line.h
    src/objects/shapes/polygon.cpp
    src/objects/shapes/polygon.h
    src/objects/shapes/polyline.cpp
    src/objects/shapes/polyline.h
    src/objects/shapes/rectangle.cpp
    src/objects/shapes/rectangle.h
    src/objects/shapes/shape.cpp
    src/objects/shapes/shape.h
    src/objects/shapes/square.cpp
    src/objects/shapes/square.h
    src/objects/shapes/text.cpp
    src/objects/shapes/text.h
    src/objects/vector.h
)

# Frontend executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Frontend
        MANUAL_FINALIZATION
        ${PROJECT_srcS}
    )
else()
    if(ANDROID)
        add_library(Frontend SHARED
            ${PROJECT_srcS}
        )
    else()
        add_executable(Frontend
            ${PROJECT_srcS}
        )
    endif()
endif()

target_link_libraries(Frontend PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Frontend bundle and install configuration
set_target_properties(Frontend PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING
        ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

include(GNUInstallDirs)
install(TARGETS Frontend
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ===============================
# Backend Configuration
# ===============================

# Backend source files
set(BACKEND_SOURCES
    src/backend/main.cpp
    src/backend/ApiClient.cpp
    src/backend/ApiClient.h
    src/objects/Converter.h

    # Objects / shapes
    src/objects/shapes/all_shapes.h
    src/objects/shapes/circle.cpp
    src/objects/shapes/circle.h
    src/objects/shapes/ellipse.cpp
    src/objects/shapes/ellipse.h
    src/objects/shapes/line.cpp
    src/objects/shapes/line.h
    src/objects/shapes/polygon.cpp
    src/objects/shapes/polygon.h
    src/objects/shapes/polyline.cpp
    src/objects/shapes/polyline.h
    src/objects/shapes/rectangle.cpp
    src/objects/shapes/rectangle.h
    src/objects/shapes/shape.cpp
    src/objects/shapes/shape.h
    src/objects/shapes/square.cpp
    src/objects/shapes/square.h
    src/objects/shapes/text.cpp
    src/objects/shapes/text.h
    src/objects/vector.h
)

# Backend executable
add_executable(Backend ${BACKEND_SOURCES})
target_link_libraries(Backend PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Backend PROPERTIES
    WIN32_EXECUTABLE FALSE
    MACOSX_BUNDLE FALSE
)

install(TARGETS Backend
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ===============================
# Webservice Configuration
# ===============================

# Webservice (Crow) source files
set(WEB_SERVICE_SOURCES
    src/webservice/webservice.cpp
)

# Webservice executable
add_executable(Webservice ${WEB_SERVICE_SOURCES})
target_include_directories(Webservice PRIVATE
    src/webservice/crow/include
    src/webservice/asio/asio/include
)
target_compile_definitions(Webservice PRIVATE -DCROW_USE_STANDALONE_ASIO)
target_compile_options(Webservice PRIVATE -Wall -pthread -g)
target_link_libraries(Webservice PRIVATE pthread)

set_target_properties(Webservice PROPERTIES
    WIN32_EXECUTABLE FALSE
    MACOSX_BUNDLE FALSE
)

install(TARGETS Webservice
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Database Visibility in Qt Creator
file(GLOB DATABASE CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/database/*)
add_custom_target(Database ALL SOURCES ${DATABASE})

# Finalize Qt Executables (Qt 6 only)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Frontend)
    qt_finalize_executable(Backend)
endif()