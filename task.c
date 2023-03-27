#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"
#include "fcntl.h"

const int N = 20;

int or(int a, int b);
int add(int a, int b);

int getCount(const char* path);

int sequential_compute(const char* path, int (*f)(int, int));
int parallel_compute(const char* path, int n_proc, int (*f)(int, int));

// int getCount(const char* path);
int* getArray(const char* path);

double time_sequential_compute(const char* path, int (*f)(int, int));
double time_parallel_compute(const char* path, int n_proc, int (*f)(int, int));

// void test_optimal_nproc(const char* path, const char* outPath);

// int find_optimal_n(const char* outfile_path);
// void find_optimal_nproc(const char* infile_path, const char* outfile_path);

// void generate_data_file(const char* path, int n);

int main(int argc, char* argv[])
{
    if(argc < 2){
        printf(1,"Insufficient number of arguments; please specify a path\n");
        exit();
    }
    char *path = argv[1];
    int sequential_answer;
    int parallel_answer;
// char path = "data2.txt";
    parallel_answer = parallel_compute(path,10, add);
    sequential_answer = sequential_compute(path, add);
    // printf(1, "sequential answer: %d\n", sequential_answer);

    double time_sequential;
    double time_parallel;
    printf(1,"sequential_answer = %d\n, parallel_answer = %d\n", sequential_answer, parallel_answer);

    time_sequential = time_sequential_compute(path, add);
    // printf(1, "time taken by sequential: %d\n", time_sequential);
    time_parallel = time_parallel_compute(path, 10, add);

    printf(1, "time taken by sequential = ");
    printfloat(1, time_sequential); printf(1, "\n");

    printf(1, "time taken by parallel = ");
    printfloat(1, time_parallel); printf(1, "\n");
    // printf(1,"time_sequential = %d, time_parallel = %d\n", time_sequential, time_parallel);
    exit();
}


int or(int a, int b) {
    return a | b;
}

int add(int a, int b) {
    return a + b;
}

int sequential_compute(const char* path, int (*f)(int, int)) {
    int n = getCount(path);
    int* rData = getArray(path); 

    int a=0, b;
    for (int i = 0; i < n; i++)
    {
        if(i==0){
            a = rData[i];
        }
        else{
            b = rData[i];
            a = f(a,b);
        }
        /* code */
    }
    
    // FILE* fp;
    // fp = fopen(path, "r");
    // int  fp = open(path, 0);
    // int* ndata = (int*) malloc(n*sizeof(int));

    // // char data[N];
    // char dig;
    // int i = 0, j = 0;

    // int a,b;
    // int i=0;

    // while(n)
    

    // if (fp == NULL) {
    //     printf(1,"The filename does not exist\n");   
    //     return -1;
    // } else {
    //     while (fgets(data, N, fp) != NULL) {
    //         if (i==0) 
    //             a = atoi(data);
    //         else {
    //             b = atoi(data);
    //             a = f(a,b);
    //         }
    //         i++;
    //     }
    // }

    // fclose(fp);

    return a;
}

