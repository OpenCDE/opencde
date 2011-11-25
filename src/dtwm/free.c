/* $XConsortium: free.c /main/5 1995/07/15 20:38:35 drk $ */
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
#include <X11/Xatom.h>

static void FreeWinData(
WSMWinData *data, int num
);

/*	Function Name: FreeRequest
 *	Description: Frees data in the request that has been allocated.
 *	Arguments: request - the request.
 *	Returns: none.
 */

void
FreeRequest(WSMRequest *request)
{
    register int i;

    if (!request->any.allocated)
	return;			/* Nothing to free. */

    switch(request->any.type) {
    case WSM_CONNECT:
	XtFree((XtPointer) request->connect.known_versions);
	break;
    case WSM_EXTENSIONS:
        {
	    register int num = request->extensions.num_extensions;
	    register String *ptr;

	    num = request->extensions.num_extensions;
	    ptr = request->extensions.extension_suggestions;
	    for (i = 0; i < num; i++, ptr++) 
		XtFree((XtPointer) *ptr);

	    XtFree((XtPointer) request->extensions.extension_suggestions);
	}
	break;
    case WSM_SET_STATE:
        {
	    register int num = request->set_state.num_win_info_list;
	    WSMWinInfo *win_info = request->set_state.win_info_list;

	    for (i = 0; i < num; i++, win_info++) 
		FreeWinData(win_info->data_list, win_info->num_data_list);

	    XtFree((XtPointer) request->set_state.win_info_list);
	}
	break;
    default:
	break;
    }
}

/*	Function Name: FreeRequest
 *	Description: Frees data in the request that has been allocated.
 *	Arguments: reply - the reply.
 *	Returns: none.
 */

void
FreeReply(WSMReply *reply)
{
    register int i;

    if (!reply->any.allocated)
	return;			/* Nothing to free. */

    switch(reply->any.type) {
    case WSM_EXTENSIONS:
        {
	    register int num = reply->extensions.num_extensions;
	    register String *ptr;

	    num = reply->extensions.num_extensions;
	    ptr = reply->extensions.extensions;
	    for (i = 0; i < num; i++, ptr++) 
		XtFree((XtPointer) *ptr);

	    XtFree((XtPointer) reply->extensions.extensions);
	}
	break;
    case WSM_GET_STATE:
        {
	    WSMWinInfo *win_info = reply->get_state.win_info_list;
	    register int num = reply->get_state.num_win_info_list;

	    for (i = 0; i < num; i++, win_info++) 
		FreeWinData(win_info->data_list, win_info->num_data_list);

	    XtFree((XtPointer) reply->get_state.win_info_list);
	}
	break;
    case WSM_REG_WINDOW:
	FreeWinData(reply->register_window.window_data,
		    reply->register_window.num_window_data);
	break;
    default:
	break;
    }
}

/************************************************************
 *
 *  Internal routines
 *
 ************************************************************/

/*	Function Name: FreeWinData
 *	Description: Frees the data associated with this window.
 *	Arguments: data - The data to free.
 *                 num - number of elements in data.
 *	Returns: none.
 */

static void
FreeWinData(WSMWinData *data, int num)
{
    register int i;
    WSMWinData *top = data;

    for (i = 0; i < num; i++, data++) {
	switch (data->type) {
	case WSM_CHAR_LIST_DATA:
	    XtFree((XtPointer) data->data.char_ptr);
	    break;
	case WSM_SHORT_LIST_DATA: 
	    XtFree((XtPointer) data->data.short_ptr);
	    break;
	case WSM_LONG_LIST_DATA:
	    XtFree((XtPointer) data->data.long_ptr);
	    break;
	default:
	    break;
	}
    }
    
    XtFree((XtPointer) top);
}	
