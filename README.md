# int2intv
## Intellivision ROM converter for Analogue Pocket & NT Mini cores

This will convert Intellivision games into the INTV2 format ([as documented here](https://github.com/SmokeMonsterPacks/Nt-Mini-Noir-Jailbreak#intellivision-core-release-notes)). I've extended the tool with built-in conversion for most compatible homebrew games. 
Original tool by [dot-bob](https://github.com/dot-bob/int2intv), and incorporating work by [mholzinger](https://github.com/mholzinger/int2intv).


## Usage
Intellivision ROM files must be first converted to BIN format using the rom2bin.exe tool in the [prebuilt downloadable toolset for jzintv](http://spatula-city.org/~im14u2c/intv/).

Then run this on the resulting BIN file, via the command line: 

> int2intv -m X \<input file\> \<output file\>

X = Memory map number for each ROM (Check this [Google Doc](https://docs.google.com/spreadsheets/d/11WgwYnT4n2ISqqROVcIkUwWzz7HQMCu4FcrRUb02kGE/edit?usp=sharing))

Map #99 is used to convert the intellivision Executive ROM (CRC32 0xCBCE86F7) to the correct format for the Intellivision core.


## Compatibility Issues
Certain games don't work - check the Google Doc above for specific info:
* Anything that relies on JLP features can't be converted to the INTV format at all, as far as I can tell.
* Some games (particularly with large numbers of memory addresses) seem to simply result in an "Unaligned Value" error when attempting to run them.
* I'm also not sure how to correctly convert games with RAM addresses specified, though some seem to run okay as-is. This should be supported by the INTV2 format.

If you know how resolve any of these errors, please let me know!


## Build
To build from source you can use your favorite flavor of the gnu c++ compiler.

> g++ int2intv.cpp -s -static -o int2intv
