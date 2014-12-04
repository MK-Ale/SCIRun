/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2009 Scientific Computing and Imaging Institute,
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


#ifndef CORE_ALGORITHMS_FIELDS_FIELDDATA_SWAPFIELDDATAWITHMATRIXENTRIESALGO_H
#define CORE_ALGORITHMS_FIELDS_FIELDDATA_SWAPFIELDDATAWITHMATRIXENTRIESALGO_H 1

//// Datatypes that the algorithm uses
//#include <Core/Datatypes/Mesh.h>
//#include <Core/Datatypes/Field.h>
//#include <Core/Datatypes/Matrix.h>

#include <Core/Datatypes/DatatypeFwd.h> 
//#include <Core/Datatypes/DenseMatrix.h>
// Base class for algorithm
#include <Core/Algorithms/Base/AlgorithmBase.h>

// for Windows support
#include <Core/Algorithms/Legacy/Fields/share.h>

namespace SCIRun {
  namespace Core {
    namespace Algorithms {
      namespace Fields {

		ALGORITHM_PARAMETER_DECL(PreserveScalar); 

class SCISHARE SwapFieldDataWithMatrixEntriesAlgo : public AlgorithmBase
{
  public:
    SwapFieldDataWithMatrixEntriesAlgo();
		//static AlgorithmInputName SwapMatrix; 
  
    bool runImpl(FieldHandle input_field, 
				Datatypes::DenseMatrixHandle input_matrix, 
				FieldHandle& output_field, 
				Datatypes::DenseMatrixHandle& output_matrix)const;

		bool runImpl(FieldHandle input, Datatypes::DenseMatrixHandle input_matrix, FieldHandle& output) const; 

		virtual AlgorithmOutput run_generic(const AlgorithmInput& input) const override; 
};
			}}}}

#endif

