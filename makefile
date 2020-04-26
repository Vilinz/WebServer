VPATH = src:src/logger:src/singleton:src/net
compile = g++ -g -std=c++11
objects = main.o logger.o epoller.o server.o

myServer : $(objects)
	$(compile) -o server $(objects)
main.o : main.cpp singleton.h logger.h server.h
	$(compile) -c $^
logger.o : logger.cpp logger.h singleton.h
	$(compile) -c $^
epoller.o : epoller.cpp epoller.h logger.h singleton.h
	$(compile) -c $^
server.o : server.cpp epoller.h logger.h singleton.h
	$(compile) -c $^

clean :
	rm myServer $(objects)