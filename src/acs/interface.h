// DR. ROBOTNIK'S RING RACERS
//-----------------------------------------------------------------------------
// Copyright (C) 2016 by James Haley, David Hill, et al. (Team Eternity)
// Copyright (C) 2022 by Sally "TehRealSalt" Cochenour
// Copyright (C) 2022 by Kart Krew
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  interface.h
/// \brief Action Code Script: Interface for the rest of SRB2's game logic

#ifndef __SRB2_ACS_INTERFACE_H__
#define __SRB2_ACS_INTERFACE_H__

#include "../doomtype.h"
#include "../doomdef.h"
#include "../doomstat.h"

/*--------------------------------------------------
	void ACS_Init(void);

		Initializes the ACS environment. Handles creating
		the VM, initializing its hooks, storing the
		pointer for future reference, and adding the
		shutdown function.
--------------------------------------------------*/

void ACS_Init(void);


/*--------------------------------------------------
	void ACS_Shutdown(void);

		Frees the ACS environment, for when the game
		is exited.
--------------------------------------------------*/

void ACS_Shutdown(void);


/*--------------------------------------------------
	void ACS_LoadLevelScripts(size_t mapID);

		Resets the ACS hub and map scopes to remove
		existing running scripts, and inserts the new
		level's ACS modules (BEHAVIOR lump) into
		the environment.

	Input Arguments:-
		mapID: The map's number to read the BEHAVIOR
			lump of.

	Return:-
		None
--------------------------------------------------*/

void ACS_LoadLevelScripts(size_t mapID);


/*--------------------------------------------------
	void ACS_RunPlayerEnterScript(player_t *player);

		Runs the map's special script for a player
		entering the game.

	Input Arguments:-
		player: The player to run the script for.

	Return:-
		None
--------------------------------------------------*/

void ACS_RunPlayerEnterScript(player_t *player);


/*--------------------------------------------------
	void ACS_RunLevelStartScripts(void);

		Runs the map's special scripts for opening
		the level, and for all players to enter
		the game.
--------------------------------------------------*/

void ACS_RunLevelStartScripts(void);


/*--------------------------------------------------
	void ACS_RunLapScript(mobj_t *mo, line_t *line);

		Runs the map's special script for a player
		crossing the finish line.

	Input Arguments:-
		player: The player to run the script for.
		line: The finish line's linedef.

	Return:-
		None
--------------------------------------------------*/

void ACS_RunLapScript(mobj_t *mo, line_t *line);


/*--------------------------------------------------
	void ACS_Tick(void);

		Executes all of the ACS environment's
		currently active threads.
--------------------------------------------------*/

void ACS_Tick(void);


/*--------------------------------------------------
	boolean ACS_Execute(const char *name, const INT32 *args, size_t numArgs, activator_t *activator);

		Runs an ACS script by its string name.
		Only one instance of the script will run at
		a time with this method.

	Input Arguments:-
		name: Script string to run.
		args: Array of the input arguments.
			Strings should be transformed into
			ACSVM string IDs.
		numArgs: Number of input arguments.
		activator: Container for information on what
			activated this script.

	Return:-
		true if we were able to run the script, otherwise false.
--------------------------------------------------*/

boolean ACS_Execute(const char *name, const INT32 *args, size_t numArgs, activator_t *activator);


/*--------------------------------------------------
	boolean ACS_ExecuteAlways(const char *name, const INT32 *args, size_t numArgs, activator_t *activator);

		Runs an ACS script by its string name.
		If the script is already running, this method
		will create another instance of the script.
		(Suspend and Terminate cannot be used, however.)

	Input Arguments:-
		name: Script string to run.
		args: Array of the input arguments.
			Strings should be transformed into
			ACSVM string IDs.
		numArgs: Number of input arguments.
		activator: Container for information on what
			activated this script.

	Return:-
		true if we were able to run the script, otherwise false.
--------------------------------------------------*/

boolean ACS_ExecuteAlways(const char *name, const INT32 *args, size_t numArgs, activator_t *activator);


/*--------------------------------------------------
	INT32 ACS_ExecuteResult(const char *name, const INT32 *args, size_t numArgs, activator_t *activator);

		Runs an ACS script by its string name.
		Will return the scripts special result
		value, if set.

	Input Arguments:-
		name: Script string to run.
		args: Array of the input arguments.
			Strings should be transformed into
			ACSVM string IDs.
		numArgs: Number of input arguments.
		activator: Container for information on what
			activated this script.

	Return:-
		true if we were able to run the script, otherwise false.
--------------------------------------------------*/

INT32 ACS_ExecuteResult(const char *name, const INT32 *args, size_t numArgs, activator_t *activator);


/*--------------------------------------------------
	boolean ACS_Suspend(const char *name);

		Pauses an ACS script by its string name.

	Input Arguments:-
		name: Script string to pause.

	Return:-
		true if we were able to pause the script, otherwise false.
--------------------------------------------------*/

boolean ACS_Suspend(const char *name);


/*--------------------------------------------------
	boolean ACS_Terminate(const char *name);

		Stops an ACS script by its string name.

	Input Arguments:-
		name: Script string to stop.

	Return:-
		true if we were able to stop the script, otherwise false.
--------------------------------------------------*/

boolean ACS_Terminate(const char *name);


/*--------------------------------------------------
	void ACS_Archive(savebuffer_t *save);

		Saves the ACS VM state into a save buffer.

	Input Arguments:-
		save: Pointer to the save buffer from P_SaveNetGame.

	Return:-
		None
--------------------------------------------------*/

void ACS_Archive(savebuffer_t *save);


/*--------------------------------------------------
	void ACS_UnArchive(savebuffer_t *save);

		Loads the ACS VM state from a save buffer.

	Input Arguments:-
		save: Pointer to the save buffer from P_LoadNetGame.

	Return:-
		None
--------------------------------------------------*/

void ACS_UnArchive(savebuffer_t *save);


#endif // __SRB2_ACS_INTERFACE_H__