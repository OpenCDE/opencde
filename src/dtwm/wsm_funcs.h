/* $XConsortium: wsm_funcs.h /main/5 1995/07/15 20:39:08 drk $ */
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

#ifndef _WSM_FUNCS_
#define _WSM_FUNCS_

/************************************************************
 *
 *  All function Prototypes for non static functions.
 *
 * Those that begin with _WSM are "private" for whatever that
 * is worth...
 *
 ************************************************************/

/*
 * disp.c
 */

WSMDispInfo * _WSMGetDispInfo(
Display *
);

WSMScreenInfo * _WSMGetScreenInfo(
Display *, int
);


void _WSMClearConfigScreenInfo(
Display *, int
);

WSMConfigFormatData * _WSMGetConfigFormat(
Display *, int, WSMConfigFormatType
);

Atom _WSMGetSelectionAtom(
Display *, int, WSMClientType
);

/*
 * free.c
 */

void FreeRequest(
WSMRequest *request
);

void FreeReply(
WSMReply *reply
);

/*
 * pack.c
 */

MessageData _WSMPackRequest(
Display *, int, WSMRequest *, unsigned long *, WSMErrorCode *
);

MessageData _WSMPackReply(
Display *, int, WSMReply *, unsigned long *
);

void _WSMUnpackRequest(
Display *, int, MessageData, unsigned long, WSMRequestType, WSMRequest *
);

void _WSMUnpackReply(
Display *, int, MessageData, unsigned long, WSMRequestType, WSMReply *
);

MessageData PackString(
MessageData, String
);

String UnpackString(
MessageData *
);

MessageData PackCARD8(
MessageData, CARD8
);

CARD8 UnpackCARD8(
MessageData *
);

MessageData PackCARD16(
MessageData, CARD16
);

CARD16 UnpackCARD16(
MessageData *
);

MessageData PackCARD32(
MessageData, CARD32
);

CARD32 UnpackCARD32(
MessageData *
);

/*
 * recv.c
 */

Boolean WSMDefaultOwnSelection(
Widget, WSMClientType, WSMRequestCallbackFunc, XtPointer
);

void WSMRegisterRequestCallback(
Display *, int, WSMRequestCallbackFunc, XtPointer
);

Boolean WSMIsKnownTarget(
Widget, Atom
);

Atom * GetTargetList(
Widget, Boolean, unsigned long *
);

Boolean WSMProcessProtoTarget(
Widget, Atom, XtPointer, unsigned long, 
int, Atom *, XtPointer *, unsigned long *, int *
);

/*
 * send.c
 */

Boolean WSMSendMessage(
Widget, WSMClientType, WSMRequest *, WSMReplyCallbackFunc, XtPointer
);

/*
 * utils.c
 */

String _WSMReqTypeToName(
WSMRequestType
);

WSMRequestType _WSMTargetToReqType(
Display *, Atom
);

Atom _WSMReqTypeToTarget(
Display *, WSMRequestType
);

Boolean _WSMRequiresConfigFormat(
WSMRequestType
);

WSMConfigFormatType _WSMGetConfigFormatType(
Window
);

WSMAttribute * _WSMGetMatchingAttr(
XrmQuark, WSMConfigFormatData *
);

WSMWinData * _WSMGetMatchingWinData(
WSMWinData *, int, XrmQuark
);

#endif /* DO NOT ADD ANYTHING AFTER THIS LINE */
