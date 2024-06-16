# Install script for directory: /Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3

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
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/libSDL2main.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2main.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2main.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2main.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/libSDL2.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/libSDL2_test.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2_test.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2_test.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2_test.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2mainTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2mainTargets.cmake"
         "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2mainTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2mainTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2mainTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2mainTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2mainTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2staticTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2staticTargets.cmake"
         "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2staticTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2staticTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2staticTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2staticTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2staticTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2testTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2testTargets.cmake"
         "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2testTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2testTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2testTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2testTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2testTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/SDL2Config.cmake"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/SDL2ConfigVersion.cmake"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/cmake/sdlfind.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_assert.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_atomic.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_audio.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_bits.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_blendmode.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_clipboard.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_copying.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_cpuinfo.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_egl.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_endian.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_error.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_events.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_filesystem.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_gamecontroller.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_gesture.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_guid.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_haptic.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_hidapi.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_hints.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_joystick.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_keyboard.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_keycode.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_loadso.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_locale.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_log.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_main.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_messagebox.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_metal.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_misc.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_mouse.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_mutex.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_name.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_opengl.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_opengl_glext.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_opengles.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_opengles2.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_opengles2_gl2.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_opengles2_gl2ext.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_opengles2_gl2platform.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_opengles2_khrplatform.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_pixels.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_platform.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_power.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_quit.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_rect.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_render.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_rwops.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_scancode.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_sensor.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_shape.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_stdinc.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_surface.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_system.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_syswm.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test_assert.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test_common.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test_compare.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test_crc32.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test_font.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test_fuzzer.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test_harness.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test_images.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test_log.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test_md5.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test_memory.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_test_random.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_thread.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_timer.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_touch.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_types.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_version.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_video.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/SDL_vulkan.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/begin_code.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/include/close_code.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/include/SDL2/SDL_revision.h"
    "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/include-config-release/SDL2/SDL_config.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/SDL2" TYPE FILE FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/LICENSE.txt")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/sdl2.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/sdl2-config")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/aclocal" TYPE FILE FILES "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/sdl2.m4")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/eyalrothschild/Google Drive/My Drive/University/Projects/Chip8/SDL2-2.30.3/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
