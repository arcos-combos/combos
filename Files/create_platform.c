/****************** CREAR DEPLOYMENT.XML CON EL NUMERO DE CLIENTES PASADO COMO ARGUMENTO ********************/

#include <stdlib.h>
#include <stdio.h>
#include "rand.h"

int main(int argc, char *argv[]){
	
	int i, j, k, index = 1;
	FILE *fd;
	char buffer[256];
	int n_projects, n_clusters;

	//Usage
	if (argc < 7) {
		printf("argc = %d\n", argc);
    		printf("Usage: %s n_clusters n_clients cluster_power cluster_bandwidth cluster_latency n_projects server_pw att_projs lbw llatency\n", argv[0]);
    		exit(1);
  	}

	/* *********** DEPLOYMENT.XML *************/
	sprintf(buffer, "platform.xml");
	fd= fopen(buffer, "w");
	if (fd == NULL){
    		printf("Error opening deployment file!\n");
    		exit(1);
	}
		
	n_clusters = atoi(argv[index++]);

	int att_proj[n_clusters];

	/* BASICS */
	fprintf(fd, "<?xml version='1.0'?>\n");
	fprintf(fd, "<!DOCTYPE platform SYSTEM \"http://simgrid.gforge.inria.fr/simgrid.dtd\">\n");
	fprintf(fd, "<platform version=\"3\">\n");

	fprintf(fd, "<AS  id=\"AS0\"  routing=\"Full\">\n");	

	// Clients
	for(i=0; i<n_clusters; i++){
		fprintf(fd, "\t<cluster id=\"cluster_%d\" prefix=\"c%d\" suffix=\"\" radical=\"0-%s\"\n\t\tpower=\"1Gf\" bw=\"%s\" lat=\"%s\" router_id=\"router_cluster%d\"/>\n", i+1, i+1, argv[index+2], argv[index+1], argv[index], i+1);
		index+=3;
	}

	fprintf(fd, "\n");

	n_projects = atoi(argv[index++]);

	// Servers
	for(i=0; i<n_projects; i++){
		fprintf(fd, "\t<AS id=\"BE%d\" routing=\"None\">\n", i+1);
		fprintf(fd, "\t\t<host id=\"b%d\" power=\"%s\"/>\n", i, argv[index]);
		fprintf(fd, "\t</AS>\n");

		char* power = argv[index++];
		char* max = argv[index++];

		// Scheduling servers
		fprintf(fd, "\t<cluster id=\"cluster_%d\" prefix=\"s%d\" suffix=\"\" radical=\"0-%s\"\n\t\tpower=\"%s\" bw=\"100Gbps\" lat=\"5ms\" router_id=\"router_cluster%d\"/>\n\n", n_clusters+i*2+1, i+1, max, power, n_clusters+i*2+1);
		
		// Data servers
		fprintf(fd, "\t<cluster id=\"cluster_%d\" prefix=\"d%d\" suffix=\"\" radical=\"0-%s\"\n\t\tpower=\"1Gf\" bw=\"100Gbps\" lat=\"5ms\" router_id=\"router_cluster%d\"/>\n\n", n_clusters+i*2+2, i+1, argv[index++], n_clusters+i*2+2);
	}

	fprintf(fd, "\t<AS id=\"AS%d\" routing=\"None\">\n", 1);
	fprintf(fd, "\t\t<host id=\"r0\" power=\"1\"/>\n");
	fprintf(fd, "\t</AS>\n");
	
	fprintf(fd, "\n");

	// Links
	for(i=0, k=0; i<n_clusters; i++){
		att_proj[i] = atoi(argv[index++]);
		for(j=0; j<att_proj[i]; j++, k++){
			fprintf(fd, "\t<link id=\"l%d\" bandwidth=\"%s\" latency=\"%s\"/>\n", k++, argv[index+1], argv[index]);
			fprintf(fd, "\t<link id=\"l%d\" bandwidth=\"%s\" latency=\"%s\"/>\n", k, argv[index+3], argv[index+2]);
			index+=4;
		}	
	}
	for(i=0; i<n_projects; i++)
		fprintf(fd, "\t<link id=\"l%d\" bandwidth=\"10Gbps\" latency=\"0\"/>\n", k++);

	fprintf(fd, "\n");

	// Clients <--> Servers (scheduling and data servers) 
	for(i=0, k=0; i<n_clusters; i++){
		for(j=0; j<att_proj[i]; j++, index++){
			fprintf(fd, "\t<ASroute src=\"cluster_%d\" dst=\"cluster_%d\" gw_src=\"router_cluster%d\" gw_dst=\"router_cluster%d\">\n", i+1, n_clusters+atoi(argv[index])*2+1, i+1, n_clusters+atoi(argv[index])*2+1);
			fprintf(fd, "\t\t<link_ctn id=\"l%d\"/>\n", k++);
			fprintf(fd, "\t</ASroute> \n");
			fprintf(fd, "\t<ASroute src=\"cluster_%d\" dst=\"cluster_%d\" gw_src=\"router_cluster%d\" gw_dst=\"router_cluster%d\">\n", i+1, n_clusters+atoi(argv[index])*2+2, i+1, n_clusters+atoi(argv[index])*2+2);
			fprintf(fd, "\t\t<link_ctn id=\"l%d\"/>\n", k++);
			fprintf(fd, "\t</ASroute> \n");
		}
	}

	// Scheduling servers <-> Data servers 
	for(i=0; i<n_projects; i++, k++){
		fprintf(fd, "\t<ASroute src=\"cluster_%d\" dst=\"cluster_%d\" gw_src=\"router_cluster%d\" gw_dst=\"router_cluster%d\">\n", n_clusters+i*2+1, n_clusters+i*2+2, n_clusters+i*2+1, n_clusters+i*2+2);
		fprintf(fd, "\t\t<link_ctn id=\"l%d\"/>\n", k);
		fprintf(fd, "\t</ASroute> \n");
	}

	fprintf(fd, "</AS>\n");	

	/* END */
	fprintf(fd, "</platform>\n");

	fclose(fd);

	return 0;
}
