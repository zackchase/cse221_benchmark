cse221_benchmark
================

CSE221 System Benchmarking Project
Python helper code to run experiments (`runner.py`)


## CPU, Scheduling, and OS Services (`experiments/system`)



## Memory (`experiments/memory`)
1. Measurement overhead
  * Overhead reading time: `/read_time_overhead.c`
  * Loop head: `/for_loop_overhead.c`
2. Procedure call overhead: `/parameter_overhead.c`
3. System call overhead: `/system_call_time.c`
4. Task creation time
  * Process fork: `/process_create.c`
  * Thread: 'pthread_create.c'
5. Context switch time
  * Process: `process_switch.c`
  * Thread: `pthread_switch.c`


## Network (`experiments/network`)

## File System (`experiments/filesys`)