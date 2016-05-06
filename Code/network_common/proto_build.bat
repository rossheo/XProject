@ECHO OFF
SET PROTO_EXE=..\..\build\protoc-2.6.1\protoc.exe
SET INCLUDE_PATH=.\proto\
SET CPP_OUT_PATH=.\pb\

@ECHO ON
%PROTO_EXE% -I=%INCLUDE_PATH% --cpp_out=%CPP_OUT_PATH% %INCLUDE_PATH%common.proto
%PROTO_EXE% -I=%INCLUDE_PATH% --cpp_out=%CPP_OUT_PATH% %INCLUDE_PATH%client_server.proto
%PROTO_EXE% -I=%INCLUDE_PATH% --cpp_out=%CPP_OUT_PATH% %INCLUDE_PATH%server_client.proto
