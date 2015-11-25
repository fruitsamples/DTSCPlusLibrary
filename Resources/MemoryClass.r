/*	File:		MemoryClass.r	Contains:	TMemory is a simple object checks heap and stack values, as well as changes them.  				TMemoryClass.r contains the resource definitions and resources used byt TMemory and TMemory testing.   				Add these resources to the test framework using something similar as:  				Rez -rd -o TargetApplication MemoryClass.r -append	Written by: Kent Sandvik		Copyright:	Copyright � 1993-1999 by Apple Computer, Inc., All Rights Reserved.				You may incorporate this Apple sample source code into your program(s) without				restriction. This Apple sample source code has been provided "AS IS" and the				responsibility for its operation is yours. You are not permitted to redistribute				this Apple sample source code as "Apple sample source code" after having made				changes. If you're going to re-distribute the source, we require that you make				it clear in the source that the code was descended from Apple sample source				code, but that you've made changes.	Change History (most recent first):				8/18/1999	Karl Groethe	Updated for Metrowerks Codewarror Pro 2.1				*/// INCLUDES#include "SysTypes.r"#include "Types.r"#include "ApplicationResources.h"#define kBaseID 1// This is our 'stak' resource definition.type 'stak' {		longint;						// stack size};resource 'stak' (kBaseID, purgeable) {	16 * 1024		// Base stack size. TMemory sums this entry for all 'stak' resources to                    // determine what it should set the stack limit to at application                    // startup.};// _________________________________________________________________________________________________________ ///*	Change History (most recent last):  No		Init.	Date		Comment  1			khs		1/2/93		New file  2			khs		1/3/93		Cleanup*/