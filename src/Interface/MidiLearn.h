/*
    MidiLearn.h

    Copyright 2016 Will Godfrey

    This file is part of yoshimi, which is free software: you can redistribute
    it and/or modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either version 2 of
    the License, or (at your option) any later version.

    yoshimi is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.   See the GNU General Public License (version 2 or
    later) for more details.

    You should have received a copy of the GNU General Public License along with
    yoshimi; if not, write to the Free Software Foundation, Inc., 51 Franklin
    Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/

#ifndef MIDILEARN_H
#define MIDILEARN_H

#include <jack/ringbuffer.h>
#include <list>
#include <string>

using namespace std;

#include "Misc/MiscFuncs.h"
#include "Interface/InterChange.h"

class SynthEngine;

class MidiLearn : private MiscFuncs
{
    public:
        MidiLearn(SynthEngine *_synth);
        ~MidiLearn();

        CommandBlock commandData;
        size_t commandSize = sizeof(commandData);

        struct Control{
            unsigned char type;
            unsigned char control;
            unsigned char part;
            unsigned char kit;
            unsigned char engine;
            unsigned char insert;
            unsigned char parameter;
            unsigned char par2;
        } data;

        struct LearnBlock{
            unsigned char CC;
            unsigned char chan;
            unsigned char min_in;
            unsigned char max_in;
            unsigned char status; // up to here must be specified on input
            int min_out; // defined programaticly
            int max_out; // defined programaticly
            Control data; // controller to learn
            string name; // optional derived from controller text?
        };
        bool learning;
        string learnedName;

        void setTransferBlock(CommandBlock *getData, string name);

        bool runMidiLearn(float value, unsigned char CC, unsigned char chan, bool in_place);
        int findEntry(list<LearnBlock> &midi_list, int lastpos, unsigned char CC, unsigned char chan, LearnBlock *block, bool show);
        void listAll(void);
        bool remove(int itemNumber);
        void changeLine(int value, unsigned char type, unsigned char control, unsigned char part, unsigned char kit, unsigned char engine, unsigned char insert, unsigned char parameter, unsigned char par2);

    private:
        list<LearnBlock> midi_list;
        Control learnTransferBlock;

        void insert(unsigned char CC, unsigned char chan);
        SynthEngine *synth;
        void updateGui(void);
};

#endif
