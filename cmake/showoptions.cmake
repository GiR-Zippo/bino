# output generic information about the core and buildtype chosen
message("")
message("* Bino commithash : ${rev_hash_str}")
if( UNIX )
  message("* Build binaries in      : ${CMAKE_BUILD_TYPE} mode")
endif()
message("")

# output information about installation-directories and locations

message("* Install Bino to        : ${CMAKE_INSTALL_PREFIX}")
if( UNIX )
  message("* Install libraries to   : ${LIBSDIR}")
  message("* Install configs to     : ${CONF_DIR}")
endif()
message("")

# Show infomation about the options selected during configuration
if( USE_PCH )
  message("* Build with PCH         : Yes (default)")
else()
  message("* Build with PCH         : No")
endif()

if( WITH_WARNINGS )
  message("* Show all warnings      : Yes")
else()
  message("* Show compile-warnings  : No  (default)")
endif()

if ( NOJEM )
  message("")
  message("*** WARNING: jemalloc linking has been disabled!")
  message("*** Please note that this is for DEBUGGING WITH VALGRIND only!")
  message("*** DO NOT DISABLE IT UNLESS YOU KNOW WHAT YOU'RE DOING!")
endif()
message("")
