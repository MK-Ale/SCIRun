/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2015 Scientific Computing and Imaging Institute,
   University of Utah.


   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

// Uniforms
uniform float    uAspectRatio  ;      
uniform float    uWindowWidth  ;
uniform float    uXTranslate;
uniform float    uYTranslate;
uniform float    uDisplaySide  ;
uniform float    uDisplayLength;

// Attributes
attribute vec3  aPos;
attribute vec2  aTexCoord;

//Outputs
varying vec2 fTexCoord;

//constants
const float text_x_scale = 0.5;
const float bar_buffer = 0.1;

void main( void )
{
  bool ds = uDisplaySide == 0.;
  bool full = uDisplayLength == 1.;
  bool half1 = uDisplayLength == 0.;
  vec3 newPos = aPos;
  float tick_separation = aPos.z * (1. - bar_buffer) * (full?2.:1.);
  float x_scale = 2. / uWindowWidth;
  float y_scale = 2. / (uWindowWidth / uAspectRatio);
  float x_trans = -1. + (  ds ?0.:(tick_separation+(full?bar_buffer:(half1?0.:(bar_buffer+1.)))))
                        + uXTranslate / 50.;
  float y_trans = -1. + ((!ds)?0.:(tick_separation+(full?bar_buffer:(half1?0.:(bar_buffer+1.)))))   
                        + uYTranslate / 50.;
  gl_Position = vec4(newPos.x * x_scale + x_trans, 
                     newPos.y * y_scale + y_trans, 0., 1.0);
  fTexCoord = aTexCoord;
}
