# TODO: Clean this up with Makefile tricks / shorthands.
# TODO: Add flags for debugging, etc.

.PHONY: all debug clean

all: client server

clean:
	rm -f ./*.exe

client: cat_laser_client.c
	gcc cat_laser_client.c -o cat_laser_client.exe

runclient: cat_laser_client.exe
	./cat_laser_client.exe

testclient: client runclient

server: cat_laser_server.c
	gcc cat_laser_server.c -o cat_laser_server.exe

runserver: cat_laser_server.exe
	./cat_laser_server.exe

testserver: server runserver

