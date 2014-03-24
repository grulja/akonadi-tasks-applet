project(akonadi-tasks-applet)

cmake_minimum_required(VERSION 2.8.0)

cmake_policy(SET CMP0005 NEW)

set(ATA_VERSION_MAJOR   0)
set(ATA_VERSION_MINOR   1)
set(ATA_VERSION_RELEASE 0)
set(ATA_VERSION_STRING "${ATA_VERSION_MAJOR}.${ATA_VERSION_MINOR}.${ATA_VERSION_RELEASE}")
add_definitions(-DATA_VERSION="\\\"${ATA_VERSION_STRING}\\\"")

set(QT_MIN_VERSION "4.8.0")
find_package(KDE4 4.12.0 REQUIRED)
find_package(KdepimLibs 4.12.0 REQUIRED)

include(KDE4Defaults)
include(MacroLibrary)
include(KDEPlatformProfile)
include(FeatureSummary)

set(CMAKE_AUTOMOC ON)
set(CMAKE_LINK_INTERFACE_LIBRARIES "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}")

include(GenerateExportHeader)
include(CMakeDependentOption)

add_definitions(-DQT_NO_CAST_FROM_ASCII
                -DQT_NO_CAST_TO_ASCII
                -DQT_NO_KEYWORDS
                -DQT_USE_FAST_CONCATENATION
                -DQT_USE_FAST_OPERATOR_PLUS
                -DQT_STRICT_ITERATORS
)

include_directories(${QT_INCLUDES}
                    ${KDE4_INCLUDES}
                    ${KDEPIMLIBS_INCLUDE_DIRS}
)

add_subdirectory(src)
