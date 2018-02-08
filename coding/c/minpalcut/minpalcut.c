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
    uint ** m = malloc (sizeof(uint *)*len);
    bool ** p = malloc (sizeof(bool *)*len);

    for(uint i = 0; i < len; i++) {
        m[i] = malloc (sizeof(uint)*len);
        p[i] = malloc (sizeof(bool)*len);
        m[i][i] = 0;
        p[i][i] = true;
    }
        
    for (uint i = 1; i < len; i++) {
        for(uint j = 0;j < len-i; j++) {
          if(i == 1) { p[j][j+i] = s[j] == s[j+i]; }
          else { p[j][j+i] = (s[j] == s[j+i]) && p[j+1][j+i-1]; }
          if(p[j][j+i]) { m[j][j+i] = 0; }
          else {
                uint cuts = len;
                for(uint k = 0; k < i; k++) {
                    cuts = min(cuts,1+m[j][j+k]+m[j+k+1][j+i]);
                }
                m[j][j+i] = cuts;
          }            
        }
    }
    return m[0][last];
}

#define TEST(a,b) \
  {\
  uint cuts = mincut(a);\
  if(cuts == b) { printf("%s: pass.\n",a); }\
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
