#
# Portable Makefile
# 
# Main platform differences and important points
#
# On Windows, signature of the 'main()' function matters - it has to be like
# this:
# int main(int argc, char *argv[])
# Also when linking manually and not using `sdl-config --cflags --libs` you
# need to pass in some extra linker flags:
# -lmingw32 -lSDLmain -lSDL -mwindows
# When packaging you need to include mingw32 and SDL .dll runtime libraries
# in the game's directory.
# 
# On Linux make sure to enable commented out sections for much improved
# programming experience.
#
# In general, the best development experience is on Linux.
# 
# Other instructions
#
# a) Compiling for different platforms
# Select the corresponding PLATFORM, this will select all correct compiler and
# linker flags.
#
# b) Debug vs Release builds
# When developing and debugging always set TARGET to DEVEL - this will enable
# elevated compiler warning flags and add debug info to the binary.
#
# RELEASE is for the final binary release. It is also a good practice to strip
# the resulting binaries using: 'strip--strip-unneeded <binary>'
#
# c) Profile Guided Optimizations
# Profiled builds are a bit trickier, one has to compile twice:
# 1. first compile with TARGET := $(GENERATE_PROFILE)
# 2. run your application to collect peformance samples (.gcda files in the
# build directory)
# 3. run make clean to delete old .o object files
# 4. now run make again with TARGET := $(PROFILED_RELEASE) to compile a new
# binary using .gcda files for extra level of optimization
#
# d) CPU specific optimizations
# Setting compiler flags to -march=native and -mtune=native will generate
# faster code for the particular machine we are building on. The drawback is
# it will make the binary non backwards compatible CPU-wise.
#
# e) Static Code Analysis
# Run 'make check' rule to make sure the code is squeaky clean.
# 
# f) Code formatting
# Run 'make fmt' rule to make sure the code has consistent formatting.
# 
# g) Code coverage
# Run 'make cov' rule to see which parts of your code were executed. Very
# helpful when doing test first development.
# 
# h) Running in a debugger
# Run 'make run' to start the debugger. If the application segfaults just
# type 'bt full' to see where the problem happened.
#
# i) Release
# This has to be done manually for each platform really.
#
# j) Duplicated code
# Run 'make dup' to identify copy and paste areas.
#
# Notes on gcc flags
# gcc -Q --help=target --help=optimizers - this will print which optimizations 
# are enabled
# CXXFLAGS += -fopt-info-vec-all - this will print info on loops that were 
# auto vectorized (SIMD)
#

SHELL := /usr/bin/env bash
CXX := g++

#
# Colorize output
#
PRINT = @echo -e "\e[1;32mBuilding $@\e[0m"

#
# PLATFORM can be only one of the below
#
LINUX := 1
WINDOWS := 2
MAC := 3

#
# Select one only at a time
#
# PLATFORM := $(LINUX)
PLATFORM := $(WINDOWS)
# PLATFORM := $(MACOS)

#
# TARGET can be only one of the below
#
DEVEL := 1
RELEASE := 2
GENERATE_PROFILE := 3
PROFILED_RELEASE := 4

#
# Select one only at a time
#
# TARGET := $(DEVEL)
TARGET := $(RELEASE)
# TARGET := $(GENERATE_PROFILE)
# TARGET := $(PROFILED_RELEASE)

#
# Name of the resulting binary file
#
BUILD_ARTIFACT := Raven
ifeq ($(PLATFORM), $(WINDOWS))
	BUILD_ARTIFACT := $(BUILD_ARTIFACT).exe
endif

#
# -I, -D preprocessor options
#
CPPFLAGS = -I. -I../Common
ifneq ($(TARGET), $(DEVEL))
	CPPFLAGS += -DNDEBUG
endif

