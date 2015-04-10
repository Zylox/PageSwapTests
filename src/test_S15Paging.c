#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>


#include "../include/S15Paging.h"

typedef struct {
	unsigned int timeInterval;
	unsigned short pageNumber;

}PageTestPair;



PageTestPair* generateTestPagePairs(unsigned int numOfPagePairs, unsigned int duplicateInterval) {
	PageTestPair* pairs = calloc(numOfPagePairs,sizeof(PageTestPair));
	if (!pairs) {
		return NULL;
	}
	unsigned int i = 0;
	for (;i < numOfPagePairs; ++i) {
		pairs[i].timeInterval = i;

		// Adds duplication of previous pageNumber from 
		// the last interval
		// else create a random number
		if (i % duplicateInterval) {
			pairs[i].pageNumber = rand() % 2048;
		}
		else {
			const unsigned int inBetweenIdx = rand() % duplicateInterval;
			pairs[i].pageNumber = pairs[inBetweenIdx].pageNumber;
		}
	}
	return pairs;
}

/*
 *                        READ THESE COMMENTS FIRST 
 * --------------------------------------------------------------
 * FULL TEST SUITE FOR PROJECT 2, DO NOT EDIT THIS FILE
 * --------------------------------------------------------------
 *  
 * INPUT FROM COMMAND LINE: ./test_S15Paging <maxNumberOfPages> <duplcateIntervalValue>
 * 
 * Ex: ./test_S15Paging 1000 10
 * Will run each of the following page swap algorithms 1000 times
 * each and will duplicate a previous pageNumber at each interval of 10 
 *
 * SAVE TIME WHILE TESTING
 * ---------------------------------------------------------------
 * To decrease running time you should redirect your ouput into a file called <whatever>.txt
 * ./test_S15Paging 1000 10 > <whatever>.txt
 *
 * Note: The > means take the output from my porgram that would go to the screen
 * and store that into a different location (file in this case).
 * 
 * To view your ouput from the redirection type the following
 * 
 * cat <whatever>.txt
 *
 * Using the less command will be helpful in this instance as well. Using the space bar to jump down
 * sections 
 *
 * less <whatever>.txt
 *
 **/

