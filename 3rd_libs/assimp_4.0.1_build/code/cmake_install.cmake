# Install script for directory: /Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/Shared/data/_miao_up/3rd_libs/assimp_4.0.1_build/code/libassimp.4.0.1.dylib"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp_4.0.1_build/code/libassimp.4.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.4.0.1.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.4.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "/usr/local/lib/libassimp.4.dylib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/Shared/data/_miao_up/3rd_libs/assimp_4.0.1_build/code/libassimp.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "/usr/local/lib/libassimp.4.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/anim.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/ai_assert.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/camera.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/color4.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/color4.inl"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp_4.0.1_build/code/../include/assimp/config.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/defs.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/cfileio.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/light.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/material.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/material.inl"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/matrix3x3.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/matrix3x3.inl"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/matrix4x4.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/matrix4x4.inl"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/mesh.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/postprocess.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/quaternion.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/quaternion.inl"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/scene.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/metadata.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/texture.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/types.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/vector2.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/vector2.inl"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/vector3.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/vector3.inl"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/version.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/cimport.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/importerdesc.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/Importer.hpp"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/DefaultLogger.hpp"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/ProgressHandler.hpp"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/IOStream.hpp"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/IOSystem.hpp"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/Logger.hpp"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/LogStream.hpp"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/NullLogger.hpp"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/cexport.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/Exporter.hpp"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/DefaultIOStream.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/DefaultIOSystem.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/SceneCombiner.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/Compiler/poppack1.h"
    "/Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