#
# Debugging and optimization options for the C and C++ compilers
#
ifeq ($(TARGET), $(DEVEL))

	#
	# Basic warnings
	#
	CXXFLAGS := -std=c++98 -pedantic -Wall -Wextra -Weffc++
	# CXXFLAGS += -Werror
	
	#
	# Extended warning and debug options
	#
	CXXFLAGS += -Wlogical-op -Wdouble-promotion -Wshadow -Wformat=2
	CXXFLAGS += -Wcast-align -Winvalid-pch -Wmissing-include-dirs
	CXXFLAGS += -Wredundant-decls -Wswitch-default -Wswitch-enum
	CXXFLAGS += -Wconversion -Wcast-qual -Wold-style-cast -Wuseless-cast
	# CXXFLAGS += -Wduplicated-cond -Wduplicated-branches -Wrestrict
	# CXXFLAGS += -Wnull-dereference
	# CXXFLAGS += -Wmissing-declarations -Wodr

	#
	# Debugger experience
	#
	CXXFLAGS += -O0 -g3 -fno-omit-frame-pointer -fno-strict-aliasing
	CXXFLAGS += -fno-optimize-sibling-calls -fasynchronous-unwind-tables
	CXXFLAGS += -fexceptions

	#
	# Code coverage and profiling
	#
	CXXFLAGS += --coverage -pg

	#
	# Security options, Linux only - comment out for Windows
	#
	# CPPFLAGS += -D_FORTIFY_SOURCE=2
	# CXXFLAGS += -fstack-protector-strong
	# CXXFLAGS += -fPIE -fPIC -pie -Wl,-pie -Wl,-z,defs -Wl,-z,now -Wl,-z,relro

	#
	# Sanitizers, Linux only - comment out for Windows
	#
	# CXXFLAGS += -fsanitize=leak
	# CXXFLAGS += -fsanitize=undefined
	#
	# Run with: ASAN_OPTIONS=detect_invalid_pointer_pairs=2: ./<binary>
	#
	# CXXFLAGS += -fsanitize=address
	# CXXFLAGS += -fsanitize=address -fsanitize=pointer-compare
	# CXXFLAGS += -fsanitize=pointer-subtract
	#
	# Those two only seem to work with clang on x86-64
	#
	# CXXFLAGS += -fsanitize=thread
	# CXXFLAGS += -fsanitize=memory
 else ifeq ($(TARGET), $(RELEASE))
	CXXFLAGS := -O2
else ifeq ($(TARGET), $(GENERATE_PROFILE))
	CXXFLAGS := -Ofast -march=native -mtune=native -flto -fprofile-generate
else ifeq ($(TARGET), $(PROFILED_RELEASE))
	CXXFLAGS := -Ofast -march=native -mtune=native -flto -fprofile-use
	#
	# Turn it on for multithreaded applications
	#
	# CXXFLAGS += -fprofile-correction
endif

#
# -L options for the linker
#
LDFLAGS := -L.

#
# -l options to pass to the linker
#
LDLIBS := -llua -lluabind -lwinmm -mwindows
ifeq ($(TARGET), $(DEVEL))
	#
	# Linux only, comment out for gcc on Windows
	#
	# LDLIBS += -fsanitize=address -static-libasan
	# LDLIBS += -fsanitize=undefined -static-libubsan
endif
ifeq ($(TARGET),$(filter $(TARGET),$(GENERATE_PROFILE) $(PROFILED_RELEASE)))
	LDLIBS += -lgcov
endif

#
# Linking
#
OBJECTS := main.o Script1.o GraveMarkers.o Raven_Bot.o Raven_Door.o Raven_Game.o Raven_Map.o
OBJECTS += Raven_SensoryMemory.o Raven_SteeringBehaviors.o Raven_TargetingSystem.o
OBJECTS += Raven_UserOptions.o Raven_WeaponSystem.o 
OBJECTS += Projectile_Bolt.o Projectile_Pellet.o Projectile_Rocket.o Projectile_Slug.o 
OBJECTS += Raven_Projectile.o Raven_Weapon.o Weapon_Blaster.o Weapon_RailGun.o Weapon_RocketLauncher.o Weapon_ShotGun.o
OBJECTS += AttackTargetGoal_Evaluator.o ExploreGoal_Evaluator.o GetHealthGoal_Evaluator.o 
OBJECTS += GetWeaponGoal_Evaluator.o Goal_AdjustRange.o Goal_AttackTarget.o 
OBJECTS += Goal_DodgeSideToSide.o Goal_Explore.o Goal_FollowPath.o Goal_GetItem.o 
OBJECTS += Goal_HuntTarget.o  Goal_MoveToPosition.o Goal_NegotiateDoor.o Goal_SayPhrase.o 
OBJECTS += Goal_SeekToPosition.o Goal_Think.o Goal_TraverseEdge.o Goal_Wander.o 
# OBJECTS += Goal_MoveToItem.o  Goal_FindTarget.o
OBJECTS += Raven_Feature.o Raven_Goal_Types.o
OBJECTS += Raven_PathPlanner.o Raven_Scriptor.o Trigger_HealthGiver.o Trigger_SoundNotify.o Trigger_WeaponGiver.o
OBJECTS += DebugConsole.o WindowUtils.o Cgdi.o PrecisionTimer.o CrudeTimer.o MessageDispatcher.o
OBJECTS += Vector2D.o iniFileLoaderBase.o BaseGameEntity.o EntityManager.o FrameCounter.o
OBJECTS += FuzzyModule.o FuzzyOperators.o FuzzySet_LeftShoulder.o FuzzySet_RightShoulder.o 
OBJECTS += FuzzySet_Singleton.o FuzzySet_Triangle.o FuzzyVariable.o