int parallel_compute(const char* path, int n_proc, int (*f)(int, int))
{
    int n = getCount(path);
    // FILE* fp;
    // fp = fopen(path, "r");
    int* ndata = (int*) malloc(n*sizeof(int));

    char* data = (char*) malloc(N*sizeof(char));

    // int j=0;

    ndata = getArray(path);

    // if (fp == NULL) {
    //     printf(1,"The filename does not exist\n");   
    //     return -1;
    // } else {
    //     while (fgets(data, N, fp) != NULL) {
    //         ndata[j] = atoi(data);
    //         j++;
    //     }
    // }

    // int ppid = getpid();

    int ans = 0;
    int rem = n%n_proc;

    int cpid;
    int c_out;
    int start;
    int* p21[n_proc];

    for (int i = 0; i < n_proc; i++) {
        p21[i] = (int*)malloc(2 * sizeof(int));    
    }

        // struct filtered_proc* p;
        // p = malloc(sizeof(struct filtered_proc));

    for (int i=0; i<n_proc; i++) {
        start = i*(n/n_proc);
        // printf(1,"i = %d\n", i);
        // printf(1, "start = %d\n", start);
        // printf(1,"PID of this process %d\n",getpid());
        // getprocinfo(getpid(),p);
        // printf(1, "Process Memory (in bytes): %d\n",p->sz );
        if (pipe(p21[i]) == -1) {

            printf(2,"Error in Pipe\n");
            return -1;
        }

        cpid = fork();

        if(cpid == 0)
            break;

    }

    int k = start/(n/n_proc);
    if (cpid == 0) {
        c_out = ndata[start];
        for (int j=start+1; j<start+n/n_proc; j++) {
            c_out = f(c_out, ndata[j]);
        }
        if(k == n_proc-1) {
            for (int j=0; j<rem; j++) {
                c_out = f(c_out, ndata[n-rem+j]);
            }
        }
        close(p21[k][0]);
        write(p21[k][1], &(c_out), sizeof(int));
        close(p21[k][1]);
        exit();
    } else {
        //removed the NULL arg to wait()
        while(wait() > 0);
        for (int k = 0; k<n_proc; k++) {
            close(p21[k][1]);
            read(p21[k][0], &(c_out), sizeof(int));
            ans = f(ans,c_out);
            close(p21[k][0]);
        }
    }

    free(ndata);
    free(data);
    // fclose(fp);
    for(int i=0; i<n_proc; i++) {
        free(p21[i]);
    }

    return ans;
}

double time_sequential_compute(const char* path, int (*f)(int, int)) 
{
    int a,b;
    int* data = getArray(path);
    int n = getCount(path);

    // clock_t time = clock();
    int time = uptime();

    for (int i=0; i<n; i++) {
        if(i==0) 
            a = data[i];
        else {
            b = data[i];
            a = f(a,b);
        }
    }
    int timeTwo = uptime() - time;
    // time = clock() - time;
    // double time_taken = ((double)time)/CLOCKS_PER_SEC;
    double time_taken = ((double)timeTwo) * 100;

    free(data);

    return time_taken;
}

double time_parallel_compute(const char* path, int n_proc, int (*f)(int, int))
{
    int* ndata = getArray(path);
    int n = getCount(path);

    // int ppid = getpid();

    // clock_t time = clock();
    int time = uptime();

    int ans = 0;
    int rem = n%n_proc;
    int cpid;
    int c_out;
    int start;

    int* p21[n_proc];

    for (int i = 0; i < n_proc; i++) {
        p21[i] = (int*)malloc(2 * sizeof(int));    
    }

    for (int i=0; i<n_proc; i++) {
        start = i*(n/n_proc);  
        if (pipe(p21[i])==-1) {
            printf(1,"Error in Pipe\n");
            return -1;
        }
        cpid = fork();
        if(cpid == 0)
            break;
    }

    int k = start/(n/n_proc);
    if (cpid == 0) {
        c_out = ndata[start];
        for (int j=start+1; j<start+n/n_proc; j++) {
            c_out = f(c_out, ndata[j]);
        }

        if(k == n_proc-1) {
            for (int j=0; j<rem; j++) {
                c_out = f(c_out, ndata[n-rem+j]);
            }
        }

        close(p21[k][0]);
        write(p21[k][1], &(c_out), sizeof(int));
        close(p21[k][1]);
        exit();
    } else {
        while(wait() > 0);

        for (int k = 0; k<n_proc; k++) {
            close(p21[k][1]);
            read(p21[k][0], &(c_out), sizeof(int));
            ans = f(ans,c_out);
            close(p21[k][0]);
        }
    }

    int timeTwo = uptime() - time;
    // time = clock() - time;
    // double time_taken = ((double)time)/CLOCKS_PER_SEC;
    double time_taken = ((double)timeTwo)*100;


    free(ndata);
    for(int i=0; i<n_proc; i++) {
        free(p21[i]);
    }

    return time_taken;
}

