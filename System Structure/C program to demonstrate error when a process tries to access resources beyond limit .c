#include <stdio.h>
#include <sys/resource.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
  
int main() {
  
    struct rlimit old_lim, lim, new_lim;
  

    if( getrlimit(RLIMIT_NOFILE, &old_lim) == 0)
        printf("Old limits -> soft limit= %ld \t"
          " hard limit= %ld \n", old_lim.rlim_cur,
                               old_lim.rlim_max);
    else
        fprintf(stderr, "%s\n", strerror(errno));
  
  
    lim.rlim_cur = 3;
    lim.rlim_max = 1024;
  
      
  
    if(setrlimit(RLIMIT_NOFILE, &lim) == -1)
        fprintf(stderr, "%s\n", strerror(errno));
      
 
    if( getrlimit(RLIMIT_NOFILE, &new_lim) == 0)
        printf("New limits -> soft limit= %ld \t"
          " hard limit= %ld \n", new_lim.rlim_cur, 
                                new_lim.rlim_max);
    else
        fprintf(stderr, "%s\n", strerror(errno));
      
    
    if(open("foo.txt", O_WRONLY | O_CREAT, 0) == -1)
        fprintf(stderr, "%s\n", strerror(errno));
    else
            printf("Opened successfully\n");
      
    return 0;
}