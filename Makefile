all: ketama_sim.cpp k_time_sim.cpp sim.cpp
	g++ -std=gnu++11 ketama_sim.cpp -o k_sim -lketama
	g++ -std=gnu++11 k_time_sim.cpp -o t_sim -lketama
	g++ -std=gnu++11 sim.cpp -o sim

ketama:
	g++ -std=gnu++11 latency_ketama_sim.cpp -o kl_sim -lketama

late: sim_latency.cpp
	g++ -std=gnu++11 sim_latency.cpp -o l_sim

clean:
	rm sim
