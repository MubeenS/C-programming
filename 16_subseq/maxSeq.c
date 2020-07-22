#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array,size_t n) {
  int prevMax=1,currMax=1;
  size_t i ;
  if(n==0) return 0;
  for(i=0;i<n;i++) {
    if(array[i]<array[i+1])
      currMax++;
    else {
      if(prevMax<currMax)
	prevMax=currMax;
      currMax=0;
    }
  }
  return prevMax;
}

