#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

extern char *processRequest (char *);

void printFirstChars (char *response, int n) {
    int i;
    
    i = 0;
    while (n >= 0 && response[i] != '\0') {
	printf ("%c", response[i]);
	n--;
	i++;
    }
    printf ("\n");
}

bool evaluateTest (char *request, char *expectedResponse, char *response, int testNo, bool allTestsPassed) {
    int len;
    
    len = strlen(expectedResponse) + 2;
    printf ("Part %d: Request is %s\n", testNo, request);
    if (response == NULL) {
	printf ("Expected response is %s, got null pointer\n", expectedResponse);
	allTestsPassed = false;
	printf ("Part %d failed \n", testNo);
    }
    else if (strncmp(response, expectedResponse, strlen(expectedResponse) + 2) != 0) {
	printf ("Expected response %s, first %d characters of response are ", expectedResponse, len);
	printFirstChars(response, len);
	allTestsPassed = false;
	printf ("Part %d failed\n", testNo);
    }
    else {
	printf ("Part %d passed\n", testNo);
    }
    return allTestsPassed;
}

int main () {
    char *response, *request, *expectedResponse;
    bool allTestsPassed = true;
    
    /* Test 1 */
    request = "A 147.188.192.43 22";
    response = processRequest(request);
    expectedResponse = "Rule added";
    allTestsPassed = evaluateTest (request, expectedResponse, response, 1, allTestsPassed);
    free(response);

    /* Test 2 */
    request = "C 147.188.192.43 22";
    response = processRequest(request);
    expectedResponse = "Connection accepted";
    allTestsPassed = evaluateTest (request, expectedResponse, response, 2, allTestsPassed);
    free(response);

    /* Test 3 */
    request = "F";
    response = processRequest(request);
    expectedResponse = "All rules deleted";
    allTestsPassed = evaluateTest (request, expectedResponse, response, 3, allTestsPassed);
    free(response);

    if (allTestsPassed)  {
	printf ("Test passed\n");
	return 0;
    }
    else {
	printf ("Test failed\n");
	return 1;
    }
}
