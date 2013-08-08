/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2012 Scientific Computing and Imaging Institute,
   University of Utah.

   License for the specific language governing rights and limitations under
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

/// \author James Hughes
/// \date   September 2012
/// \brief  Not sure this file should go in Modules/Render. But it is an 
///         auxiliary file to the ViewScene render module.

#include <iostream>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <Core/Application/Application.h>

#include "GLWidget.h"

using namespace SCIRun::Gui;

void logFunction(const std::string& str, Spire::Interface::LOG_LEVEL level)
{
  std::cout << str;
}

//------------------------------------------------------------------------------
GLWidget::GLWidget(QtGLContext* context) :
    QGLWidget(context),
    mContext(new GLContext(this))
{
  /// \todo Implement this intelligently. This function is called everytime
  ///       there is a new graphics context.
  std::vector<std::string> shaderSearchDirs;
  
  auto shadersInBinDirectory = SCIRun::Core::Application::Instance().executablePath() / "Shaders";
  shaderSearchDirs.push_back(shadersInBinDirectory.string());

#ifdef SPIRE_USE_STD_THREADS
  mGraphics = std::shared_ptr<Spire::SCIRun::SRInterface>(
      new Spire::SCIRun::SRInterface(
          std::dynamic_pointer_cast<Spire::Context>(mContext),
          shaderSearchDirs, true));
#else
  mGraphics = std::shared_ptr<Spire::SCIRun::SRInterface>(
      new Spire::SCIRun::SRInterface(
          std::dynamic_pointer_cast<Spire::Context>(mContext),
          shaderSearchDirs, false, logFunction));
  mTimer = new QTimer(this);
  connect(mTimer, SIGNAL(timeout()), this, SLOT(updateRenderer()));
  mTimer->start(35);
#endif

  // Add shader attributes that we will be using.
  mGraphics->addShaderAttribute("aPos",         3,  false,  sizeof(float) * 3,  Spire::Interface::TYPE_FLOAT);
  mGraphics->addShaderAttribute("aNormal",      3,  false,  sizeof(float) * 3,  Spire::Interface::TYPE_FLOAT);
  mGraphics->addShaderAttribute("aFieldData",   1,  false,  sizeof(float),      Spire::Interface::TYPE_FLOAT);
  mGraphics->addShaderAttribute("aColorFloat",  4,  false,  sizeof(float) * 4,  Spire::Interface::TYPE_FLOAT);
  mGraphics->addShaderAttribute("aColor",       4,  true,   sizeof(char) * 4,   Spire::Interface::TYPE_UBYTE);

  /// \todo Where should we store common shader names?
  std::vector<std::tuple<std::string, Spire::Interface::SHADER_TYPES>> shaderFiles;
  shaderFiles.push_back(std::make_pair("UniformColor.vsh", Spire::Interface::VERTEX_SHADER));
  shaderFiles.push_back(std::make_pair("UniformColor.fsh", Spire::Interface::FRAGMENT_SHADER));

  mGraphics->addPersistentShader(
      "UniformColor", 
      shaderFiles);

  shaderFiles.clear();
  shaderFiles.push_back(std::make_pair("ColorMap.vsh", Spire::Interface::VERTEX_SHADER));
  shaderFiles.push_back(std::make_pair("ColorMap.fsh", Spire::Interface::FRAGMENT_SHADER));

  mGraphics->addPersistentShader(
      "ColorMap", 
      shaderFiles);

  // We must disable auto buffer swap on the 'paintEvent'.
  setAutoBufferSwap(false);
}

//------------------------------------------------------------------------------
GLWidget::~GLWidget()
{
  // Need to inform module that the context is being destroyed.
  if (mGraphics != nullptr)
  {
    //std::cout << "Terminating spire." << std::endl;
    mGraphics->terminate();
    mGraphics.reset();
  }
}

//------------------------------------------------------------------------------
void GLWidget::initializeGL()
{
}

//------------------------------------------------------------------------------
Spire::SCIRun::SRInterface::MouseButton GLWidget::getSpireButton(QMouseEvent* event)
{
  Spire::SCIRun::SRInterface::MouseButton btn = Spire::SCIRun::SRInterface::MOUSE_NONE;
  if (event->buttons() & Qt::LeftButton)
    btn = Spire::SCIRun::SRInterface::MOUSE_LEFT;
  else if (event->buttons() & Qt::RightButton)
    btn = Spire::SCIRun::SRInterface::MOUSE_RIGHT;
  else if (event->buttons() & Qt::MidButton)
    btn = Spire::SCIRun::SRInterface::MOUSE_MIDDLE;
  
  return btn;
}

//------------------------------------------------------------------------------
void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
  // Extract appropriate key.
  Spire::SCIRun::SRInterface::MouseButton btn = getSpireButton(event);
  mGraphics->inputMouseMove(glm::ivec2(event->x(), event->y()), btn);
}

//------------------------------------------------------------------------------
void GLWidget::mousePressEvent(QMouseEvent* event)
{
  Spire::SCIRun::SRInterface::MouseButton btn = getSpireButton(event);
  mGraphics->inputMouseDown(glm::ivec2(event->x(), event->y()), btn);
}

//------------------------------------------------------------------------------
void GLWidget::mouseReleaseEvent(QMouseEvent* event)
{
  Spire::SCIRun::SRInterface::MouseButton btn = getSpireButton(event);
  mGraphics->inputMouseUp(glm::ivec2(event->x(), event->y()), btn);
}

//------------------------------------------------------------------------------
void GLWidget::wheelEvent(QWheelEvent * event)
{
  mGraphics->inputMouseWheel(event->delta());
}

//------------------------------------------------------------------------------
void GLWidget::resizeGL(int width, int height)
{
  mGraphics->eventResize(static_cast<size_t>(width),
                         static_cast<size_t>(height));
}

//------------------------------------------------------------------------------
void GLWidget::updateRenderer()
{
  mContext->makeCurrent();    // Required on windows...
  mGraphics->ntsDoFrame();
  mContext->swapBuffers();
}

