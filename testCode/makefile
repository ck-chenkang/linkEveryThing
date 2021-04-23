cjsonTest.exe:
	gcc -o cJsonTest.exe ./cJsonTest/cJsonTest.c ./cJsonTest/cJSON.c -I/../../inc/cJSON.h
readArr.exe:
	gcc -o readArr.exe ./cJsonTest/readArr.c ./cJsonTest/cJSON.c -I/../../inc/cJSON.h
readWholeFileContents.exe:
	gcc -o readWholeFileContents.exe ./readWholeFileContents/main.c
test.exe:
	arm-linux-gnueabihf-gcc -o test test.c 
structlen.exe:
	gcc -o structlen.exe ./structLen/case1.c
getCurrentTime.exe:
	gcc -o getCurrentTime.exe ./time/getCurrentTime.c
getCurrentTime2.exe:
	gcc -o getCurrentTime2.exe ./time/getCurrentTime2.c
asprintf.exe:
	gcc -o asprintf.exe ./printFamily/asprintf.c
threadSimpleCase1.exe:
	gcc -o threadSimpleCase1.exe ./threads/simplecase1.c -lpthread
lock.exe:
	gcc -o lock.exe ./threads/lock.c -lpthread
join.exe:
	gcc -o join.exe ./threads/join.c -lpthread
condition.exe:
	gcc -o condition.exe ./threads/condition.c -lpthread
clean:
	rm -f *.exe