/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *
 */

#ifndef GAMIMP_H
#define GAMIMP_H

#include "../Core/SaveGameMgr.h"
#include "../Core/ActorMgr.h"

#define GAM_VER_GEMRB  0 
#define GAM_VER_BG  10   
#define GAM_VER_IWD 11  
#define GAM_VER_PST 12 
#define GAM_VER_BG2 20 
#define GAM_VER_TOB 21 
#define GAM_VER_IWD2 22

class GAMImp : public SaveGameMgr {
private:
	DataStream* str;
	bool autoFree;
	int version;
	unsigned int PCSize;
	ieDword PCOffset, PCCount;
	ieDword MazeOffset;
	ieDword NPCOffset, NPCCount;
	ieDword GlobalOffset, GlobalCount;
	ieDword JournalOffset, JournalCount;
	ieDword KillVarsOffset, KillVarsCount;
	ieDword FamiliarsOffset;
	ieDword BestiaryOffset;
	ieDword SavedLocOffset, SavedLocCount;

public:
	GAMImp(void);
	~GAMImp(void);
	bool Open(DataStream* stream, bool autoFree = true);
	Game* GetGame();

	int GetStoredFileSize(Game *game);
	/* stores a gane in the savegame folder */
	int PutGame(DataStream *stream, Game *game);
public:
	void release(void)
	{
		delete this;
	}
private:
	Actor* GetActor( ActorMgr* aM, bool is_in_party );
	PCStatsStruct* GetPCStats();
	GAMJournalEntry* GetJournalEntry();

	int PutHeader(DataStream *stream, Game *game);
	int PutActor(DataStream *stream, Actor *ac, ieDword CRESize, ieDword CREOffset, ieDword version);
	int PutPCs(DataStream *stream, Game *game);
	int PutNPCs(DataStream *stream, Game *game);
	int PutJournals(DataStream *stream, Game *game);
	int PutVariables( DataStream *stream, Game *game);
	int PutKillVars(DataStream *stream, Game *game);
	int PutMaze(DataStream *stream, Game *game);
	int PutFamiliars(DataStream *stream, Game *game);
};

#endif

