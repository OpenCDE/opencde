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
/*   $XConsortium: WmIconBox.h /main/4 1995/11/01 11:42:06 rswiston $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */


#ifdef WSM
extern void AddIconBoxForWorkspace (WmWorkspaceData *pWS);
#endif /* WSM */
extern void AddNewBox (WmWorkspaceData *pWS, IconBoxData *pIBD);
extern void ChangeActiveIconboxIconText (Widget icon, caddr_t dummy, 
					 XFocusChangeEvent *event);
extern void CheckIconBoxResize (ClientData *pCD, unsigned int changedValues, 
				int newWidth, int newHeight);
extern Boolean CheckIconBoxSize (IconBoxData *pIBD);
extern void DeleteIconFromBox (IconBoxData *pIBD, ClientData *pCD);
extern void DeleteIconInfo (IconBoxData *pIBD, ClientData *pCD);
extern Boolean ExpandVirtualSpace (IconBoxData *pIBD, int newWidth, 
				   int newHeight);
extern Boolean ExtendIconList (IconBoxData *pIBD, int incr);
extern void FindNewPosition (Cardinal *newPosition, IconPlacementData *pIPD, 
			     int newPlace);
extern MenuItem *GetIconBoxMenuItems (WmScreenData *pSD);
extern void GetIconBoxIconRootXY (ClientData *pCD, int *pX, int *pY);
extern void HandleIconBoxButtonMotion (Widget icon, caddr_t client_data, 
				       XEvent *pev);
extern void HandleIconBoxIconKeyPress (Widget icon, caddr_t dummy, 
				       XKeyEvent *keyEvent);
#ifndef MOTIF_ONE_DOT_ONE
extern void IconScrollVisibleCallback (Widget w, caddr_t client_data, 
				  XmAnyCallbackStruct *call_data);
#endif
extern void IconActivateCallback (Widget w, caddr_t client_data, 
				  XmAnyCallbackStruct *call_data);
extern Boolean IconVisible (ClientData *pCD);
extern IconInfo *InsertIconInfo (IconBoxData *pIBD, ClientData *pCD, 
				 Widget theWidget);
extern Boolean InsertIconIntoBox (IconBoxData *pIBD, ClientData *pCD);
extern void InitIconBox (WmScreenData *pSD);
extern void InitializeClientData (ClientData *pCD, IconBoxData *pIBD);
extern void InitializeIconBoxData (WmWorkspaceData *pWS, IconBoxData *pIBD);
extern Cardinal InsertPosition (Widget w);
extern void MakeBulletinBoard (WmWorkspaceData *pWS, IconBoxData *pIBD);
extern void MakeFadeIconGC (WmScreenData *pSD);
extern Boolean MakeIconBox (WmWorkspaceData *pWS, ClientData *pCD);
extern void MakeScrolledWindow (WmWorkspaceData *pWS, IconBoxData *pIBD);
extern void MakeShell (WmWorkspaceData *pWS, IconBoxData *pIBD);
extern void MakeShrinkWrapIconsGC (WmScreenData *pSD, Pixmap bgPixmap);
extern void MapIconBoxes (WmWorkspaceData *pWS);
extern void PackIconBox (IconBoxData *pIBD, Boolean packVert, 
			 Boolean packHorz, int passedInWidth, 
			 int passedInHeight);
extern void RealignIconList (IconBoxData *pIBD, int newCols, int newRows);
extern void RealizeIconBox (WmWorkspaceData *pWS, IconBoxData *pIBD, 
			    ClientData *pCD);
extern void ReorderIconBoxIcons (ClientData *pCD, IconBoxData *pIBD, 
				 Widget theIcon, int newX, int newY);
extern void ResetArrowButtonIncrements (ClientData *pCD);
extern void ResetIconBoxMaxSize (ClientData *pCD, Widget bBoardWidget);
extern void SetGeometry (WmWorkspaceData *pWS, ClientData *pCD, 
			 IconBoxData *pIBD);
extern void SetGranularity (WmWorkspaceData *pWS, ClientData *pCD, 
			    IconBoxData *pIBD);
extern void SetIconBoxInfo (WmWorkspaceData *pWS, ClientData *pCD);
extern void SetNewBounds (IconBoxData *pIBD);
extern void ShowClientIconState (ClientData *pCD, int newState);
#ifdef WSM
extern void UnmapIconBoxes (WmWorkspaceData *pWS);
#endif /* WSM */
extern void UpdateIncrements (Widget sWidget, IconBoxData *pIBD, 
			      XConfigureEvent *event);
extern String WmXmStringToString (XmString xmString);

