cmake_minimum_required (VERSION 2.6)

project(KDservice)

if(SIM)
    add_definitions(-DSIM)
    add_definitions(-DAPP)
else(SIM)
	set(CMAKE_CXX_FLAGS "/MDd /EHsc")
endif(SIM)

if(APP)
    add_definitions(-DAPP)
endif(APP)

if(AMD64)
	set(CMAKE_EXE_LINKER_FLAGS "/machine:x64")
endif(AMD64)

if(WIN32)
	add_definitions(/D_DEBUG)
	add_definitions(/DWIN32)
#/D_ITERATOR_DEBUG_LEVEL=2 /D_ITERATOR_DEBUG_LEVEL=2
endif(WIN32)


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
    src/ErrorEvent.cpp
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
    src/ErrorEvent.cpp
    src/AttachKernelEvent.cpp
    src/InitialState.cpp
    src/ConnectedState.cpp
    src/AttachedKernelState.cpp
    src/DebugEventCallbacks.cpp
    src/RunWindowsService.cpp
    src/ServerBuilder.cpp)
    
target_link_libraries(KDservice libxmlrpc libxmlrpc++ libxmlrpc_client libxmlrpc_server libxmlrpc_abyss libxmlrpc_server_abyss libxmlrpc_util libxmlrpc_server_w32httpsys 
	log4cppD 
	libboost_thread-vc100-mt-1_53
	 dbgeng dbghelp  )

endif(SIM)
    
   