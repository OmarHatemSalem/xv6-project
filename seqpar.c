#include "types.h"
#include "stat.h"
#include "user.h"

const int N = 20;

int or(int a, int b);
int add(int a, int b);

int getCount(const char* path);

int* getArray(const char* path);
int sequential_compute(int* ndata, int n, int (*f)(int, int));
int parallel_compute(int* data, int n, int n_proc, int (*f)(int, int));

void test_optimal_nproc(const char* path);


int main()
{
    printf(1, "hi\n");
    int* rdata = getArray("data2.txt");
    printf(1, "hi 2\n");

    int n = getCount("data2.txt");
    printf(1, "hi 2\n");

    int t1,t2;
    t1 = uptime();
    // printf(1, "Length of File = %d\n", n);
    // for (int i=0; i<n; i++) printf(1, "File[%d] = %d\n", i, rdata[i]);
    int ans1 = sequential_compute(rdata, n, add);
    t1 = uptime() - t1;
    double time_taken_1 = ((double)t1)*100; ///100.0;
    printf(1, "Value of sequential = %d, time taken = ", ans1);
    printfloat(1, time_taken_1); printf(1, "\n");

    t2 = uptime();
    // printf(1, "Length of File = %d\n", n);
    // for (int i=0; i<n; i++) printf(1, "File[%d] = %d\n", i, rdata[i]);
    int ans2 = parallel_compute(rdata, n, 1, add);
    t2 = uptime() - t2;
    double time_taken_2 = ((double)t2)*100; ///100.0;
    printf(1, "Value of parallel = %d, time taken = ", ans2);
    printfloat(1, time_taken_2); printf(1, "\n");



    exit();
}

int or(int a, int b) {
    return a | b;
}

int add(int a, int b) {
    return a + b;
}

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

int* getArray(const char* path)
{
    int n = getCount(path);
    // printf(1,"n = %d\n", n);

    int  fp = open(path, 0);
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

int sequential_compute(int* data, int n, int (*f)(int, int)) {


    int a=0,b;

    for (int i=0; i<n; i++) {
        if (i==0) a = data[i];
        else {b = data[i]; a = f(a,b);}
    }

    return a;
}

int parallel_compute(int* ndata, int n, int n_proc, int (*f)(int, int))
{
    // clock_t t1,t2,t3;
    // t2 = clock();
    // t1 = clock();
    // t3 = clock();
    // printf("Finished reading at time=%lf, pid = %i\n", ((double)(t1-t2))/CLOCKS_PER_SEC, getpid());


    // int ppid = getpid();

    int ans = 0;
    int par_len = n%n_proc;
    for (int j=0; j<par_len; j++) {
        ans = f(ans, ndata[j]);
    }
    // printf("ans before = %i\n", ans);


    int cpid;
    int c_out;
    int start;
    // int** p12 = ((int*)malloc(n_proc*sizeof(int[2]));

    // int* p12[n_proc];
    int* p21[n_proc];
    for (int i = 0; i < n_proc; i++) {
        // p12[i] = (int*)malloc(2 * sizeof(int));
        p21[i] = (int*)malloc(2 * sizeof(int));    
    }

    //int p12[2], p21[2];
    for (int i=0; i<n_proc; i++) {
        start = par_len+i*(n/n_proc);
        
        if (/*pipe(p12[i]) == -1 ||*/ pipe(p21[i])==-1) {
            printf(2, "Error in Pipe\n");
            return -1;
        }

        // t1 = clock();
        cpid = fork();
        if (cpid > 0) {
            // close(p12[i][0]);
            // write(p12[i][1], &start, sizeof(int));
            // close(p12[i][1]);
        } else {
            // printf("child forked at time=%lf, pid = %i\n", ((double)(t1-t2))/CLOCKS_PER_SEC, getpid());
            // printf("child does not fork\n");
            break;
        }
    }


   

    int k = (start - par_len)/(n/n_proc);
    if (cpid == 0) {
        // printf("child created\n");
        // read(p12[0], &start, sizeof(int));
        c_out = ndata[start];
        for (int j=start+1; j<start+n/n_proc; j++) {
            c_out = f(c_out, ndata[j]);
        }

        // printf("start = %i\n", start);
        close(p21[k][0]);
        write(p21[k][1], &(c_out), sizeof(int));
        close(p21[k][1]);
        // t1 = clock();
        // printf("child finished at time=%lf, pid = %i\n", ((double)(t1-t2))/CLOCKS_PER_SEC, getpid());
        // printf("Wrote result = %i to parent in index = %i , pid =%i\n", c_out, k, getpid());
        exit();


    } else {
        while(wait() > 0);
        // wait(NULL);

        for (int k = 0; k<n_proc; k++) {
            close(p21[k][1]);
            read(p21[k][0], &(c_out), sizeof(int));
            // printf("ans before msg = %i\n", ans);
            // printf("parent received ans = %i, c_out = %i, k = %i, pid = %i\n", ans, c_out, k, getpid());
            ans = f(ans,c_out);
            close(p21[k][0]);
            // t1 = clock();
        }
        // printf("parent finished at time=%lf, pid = %i\n", ((double)(t1-t2))/CLOCKS_PER_SEC, getpid());
    }

    // for (int v=0; v<n_proc; v++) ans = printf("results[%i] = %i\n", v, nresults[v]);

    // for (int v=0; v<n_proc; v++) {ans = f(ans, nresults[v]); printf("ans = %i\n", ans); }
    // printf("finisehd exec, ans = %i, pid = %i\n", ans, getpid());
    // t3 = clock() - t3;
    // printf("calculation time=%lf, pid = %i\n", ((double)(t3))/CLOCKS_PER_SEC, getpid());
    return ans;
}