3900 #include "types.h"
3901 #include "x86.h"
3902 #include "defs.h"
3903 #include "date.h"
3904 #include "param.h"
3905 #include "memlayout.h"
3906 #include "mmu.h"
3907 #include "proc.h"
3908 
3909 int
3910 sys_fork(void)
3911 {
3912   return fork();
3913 }
3914 
3915 int
3916 sys_exit(void)
3917 {
3918   exit();
3919   return 0;  // not reached
3920 }
3921 
3922 int
3923 sys_wait(void)
3924 {
3925   return wait();
3926 }
3927 
3928 int
3929 sys_kill(void)
3930 {
3931   int pid;
3932 
3933   if(argint(0, &pid) < 0)
3934     return -1;
3935   return kill(pid);
3936 }
3937 
3938 int
3939 sys_getpid(void)
3940 {
3941   return myproc()->pid;
3942 }
3943 
3944 
3945 
3946 
3947 
3948 
3949 
3950 int
3951 sys_sbrk(void)
3952 {
3953   int addr;
3954   int n;
3955 
3956   if(argint(0, &n) < 0)
3957     return -1;
3958   addr = myproc()->sz;
3959   if(growproc(n) < 0)
3960     return -1;
3961   return addr;
3962 }
3963 
3964 int
3965 sys_sleep(void)
3966 {
3967   int n;
3968   uint ticks0;
3969 
3970   if(argint(0, &n) < 0)
3971     return -1;
3972   acquire(&tickslock);
3973   ticks0 = ticks;
3974   while(ticks - ticks0 < n){
3975     if(myproc()->killed){
3976       release(&tickslock);
3977       return -1;
3978     }
3979     sleep(&ticks, &tickslock);
3980   }
3981   release(&tickslock);
3982   return 0;
3983 }
3984 
3985 // return how many clock tick interrupts have occurred
3986 // since start.
3987 int
3988 sys_uptime(void)
3989 {
3990   uint xticks;
3991 
3992   acquire(&tickslock);
3993   xticks = ticks;
3994   release(&tickslock);
3995   return xticks;
3996 }
3997 
3998 
3999 
4000 int
4001 sys_getprocs(void)
4002 {
4003   int *st;
4004   int *count;
4005   if(argptr(0, (void*)&st, sizeof(st)) < 0 || argptr(1, (void*)&count, sizeof(*st)) < 0)
4006     return -1;
4007 
4008   return getprocs(st, count);
4009 }
4010 
4011 int
4012 sys_getprocinfo(void)
4013 {
4014   int pid;
4015   struct filtered_proc *st;
4016   if(argint(0, &pid) < 0)
4017     return -1;
4018   // use argstr to check if second argument is a valid string
4019   // char *tmp = name;
4020   if((argptr(1, (void*)&st, sizeof(st)) < 0))
4021     return -1;
4022 
4023   return getprocinfo(pid, st);
4024 }
4025 
4026 int
4027 sys_date(void){
4028   struct rtcdate *myDate;
4029 
4030     if(argptr (0 , (void*)&myDate ,sizeof(*myDate)) < 0 ){
4031       cprintf("Error in sys_getali, yo\n");
4032       return -1;
4033     };
4034 
4035   cmostime(myDate);
4036 
4037   return 0;
4038 }
4039 
4040 
4041 
4042 
4043 
4044 
4045 
4046 
4047 
4048 
4049 
4050 int
4051 sys_set_priority(void) {
4052   int pid;
4053   int priority;
4054 
4055   if(argint(0, &pid) < 0 || argint(0, &priority) < 0)
4056     return -1;
4057 
4058   return nice(pid, priority);
4059   // return 0;
4060 }
4061 
4062 
4063 
4064 
4065 
4066 
4067 
4068 
4069 
4070 
4071 
4072 
4073 
4074 
4075 
4076 
4077 
4078 
4079 
4080 
4081 
4082 
4083 
4084 
4085 
4086 
4087 
4088 
4089 
4090 
4091 
4092 
4093 
4094 
4095 
4096 
4097 
4098 
4099 
