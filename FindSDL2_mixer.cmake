# Locate SDL_image library
# This module defines
# SDL2_MIXER_LIBRARY, the name of the library to link against
# SDL2_MIXER_FOUND, if false, do not try to link to SDL
# SDL2_MIXER_INCLUDE_DIR, where to find SDL/SDL.h
#
# $SDLDIR is an environment variable that would
# correspond to the ./configure --prefix=$SDLDIR
# used in building SDL.
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake 
# module, but with modifications to recognize OS X frameworks and 
# additional Unix paths (FreeBSD, etc).

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

FIND_PATH(SDL2_MIXER_INCLUDE_DIR SDL2/SDL_mixer.h
  HINTS
  $ENV{SDL2_MIXERDIR}
  $ENV{SDLDIR}
  PATH_SUFFIXES include
  PATHS
  ../SDL2_mixer/prefix
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/SDL
  /usr/include/SDL
  /usr/local/include/SDL12
  /usr/local/include/SDL11 # FreeBSD ports
  /usr/include/SDL12
  /usr/include/SDL11
  /usr/local/include
  /usr/include
  /sw/include/SDL # Fink
  /sw/include
  /opt/local/include/SDL # DarwinPorts
  /opt/local/include
  /opt/csw/include/SDL # Blastwave
  /opt/csw/include 
  /opt/include/SDL
  /opt/include
)

SET(SDL2_MIXER_INCLUDE_DIR ${SDL2_MIXER_INCLUDE_DIR}/SDL2)


FIND_LIBRARY(SDL2_MIXER_LIBRARY 
  NAMES SDL2_mixer
  HINTS
  $ENV{SDL2_MIXERDIR}
  $ENV{SDLDIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ../SDL2_mixer/prefix
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

SET(SDL2_MIXER_FOUND "NO")
IF(SDL2_MIXER_LIBRARY AND SDL2_MIXER_INCLUDE_DIR)
  SET(SDL2_MIXER_FOUND "YES")
ENDIF(SDL2_MIXER_LIBRARY AND SDL2_MIXER_INCLUDE_DIR)

message("SDL2_MIXER INCLUDE DIR " ${SDL2_MIXER_INCLUDE_DIR})
message("SDL2_MIXER_LIBRARY " ${SDL2_MIXER_LIBRARY})
