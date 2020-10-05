#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CApp.o \
	${OBJECTDIR}/CBinaryHeap.o \
	${OBJECTDIR}/CCamera.o \
	${OBJECTDIR}/CCity.o \
	${OBJECTDIR}/CCivilization.o \
	${OBJECTDIR}/CDebugLogging.o \
	${OBJECTDIR}/CEvent.o \
	${OBJECTDIR}/CEventsManager.o \
	${OBJECTDIR}/CFindTileTypeProblem.o \
	${OBJECTDIR}/CFontsManager.o \
	${OBJECTDIR}/CFramerate.o \
	${OBJECTDIR}/CGame.o \
	${OBJECTDIR}/CGame_Initialize.o \
	${OBJECTDIR}/CGame_Loop.o \
	${OBJECTDIR}/CGame_OnEvent.o \
	${OBJECTDIR}/CMap.o \
	${OBJECTDIR}/CPath.o \
	${OBJECTDIR}/CPathFindingProblem.o \
	${OBJECTDIR}/CPathFindingStateSpace.o \
	${OBJECTDIR}/CSoundManager.o \
	${OBJECTDIR}/CState.o \
	${OBJECTDIR}/CStateManager.o \
	${OBJECTDIR}/CSurface.o \
	${OBJECTDIR}/CSurfaceManager.o \
	${OBJECTDIR}/CTile.o \
	${OBJECTDIR}/CTilesetManager.o \
	${OBJECTDIR}/CUnit.o \
	${OBJECTDIR}/DataSetup.o \
	${OBJECTDIR}/DrawingFunctions.o \
	${OBJECTDIR}/alphaBlit.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs SDL_image` `pkg-config --libs SDL_mixer` `pkg-config --libs SDL_ttf`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isometric

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isometric: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isometric ${OBJECTFILES} ${LDLIBSOPTIONS} `sdl-config --cflags --libs`

${OBJECTDIR}/CApp.o: CApp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CApp.o CApp.cpp

${OBJECTDIR}/CBinaryHeap.o: CBinaryHeap.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CBinaryHeap.o CBinaryHeap.cpp

${OBJECTDIR}/CCamera.o: CCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CCamera.o CCamera.cpp

${OBJECTDIR}/CCity.o: CCity.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CCity.o CCity.cpp

${OBJECTDIR}/CCivilization.o: CCivilization.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CCivilization.o CCivilization.cpp

${OBJECTDIR}/CDebugLogging.o: CDebugLogging.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CDebugLogging.o CDebugLogging.cpp

${OBJECTDIR}/CEvent.o: CEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CEvent.o CEvent.cpp

${OBJECTDIR}/CEventsManager.o: CEventsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CEventsManager.o CEventsManager.cpp

${OBJECTDIR}/CFindTileTypeProblem.o: CFindTileTypeProblem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CFindTileTypeProblem.o CFindTileTypeProblem.cpp

${OBJECTDIR}/CFontsManager.o: CFontsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CFontsManager.o CFontsManager.cpp

${OBJECTDIR}/CFramerate.o: CFramerate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CFramerate.o CFramerate.cpp

${OBJECTDIR}/CGame.o: CGame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CGame.o CGame.cpp

${OBJECTDIR}/CGame_Initialize.o: CGame_Initialize.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CGame_Initialize.o CGame_Initialize.cpp

${OBJECTDIR}/CGame_Loop.o: CGame_Loop.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CGame_Loop.o CGame_Loop.cpp

${OBJECTDIR}/CGame_OnEvent.o: CGame_OnEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CGame_OnEvent.o CGame_OnEvent.cpp

${OBJECTDIR}/CMap.o: CMap.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CMap.o CMap.cpp

${OBJECTDIR}/CPath.o: CPath.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CPath.o CPath.cpp

${OBJECTDIR}/CPathFindingProblem.o: CPathFindingProblem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CPathFindingProblem.o CPathFindingProblem.cpp

${OBJECTDIR}/CPathFindingStateSpace.o: CPathFindingStateSpace.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CPathFindingStateSpace.o CPathFindingStateSpace.cpp

${OBJECTDIR}/CSoundManager.o: CSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CSoundManager.o CSoundManager.cpp

${OBJECTDIR}/CState.o: CState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CState.o CState.cpp

${OBJECTDIR}/CStateManager.o: CStateManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CStateManager.o CStateManager.cpp

${OBJECTDIR}/CSurface.o: CSurface.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CSurface.o CSurface.cpp

${OBJECTDIR}/CSurfaceManager.o: CSurfaceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CSurfaceManager.o CSurfaceManager.cpp

${OBJECTDIR}/CTile.o: CTile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CTile.o CTile.cpp

${OBJECTDIR}/CTilesetManager.o: CTilesetManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CTilesetManager.o CTilesetManager.cpp

${OBJECTDIR}/CUnit.o: CUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CUnit.o CUnit.cpp

${OBJECTDIR}/DataSetup.o: DataSetup.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DataSetup.o DataSetup.cpp

${OBJECTDIR}/DrawingFunctions.o: DrawingFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DrawingFunctions.o DrawingFunctions.cpp

${OBJECTDIR}/alphaBlit.o: alphaBlit.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_mixer` `pkg-config --cflags SDL_ttf` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alphaBlit.o alphaBlit.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/isometric

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
