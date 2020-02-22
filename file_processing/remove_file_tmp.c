#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main () {
   int ret;
   FILE *fp;
   char filename[] = "file.txt";

   //fp = fopen(filename, "w");
   fp = open(filename, O_CREAT, S_IRWXU);
   if (-1 == fp) {
       printf("Unable to open file!");
       return -1;
   }

   fprintf(fp, "%s", "This is tutorialspoint.com from temp binary\n");
   fclose(fp);

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
   
   return(0);
}


