VPATH = src:src/logger:src/singleton:src/net:src/base:src/http
compile = g++ -g -std=c++11
objects = main.o logger.o eventBase.o epoller.o looper.o connection.o server.o util.o httpResponse.o matcher.o route.o router.o httpParser.o httpServer.o

myServer : $(objects)
	$(compile) -o myServer $(objects)
main.o : main.cpp singleton.h logger.h server.h httpServer.h httpRequest.h
	$(compile) -c $<
logger.o : logger.cpp logger.h singleton.h
	$(compile) -c $<
eventBase.o : eventBase.cpp eventBase.h timestamp.h
	$(compile) -c $<
epoller.o : epoller.cpp epoller.h logger.h singleton.h eventBase.h
	$(compile) -c $<
looper.o : looper.cpp looper.h epoller.h
	$(compile) -c $<
connection.o : connection.cpp connection.h timestamp.h looper.h anyone.h
	$(compile) -c $<
server.o : server.cpp util.h looper.h util.h
	$(compile) -c $<
util.o : util.cpp util.h
	$(compile) -c $<
httpResponse.o : httpResponse.cpp httpResponse.h
	$(compile) -c $<
matcher.o : matcher.cpp matcher.h httpRequest.h
	$(compile) -c $<
route.o : route.cpp route.h matcher.h httpResponse.h
	$(compile) -c $<
router.o : router.cpp router.h route.h
	$(compile) -c $<
httpParser.o : httpParser.cpp httpParser.h httpRequest.h
	$(compile) -c $<
httpServer.o : httpServer.cpp httpServer.h server.h router.h timestamp.h httpParser.h httpRequest.h httpResponse.h
	$(compile) -c $<

clean :
	rm myServer $(objects)