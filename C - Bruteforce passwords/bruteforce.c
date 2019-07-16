//#SO2 IS1 210B LAB06
//#Przemyslaw Samsel 
//#sp39427@wi.zut.edu.pl

#define _GNU_SOURCE
#define _POSIX_SOURCE
#define _POSIC_C_SOURCE 199309L
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
#include <pthread.h>
#include <time.h>
#define RESET "\x1B[0m"
#define MAG   "\x1B[35m"
int liczbalinijek = 0;

pthread_mutex_t fastMutex = PTHREAD_MUTEX_INITIALIZER;
//int globalVariable = 0;
// For using ubuntu commands
// void clrscr()
// {
//     system("clear");
// }

typedef struct {
    char * passwordToBreak;
    char * begSalt;
    int    startRead;
    int    endRead;
    int    charsInFile;
    char * filename;
    int    progressedChars;
    int    doExperiment;
    char * foundPassword;
    int    matched;
}crawlArgs;

// Calculating time difference between two events
struct timespec diff(struct timespec start,struct timespec end)
{
	struct timespec temp;
	if ( 0 > (end.tv_nsec-start.tv_nsec) ) 
    {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} 
	else 
    {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
//

//Show progress bar
void showFilePercentage(int charsInFile, int progressed)
{
    sleep((float)(rand()%100)/100.f);
    float res = (float)progressed/charsInFile * 100;
    printf("Read %.2f%% of file.\n", res >= 100.f ? 100.f : res );
}

// Open file with specified filename, set buffer and ret pointer
FILE * readFileWithPasswords(char * fileBuf, char * filename)
{
    //Open file
	FILE * passfile = fopen(filename,"r");
    //Set pointer to beginning of file
    fseek(passfile,0,SEEK_SET);
    //Set buffersize for multiply of disk block capacity
    setbuffer(passfile,fileBuf,40960 * sizeof(char));
    
    return passfile;
}

//Get password, beginning positon and how many chars to read and start breaking password
void * crawlThroughFile(void * args)
{
    crawlArgs * aArgs = args;

    //Create pointer to file
    char * buffer = NULL;
    //Allocate memory for buffer
    buffer = (char *)calloc(40960,sizeof(char));
    FILE * fileToRead = readFileWithPasswords(buffer, aArgs->filename);
    
    // This contains read line from file - where there is one password per line
    char * lineToRead = NULL;
           lineToRead = (char *)calloc(100,sizeof(char));
           
    char * find_n;
	char * result;
    int    current = 0;
    
    //Prepare for decryption
    struct crypt_data mydata;
    mydata.initialized = 0;
    // //
    
    //Set file position 
    fseek(fileToRead,aArgs->startRead,SEEK_SET);
    
    while( NULL != fgets(lineToRead,100,fileToRead) && current < aArgs->endRead )//&& aArgs->progressedChars < aArgs->charsInFile)
	{
        
//      Find position of newline character
//      To clock up how many chars has already been read
        find_n = strchr(lineToRead,'\n');
 		current += find_n - lineToRead;
        
        pthread_mutex_lock(&fastMutex);
        
            int localAdd = aArgs->progressedChars;
            localAdd += (int) (find_n - lineToRead);
            liczbalinijek++;
            aArgs->progressedChars = localAdd;
            
            if(!aArgs->doExperiment)
            showFilePercentage(aArgs->charsInFile,aArgs->progressedChars);
        
        pthread_mutex_unlock(&fastMutex);        
        
        // Result is encrypted password from file - now we have to compare it 
        // With original password
        char * pString = NULL;
        pString = (char *)calloc((int)(find_n - lineToRead),sizeof(char));
        strncpy(pString,lineToRead,(int)(find_n - lineToRead));
        
		result = crypt_r(pString,aArgs->begSalt,&mydata);
		
        printf("Haslo do zlamania: %s\n",pString);
        printf("Hash arg: %s\n",aArgs->passwordToBreak);
        printf("Hash gen: %s\n",result);
        
        //Comparing two passwords
        if( 0 == strcmp(result,aArgs->passwordToBreak) && !aArgs->matched)
		{
            
            strcpy(aArgs->foundPassword,pString);
            aArgs->matched = 1;
            printf("result: %s\n",pString);
            //printf("result: %s\n",aArgs->passwordToBreak);
            int status;
            exit(status);
        }
		
		//Trace:


        free(pString);
        
    }
    
    free(buffer);
    //free(lcaineToRead);
    fclose(fileToRead);
}

char * getSaltBeginning(char *password)
{
    char * result;
    //Move to salt
	password = (password + 3);
	
	//Find position where salt ends
	char *find_dollar;
	find_dollar = strchr(password,'$');
	int salt_length = find_dollar-password;
	
	//Then copy our salt to new string
	result = (char *)calloc(salt_length + 5, sizeof(char));
	
    //Move to the beginning of password again
	password = (password-3);
	strncpy(result,password,salt_length+4);
    
    //Now we have string: $6$<SALT>$ to begin encryption
    return result;
}

int * countCharsInFile(FILE * filestr,int * charsInFile)
{
    //Move to beginning of file
    fseek(filestr,0,SEEK_SET);
    
    char * pass_string = (char *)calloc(100,sizeof(char));
	char * read_n;
    
    //Iterate through file to count all chars
	while( NULL != fgets(pass_string,100,filestr ))
    {
 		read_n = strchr(pass_string,'\n');
 		*charsInFile += read_n - pass_string;
	}	
	
	
	//TRACE: Print how many chars has been read
	//printf("Read: %d\n",*charsInFile);
    
    fseek(filestr,0,SEEK_SET);
    free(pass_string);
    
    return charsInFile;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
	//1 arg: hash
	//2    : textfile (with passwords) 
	//3    : number of threads
	
    //To calculate exec time
	struct timespec start, end;
    int maxThreads = sysconf(_SC_CHILD_MAX);
    
	if( ! ( argc == 4 || argc == 3 ))
	return 0;
    
    if( 4 == argc)
    {
        if ( atoi(argv[3]) >= maxThreads )
        {
            printf("You cannot create more threads than processors on-line. Cancelling.");
            return 0;
        }
    }
        
    //Get beginning of hash to encrypt
    char * saltBeginning;
    saltBeginning = getSaltBeginning(argv[1]);
    
    //Get number of total chars in file with passwords
    char * tempbuf;
    char * storefoundpass;
    int  * charsInFile;
    int  * progressedChars;
    
    charsInFile         =  (int *)calloc(1,sizeof(int));
    progressedChars     =  (int *)calloc(1,sizeof(int));
    tempbuf             =  (char *)calloc(40960,sizeof(char));
    storefoundpass      =  (char *)calloc(100,sizeof(char));
    FILE * filePass     =  readFileWithPasswords(tempbuf,argv[2]);
    
    countCharsInFile(filePass,charsInFile);
    free(tempbuf);
    //
    
    //Preparing arguments for breaking password function
    crawlArgs * nL1       = (crawlArgs *)malloc(sizeof(crawlArgs));
    
    nL1->passwordToBreak  = argv[1];
    nL1->begSalt          = saltBeginning;
    
    //Position in file to start
    nL1->startRead        = 0;
    //How many chars file contain
    nL1->charsInFile      = *charsInFile;
    nL1->filename         = argv[2];
    //Shows progress of reading file with passwords
    nL1->progressedChars  = *progressedChars;
    //If false, then number of threads are specified by user
    nL1->doExperiment     = 1;
    nL1->foundPassword    = storefoundpass;
    nL1->matched          = 0;
    
    //How many threads should create
    int     howManyThreads = 2;
    
    //Size of table
    int     threadsLimit = 1;
    int     resultCounter = 0;   
    
    float * ElapsedTT;
    int   * ThreadsC;
        
    //If user provided number of args
    if( 4 == argc )
    {
        //Then we don't do experiment
        nL1->doExperiment = 0;
        howManyThreads = atoi(argv[3]);
    }
    else
    {
        //Otherwise we do experiment for 9 threads
        threadsLimit = 9;
        //And 1% of passwords that file contains
        nL1->charsInFile = nL1->charsInFile * 0.01;
    }
        ElapsedTT = calloc(threadsLimit,sizeof(float));
        ThreadsC  = calloc(threadsLimit,sizeof(int));
   
    do
    {
        int temporary = 0;
        
        //Start!
        clock_gettime(CLOCK_MONOTONIC,&start);
        
        //Create proper number of threads
        pthread_t threadID[howManyThreads];
        //Each thread should read that number of chars
        nL1->endRead = *charsInFile/howManyThreads + 1;
    
        //Creating threads and each thread starts function crawlThroughFile
        for(int i = 0; i < howManyThreads; i++)
        {
            nL1->startRead = i * (*charsInFile/howManyThreads) - temporary;
            pthread_create (&threadID[i], NULL, crawlThroughFile, nL1);    
            temporary = 1;
        }
        
        //Waiting for finished of each thread
        for(int i = 0; i < howManyThreads; i++)
        {
            pthread_join(threadID[i],NULL);
        }
    
        //Stop!
        clock_gettime(CLOCK_MONOTONIC,&end);
        
        //Save results to table:
        ElapsedTT[resultCounter] = diff(start,end).tv_sec+diff(start,end).tv_nsec/1e9;
        ThreadsC[resultCounter]  = howManyThreads;
        
        //Increment number of threads
        howManyThreads++;
        resultCounter++;
        
        //Re-initialize global variable which contains number of chars read
        nL1->progressedChars = 0;
    }
    while (resultCounter < threadsLimit);
    
    //Calculate minimum time for threads
    float minimum=0;
    minimum = ElapsedTT[0];

    for(int j=0; j<threadsLimit; j++ )
    {
        if( ElapsedTT[j] < minimum )
        {
            minimum = ElapsedTT[j];
        }
            
    }
    // // //
    
    //Print results
    for(int j=0; j<threadsLimit; j++ )
    {
        if ( ElapsedTT[j] == minimum && nL1->doExperiment)
        {
            printf(MAG "Elapsed time: %.4fs for %d threads.\n",ElapsedTT[j],ThreadsC[j]);
            printf(RESET"");
        }
        else
        {
            printf("Elapsed time: %.4fs for %d threads.\n",ElapsedTT[j],ThreadsC[j]);
        }
    }
    
    if(!nL1->doExperiment && nL1->matched)
    {
        printf(MAG"Match! Password: %s\n",nL1->foundPassword);
    }
    //  //
    
    //Clean
    free(ElapsedTT);
    free(ThreadsC);
    free(progressedChars);
    free(charsInFile);
    free(saltBeginning);
    free(nL1);
    pthread_mutex_destroy(&fastMutex);
    printf("\n\nOdczytanych linii: %d",liczbalinijek);
	return 0;
}
//Program finish after: 
//a) match
//b) end of file
//no more threads than proceses sysconf(3)

//Number of pwd read in %
//Read passwords in blocks

//Without parameter threads:
//optymalna liczba wątków
//wykonuj obliczenia dla n hasel
//rozna ilosc watkow (mierzy czas - clock_gettime, pthread_getcpuclockid)

/////////////////////////

/* ftell example : getting size of a file */
//#include <stdio.h>
// FTELL -> current value of position i
// int main ()
// {
//   FILE * pFile;
//   long size;
// 
//   pFile = fopen ("myfile.txt","rb");
//   if (pFile==NULL) perror ("Error opening file");
//   else
//   {
//     fseek (pFile, 0, SEEK_END);   // non-portable
//     size=ftell (pFile);
//     fclose (pFile);
//     printf ("Size of myfile.txt: %ld bytes.\n",size);
//   }
//   return 0;
// }


	
// 	while ( 0 != retval )
// 	{
// 		retval = read(pass_file, buffer,sizeof(buffer));
// 		printf("%s \n",buffer);
//  		char *read_n;
//  		read_n = strchr(buffer,'\n');
//  		int gr = read_n - buffer;
//  		printf("-> %d\n",gr);
// 			printf("%s",buffer);
// 			char *password;
	
// 		while( '\0' != buffer )
// 		{
// 			char *read_n;
// 			read_n = strchr(buffer,'\n');
// 			int linelength = read_n - buffer;
// 			int linelength = strspn(buffer,n);
// 			printf("%d \n",linelength);
// 			buffer = buffer + linelength;
// 			
// 		}
//  			password = (char *)calloc(linelength+1, sizeof(char));
// 			strncpy(password,buffer,linelength);
// 			printf("pas: %s\n",password+1);
// 			buffer = buffer + linelength;
// 			free(password);
// 		
// 		buffer = (buffer + (gr));
// 		printf("PA: %s\n",password);
// 		/*while(read_n != NULL)
// 		{
// 			read_n = strchr(buffer,'\n');
// 		
// 			password = (char *)malloc(sizeof(read_n-buffer+1));
// 			strncpy(password,buffer,read_n-buffer);
// 			buffer = (buffer + (read_n-buffer));
// 			printf("PA: %s\n",password);
// 			free(password);
// 		}*/	
// 	}
// 	
	//zwolnij pamiec po tych mallocach!
	

	//struct crypt_data data[1] = {0};
	//char *result;
	//result = crypt_r(argv[1],argv[2],data);
	
	

	//printf(" %s \n",result);
