/*	File:		Application.h	Contains:	TApplication is an abstract base class, TBKApplication is a background only application class,  				TGUIApplication is a window-based user application class. TQTApplication is a QuickTime aware application  				class, TGXApplication is a Quickdraw GX aware application class. Finally TQTAndGXApplication  				handles both QX and QT application work. 		 		Application.h contains application level classes for building the wire for an application framework. 	Written by: 		Copyright:	Copyright � 1992-1999 by Apple Computer, Inc., All Rights Reserved.				You may incorporate this Apple sample source code into your program(s) without				restriction. This Apple sample source code has been provided "AS IS" and the				responsibility for its operation is yours. You are not permitted to redistribute				this Apple sample source code as "Apple sample source code" after having made				changes. If you're going to re-distribute the source, we require that you make				it clear in the source that the code was descended from Apple sample source				code, but that you've made changes.	Change History (most recent first):				8/18/1999	Karl Groethe	Updated for Metrowerks Codewarror Pro 2.1				*/// Declare label for this header file#ifndef _APPLICATION_#define _APPLICATION_#ifndef _DTSCPLUSLIBRARY_#include "DTSCPlusLibrary.h"#endif//	Toolbox Interfaces#ifndef __QUICKDRAW__#include <Quickdraw.h>#endif#ifndef __EVENTS__#include <Events.h>#endif#ifndef __OSEVENTS__#include <OSEvents.h>#endif#ifndef __MEMORY__#include <Memory.h>#endif#ifndef __WINDOWS__#include <Windows.h>#endif#ifndef __DESK__#include <Desk.h>#endif#ifndef __FONTS__#include <Fonts.h>#endif#ifndef __TOOLUTILS__#include <ToolUtils.h>#endif#ifndef __DIALOGS__#include <Dialogs.h>#endif#ifndef __MENUS__#include <Menus.h>#endif#ifndef __TEXTEDIT__#include <TextEdit.h>#endif#ifndef __APPLEEVENTS_#include <AppleEvents.h>#endif#ifndef __RESOURCES__#include <Resources.h>#endif#ifndef __DISKINIT__#include <DiskInit.h>#endif// DTS Library headers#ifndef _WINDOW_#include "Window.h"#endif#ifndef _APPLEEVENT_#include "AppleEvent.h"#endif#include "Menu.h"#include <AERegistry.h>#include "ApplicationResources.h"#include "CollectionClasses.h"// GLOBAL INTERNAL STRUCTURESstruct AEEventTable{												// AppleEvent record	OSType theClass;	OSType theID;	long theValue;};typedef AEEventTable* AEEventTablePtr;// _________________________________________________________________________________________________________ ////	TApplication Interface.class TApplication// The TApplication is the base class for Application classes. It contains the basic behavior// for any application work. Note that it's an abstract class.{public:	// TYPEDEFS AND ENUMS	enum EConstants	{		kForgroundSleepValue = 0, kSuspendResumeMessage = 1, kResumeMask = 1, kHighByte = 24, kBackgroundSleepValue = 60	};	enum EState	{		kInit = 1, kRun, kQuit	};	// CONSTRUCTORS AND DESTRUCTORS	TApplication();								// default constructor	virtual~ TApplication();					// default destructor	// MAIN INTERFACE	virtual void InitializeMemory();			// initialize our memory needs	virtual void InitializeToolbox() = 0;		// initialize the toolbox	// EVENT AND CONTROL METHODS	virtual void DoNextEvent();					// handle the incoming events	virtual void DoEventLoop(){};				// handle the actual event dispatching	virtual void DoHighLevelEvent();			// handle high level events	virtual void Start();						// start the application and let it run	virtual void DoIdle() = 0;					// call idle handler	virtual void Quit();						// quit the application 	virtual void DoCommand(long	 /*command*/){};// handle commands	// CORE AE HANDLER METHODS	virtual void InstallAEHandler();			// install our AE dispatcher	virtual void DispatchAppleEvents(AppleEvent* in,									 AppleEvent* out,									 long Command);// Dispatch incoming Apple Events in the framework	virtual OSErr HandleQuit(AppleEvent* in,							 AppleEvent* out,							 long refCon);		// handle the quit AE	virtual OSErr HandleOpen(AppleEvent* in,							 AppleEvent* out,							 long refCon);		// handle the open AE	virtual OSErr HandleOpenDocuments(AppleEvent* in,									  AppleEvent* out,									  long refCon);// handle the open document AE	virtual OSErr HandlePrint(AppleEvent* in,							  AppleEvent* out,							  long refCon);		// handle the print command	// STATE CHANGE METHODS	virtual void SetState(TApplication::EState theState);// change the state of the application FSM	// FIELDSprotected:	RgnHandle fSleepRegion;						// our sleep region (for possible mouse movements)	long fSleepValue;							// defined sleep value for WaitNextEvent	EventRecord fEventRecord;					// current event record	short fEventMask;							// our eventMask	short fMoreMasters;							// amount of MoreMaster calls	TAppleEvent fMessenger;						// our AE posting system	EState fState;								// internal state of the TApplication	OSErr fError;								// latest error};// _________________________________________________________________________________________________________ ////	TBKApplication Interface.class TBKApplication : public TApplication// The TBKApplication is the base class for background only/faceless applications. It provides// the basic skeleton for building such applications.{public:	// CONSTRUCTORS AND DESTRUCTORS	TBKApplication();	virtual~ TBKApplication();};// _________________________________________________________________________________________________________ ////	TGUIApplication Interface.class TGUIApplication : public TApplication// The TGUIApplication is the base class for writing window/menu based user interaction applications.{public:	// CONSTRUCTORS AND DESTRUCTORS	TGUIApplication();							// default constructor	virtual~ TGUIApplication();					// default destructor	// MAIN INTERFACE	// CONTROL	virtual void InitializeToolbox();			// initialize the toolbox	virtual void Start();						// handle the cursor before calling inherited Start	virtual void DoEventLoop();					// handle the actual event dispatching	// SYSTEM	virtual void DoIdle();						// handle idle time	virtual void DoSystemTime();				// handle DA time	virtual void DoDiskEvent();					// handle disk insertion events	virtual void DispatchAppleEvents(AppleEvent* in,									 AppleEvent* out,									 long command);	// GENERAL WINDOW EVENTS	virtual void DoWindowUpdate();				// handle window updating	virtual void DoDragWindow();				// handle inDrag events	virtual void DoGoAwayWindow();				// handle doGoAway events	virtual void DoInWindowContent();			// handle window mouse clicks	// MENU EVENTS	virtual void DoMenuCommand();				// handle menu command	virtual void DoInternalMenus(long command);	// handle internal menus (Apple)	virtual void DoCommand(long command);		// handle commands related to default GUI	virtual long CalculateMenuCommand(long menuentry);// calculate the menu command	// AE HANDLING	virtual OSErr HandleOpen(AppleEvent* in,							 AppleEvent* out,							 long refCon);		// OVERRIDE - handle the open AE	// DOCUMENT METHODS	virtual void DoCreateDocument();			// create our document (default one window)	virtual void DoCreateDocument(short windowID);// create our document from a resource (default one window)	virtual void AddDocument(TWindow* theDocument);// add the document to the list of known ones	// USER INTERACTIONS	virtual void Draw();						// draw in the main window	virtual void DoClick();						// handle a click inside a window	virtual void AdjustUserInterface(){};		// adjust the user interface based on state changes	virtual void DoAboutBox();					// present our About� box	virtual void DoHelp();						// a hook to a possible outside help system	// FIELDSprotected:	CursHandle fCursHandle;						// current cursor selected	TWindow* fDocument;							// our only window/document (create list of windows later)	WindowPtr fCurrentWindow;					// the current window attached to the event	short fWindowNum;							// amount of windows	long fMenuResult;							// value received from menu};// _________________________________________________________________________________________________________ ////	TQTApplication Interface.class TQTApplication : public TGUIApplication// The TQTApplication is the base class for writing window/menu based user interaction applications// that also handles QuickTime calls.{public:	// CONSTRUCTORS AND DESTRUCTORS	TQTApplication();	virtual~ TQTApplication();};// _________________________________________________________________________________________________________ ////	TGXApplication Interface.class TGXApplication : public TGUIApplication// The TGXApplication is the base class for writing window/menu based user interaction applications// that also handles Quickdraw GX calls.{public:	// CONSTRUCTORS AND DESTRUCTORS	TGXApplication();	virtual~ TGXApplication();};// _________________________________________________________________________________________________________ ////	TQTAndGXApplication Interface.class TQTAndGXApplication : public TGUIApplication// The TGXApplication is the base class for writing window/menu based user interaction applications// that handles both Quickdraw GX and QuickTime calls.{public:	// CONSTRUCTORS AND DESTRUCTORS	TQTAndGXApplication();	virtual~ TQTAndGXApplication();};#endif// _________________________________________________________________________________________________________ ///*	Change History (most recent last):  No		Init.	Date		Comment  1			khs		11/6/92		New file  2			khs		1/14/92		Cleanup*/