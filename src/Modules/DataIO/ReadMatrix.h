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

#ifndef MODULES_DATAIO_READ_MATRIX_H
#define MODULES_DATAIO_READ_MATRIX_H

#include <Core/Dataflow/Network/Module.h>
#include <Modules/DataIO/Share.h>

namespace SCIRun {
namespace Modules {
namespace DataIO {
  
  //TODO DAN
  class SCISHARE ReadMatrixModule : public SCIRun::Domain::Networks::Module,
    public Has1InputPort<StringPortTag>,
    public Has2OutputPorts<MatrixPortTag, StringPortTag>
  {
  public:
    ReadMatrixModule();
    virtual void execute();
    static std::string inputPort0Name() { return "Filename"; }
    static std::string outputPort0Name() { return "Matrix"; }
    static std::string outputPort1Name() { return inputPort0Name(); }
  private:
    std::string filename_;
  };

}}}

#endif