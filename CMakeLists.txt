cmake_minimum_required(VERSION 3.5)

project(Space VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find and include packages from Vcpkg
find_package(Boost 1.82.0 REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)  # Added 'Sql' component
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)  # Added 'Sql' component

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(SOURCES
    main.cpp
    src/client/client.cpp
    src/client/runClient.cpp
    ui/RegWindow/MainWindow.cpp
    ui/LoginWindow/Login.cpp
    ui/ApplicationWindow/Application.cpp
)

set(HEADERS
    include/client/Client.h
    include/client/run_Client.h
    ui/RegWindow/MainWindow.h
    ui/LoginWindow/Login.h
    ui/ApplicationWindow/Application.h
)

set(UI_FILES
    ui/RegWindow/MainWindow.ui
    ui/LoginWindow/Login.ui
    ui/ApplicationWindow/Application.ui
)

add_executable(Space ${SOURCES} ${HEADERS} ${UI_FILES})

target_include_directories(Space PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/RegWindow
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/LoginWindow
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/ApplicationWindow
)

target_link_libraries(Space PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    ${Boost_LIBRARIES}
    ws2_32
    wsock32
)

set_target_properties(Space PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Space
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Space)
endif()
