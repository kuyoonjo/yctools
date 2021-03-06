# add the modules subdirectories
set(INCROOT include)
set(SRCROOT src)

# source files
set(DSF_SRC
    ${SRCROOT}/DSF/DualStateFramework.cpp
    ${SRCROOT}/DSF/Lock.cpp
    ${SRCROOT}/DSF/SynchronizedObject.cpp
    ${SRCROOT}/DSF/SynchronizedVar.cpp
    ${SRCROOT}/DSF/Task.cpp
    ${SRCROOT}/DSF/TaskBox.cpp
)
source_group("" FILES ${DSF_SRC})

set(YCTOOL_SRC
    ${SRCROOT}/YC/Any.cpp
    ${SRCROOT}/YC/AnyException.cpp
)
source_group("" FILES ${YCTOOL_SRC})

# headers

set(DSF_INC
    ${INCROOT}/DSF/Config.h
    ${INCROOT}/DSF/Debug.h
    ${INCROOT}/DSF/Declaration.h
    ${INCROOT}/DSF/DualStateFramework.h
    ${INCROOT}/DSF/Export.h
    ${INCROOT}/DSF/Lock.h
    ${INCROOT}/DSF/Runnable.h
    ${INCROOT}/DSF/SynchronizedObject.h
    ${INCROOT}/DSF/SynchronizedVar.h
    ${INCROOT}/DSF/Task.h
    ${INCROOT}/DSF/TaskArgument.h
    ${INCROOT}/DSF/TaskBox.h
    ${INCROOT}/DSF/TaskFunction.h
)
source_group("" FILES ${DSF_INC})

set(YCTOOL_INC
    ${INCROOT}/YC/Any.h
    ${INCROOT}/YC/AnyException.h
)
source_group("" FILES ${YCTOOL_INC})

# add the header path
include_directories(${INCROOT})

# output
set (OUTPUT_DSF ${PROJECT_NAME})
include_directories(${INC})
add_library (${OUTPUT_DSF} SHARED ${DSF_INC} ${YCTOOL_INC} ${DSF_SRC} ${YCTOOL})
set_target_properties(
    ${OUTPUT_DSF} PROPERTIES DEBUG_POSTFIX -d
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
)
if(OSX_FRAMEWORK)
    set_target_properties(
        ${OUTPUT_DSF} PROPERTIES
        FRAMEWORK TRUE
        FRAMEWORK_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        MACOSX_FRAMEWORK_IDENTIFIER ie.itcarlow.yuchen.dsf
        MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        MACOSX_FRAMEWORK_BUNDLE_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        PUBLIC_HEADER "${INC}"
    )
endif()
target_link_libraries (${OUTPUT_DSF} ${LINK_LIBRARY})
