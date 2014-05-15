/*
 * This file is part of bino, a 3D video player.
 *
 * Copyright (C) 2010-2011
 * Martin Lambers <marlam@marlam.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIB_VERSIONS_H
#define LIB_VERSIONS_H

#include <vector>
#include <string>

/* Get a vector of strings that describe the versions of all libraries used.
 * If 'html' is set, then the strings will contains HTML links to the
 * websites of the libraries.
 *
 * The versions are only retrieved once; subsequent calls will return the same
 * results. This is important to avoid OpenAL/OpenGL context trouble. */
std::vector<std::string> lib_versions(bool html);

// Call this function to get the OpenAL version (if a suitable context is available)
void set_openal_versions();
// Call this function to get the OpenGL version (if a suitable context is available)
void set_opengl_versions();

#endif
