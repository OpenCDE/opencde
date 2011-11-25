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
/*   $XConsortium: WmWinConf.h /main/5 1996/06/11 16:01:31 rswiston $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */


extern void AdjustPos (int *pX, int *pY, unsigned int oWidth, 
		       unsigned int oHeight, unsigned int nWidth, 
		       unsigned int nHeight);
extern unsigned int ButtonStateBit (unsigned int button);
extern void CancelFrameConfig (ClientData *pcd);
extern void	CheckEatButtonRelease (ClientData *pcd, XEvent *pev);
extern Boolean CheckVisualPlace (ClientData *pCD, int tmpX, int tmpY);
extern void CompleteFrameConfig (ClientData *pcd, XEvent *pev);
extern Cursor ConfigCursor (int frame_part);
extern void DoFeedback (ClientData *pcd, int x, int y, unsigned int width, 
			unsigned int height, unsigned long newStyle, 
			Boolean resizing);
extern Boolean DoGrabs (Window grab_win, Cursor cursor, unsigned int pmask, 
			Time grabTime, ClientData *pCD, Boolean alwaysGrab);
extern void DrawOutline (int x, int y, unsigned int width, 
			 unsigned int height);
extern void	EatButtonRelease (unsigned int releaseButtons);
extern void FixFrameValues (ClientData *pcd, int *pfX, int *pfY, 
			    unsigned int *pfWidth, unsigned int *pfHeight, 
			    Boolean resizing);
extern void FlashOutline (int x, int y, unsigned int width, 
			  unsigned int height);
extern void ForceOnScreen (int screen, int *pX, int *pY);
extern void GetClipDimensions (ClientData *pCD, Boolean fromRoot);
extern void GetConfigEvent (Display *display, Window window, 
			    unsigned long mask, int curX, int curY, 
			    int oX, int oY, unsigned oWidth, 
			    unsigned oHeight, XEvent *pev);
extern Window GrabWin (ClientData *pcd, XEvent *pev);
extern void HandleClientFrameMove (ClientData *pcd, XEvent *pev);
extern void HandleClientFrameResize (ClientData *pcd, XEvent *pev);
extern Boolean HandleResizeKeyPress (ClientData *pcd, XEvent *pev);
extern void    MoveOpaque (ClientData *pcd, int x, int y,
		 unsigned int width, unsigned int height);
extern void MoveOutline (int x, int y, unsigned int width, 
			 unsigned int height);
extern void ProcessNewConfiguration (ClientData *pCD, int x, int y, 
				     unsigned int width, unsigned int height, 
				     Boolean clientRequest);
extern void ReGrabPointer (Window grab_win, Time grabTime);
#if ((!defined(WSM)) || defined(MWM_QATS_PROTOCOL))
extern void SetGrabServer (void);
#endif /* !defined(WSM) || defined(MWM_QATS_PROTOCOL) */
extern void SetOutline (XSegment *pOutline, int x, int y, unsigned int width, 
			unsigned int height, int fatness);
extern void SetPointerPosition (int newX, int newY, int *actualX, 
				int *actualY);
extern Boolean SetPointerResizePart (ClientData *pcd, XEvent *pev);
extern Boolean StartClientMove (ClientData *pcd, XEvent *pev);
extern void StartClientResize (ClientData *pcd, XEvent *pev);
extern Boolean StartResizeConfig (ClientData *pcd, XEvent *pev);
extern int ResizeType (ClientData *pcd, XEvent *pev);
extern void UndoGrabs (void);
#ifdef WSM
extern void HandleMarqueeSelect (WmScreenData *pSD, XEvent *pev);
extern void StartMarqueeSelect(WmScreenData *pSD, XEvent *pev);
extern void UpdateMarqueeSelectData (WmScreenData *pSD);
extern Boolean HandleMarqueeKeyPress (WmScreenData *pSD, XEvent *pev);
extern void WindowOutline (int x, int y, unsigned int width, 
			 unsigned int height);
#endif /* WSM */

