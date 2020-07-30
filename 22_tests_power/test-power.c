#include <stdlib.h>
#include <stdbool.h>
unsigned power (unsigned x, unsigned y);
int main() {
  bool check = true;
  if(power(2,0)!=1)
    return EXIT_FAILURE;
  if(power(9,1)!=9)
    return EXIT_FAILURE;
   if(power(0,0)!=1)
    return EXIT_FAILURE;
  if(power(2,2)!=4)
    return EXIT_FAILURE;
   if(power(0,1)!=0)
    return EXIT_FAILURE;
    if(power(-1,6)!=1)
    return EXIT_FAILURE;
    if(power(-1,3)!=-1)
    return EXIT_FAILURE;
    if(power(0,-2)!=0)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
