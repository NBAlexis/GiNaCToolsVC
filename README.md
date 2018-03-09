# GiNaCToolsVC
Use GiNaC and some libs based on it using VS2017 on WIN10

###Build and run###

Should work in VS2017 without modifications.

Only test x64 version on Win10

Build solution.
put "Dependency/gmp-6.1.2/libgmp-10.dll"
to "Bin/x64/Debug" and "Bin/x64/Release"

Run CLN_Test.exe to test CLN
Run GINAC_Test.exe to test GiNaC

###Dependency###

GMP: v6.1.2
Built with MinGW64

CLN: v1.3.4
Modified for VS

GiNaC: v1.7.4
Modified for VS

NestedSums: v1.5.1
http://wwwthep.physik.uni-mainz.de/~stefanw/nestedsums/

Reduz: v2.2
https://reduze.hepforge.org/

GiNaCRA: v0.6.4
NOTICE!: 
GiNaCRA seems not complete yet, I should NOT waste my time on this.
Code added, some test runs while others not.
And I will not work on this any longer.
http://ginacra.sourceforge.net/

###Build GMP, CLN, GiNaC in MinGW64###

Before put the code into VS, we need configure the projects. They might be helpful if you only want to use MinGW but not VS.

The modifications needed to make cln, ginac, etc are put into MinGWVersion folder.
Just copy and overwrite them before make in MinGW.
Tested in MinGW64 in MSYS2

For GMP, configure use
$./configure --disable-static --enable-shared
To obtain the import lib for VS, follow the instructions in the document, but change the file name libgmp-3.dll.def to libgmp-10.def first

For CLN, configure use
$./configure --enable-shared

For GiNaC, need python
$pacman -S python

For Reduze, need cmake
$pacman -S cmake



