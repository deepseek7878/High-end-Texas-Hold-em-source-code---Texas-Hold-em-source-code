
#-----------------------------------------------------------------------

APP           := XGame
TARGET        := PushServer
CONFIG        := 
STRIP_FLAG    := N
TARS2CPP_FLAG :=
CFLAGS        += -lm
CXXFLAGS      += -lm

INCLUDE   += -I/usr/local/cpp_modules/wbl/include
LIB       += -L/usr/local/cpp_modules/wbl/lib -lwbl

INCLUDE   += -I/usr/local/cpp_modules/protobuf/include
LIB       += -L/usr/local/cpp_modules/protobuf/lib -lprotobuf

#-----------------------------------------------------------------------
include /home/tarsproto/XGame/Comm/Comm.mk
include /home/tarsproto/XGame/util/util.mk
include /home/tarsproto/XGame/protocols/protocols.mk
include /home/tarsproto/XGame/ConfigServer/ConfigServer.mk
include /home/tarsproto/XGame/RouterServer/RouterServer.mk
include /home/tarsproto/XGame/DBAgentServer/DBAgentServer.mk
include /home/tarsproto/XGame/HallServer/HallServer.mk
include /home/tarsproto/XGame/LoginServer/LoginServer.mk
include /home/tarsproto/XGame/PushServer/PushServer.mk
include /usr/local/tars/cpp/makefile/makefile.tars

#-----------------------------------------------------------------------

xgame:
	cp -f $(TARGET) /usr/local/app/tars/tarsnode/data/XGame.PushServer/bin/
