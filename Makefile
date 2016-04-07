all: ketama_sim.cpp k_time_sim.cpp
	g++ -std=gnu++11 ketama_sim.cpp -o sim -lketama
	g++ -std=gnu++11 k_time_sim.cpp -o t_sim -lketama

clean:
	rm sim
