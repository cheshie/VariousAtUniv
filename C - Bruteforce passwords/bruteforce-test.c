// ldd --version shows 2.23 -> and I need glibc 2.7
//Is that a problem? 
//http://man7.org/linux/man-pages/man3/crypt.3.html
//http://man7.org/linux/man-pages/man3/crypt.3.html
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <crypt.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


//Work on the strand of the problem
//To salivate themselves
//Innocuous problem these times

//"There is one thing you should remember when
//Dealing with parallel universes. One - they are 
//not really parallel, and two, they are not really
//universes"
int main(int argc, char *argv[])
{
	//Program should have two args: password and salt
	//printf("%d\n",argc);
	
	if(argc != 3)
	return 0;
	
	char *salt_param;
	char *arg = argv[2];
	asprintf(&salt_param, "$6$");
	asprintf(&salt_param,"%s%s",salt_param,arg);
	asprintf(&salt_param,"%s%s",salt_param,"$");
	
	
	//Prepare for decryption
    struct crypt_data mydata;
    mydata.initialized = 0;
    // // // // 
    
    //printf("argv[1]: %s\n",argv[1]);
    //printf("salt: %s\n",salt_param);
    
    int i = 0;
    char *result;
    //while(100 > i++)
    //{
        result = crypt_r(argv[1],salt_param,&mydata);
        printf("%s",result);
    //}    
    
	int hash_file = open("hash.txt", O_CREAT | O_WRONLY );
	
	write(hash_file,result,256);
	close(hash_file);

	return 0;
}
