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
/*   $XConsortium: WmResParse.h /main/5 1996/06/11 16:00:58 rswiston $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */

#include <stdio.h>


#ifdef PANELIST
extern void            ProcessWmFile (WmScreenData *pSD, Boolean bNested);
#else /* PANELIST */
extern void ProcessWmFile (WmScreenData *pSD);
#endif /* PANELIST */
extern void ProcessCommandLine (int argc,  char *argv[]);
extern void ProcessMotifBindings (void);
#ifdef WSM
extern Boolean         FindDtSessionMatch(int commandArgc, 
					   char **commandArgv, 
					   ClientData *pCD, 
					   WmScreenData *pSD, 
					   char **pWorkSpaceList,
					   char *clientMachine);
extern void            WmDtGetHelprgs(char *args, 
				       unsigned char** volume, 
				       unsigned char** topic, 
				       int *argsCount);
extern void GetActionIndex (int tableSize, int *actionIndex);
extern void            GetFunctionTableValues (int *execIndex, int *nopIndex,
		    int *actionIndex);
extern void GetNopIndex (int tableSize, int *nopIndex);
extern void GetExecIndex (int tableSize, int *execIndex);
extern Boolean GetSessionHintsInfo (WmScreenData *pSD, long numItems);
#endif /* WSM */
extern FILE          * FopenConfigFile (void);
extern void            FreeMenuItem (MenuItem *menuItem);
#ifndef WSM
extern unsigned char * GetNextLine (void);
#endif /* not WSM */
#ifdef WSM
extern unsigned char * GetStringC (unsigned char **linePP, Boolean SmBehavior);
extern void SystemCmd (char *pchCmd);
#else /* WSM */
extern unsigned char * GetString (unsigned char **linePP);
#endif /* WSM */
extern Boolean ParseBtnEvent (unsigned char  **linePP,
                              unsigned int *eventType,
                              unsigned int *button,
                              unsigned int *state,
                              Boolean      *fClick);

extern void            ParseButtonStr (WmScreenData *pSD, unsigned char *buttonStr);
extern void            ParseKeyStr (WmScreenData *pSD, unsigned char *keyStr);
extern Boolean ParseKeyEvent (unsigned char **linePP, unsigned int *eventType,
		       KeyCode *keyCode,  unsigned int *state);
extern MenuItem      * ParseMwmMenuStr (WmScreenData *pSD, unsigned char *menuStr);
#ifdef WSM
extern void ParseSessionClientState (WmScreenData *pSD, int count,
			      unsigned char *string);
extern void ParseSessionCommand (WmScreenData *pSD,  int count,
			  unsigned char **commandString);
extern void ParseSessionGeometry (WmScreenData *pSD, int count,
			   unsigned char *string);
extern void ParseSessionItems (WmScreenData *pSD);
extern void ParseSessionWorkspaces (WmScreenData *pSD,  int count,
			     unsigned char *string);
extern void ParseSessionHost (WmScreenData *pSD,  int count,
			     unsigned char *string);
extern void ParseDtSessionHints (WmScreenData *pSD, unsigned char *property);
#endif /* WSM */
extern int             ParseWmFunction (unsigned char **linePP, unsigned int res_spec, WmFunction *pWmFunction);
extern void            PWarning (char *message);
extern void            SaveMenuAccelerators (WmScreenData *pSD, MenuSpec *newMenuSpec);
extern void      ScanAlphanumeric (unsigned char **linePP);
#ifndef WSM
extern void            ScanWhitespace(unsigned char  **linePP);
#endif /* not WSM */
extern void            ToLower (unsigned char  *string);
extern void		SyncModifierStrings(void);
#ifdef PANELIST
extern void DeleteTempConfigFileIfAny (void);
extern Boolean ParseWmFunctionArg (
		unsigned char **linePP,
		int ix, 
		WmFunction wmFunc, 
		void **ppArg,
		String sClientName,
		String sTitle);
extern Boolean ParseWmFuncMaybeStrArg (unsigned char **linePP, 
				       WmFunction wmFunction, String *pArgs);
extern Boolean ParseWmFuncStrArg (unsigned char **linePP, 
				       WmFunction wmFunction, String *pArgs);
extern Boolean ParseWmFuncActionArg (unsigned char **linePP, 
				  WmFunction wmFunction, String *pArgs);
#endif /* PANELIST */
#ifdef WSM
#define ToLower(s)		(_DtWmParseToLower (s))
#define GetNextLine()		(_DtWmParseNextLine (wmGD.pWmPB))
#define GetSmartSMString(s)	(_DtWmParseNextTokenC (s, True))
#define GetSmartString(s)	(_DtWmParseNextTokenC (s, False))
#define GetString(s)		(_DtWmParseNextTokenC (s, False))
#define ScanWhitespace(s)	(_DtWmParseSkipWhitespaceC (s))
#endif /* WSM */

#if ((!defined(WSM)) || defined(MWM_QATS_PROTOCOL))
extern Boolean IsClientCommand (String);
extern Boolean SetGreyedContextAndMgtMask (MenuItem *menuItem,
					   WmFunction wmFunction);
#endif /* !defined(WSM) || defined(MWM_QATS_PROTOCOL) */