all: $(OBJECTS)
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(BUILD_ARTIFACT)

#
# Compiling
# *.h
main.o: main.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Script1.o: Script1.rc
	$(PRINT)
	windres -i $< -o $@
	
GraveMarkers.o: GraveMarkers.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)
	
Raven_Bot.o: Raven_Bot.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)
	
Raven_Door.o: Raven_Door.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)
	
Raven_Game.o: Raven_Game.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)
	
Raven_Map.o: Raven_Map.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)
	
Raven_SensoryMemory.o: Raven_SensoryMemory.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)
	
Raven_SteeringBehaviors.o: Raven_SteeringBehaviors.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)
	
Raven_TargetingSystem.o: Raven_TargetingSystem.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)
	
Raven_UserOptions.o: Raven_UserOptions.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)
	
Raven_WeaponSystem.o: Raven_WeaponSystem.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Projectile_Bolt.o: Armory/Projectile_Bolt.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)
	
Projectile_Pellet.o: Armory/Projectile_Pellet.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Projectile_Rocket.o: Armory/Projectile_Rocket.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Projectile_Slug.o: Armory/Projectile_Slug.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Raven_Projectile.o: Armory/Raven_Projectile.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Raven_Weapon.o: Armory/Raven_Weapon.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Weapon_Blaster.o: Armory/Weapon_Blaster.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Weapon_RailGun.o: Armory/Weapon_RailGun.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Weapon_RocketLauncher.o: Armory/Weapon_RocketLauncher.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Weapon_ShotGun.o: Armory/Weapon_ShotGun.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

AttackTargetGoal_Evaluator.o: Goals/AttackTargetGoal_Evaluator.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

ExploreGoal_Evaluator.o: Goals/ExploreGoal_Evaluator.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

GetHealthGoal_Evaluator.o: Goals/GetHealthGoal_Evaluator.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

GetWeaponGoal_Evaluator.o: Goals/GetWeaponGoal_Evaluator.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_AdjustRange.o: Goals/Goal_AdjustRange.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_AttackTarget.o: Goals/Goal_AttackTarget.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_DodgeSideToSide.o: Goals/Goal_DodgeSideToSide.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_Explore.o: Goals/Goal_Explore.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_FindTarget.o: Goals/Goal_FindTarget.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_FollowPath.o: Goals/Goal_FollowPath.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_GetItem.o: Goals/Goal_GetItem.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_HuntTarget.o: Goals/Goal_HuntTarget.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_MoveToItem.o: Goals/Goal_MoveToItem.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_MoveToPosition.o: Goals/Goal_MoveToPosition.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_NegotiateDoor.o: Goals/Goal_NegotiateDoor.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_SayPhrase.o: Goals/Goal_SayPhrase.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_SeekToPosition.o: Goals/Goal_SeekToPosition.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_Think.o: Goals/Goal_Think.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_TraverseEdge.o: Goals/Goal_TraverseEdge.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Goal_Wander.o: Goals/Goal_Wander.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Raven_Feature.o: Goals/Raven_Feature.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Raven_Goal_Types.o: Goals/Raven_Goal_Types.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Raven_PathPlanner.o: Navigation/Raven_PathPlanner.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Raven_Scriptor.o: Scriptor/Raven_Scriptor.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Trigger_HealthGiver.o: Triggers/Trigger_HealthGiver.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Trigger_SoundNotify.o: Triggers/Trigger_SoundNotify.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Trigger_WeaponGiver.o: Triggers/Trigger_WeaponGiver.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Cgdi.o: *.h ../Common/misc/Cgdi.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

FrameCounter.o: *.h ../Common/misc/FrameCounter.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

WindowUtils.o: *.h ../Common/misc/WindowUtils.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

CrudeTimer.o: *.h ../Common/Time/CrudeTimer.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

PrecisionTimer.o: *.h ../Common/Time/PrecisionTimer.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

DebugConsole.o: *.h ../Common/Debug/DebugConsole.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)
MessageDispatcher.o: *.h ../Common/Messaging/MessageDispatcher.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

iniFileLoaderBase.o: *.h ../Common/misc/iniFileLoaderBase.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

