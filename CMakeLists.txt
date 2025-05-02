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
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Network)
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

    # testimonial system
    src/frontend/TestimonialDialog.cpp
    src/frontend/TestimonialDialog.h
    src/frontend/TestimonialsDisplayDialog.cpp
    src/frontend/TestimonialsDisplayDialog.h
    src/backend/Testimonial.cpp
    src/backend/Testimonial.h
    src/backend/TestimonialManager.cpp
    src/backend/TestimonialManager.h

    # Backend components used by Frontend
    src/backend/ApiClient.cpp
    src/backend/Parser.cpp
    src/backend/AppDriver.cpp
    src/backend/RenderAreaManager.cpp
    src/backend/ShapesManager.cpp
    src/backend/UserManager.cpp
    src/backend/UserAccount.cpp

    # Objects / shapes are now in src/objects/
    src/objects/all_shapes.h
    src/objects/circle.cpp
    src/objects/circle.h
    src/objects/ellipse.cpp
    src/objects/ellipse.h
    src/objects/line.cpp
    src/objects/line.h
    src/objects/polygon.cpp
    src/objects/polygon.h
    src/objects/polyline.cpp
    src/objects/polyline.h
    src/objects/rectangle.cpp
    src/objects/rectangle.h
    src/objects/shape.cpp
    src/objects/shape.h
    src/objects/square.cpp
    src/objects/square.h
    src/objects/text.cpp
    src/objects/text.h
    src/objects/vector.h

    src/frontend/loginwindow.cpp
    src/frontend/loginwindow.h
    src/frontend/resources.qrc
)

# Frontend executable
if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(Frontend
        MANUAL_FINALIZATION
        ${PROJECT_srcS}
        src/frontend/ColumnEditDelegate.h
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

# Link Core, Widgets, and Network for Frontend
target_link_libraries(Frontend PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

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
    BUNDLE     DESTINATION .
    LIBRARY    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME    DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ===============================
# Webservice Configuration
# ===============================

# Webservice (Crow) source files
set(WEB_SERVICE_SOURCES
    src/webservice/webservice.cpp
)

find_package(Threads REQUIRED)

# Webservice executable
add_executable(Webservice ${WEB_SERVICE_SOURCES})
target_include_directories(Webservice PRIVATE
    src/webservice/crow/include
    src/webservice/asio/asio/include
)
target_compile_definitions(Webservice PRIVATE -DCROW_USE_STANDALONE_ASIO)
target_compile_options(Webservice PRIVATE -Wall -g)
target_link_libraries(Webservice PRIVATE
    Threads::Threads
    $<$<PLATFORM_ID:Windows>:Ws2_32>
    $<$<PLATFORM_ID:Windows>:Mswsock>
)
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
    qt_finalize_executable(Webservice)
endif()