// void test_optimal_nproc(const char* path, const char* outPath)
// {
//     FILE* fp;
//     double trial[10];
//     fp = fopen(outPath, "w+");

//     for (int i=1; i<=10; i++) {
//         for (int j=0; j<5; j++) {
//             // clock_t t1, t2;
//             int t1, t2;
//             t1 = clock();
//             int ans1 = sequential_compute(path, or);
//             t1 = clock() - t1;
//             double time_taken_1 = ((double)t1)*100; // in seconds
//             trial[j] = time_taken_1;

//             t2 = clock();
//             int ans2 = parallel_compute(path, i, or);
//             t2 = clock() - t2;
//             double time_taken_2 = ((double)t2)*100; // in seconds    
//             trial[5+j] = time_taken_2;
//         }

//         for (int k=0; k<10; k++) {
//             // fprintf(fp, "%lf,", trial[k]);
//             printf(1,"%lf,", trial[k]);
//         }
//         // fprintf(fp,"\n");
//         printf(1,"\n");

//     }

//     fclose(fp);
// }


int getCount(const char* path)
{

    int filed = open(path, 0);
    // if (filed != -1) {printf(1, "opened file\n");} else {printf(1, "open failed\n");}
    // int* nresults = (int*) malloc((n_proc)*sizeof(int));

    char data;

    int j=1;

    int n;
    while((n = read(filed, &data, sizeof(data))) > 0) {
        if (data == '\n') j++;
    }

    close(filed);

    return j;
}


// int getCount(const char* path)
// {

//     FILE* fp;
//     fp = fopen(path, "r");

//     char data[N];

//     int j=0;

//     if (fp == NULL) {
//         printf(1,"The filename does not exist\n");   
//         return -1;
//     } else {
//         while (fgets(data, N, fp) != NULL) {
//             j++;
//         }
//     }
//     fclose(fp);

//     return j;
// }

int* getArray(const char* path)
{
    int n = getCount(path);
    // printf(1,"n = %d\n", n);

    int  fp = open(path, 0);
    if(fp < 0 ){
        printf(1,"File \"%s\" not found; please, try again\n", path);
        exit();
    }
    int* ndata = (int*) malloc(n*sizeof(int));
    // int* nresults = (int*) malloc((n_proc)*sizeof(int));

    char data[N];
    char dig;

    int j=0;
    int i=0;

   
    while ((n = read(fp, &dig, sizeof(dig))) > 0) {
        
        if (dig == '\n') {
            ndata[j] = atoi(data);
            // for (int k=0; k<N; k++) {printf(1, "%c", data[i]);}
            // strcpy(data, "");
            memset(data, '\0', N);
            i=0;
            j++;
        } else {
            data[i] = dig;
            i++;
        }
    }

    ndata[j] = atoi(data);


    return ndata; 
}

// // int* getArray(const char* path)
// // {
// //     int n = getCount(path);

// //     FILE* fp;
// //     fp = fopen(path, "r");
// //     int* ndata = (int*) malloc(n*sizeof(int));

// //     char* data = (char*) malloc(N*sizeof(char));

// //     int j=0;

// //     if (fp == NULL) {
// //         printf(1,"The filename does not exist\n"); 
// //         return NULL; 
// //     } else {
// //         while (fgets(data, N, fp) != NULL) {
// //             ndata[j] = atoi(data);
// //             j++;
// //         }
// //     }

// //     free(data);
// //     fclose(fp);   

// //     return ndata; 
// // }

