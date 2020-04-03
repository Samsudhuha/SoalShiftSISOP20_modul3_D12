#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h> 
#include<dirent.h>
// #include <dir.h>
#define MAX 256
 
/*************** PROTOTYPES ************************/
static void StripFileName(char *FileName, char *NewFileName, char *ekstensi);
static void taruhvariable(char *NewFileName, char *ekstensi, char *pathawal, char *pathakhir, char* unknown);
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
    char *za[1];
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
    char pathawal[100];
    char pathakhir[100];
    char unknown[10];
    char bintang[] = "*";
    char f[] = "-f";
    char d[] = "-d";
    int i = 2;
    strcpy(unknown, "Unknown");
    // argumen = -f
    if (strcmp (argv[1],f) == 0)
    {
        // ngeloop sebanyak argumen yang diminta
        for (; i < argc; i++)
        {
            // memset
            memset(FileName, 0, sizeof(FileName));
            memset(NewFileName, 0, sizeof(NewFileName));
            memset(ekstensi, 0, sizeof(ekstensi));
            memset(pathawal, 0, sizeof(pathawal));
            memset(pathakhir, 0, sizeof(pathakhir));

            // mencari nama file, ekstensi, dan path
            strcpy(FileName, argv[i]);

            StripFileName(FileName, NewFileName, ekstensi);
            int cek = strlen(ekstensi);
            taruhvariable(NewFileName, ekstensi, pathawal, pathakhir, unknown);

            // ditaruh dalam struct
            struct v *data = (struct v*) malloc (sizeof (struct v));
            *data -> x = NewFileName;
            if (cek != 0)
            {
                *data -> y = ekstensi;
            } else {
                *data -> y = unknown;
            }
            *data -> z = pathawal;
            *data -> za = pathakhir;

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
                pthread_join(tid[k],NULL);
                k++;
            }
        }
    }

    if (strcmp (argv[1],bintang) == 0)
    {
        DIR *dir;
        struct dirent *ent;
        int i = 0;
        if ((dir = opendir ("/Users/samsudhuha/Desktop/sisop/shift3/kategori")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (i >= 2)
            {
                printf ("%s\n", ent->d_name);
                memset(FileName, 0, sizeof(FileName));
                memset(NewFileName, 0, sizeof(NewFileName));
                memset(ekstensi, 0, sizeof(ekstensi));
                memset(pathawal, 0, sizeof(pathawal));
                memset(pathakhir, 0, sizeof(pathakhir));

                strcpy(FileName, ent->d_name);
                StripFileName(FileName, NewFileName, ekstensi);
                int cek = strlen(ekstensi);
                taruhvariable(NewFileName, ekstensi, pathawal, pathakhir, unknown);

                struct v *data = (struct v*) malloc (sizeof (struct v));
                *data -> x = NewFileName;
                if (cek != 0)
                {
                    *data -> y = ekstensi;
                } else {
                    *data -> y = unknown;
                }
                *data -> z = pathawal;
                *data -> za = pathakhir;

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
                    pthread_join(tid[k],NULL);
                    k++;
                }
            }
            i++;
        }
        closedir (dir);
        } else {
        /* could not open directory */
        perror ("didn't get directory");
        return EXIT_FAILURE;
        }
    }
 
    if (strcmp (argv[1],d) == 0)
    {

    }
 
    return 0;
}

static void taruhvariable(char *NewFileName, char *ekstensi, char *pathawal, char *pathakhir, char* unknown)
{
    int cek = strlen(ekstensi);
    if (cek != 0)
    {
        strcat(NewFileName, ".");
        strcat(NewFileName, ekstensi);
        strcat(pathawal, "/Users/samsudhuha/Desktop/sisop/shift3/kategori/");
        strcat(pathawal, NewFileName);
        strcat(pathakhir, "/Users/samsudhuha/Desktop/sisop/shift3/");
        strcat(pathakhir, ekstensi);
        strcat(pathakhir, "/");
        strcat(pathakhir, NewFileName);
    } else {
        strcat(pathawal, "/Users/samsudhuha/Desktop/sisop/shift3/kategori/");
        strcat(pathawal, NewFileName);
        strcat(pathakhir, "/Users/samsudhuha/Desktop/sisop/shift3/");
        strcat(pathakhir, unknown);
        strcat(pathakhir, "/");
        strcat(pathakhir, NewFileName);
    }
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

    mkdir(*par->y, 0777);

	return NULL;
}

void* move(void *param)
{
    struct v *par = (struct v*) param;

    while (status != 1)
    {

    }
    
    int ch;
    FILE *fp1, *fp2;

    fp1 = fopen(*par->z, "r");
    fp2 = fopen(*par->za, "w");

    /* error handling */
    if (!fp1) {
            printf("Unable to open source file to read!!\n");
            fclose(fp2);
            return 0;
    }
    if (!fp2) {
            printf("Unable to open target file to write\n");
            return 0;
    }
    /* copying contents of source file to target file */
    while ((ch = fgetc(fp1)) != EOF) {
            fputc(ch, fp2);
    }
    /* closing the opened files */
    fclose(fp1);
    fclose(fp2);
    /* removing the source file */
    remove(*par->z);

	return NULL;
}
