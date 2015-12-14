/*
  ZynAddSubFX - a software synthesizer

  WavFile.h - Records sound to a file
  Copyright (C) 2008 Nasca Octavian Paul
  Author: Nasca Octavian Paul
          Mark McCurry

  This program is free software; you can redistribute it and/or modify
  it under the terms of either version 2 of the License, or (at your option)
  any later version, as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License (version 2 or later) for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#ifndef CMDINTERFACE_H
#define CMDINTERFACE_H
#include <string>
#include <Misc/MiscFuncs.h>
#include <Misc/SynthEngine.h>

extern map<SynthEngine *, MusicClient *> synthInstances;

typedef enum { all_fx = 0, ins_fx, part_lev, } level_bits;

typedef enum { ok_msg = 0, value_msg, operation_msg, what_msg, range_msg, unrecognised_msg, level_msg, } error_messages;

class SynthEngine;

class CmdInterface : private MiscFuncs
{
    public:
        void defaults();
        void cmdIfaceCommandLoop();
        
    private:
        bool helpList(char *point, string *commands, SynthEngine *synth);
        int commandVector(char *point, SynthEngine *synth);
        int commandPart(char *point, SynthEngine *synth, bool justSet);
        int commandSet(char *point, SynthEngine *synth);
        bool cmdIfaceProcessCommand(char *buffer);
    
        char welcomeBuffer [128];
};
#endif