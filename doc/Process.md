# Process
## Overview
A process represents a program running on the system.<br>
It has a unique identifier (a Process ID or <i>PID</i>) to allow other processes to communicate with each other.
It represents the permissions, memory pages and the domain in which its [threads](doc/Thread.md) are executed.
## Structure
A process has a structure representing it on the kernel's [process table](doc/ProcessTable.md).<br>
It's declared as follows:

```
struct Process_s {
    uint32_t pid; // The Process' ID
    Link_s *childProcesses; // A linked list with pointers to child processes of this process. 
    Link_s *threads;        // A linked list with pointers to this process’ threads. 
    uint64_t ioAccess[1024];// A bitmap detailing which IO ports does this process have access to.
    uint8_t intNumber;      // The interrupt number that this process is associated with. When any other process calls this interrupt, the kernel will yield execution to it.
    MsgHead_t *msgStackStart; // The pointer to the start of the message stack (according to the physical address space).
    uint32_t pageDirectory;   // The index of the process' page directory inside the kernel's page directory table.
};
```

You can find Link_t in [include/types.h](include/types.h) and MsgHead_t in [include/sys/ipc.h](include/sys/ipc.h).
