project(print-manager)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/)

find_package(KDE4 REQUIRED)
find_package(CUPS "1.4" REQUIRED)
include (MacroLibrary)


# If CUPS 1.6 is installed set this
option(CUPS_1_6 "Build for CUPS 1.6 and above enabled" OFF)
set(HAVE_CUPS_1_6 ${CUPS_1_6})
message(STATUS "Build for CUPS 1.6 and above: " ${CUPS_1_6})

# Print-Manager version
set(PM_VERSION "0.3.0" CACHE STRING "Print Manager version")

# Generate config.h
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include(FindPkgConfig)
include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE_DEFINITIONS})
include_directories(${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${KDE4_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/libkcups
)

add_subdirectory(libkcups)
add_subdirectory(configure-printer)
add_subdirectory(add-printer)
add_subdirectory(printer-manager-kcm)
add_subdirectory(printqueue)
add_subdirectory(print-manager-kded)
add_subdirectory(printjobs-dataengine)
add_subdirectory(printers-dataengine)

install(DIRECTORY plasmoid-package/
        DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/printmanager)

install(FILES plasmoid-package/metadata.desktop
        DESTINATION ${SERVICES_INSTALL_DIR} RENAME plasma-applet-printmanager.desktop)
