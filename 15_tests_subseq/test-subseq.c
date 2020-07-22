#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);
int main() {
  int arr1[]={1,2,3,1,2,3,4,5,6,0,1,2};
  int arr2[]={3,2,1,5,9,7,10,13,14,15,16};
  size_t a=maxSeq(arr1,sizeof(arr1)/sizeof(int));
  if(a==6) return EXIT_SUCCESS;
  else return EXIT_FAILURE;
   size_t b=maxSeq(arr2,sizeof(arr2)/sizeof(int));
  if(a==6) return EXIT_SUCCESS;
  else return EXIT_FAILURE;
}
