#ifndef _S15_PAGING_H_
#define _S15_PAGING_H_
#include <stdbool.h>

typedef struct {
	unsigned short pageRequested;
	unsigned short frameReplaced;
	unsigned short pageReplaced;
}PageAlgorithmResults;

void initialize_page_table();

void initialize_frame_table();

PageAlgorithmResults* first_in_first_out(unsigned short page_number, unsigned int time_interval);

PageAlgorithmResults* least_recently_used(unsigned short page_number, unsigned int time_interval);

PageAlgorithmResults* least_recently_used_approx(unsigned short page_number, unsigned int time_interval);

PageAlgorithmResults* least_frequently_used(unsigned short page_number, unsigned int time_interval);

PageAlgorithmResults* most_frequently_used(unsigned short page_number, unsigned int time_interval);

bool init_backing_store();

bool close_backing_store();

#endif
