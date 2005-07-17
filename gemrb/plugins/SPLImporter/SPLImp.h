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
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/SPLImporter/SPLImp.h,v 1.7 2005/07/17 18:58:27 avenger_teambg Exp $
 *
 */

#ifndef SPLIMP_H
#define SPLIMP_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../../includes/ie_types.h"
#include "../Core/Spell.h"
#include "../Core/SpellMgr.h"


class SPLImp : public SpellMgr {
private:
	DataStream* str;
	bool autoFree;
	int version;

public:
	SPLImp(void);
	~SPLImp(void);
	bool Open(DataStream* stream, bool autoFree = true);
	Spell* GetSpell(Spell *spl);
	void release(void)
	{
		delete this;
	}
private:
	void GetExtHeader(Spell *s, SPLExtHeader* eh);
	void GetFeature(Spell *s, Effect *f);
};


#endif
