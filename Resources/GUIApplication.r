/*	File:		GUIApplication.r	Contains:	Application is a simple application environment.  				GUIApplication contains the default window oriented application resources.  				Rez -rd -o TargetApplication GUIApplication.r -append	Written by: 		Copyright:	Copyright � 1992-1999 by Apple Computer, Inc., All Rights Reserved.				You may incorporate this Apple sample source code into your program(s) without				restriction. This Apple sample source code has been provided "AS IS" and the				responsibility for its operation is yours. You are not permitted to redistribute				this Apple sample source code as "Apple sample source code" after having made				changes. If you're going to re-distribute the source, we require that you make				it clear in the source that the code was descended from Apple sample source				code, but that you've made changes.	Change History (most recent first):				8/18/1999	Karl Groethe	Updated for Metrowerks Codewarror Pro 2.1				*/// INCLUDES#include "SysTypes.r"#include "Types.r"#include "ApplicationResources.h"// _________________________________________________________________________________________________________ //// MEMORY#define kPrefSize	314				// k of memory preferred#define kMinSize 	314				// k of memory minimally  // _________________________________________________________________________________________________________ //// MENU HANDLING (MBAR, MENU)// MBAR: If you have more menu entries, add these in after the default onesresource 'MBAR' (mAppMBAR, preload) {	{ mApple, mFile };};// MENU RESOURCESresource 'MENU' (mApple, preload) {	mApple, textMenuProc,	0b1111111111111111111111111111101,	/* disable dashed line, enable About and DAs */	enabled, apple,	{		"About Application�",			noicon, nokey, nomark, plain;		"-",			noicon, nokey, nomark, plain	}};resource 'MENU' (mFile, preload) {	mFile, textMenuProc,	0b0000000000000000000100000000000,	/* enable Quit only, program enables others */	enabled, "File",	{		"New",			noicon, "N", nomark, plain;		"Open",			noicon, "O", nomark, plain;		"-",			noicon, nokey, nomark, plain;		"Close",			noicon, "W", nomark, plain;		"Save",			noicon, "S", nomark, plain;		"Save As�",			noicon, nokey, nomark, plain;		"Revert",			noicon, nokey, nomark, plain;		"-",			noicon, nokey, nomark, plain;		"Page Setup�",			noicon, nokey, nomark, plain;		"Print�",			noicon, nokey, nomark, plain;		"-",			noicon, nokey, nomark, plain;		"Quit",			noicon, "Q", nomark, plain	}};// _________________________________________________________________________________________________________ //// APPLE EVENT SUPPORTresource 'aedt' (kCoreAEDispatchTable) {{			// Minimum for AppleEvent aware application	'aevt', 'ansr', cAppleEventReply;	'aevt', 'oapp', cNewCommand;	'aevt', 'odoc', cOpenCommand;	'aevt', 'quit', cQuitCommand;	'aevt', 'pdoc', cPrintCommand;	}};resource 'aedt' (kGUIAEDispatchTable) {{			// Basic GUI AE framework support	'aevt', 'abou', cAboutCommand;	}};// _________________________________________________________________________________________________________ //// USER INTERACTION MODULES (Alerts, Dialog boxes�)/* this ALRT and DITL are used as an ASSERT error screen */resource 'ALRT' (kUserAlert, purgeable) {	{40, 20, 189, 468},	100,	{	/* array: 4 elements */		/* [1] */		OK, visible, silent,		/* [2] */		OK, visible, silent,		/* [3] */		OK, visible, silent,		/* [4] */		OK, visible, silent	},	alertPositionMainScreen};resource 'DITL' (kUserAlert, purgeable) {	{	/* array DITLarray: 3 elements */		/* [1] */		{122, 360, 142, 440},		Button {			enabled,			"OK"		},		/* [2] */		{9, 48, 115, 439},		StaticText {			disabled,			"Error: ^0."		},		/* [3] */		{8, 8, 40, 40},		Icon {			disabled,			2		}	}};// _________________________________________________________________________________________________________ //// VERS RESOURCESresource 'vers' (1) {	0x01, 0x00, release, 0x00,	verUS,	"1.00",	"1.00, Copyright � 1993 Apple Computer, Inc."};// SIZE -----------------------------------------------------------------------------------/* here is the quintessential MultiFinder friendliness device, the SIZE resource */resource 'SIZE' (-1) {	dontSaveScreen,	acceptSuspendResumeEvents,	enableOptionSwitch,	canBackground,				// we can background; we don't currently, but our sleep value								// guarantees we don't hog the Mac while we are in the background	doesActivateOnFGSwitch,		// this says we do our own activate/deactivate; don't fake us out	backgroundAndForeground,	// this is definitely not a background-only application!	dontGetFrontClicks,			// change this is if you want "do first click" behavior like the Finder	ignoreAppDiedEvents,		// essentially, I'm not a debugger (sub-launching)	is32BitCompatible,			// this app works OK in 32-bit address space	isHighLevelEventAware,		// Apple Events support	localAndRemoteHLEvents,		// Apple Events support	reserved,	reserved,	reserved,	reserved,	reserved,	kPrefSize * 1024,	kMinSize * 1024	};// _________________________________________________________________________________________________________ ///*	Change History (most recent last):  No		Init.	Date		Comment  1			khs		11/15/92	New file  2			khs		1/14/93		Cleanup*/