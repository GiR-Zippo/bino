/* GENERATED AUTOMATICALLY FROM video_output_color.fs.glsl */
#ifndef VIDEO_OUTPUT_COLOR_FS_GLSL_STR
#define VIDEO_OUTPUT_COLOR_FS_GLSL_STR \
"/*\n"\
" * This file is part of bino, a 3D video player.\n"\
" *\n"\
" * Copyright (C) 2010, 2011, 2012\n"\
" * Martin Lambers <marlam@marlam.de>\n"\
" *\n"\
" * This program is free software; you can redistribute it and/or modify\n"\
" * it under the terms of the GNU General Public License as published by\n"\
" * the Free Software Foundation; either version 3 of the License, or\n"\
" * (at your option) any later version.\n"\
" *\n"\
" * This program is distributed in the hope that it will be useful,\n"\
" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"\
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"\
" * GNU General Public License for more details.\n"\
" *\n"\
" * You should have received a copy of the GNU General Public License\n"\
" * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"\
" */\n"\
"\n"\
"#version 110\n"\
"\n"\
"// quality: 0 .. 4\n"\
"#define quality $quality\n"\
"\n"\
"// layout_yuv_p\n"\
"// layout_bgra32\n"\
"#define $layout\n"\
"\n"\
"// color_space_yuv601\n"\
"// color_space_yuv709\n"\
"// color_space_srgb\n"\
"#define $color_space\n"\
"\n"\
"// value_range_8bit_full\n"\
"// value_range_8bit_mpeg\n"\
"// value_range_10bit_full\n"\
"// value_range_10bit_mpeg\n"\
"#define $value_range\n"\
"\n"\
"// the offset between the y texture coordinates and the appropriate\n"\
"// u and v texture coordinates, according to the chroma sample location\n"\
"#define chroma_offset_x $chroma_offset_x\n"\
"#define chroma_offset_y $chroma_offset_y\n"\
"\n"\
"// storage_srgb\n"\
"// storage_linear_rgb\n"\
"#define $storage\n"\
"\n"\
"#if defined(layout_yuv_p)\n"\
"uniform sampler2D y_tex;\n"\
"uniform sampler2D u_tex;\n"\
"uniform sampler2D v_tex;\n"\
"#elif defined(layout_bgra32)\n"\
"uniform sampler2D srgb_tex;\n"\
"#endif\n"\
"\n"\
"/* The YUV triplets used internally in this shader use the following\n"\
" * conventions:\n"\
" * - All three components are in the range [0,1]\n"\
" * - The U and V components refer to the normalized E_Cr and E_Cb\n"\
" *   components in the ITU.BT-* documents, shifted from [-0.5,+0.5]\n"\
" *   to [0,1]\n"\
" * - The color space is either the one defined in ITU.BT-601 or the one\n"\
" *   defined in ITU.BT-709. */\n"\
"#if !defined(layout_bgra32)\n"\
"vec3 yuv_to_srgb(vec3 yuv)\n"\
"{\n"\
"    // Convert the MPEG range to the full range for each component, if necessary\n"\
"# if defined(value_range_8bit_mpeg)\n"\
"    yuv = (yuv - vec3(16.0 / 255.0)) * vec3(256.0 / 220.0, 256.0 / 225.0, 256.0 / 225.0);\n"\
"# elif defined(value_range_10bit_mpeg)\n"\
"    yuv = (yuv - vec3(64.0 / 1023.0)) * vec3(1024.0 / 877.0, 1024.0 / 897.0, 1024.0 / 897.0);\n"\
"# endif\n"\
"\n"\
"# if defined(color_space_yuv709)\n"\
"    // According to ITU.BT-709 (see entries 3.2 and 3.3 in Sec. 3 (\"Signal format\"))\n"\
"    mat3 m = mat3(\n"\
"            1.0,     1.0,      1.0,\n"\
"            0.0,    -0.187324, 1.8556,\n"\
"            1.5748, -0.468124, 0.0);\n"\
"    return m * (yuv - vec3(0.0, 0.5, 0.5));\n"\
"# else\n"\
"    // According to ITU.BT-601 (see formulas in Sec. 2.5.1 and 2.5.2)\n"\
"    mat3 m = mat3(\n"\
"            1.0,    1.0,      1.0,\n"\
"            0.0,   -0.344136, 1.772,\n"\
"            1.402, -0.714136, 0.0);\n"\
"    return m * (yuv - vec3(0.0, 0.5, 0.5));\n"\
"# endif\n"\
"}\n"\
"#endif\n"\
"\n"\
"#if defined(storage_linear_rgb)\n"\
"# if quality >= 4\n"\
"// See GL_ARB_framebuffer_sRGB extension\n"\
"float nonlinear_to_linear(float x)\n"\
"{\n"\
"    return (x <= 0.04045 ? (x / 12.92) : pow((x + 0.055) / 1.055, 2.4));\n"\
"}\n"\
"vec3 srgb_to_rgb(vec3 srgb)\n"\
"{\n"\
"    float r = nonlinear_to_linear(srgb.r);\n"\
"    float g = nonlinear_to_linear(srgb.g);\n"\
"    float b = nonlinear_to_linear(srgb.b);\n"\
"    return vec3(r, g, b);\n"\
"}\n"\
"# elif quality >= 2\n"\
"vec3 srgb_to_rgb(vec3 srgb)\n"\
"{\n"\
"    return pow(srgb, vec3(2.2));\n"\
"}\n"\
"# else\n"\
"vec3 srgb_to_rgb(vec3 srgb)\n"\
"{\n"\
"    return srgb * srgb;\n"\
"}\n"\
"# endif\n"\
"#endif\n"\
"\n"\
"vec3 get_srgb(vec2 tex_coord)\n"\
"{\n"\
"#if defined(layout_bgra32)\n"\
"    return texture2D(srgb_tex, tex_coord).xyz;\n"\
"#elif defined(value_range_8bit_full) || defined(value_range_8bit_mpeg)\n"\
"    return yuv_to_srgb(vec3(\n"\
"                texture2D(y_tex, tex_coord).x,\n"\
"                texture2D(u_tex, tex_coord + vec2(chroma_offset_x, chroma_offset_y)).x,\n"\
"                texture2D(v_tex, tex_coord + vec2(chroma_offset_x, chroma_offset_y)).x));\n"\
"#else\n"\
"    return yuv_to_srgb((65535.0 / 1023.0) * vec3(\n"\
"                texture2D(y_tex, tex_coord).x,\n"\
"                texture2D(u_tex, tex_coord + vec2(chroma_offset_x, chroma_offset_y)).x,\n"\
"                texture2D(v_tex, tex_coord + vec2(chroma_offset_x, chroma_offset_y)).x));\n"\
"#endif\n"\
"}\n"\
"\n"\
"void main()\n"\
"{\n"\
"    vec3 srgb = get_srgb(gl_TexCoord[0].xy);\n"\
"#if defined(storage_srgb)\n"\
"    gl_FragColor = vec4(srgb, 1.0);\n"\
"#else\n"\
"    vec3 rgb = srgb_to_rgb(srgb);\n"\
"    gl_FragColor = vec4(rgb, 1.0);\n"\
"#endif\n"\
"}\n"\
""
#endif
