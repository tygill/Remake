cmake_minimum_required(VERSION 2.8)

# Directory:
# GameFrame/gf


# Core library (libGameFrame.a, GameFrame.dll, etc.)

set(GameFrame_LIB_CXX
    "Component.cpp"
    "ComponentLock.cpp"
    "ComponentLocks.cpp"
    "ComponentPtr.cpp"
    "ComponentTree.cpp"
    "ComponentTypes.cpp"
    "Entities.cpp"
    "Entity.cpp"
    "EntityIds.cpp"
    "EntityManager.cpp"
    "EntitySystem.cpp"
    "EntitySystems.cpp"
    "Exceptions.cpp"
    "GameFrame.cpp"
    "GameFrameThread.cpp"
    "HashMap.cpp"
    "HashSet.cpp"
    "Message.cpp"
    "MessageManager.cpp"
    "MessagePtr.cpp"
    "OrderedSet.cpp"
    "PtrHashMap.cpp"
    "PtrHashMultimap.cpp"
    "PtrOrderedSet.cpp"
    "Queue.cpp"
    "Resource.cpp"
    "ResourceManager.cpp"
    "ResourcePtr.cpp"
)

file(GLOB GameFrame_LIB_H "*.h")
#file(GLOB GameFrame_CORE_LIB_H "core/*.h")

# Global linkage libraries

if (UNIX)
set(GameFrame_EXTRA_LIBS
    ${Boost_LIBRARIES}
#    "rt"
    CACHE
    FILEPATH
    "Full paths to all dependent libraries for GameFrame"
)
elseif (WIN32)
set(GameFrame_EXTRA_LIBS
    ${Boost_LIBRARIES}
    CACHE
    FILEPATH
    "Full paths to all dependent libraries for GameFrame"
)
endif (UNIX)

# Revise this...
add_library(GameFrame ${GameFrame_LIB_CXX} ${GameFrame_LIB_H})
set(GameFrame_LIBS
    ${GameFrame}
    ${GameFrame_EXTRA_LIBS}
    CACHE
    FILEPATH
    "Full path to all GameFrame libraries."
)

#if(CMAKE_BUILD_TYPE STREQUAL Release)
#add_library(GameFrame ${GameFrame_LIB_CXX} ${GameFrame_LIB_H} ${GameFrame_CORE_LIB_H})
#set(GameFrame_LIBS
#    ${GameFrame}
#    ${GameFrame_EXTRA_LIBS}
#    CACHE
#    FILEPATH
#    "Full path to all GameFrame libraries."
#)
#endif(CMAKE_BUILD_TYPE STREQUAL Release)
#if(CMAKE_BUILD_TYPE STREQUAL Debug)
#add_library(GameFramed ${GameFrame_LIB_CXX} ${GameFrame_LIB_H} ${GameFrame_CORE_LIB_H})
#set(GameFramed_LIBS
#    ${GameFramed}
#    ${GameFrame_EXTRA_LIBS}
#    CACHE
#    FILEPATH
#    "Full path to all GameFrame debug libraries."
#)
#endif(CMAKE_BUILD_TYPE STREQUAL Debug)

#find_library(GameFrame_LIBRARY GameFrame ${LIBRARY_OUTPUT_PATH})

# Add the core component libraries
#add_subdirectory(core)
#add_subdirectory(sdl)
