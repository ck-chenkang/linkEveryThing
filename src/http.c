#include "http.h"

void httpTest()
{
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.13.29:3000/");
    struct curl_slist *headers = NULL;
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    res = curl_easy_perform(curl);
  }
  curl_easy_cleanup(curl);
}

void httpPostTest()
{
CURL *curl;
CURLcode res;
curl = curl_easy_init();
if(curl) {
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.13.29:3000/");
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
  struct curl_slist *headers = NULL;
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  res = curl_easy_perform(curl);
}
curl_easy_cleanup(curl);
}

void getToken()
{
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl, CURLOPT_URL, "http://portal-datahub-texpro-ews001.hz.wise-paas.com.cn/api/Auth");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Cookie: EIToken=eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJjb3VudHJ5IjoiQ04iLCJjcmVhdGlvblRpbWUiOjE1ODQ2ODg0MzksImV4cCI6MTYxNzg1MjE5NCwiZmlyc3ROYW1lIjoic2h1YWkiLCJpYXQiOjE2MTc4NDg1OTQsImlkIjoiNWU5YzMxZDItNmE3YS0xMWVhLWE0MDAtYmU1MzNmMDI5MTkwIiwiaXNzIjoid2lzZS1wYWFzIiwibGFzdE1vZGlmaWVkVGltZSI6MTYxNzg0ODQ0NSwibGFzdE5hbWUiOiJ3ZWkiLCJyZWZyZXNoVG9rZW4iOiI1ZjBjNTk3MC05ODExLTExZWItOTJhOC1jNmM2NDdjODM1MTAiLCJzdGF0dXMiOiJBY3RpdmUiLCJ1c2VybmFtZSI6IndlaXNodWFpQHRleHByby1ncm91cC5jb20ifQ.qQK4LFS-Py-g5Nlwiqo3NYBGsgNObgdBdZo4CrrYMb_6Z2YbuklyfZAbDK-OAoC-8tBa6rZyHdsJXOpQZfF-OQ; EIName=shuai");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    const char *data = "{\n    \"username\": \"weishuai@texpro-group.com\",\n    \"password\": \"Sontech@222\"\n}";
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    res = curl_easy_perform(curl);
    printf("\nres:%d", res);
  }
  curl_easy_cleanup(curl);
}

void init_string(struct string *s)
{
  s->len = 0;
  s->ptr = malloc(s->len + 1);
  if (s->ptr == NULL)
  {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size * nmemb;
  s->ptr = realloc(s->ptr, new_len + 1);
  if (s->ptr == NULL)
  {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr + s->len, ptr, size * nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size * nmemb;
}
