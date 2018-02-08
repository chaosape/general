#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


/* Recursive approach to solving the problem with dynamic programming. Performance will 
   suffer drastically on large input arrays. */
bool dynprog_rec(int * nums, int idx, int target) {
  if(target == 0) { return true; }
  if(idx < 0) {return false; }
  if(target - nums[idx] < 0) { return dynprog_rec(nums,idx-1,target); }
  else { return ((dynprog_rec(nums,idx-1,target)) || (dynprog_rec(nums,idx-1,target - nums[idx]))); } 
}

/* Iterative approach to solving the problem with dynamic programming. */
bool dynprog_it(int * nums, int numsSize, int target) {

  bool ** matrix = malloc(numsSize * sizeof(bool*));
  for(int i = 0; i < numsSize; i++) {
    matrix[i] = malloc((target+1)*sizeof(bool));
    matrix[i][0] = true;
  }

  for(int i = 0; i < numsSize; i++) {
    for(int j = 1; j < target + 1; j++) {
      if(i == 0) {
        matrix[i][j] = nums[i] == j;
      }
      else {
        if(j < nums[i]){ matrix[i][j] = matrix[i-1][j]; }
        else if(j == nums[i]){ matrix[i][j]=true; }
        else {
          matrix[i][j] = matrix[i-1][j] || matrix[i-1][j - nums[i]];
        }
      }
    }
  }
  return matrix[numsSize-1][target];
}

/* Recursive approach to solving the problem via brute
   force. Performance will suffer drastically on large input
   arrays. */
bool bruteforce_rec(int * nums,int numsSize, int idx, int sum, int target) {
  if( idx == numsSize ) { return sum == target; }
  return ((bruteforce_rec(nums,numsSize,idx+1,sum+nums[idx],target))
          || (bruteforce_rec(nums,numsSize,idx+1,sum,target)));
}



#include <limits.h>   /* for CHAR_BIT */

#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)

void bitinc(char bs[], int size) {
  for(int i = 0 ; i < size; i++) {
    if(!BITTEST(bs,i+1)) {
      BITSET(bs,i+1);
      return;
    } else {
      BITCLEAR(bs,i+1);
    }
  }
}

bool emptyP(char bs[], int size) {
  for(int i = 0; i < size; i++) {
    if(BITTEST(bs,i+1)){ return false; }
  }
  return true;
}

/* Iterative approach to solving the problem via brute
   force. */
bool bruteforce_it(int * nums, int numsSize, int target) {
  char bs[BITNSLOTS(numsSize)];
  memset(bs,0,BITNSLOTS(numsSize));
  int c = 0;
  do {
    int sum = 0;
    for(int j = 0; j < numsSize; j++) {
      if(BITTEST(bs,j+1)) { sum += nums[j]; } 
    }
    if(sum == target) { return true; }
    bitinc(bs,numsSize);
  } while (!emptyP(bs,numsSize));

  return false;
}


bool canPartition(int* nums, int numsSize) {
    int sum = 0;
    for(int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }
    if(sum % 2 != 0) { return false; }
    /* return bruteforce(nums,numsSize,0,0,sum/2); */
    return dynprog_it(nums,numsSize,sum/2);
}

void main() {

  int test1[] = {1,5,11,5};
  if(canPartition(test1,4)) { printf("Correct.\n"); }

  int test2[] = {1,5,2,2,2};
  if(canPartition(test2,5)) { printf("Correct.\n"); }

  int test3[] = {5,7};
  if(!canPartition(test3,2)) { printf("Correct.\n"); }

  int test4[50];
  for(int i = 0; i < 50; i++) { test4[i]=100; }
  if(canPartition(test4,50)) { printf("Correct.\n"); }
  
}
