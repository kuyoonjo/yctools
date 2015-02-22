cmake_minimum_required(VERSION 2.8)

# project name
project(yctools)

# setup version numbers
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)


# disable the rpath stuff
set(CMAKE_SKIP_BUILD_RPATH FALSE)


# detect the architecture (note: this test won't work for cross-compilation)
    
include(CheckTypeSize)
check_type_size(void* SIZEOF_VOID_PTR)
if("${SIZEOF_VOID_PTR}" STREQUAL "4")
	set(ARCH x86)
elseif("${SIZEOF_VOID_PTR}" STREQUAL "8")
	set(ARCH x64)
else()
	message(FATAL_ERROR "Unsupported architecture")
	return()
endif()

# configure links and headers

if (MSVC)
	# Windows VC
	# Activate C++ exception handling
	if (NOT CMAKE_CXX_FLAGS MATCHES "/EHsc")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
	endif ()

	# Set Warning level always to 4
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else ()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif () 
elseif(APPLE)
	# Mac OS X Xcode
    set(CMAKE_MACOSX_RPATH 1)
	ADD_DEFINITIONS(
    		-std=c++11
	)
else()
	# Unix
	ADD_DEFINITIONS(
    		-std=c++11
	)
endif()

if(APPLE)
    OPTION(OSX_FRAMEWORK "Build a Mac OS X Framework")
endif()

set(INCROOT include)
set(SRCROOT src)

# source files
set(YCTOOL_SRC
    ${SRCROOT}/yctools/Any.cpp
    ${SRCROOT}/yctools/AnyException.cpp
    ${SRCROOT}/yctools/Random.cpp
)
source_group("" FILES ${YCTOOL_SRC})

# headers
set(YCTOOL_INC
    ${INCROOT}/yctools/Any.h
    ${INCROOT}/yctools/AnyException.h
    ${INCROOT}/yctools/Config.h
    ${INCROOT}/yctools/Export.h
    ${INCROOT}/yctools/Random.h
)
source_group("" FILES ${YCTOOL_INC})

# add the header path
include_directories(${INCROOT})

# output
set (OUTPUT ${PROJECT_NAME})
add_library (${OUTPUT} SHARED ${YCTOOL_INC} ${YCTOOL_SRC})
set_target_properties(
    ${OUTPUT} PROPERTIES DEBUG_POSTFIX -d
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
)
if(OSX_FRAMEWORK)
    set_target_properties(
        ${OUTPUT} PROPERTIES
        FRAMEWORK TRUE
        FRAMEWORK_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        MACOSX_FRAMEWORK_IDENTIFIER ie.itcarlow.yuchen.yctools
        MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        MACOSX_FRAMEWORK_BUNDLE_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        PUBLIC_HEADER "${YCTOOL_INC}"
    )
endif()

