#ifndef _MItSelectionList
#define _MItSelectionList
//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc., and/or its licensors.  All
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
// CLASS:    MItSelectionList
//
// ****************************************************************************

#if defined __cplusplus

// ****************************************************************************
// INCLUDED HEADER FILES


#include <maya/MStatus.h>
#include <maya/MObject.h>
#include <maya/MSelectionList.h>
#include <maya/MStringArray.h>

// ****************************************************************************
// DECLARATIONS

class MDagPath;

// ****************************************************************************
// CLASS DECLARATION (MItSelectionList)

//! \ingroup OpenMaya
//! \brief Iterate over the items in the selection list. 
/*!
Class for iterating over the items in an MSelection list.
A filter can be specified so that only those items of interest on a selection
list can be obtained.

If a filter is specified then the children of DAG selection items will be
searched if the selection item does not match the filter.
For example, if  <i>filter = MFn::kNurbsCurve</i>  and a transform is selected
then the underlying shape for the transform will be in the iteration if it
is a nurbs curve.

<b>Example:</b> (of a simple traversal)

\code
    MSelectionList activeList;
    MGlobal::activeSelectionList(activeList);
    MItSelectionList iter( activeList );

    for ( ; !iter.isDone(); iter.next() )
    {
        MDagPath item;
        MObject component;
        iter.getDagPath( item, component );

        // do something with it
    }
\endcode


<b>Example:</b> (of a traversal to find all active cameras)

\code
    MSelectionList activeList;
    MGlobal::activeSelectionList(activeList);
    MItSelectionList iter( activeList, MFn::kCamera );

    for ( ; !iter.isDone(); iter.next() )
    {
        MDagPath camera;
        iter.getDagPath( camera );

        MFnCamera cameraFn( camera );

        // ...
   }
\endcode
*/
class OPENMAYA_EXPORT MItSelectionList
{
public:
	//! Types of items which can appear on a selection list.
	enum selItemType{
		kUnknownItem = -1,
		kDagSelectionItem,	//!< DAG node or component
		kAnimSelectionItem,	//!< keyset
		kDNselectionItem,	//!< dependency node
		kPlugSelectionItem	//!< plug
	};
	bool		isDone( MStatus * ReturnStatus = NULL );
	MStatus		next();
	MStatus		reset();
	MStatus		getDependNode( MObject &depNode );
	MStatus		getDagPath( MDagPath &dagPath, MObject &component );
	MStatus     getDagPath( MDagPath &dagPath );
	MStatus     getPlug( MPlug &plug );
	MStatus     getStrings( MStringArray & array );
	selItemType itemType( MStatus * ReturnStatus = NULL );
	MStatus		setFilter( MFn::Type filter );
	bool		hasComponents( MStatus * ReturnStatus = NULL ) const;
	MItSelectionList( 	const MSelectionList & list,
						MFn::Type = MFn::kInvalid,
						MStatus * ReturnStatus = NULL );
	virtual ~MItSelectionList();

	static const char* 	className();

protected:
// No protected members

private:
	MObject			findMObject(void *);
	MStatus				resetInner();
	void*				f_main_iter;
	void*				f_component_iter;
	void*				list_data;
	MFn::Type			f_filter;
};

#endif /* __cplusplus */
#endif /* _MItSelectionList */
