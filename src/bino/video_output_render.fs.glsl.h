/* GENERATED AUTOMATICALLY FROM video_output_render.fs.glsl */
#ifndef VIDEO_OUTPUT_RENDER_FS_GLSL_STR
#define VIDEO_OUTPUT_RENDER_FS_GLSL_STR \
"/*\n"\
" * This file is part of bino, a 3D video player.\n"\
" *\n"\
" * Copyright (C) 2010, 2011, 2012\n"\
" * Martin Lambers <marlam@marlam.de>\n"\
" * Frédéric Devernay <Frederic.Devernay@inrialpes.fr>\n"\
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
"// mode_onechannel\n"\
"// mode_red_cyan_monochrome\n"\
"// mode_red_cyan_half_color\n"\
"// mode_red_cyan_full_color\n"\
"// mode_red_cyan_dubois\n"\
"// mode_green_magenta_monochrome\n"\
"// mode_green_magenta_half_color\n"\
"// mode_green_magenta_full_color\n"\
"// mode_green_magenta_dubois\n"\
"// mode_amber_blue_monochrome\n"\
"// mode_amber_blue_half_color\n"\
"// mode_amber_blue_full_color\n"\
"// mode_amber_blue_dubois\n"\
"// mode_red_green_monochrome\n"\
"// mode_red_blue_monochrome\n"\
"// mode_even_odd_rows\n"\
"// mode_even_odd_columns\n"\
"// mode_checkerboard\n"\
"#define $mode\n"\
"\n"\
"// subtitle_enabled\n"\
"// subtitle_disabled\n"\
"#define $subtitle\n"\
"\n"\
"// coloradjust_enabled\n"\
"// coloradjust_disabled\n"\
"#define $coloradjust\n"\
"\n"\
"// ghostbust_enabled\n"\
"// ghostbust_disabled\n"\
"#define $ghostbust\n"\
"\n"\
"uniform sampler2D rgb_l;\n"\
"uniform sampler2D rgb_r;\n"\
"uniform float parallax;\n"\
"\n"\
"#if defined(subtitle_enabled)\n"\
"uniform sampler2D subtitle;\n"\
"uniform float subtitle_parallax;\n"\
"#endif\n"\
"\n"\
"#if defined(coloradjust_enabled)\n"\
"uniform mat4 color_matrix;\n"\
"#endif\n"\
"\n"\
"#if defined(ghostbust_enabled) && (defined(mode_onechannel) || defined(mode_even_odd_rows) || defined(mode_even_odd_columns) || defined(mode_checkerboard))\n"\
"uniform vec3 crosstalk;\n"\
"#endif\n"\
"\n"\
"#if defined(mode_onechannel)\n"\
"uniform float channel;  // 0.0 for left, 1.0 for right\n"\
"#endif\n"\
"\n"\
"#if defined(mode_even_odd_rows) || defined(mode_even_odd_columns) || defined(mode_checkerboard)\n"\
"uniform sampler2D mask_tex;\n"\
"uniform float step_x;\n"\
"uniform float step_y;\n"\
"#endif\n"\
"\n"\
"\n"\
"#if defined(mode_red_cyan_monochrome) || defined(mode_red_cyan_half_color) || defined(mode_green_magenta_monochrome) || defined(mode_green_magenta_half_color) || defined(mode_amber_blue_monochrome) || defined(mode_amber_blue_half_color) || defined(mode_red_green_monochrome) || defined(mode_red_blue_monochrome)\n"\
"float srgb_to_lum(vec3 srgb)\n"\
"{\n"\
"    // Values taken from http://www.fourcc.org/fccyvrgb.php\n"\
"    return dot(srgb, vec3(0.299, 0.587, 0.114));\n"\
"}\n"\
"#endif\n"\
"\n"\
"#if quality >= 4\n"\
"// Correct variant, see GL_ARB_framebuffer_sRGB extension\n"\
"float linear_to_nonlinear(float x)\n"\
"{\n"\
"    return (x <= 0.0031308 ? (x * 12.92) : (1.055 * pow(x, 1.0 / 2.4) - 0.055));\n"\
"}\n"\
"vec3 rgb_to_srgb(vec3 rgb)\n"\
"{\n"\
"    float sr = linear_to_nonlinear(rgb.r);\n"\
"    float sg = linear_to_nonlinear(rgb.g);\n"\
"    float sb = linear_to_nonlinear(rgb.b);\n"\
"    return vec3(sr, sg, sb);\n"\
"}\n"\
"#elif quality >= 2\n"\
"vec3 rgb_to_srgb(vec3 rgb)\n"\
"{\n"\
"    // Faster variant\n"\
"    return pow(rgb, vec3(1.0 / 2.2));\n"\
"}\n"\
"#elif quality >= 1\n"\
"vec3 rgb_to_srgb(vec3 rgb)\n"\
"{\n"\
"    // Even faster variant, assuming gamma = 2.0\n"\
"    return sqrt(rgb);\n"\
"}\n"\
"#else // quality == 0: SRGB stored in GL_RGB8\n"\
"# define rgb_to_srgb(rgb) rgb\n"\
"#endif\n"\
"\n"\
"#if defined(mode_onechannel) || defined(mode_even_odd_rows) || defined(mode_even_odd_columns) || defined(mode_checkerboard)\n"\
"#  if defined(ghostbust_enabled)\n"\
"vec3 ghostbust(vec3 original, vec3 other)\n"\
"{\n"\
"    return original + crosstalk - (other + original) * crosstalk;\n"\
"}\n"\
"#  else\n"\
"#    define ghostbust(original, other) original\n"\
"#  endif\n"\
"#endif\n"\
"\n"\
"#if defined(coloradjust_enabled)\n"\
"vec3 adjust_color(vec3 rgb)\n"\
"{\n"\
"    vec4 rgbw = color_matrix * vec4(rgb, 1.0);\n"\
"    float w = max(rgbw.w, 0.0001);\n"\
"    return clamp(rgbw.rgb / w, 0.0, 1.0);\n"\
"}\n"\
"#else\n"\
"#  define adjust_color(rgb) rgb\n"\
"#endif\n"\
"\n"\
"vec3 tex_l(vec2 texcoord)\n"\
"{\n"\
"    return adjust_color(texture2D(rgb_l, texcoord + vec2(parallax, 0.0)).rgb);\n"\
"}\n"\
"vec3 tex_r(vec2 texcoord)\n"\
"{\n"\
"    return adjust_color(texture2D(rgb_r, texcoord - vec2(parallax, 0.0)).rgb);\n"\
"}\n"\
"\n"\
"#if defined(subtitle_enabled)\n"\
"vec4 sub_l(vec2 texcoord)\n"\
"{\n"\
"    return texture2D(subtitle, vec2(texcoord.x + subtitle_parallax, 1.0 - texcoord.y));\n"\
"}\n"\
"vec4 sub_r(vec2 texcoord)\n"\
"{\n"\
"    return texture2D(subtitle, vec2(texcoord.x - subtitle_parallax, 1.0 - texcoord.y));\n"\
"}\n"\
"vec3 blend_subtitle(vec3 rgb, vec4 sub)\n"\
"{\n"\
"    return mix(rgb, sub.rgb, sub.a);\n"\
"}\n"\
"#else\n"\
"#  define blend_subtitle(rgb, sub) rgb\n"\
"#endif\n"\
"\n"\
"void main()\n"\
"{\n"\
"    vec3 l, r;\n"\
"    vec3 srgb;\n"\
"\n"\
"#if defined(mode_onechannel)\n"\
"\n"\
"    l = blend_subtitle(tex_l(gl_TexCoord[0].xy), sub_l(gl_TexCoord[0].xy));\n"\
"    r = blend_subtitle(tex_r(gl_TexCoord[1].xy), sub_r(gl_TexCoord[1].xy));\n"\
"    srgb = rgb_to_srgb(ghostbust(mix(l, r, channel), mix(r, l, channel)));\n"\
"\n"\
"#elif defined(mode_even_odd_rows) || defined(mode_even_odd_columns) || defined(mode_checkerboard)\n"\
"\n"\
"    /* This implementation of the masked modes works around many different problems and therefore may seem strange.\n"\
"     * Why not use stencil buffers?\n"\
"     *  - Because we want to filter, to account for masked out features\n"\
"     *  - Because stencil did not work with some drivers when switching fullscreen on/off\n"\
"     * Why not use polygon stipple?\n"\
"     *  - Because we want to filter, to account for masked out features\n"\
"     *  - Because polygon stippling may not be hardware accelerated and is currently broken with many free drivers\n"\
"     * Why use a mask texture? Why not use the mod() function to check for even/odd pixels?\n"\
"     *  - Because mod() is broken with many drivers, and I found no reliable way to work around it. Some\n"\
"     *    drivers seem to use extremely low precision arithmetic in the shaders; too low for reliable pixel\n"\
"     *    position computations.\n"\
"     */\n"\
"    float m = texture2D(mask_tex, gl_TexCoord[2].xy).x;\n"\
"# if quality <= 2\n"\
"    // Do not perform expensive filtering with this quality setting\n"\
"    vec3 rgbc_l = tex_l(gl_TexCoord[0].xy);\n"\
"    vec3 rgbc_r = tex_r(gl_TexCoord[1].xy);\n"\
"# elif defined(mode_even_odd_rows)\n"\
"    vec3 rgb0_l = tex_l(gl_TexCoord[0].xy - vec2(0.0, step_y));\n"\
"    vec3 rgb1_l = tex_l(gl_TexCoord[0].xy);\n"\
"    vec3 rgb2_l = tex_l(gl_TexCoord[0].xy + vec2(0.0, step_y));\n"\
"    vec3 rgbc_l = (rgb0_l + 2.0 * rgb1_l + rgb2_l) / 4.0;\n"\
"    vec3 rgb0_r = tex_r(gl_TexCoord[1].xy - vec2(0.0, step_y));\n"\
"    vec3 rgb1_r = tex_r(gl_TexCoord[1].xy);\n"\
"    vec3 rgb2_r = tex_r(gl_TexCoord[1].xy + vec2(0.0, step_y));\n"\
"    vec3 rgbc_r = (rgb0_r + 2.0 * rgb1_r + rgb2_r) / 4.0;\n"\
"# elif defined(mode_even_odd_columns)\n"\
"    vec3 rgb0_l = tex_l(gl_TexCoord[0].xy - vec2(step_x, 0.0));\n"\
"    vec3 rgb1_l = tex_l(gl_TexCoord[0].xy);\n"\
"    vec3 rgb2_l = tex_l(gl_TexCoord[0].xy + vec2(step_x, 0.0));\n"\
"    vec3 rgbc_l = (rgb0_l + 2.0 * rgb1_l + rgb2_l) / 4.0;\n"\
"    vec3 rgb0_r = tex_r(gl_TexCoord[1].xy - vec2(step_x, 0.0));\n"\
"    vec3 rgb1_r = tex_r(gl_TexCoord[1].xy);\n"\
"    vec3 rgb2_r = tex_r(gl_TexCoord[1].xy + vec2(step_x, 0.0));\n"\
"    vec3 rgbc_r = (rgb0_r + 2.0 * rgb1_r + rgb2_r) / 4.0;\n"\
"# elif defined(mode_checkerboard)\n"\
"    vec3 rgb0_l = tex_l(gl_TexCoord[0].xy - vec2(0.0, step_y));\n"\
"    vec3 rgb1_l = tex_l(gl_TexCoord[0].xy - vec2(step_x, 0.0));\n"\
"    vec3 rgb2_l = tex_l(gl_TexCoord[0].xy);\n"\
"    vec3 rgb3_l = tex_l(gl_TexCoord[0].xy + vec2(step_x, 0.0));\n"\
"    vec3 rgb4_l = tex_l(gl_TexCoord[0].xy + vec2(0.0, step_y));\n"\
"    vec3 rgbc_l = (rgb0_l + rgb1_l + 4.0 * rgb2_l + rgb3_l + rgb4_l) / 8.0;\n"\
"    vec3 rgb0_r = tex_r(gl_TexCoord[1].xy - vec2(0.0, step_y));\n"\
"    vec3 rgb1_r = tex_r(gl_TexCoord[1].xy - vec2(step_x, 0.0));\n"\
"    vec3 rgb2_r = tex_r(gl_TexCoord[1].xy);\n"\
"    vec3 rgb3_r = tex_r(gl_TexCoord[1].xy + vec2(step_x, 0.0));\n"\
"    vec3 rgb4_r = tex_r(gl_TexCoord[1].xy + vec2(0.0, step_y));\n"\
"    vec3 rgbc_r = (rgb0_r + rgb1_r + 4.0 * rgb2_r + rgb3_r + rgb4_r) / 8.0;\n"\
"# endif\n"\
"    vec3 rgbcs_l = blend_subtitle(rgbc_l, sub_l(gl_TexCoord[0].xy));\n"\
"    vec3 rgbcs_r = blend_subtitle(rgbc_r, sub_r(gl_TexCoord[1].xy));\n"\
"    srgb = rgb_to_srgb(ghostbust(mix(rgbcs_r, rgbcs_l, m), mix(rgbcs_l, rgbcs_r, m)));\n"\
"\n"\
"#elif defined(mode_red_cyan_dubois) || defined(mode_green_magenta_dubois) || defined(mode_amber_blue_dubois)\n"\
"\n"\
"    // The Dubois anaglyph method is generally the highest quality anaglyph method.\n"\
"    // Authors page: http://www.site.uottawa.ca/~edubois/anaglyph/\n"\
"    // This method depends on the characteristics of the display device and the anaglyph glasses.\n"\
"    // According to the author, the matrices below are intended to be applied to linear RGB values,\n"\
"    // and are designed for CRT displays.\n"\
"    l = blend_subtitle(tex_l(gl_TexCoord[0].xy), sub_l(gl_TexCoord[0].xy));\n"\
"    r = blend_subtitle(tex_r(gl_TexCoord[1].xy), sub_r(gl_TexCoord[1].xy));\n"\
"# if defined(mode_red_cyan_dubois)\n"\
"    // Source of this matrix: http://www.site.uottawa.ca/~edubois/anaglyph/LeastSquaresHowToPhotoshop.pdf\n"\
"    mat3 m0 = mat3(\n"\
"             0.437, -0.062, -0.048,\n"\
"             0.449, -0.062, -0.050,\n"\
"             0.164, -0.024, -0.017);\n"\
"    mat3 m1 = mat3(\n"\
"            -0.011,  0.377, -0.026,\n"\
"            -0.032,  0.761, -0.093,\n"\
"            -0.007,  0.009,  1.234);\n"\
"# elif defined(mode_green_magenta_dubois)\n"\
"    // Source of this matrix: http://www.flickr.com/photos/e_dubois/5132528166/\n"\
"    mat3 m0 = mat3(\n"\
"            -0.062,  0.284, -0.015,\n"\
"            -0.158,  0.668, -0.027,\n"\
"            -0.039,  0.143,  0.021);\n"\
"    mat3 m1 = mat3(\n"\
"             0.529, -0.016,  0.009,\n"\
"             0.705, -0.015,  0.075,\n"\
"             0.024, -0.065,  0.937);\n"\
"# elif defined(mode_amber_blue_dubois)\n"\
"    // Source of this matrix: http://www.flickr.com/photos/e_dubois/5230654930/\n"\
"    mat3 m0 = mat3(\n"\
"             1.062, -0.026, -0.038,\n"\
"            -0.205,  0.908, -0.173,\n"\
"             0.299,  0.068,  0.022);\n"\
"    mat3 m1 = mat3(\n"\
"            -0.016,  0.006,  0.094,\n"\
"            -0.123,  0.062,  0.185,\n"\
"            -0.017, -0.017,  0.911);\n"\
"# endif\n"\
"    srgb = rgb_to_srgb(m0 * l + m1 * r);\n"\
"\n"\
"#else // lower quality anaglyph methods\n"\
"\n"\
"    l = rgb_to_srgb(blend_subtitle(tex_l(gl_TexCoord[0].xy), sub_l(gl_TexCoord[0].xy)));\n"\
"    r = rgb_to_srgb(blend_subtitle(tex_r(gl_TexCoord[1].xy), sub_r(gl_TexCoord[1].xy)));\n"\
"# if defined(mode_red_cyan_monochrome)\n"\
"    srgb = vec3(srgb_to_lum(l), srgb_to_lum(r), srgb_to_lum(r));\n"\
"# elif defined(mode_red_cyan_half_color)\n"\
"    srgb = vec3(srgb_to_lum(l), r.g, r.b);\n"\
"# elif defined(mode_red_cyan_full_color)\n"\
"    srgb = vec3(l.r, r.g, r.b);\n"\
"# elif defined(mode_green_magenta_monochrome)\n"\
"    srgb = vec3(srgb_to_lum(r), srgb_to_lum(l), srgb_to_lum(r));\n"\
"# elif defined(mode_green_magenta_half_color)\n"\
"    srgb = vec3(r.r, srgb_to_lum(l), r.b);\n"\
"# elif defined(mode_green_magenta_full_color)\n"\
"    srgb = vec3(r.r, l.g, r.b);\n"\
"# elif defined(mode_amber_blue_monochrome)\n"\
"    srgb = vec3(srgb_to_lum(l), srgb_to_lum(l), srgb_to_lum(r));\n"\
"# elif defined(mode_amber_blue_half_color)\n"\
"    srgb = vec3(srgb_to_lum(l), srgb_to_lum(l), r.b);\n"\
"# elif defined(mode_amber_blue_full_color)\n"\
"    srgb = vec3(l.r, l.g, r.b);\n"\
"# elif defined(mode_red_green_monochrome)\n"\
"    srgb = vec3(srgb_to_lum(l), srgb_to_lum(r), 0.0);\n"\
"# elif defined(mode_red_blue_monochrome)\n"\
"    srgb = vec3(srgb_to_lum(l), 0.0, srgb_to_lum(r));\n"\
"# endif\n"\
"\n"\
"#endif\n"\
"\n"\
"    gl_FragColor = vec4(srgb, 1.0);\n"\
"}\n"\
""
#endif
