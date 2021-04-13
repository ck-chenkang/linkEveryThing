build: WISEPaaS.Datahub.Edge.so.1.0.3
	arm-linux-gnueabihf-gcc main.c -ldl -g -o main -std=c99

WISEPaaS.Datahub.Edge.so.1.0.3: DatahubEdge.o cJSON.o message.o libmosquitto.so libsqlite3.so libcurl.so
	arm-linux-gnueabihf-gcc -shared -Wl,-soname,DatahubEdge.so.1 -o DatahubEdge.so.1.0.3 DatahubEdge.o message.o cJSON.o libmosquitto.so libsqlite3.so libcurl.so

DatahubEdge.o: DatahubEdge.c
	arm-linux-gnueabihf-gcc -c -fPIC -o DatahubEdge.o DatahubEdge.c

message.o: message.c cJSON.o
	arm-linux-gnueabihf-gcc -c -fPIC -o message.o message.c
	
cJSON.o: cJSON.c
	arm-linux-gnueabihf-gcc -c -fPIC -o cJSON.o cJSON.c
clean:
	rm -rf test.o