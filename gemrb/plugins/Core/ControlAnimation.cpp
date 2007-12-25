/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Id$
 *
 */

#include "../../includes/win32def.h"
#include "ControlAnimation.h"
#include "Interface.h"
#include "ResourceMgr.h"
#include "Button.h"


ControlAnimation::ControlAnimation(Control* ctl, const ieResRef ResRef, int Cycle)
{
	control = NULL;
	bam = NULL;
	cycle = Cycle;
	frame = 0;
	anim_phase = 0;

	bam = ( AnimationFactory* )
		core->GetResourceMgr()->GetFactoryResource( ResRef,
													IE_BAM_CLASS_ID,
													IE_NORMAL );
	if (! bam)
		return;

	control = ctl;
	control->animation = this;
}

//freeing the bitmaps only once, but using an intelligent algorithm
ControlAnimation::~ControlAnimation(void)
{
	//removing from timer first
	core->timer->RemoveAnimation( this );

	bam = NULL;
}

bool ControlAnimation::SameResource(const ieResRef ResRef, int Cycle)
{
	if (!control ) return false;
	if (!bam) return false;
	if (memcmp(ResRef, bam->ResRef, sizeof(ieResRef) )) return false;
	int c = cycle;
	if (control->Flags&IE_GUI_BUTTON_PLAYRANDOM) {
		c&=~1;
	}
	if (Cycle!=c) return false;
	return true;
}

void ControlAnimation::UpdateAnimation(void)
{
	unsigned long time;
	int Cycle = cycle;

	if (control->Flags & IE_GUI_BUTTON_PLAYRANDOM) {
		// simple Finite-State Machine
		if (anim_phase == 0) {
			frame = 0;
			anim_phase = 1;
			time = 500 + 500 * (rand() % 20);
			cycle&=~1;
			Cycle=cycle;
		} else if (anim_phase == 1) {
			if (rand() % 30 == 0) {
				cycle|=1;
				Cycle=cycle;
			}
			anim_phase = 2;
			time = 100;
		} else {
			frame++;
			time = 100;
		}
	} else {
		frame ++;
		time = 15;
	}

	Sprite2D* pic = bam->GetFrame( (unsigned short) frame, (unsigned char) Cycle );

	if (pic == NULL) {
		//stopping at end frame
		if (control->Flags & IE_GUI_BUTTON_PLAYONCE) {
			core->timer->RemoveAnimation( this );
			return;
		}
		anim_phase = 0;
		frame = 0;
		pic = bam->GetFrame( 0, 0 );
	}

	control->SetAnimPicture( pic );
	core->timer->AddAnimation( this, time );
}
