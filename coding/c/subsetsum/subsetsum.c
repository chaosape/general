#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
int int_compare (const void * a, const void * b) {
    return (*((const int *)a) - *((const int *)a) );
}

bool dynprog(int * nums, int idx, int target) {
  if(target == 0) { return true; }
  if(idx < 0) {return false; }
  if(target - nums[idx] < 0) { return dynprog(nums,idx-1,target); }
  else { return ((dynprog(nums,idx-1,target)) || (dynprog(nums,idx--,target - nums[idx]))); } 
}

bool bruteforce(int * nums,int numsSize, int idx, int sum, int target) {
  if( idx == numsSize ) { return sum == target; }
  return ((bruteforce(nums,numsSize,idx+1,sum+nums[idx],target))
          || (bruteforce(nums,numsSize,idx+1,sum,target)));
}

bool canPartition(int* nums, int numsSize) {
    qsort(nums,numsSize,sizeof(int),int_compare);
    int sum = 0;
    for(int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }
    if(sum % 2 != 0) { return false; }
    return bruteforce(nums,numsSize,0,0,sum/2);
    /* return dynprog(nums,numsSize-1,sum/2); */
}


void main() {

  int test1[] = {1,5,11,5};
  if(canPartition(test1,4)) { printf("Correct.\n"); }

  int test2[] = {1,5,2,2,2};
  if(canPartition(test2,5)) { printf("Correct.\n"); }

  int test3[] = {5,7};
  if(!canPartition(test3,2)) { printf("Correct.\n"); }


}
