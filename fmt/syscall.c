3700 #include "types.h"
3701 #include "defs.h"
3702 #include "param.h"
3703 #include "memlayout.h"
3704 #include "mmu.h"
3705 #include "proc.h"
3706 #include "x86.h"
3707 #include "syscall.h"
3708 // #include <errno.h>
3709 // #include <sys/types.h>
3710 // #include <unistd.h>
3711 
3712 // User code makes a system call with INT T_SYSCALL.
3713 // System call number in %eax.
3714 // Arguments on the stack, from the user call to the C
3715 // library system call function. The saved user %esp points
3716 // to a saved program counter, and then the first argument.
3717 
3718 // Fetch the int at addr from the current process.
3719 int
3720 fetchint(uint addr, int *ip)
3721 {
3722   struct proc *curproc = myproc();
3723 
3724   if(addr >= curproc->sz || addr+4 > curproc->sz)
3725     return -1;
3726   *ip = *(int*)(addr);
3727   return 0;
3728 }
3729 
3730 // Fetch the nul-terminated string at addr from the current process.
3731 // Doesn't actually copy the string - just sets *pp to point at it.
3732 // Returns length of string, not including nul.
3733 int
3734 fetchstr(uint addr, char **pp)
3735 {
3736   char *s, *ep;
3737   struct proc *curproc = myproc();
3738 
3739   if(addr >= curproc->sz)
3740     return -1;
3741   *pp = (char*)addr;
3742   ep = (char*)curproc->sz;
3743   for(s = *pp; s < ep; s++){
3744     if(*s == 0)
3745       return s - *pp;
3746   }
3747   return -1;
3748 }
3749 
3750 // Fetch the nth 32-bit system call argument.
3751 int
3752 argint(int n, int *ip)
3753 {
3754   return fetchint((myproc()->tf->esp) + 4 + 4*n, ip);
3755 }
3756 
3757 // Fetch the nth word-sized system call argument as a pointer
3758 // to a block of memory of size bytes.  Check that the pointer
3759 // lies within the process address space.
3760 int
3761 argptr(int n, char **pp, int size)
3762 {
3763   int i;
3764   struct proc *curproc = myproc();
3765 
3766   if(argint(n, &i) < 0)
3767     return -1;
3768   if(size < 0 || (uint)i >= curproc->sz || (uint)i+size > curproc->sz)
3769     return -1;
3770   *pp = (char*)i;
3771   return 0;
3772 }
3773 
3774 // Fetch the nth word-sized system call argument as a string pointer.
3775 // Check that the pointer is valid and the string is nul-terminated.
3776 // (There is no shared writable memory, so the string can't change
3777 // between this check and being used by the kernel.)
3778 int
3779 argstr(int n, char **pp)
3780 {
3781   int addr;
3782   if(argint(n, &addr) < 0)
3783     return -1;
3784   return fetchstr(addr, pp);
3785 }
3786 
3787 
3788 
3789 
3790 
3791 
3792 
3793 
3794 
3795 
3796 
3797 
3798 
3799 
3800 extern int sys_chdir(void);
3801 extern int sys_close(void);
3802 extern int sys_dup(void);
3803 extern int sys_exec(void);
3804 extern int sys_exit(void);
3805 extern int sys_fork(void);
3806 extern int sys_fstat(void);
3807 extern int sys_getpid(void);
3808 extern int sys_kill(void);
3809 extern int sys_link(void);
3810 extern int sys_mkdir(void);
3811 extern int sys_mknod(void);
3812 extern int sys_open(void);
3813 extern int sys_pipe(void);
3814 extern int sys_read(void);
3815 extern int sys_sbrk(void);
3816 extern int sys_sleep(void);
3817 extern int sys_unlink(void);
3818 extern int sys_wait(void);
3819 extern int sys_write(void);
3820 extern int sys_uptime(void);
3821 extern int sys_getyear(void);
3822 extern int sys_ftruncate(void);
3823 extern int sys_getprocs(void);
3824 extern int sys_getprocinfo(void);
3825 extern int sys_date(void);
3826 extern int sys_set_priority(void);
3827 
3828 int
3829 sys_getyear(void)
3830 {
3831 
3832 return 1975;
3833 }
3834 
3835 
3836 static int (*syscalls[])(void) = {
3837 [SYS_fork]    sys_fork,
3838 [SYS_exit]    sys_exit,
3839 [SYS_wait]    sys_wait,
3840 [SYS_pipe]    sys_pipe,
3841 [SYS_read]    sys_read,
3842 [SYS_kill]    sys_kill,
3843 [SYS_exec]    sys_exec,
3844 [SYS_fstat]   sys_fstat,
3845 [SYS_chdir]   sys_chdir,
3846 [SYS_dup]     sys_dup,
3847 [SYS_getpid]  sys_getpid,
3848 [SYS_sbrk]    sys_sbrk,
3849 [SYS_sleep]   sys_sleep,
3850 [SYS_uptime]  sys_uptime,
3851 [SYS_open]    sys_open,
3852 [SYS_write]   sys_write,
3853 [SYS_mknod]   sys_mknod,
3854 [SYS_unlink]  sys_unlink,
3855 [SYS_link]    sys_link,
3856 [SYS_mkdir]   sys_mkdir,
3857 [SYS_close]   sys_close,
3858 [SYS_getyear] sys_getyear,
3859 [SYS_ftruncate] sys_ftruncate,
3860 [SYS_getprocs] sys_getprocs,
3861 [SYS_getprocinfo] sys_getprocinfo,
3862 [SYS_date]    sys_date,
3863 [SYS_set_priority]    sys_set_priority
3864 };
3865 
3866 void
3867 syscall(void)
3868 {
3869   int num;
3870   struct proc *curproc = myproc();
3871 
3872   num = curproc->tf->eax;
3873   if(num > 0 && num < NELEM(syscalls) && syscalls[num]) {
3874     curproc->tf->eax = syscalls[num]();
3875   } else {
3876     cprintf("%d %s: unknown sys call %d\n",
3877             curproc->pid, curproc->name, num);
3878     curproc->tf->eax = -1;
3879   }
3880 }
3881 
3882 
3883 
3884 
3885 
3886 
3887 
3888 
3889 
3890 
3891 
3892 
3893 
3894 
3895 
3896 
3897 
3898 
3899 
