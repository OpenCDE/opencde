/* $XConsortium: send.c /main/5 1995/07/15 20:38:50 drk $ */
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

#include <Xm/Transfer.h>
#include "wsm_proto.h"
#include "utm_send.h"

typedef struct _RequestInfo {
    WSMReplyCallbackFunc reply_callback; /* The reply callback func */
    XtPointer reply_data;	/* The user data for the callback func */
    WSMRequestType request_type; /* The kind of request for cross check. */
    Atom send_atom;		/* The atom that we sent this message to. */
} RequestInfo;

static void UTMReplyReceived(
Widget, XtPointer, XtPointer
);

static void ReplyReceived(
Widget, XtPointer, Atom *, Atom *, XtPointer, unsigned long *, int *
);

/*	Function Name: WSMSendMessage
 *	Description: Sends a message to WSM or WM on the screen
 *                   and display specified.
 *	Arguments: w - any widget on this display and screen that
 *                     also has destination callback.
 *                     Note - This widget MUST have the destination
 *                            callback set to UTMDestinationProc that
 *                            is defined in utm_send.c.
 *                 send_to - either WSMWorkspaceManager or WSMWindowManager
 *                 request - the request to send.
 *                 reply_callback - The routine to call when the
 *                                  reply comes in.
 *                 reply_data - Client data passed to the reply_callback.
 *	Returns: True if an attempt is made to retrieve the selection,
 *               False if an obvious error occured.
 * 
 * NOTE: Reply callback will be called with reply == NULL if unable
 *       to convert request.
 */

Boolean
WSMSendMessage(Widget w, WSMClientType send_to, WSMRequest *request, 
	       WSMReplyCallbackFunc reply_callback, XtPointer reply_data)
{
    int screen_num = XScreenNumberOfScreen(XtScreen(w));
    Display *dpy = XtDisplay(w);
    Atom send_atom = _WSMGetSelectionAtom(dpy, screen_num, send_to);
    MessageData msg_data;
    unsigned long msg_len;
    RequestInfo *req_info;
    WSMErrorCode error;
    Time time = GetTimestamp(dpy);

    if (send_atom == None) {
	fprintf(stderr, "%s: Could not get selection atom to send message\n",
		"Internal Error");
	return(False);
    }

    /*
     * Package human-readable request data into protocol package.
     */
    msg_data = _WSMPackRequest(dpy, screen_num, request, &msg_len, &error);
    if (msg_data == NULL) {
	(*reply_callback)(w, reply_data, NULL, error);
	return(False);
    }

    req_info = (RequestInfo *) XtMalloc(sizeof(RequestInfo));
    req_info->reply_callback = reply_callback;	/* The reply callback func */
    req_info->reply_data = reply_data;	/* user data for the callback func */
    req_info->request_type = request->any.type;/*request kind for cross check*/
    req_info->send_atom = send_atom;	/* Atom we sent this message to. */

    if (!XtIsRealized(w)) {
	fprintf(stderr, "%s WSMSendMessage must be realized, and is not.\n",
		"Programmer Error: Widget passed to");
	return(False);
    }

    UTMSendMessage(w,
		   send_atom,
		   _WSMReqTypeToTarget(dpy, request->any.type),
		   (XtPointer) msg_data, msg_len, WSM_PROTO_FMT,
		   UTMReplyReceived, req_info,
		   time);
    return(True);
}


/************************************************************
 *
 *  Internal Routines.
 *
 ************************************************************/


/*	Function Name: UTMReplyReceived
 *	Description: Called after the selection owner's convert proc
 *                   has finished.
 *	Arguments: w - The widget who initiated the request.
 *                 clientData - 
 *                 callData - 
 *	Returns: none
 */
