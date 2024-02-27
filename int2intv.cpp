
/**
 * Intellivision rom file converter for the NT Mini Noir intellivision rom format
 * Copyright (c) 2020 Robert Mendon (https://github.com/dot-bob)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <unistd.h>
using namespace std;

#define MAXBUFFER 256

// header details
//unsigned int MapAddress[5] = {0,0,0,0,0};
//unsigned int DataSize[5] = {0,0,0,0,0};
unsigned int MapAddress[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned int DataSize[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void PrintHelp(void)
{
	cout	<< "\nNT Mini Noir intellivision rom formater v1.2\nCommand Use:  int2intv -m X <input file> <output file>\n"
		<< "\nSwitches:\n-m X, where X = rom memory map to encode\n";

	exit(1);
}

void PopulateHeader(int Format)
{
    switch(Format)
    {
        case 0:
        MapAddress[0] = 0x5000;
        DataSize[0] = 0x2000;

        MapAddress[1] = 0xD000;
        DataSize[1] = 0x1000;

        MapAddress[2] = 0xF000;
        DataSize[2] = 0x1000;
        break;

        case 1:
        MapAddress[0] = 0x5000;
        DataSize[0] = 0x2000;

        MapAddress[1] = 0xD000;
        DataSize[1] = 0x2FFF;
        break;

        case 2:
        MapAddress[0] = 0x5000;
        DataSize[0] = 0x2000;

        MapAddress[1] = 0x9000;
        DataSize[1] = 0x2FFF;

        MapAddress[2] = 0xD000;
        DataSize[2] = 0x1000;
        break;

        case 3:
        case 9:
        MapAddress[0] = 0x5000;
        DataSize[0] = 0x2000;

        MapAddress[1] = 0x9000;
        DataSize[1] = 0x2000;

        MapAddress[2] = 0xD000;
        DataSize[2] = 0x1000;

        MapAddress[3] = 0xF000;
        DataSize[3] = 0x1000;
        break;

        case 4:
        MapAddress[0] = 0x5000;
        DataSize[0] = 0x2000;
        break;

        case 5:
        MapAddress[0] = 0x5000;
        DataSize[0] = 0x2FFF;

        MapAddress[1] = 0x9000;
        DataSize[1] = 0x2FFF;
        break;

        case 6:
        MapAddress[0] = 0x6000;
        DataSize[0] = 0x2000;
        break;

        case 7:
        MapAddress[0] = 0x4800;
        DataSize[0] = 0x2000;
        break;

        case 8:
        MapAddress[0] = 0x5000;
        DataSize[0] = 0x1000;

        MapAddress[1] = 0x7000;
        DataSize[1] = 0x1000;
        break;

	// 2048
	case 10:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1F00;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x0B00;
    break;

	// A Sparrow Goes Flapping
	case 11:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x0C00;

    MapAddress[1] = 0xA000;
    DataSize[1] = 0x1500;

    MapAddress[2] = 0xC100;
    DataSize[2] = 0x1600;
    break;

	// Aardvark (Free)
	case 12:
	MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1E00;

    MapAddress[2] = 0xA000;
    DataSize[2] = 0x0F00;

    MapAddress[3] = 0xD000;
    DataSize[3] = 0x0700;

	MapAddress[4] = 0xF000;
    DataSize[4] = 0x0F00;
	break;

	// Alligator Swamp / IntyLander 
	case 13:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x0E00;
    break;

	// Antarctic Tales Enhanced
	case 14:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0C00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x0300;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x2000;

    MapAddress[3] = 0x7100;
    DataSize[3] = 0x0A00;

    MapAddress[4] = 0xA000;
    DataSize[4] = 0x1E00;

    MapAddress[5] = 0xC000;
    DataSize[5] = 0x4000;
    break;

	// Astro Invader
	case 15:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x0800;

    MapAddress[1] = 0x5800;
    DataSize[1] = 0x0800;

    MapAddress[2] = 0x6000;
    DataSize[2] = 0x0800;

    MapAddress[3] = 0x6800;
    DataSize[3] = 0x0800;

    MapAddress[4] = 0xD000;
    DataSize[4] = 0x0800;

    MapAddress[5] = 0xF000;
    DataSize[5] = 0x0800;

    MapAddress[6] = 0xF800;
    DataSize[6] = 0x0800;
    break;

	// Astrosmash Competition / BSG Space Battle
	case 16:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1000;
    break;

	// Bank Panic
	case 17:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0300;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x2700;

    MapAddress[2] = 0x7100;
    DataSize[2] = 0x0A00;

    MapAddress[3] = 0xA000;
    DataSize[3] = 0x1A00;

    MapAddress[4] = 0xC000;
    DataSize[4] = 0x3900;
    break;

	// BC's Quest for Tires
	case 18:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x0100;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1F00;

    MapAddress[2] = 0xC100;
    DataSize[2] = 0x3F00;
    break;

	// Beach Head
	case 19:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x000E;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0x6000;
    DataSize[2] = 0x0F83;

    MapAddress[3] = 0x7100;
    DataSize[3] = 0x099F;

    MapAddress[4] = 0xA000;
    DataSize[4] = 0x1000;

    MapAddress[5] = 0xB000;
    DataSize[5] = 0x0F07;

    MapAddress[6] = 0xC100;
    DataSize[6] = 0x0F00;

    MapAddress[7] = 0xD000;
    DataSize[7] = 0x1000;

    MapAddress[8] = 0xE000;
    DataSize[8] = 0x1000;

    MapAddress[9] = 0xF000;
    DataSize[9] = 0x00E1;
    break;

	// Beat Em & Eat Em / Intellipongola
	case 20:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1D00;
    break;

	// Boot Hill
	case 21:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0A00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x0400;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x2000;

    MapAddress[3] = 0x7100;
    DataSize[3] = 0x2800;

    MapAddress[4] = 0xA000;
    DataSize[4] = 0x0F00;

    MapAddress[5] = 0xC000;
    DataSize[5] = 0x0300;
    break;

	// Bowl Bust / Istar / runnerZ
	case 22:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1800;
    break;

	// Bump n Jump Super Pro
	case 23:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xA000;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0xD000;
    DataSize[2] = 0x1000;

    MapAddress[3] = 0xF000;
    DataSize[3] = 0x1000;
    break;

	// Caverns of Mars
	case 24:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0C00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x0700;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x1F00;

    MapAddress[3] = 0x7100;
    DataSize[3] = 0x0B00;

    MapAddress[4] = 0xA000;
    DataSize[4] = 0x1C00;

    MapAddress[5] = 0xC100;
    DataSize[5] = 0x3F00;
    break;

	// CB-TICTACTOE
	case 25:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1B00;
    break;

	// Choplifter
	case 26:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0x9000;
    DataSize[1] = 0x2000;
    break;

	// Christmas Carol Vs The Ghost Of Christmas Presents
	case 27:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x00FF;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x2000;

    MapAddress[3] = 0x7100;
    DataSize[3] = 0x0500;

    MapAddress[4] = 0XA000;
    DataSize[4] = 0x1D00;

    MapAddress[5] = 0xC000;
    DataSize[5] = 0x3FFF;
    break;

	// Classic Battle Ship
	case 28:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1500;

    MapAddress[1] = 0xC000;
    DataSize[1] = 0x1000;
    break;

	// Clowns and Balloons
	case 29:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1100;
    break;

	// Copter Command
	case 30:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1F00;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x0B00;

    MapAddress[2] = 0xF000;
    DataSize[2] = 0x0A00;
    break;

	// Cosmic Avenger
	case 31:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0963;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x000E;

    MapAddress[2] = 0x4810;
    DataSize[2] = 0x07B6;

    MapAddress[3] = 0x5000;
    DataSize[3] = 0x1000;

    MapAddress[4] = 0x6000;
    DataSize[4] = 0x0F29;

    MapAddress[5] = 0x7100;
    DataSize[5] = 0x0F00;

    MapAddress[6] = 0x8000;
    DataSize[6] = 0x00CC;

    MapAddress[7] = 0xC040;
    DataSize[7] = 0x0FC0;

    MapAddress[8] = 0xD000;
    DataSize[8] = 0x1000;

    MapAddress[9] = 0xE000;
    DataSize[9] = 0x1000;

    MapAddress[10] = 0xF000;
    DataSize[10] = 0x0FF2;
    break;

	// The Crimson Tower
	case 32:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0B00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x0500;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x0300;

    MapAddress[3] = 0xA000;
    DataSize[3] = 0x1500;

    MapAddress[4] = 0xC000;
    DataSize[4] = 0x4000;
    break;

	// D2K
	case 33:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0x9000;
    DataSize[1] = 0x3000;

    MapAddress[2] = 0xD000;
    DataSize[2] = 0x1000;

    MapAddress[3] = 0xF000;
    DataSize[3] = 0x1000;
    break;

	// Death Race
	case 34:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1800;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x0A00;
    break;

	// Deep Zone
	case 35:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x0600;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x2000;

    MapAddress[3] = 0x7100;
    DataSize[3] = 0x7800;
    break;

	// The Depth of Nitemare
	case 36:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1800;

    MapAddress[1] = 0xA000;
    DataSize[1] = 0x1800;

    MapAddress[2] = 0xC100;
    DataSize[2] = 0x3400;
    break;

	// Desert Bus
	case 37:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0E5B;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x000E;

    MapAddress[2] = 0x4900;
    DataSize[2] = 0x06E5;

    MapAddress[3] = 0x5000;
    DataSize[3] = 0x1000;

    MapAddress[4] = 0x6000;
    DataSize[4] = 0x0E87;

    MapAddress[5] = 0x7100;
    DataSize[5] = 0x0DAB;

    MapAddress[6] = 0xA000;
    DataSize[6] = 0x1000;

    MapAddress[7] = 0xB000;
    DataSize[7] = 0x0EFA;

    MapAddress[8] = 0xC100;
    DataSize[8] = 0x0F00;

    MapAddress[9] = 0xD000;
    DataSize[9] = 0x1000;

    MapAddress[10] = 0xE000;
    DataSize[10] = 0x1000;

    MapAddress[11] = 0xF000;
    DataSize[11] = 0x0F9C;
    break;

	// Donkey Kong Arcade
	case 38:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0x9000;
    DataSize[1] = 0x2000;

    MapAddress[2] = 0xD000;
    DataSize[2] = 0x1000;

    MapAddress[3] = 0xF000;
    DataSize[3] = 0x1000;
    break;

	// Dragon Quest
	case 39:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0EE6;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x000F;

    MapAddress[2] = 0x4810;
    DataSize[2] = 0x0557;

    MapAddress[3] = 0x5000;
    DataSize[3] = 0x1000;

    MapAddress[4] = 0x6000;
    DataSize[4] = 0x0FBA;

    MapAddress[5] = 0x7100;
    DataSize[5] = 0x0EFB;

    MapAddress[6] = 0x8800;
    DataSize[6] = 0x0800;

    MapAddress[7] = 0x9000;
    DataSize[7] = 0x1000;

    MapAddress[8] = 0xA000;
    DataSize[8] = 0x1000;

    MapAddress[9] = 0xB000;
    DataSize[9] = 0x0A62;

    MapAddress[10] = 0xC100;
    DataSize[10] = 0x0F00;

    MapAddress[11] = 0xD000;
    DataSize[11] = 0x1000;

    MapAddress[12] = 0xE000;
    DataSize[12] = 0x1000;

    MapAddress[13] = 0xF000;
    DataSize[13] = 0x0F2E;
    break;

	// Dwarven Mine / Minehunter
	case 40:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1F00;
    break;

	// Eggerland Mystery Demo
	case 41:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0C00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x0100;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x0900;

    MapAddress[3] = 0x7100;
    DataSize[3] = 0x0200;

    MapAddress[4] = 0x8000;
    DataSize[4] = 0x1300;

    MapAddress[5] = 0xA000;
    DataSize[5] = 0x1500;

    MapAddress[6] = 0xC000;
    DataSize[6] = 0x0900;
    break;

	// Fantasy Puzzle
	case 42:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x00FF;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x2000;

    MapAddress[3] = 0x7100;
    DataSize[3] = 0x1000;

    MapAddress[4] = 0xA000;
    DataSize[4] = 0x6000;
    break;

	// Fast Food Plus
	case 43:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1000;

    MapAddress[1] = 0xC100;
    DataSize[1] = 0x1E00;
    break;

	// Flappy Byrd
	case 44:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1300;
    break;

	// The Flintstones Keyboard Fun
	case 45:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x1000;
    break;

	// Fox's Quest (Missing)
	// case 46:

	// Frankenstein's Monster
	case 47:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1C00;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x0700;

    MapAddress[2] = 0xF000;
    DataSize[2] = 0x0D00;
    break;

	// FUBAR
	case 48:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0xF000;
    DataSize[2] = 0x1000;
    break;

	// FW Diagnostics
	case 49:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x000E;

    MapAddress[1] = 0x4900;
    DataSize[1] = 0x0577;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x1000;

    MapAddress[3] = 0x6000;
    DataSize[3] = 0x0AB6;

    MapAddress[4] = 0x7100;
    DataSize[4] = 0x0EA4;

    MapAddress[5] = 0xA000;
    DataSize[5] = 0x0F9C;

    MapAddress[6] = 0xC100;
    DataSize[6] = 0x0F00;

    MapAddress[7] = 0xD000;
    DataSize[7] = 0x1000;

    MapAddress[8] = 0xE000;
    DataSize[8] = 0x1000;

    MapAddress[9] = 0xF000;
    DataSize[9] = 0x0D9A;
    break;

	// Galaxian
	case 50:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x000E;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0x6000;
    DataSize[2] = 0x0C8C;

    MapAddress[3] = 0xC100;
    DataSize[3] = 0x0F00;

    MapAddress[4] = 0xD000;
    DataSize[4] = 0x00EA;
    break;

	// Goatnom
	case 51:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x000E;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x0E11;

    MapAddress[2] = 0xC100;
    DataSize[2] = 0x0F00;

    MapAddress[3] = 0xD000;
    DataSize[3] = 0x1000;

    MapAddress[4] = 0xE000;
    DataSize[4] = 0x0C3F;
    break;

	// Gooninuff / H.E.L.I.
	case 52:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x2800;

    MapAddress[2] = 0x7100;
    DataSize[2] = 0x0F00;

    MapAddress[3] = 0xA000;
    DataSize[3] = 0x5E00;
    break;

	// GORF
	case 53:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x2800;

    MapAddress[2] = 0x8800;
    DataSize[2] = 0x2F00;

    MapAddress[3] = 0xC800;
    DataSize[3] = 0x3800;
    break;

	// Gorillas / Old Skool / Space Cunt / Super Mine-field / Tetris
	case 54:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;
    break;

	// GoSub
	case 55:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x0100;
    break;

	// GoSub (Digital)
	case 56:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0460;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x000F;

    MapAddress[2] = 0x4810;
    DataSize[2] = 0x00DC;

    MapAddress[3] = 0x5000;
    DataSize[3] = 0x1000;

    MapAddress[4] = 0x6000;
    DataSize[4] = 0x0470;

    MapAddress[5] = 0xA000;
    DataSize[5] = 0x07CE;

    MapAddress[6] = 0xB000;
    DataSize[6] = 0x09EC;

    MapAddress[7] = 0xC040;
    DataSize[7] = 0x0C14;
    break;

	// Hotel Bunny
	case 57:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1600;
    break;

	// Hunt the Wumpus
	case 58:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1800;

    MapAddress[1] = 0xC100;
    DataSize[1] = 0x2600;
    break;

	// Infiltrator (Alpha)
	case 59:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0AA2;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x000F;

    MapAddress[2] = 0x4810;
    DataSize[2] = 0x0503;

    MapAddress[3] = 0x5000;
    DataSize[3] = 0x1000;

    MapAddress[4] = 0x6000;
    DataSize[4] = 0x0F71;

    MapAddress[5] = 0x7100;
    DataSize[5] = 0x0943;

    MapAddress[6] = 0x8040;
    DataSize[6] = 0x0FC0;

    MapAddress[7] = 0x9000;
    DataSize[7] = 0x0EDE;

    MapAddress[8] = 0xA000;
    DataSize[8] = 0x1000;

    MapAddress[9] = 0xB000;
    DataSize[9] = 0x0DFF;

    MapAddress[10] = 0xC040;
    DataSize[10] = 0x0FC0;

    MapAddress[11] = 0xD000;
    DataSize[11] = 0x1000;

    MapAddress[12] = 0xE000;
    DataSize[12] = 0x1000;

    MapAddress[13] = 0xF000;
    DataSize[13] = 0x0DD2;
    break;

	// IntelliVania
	case 60: 
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x2800;

    MapAddress[2] = 0x7100;
    DataSize[2] = 0x0F00;

    MapAddress[3] = 0x8800;
    DataSize[3] = 0x2F00;

    MapAddress[4] = 0xC800;
    DataSize[4] = 0x3800;
	break;

	// Intle
	case 61:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0A00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x0100;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x1300;

    MapAddress[3] = 0xA000;
    DataSize[3] = 0x0700;

    MapAddress[4] = 0xC000;
    DataSize[4] = 0x3500;
    break;

	// IntyBASIC Showcase Vol 1
	case 62:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0C00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x0700;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x2000;

    MapAddress[3] = 0x7100;
    DataSize[3] = 0x0F00;

    MapAddress[4] = 0x9000;
    DataSize[4] = 0x2F00;

    MapAddress[5] = 0xC000;
    DataSize[5] = 0x3600;
    break;

	// IntyBASIC Showcase Vol 2
	case 63:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x0700;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x2000;

    MapAddress[2] = 0x8800;
    DataSize[2] = 0x2F00;

    MapAddress[3] = 0xC800;
    DataSize[3] = 0x2F00;
	break;

	// IntyPak
	case 64:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x0D00;
    break;

	// Jawcrusher
	case 66:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xA000;
    DataSize[1] = 0x0F00;

    MapAddress[2] = 0xC000;
    DataSize[2] = 0x3300;
    break;

	// Jr. Pac-Man
	case 67:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0EF1;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x1000;

    MapAddress[3] = 0x6000;
    DataSize[3] = 0x0FCE;

    MapAddress[4] = 0xA000;
    DataSize[4] = 0x1000;

    MapAddress[5] = 0xB000;
    DataSize[5] = 0x0FFA;

    MapAddress[6] = 0xC100;
    DataSize[6] = 0x0F00;

    MapAddress[7] = 0xD000;
    DataSize[7] = 0x1000;

    MapAddress[8] = 0xE000;
    DataSize[8] = 0x1000;

    MapAddress[9] = 0xF000;
    DataSize[9] = 0x0E61;
    break;

	// JumpKing Junior
	case 68:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xA000;
    DataSize[1] = 0x2000;

    MapAddress[2] = 0xD000;
    DataSize[2] = 0x1000;

    MapAddress[3] = 0xF000;
    DataSize[3] = 0x1000;
    break;

	// Jungle Hunt
	case 69:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xA000;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0xD000;
    DataSize[2] = 0x3000;
    break;

	// Keystone Kopps
	case 70:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1800;

    MapAddress[1] = 0xB000;
    DataSize[1] = 0x4D00;
    break;

	// Kvader
	case 71:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x0100;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1B00;
    break;

	// Laser Sharks
	case 72:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x2800;

    MapAddress[1] = 0xC800;
    DataSize[1] = 0x3800;
    break;

	// The Leprechaun's Flight
	case 73:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1600;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x1100;
    break;

	// Lock n Chase Revenge of Lupin
	case 74:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1000;

    MapAddress[1] = 0x6000;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0x9000;
    DataSize[2] = 0x1000;
    break;

	// Lode Runner (missing)
	// case 75:

	// Lost Caves of Kroz
	case 76:
    MapAddress[0] = 0x0800;
    DataSize[0] = 0x0800;

    MapAddress[1] = 0x2000;
    DataSize[1] = 0x0800;

    MapAddress[2] = 0x2800;
    DataSize[2] = 0x0800;

    MapAddress[3] = 0xB000;
    DataSize[3] = 0x0800;

    MapAddress[4] = 0xB800;
    DataSize[4] = 0x0800;
    break;

	// Mad Bomber + Avalanche
	case 77:
    MapAddress[0] = 0x2000;
    DataSize[0] = 0x0D00;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x2000;

    MapAddress[2] = 0x7100;
    DataSize[2] = 0x0A00;

    MapAddress[3] = 0xA000;
    DataSize[3] = 0x1500;

    MapAddress[4] = 0xC100;
    DataSize[4] = 0x2A00;
    break;

	// Maria
	case 78:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x0700;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x2000;

    MapAddress[3] = 0x7100;
    DataSize[3] = 0x0F00;

    MapAddress[4] = 0xA000;
    DataSize[4] = 0x6000;
    break;

	// Mars Mini Games
	case 79:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1400;
    break;

	// MazezaM
	case 80:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1C00;

    MapAddress[1] = 0xA000;
    DataSize[1] = 0x3800;
    break;

	// Mermaid
	case 81:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x0100;

    MapAddress[1] = 0xC000;
    DataSize[1] = 0x3900;
    break;

	// Meteors!
	case 82:
	MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x0E00;

    MapAddress[2] = 0xF000;
    DataSize[2] = 0x0D00;
    break;

	// Missile Domination
	case 83:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1E00;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x0C00;

    MapAddress[2] = 0xF000;
    DataSize[2] = 0x1000;
    break;

	// Moon Blast
	case 84:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x0100;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1D00;

    MapAddress[2] = 0xC100;
    DataSize[2] = 0x2500;
    break;

	// Moonsweeper
	case 85:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1D00;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x0E00;

    MapAddress[2] = 0xF000;
    DataSize[2] = 0x0A00;
    break;

	// Mr Turtle
	case 86:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0700;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x0600;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x2000;

    MapAddress[3] = 0x7100;
    DataSize[3] = 0x1B00;

    MapAddress[4] = 0xA000;
    DataSize[4] = 0x5000;
    break;

	// Mr Chess
	case 87:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x0100;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1E00;

    MapAddress[2] = 0xA000;
    DataSize[2] = 0x1800;

    MapAddress[3] = 0xC100;
    DataSize[3] = 0x3900;
    break;

	// Ms Stalker
	case 88:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x1000;
    break;

	// Ms. Pac-Man
	case 89:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0x8800;
    DataSize[1] = 0x3000;

    MapAddress[2] = 0xD000;
    DataSize[2] = 0x3000;
    break;

	// Mystic Castle
	case 90:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0x9000;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0xD000;
    DataSize[2] = 0x1000;

    MapAddress[3] = 0xF000;
    DataSize[3] = 0x1000;
    break;

	// Norseman, The
	case 91:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x0100;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x2000;

    MapAddress[2] = 0x7100;
    DataSize[2] = 0x0B00;

    MapAddress[3] = 0xA000;
    DataSize[3] = 0x0B00;

    MapAddress[4] = 0xC000;
    DataSize[4] = 0x1000;
    break;

	// Oh Mummy!
	case 92:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1D00;
    break;

	// Omega Race
	case 93:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0413;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x000E;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x1000;

    MapAddress[3] = 0x6000;
    DataSize[3] = 0x0B34;

    MapAddress[4] = 0x7100;
    DataSize[4] = 0x09F0;

    MapAddress[5] = 0xA000;
    DataSize[5] = 0x0C70;

    MapAddress[6] = 0xC040;
    DataSize[6] = 0x0FC0;

    MapAddress[7] = 0xD000;
    DataSize[7] = 0x1000;

    MapAddress[8] = 0xE000;
    DataSize[8] = 0x049C;
    break;

	// Oregon Bound
	case 94:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x2800;

    MapAddress[2] = 0x7100;
    DataSize[2] = 0x0F00;

    MapAddress[3] = 0xA000;
    DataSize[3] = 0x1D00;

    MapAddress[4] = 0xC100;
    DataSize[4] = 0x3F00;
    break;

	// Ouranos / Space Raid / Upmonsters
	case 95:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1F00;
    break;

	// The Pandora Incident (Alpha)
	case 96:
    MapAddress[0] = 0x0500;
    DataSize[0] = 0x09FC;

    MapAddress[1] = 0x2100;
    DataSize[1] = 0x0EF7;

    MapAddress[2] = 0x4800;
    DataSize[2] = 0x000E;

    MapAddress[3] = 0x4810;
    DataSize[3] = 0x07E7;

    MapAddress[4] = 0x5000;
    DataSize[4] = 0x1000;

    MapAddress[5] = 0x6000;
    DataSize[5] = 0x0FF7;

    MapAddress[6] = 0x7100;
    DataSize[6] = 0x0EF7;

    MapAddress[7] = 0x8040;
    DataSize[7] = 0x0FC0;

    MapAddress[8] = 0x9000;
    DataSize[8] = 0x1000;

    MapAddress[9] = 0xA000;
    DataSize[9] = 0x1000;

    MapAddress[10] = 0xB000;
    DataSize[10] = 0x0FF2;

    MapAddress[11] = 0xC040;
    DataSize[11] = 0x0FC0;

    MapAddress[12] = 0xD000;
    DataSize[12] = 0x1000;

    MapAddress[13] = 0xE000;
    DataSize[13] = 0x1000;

    MapAddress[14] = 0xF000;
    DataSize[14] = 0x0FFA;
    break;

	// Parsec (missing)
	// case 97:

	// Penguin Land
	case 98:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0532;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x000E;

    MapAddress[2] = 0x4810;
    DataSize[2] = 0x06FE;

    MapAddress[3] = 0x5000;
    DataSize[3] = 0x1000;

    MapAddress[4] = 0x6000;
    DataSize[4] = 0x0F45;

    MapAddress[5] = 0x7100;
    DataSize[5] = 0x0AE2;

    MapAddress[6] = 0xA000;
    DataSize[6] = 0x1000;

    MapAddress[7] = 0xB000;
    DataSize[7] = 0x0F4E;

    MapAddress[8] = 0xC100;
    DataSize[8] = 0x0F00;

    MapAddress[9] = 0xD000;
    DataSize[9] = 0x1000;

    MapAddress[10] = 0xE000;
    DataSize[10] = 0x1000;

    MapAddress[11] = 0xF000;
    DataSize[11] = 0x0F8D;
    break;

	// Piggy Bank
	case 99:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x2800;

    MapAddress[1] = 0xA000;
    DataSize[1] = 0x4000;
    break;

	// Pitfall 2
	case 100:
    MapAddress[0] = 0x2000;
    DataSize[0] = 0x1000;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x3800;

    MapAddress[2] = 0x8800;
    DataSize[2] = 0x3000;

    MapAddress[3] = 0xC800;
    DataSize[3] = 0x3800;
    break;

	// Pitfall III - Return to the Caverns (missing)
	// case 101:

	// Poker Risque
	case 102:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1A00;

    MapAddress[1] = 0xA000;
    DataSize[1] = 0x1500;

    MapAddress[2] = 0xC800;
    DataSize[2] = 0x2B00;
    break;

	// Princess Lydie (Beta 1)
	case 103:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x0100;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1B00;

    MapAddress[2] = 0xA000;
    DataSize[2] = 0x1400;

    MapAddress[3] = 0xC000;
    DataSize[3] = 0x3B00;
    break;

	// Princess Quest
	case 104:
	MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x2800;

    MapAddress[2] = 0xA000;
    DataSize[2] = 0x1F00;

    MapAddress[3] = 0xC100;
    DataSize[3] = 0x3F00;
	break;

	// Pumpkin Castle
	case 105:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1E00;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x0F00;

    MapAddress[2] = 0xF000;
    DataSize[2] = 0x0A00;
    break;

	// Pumpkin Trilogy
	case 106:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x0700;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x1000;

    MapAddress[3] = 0xA000;
    DataSize[3] = 0x1F00;

    MapAddress[4] = 0xC100;
    DataSize[4] = 0x3E00;
    break;

	// Rick Dynamite
	case 107:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x000E;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0x6000;
    DataSize[2] = 0x0981;

    MapAddress[3] = 0xA000;
    DataSize[3] = 0x1000;

    MapAddress[4] = 0xB000;
    DataSize[4] = 0x0E36;

    MapAddress[5] = 0xC040;
    DataSize[5] = 0x043D;

    MapAddress[6] = 0xC480;
    DataSize[6] = 0x05C2;

    MapAddress[7] = 0xCA44;
    DataSize[7] = 0x05BC;

    MapAddress[8] = 0xD000;
    DataSize[8] = 0x1000;

    MapAddress[9] = 0xE000;
    DataSize[9] = 0x062C;
    break;

	// Robot Finds Kitten
	case 108:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xA000;
    DataSize[1] = 0x4000;

    MapAddress[2] = 0xF000;
    DataSize[2] = 0x1000;
    break;

	// Rocky & Bullwinkle (missing)
	// case 109:

	// SameGame & Robots
	case 110:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x2800;

    MapAddress[1] = 0x8800;
    DataSize[1] = 0x3000;

    MapAddress[2] = 0xC800;
    DataSize[2] = 0x3800;
    break;

	// Secret Government Waffle Project
	case 111:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x0100;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1C00;
    break;

	// Shape Escape / Tramps
	case 112:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x0C00;
    break;

	// Shark Shark 2
	case 113:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1000;

    MapAddress[1] = 0x6000;
    DataSize[1] = 0x1000;
    break;

	// The Show Must Go On (missing)
	// case 114:

	// Slalom / Zombie Marbles
	case 115:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x0A00;
    break;

	// Smurf - Rescue in Gargamel's Castle
	case 116:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0xF000;
    DataSize[2] = 0x0700;
    break;

	// Space Invaders
	case 117:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1000;

    MapAddress[1] = 0x6000;
    DataSize[1] = 0x08B9;
    break;

	// Space Panic
	case 118:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xA000;
    DataSize[1] = 0x0B00;

    MapAddress[2] = 0xD000;
    DataSize[2] = 0x1000;

    MapAddress[3] = 0xF000;
    DataSize[3] = 0x1000;
    break;

	// Space Versus
	case 119:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x0100;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1900;

    MapAddress[2] = 0xD000;
    DataSize[2] = 0x2600;
    break;

	// Spirit
	case 120:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1600;

    MapAddress[1] = 0x9000;
    DataSize[1] = 0x2700;

    MapAddress[2] = 0xF000;
    DataSize[2] = 0x0800;
    break;

	// Stack 'Em!
        case 121:
        MapAddress[0] = 0x4800;
        DataSize[0] = 0x0800;
        break;

	// Stonix
	case 122:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0xF000;
    DataSize[2] = 0x1000;
    break;

	// Stop the Express
	case 123:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0E10;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x000E;

    MapAddress[2] = 0x4810;
    DataSize[2] = 0x0557;

    MapAddress[3] = 0x5000;
    DataSize[3] = 0x1000;

    MapAddress[4] = 0x6000;
    DataSize[4] = 0x0DE7;

    MapAddress[5] = 0x7100;
    DataSize[5] = 0x08FC;

    MapAddress[6] = 0xA000;
    DataSize[6] = 0x1000;

    MapAddress[7] = 0xB000;
    DataSize[7] = 0x0F31;

    MapAddress[8] = 0xC100;
    DataSize[8] = 0x0F00;

    MapAddress[9] = 0xD000;
    DataSize[9] = 0x1000;

    MapAddress[10] = 0xE000;
    DataSize[10] = 0x0EA4;
    break;

	// Stunt Cycle
	case 124:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x0100;

    MapAddress[1] = 0xC000;
    DataSize[1] = 0x3000;
    break;

	// Super Chef BurgerTime
	case 125:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x3000;
    break;

	// Super Mario Bros. Demo
	case 126:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x0100;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1F00;

    MapAddress[2] = 0x7100;
    DataSize[2] = 0x0F00;

    MapAddress[3] = 0x8800;
    DataSize[3] = 0x2400;

    MapAddress[4] = 0xC800;
    DataSize[4] = 0x2400;
    break;

	// Super Mystery Adventure
	// case 127:

	// Super Pixel Bros
	case 128:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1F00;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x0E00;
    break;

	// Super Pro Baseball
	case 129:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x2000;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x1000;
    break;

	// Super Pro Hockey/Tennis
	case 130:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1000;

    MapAddress[1] = 0x6000;
    DataSize[1] = 0x1000;
    break;

	// Sydney Hunter and the Sacred Tribe
	case 131:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x2800;

    MapAddress[2] = 0x7100;
    DataSize[2] = 0x0F00;

    MapAddress[3] = 0xA000;
    DataSize[3] = 0x2000;

    MapAddress[4] = 0xC100;
    DataSize[4] = 0x3E00;
    break;

	// Tag-Along Todd
	case 132:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1500;
    break;

	// Takeover (missing)
	// case 133:

	// Thunder Soldier
	case 134:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x0700;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x2000;

    MapAddress[3] = 0x7100;
    DataSize[3] = 0x0F00;

    MapAddress[4] = 0xA000;
    DataSize[4] = 0x2000;

    MapAddress[5] = 0xC100;
    DataSize[5] = 0x3F00;
    break;

	// Tower Attack!
	case 135:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1A00;
    break;

	// Towering Inferno
	case 136:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1200;

    MapAddress[1] = 0x7100;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0xC100;
    DataSize[2] = 0x3A00;
    break;

	// TV Powww!
	case 137:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1E00;

    MapAddress[1] = 0x9000;
    DataSize[1] = 0x1700;
    break;

	// Ultimate Pong
	case 138:
    MapAddress[0] = 0x4800;
    DataSize[0] = 0x0100;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1E00;

    MapAddress[2] = 0xA000;
    DataSize[2] = 0x1500;

    MapAddress[3] = 0xC100;
    DataSize[3] = 0x3D00;
    break;

	// Unlucky Pony
	case 139:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x0E00;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x0E00;
    break;

	// Vanguard
	case 140:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0DF9;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x000E;

    MapAddress[2] = 0x5000;
    DataSize[2] = 0x1000;

    MapAddress[3] = 0x6000;
    DataSize[3] = 0x0F50;

    MapAddress[4] = 0x7100;
    DataSize[4] = 0x0EEB;

    MapAddress[5] = 0xA000;
    DataSize[5] = 0x1000;

    MapAddress[6] = 0xB000;
    DataSize[6] = 0x01DE;

    MapAddress[7] = 0xC100;
    DataSize[7] = 0x0F00;

    MapAddress[8] = 0xD000;
    DataSize[8] = 0x1000;

    MapAddress[9] = 0xE000;
    DataSize[9] = 0x1000;

    MapAddress[10] = 0xF000;
    DataSize[10] = 0x0E80;
    break;

	// Whale Hunt
	case 141:
    MapAddress[0] = 0x0500;
    DataSize[0] = 0x0600;

    MapAddress[1] = 0x2000;
    DataSize[1] = 0x0C00;

    MapAddress[2] = 0x4800;
    DataSize[2] = 0x2600;

    MapAddress[3] = 0x7800;
    DataSize[3] = 0x0700;

    MapAddress[4] = 0x8000;
    DataSize[4] = 0x1D00;

    MapAddress[5] = 0xB800;
    DataSize[5] = 0x3300;

    MapAddress[6] = 0xF800;
    DataSize[6] = 0x0600;
    break;

	// Wizard of Wor
	case 142:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x063B;

    MapAddress[1] = 0x4800;
    DataSize[1] = 0x000E;

    MapAddress[2] = 0x4810;
    DataSize[2] = 0x0300;

    MapAddress[3] = 0x5000;
    DataSize[3] = 0x1000;

    MapAddress[4] = 0x6000;
    DataSize[4] = 0x0F66;

    MapAddress[5] = 0x7100;
    DataSize[5] = 0x0F00;

    MapAddress[6] = 0x8000;
    DataSize[6] = 0x1000;

    MapAddress[7] = 0x9000;
    DataSize[7] = 0x00C2;

    MapAddress[8] = 0xA000;
    DataSize[8] = 0x0B7D;

    MapAddress[9] = 0xC040;
    DataSize[9] = 0x0FC0;

    MapAddress[10] = 0xD000;
    DataSize[10] = 0x1000;

    MapAddress[11] = 0xE000;
    DataSize[11] = 0x1000;

    MapAddress[12] = 0xF000;
    DataSize[12] = 0x0E1D;
    break;

	// X-Rally
	case 143:
    MapAddress[0] = 0x2100;
    DataSize[0] = 0x0F00;

    MapAddress[1] = 0x5000;
    DataSize[1] = 0x1A00;

    MapAddress[2] = 0x7100;
    DataSize[2] = 0x0D00;

    MapAddress[3] = 0x8800;
    DataSize[3] = 0x1100;

    MapAddress[4] = 0xA000;
    DataSize[4] = 0x2000;

    MapAddress[5] = 0xC100;
    DataSize[5] = 0x3D00;
    break;

	// Yars' Revenge
	case 144:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1A00;

    MapAddress[1] = 0xA000;
    DataSize[1] = 0x1000;

    MapAddress[2] = 0xC100;
    DataSize[2] = 0x3F00;
    break;

	// Zombie Madness
	case 145:
    MapAddress[0] = 0x5000;
    DataSize[0] = 0x1F00;

    MapAddress[1] = 0xD000;
    DataSize[1] = 0x0C00;

    MapAddress[2] = 0xF000;
    DataSize[2] = 0x0F00;
    break;





        case 999:
        MapAddress[0] = 0x1000;
        DataSize[0] = 0x1000;
        break;

        default:
        cout << "Error: invalid rom map." << endl;
        PrintHelp();
        break;
    }
}

int ProcessArg(const char *value, char *buffer, int argc, char* argv[])
{
	int i;
	for(i = 1;i< argc;i++)
	{
		if(strcmp(value,argv[i]) == 0)
		{
			i++;
			if(i < argc)
			{
				if(strlen(argv[i]) < MAXBUFFER) // Prevent buffer overflow.
				{
					strcpy(buffer, argv[i]);
					return(1);
				}
				else
				{
					cout << "Error: Argument too long.  Buffer overflow.";
					exit(3);
					return(-1);
				}
			}
			else
				return(-1);
		}
	}
	return(0);
}

bool CheckforFile(const char *path)
{
	
	if(access(path, 0) == 0)
	{
		return(true);
	}
	else return(false);
}

const int wordsize = 2;
const char tempFileName[] = "tempfile.tmp";

int main(int argc, char* argv[])
{
    ifstream inputFile;
    ofstream outputFile;

    char inputBuffer[wordsize];
    char outputBuffer[wordsize];
    char stringBuffer[MAXBUFFER];
    char intputFileName[MAXBUFFER];
    char outputFileName[MAXBUFFER];
    unsigned int readSize = 0;
    unsigned int headerSize;

    if(argc < 4)
	{
        PrintHelp();
	}

    if(ProcessArg("-m",stringBuffer,argc,argv) != 1)
		PrintHelp();

    PopulateHeader(atoi(stringBuffer));
    
    strcpy(intputFileName, argv[3]);
    strcpy(outputFileName, argv[4]);

    if(!CheckforFile(intputFileName))
    {
        cout << "Error opening input file: "<< intputFileName << endl;
        exit(1);
    }

    inputFile.open(intputFileName, ios::binary);
    outputFile.open(tempFileName, ios::binary);

    // swap data order
    while(inputFile.read(inputBuffer, wordsize))
    {   
        readSize++; 
        for(int i=0;i<wordsize;i++)
            outputBuffer[i] = inputBuffer[(wordsize-1)-i];

        outputFile.write(outputBuffer, wordsize);
    }
    inputFile.close();
    outputFile.close();
    
    inputFile.open(tempFileName, ios::binary);
    outputFile.open(outputFileName, ios::binary);

// first block
    if(readSize > DataSize[0])
        headerSize = DataSize[0];
    else
        headerSize = readSize;

    readSize -= headerSize;
    
    //write header
    outputFile.write((const char *) &MapAddress[0], sizeof(unsigned int)); // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write address

    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;

// second block
    if(readSize > DataSize[1])
        headerSize = DataSize[1];
    else
        headerSize = readSize;

    readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[1], sizeof(unsigned int)); // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size
 
    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;

// third block
    if(readSize > DataSize[2])
        headerSize = DataSize[2];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[2], sizeof(unsigned int)); // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size

    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;

// fourth block
    if(readSize > DataSize[3])
        headerSize = DataSize[3];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[3], sizeof(unsigned int)); // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size

    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;

// fifth block
    if(readSize > DataSize[4])
        headerSize = DataSize[4];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[4], sizeof(unsigned int));

    // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size


    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;


// 6th block
    if(readSize > DataSize[5])
        headerSize = DataSize[5];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[5], sizeof(unsigned int));

    // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size


    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;


// 7th block
    if(readSize > DataSize[6])
        headerSize = DataSize[6];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[6], sizeof(unsigned int));

    // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size


    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;


// 8th block
    if(readSize > DataSize[7])
        headerSize = DataSize[7];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[7], sizeof(unsigned int));

    // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size


    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;


// 9th block
    if(readSize > DataSize[8])
        headerSize = DataSize[8];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[8], sizeof(unsigned int));

    // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size


    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;


// 10th block
    if(readSize > DataSize[9])
        headerSize = DataSize[9];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[9], sizeof(unsigned int));

    // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size


    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;


// 11th block
    if(readSize > DataSize[10])
        headerSize = DataSize[10];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[10], sizeof(unsigned int));

    // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size


    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;


// 12th block
    if(readSize > DataSize[11])
        headerSize = DataSize[11];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[11], sizeof(unsigned int));

    // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size


    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;


// 13th block
    if(readSize > DataSize[12])
        headerSize = DataSize[12];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[12], sizeof(unsigned int));

    // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size


    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;

// 14th block
    if(readSize > DataSize[13])
        headerSize = DataSize[13];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[13], sizeof(unsigned int));

    // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size


    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;

// 15th block
    if(readSize > DataSize[14])
        headerSize = DataSize[14];
    else
        headerSize = readSize;

     readSize -= headerSize;

    //write header
    outputFile.write((const char *) &MapAddress[14], sizeof(unsigned int));

    // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size


    //write data
    while(inputFile.read(inputBuffer, wordsize))
    {
        outputFile.write(inputBuffer, wordsize);
        if(--headerSize == 0)
            break;
    }

    if(readSize == 0)
        goto endblock;

endblock:
// end block
    headerSize = 0;
    // write footer: write the address and size as zero
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write address
    outputFile.write((const char *) &headerSize, sizeof(unsigned int)); // write size

    inputFile.close();
    outputFile.close();

    unlink(tempFileName);
    return 0;
}

