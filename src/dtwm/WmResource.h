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
/*   $TOG: WmResource.h /main/6 1997/04/14 12:52:19 dbl $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */

#ifndef NO_MESSAGE_CATALOG
extern void InitBuiltinSystemMenu(void);
#endif
extern void GetAppearanceGCs (WmScreenData *pSD, Pixel fg, Pixel bg, XFontStruct *font, Pixmap bg_pixmap, Pixel ts_color, Pixmap ts_pixmap, Pixel bs_color, Pixmap bs_pixmap, GC *pGC, GC *ptsGC, GC *pbsGC);
extern GC   GetHighlightGC (WmScreenData *pSD, Pixel fg, Pixel bg, Pixmap pixmap);
extern void MakeAppearanceResources (WmScreenData *pSD, AppearanceData *pAData, Boolean makeActiveResources);
#ifdef WSM
extern Boolean Monochrome (Screen *screen);
extern void ProcessWmColors (WmScreenData *pSD);
#endif /* WSM */
extern void ProcessWmResources (void);
extern void SetStdGlobalResourceValues (void);
extern void ProcessScreenListResource (void);
extern void ProcessAppearanceResources (WmScreenData *pSD);
extern void ProcessGlobalScreenResources (void);
extern void ProcessScreenResources (WmScreenData *pSD, unsigned char *screenName);
#ifdef WSM
extern void ProcessWorkspaceList (WmScreenData *pSD);
#endif /* WSM */
extern void ProcessWorkspaceResources (WmWorkspaceData *pWS);
extern void ProcessClientResources (ClientData *pCD);
extern void SetStdClientResourceValues (ClientData *pCD);
extern void SetStdScreenResourceValues (WmScreenData *pSD);
extern char *WmRealloc (char *ptr, unsigned size);
extern char *WmMalloc (char *ptr, unsigned size);
extern void SetupDefaultResources (WmScreenData *pSD);
extern Boolean SimilarAppearanceData (AppearanceData *pAD1, AppearanceData *pAD2);
#ifdef WSM
extern String ResCat (String s1, String s2, String s3, String s4);
void CheckForNoDither (AppearanceData *pAD);
#endif /* WSM */

#ifndef NO_MESSAGE_CATALOG
extern char *builtinSystemMenu;
#else
extern char builtinSystemMenu[];
#endif
extern char builtinKeyBindings[];
extern char builtinRootMenu[];
extern char builtinSystemMenuName[];

#ifndef WSM
#define Monochrome(screen) ( DefaultDepthOfScreen(screen) == 1 )
#endif /* not WSM */
