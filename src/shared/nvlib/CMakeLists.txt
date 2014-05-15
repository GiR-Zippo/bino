file(GLOB sources_localdir *.c *.h)


set(nvstusb_STAT_SRCS
  ${nvstusb_STAT_SRCS}
  ${sources_localdir}
)

source_group(localdir FILES ${sources_localdir})

include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${LIBUSB_1_INCLUDE_DIRS}
)

add_library(nvstusb STATIC ${nvstusb_STAT_SRCS})