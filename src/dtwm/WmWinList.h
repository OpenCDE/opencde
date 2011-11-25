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
/*   $XConsortium: WmWinList.h /main/5 1996/05/17 12:54:05 rswiston $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */


extern void AddClientToList (WmWorkspaceData *pWS, ClientData *pCD, 
			     Boolean onTop);
extern void AddEntryToList (WmWorkspaceData *pWS, ClientListEntry *pEntry, 
			    Boolean onTop, ClientListEntry *pStackEntry);
extern void AddTransient (WmWorkspaceData *pWS, ClientData *pCD);
#ifdef WSM
extern Boolean BumpPrimaryToBottom (ClientData *pcdLeader);
extern Boolean BumpPrimaryToTop (ClientData *pcdLeader);
#endif /* WSM */
extern Boolean CheckIfClientObscuredByAny (ClientData *pcd);
extern Boolean CheckIfClientObscuring (ClientData *pcdTop, ClientData *pcd);
extern Boolean CheckIfClientObscuringAny (ClientData *pcd);
extern Boolean CheckIfObscuring (ClientData *pcdA, ClientData *pcdB);
extern int CountTransientChildren (ClientData *pcd);
extern void DeleteClientFromList (WmWorkspaceData *pWS, ClientData *pCD);
extern void DeleteEntryFromList (WmWorkspaceData *pWS, 
				 ClientListEntry *pListEntry);
extern void DeleteFullAppModalChildren (ClientData *pcdLeader, 
					ClientData *pCD);
extern void DeleteTransient (ClientData *pCD);
extern ClientListEntry *FindClientNameMatch (ClientListEntry *pEntry, 
					     Boolean toNext, 
					     String clientName,
					     unsigned long types);
#ifdef WSM
extern ClientData *FindSubLeaderToTop (ClientData *pcd);
#endif /* WSM */
extern ClientData *FindTransientFocus (ClientData *pcd);
extern ClientData *FindTransientOnTop (ClientData *pcd);
extern ClientData *FindTransientTreeLeader (ClientData *pcd);
extern void FixupFullAppModalCounts (ClientData *pcdLeader, 
				     ClientData *pcdDelete);
#ifdef WSM
extern Boolean LeaderOnTop (ClientData *pcdLeader);
extern Window LowestWindowInTransientFamily (ClientData *pcdLeader);
extern void MakeTransientFamilyStackingList (Window *windows, 
					    ClientData *pcdLeader);
#endif /* WSM */
extern Window *MakeTransientWindowList (Window *windows, ClientData *pcd);
extern void MarkModalSubtree (ClientData *pcdTree, ClientData *pcdAvoid);
extern void MarkModalTransient (ClientData *pcdLeader, ClientData *pCD);
extern void MoveEntryInList (WmWorkspaceData *pWS, ClientListEntry *pEntry, 
			     Boolean onTop, ClientListEntry *pStackEntry);
#ifdef WSM
extern Boolean NormalizeTransientTreeStacking (ClientData *pcdLeader);
#endif /* WSM */
extern Boolean PutTransientBelowSiblings (ClientData *pcd);
extern Boolean PutTransientOnTop (ClientData *pcd);
extern void RestackTransients (ClientData *pcd);
extern void RestackTransientsAtWindow (ClientData *pcd);
extern void SetupSystemModalState (ClientData *pCD);
extern void StackTransientWindow (ClientData *pcd);
extern void StackWindow (WmWorkspaceData *pWS, ClientListEntry *pEntry, 
			 Boolean onTop, ClientListEntry *pStackEntry);
extern void UnMarkModalTransient (ClientData *pcdModee, int modalCount, 
				  ClientData *pcdModal);
extern void UndoSystemModalState (void);

