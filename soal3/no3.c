#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
 
/*************** PROTOTYPES ************************/
static void StripFileName(char *FileName, char *NewFileName, char *ekstensi);
void* makedir(void *data);
void* move(void *data);
void* thread(void *arg);
/**************************************************/
/***************** STRUCTS ************************/
struct v
{
    char *x[1];
    char *y[1];
    char *z[1];
};
/**************************************************/
/*************** GLOBAL VARIABLE ******************/
int status;
pthread_t tid[3];
/**************************************************/

int main(int argc, char* argv[])
{
    // Declare variable
    char FileName[31];
    char NewFileName[31];
    char ekstensi[5];
    char path[50];
    char bintang[] = "*";
    char f[] = "-f";
    char d[] = "-d";
    int i = 2;

    // argumen = -f
    if (strcmp (argv[1],f) == 0)
    {
        // ngeloop sebanyak argumen yang diminta
        for (; i < argc; i++)
        {
            // mencari nama file, ekstensi, dan path
            strcpy(FileName, argv[i]);
            StripFileName(FileName, NewFileName, ekstensi);
            strcat(NewFileName, ".");
            strcat(NewFileName, ekstensi);
            strcat(path, "/Users/samsudhuha/Desktop/sisop/shift3/");
            strcat(path, ekstensi);
            strcat(path, "/");

            // ditaruh dalam struct
            struct v *data = (struct v*) malloc (sizeof (struct v));
            *data -> x = NewFileName;
            *data -> y = ekstensi;
            *data -> z = path;

            int k = 0;
            status = 0;

            //membuat thread
            while (k<2)
            {
                if(k==0){
                    pthread_create(&(tid[k]),NULL,&makedir,(void *) data);
                } else {
                    pthread_create(&(tid[k]),NULL,&move,(void *) data);
                }
                k++;
            }
        }
        int k = 0;
        while (k<2)
        {
            pthread_join(tid[k],NULL);
            k++;
        }
    }

    if (strcmp (argv[1],bintang) == 0)
    {

    }
 
    if (strcmp (argv[1],d) == 0)
    {

    }
 
    return 0;
}
 
static void StripFileName(char *FileName, char *NewFileName, char *ekstensi)
{
    int PLocation;
    int i, j, x, y, z;
 
    i = strlen(FileName) - 1;
 
    /* LOOK FOR THE PERIOD OR THE BEGINNING OF THE FILE NAME */
    while (i && FileName[i] != '.')
    {
        i--;
    }
 
    /* IF I IS > 0, THE FILE NAME HAS A PERIOD */
    if (i)
    {
        PLocation = i;
    }
    else
    {
        /* NO PERIOD, SO COPY TO THE END OF THE FILE NAME */
        PLocation = strlen(FileName);
 
        /* RESET i TO LOOK FOR THE FIRST PATH NAME SEPARATOR, SINCE i WENT TO ZERO LOOKING FOR A PERIOD */
        i = strlen(FileName) - 1;
    }
 
    /* SEARCH FOR THE FIRST PATH NAME SEPARATOR, IF THERE IS ONE */
    while (i && FileName[i] != '/')
    {
        if (FileName[i] != '/')
            i--;
    }
 
    /* IF THERE IS A SEPARATOR, WE NEED TO GO FORWARD 1 CHARACTER */
    if (FileName[i] == '/')
        i++;
         
    x = 0;
    
    /* COPY FROM THE SEPARATOR (OR THE BEGINNING OF THE FILE NAME IF NO SEPARATOR) TO LOCATION OF THE PERIOD */
    while (i < PLocation)
    {
        NewFileName[x] = FileName[i];
        x++;
        i++;
    }
    /* COPY EKSTENSI */

    y = 0;
    j = strlen(FileName) - 1;
    while (i<j)
    {
        ekstensi[y] = FileName[i+1];
        y++;
        i++;
    }
    /* PLACE A NULL AT THE END WHEN WE'RE DONE COPYING */
    NewFileName[x] = '\0';
    ekstensi[y] = '\0';
}

void* makedir(void *param)
{
    struct v *par = (struct v*) param;

    status = 1;

    printf("masuk dir\n");
    char *mkdir[] = {"mkdir", "-p", *par -> y, NULL};
    execv("/bin/mkdir", mkdir);

	return NULL;
}

void* move(void *param)
{
    struct v *par = (struct v*) param;

    printf("masuk move\n");
    while (status != 1)
    {
        /* code */
    }
    
    char* move[] = {"mv", *par->x, *par->z, NULL};
    execv("/bin/mv", move);

	return NULL;
}
