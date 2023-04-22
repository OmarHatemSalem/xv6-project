0250 struct buf;
0251 struct context;
0252 struct file;
0253 struct inode;
0254 struct pipe;
0255 struct proc;
0256 struct rtcdate;
0257 struct spinlock;
0258 struct sleeplock;
0259 struct stat;
0260 struct superblock;
0261 struct filtered_proc;
0262 
0263 
0264 // bio.c
0265 void            binit(void);
0266 struct buf*     bread(uint, uint);
0267 void            brelse(struct buf*);
0268 void            bwrite(struct buf*);
0269 
0270 // console.c
0271 void            consoleinit(void);
0272 void            cprintf(char*, ...);
0273 void            consoleintr(int(*)(void));
0274 void            panic(char*) __attribute__((noreturn));
0275 
0276 // exec.c
0277 int             exec(char*, char**);
0278 
0279 // file.c
0280 struct file*    filealloc(void);
0281 void            fileclose(struct file*);
0282 struct file*    filedup(struct file*);
0283 void            fileinit(void);
0284 int             fileread(struct file*, char*, int n);
0285 int             filestat(struct file*, struct stat*);
0286 int             filewrite(struct file*, char*, int n);
0287 int             filetruncate(struct file*, char*, int n);
0288 
0289 // fs.c
0290 void            readsb(int dev, struct superblock *sb);
0291 int             dirlink(struct inode*, char*, uint);
0292 struct inode*   dirlookup(struct inode*, char*, uint*);
0293 struct inode*   ialloc(uint, short);
0294 struct inode*   idup(struct inode*);
0295 void            iinit(int dev);
0296 void            ilock(struct inode*);
0297 void            iput(struct inode*);
0298 void            iunlock(struct inode*);
0299 void            iunlockput(struct inode*);
0300 void            iupdate(struct inode*);
0301 int             namecmp(const char*, const char*);
0302 struct inode*   namei(char*);
0303 struct inode*   nameiparent(char*, char*);
0304 int             readi(struct inode*, char*, uint, uint);
0305 void            stati(struct inode*, struct stat*);
0306 int             writei(struct inode*, char*, uint, uint);
0307 
0308 // ide.c
0309 void            ideinit(void);
0310 void            ideintr(void);
0311 void            iderw(struct buf*);
0312 
0313 // ioapic.c
0314 void            ioapicenable(int irq, int cpu);
0315 extern uchar    ioapicid;
0316 void            ioapicinit(void);
0317 
0318 // kalloc.c
0319 char*           kalloc(void);
0320 void            kfree(char*);
0321 void            kinit1(void*, void*);
0322 void            kinit2(void*, void*);
0323 
0324 // kbd.c
0325 void            kbdintr(void);
0326 
0327 // lapic.c
0328 void            cmostime(struct rtcdate *r);
0329 int             lapicid(void);
0330 extern volatile uint*    lapic;
0331 void            lapiceoi(void);
0332 void            lapicinit(void);
0333 void            lapicstartap(uchar, uint);
0334 void            microdelay(int);
0335 
0336 // log.c
0337 void            initlog(int dev);
0338 void            log_write(struct buf*);
0339 void            begin_op();
0340 void            end_op();
0341 
0342 // mp.c
0343 extern int      ismp;
0344 void            mpinit(void);
0345 
0346 // picirq.c
0347 void            picenable(int);
0348 void            picinit(void);
0349 
0350 // pipe.c
0351 int             pipealloc(struct file**, struct file**);
0352 void            pipeclose(struct pipe*, int);
0353 int             piperead(struct pipe*, char*, int);
0354 int             pipewrite(struct pipe*, char*, int);
0355 
0356 
0357 // proc.c
0358 int             cpuid(void);
0359 void            exit(void);
0360 int             fork(void);
0361 int             growproc(int);
0362 int             kill(int);
0363 struct cpu*     mycpu(void);
0364 struct proc*    myproc();
0365 void            pinit(void);
0366 void            procdump(void);
0367 void            scheduler(void) __attribute__((noreturn));
0368 void            sched(void);
0369 void            setproc(struct proc*);
0370 void            sleep(void*, struct spinlock*);
0371 void            userinit(void);
0372 int             wait(void);
0373 void            wakeup(void*);
0374 void            yield(void);
0375 int             getprocs(int*, int*); // added function
0376 int             getprocinfo(int, struct filtered_proc*); // added function
0377 int             nice(int pid, int priority); //added function
0378 
0379 // swtch.S
0380 void            swtch(struct context**, struct context*);
0381 
0382 // spinlock.c
0383 void            acquire(struct spinlock*);
0384 void            getcallerpcs(void*, uint*);
0385 int             holding(struct spinlock*);
0386 void            initlock(struct spinlock*, char*);
0387 void            release(struct spinlock*);
0388 void            pushcli(void);
0389 void            popcli(void);
0390 
0391 // sleeplock.c
0392 void            acquiresleep(struct sleeplock*);
0393 void            releasesleep(struct sleeplock*);
0394 int             holdingsleep(struct sleeplock*);
0395 void            initsleeplock(struct sleeplock*, char*);
0396 
0397 
0398 
0399 
0400 // string.c
0401 int             memcmp(const void*, const void*, uint);
0402 void*           memmove(void*, const void*, uint);
0403 void*           memset(void*, int, uint);
0404 char*           safestrcpy(char*, const char*, int);
0405 int             strlen(const char*);
0406 int             strncmp(const char*, const char*, uint);
0407 char*           strncpy(char*, const char*, int);
0408 
0409 // syscall.c
0410 int             argint(int, int*);
0411 int             argptr(int, char**, int);
0412 int             argstr(int, char**);
0413 int             fetchint(uint, int*);
0414 int             fetchstr(uint, char**);
0415 void            syscall(void);
0416 
0417 // timer.c
0418 void            timerinit(void);
0419 
0420 // trap.c
0421 void            idtinit(void);
0422 extern uint     ticks;
0423 void            tvinit(void);
0424 extern struct spinlock tickslock;
0425 
0426 // uart.c
0427 void            uartinit(void);
0428 void            uartintr(void);
0429 void            uartputc(int);
0430 
0431 // vm.c
0432 void            seginit(void);
0433 void            kvmalloc(void);
0434 pde_t*          setupkvm(void);
0435 char*           uva2ka(pde_t*, char*);
0436 int             allocuvm(pde_t*, uint, uint);
0437 int             deallocuvm(pde_t*, uint, uint);
0438 void            freevm(pde_t*);
0439 void            inituvm(pde_t*, char*, uint);
0440 int             loaduvm(pde_t*, char*, struct inode*, uint, uint);
0441 pde_t*          copyuvm(pde_t*, uint);
0442 void            switchuvm(struct proc*);
0443 void            switchkvm(void);
0444 int             copyout(pde_t*, uint, void*, uint);
0445 void            clearpteu(pde_t *pgdir, char *uva);
0446 
0447 // number of elements in fixed-size array
0448 #define NELEM(x) (sizeof(x)/sizeof((x)[0]))
0449 
