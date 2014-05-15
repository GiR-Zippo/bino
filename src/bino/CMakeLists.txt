include(${QT_USE_FILE})
set (MOC_HEADERS_GUI ${CMAKE_CURRENT_SOURCE_DIR}/gui.h )
set (MOC_HEADERS_VIDEO ${CMAKE_CURRENT_SOURCE_DIR}/video_output_qt.h )
qt4_wrap_cpp (MOC_OUT_GUI ${MOC_HEADERS_GUI})
qt4_wrap_cpp (MOC_OUT_VIDEO ${MOC_HEADERS_VIDEO})
# QT4_AUTOMOC( ${CMAKE_CURRENT_SOURCE_DIR}/gui.moc
#              ${CMAKE_CURRENT_SOURCE_DIR}/video_output_qt.moc)

file(GLOB_RECURSE sources_Base base/*.cpp base/*.h)
file(GLOB sources_localdir *.cpp *.h)

set(bino_SRCS
  ${bino_SRCS}
  ${sources_Base}
  ${MOC_OUT_GUI}
  ${MOC_OUT_VIDEO}
  ${sources_localdir}
)

if( WIN32 )
set(bino_SRCS
    ${bino_SRCS}
    ${sources_Debugging}
    bino.rc
)
endif()

include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src/shared/nvlib
  ${CMAKE_CURRENT_SOURCE_DIR}/
  ${CMAKE_CURRENT_SOURCE_DIR}/base
  ${FFMPEG_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIR}
  ${OPENAL_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${QT_QTGUI_INCLUDE_DIR}
  ${QT_QTCORE_INCLUDE_DIR}
  ${QT_QTDESIGNER_INCLUDE_DIR}
  ${QT_QTDESIGNERCOMPONENTS_INCLUDE_DIR}
  ${QT_QTOPENGL_INCLUDE_DIR}
)

set(bino_LINK_FLAGS "")

add_executable(bino ${bino_SRCS})

if( NOT WIN32 )
  add_definitions(-DLOCALEDIR='"${CONF_DIR}/Contents/Resources/locale"')
  add_definitions(-DHTMLDIR='"${CONF_DIR}/Contents/Resources/Bino Help"')
endif()

add_dependencies(bino revision.h)

if( UNIX )
  if ( USE_GOLD )
    set(bino_LINK_FLAGS "-B'/usr/local/bin' -pthread -lncurses -ldl ${bino_LINK_FLAGS}")
  else()
    set(bino_LINK_FLAGS "-pthread -lncurses ${bino_LINK_FLAGS}")
  endif()
endif()

if( CMAKE_SYSTEM_NAME MATCHES "Darwin" )
  set(bino_LINK_FLAGS "-framework Carbon ${bino_LINK_FLAGS}")
endif()

set_target_properties(bino PROPERTIES LINK_FLAGS "${bino_LINK_FLAGS}")

target_link_libraries(bino
    nvstusb
    ${FFMPEG_LIBRARIES}
    ${FFMPEG_LIBAVFORMAT}
    ${FFMPEG_LIBAVUTIL}
    ${FFMPEG_LIBAVFORMAT}
    ${OPENGL_LIBRARY}
    ${OPENAL_LIBRARY}
    ${GLUT_glut_LIBRARY}
    ${QT_LIBRARY_DIR}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTDESIGNER_LIBRARY}
    ${QT_QTDESIGNERCOMPONENTS_LIBRARY}
    ${QT_QTOPENGL_LIBRARY}
    /usr/lib/x86_64-linux-gnu/libGLEWmx.so
    /usr/lib/x86_64-linux-gnu/libass.so
    /usr/lib/x86_64-linux-gnu/libXxf86vm.so
    ${LIBUSB_1_LIBRARY}
)

if( UNIX )
  install(TARGETS bino DESTINATION bin)
elseif( WIN32 )
  install(TARGETS bino DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()