Vector2D.o: *.h ../Common/2D/Vector2D.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

BaseGameEntity.o: *.h ../Common/Game/BaseGameEntity.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

EntityManager.o: *.h ../Common/Game/EntityManager.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

FuzzyModule.o: ../Common/fuzzy/FuzzyModule.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

FuzzyOperators.o: ../Common/fuzzy/FuzzyOperators.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

FuzzySet_LeftShoulder.o: ../Common/fuzzy/FuzzySet_LeftShoulder.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

FuzzySet_RightShoulder.o: ../Common/fuzzy/FuzzySet_RightShoulder.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

FuzzySet_Singleton.o: ../Common/fuzzy/FuzzySet_Singleton.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

FuzzySet_Triangle.o: ../Common/fuzzy/FuzzySet_Triangle.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

FuzzyVariable.o: ../Common/fuzzy/FuzzyVariable.cpp
	$(PRINT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)

cov:
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out
	# chromium-browser ./out/index.html

prof:
	gprof $(BUILD_ARTIFACT) gmon.out

run: all
	echo "run" | gdb -quiet $(BUILD_ARTIFACT)

clean:
	rm -f *.o $(BUILD_ARTIFACT) || true
	rm *plist *gcno *gch gmon.out coverage.info profile.txt tests || true
	# rm *.gcda || true
	rm -f output.db || true
	rm -rf "infer-out" "out" || true
	rm -f *tar.gz || true
	rm -f *.orig */*.orig || true

release:
	strip --strip-unneeded $(BUILD_ARTIFACT)
	tar -czf $(BUILD_ARTIFACT).tar.gz $(BUILD_ARTIFACT)

SOURCE_FILES := *.cpp */*.cpp
HEADER_FILES := *.h */*.h

fmt:
	uncrustify -c ~/cpp.cfg --replace --no-backup $(HEADER_FILES) $(SOURCE_FILES)
	astyle --style=otbs --max-code-length=120 -k3 $(HEADER_FILES) $(SOURCE_FILES)
	astyle --style=allman --max-code-length=120 -k3 $(HEADER_FILES) $(SOURCE_FILES)
	# clang-format -i -style="{BasedOnStyle: Microsoft, ColumnLimit: 120}" $(HEADER_FILES) $(SOURCE_FILES)

check:
	# @echo
	# @echo -e "\e[1;33mAnalazing: clang-analyze... \e[0m"	
	# clang --analyze $(HEADER_FILES) $(SOURCE_FILES)

	# @echo
	# @echo -e "\e[1;33m Running clang-tidy... \e[0m"
	# #  -warnings-as-errors=*
	# clang-tidy -checks=boost-*,bugprone-*,cert-*,cppcoreguidelines-*,clang-analyzer-*,hicpp-*,modernize-*,performance-*,portability-*,readability-* $(HEADER_FILES) $(SOURCE_FILES)

	@echo
	@echo -e "\e[1;33mAnalazing: cppcheck... \e[0m"
	cppcheck --enable=all --platform=unix64 $(CPPFLAGS) std=c++98 $(HEADER_FILES) $(SOURCE_FILES)

	# @echo
	# @echo -e "\e[1;33mAnalazing: infer... \e[0m"
	# infer run -- gcc -c $(HEADER_FILES) $(SOURCE_FILES)

	# @echo
	# @echo -e "\e[1;33mAnalazing: oclint... \e[0m"
	# oclint $(HEADER_FILES) $(SOURCE_FILES) -- -c

	@echo
	@echo -e "\e[1;33mAnalazing: flawfinder... \e[0m"
	flawfinder $(HEADER_FILES) $(SOURCE_FILES)

	# @echo
	# @echo -e "\e[1;33mAnalazing: rats... \e[0m"
	# rats $(HEADER_FILES) $(SOURCE_FILES)

	@echo
	@echo -e "\e[1;33mAnalazing: flint++... \e[0m"	
	flint++ --cmode $(HEADER_FILES) $(SOURCE_FILES)

	# @echo
	# @echo -e "\e[1;33m Running cpplint... \e[0m"
	# cpplint $(HEADER_FILES) $(SOURCE_FILES)

dup:
	# @echo
	# @echo -e "\e[1;33mAnalazing: cpd... \e[0m"
	# cpd --language c++ --minimum-tokens 50 --files $(SOURCE_FILES)	
	
	@echo
	@echo -e "\e[1;33mAnalazing: lizard... \e[0m"
	python3 -m lizard -Eduplicate $(SOURCE_FILES)
