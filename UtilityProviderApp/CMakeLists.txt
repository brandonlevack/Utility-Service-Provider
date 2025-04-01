cmake_minimum_required(VERSION 3.16)

# Enable both C and C++ since SQLite is written in C
project(UtilityProviderApp VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SQLite configuration
set(SQLITE_AMALGAMATION_DIR "C:/sqlite")
set(SQLITE_SOURCE "${SQLITE_AMALGAMATION_DIR}/sqlite3.c")
set(SQLITE_HEADER "${SQLITE_AMALGAMATION_DIR}/sqlite3.h")

# Set SQLite as C source file
set_source_files_properties(${SQLITE_SOURCE} PROPERTIES LANGUAGE C)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    TableModifier.cpp
    TableModifier.h
    CustomerPage.cpp
    CustomerPage.h
    ProviderPage.h
    ProviderPage.cpp
    ../src/Bill.cpp 
    ../src/Bill.h 
    ../src/Customer.cpp 
    ../src/Customer.h 
    ../src/Provider.cpp 
    ../src/Provider.h 
    ../src/Service.cpp 
    ../src/Service.h
    ../src/populateCustomer.cpp 
    ../src/populateCustomer.h
    ${SQLITE_SOURCE}
    ${SQLITE_HEADER}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(UtilityProviderApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(UtilityProviderApp SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(UtilityProviderApp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Add SQLite-specific definitions
target_compile_definitions(UtilityProviderApp PRIVATE
    SQLITE_THREADSAFE=1
    SQLITE_ENABLE_COLUMN_METADATA
)

target_link_libraries(UtilityProviderApp PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(UtilityProviderApp PRIVATE 
    ${SQLITE_AMALGAMATION_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

# macOS/iOS bundle settings
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.UtilityProviderApp)
endif()

set_target_properties(UtilityProviderApp PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Installation settings
include(GNUInstallDirs)
install(TARGETS UtilityProviderApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Qt 6 finalization
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(UtilityProviderApp)
endif()