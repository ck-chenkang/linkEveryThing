#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/typecheck-gcc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string {
  char *ptr;
  size_t len;
};

void httpTest();
void httpPostTest();


void getToken();



void init_string(struct string *s);

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s);