int main (int argc, char **argv) {

	srand(1337);
	if (argc <= 2) {
		printf("Improper Usage: %s <maxNumberOfPages> <duplicateIntervalValue>\n\n", argv[0]);
		return -1;
	}
	
	unsigned int numOfPagePairs = 0;
	unsigned int duplicateIntervalValue = 0;
	if (sscanf(argv[1],"%u",&numOfPagePairs) != 1 || sscanf(argv[2],"%u",&duplicateIntervalValue) != 1) {	
		printf("Improper Usage: %s <maxNumberOfPages> <duplicateIntervalValue>\n", argv[0]);
		printf("maxNumberOfPages and duplicateIntervalValue must be greater than 0, and duplicateInterValue must be less than 2048\n\n");
		return -1;
	}

	if (numOfPagePairs <= 0 || numOfPagePairs > 1000000 
			||  duplicateIntervalValue <= 0 || duplicateIntervalValue > 1024) {	
		printf("Improper Usage: %s <maxNumberOfPages> <duplicateIntervalValue>\n", argv[0]);
		printf("maxNumberOfPages and duplicateIntervalValue must be greater than 0, and duplicateInterValue must be less than or equal to 1024 and maxNumberOfPages must be less than or equal to 1000000\n\n");
		return -1;
	}
	
	if (numOfPagePairs < duplicateIntervalValue ) {	
		printf("Improper Usage: %s <maxNumberOfPages> <duplicateIntervalValue>\n", argv[0]);
		printf("duplicateIntervalValue must be less than or equal to numOfPage\n\n");
		return -1;
	}

	unsigned int i = 0;
	PageAlgorithmResults* results = NULL;
	
	PageTestPair* pageTestPairs = generateTestPagePairs(numOfPagePairs,duplicateIntervalValue);
	if (!pageTestPairs) {	
		printf("ERROR: NOT ENOUGH MEMORY FOR REQUESTED ALLOCATION\n\n");
		return -1;
	}	
	/*
	 * UNIT TESTS FOR PAGE SWAP ALGORITHMS
	 **/
	
	/*
	 * UNCOMMENT FUNCTION CALL BELOW FOR TIER TWO PRE-SET UP*/
	
	/*
	init_backing_store();	
	*/

	/*
	 * TESTING FIFO PAGE SWAP ALGORITHM
	 **/
	printf("FIFO PAGE SWAP ALGORITHM\n");
	printf("------------------------------------\n");
	initialize_page_table();
	initialize_frame_table();
	for (i = 0; i < numOfPagePairs; ++i) {
 		results = first_in_first_out (pageTestPairs[i].pageNumber,pageTestPairs[i].timeInterval);
		if(results) {
			printf("%u)PAGE FAULT: Page Requested = %u, Frame Replaced = %u, Page Replaced = %u\n",i,
					results->pageRequested,results->frameReplaced,results->pageReplaced);
			free(results);
			results = NULL;
		}
		
    }
	printf("------------------------------------\n");
	/*
	 * TESTING LRU PAGE SWAP ALGORITHM
	 **/
	// printf("LRU PAGE SWAP ALGORITHM\n");
	// printf("------------------------------------\n");

	// initialize_page_table();
	// initialize_frame_table();
	// for (i = 0; i < numOfPagePairs; ++i) {
		// results = least_recently_used (pageTestPairs[i].pageNumber,pageTestPairs[i].timeInterval);
		// if(results) {
			// printf("%u)PAGE FAULT: Page Requested = %u, Frame Replaced = %u, Page Replaced = %u\n",i,
					// results->pageRequested,results->frameReplaced,results->pageReplaced);
			// free(results);
			// results = NULL;
		// }
	// }
	// printf("------------------------------------\n");

	/*
	 * TESTING LRU APPOX PAGE SWAP ALGORITHM
	 **/
	printf("LRU APPROX PAGE SWAP ALGORITHM\n");
	printf("------------------------------------\n");

	initialize_page_table();
	initialize_frame_table();
	for (i = 0; i < numOfPagePairs; ++i) {
		results = least_recently_used_approx (pageTestPairs[i].pageNumber,pageTestPairs[i].timeInterval);
		if(results) {
			printf("%u)PAGE FAULT: Page Requested = %u, Frame Replaced = %u, Page Replaced = %u\n",i,
					results->pageRequested,results->frameReplaced,results->pageReplaced);
			free(results);
			results = NULL;
		}
	}
	printf("------------------------------------\n");

	/*
	 * TESTING LFU PAGE SWAP ALGORITHM
	 **/
	printf("LFU PAGE SWAP ALGORITHM\n");
	printf("------------------------------------\n");
	initialize_page_table();
	initialize_frame_table();
	for (i = 0; i < numOfPagePairs; ++i) {
		results = least_frequently_used (pageTestPairs[i].pageNumber,pageTestPairs[i].timeInterval);
		if(results) {
			printf("%u)PAGE FAULT: Page Requested = %u, Frame Replaced = %u, Page Replaced = %u\n",i,
					results->pageRequested,results->frameReplaced,results->pageReplaced);
			free(results);
			results = NULL;
		}
	}
	printf("------------------------------------\n");

	/*
	 * TESTING MFU PAGE SWAP ALGORITHM
	 **/
	printf("MFU PAGE SWAP ALGORITHM\n");
	printf("------------------------------------\n");

	initialize_page_table();
	initialize_frame_table();
	for (i = 0; i < numOfPagePairs; ++i) {
		results = most_frequently_used (pageTestPairs[i].pageNumber,pageTestPairs[i].timeInterval);
		if(results) {
			printf("%u)PAGE FAULT: Page Requested = %u, Frame Replaced = %u, Page Replaced = %u\n",i,
                                results->pageRequested,results->frameReplaced,results->pageReplaced);
            free(results);
			results = NULL;
		}
	}
	printf("------------------------------------\n");

	/*
	 * Frees the allocated array of PageTestPair
	 **/
	free(pageTestPairs);
	
	/*
	 * UNCOMMENT FUNCTION CALL BELOW FOR TIER TWO PRE-SET UP*/	
	/*
	close_backing_store();	
	*/

	return 0;
}
