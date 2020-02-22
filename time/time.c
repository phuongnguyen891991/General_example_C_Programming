#include <stdio.h>
#include <time.h>

int main () {
   time_t seconds;
   time_t orig_format;
//
//   seconds = time(12);
//   printf("Hours since January 1, 1970 = %ld\n", seconds);

   orig_format = time(NULL);

//   printf ("Universal Time is %s",asctime(gmtime(&orig_format)));
   printf ("Second is %ld \n", orig_format);
   sleep(1);
   printf ("delta time are: %ld \n", time(NULL) - orig_format);

   return(0);
}
