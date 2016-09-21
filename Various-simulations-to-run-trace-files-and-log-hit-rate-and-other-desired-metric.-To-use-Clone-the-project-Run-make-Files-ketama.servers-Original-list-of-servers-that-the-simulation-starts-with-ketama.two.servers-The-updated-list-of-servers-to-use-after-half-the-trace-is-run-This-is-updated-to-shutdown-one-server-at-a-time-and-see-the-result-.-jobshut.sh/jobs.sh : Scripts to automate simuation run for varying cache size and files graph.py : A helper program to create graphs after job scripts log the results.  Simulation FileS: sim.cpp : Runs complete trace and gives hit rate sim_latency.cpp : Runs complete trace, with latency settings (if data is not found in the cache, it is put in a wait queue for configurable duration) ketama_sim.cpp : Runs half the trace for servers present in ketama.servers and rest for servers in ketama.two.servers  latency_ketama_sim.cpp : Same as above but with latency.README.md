Various simulations to run trace files and log hit rate and other desired metric.

To use: 
Clone the project
Run make

Files:
ketama.servers : Original list of servers that the simulation starts with
ketama.two.servers : The updated list of servers to use after half the trace is run(This is updated to shutdown one server at a time and see the result).
jobshut.sh/jobs.sh : Scripts to automate simuation run for varying cache size and files
graph.py : A helper program to create graphs after job scripts log the results.

Simulation FileS:
sim.cpp : Runs complete trace and gives hit rate
sim_latency.cpp : Runs complete trace, with latency settings (if data is not found in the cache, it is put in a wait queue for configurable duration)
ketama_sim.cpp : Runs half the trace for servers present in ketama.servers and rest for servers in ketama.two.servers 
latency_ketama_sim.cpp : Same as above but with latency.
