cmake_minimum_required (VERSION 2.6)

project(KDservice)

if(SIM)
    add_definitions(-DSIM)
    add_definitions(-DAPP)
endif(SIM)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

if(SIM)
add_executable(KDservice 
    src/AbstractMethod.cpp
    src/CommandHandler.cpp
    src/DebugRpcServer.cpp
    src/FakeClient.cpp
    src/KdConnectMethod.cpp
    src/KdAttachKernelMethod.cpp
    src/kdservice.cpp
    src/MethodRegistry.cpp
    src/DebugEventRpcSender.cpp
    src/Run.cpp
    src/RunApplication.cpp
    src/Install.cpp
    src/EventSerializer.cpp
    src/StateMachine.cpp
    src/ChangeStateEvent.cpp
    src/OutputEvent.cpp
    src/AttachKernelEvent.cpp
    src/InitialState.cpp
    src/ConnectedState.cpp
    src/AttachedKernelState.cpp
    src/ServerBuilder.cpp)
target_link_libraries(KDservice 
    xmlrpc xmlrpc_client++.a xmlrpc++ xmlrpc_client.a xmlrpc_server xmlrpc_abyss xmlrpc_server_abyss xmlrpc_util 
    pthread log4cpp 
    boost_thread
    curl)
else(SIM)

add_executable(KDservice 
    src/AbstractMethod.cpp
    src/CommandHandler.cpp
    src/DebugRpcServer.cpp
    src/Install.cpp
    src/KdClient.cpp
    src/KdConnectMethod.cpp
    src/KdAttachKernelMethod.cpp
    src/kdservice.cpp
    src/MethodRegistry.cpp
    src/DebugEventRpcSender.cpp
    src/Run.cpp
    src/RunApplication.cpp
    src/EventSerializer.cpp
    src/StateMachine.cpp
    src/ChangeStateEvent.cpp
    src/OutputEvent.cpp
    src/AttachKernelEvent.cpp
    src/InitialState.cpp
    src/ConnectedState.cpp
    src/AttachedKernelState.cpp
    src/ServerBuilder.cpp)
target_link_libraries(KDservice xmlrpc xmlrpc_server xmlrpc_client xmlrpc_client++ log4cpp boost_thread)
endif(SIM)
    
   