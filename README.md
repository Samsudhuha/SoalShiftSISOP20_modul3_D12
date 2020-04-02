Kelompok D12

Yulia Niza    05111840000053

Samsu Dhuha   05111840000155


### Soal 3 
#### Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.


```
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/stat.h> 
#define MAX 256
 
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
    char pathawal[50];
    char pathakhir[50];
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
            // memset
            memset(FileName, 0, sizeof(FileName));
            memset(NewFileName, 0, sizeof(NewFileName));
            memset(ekstensi, 0, sizeof(ekstensi));
            memset(pathawal, 0, sizeof(pathawal));
            memset(pathakhir, 0, sizeof(pathakhir));

            // mencari nama file, ekstensi, dan path
            strcpy(FileName, argv[i]);
            StripFileName(FileName, NewFileName, ekstensi);
            strcat(NewFileName, ".");
            strcat(NewFileName, ekstensi);
            strcat(pathawal, "/Users/samsudhuha/Desktop/sisop/shift3/");
            strcat(pathawal, NewFileName);
            strcat(pathakhir, "/Users/samsudhuha/Desktop/sisop/shift3/");
            strcat(pathakhir, ekstensi);
            strcat(pathakhir, "/");
            strcat(pathakhir, NewFileName);

            // ditaruh dalam struct
            struct v *data = (struct v*) malloc (sizeof (struct v));
            *data -> x = NewFileName;
            *data -> y = ekstensi;
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

```


### Soal 4. 
#### 4a. Batu mulia pertama. Emerald. Batu mulia yang berwarna hijau mengkilat. Pada batu itu Ia menemukan sebuah kalimat petunjuk. Ada sebuah teka-teki yang berisi:

##### 1. Buatlah program C dengan nama "4a.c", yang berisi program untukmelakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).
##### 2. Tampilkan matriks hasil perkalian tadi ke layar.

++ Mendefinisikan ukuran matriks dan isi matriks
```
#define M 4
#define K 2
#define N 5
#define NUM_THREADS M * N
int (*value)[10];

/* Global variables for threads to share */
int A[M][K] = {{0,1},
               {2,3},
               {4,5},
               {6,7}
              };
int B[K][N] = {{1,1,1,1,1}, 
               {1,1,1,1,1}
              };

```

++ Struct untuk passing data ke threads
```
struct v
{
	int i; /* row */
	int j; /* column */
};
```
++ Membuat shared memory
```
  key_t key = 1234;
    int shmid = shmget(key, sizeof(int[10][10]), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);
```

++ Membuat M*N bekerja di thread
```
for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++) 
		{
			struct v *data = (struct v *) malloc(sizeof(struct v));
			data->i = i;
			data->j = j;
			/* create the thread passing it data as a paramater*/
			pthread_create(&workers[thread_counter], NULL, runner, data);
			pthread_join(workers[thread_counter], NULL);
			thread_counter++;
		}
	}
```

++ Menunggu threads selesa mengalikan
```
for (i = 0; i < NUM_THREADS; i++)
	{
	    pthread_join(workers[i], NULL);
	}
	
	for(i = 0; i < M; i++)
	{ 
		for(j = 0; j < N; j++)
		{ 
			printf("%d\t", value[i][j]);
		}
		printf("\n");
	}
```


++ Casting paramater ke struct v pointer

```
void *runner(void *ptr)
{	
	struct v *data = ptr;
	int i, sum = 0;
	
	for(i = 0; i < K; i++)
	{	
		sum += A[data->i][i] * B[i][data->j];
	}
	
	value[data->i][data->j] = sum;
	pthread_exit(0);
}

```



#### 4b.
##### 1. Buatlah program C kedua dengan nama "​ 4b.c​ ". Program ini akan mengambil variabel ​ hasil perkalian matriks dari program "4a.c" (program sebelumnya), dan tampilkan hasil matriks tersebut ke layar.(​ Catatan!​ : gunakan shared memory)  
##### 2. Setelah ditampilkan, berikutnya untuk setiap angka dari matriks tersebut, carilah nilai ​ faktorialnya​ , dan tampilkan hasilnya ke layar dengan format seperti matriks.

++ M embuat terminasi thread dan melakukan join thread
```
void pthread_exit(void *rval_ptr);
int pthread_join(pthread_t thread, void **rval_ptr);
pthread_t thread1;

```

++ Membuat Shared memory
```
 key_t key = 1234;
    int (*value)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);

```
++ Menampilkan matriks
```
 int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%d\t", value[i][j]);
		}
		printf("\n");
	}

```

++ Menampilkan hasil faktorial dari thread 
```
int buat_thread;
	buat_thread = pthread_create(&thread1, NULL, buat_factorial, NULL);
	pthread_join(thread1,NULL);
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%llu\t", hasil_factorial[i][j]);
		}
		printf("\n");
	}

```

++ Membuat fungsi thread faktorial

```
void *buat_factorial()
{
    key_t key = 1234;
    int (*value)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);

	int i,j,k;
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			unsigned long long f=1;
			for(k=1;k<=value[i][j];k++)
			{
				f= f+k;
				hasil_factorial[i][j] = f-1;
			}
		}
	}
}

```



#### 4c
#### 1. Buatlah program C ketiga dengan nama " 4c.c ". Program ini tidak memiliki hubungan terhadap program yang lalu.
#### 2. Pada program ini, Norland diminta mengetahui jumlah file dan folder di direktori saat ini dengan command " ls | wc -l ". Karena sudah belajar IPC, Norland mengerjakannya dengan semangat.( Catatan! : Harus menggunakan IPC Pipes)

++ Mendeklarasikan pipe dan fork
```
int p[2];
  pipe(p);
  int pid = fork();

```

++ Fork pada parent yang menrima inputan dari child yang dihubungkan dengan pipe
```
if (pid == 0) // parent
    {
      // p[0] read
      dup2(p[0], 0);
      close(p[1]);
      char *argv[] = {"wc", "-l", NULL};
      execv("/usr/bin/wc", argv);
    }

```
++ Child process untuk menampilkan ls
```
 else //child
    { 
      //p[0] write
      dup2(p[1], 1);
      close(p[0]);
      char *argv[] = {"ls", NULL};
      execv("/bin/ls", argv);
    }

```

