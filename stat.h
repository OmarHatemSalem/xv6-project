#define T_DIR  1   // Directory
#define T_FILE 2   // File
#define T_DEV  3   // Device

struct stat {
  short type;  // Type of file
  int dev;     // File system's disk device
  uint ino;    // Inode number
  short nlink; // Number of links to file
  uint size;   // Size of file in bytes
};

struct filtered_proc {
  uint sz;                     // Size of process memory (bytes)
  char state[16];              // Process state
  int pid;                     // Process ID
  uint priority;               // Process Priority
  int parentpid;               // Parent Process ID
  char name[16];               // Process name (debugging)
};