// int find_optimal_n(const char* outfile_path)
// {
//     int optimal_n = 50000000;
//     double optimal_time = 1000000;
//     // FILE* fp;
//     int fp;
//     int ns[50];
//     double sequential_times[50];
//     double parallel_times[50];   
//     printf(1,"\n");
//     printf(1,"Optimal N:\n");
//     printf(1,"n, sequential_time, parallel_time\n");
//     for(int n=1000000; n<=50000000; n += 1000000) {
//         if((fp = open("temp.txt", O_CREATE | O_RDWR)) < 0 ){
//         printf(1, "Error creating file");
//     }
//         // fp = fopen("temp.txt", "w");
//         int randomNum = -1;
//         for(int i=0; i<n; i++)
//         randomNum = rand(); 
//         char lineBreak = "\n";
//             write(fp, randomNum,sizeof(randomNum));
//             write(fp, lineBreak,sizeof(lineBreak));
//             // fprintf(fp, "%d\n", rand());
//         close(fp);
//         double t1 = time_sequential_compute("temp.txt", or);
//         double t2 = time_parallel_compute("temp.txt", 15, or);
//         ns[(n-1000000)/1000000] = n;
//         sequential_times[(n-1000000)/1000000] = t1;
//         parallel_times[(n-1000000)/1000000] = t2;
//         if (t2 < t1 && t2 < optimal_time) {
//             optimal_n = n;
//             optimal_time = t2;
//         }
//         printf(1,"%d, %lf, %lf\n", n, t1, t2);
//     }
//     int fp;
//     if((fp = open(outfile_path, O_CREATE | O_RDWR)) < 0 ){
//         printf(1, "Error creating file");
//     }
//     // FILE* out_fp = fopen(outfile_path, "w");
//     char fileColumns [] = "n, sequential_time, parallel_time\n";
//     write(fp,fileColumns, sizeof(fileColumns));
//     // fprintf(out_fp, "n, sequential_time, parallel_time\n");
//     for(int i=0; i<50; i++) {
        
//         write(fp,)
//         // fprintf(out_fp, "%d, %lf, %lf\n", ns[i], sequential_times[i], parallel_times[i]);
//     }
//     fclose(out_fp);
//     return optimal_n;
// }

// void find_optimal_nproc(const char* infile_path, const char* outfile_path)
// {
//     double parallel_times[100][10];
//     double sequential_times[100][10];
//     for(int i=1; i<=100; i++)
//     {
//         for(int j=0; j<10; j++)
//         {
//             sequential_times[i-1][j] = time_sequential_compute(infile_path, or);
//             parallel_times[i-1][j] = time_parallel_compute(infile_path, i, or);
//             printf(1,"n_procs: %d, trial: %d, sequential_time: %lf, parallel_time: %lf\n", i, j, sequential_times[i-1][j], parallel_times[i-1][j]);
//         }
//     }
//     FILE* out_fp = fopen(outfile_path, "w");
//     fprintf(out_fp, "n_procs, sequential_time1, sequential_time2, sequential_time3, sequential_time4, sequential_time5, sequential_time6, sequential_time7, sequential_time8, sequential_time9, sequential_time10, parallel_time1, parallel_time2, parallel_time3, parallel_time4, parallel_time5, parallel_time6, parallel_time7, parallel_time8, parallel_time9, parallel_time10\n");
//     for(int i=1; i<=100; i++)
//     {
//         fprintf(out_fp, "%d, ", i);
//         for(int j=0; j<10; j++)
//         {
//             fprintf(out_fp, "%lf, ", sequential_times[i-1][j]);
//         }
//         for(int j=0; j<10; j++)
//         {
//             fprintf(out_fp, "%lf, ", parallel_times[i-1][j]);
//         }
//         fprintf(out_fp, "\n");
//     }
//     fclose(out_fp);
// }

// void generate_data_file(const char* path, int n)
// {
//     FILE* fp;
//     fp = fopen(path, "w");
//     for(int i=0; i<n; i++)
//         fprintf(fp, "%d\n", rand());
//     fclose(fp);
// }

