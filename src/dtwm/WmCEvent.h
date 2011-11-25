/* 
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1989, 1990, 1991, 1992 Open Software Foundation, Inc. 
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF). See the file named COPYRIGHT.MOTIF for
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
*/ 
/* 
 * Motif Release 1.2
*/ 
/*   $XConsortium: WmCEvent.h /main/4 1995/11/01 11:34:01 rswiston $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */


extern void CheckButtonPressBuiltin (XButtonEvent *buttonEvent, 
				     Context context, Context subContext, 
				     int partContext, ClientData *pCD);
extern void CheckButtonReleaseBuiltin (XButtonEvent *buttonEvent, 
				       Context context, Context subContext, 
				       ClientData *pCD);
extern Window GetParentWindow (Window window);
extern WmScreenData *GetScreenForWindow (Window win);
extern Boolean HandleCButtonPress (ClientData *pCD, XButtonEvent *buttonEvent);
extern void HandleCButtonRelease (ClientData *pCD, XButtonEvent *buttonEvent);
extern void HandleCColormapNotify (ClientData *pCD, 
				   XColormapEvent *colorEvent);
extern void HandleCConfigureRequest (ClientData *pCD, 
				     XConfigureRequestEvent *configureRequest);
extern void HandleCEnterNotify (ClientData *pCD, 
				XEnterWindowEvent *enterEvent);
extern void HandleCLeaveNotify (ClientData *pCD, 
				XLeaveWindowEvent *leaveEvent);
extern Boolean HandleCFocusIn (ClientData *pCD, 
			       XFocusChangeEvent *focusChangeEvent);
extern Boolean HandleCFocusOut (ClientData *pCD, 
				XFocusChangeEvent *focusChangeEvent);
extern Boolean HandleCKeyPress (ClientData *pCD, XKeyEvent *keyEvent);
extern void HandleClientMessage (ClientData *pCD, 
				 XClientMessageEvent *clientEvent);
extern void HandleCMotionNotify (ClientData *pCD, XMotionEvent *motionEvent);
extern void HandleCPropertyNotify (ClientData *pCD, 
				   XPropertyEvent *propertyEvent);
#ifndef NO_SHAPE
extern void HandleCShapeNotify (ClientData *pCD,  XShapeEvent *shapeEvent);
#endif /* NO_SHAPE */
extern Boolean HandleEventsOnClientWindow (ClientData *pCD, XEvent *pEvent);
extern Boolean HandleEventsOnSpecialWindows (XEvent *pEvent);


extern void SetupCButtonBindings (Window window, ButtonSpec *buttonSpecs);
extern Boolean WmDispatchClientEvent (XEvent *event);
extern void HandleIconBoxButtonPress (ClientData *pCD, 
				      XButtonEvent *buttonEvent, 
				      Context subContext);
extern void HandleIconButtonPress (ClientData *pCD, XButtonEvent *buttonEvent);


extern void ProcessButtonGrabOnClient (ClientData *pCD, 
				       XButtonEvent *buttonEvent, 
				       Boolean replayEvent);
extern void DetermineActiveScreen (XEvent *pEvent);
extern Boolean WmDispatchClientEvent (XEvent *event);

#define SetActiveScreen(psd) (ACTIVE_PSD=(psd), wmGD.queryScreen=False)
