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
/*   $XConsortium: WmCDecor.h /main/4 1995/11/01 11:33:13 rswiston $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */

extern Boolean FrameWindow (ClientData *pcd);
extern void FrameExposureProc (ClientData *pcd);
extern void BaseWinExposureProc (ClientData *pcd);
extern void SetFrameShape (ClientData *pcd);
extern Boolean ConstructFrame (ClientData *pcd);
extern void GenerateFrameDisplayLists (ClientData *pcd);
extern void AdoptClient (ClientData *pcd);
extern void GetTextBox (ClientData *pcd, XRectangle *pBox);
extern void DrawWindowTitle (ClientData *pcd, Boolean eraseFirst);
extern void CreateStretcherWindows (ClientData *pcd);
extern void CountFrameRectangles (WmScreenData *pSD);
extern Boolean AllocateFrameDisplayLists (ClientData *pcd);
extern void InitClientDecoration (WmScreenData *pSD);
extern Boolean AllocateGadgetRectangles (ClientData *pcd);
extern void ComputeGadgetRectangles (ClientData *pcd);
extern void GetSystemMenuPosition (ClientData *pcd, int *px, int *py, unsigned int height, Context context);
extern void ShowActiveClientFrame (ClientData *pcd);
extern void ShowInactiveClientFrame (ClientData *pcd);
extern void RegenerateClientFrame (ClientData *pcd);
extern void BevelSystemButton (RList *prTop, RList *prBot, int x, int y, unsigned int width, unsigned int height);
extern void BevelMinimizeButton (RList *prTop, RList *prBot, int x, int y, unsigned int height);
extern void BevelMaximizeButton (RList *prTop, RList *prBot, int x, int y, unsigned int height);
extern Boolean DepressGadget (ClientData *pcd, int gadget, Boolean depressed);
extern void PushGadgetIn (ClientData *pcd, int gadget);
extern void PopGadgetOut (ClientData *pcd, int gadget);
