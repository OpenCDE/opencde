#ifndef _WM_MENU_H
#define _WM_MENU_H

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
 * Motif Release 1.2.2
*/ 
/*   $XConsortium: WmMenu.h /main/7 1996/11/20 15:20:45 rswiston $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */

#if ((!defined(WSM)) || defined(MWM_QATS_PROTOCOL))
# define MAKE_MENU(pSD, pCD, mName, iC, aC, moreItems, sysMenu) \
	MakeMenu(pSD, pCD, mName, iC, aC, moreItems, sysMenu)
# define CREATE_MENU_WIDGET(pSD, pCD, mName, parent, fTLP, tSpec, moreItems) \
	CreateMenuWidget(pSD, pCD, mName, parent, fTLP, tSpec, moreItems)
#else
# define MAKE_MENU(pSD, pCD, mName, iC, aC, moreItems, sysMenu) \
	MakeMenu(pSD, mName, iC, aC, moreItems, sysMenu)
# define CREATE_MENU_WIDGET(pSD, pCD, mName, parent, fTLP, tSpec, moreItems) \
	CreateMenuWidget(pSD, mName, parent, fTLP, tSpec, moreItems)
#endif /* !defined(WSM) || defined(MWM_QATS_PROTOCOL) */

extern void ActivateCallback (Widget w, caddr_t client_data, 
			      caddr_t call_data);
extern Widget CreateMenuWidget (WmScreenData *pSD,
#if ((!defined(WSM)) || defined(MWM_QATS_PROTOCOL))
				ClientData *pCD,
#endif /* !defined(WSM) || defined(MWM_QATS_PROTOCOL) */
				String menuName, Widget parent,
				Boolean fTopLevelPane, MenuSpec *topMenuSpec,
				MenuItem *moreMenuItems);
extern void FreeCustomMenuSpec (MenuSpec *menuSpec);
extern void MWarning (char *format, char *message);
extern MenuSpec *MakeMenu (WmScreenData *pSD,
#if ((!defined(WSM)) || defined(MWM_QATS_PROTOCOL))
			   ClientData *pCD,
#endif /* !defined(WSM) || defined(MWM_QATS_PROTOCOL) */
			   String menuName, 
			   Context initialContext, Context accelContext, 
			   MenuItem *moreMenuItems, Boolean fSystemMenu);
extern void PostMenu (MenuSpec *menuSpec, ClientData *pCD, int x, int y, 
		      unsigned int button, Context newContext, long flags, 
		      XEvent *passedInEvent);
extern void TraversalOff (MenuSpec *menuSpec);
extern void TraversalOn (MenuSpec *menuSpec);
extern void UnpostMenu (MenuSpec *menuSpec);

#if ((!defined(WSM)) || defined(MWM_QATS_PROTOCOL))
extern void InsertTreeOnAllClients (WmScreenData *pSD, CmdTree *tree,
				    Atom selection, Context active_context,
				    Boolean in_line);
extern void InsertTreeOnSingleClient (WmScreenData *pSD, ClientData *pCD,
				      CmdTree *tree, Atom selection,
				      Context active_context, Boolean in_line);
extern void InsertTreeOnRootMenu (WmScreenData *pSD, CmdTree *tree,
				  Atom selection, Boolean in_line);
extern void ModifyClientCommandTree (WmScreenData *pSD, ClientData *pCD,
				     OpRange range, CmdTree *tree,
				     CmdModifier modifier, Context context,
				     String newname);
extern void DestroyMenuSpecWidgets (MenuSpec *menuspec);
extern void DestroyMenuSpec (WmScreenData *pSD, CARD32 commandID);
#endif /* !defined(WSM) || defined(MWM_QATS_PROTOCOL) */

extern MenuSpec *DuplicateMenuSpec (MenuSpec *menuSpec);

#endif /* _WM_MENU_H */
