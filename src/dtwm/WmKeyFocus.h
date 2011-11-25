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
/*   $XConsortium: WmKeyFocus.h /main/4 1995/11/01 11:43:42 rswiston $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */


extern void AutoResetKeyFocus (ClientData *pcdNoFocus, Time focusTime);
extern void ClearFocusIndication (ClientData *pCD, Boolean refresh);
extern Boolean CheckForKeyFocus (ClientListEntry *pNextEntry, 
				 unsigned long type, Boolean focusNext, 
				 Time focusTime);
extern void DoExplicitSelectGrab (Window window);
extern ClientData *FindLastTransientTreeFocus (ClientData *pCD, 
					       ClientData *pcdNoFocus);
extern ClientData *FindNextTFocusInSeq (ClientData *pCD, 
					unsigned long startAt);
extern ClientData *FindPrevTFocusInSeq (ClientData *pCD, 
					unsigned long startAt);
extern Boolean FocusNextTransient (ClientData *pCD, unsigned long type, 
				   Boolean initiate, Time focusTime);
extern Boolean FocusNextWindow (unsigned long type, Time focusTime);
extern Boolean FocusPrevTransient (ClientData *pCD, unsigned long type, 
				   Boolean initiate, Time focusTime);
extern Boolean FocusPrevWindow (unsigned long type, Time focusTime);
extern ClientData *GetClientUnderPointer (Boolean *pSameScreen);
extern void InitKeyboardFocus (void);
extern void RepairFocus (void);
extern void ResetExplicitSelectHandling (ClientData *pCD);
extern void SetFocusIndication (ClientData *pCD);
extern void SetKeyboardFocus (ClientData *pCD, long focusFlags);



