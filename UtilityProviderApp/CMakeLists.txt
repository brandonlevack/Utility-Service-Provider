cmake_minimum_required(VERSION 3.16)
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
set_source_files_properties(${SQLITE_SOURCE} PROPERTIES LANGUAGE C)

# Database file configuration
set(DATABASE_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/../newfile.db")
set(DATABASE_DEST "utility.db")  # Rename if desired

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
    ../src/Bill.cpp ../src/Bill.h 
    ../src/Customer.cpp ../src/Customer.h 
    ../src/DataLoader.cpp ../src/DataLoader.h
    ../src/populateCustomer.cpp ../src/populateCustomer.h 
    ../src/populateProvider.cpp ../src/populateProvider.h 
    ../src/populateService.cpp ../src/populateService.h 
    ../src/Provider.cpp ../src/Provider.h 
    ../src/Service.cpp ../src/Service.h
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
        add_library(UtilityProviderApp SHARED ${PROJECT_SOURCES})
    else()
        add_executable(UtilityProviderApp ${PROJECT_SOURCES})
    endif()
endif()

# Copy database file to build directory
add_custom_command(TARGET UtilityProviderApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${DATABASE_SOURCE}"
        "$<TARGET_FILE_DIR:UtilityProviderApp>/${DATABASE_DEST}"
    COMMENT "Copying database file to build directory"
)

target_compile_definitions(UtilityProviderApp PRIVATE
    SQLITE_THREADSAFE=1
    SQLITE_ENABLE_COLUMN_METADATA
    DATABASE_FILENAME="${DATABASE_DEST}"  # Pass filename as define
)

target_link_libraries(UtilityProviderApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(UtilityProviderApp PRIVATE 
    ${SQLITE_AMALGAMATION_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

# Installation settings
install(TARGETS UtilityProviderApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ${DATABASE_SOURCE}
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    RENAME ${DATABASE_DEST}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(UtilityProviderApp)
endif()