static void
UTMReplyReceived(Widget w, XtPointer clientData, XtPointer callData)
{
  XmSelectionCallbackStruct *scs = (XmSelectionCallbackStruct *) callData;
  RequestInfo *req_info = (RequestInfo *) clientData;
  Boolean errorFound = False;
  Atom type = _WSMReqTypeToTarget(XtDisplay(w), req_info->request_type);

  /* Let's check some other values just to make sure things are ok. */
  if (scs->reason != XmCR_OK) {
    fprintf(stderr, "ERROR: Bad reason value received in UTMReplyReceived.\n");
    errorFound = True;
  }
  if (scs->type == XT_CONVERT_FAIL) {
    fprintf(stderr, "ERROR: Convert failure detected in UTMReplyReceived.\n");
    errorFound = True;
  }
  if (scs->flags != XmSELECTION_DEFAULT) {
    fprintf(stderr, "ERROR: Bad flags value received in UTMReplyReceived.\n");
    errorFound = True;
  }
  if (errorFound)
    return;

  ReplyReceived(w,
		req_info, /* the request info pointer to fill in. */
		&scs->selection,
		&type,  /* type of request that was made. */
		scs->value, /* data returned from conversion. */
		&scs->length,
		&scs->format);
}


/*	Function Name: ReplyReceived
 *	Description: Called when a reply is received from a request
 *                   initiated by a WSMSendMessage.
 *	Arguments: w - The widget who initiated the request.
 *                 req_info_ptr - pointer to the request info.
 *                 selection - The selection that has been converted.
 *                 req_type_atom - The type of request that was made.
 *                 length - the amount of message data.
 *                 format - the format of the reply.
 *	Returns: none
 */
static void
ReplyReceived(Widget w, XtPointer req_info_ptr,
	      Atom *selection, Atom *req_type_atom,
	      XtPointer value, unsigned long *length, int *format)
{
    RequestInfo *req_info = (RequestInfo *) req_info_ptr;
    WSMReply reply;
    Display *dpy = XtDisplay(w);
    int screen_num;
    WSMErrorCode fail_code = WSM_SUCCESS;

    /*
     * First a few checks to make sure everything is as we expect.
     */

    if (*selection != req_info->send_atom) {
	fprintf(stderr, "%s, request %d - reply %d\n",
	       "Selection of the reply is not the same as the request",
	       (int) req_info->send_atom, (int) *selection);

	    fail_code = WSM_ERROR_INTERNAL;
    }
    if (*req_type_atom != _WSMReqTypeToTarget(dpy, req_info->request_type)) {
	if (*req_type_atom == None) {
	    if (XGetSelectionOwner(dpy, *selection) == None)
	      {
		fail_code = WSM_ERROR_NO_SEL_OWNER;
		fprintf(stderr, "No owner for selection #%d\n", (int)*selection);
	      }
	    else
		fail_code = WSM_ERROR_CONVERSION_FAILED;
	}
	else if (*req_type_atom == XT_CONVERT_FAIL)
	    fail_code = WSM_ERROR_TIMEOUT;
	else {
	    fprintf(stderr, "%s, request %s - reply %d:%s\n",
		"Target of the reply is not the same as the request",
		_WSMReqTypeToName(req_info->request_type),
		(int) *req_type_atom,
		_WSMReqTypeToName(_WSMTargetToReqType(dpy, *req_type_atom)));

	    fail_code = WSM_ERROR_INTERNAL;
	}
    }
    if (*format != WSM_PROTO_FMT) {
	fprintf(stderr, "%s, request %d - reply %d\n",
	       "Format of the reply is not the same as the request",
	       (int) WSM_PROTO_FMT, (int) *format);

	fail_code = WSM_ERROR_INTERNAL;
    }

    if (fail_code != WSM_SUCCESS) {
	/*
	 * Failure, call callback with NULL reply.
	 */

	(*req_info->reply_callback)(w, req_info->reply_data, NULL, fail_code);
    }
    else {
	screen_num = XScreenNumberOfScreen(XtScreen(w));
	
	_WSMUnpackReply(dpy, screen_num, value, *length,
			  req_info->request_type, &reply);
	
	(*req_info->reply_callback)(w, req_info->reply_data, &reply,fail_code);
	
	FreeReply(&reply);
    }

    XtFree((XtPointer) req_info_ptr);
}
