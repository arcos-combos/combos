#!/bin/bash

# 100,000 hosts, 1 day

	line="<n_clients>100000<\/n_clients>\t\t\t <!-- Number of clients of the cluster -->" 
	sed -i "s/<n_clients>.*/${line}/" parameters.xml	
	./generator
	./execute > performance/1day/0100000
	
# 200,000 hosts, 1 day

	line="<n_clients>200000<\/n_clients>\t\t\t <!-- Number of clients of the cluster -->" 
	sed -i "s/<n_clients>.*/${line}/" parameters.xml	
	./generator
	./execute > performance/1day/0200000

# 300,000 hosts, 1 day

	line="<n_clients>300000<\/n_clients>\t\t\t <!-- Number of clients of the cluster -->" 
	sed -i "s/<n_clients>.*/${line}/" parameters.xml	
	./generator
	./execute > performance/1day/0300000

# 400,000 hosts, 1 day

	line="<n_clients>400000<\/n_clients>\t\t\t <!-- Number of clients of the cluster -->" 
	sed -i "s/<n_clients>.*/${line}/" parameters.xml	
	./generator
	./execute > performance/1day/0400000

# 500,000 hosts, 1 day

	line="<n_clients>500000<\/n_clients>\t\t\t <!-- Number of clients of the cluster -->" 
	sed -i "s/<n_clients>.*/${line}/" parameters.xml	
	./generator
	./execute > performance/1day/0500000

# 600,000 hosts, 1 day

	line="<n_clients>600000<\/n_clients>\t\t\t <!-- Number of clients of the cluster -->" 
	sed -i "s/<n_clients>.*/${line}/" parameters.xml	
	./generator
	./execute > performance/1day/0600000

# 700,000 hosts, 1 day

	line="<n_clients>700000<\/n_clients>\t\t\t <!-- Number of clients of the cluster -->" 
	sed -i "s/<n_clients>.*/${line}/" parameters.xml	
	./generator
	./execute > performance/1day/0700000

# 800,000 hosts, 1 day

	line="<n_clients>800000<\/n_clients>\t\t\t <!-- Number of clients of the cluster -->" 
	sed -i "s/<n_clients>.*/${line}/" parameters.xml	
	./generator
	./execute > performance/1day/0800000

