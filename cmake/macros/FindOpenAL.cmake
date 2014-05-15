IF(WIN32)
SET(AL_HEADER_PREFIX "")
ELSEIF(APPLE)
SET(AL_HEADER_PREFIX "OpenAL/")
ELSE(WIN32)
SET(AL_HEADER_PREFIX "AL/")
ENDIF(WIN32)
FIND_PATH(OPENAL_INCLUDE_DIR "${AL_HEADER_PREFIX}al.h"
HINTS
$ENV{OPENALDIR}
PATH_SUFFIXES include include/AL
PATHS
~/Library/Frameworks
/Library/Frameworks
/usr/local
/usr
/sw # Fink
/opt/local # DarwinPorts
/opt/csw # Blastwave
/opt
[HKEY_LOCAL_MACHINE\\SOFTWARE\\Creative\ Labs\\OpenAL\ 1.1\ Software\ Development\ Kit\\1.00.0000;InstallDir]
${CMAKE_SOURCE_DIR}/dep/openAL
)
FIND_LIBRARY(OPENAL_LIBRARY
NAMES OpenAL al openal OpenAL32
HINTS
$ENV{OPENALDIR}
PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
PATHS
~/Library/Frameworks
/Library/Frameworks
/usr/local
/usr
/sw
/opt/local
/opt/csw
/opt
[HKEY_LOCAL_MACHINE\\SOFTWARE\\Creative\ Labs\\OpenAL\ 1.1\ Software\ Development\ Kit\\1.00.0000;InstallDir]
${CMAKE_SOURCE_DIR}/dep/openAL
)
# handle the QUIETLY and REQUIRED arguments and set OPENAL_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OpenAL DEFAULT_MSG OPENAL_LIBRARY OPENAL_INCLUDE_DIR)
MARK_AS_ADVANCED(OPENAL_LIBRARY OPENAL_INCLUDE_DIR) 


SET(OPENAL_FOUND "NO")
IF(OPENAL_LIBRARY AND OPENAL_INCLUDE_DIR)
  SET(OPENAL_FOUND "YES")
  message(STATUS "Found OpenAL or Libav: ${OPENAL_LIBRARY}, ${OPENAL_INCLUDE_DIR}")
else()
  message(FATAL_ERROR "Could not find OpenAL")
ENDIF(OPENAL_LIBRARY AND OPENAL_INCLUDE_DIR)