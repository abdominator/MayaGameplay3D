#ifndef _MPxVertexBufferMutator
#define _MPxVertexBufferMutator
//-
// ==========================================================================
// Copyright (C) 2012 Autodesk, Inc., and/or its licensors.  All
// rights reserved.
//
// The coded instructions, statements, computer programs, and/or related
// material (collectively the "Data") in these files contain unpublished
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its
// licensors,  which is protected by U.S. and Canadian federal copyright law
// and by international treaties.
//
// The Data may not be disclosed or distributed to third parties or be
// copied or duplicated, in whole or in part, without the prior written
// consent of Autodesk.
//
// The copyright notices in the Software and this entire statement,
// including the above license grant, this restriction and the following
// disclaimer, must be included in all copies of the Software, in whole
// or in part, and all derivative works of the Software, unless such copies
// or derivative works are solely in the form of machine-executable object
// code generated by a source language processor.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE,
// OR ARISING FROM A COURSE OF DEALING, USAGE, OR TRADE PRACTICE. IN NO
// EVENT WILL AUTODESK AND/OR ITS LICENSORS BE LIABLE FOR ANY LOST
// REVENUES, DATA, OR PROFITS, OR SPECIAL, DIRECT, INDIRECT, OR
// CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK AND/OR ITS LICENSORS HAS
// BEEN ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES.
// ==========================================================================
//+
//
// CLASS: MPxVertexBufferMutator
//
// ****************************************************************************


#if defined __cplusplus

// ****************************************************************************
// INCLUDED HEADER FILES

#include <maya/MStatus.h>
#include <maya/MHWGeometry.h>
#include <maya/MDagPath.h>
#include <maya/MViewport2Renderer.h>
#include <maya/MComponentDataIndexing.h>

// ****************************************************************************
// DECLARATIONS

class MString;
class MUserData;

// ****************************************************************************
// NAMESPACE

namespace MHWRender
{
// ****************************************************************************
// CLASS DECLARATION (MPxVertexBufferMutator)

//! \ingroup OpenMayaRender MPx
//! \brief Base class for user defined vertex buffer generators.
/*!

Implementations of MPxVertexBufferMutator must be registered with Maya through
MDrawRegistry.

MPxVertexBufferMutators are registered with a unique buffer name.  
The name signifies the name of the custom stream the mutator can alter.  
When an MPxShaderOverride or custom renderer uses an effect with custom input 
streams they can provide a unique name in the MVertexBufferDescriptor and 
a registered MPxVertexBufferMutator will be used to alter the custom stream
for a given shape using the incoming requirements held in the MVertexBuffer.

modifyVertexStream() is called to allow the mutator to alter the vertex data
Access the requirements for the requested stream through vertexBuffer.descriptor().
Populate the stream using vertexBuffer.acquire() and vertexBuffer.commit().
*/

class OPENMAYARENDER_EXPORT MPxVertexBufferMutator
{
public:

    MPxVertexBufferMutator();
    virtual ~MPxVertexBufferMutator();

    virtual void modifyVertexStream(const MObject& object,
		MVertexBuffer& vertexBuffer, const MComponentDataIndexing& targetIndexing) const=0;

    static	const char*	className();
};

} // namespace MHWRender

#endif /* __cplusplus */
#endif /* _MPxVertexBufferMutator */
