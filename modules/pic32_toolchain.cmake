set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR mips)

if (MINGW OR CYGWIN OR WIN32)
    set(UTIL_SEARCH_CMD where)
elseif (UNIX OR APPLE)
    set(UTIL_SEARCH_CMD which)
endif ()

set(TOOLCHAIN_PREFIX xc32-)

execute_process(
        COMMAND ${UTIL_SEARCH_CMD} ${TOOLCHAIN_PREFIX}gcc
        OUTPUT_VARIABLE BINUTILS_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (MINGW OR CYGWIN OR WIN32)
    if (BINUTILS_PATH)
        string(REPLACE "\n" ";" BINUTILS_PATH "${BINUTILS_PATH}")
        list(GET BINUTILS_PATH 0 BINUTILS_PATH)
    endif ()
endif ()

if (NOT BINUTILS_PATH)
    message(FATAL_ERROR "ARM GCC toolchain not found")
endif ()

get_filename_component(ARM_TOOLCHAIN_DIR ${BINUTILS_PATH} DIRECTORY)
# Without that flag CMake is not able to pass test compilation check
if (${CMAKE_VERSION} VERSION_EQUAL "3.6.0" OR ${CMAKE_VERSION} VERSION_GREATER "3.6")
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
else ()
    set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nosys.specs")
endif ()

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_AR ${TOOLCHAIN_PREFIX}gcc-ar)
set(CMAKE_RANLIB ${TOOLCHAIN_PREFIX}gcc-ranlib)




#set(latest_folder "")
#
#if (UNIX)
#    # Set the search path to /opt/microchip/xc32
#    set(compiler_folder_path "/opt/microchip/xc32")
#    # Define the regular expression pattern
#    set(pattern "v[0-9].[0-9][0-9]")
#    # Search for matching folders
#    file(GLOB matching_folders "${compiler_folder_path}/${pattern}")
#    set(latest_version "0.00")
#    # Iterate through the matching folders
#    foreach(folder ${matching_folders})
#        # Extract the version number from the folder name
#        string(REGEX MATCH "[0-9].[0-9][0-9]" version "${folder}")
#        # Compare the current version with the latest version found
#        if(version VERSION_GREATER latest_version)
#            set(latest_version ${version})
#            set(latest_folder ${folder})
#        endif()
#    endforeach()
#elseif (WINDOWS)
#    # Define the search paths
#    set(search_paths "C:/Program Files/Microchip/xc32" "C:/Program Files(x86)/Microchip/xc32")
#
#    # Define the regular expression pattern
#    set(pattern "v[0-9].[0-9][0-9]")
#
#    # Initialize variables
#    set(latest_folder "")
#    set(latest_version "0.00")
#
#    # Iterate through the search paths
#    foreach(search_path ${search_paths})
#        # Search for matching folders
#        file(GLOB matching_folders "${search_path}/${pattern}")
#
#        # Iterate through the matching folders
#        foreach(folder ${matching_folders})
#            # Extract the version number from the folder name
#            string(REGEX MATCH "[0-9].[0-9][0-9]" version "${folder}")
#            # Compare the current version with the latest version found
#            if(version VERSION_GREATER latest_version)
#                set(latest_version ${version})
#                set(latest_folder ${folder})
#            endif()
#        endforeach()
#    endforeach()
#endif ()
#
## Print the folder with the largest version number
#message("Latest folder: ${latest_folder}/bin")