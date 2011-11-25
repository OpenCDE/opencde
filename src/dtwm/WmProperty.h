/* 
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1989, 1990, 1991, 1992, 1993 Open Software Foundation, Inc. 
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
 * Motif Release 1.2.3
*/ 
/*   $XConsortium: WmProperty.h /main/4 1995/11/01 11:48:54 rswiston $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */

extern SizeHints * GetNormalHints (ClientData *pCD);
extern void ProcessWmProtocols (ClientData *pCD);
extern void ProcessMwmMessages (ClientData *pCD);
extern void SetMwmInfo (Window propWindow, long flags, Window wmWindow);
#ifdef WSM
void SetMwmSaveSessionInfo (Window wmWindow);
#endif /* WSM */
extern PropWMState * GetWMState (Window window);
extern void SetWMState (Window window, int state, Window icon);
extern PropMwmHints * GetMwmHints (ClientData *pCD);
extern PropMwmInfo * GetMwmInfo (Window rootWindowOfScreen);
extern void ProcessWmColormapWindows (ClientData *pCD);
extern Colormap FindColormap (ClientData *pCD, Window window);
extern MenuItem * GetMwmMenuItems (ClientData *pCD);
#ifdef WSM
extern void GetInitialPropertyList (ClientData *pCD);
extern Status GetWorkspaceHints (Display *display, Window window, Atom **ppWsAtoms, unsigned int *pCount, Boolean *pbAll);
#ifdef HP_VUE
extern void SetWorkspaceInfo (Window propWindow, WorkspaceInfo *pWsInfo, unsigned long cInfo);
#endif /* HP_VUE */
extern void SetWorkspacePresence (Window propWindow, Atom *pWsPresence, unsigned long cPresence);
extern Boolean HasProperty(ClientData *pCD, Atom property);
extern void DiscardInitialPropertyList (ClientData *pCD);
extern void GetInitialPropertyList (ClientData *pCD);
extern void SetWorkspaceListProperty (WmScreenData *pSD);
extern void SetCurrentWorkspaceProperty (WmScreenData *pSD);
extern void SetWorkspaceInfoProperty (WmWorkspaceData *pWS);
extern void DeleteWorkspaceInfoProperty (WmWorkspaceData *pWS);
extern char *WorkspacePropertyName (WmWorkspaceData *pWS);
#endif /* WSM */
