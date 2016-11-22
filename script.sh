#!/bin/bash

# 300,000 hosts, 2 days

	line="<simulation_time>48<\/simulation_time>\t\t\t <!-- Simulation time in hours -->" 
	sed -i "s/<simulation_time>.*/${line}/" parameters.xml	
	line="<n_clients>300000<\/n_clients>\t\t\t <!-- Number of clients of the cluster -->" 
	sed -i "s/<n_clients>.*/${line}/" parameters.xml	
	./generator
	./execute > performance/2days/0300000
	
# 300,000 hosts, 3 days

	line="<simulation_time>72<\/simulation_time>\t\t\t <!-- Simulation time in hours -->" 
	sed -i "s/<simulation_time>.*/${line}/" parameters.xml	
	line="<n_clients>300000<\/n_clients>\t\t\t <!-- Number of clients of the cluster -->" 
	sed -i "s/<n_clients>.*/${line}/" parameters.xml	
	./generator
	./execute > performance/3days/0300000

# 300,000 hosts, 4 days

	line="<simulation_time>96<\/simulation_time>\t\t\t <!-- Simulation time in hours -->" 
	sed -i "s/<simulation_time>.*/${line}/" parameters.xml	
	line="<n_clients>300000<\/n_clients>\t\t\t <!-- Number of clients of the cluster -->" 
	sed -i "s/<n_clients>.*/${line}/" parameters.xml	
	./generator
	./execute > performance/4days/0300000

