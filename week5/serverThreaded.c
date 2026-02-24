/* A threaded server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define BUFFERLENGTH 256


/* displays error messages from system calls */
void error(char *msg) {
    perror(msg);
    exit(1);
};

int isExecuted = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; /* the lock used for processing */

int writeResult (int sockfd, char *buffer, size_t bufsize) {
    int n;
   
    n = write(sockfd, &bufsize, sizeof(size_t));
    if (n < 0) {
		fprintf (stderr, "ERROR writing to result\n");
		return -1;
    }
    
    n = write(sockfd, buffer, bufsize);
    if (n != bufsize) {
		fprintf (stderr, "Couldn't write %ld bytes, wrote %d bytes\n", bufsize, n);
		return -1;
    }
    return 0;
}

char *readRes(int sockfd) {
    size_t bufsize;
    int res;
    char *buffer;

    res = read(sockfd, &bufsize, sizeof(size_t));
    if (res != sizeof(size_t)) {
		fprintf (stderr, "Reading number of bytes from socket failed\n");
		return NULL;
    }

    buffer = malloc(bufsize+1);
    if (buffer) {
		buffer[bufsize]  = '\0';
		res = read(sockfd, buffer, bufsize);
		if (res != bufsize) {
			fprintf (stderr, "Reading reply from socket\n");
			free(buffer);
			return NULL;
		}
    }
    
    return buffer;
}    


/* For each connection, this function is called in a separate thread. */
void *processRequest (void *args) {
    int *newsockfd =  (int *) args;   
    int n;
    int tmp;
    char *buffer;

    buffer = readRes (*newsockfd);
    if (!buffer)  {
		fprintf (stderr, "ERROR reading from socket\n");
    }
    else {
		printf ("Here is the message: %s\n",buffer);
		pthread_mutex_lock (&mut); /* lock exclusive access to variable isExecuted */
		tmp = isExecuted;
			
		printf ("Waiting for confirmation: Please input an integer\n");
		scanf ("%d", &n); /* not to be done in real programs: don't go to sleep while holding a lock! Done here to demonstrate the mutual exclusion problem. */
		printf ("Read value %d\n", n);

		isExecuted = tmp +1;
		pthread_mutex_unlock (&mut); /* release the lock */
		
		buffer = realloc(buffer, BUFFERLENGTH);
		n = sprintf (buffer, "I got you message, the value of isExecuted is %d\n", isExecuted);
		/* send the reply back */
		n = writeResult (*newsockfd, buffer, strlen(buffer) + 1);
		if (n < 0) {
			fprintf (stderr, "Error writing to socket\n");
		}
    }

    free(buffer);
    close(*newsockfd); /* important to avoid memory leak */
    free (newsockfd);
	  
    pthread_exit (NULL); /*exit value not used */
}

int main(int argc, char *argv[]) {
    int sockfd, portno;
    struct sockaddr_in6 serv_addr;
    int result;

    if (argc < 2) {
		fprintf (stderr,"ERROR, no port provided\n");
		exit(1);
    }
	     
    /* create socket */
    sockfd = socket (AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0) 
	error("ERROR opening socket");
    bzero ((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin6_family = AF_INET6;
    serv_addr.sin6_addr = in6addr_any;
    serv_addr.sin6_port = htons (portno);

    /* bind it */
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		error("ERROR on binding");
	}

    /* ready to accept connections */
    listen (sockfd,5);

    /* now wait in an endless loop for connections and process them */
    while(1) {
		pthread_t server_thread; /* thread information */
		pthread_attr_t pthread_attr; /* attributes for newly created thread */
		int *newsockfd;
		struct sockaddr_in6 cli_addr;
		socklen_t clilen;

		clilen = sizeof(cli_addr);
		newsockfd  = malloc(sizeof (int));
		if (!newsockfd) {
			fprintf (stderr, "Memory allocation failed!\n");
			exit(1);
		}
		
		/* waiting for connections */
		*newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (*newsockfd < 0) {
			error ("ERROR on accept");
		}

		/* create thread for processing of connection */
		if (pthread_attr_init (&pthread_attr)) {
			fprintf (stderr, "Creating initial thread attributes failed!\n");
			exit (1);
		}

		if (pthread_attr_setdetachstate (&pthread_attr, PTHREAD_CREATE_DETACHED)) {
			fprintf (stderr, "setting thread attributes failed!\n");
			exit (1);
		}
			
		result = pthread_create (&server_thread, &pthread_attr, processRequest, (void *) newsockfd);
		if (result != 0) {
			fprintf (stderr, "Thread creation failed!\n");
			exit (1);
		}
    }
}





