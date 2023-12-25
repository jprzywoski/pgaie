Programming game AI by example
==
by Mat Buckland
© 2005, Wordware Publishing, Inc.
All Rights Reserved

Introduction
==

This repository contains source code ported from original Visual Studio 2010
projects into gcc and make buildable format.

Luabind was updated to 0.9.1 with some patches for newer boost libraries applied.

Build environment
==

All code samples build on Windows XP SP3 32-bit and Windows 7 64-bit without
errors. Lots of compiler warnings though.

This code won't compile on Linux or Mac, since win32 api calls are used. Porting
to gtk+ or Qt to handle graphics and mouse and keyboard input wouldn't be much 
of a deal, but I don't have any enthusiasm left right now.

Steps
==
Those instructions are for Windows XP. If you are using anything modern install 
newer versions of Git and gcc. Don't install 32 bit versions of Git on
64 bit Windows and don't mix 32 bit and 64 bit libraries on your system.

a) Install Git for Windows (Git-2.10.0-32-bit)
Download location: https://github.com/git-for-windows/git/releases/tag/v2.10.0.windows.1

b) Install TDM-GCC compiler (tdm-gcc-5.1.0-3)
Download location: https://sourceforge.net/projects/tdm-gcc/files/TDM-GCC%20Installer/
1. Deselect 'Check for updated ...' option if using the offline installer
2. (Optional) Add 'OpenMP' during install to get easy multithreading support
3. After install go to C:\TDM-GCC-32\bin and make copies of those two files 
(select the file, press CTRL+C and then CTRL+V):
mingw32-make and gdb32
4. Rename copies to simply 'make' and 'gdb' respectively.

c) Compile Lua 5.1 (lua-5.1.5.tar)
Download location: https://www.lua.org/versions.html#5.1
1. Unpack the archive, open the folder with 'Git Bash Here' (by right clicking)
2. Compile with 'make mingw local'
3. Copy the following files or folder contents into TDM-GCC-32 directory:

	Source						Destination
	lua-5.1.5\lib\liblua.a		TDM-GCC-32\lib
	lua-5.1.5\bin				TDM-GCC-32\bin
	lua-5.1.5\src\lua51.dll		TDM-GCC-32\bin
	lua-5.1.5\include 			TDM-GCC-32\include

d) Download boost 1.57 and unpack files somewhere (say C:\Devtools)
Download location: https://www.boost.org/users/history/version_1_57_0.html

e) Install boost-build
1. Open windows command crompt (Start > Programs > Accessories > command prompt, not Git Bash) and cd to C:\Devtools\boost_1_57_0\tools\build
2. Run bootstrap.bat gcc
3. Run b2 install --prefix="C:\Devtools\boost-build" toolset=gcc
4. Add C:\Devtools\boost-build\bin to Windows PATH:
Right click on 'My Computer', go to 'Advanced > Environment Variables'
Add new 'PATH' variable to 'User variables' if necessary; append 'C:\Devtools\boost-build\bin' to its values

f) Compile and install boost 1.57
1. Open new (needs to re-read PATH) windows command prompt and go to C:\Devtools\boost_1_57_0
2. Run this:
3. bootstrap.bat gcc
4. b2 --build-dir="C:\Devtools\boost_1_57_0\build" --prefix="C:\Devtools\boost" toolset=gcc install
5. (Optional) This will expose boost headers and make linking simpler, but will also
shadow all other versions of boost on your machine.
Copy the following files or folders into TDM-GCC-32 directory:

	Source										Destination
	C:\Devtools\boost\include\boost-1_57\boost	TDM-GCC-32\include
	C:\Devtools\boost\lib						TDM-GCC-32\lib

Now you can build code like this (second example from 'Getting started'):

	$ g++ main.cpp -lboost_regex-mgw51-mt-1_57

f) Build Luabind
1. Open new windows command prompt and go to luabind-0.9.1 directory
2. Export required variables:
set BOOST_ROOT="C:\Devtools\boost\include\boost-1_57"
set LUA_PATH=C:\TDM-GCC-32
3. Build luabind with:
bjam stage toolset=gcc release
4. Copy the following files or folders into TDM-GCC-32 directory:

	Source									Destination
	luabind-0.9.1\luabind					TDM-GCC-32\include
	luabind-0.9.1\stage\libluabind.dll.a	TDM-GCC-32\lib
	luabind-0.9.1\stage\libluabind.dll		TDM-GCC-32\bin

g) Now you can build any project by executing 'make' in Git Bash terminal.

	MINGW64 /PGAIE/Buckland_Chapter3-Steering Behaviors
	$ make
	Building main.o
	...
	Building all
	g++ ... -o Steering.exe

Note. Run compiled applications in windows command prompt or just double click them to run.
Don't use Git terminal.

h) Code editor recommendations:
1. Visual Studio Code
2. Qt Creator (3.6.1 works fine with this setup)
3. Eclipse Cevelop
4. Notepad++

