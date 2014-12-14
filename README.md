cse221_benchmark
================

CSE221 System Benchmarking Project
Python helper code to run experiments (`runner.py`)


### CPU, Scheduling, and OS Services (`experiments/system`)
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


### Memory (`experiments/memory`)
1. RAM access time: 
  * sequential attempt (gives constant times): `/mem_test2.c`
  * random: `/rand_mem.c`
2. RAM bandwidth:
  * reading: `/read_band.c`
  * writing: `/write_band.c`
3. Page fault: `/page_fault.c`



### Network (`experiments/network`)

### File System (`experiments/filesys`)