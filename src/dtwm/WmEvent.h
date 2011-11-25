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
/*   $XConsortium: WmEvent.h /main/5 1996/06/11 15:59:25 rswiston $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */

#ifdef WSM
/* Shared Variables */
extern int smAckState;

#endif /* WSM */

extern Boolean CheckForButtonAction (XButtonEvent *buttonEvent, 
				     Context context, Context subContext, 
				     ClientData *pCD);
extern Time GetTimestamp (void);
#if ((!defined(WSM)) || defined(MWM_QATS_PROTOCOL))
extern Time LastTime (void);
#endif /* !defined(WSM) || defined(MWM_QATS_PROTOCOL) */
extern Boolean HandleKeyPress (XKeyEvent *keyEvent, KeySpec *keySpecs, 
			       Boolean checkContext, Context context, 
			       Boolean onlyFirst, ClientData *pCD);
extern void HandleWsButtonPress (XButtonEvent *buttonEvent);
extern void HandleWsButtonRelease (XButtonEvent *buttonEvent);
extern void HandleWsConfigureRequest (XConfigureRequestEvent *configureEvent);
extern void HandleWsEnterNotify (XEnterWindowEvent *enterEvent);
extern void HandleWsFocusIn (XFocusInEvent *focusEvent);
extern Boolean HandleWsKeyPress (XKeyEvent *keyEvent);
extern void HandleWsLeaveNotify (XLeaveWindowEvent *leaveEvent);
extern void IdentifyEventContext (XButtonEvent *event, ClientData *pCD, 
				  Context *pContext, int *pPartContext);
extern void InitEventHandling (void);
extern void ProcessClickBPress (XButtonEvent *buttonEvent, ClientData *pCD, 
				Context context, Context subContext);
extern void ProcessClickBRelease (XButtonEvent *buttonEvent, ClientData *pCD, 
				  Context context, Context subContext);
extern void PullExposureEvents (void);
extern int SetupKeyBindings (KeySpec *keySpecs, Window grabWindow, 
			     int keyboardMode, long context);
extern Boolean WmDispatchMenuEvent (XButtonEvent *event);
extern Boolean WmDispatchWsEvent (XEvent *event);
extern void WmGrabButton (Display *display, unsigned int button, 
		unsigned int modifiers, Window grab_window, 
		unsigned int event_mask, Bool owner_events, int pointer_mode, 
		int keyboard_mode, Window confine_to, Cursor cursor);
extern void WmGrabKey (Display *display, int keycode, unsigned int modifiers, 
		Window grab_window, Bool owner_events, int pointer_mode, 
		int keyboard_mode);
extern void WmUngrabButton (Display *display, unsigned int button,
		unsigned int modifiers, Window grab_window);
#ifdef WSM
extern void HandleDtWmClientMessage (XClientMessageEvent *clientEvent);
extern void HandleDtWmRequest (WmScreenData *pSD, XEvent *pev);
extern Boolean ReplayedButtonEvent (XButtonEvent *pevB1, XButtonEvent *pevB2);
#endif /* WSM */
