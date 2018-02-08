#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define min(a, b) a<b?a:b

void printmatrix(uint ** m, uint len) {
  for(uint i = 0; i < len; i++) {
    for(uint j = 0; j < len; j++) {
      printf("%4i",m[i][j]);
    }
    printf("\n");
  }
}

int mincut(char* s) {

  uint first = 0;
  uint last = 0;
  uint len = 0;
  for(; s[len] != '\0'; len++) {}
  last = len - 1;
  if(len <= 1) { return 0; }
  uint * c = malloc (sizeof(uint)*len);

  bool ** p = malloc (sizeof(bool *)*len);

  for(uint i = 0; i < len; i++) {
    p[i] = malloc (sizeof(bool)*len);
    memset(p[i],false,sizeof(bool)*len);
    p[i][i] = true;
    c[i] = len-1;
  }

  for (uint i = 1; i < len; i++) {
    for(uint j = 0;j < len-i; j++) {
      if(i == 1) { p[j][j+i] = s[j] == s[j+i]; }
      else { p[j][j+i] = (s[j] == s[j+i]) && p[j+1][j+i-1]; }
    }
  }
    
  for (uint i = 1; i < len; i++) {
    if(p[0][i]) { c[i] = 0; }
    else {
      for(uint j = 0; j < i; j++) {
        c[i] = min(c[i],c[j]+1);
      }
    }
  }
  return c[last];
}

#define TEST(a,b)                                                 \
  {                                                               \
    uint cuts = mincut(a);                                        \
    if(cuts == b) { printf("%s: pass.\n",a); }                    \
    else { printf("%s: fail (expected %i got %i).\n",a,b,cuts); } \
  }

void main() {
  
  TEST("aab",1);
  TEST("aaabaa",1);
  TEST("racecar",0);
  TEST("a",0);
  TEST("",0);
  TEST("abcdefghijklmnopqrstuvwxyz",25);
  TEST("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       ,1);

}
