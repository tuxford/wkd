cmake_minimum_required (VERSION 2.6)

project(KDservice)

if(SIM)
    add_definitions(-DSIM)
endif(SIM)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

if(SIM)
add_executable(KDservice 
    src/AbstractMethod.cpp
    src/CommandHandler.cpp
    src/DebugClientConnectProxy.cpp
    src/DebugRpcServer.cpp
    src/FakeClient.cpp
    src/KdConnectMethod.cpp
    src/kdservice.cpp
    src/MethodRegistry.cpp
    src/Run.cpp
    src/ServerBuilder.cpp)
else(SIM)

add_executable(KDservice 
    src/AbstractMethod.cpp
    src/CommandHandler.cpp
    src/DebugClientConnectProxy.cpp
    src/DebugRpcServer.cpp
    src/Install.cpp
    src/KdClient.cpp
    src/KdConnectMethod.cpp
    src/kdservice.cpp
    src/MethodRegistry.cpp
    src/Run.cpp
    src/ServerBuilder.cpp)
endif(SIM)
    
target_link_libraries(KDservice xmlrpc++ xmlrpc_server++ xmlrpc_abyss xmlrpc_server_abyss++ pthread)
   