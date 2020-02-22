#include <sys/file.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main () {
   int ret;
   FILE *fp;
   char filename[] = "file.txt";
    int fd;
   fp = fopen(filename, "w");
   fd = fileno(fp);
   
   flock(fd, LOCK_EX);

   fprintf(fp, "%s", "This is tutorialspoint.com \n");
//   fclose(fp);

//    if (access(filename, F_OK) != 1) {
//        ret = remove(filename);
//        
//        if(ret == 0) {
//           printf("File deleted successfully\n");
//        } else {
//           printf("Error: unable to delete the file\n");
//        }
//   }
//   fprintf(fp, "%s", "This is tutorialspoint.com \n");
//   fclose(fp);
    while(1);
   
   return(0);
}


