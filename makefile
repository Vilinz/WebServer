VPATH = src:src/logger:src/singleton:src/net:src/base
compile = g++ -g -std=c++11
objects = main.o logger.o eventBase.o epoller.o looper.o connection.o server.o util.o

myServer : $(objects)
	$(compile) -o server $(objects)
main.o : main.cpp singleton.h logger.h server.h
	$(compile) -c $<
logger.o : logger.cpp logger.h singleton.h
	$(compile) -c $<
eventBase.o : eventBase.cpp eventBase.h timestamp.h
	$(compile) -c $<
epoller.o : epoller.cpp epoller.h logger.h singleton.h eventBase.h
	$(compile) -c $<
looper.o : looper.cpp looper.h epoller.h
	$(compile) -c $<
connection.o : connection.cpp connection.h timestamp.h looper.h
	$(compile) -c $<
server.o : server.cpp util.h looper.h util.h
	$(compile) -c $<
util.o : util.cpp util.h
	$(compile) -c $<

clean :
	rm myServer $(objects)