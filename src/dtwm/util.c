/* $XConsortium: util.c /main/5 1995/07/15 20:38:54 drk $ */
/*
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF).  See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 */
/*
 * HISTORY
 */

#include "wsm_proto.h"

/************************************************************
 *
 *  Routines for converting from targets to names to atoms.
 *
 ************************************************************/

/*	Function Name: _WSMReqTypeToName
 *	Description: Given a request type, return its name, used mostly
 *                   for error messages.
 *	Arguments: req_type - The request type to check.
 *	Returns: a string that is the name of the request.
 */

String
_WSMReqTypeToName(WSMRequestType req_type)
{
    switch (req_type) {
    case WSM_CONNECT:
	return("Connect");
    case WSM_EXTENSIONS:
	return("Extensions");
    case WSM_CONFIG_FMT:
	return("Config Format");
    case WSM_GET_STATE:
	return("Get State");
    case WSM_SET_STATE:
	return("Set State");
    case WSM_REG_WINDOW:
	return("Register Window");
    default:
	return("unknown");
    }
}

/*	Function Name: _WSMTargetToReqType
 *	Description: Given a target (Atom) and a display, returns the
 *                   request type associated with this atom.
 *	Arguments: dpy - The display.
 *                 target - The atom that needs to be mapped to a request.
 *	Returns: The request type.
 */

WSMRequestType
_WSMTargetToReqType(Display *dpy, Atom target)
{
    WSMDispInfo *disp_atoms = _WSMGetDispInfo(dpy);

    if (target == disp_atoms->connect) 
	return(WSM_CONNECT);
    if (target == disp_atoms->extensions) 
	return(WSM_EXTENSIONS);
    if (target == disp_atoms->config_fmt) 
	return(WSM_CONFIG_FMT);
    if (target == disp_atoms->get_state) 
	return(WSM_GET_STATE);
    if (target == disp_atoms->set_state) 
	return(WSM_SET_STATE);
    if (target == disp_atoms->reg_window) 
	return(WSM_REG_WINDOW); 

    /*
     * Atom doesn't match any request, generate error message.
     */
    
    return(WSM_UNKNOWN);
}

/*	Function Name: _WSMReqTypeToTarget
 *	Description: Given a request type and a display, return the target
 *                   (Atom) that maps to it.
 *	Arguments: dpy - The display.
 *                 req_type - The request type id.
 *	Returns: The atom that maps to this request type on this display.
 */

Atom
_WSMReqTypeToTarget(Display *dpy, WSMRequestType req_type)
{
    WSMDispInfo *disp_atoms = _WSMGetDispInfo(dpy);

    switch (req_type) {
    case WSM_CONNECT:
	return(disp_atoms->connect);
    case WSM_EXTENSIONS:
	return(disp_atoms->extensions);
    case WSM_CONFIG_FMT:
	return(disp_atoms->config_fmt);
    case WSM_GET_STATE:
	return(disp_atoms->get_state);
    case WSM_SET_STATE:
	return(disp_atoms->set_state);
    case WSM_REG_WINDOW:
	return(disp_atoms->reg_window);
    default:
	break;
    }

    return(None);		/* Universal null atom. */
}

/*	Function Name: _WSMRequiresConfigFormat
 *	Description: Returns True if this request requires a valid config
 *                   formats.
 *	Arguments: request_type - the request type to check.
 *	Returns: True if config format required for this request.
 */

Boolean
_WSMRequiresConfigFormat(WSMRequestType request_type)
{
    switch (request_type) {
    case WSM_GET_STATE:
    case WSM_SET_STATE:
    case WSM_REG_WINDOW:
	return(True);
    default:
	break;
    }

    return(False);
}

/*	Function Name: _WSMGetConfigFormatType
 *	Description: Gets the config format type for this window.
 *	Arguments: win - The window to check.
 *	Returns: The config format type that matches the window passed.
 */

WSMConfigFormatType
_WSMGetConfigFormatType(Window win)
{
    if (win == None)
	return(WSM_GLOBAL_FMT);

    if (win & ~WIN_MASK)
	return(WSM_ICON_FMT);

    return(WSM_WINDOW_FMT);
}

/*	Function Name: _WSMGetMatchingAttr
 *	Description: Gets the attribute from the format data passed
 *                   that matches the the name passed.
 *	Arguments: nameq - The name to match stored as a quark.
 *                 fmt_data - the config format data to check against.
 *	Returns: The attribute information that matches the name passed or NULL
 */

WSMAttribute *
_WSMGetMatchingAttr(XrmQuark nameq, WSMConfigFormatData *fmt_data)
{
    register int i;
    WSMAttribute * attr = fmt_data->attr_list;

    for (i = 0; i < fmt_data->num_attrs; i++, attr++) {
	if (nameq == attr->nameq)
	    return(attr);
    }

    return(NULL);
}

/*	Function Name: _WSMGetMatchingWinData
 *	Description: Gets the window data in the list passed whose name
 *                   matches quark passed.
 *	Arguments: win_data_top - The top of the window data list.
 *                 num - The number of items in the window data list.
 *                 nameq - The name to match.
 *	Returns: The matching window data or NULL.
 */

WSMWinData *
_WSMGetMatchingWinData(WSMWinData *win_data_top, int num, XrmQuark nameq)
{
    register int i; 
    WSMWinData *local = win_data_top;

    for (i = 0; i < num; i++, local++) {
	if (local->nameq == nameq)
	    return(local);
    }

    return(NULL);
}

