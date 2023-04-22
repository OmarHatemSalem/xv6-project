4250 #define T_DIR  1   // Directory
4251 #define T_FILE 2   // File
4252 #define T_DEV  3   // Device
4253 
4254 struct stat {
4255   short type;  // Type of file
4256   int dev;     // File system's disk device
4257   uint ino;    // Inode number
4258   short nlink; // Number of links to file
4259   uint size;   // Size of file in bytes
4260 };
4261 
4262 struct filtered_proc {
4263   uint sz;                     // Size of process memory (bytes)
4264   char state[16];              // Process state
4265   int pid;                     // Process ID
4266   uint priority;               // Process Priority
4267   int parentpid;               // Parent Process ID
4268   char name[16];               // Process name (debugging)
4269 };
4270 
4271 
4272 
4273 
4274 
4275 
4276 
4277 
4278 
4279 
4280 
4281 
4282 
4283 
4284 
4285 
4286 
4287 
4288 
4289 
4290 
4291 
4292 
4293 
4294 
4295 
4296 
4297 
4298 
4299 
