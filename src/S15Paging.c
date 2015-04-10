#include <string.h>
#include <stdlib.h>
#include <VirtualBlockStorage.h> // NOTE THIS WILL ONLY BE USED FOR TIER 2


#include "../include/S15Paging.h"
#include "../include/dll.h"

#define MAX_PAGE_TABLE_ENTRIES_COUNT 2048
#define MAX_PHYSICAL_MEMORY_FRAME_COUNT 512

#define VBS_FILENAME "SWAP_FILE"


static VBS_Type* vbs;

/*				READ THESE COMMENTS FIRST
 * ---------------------------------------------------
 *
 * Create a custom linear data structure that will hold
 * values that are indices into the frame table
 * This will be used for the LRU and FIFO
 * implementations. Make sure the structure is 
 * declared as static and is cleared(reset) inside 
 * of initialize_frame_table function.  
 
 * Do not be afraid to add additional helper functions 
 * to decrease duplications of functionality between 
 * functions. Program modularly and don't 
 * be afraid to leave functions incomplete! All work in, 
 * incompleted functions may count for partial points.
 * ---------------------------------------------------
 **/

 #define BIT_SET 1
 #define BIT_UNSET 0
 #define MAX_FRAMES 512
 #define MAX_PAGES 2048
 #define NOTHING_SENTINEL 65535
 
 typedef unsigned char byte_t;
 typedef unsigned char bit_t;
 
typedef struct {
/*
 * Fill in the missing fields needed
 * Check the Prj 2 specs for help
 **/
	unsigned short pageNum;
	bit_t accessed;
	byte_t accessPattern;
	byte data[1024];
}FrameEntry_t;


typedef struct {
/*
 * Fill in the missing fields needed
 * Check the Prj 2 specs for help
 **/
	unsigned short frameNumMapped; //frame index/address
	bit_t valid;
}PageEntry_t;

typedef struct {
/*
 * Note this is a table not a single element
 * of a table, so you must create an
 * array of frame enrties and a size for frame entries variable
 **/
	FrameEntry_t FT[MAX_FRAMES];
	int size;
}FrameTable_t;


typedef struct {
/*
 * Note this is a table not a single element
 * of a table, so you must create an
 * array of page entries and a size for page entries variable
 **/
	PageEntry_t PT[MAX_PAGES];
	int size;
}PageTable_t;

/*
 * Global protected variables to this C file only
 **/
static FrameTable_t frameTable;
static PageTable_t pageTable;
// TODO: add static linear data structure instantiation here
static DLL* fifo = NULL;
static DLL* lru = NULL;

/*
 * FUNCTION PROTOTYPES FOR ADDED HELPER FUNCTIONS
 * Note: A good design pattern to implement while handling 
 * global variables in C is called the Singleton Pattern!
 * Wiki or Google such pattern. Adding mutator and accessor
 * functions to a single instance of a object (variable) provides some 
 * security over bare global variable access.
 **/



/*
 * CLEARS THE PAGE TABLE and FRAME TABLE WITH ALL ZEROS
 * AND clears your created linear data structure
 **/
void initialize_page_table() {
	memset(&pageTable,0,sizeof(PageTable_t));	
	int i = 0;
	for(i = 0; i<MAX_PAGES; i++){
		pageTable.PT[i].valid = BIT_UNSET;
		pageTable.PT[i].frameNumMapped = NOTHING_SENTINEL;
	}
}

void initialize_frame_table () {
	memset(&frameTable,0,sizeof(FrameTable_t));
	int i = 0;
	for(i = 0; i<MAX_FRAMES; i++){
		frameTable.FT[i].pageNum = NOTHING_SENTINEL;
	}
	/* TODO: */
	/* Implement the clearing and/or resetting of your 
	   linear data structure for LRU and FIFO*/
	   if(fifo != NULL){
			destroyList(fifo);
	   }
	   if(lru != NULL){
			destroyList(lru);
	   }
	   fifo = createEmptyList();
	   lru = createEmptyList();
}


/*
 * START OF THE PAGE SWAP ALGORITHMS
 *
 * RETURN REQUIREMENT FOR EACH ONE 
 *
 * return NULL when NO PAGE FAULT HAPPENDED
 * else return a filled and allocated PageAlgorithmResults 
 * structure. See Prj 2 document for assistance, the 
 * struct inside of S15Paging.h, and/or test_S15Paging.c
 **/
 
static int checkPageNum(unsigned short page_number){
	if(page_number < 0 || page_number > MAX_PAGES-1){
		return -1;
	}
	
	return 1;
}

static unsigned short findFirstOpenFrame(){
	if(frameTable.size == MAX_FRAMES){
		return NOTHING_SENTINEL;
	}
	return ((unsigned short) frameTable.size)+1;
}

static void addToFrameTable(int i, unsigned short page_number){
	FrameEntry_t* frame = &(frameTable.FT[i]);
	if(frame->pageNum != NOTHING_SENTINEL){
		pageTable.PT[frame->pageNum].valid = BIT_UNSET;
		pageTable.PT[frame->pageNum].frameNumMapped = NOTHING_SENTINEL;
	}
	frame->pageNum = page_number;
	frame->accessed = BIT_UNSET;
	frame->accessPattern = 0;
	pageTable.PT[page_number].valid = BIT_SET;
	pageTable.PT[page_number].frameNumMapped = i;
	//frame->data nothing to do here
}

static unsigned short getBackAndRemove(DLL* dll){
	if(dll->size == 0){
		perror("tried to pull the back of an empty queue");
	}
	unsigned short frameNum = getDatumFromBack(dll);
	removeFromBack(dll);
	return frameNum;
}
 

PageAlgorithmResults* first_in_first_out(unsigned short page_number, unsigned int time_interval) {
	if(checkPageNum(page_number) < 0){
		perror("Invalid page number, abort, abort");
		return NULL;
	}
	
	if((pageTable.PT[page_number]).valid == BIT_SET){
		//page table hit
		return NULL;
	}
	
	
	unsigned short fn = findFirstOpenFrame();
	if(fn == NOTHING_SENTINEL){
		printf("heyo\n");
		fn = getBackAndRemove(fifo);
	}else{
		frameTable.size += 1;
	}
	PageAlgorithmResults* result = malloc(sizeof(PageAlgorithmResults));
	result->pageRequested = page_number;
	result->frameReplaced = fn;
	result->pageReplaced = frameTable.FT[fn].pageNum;
	addToFrameTable(fn, page_number);
	appendToFront(fn, fifo);
	return result;	
}

static void findRemove(unsigned short frameNum, DLL* dll){
	Node_t* foundNode = dll->head;
	while(foundNode!=NULL){
		if(foundNode->datum == frameNum){
			if(foundNode != NULL){
				if(foundNode->next != NULL){
					foundNode->next->prev = foundNode->prev;
				}
				if(foundNode->prev != NULL){
					foundNode->prev->next = foundNode->next;
				}
				dll->size -= 1;
				free(foundNode);
				return;
			}
		}
	}
	//node not found
}

PageAlgorithmResults* least_recently_used(unsigned short page_number, unsigned int time_interval) {
	if(checkPageNum(page_number) < 0){
		perror("Invalid page number, abort, abort");
		return NULL;
	}
	
	if((pageTable.PT[page_number]).valid == BIT_SET){
		//page table hit
		findRemove(pageTable.PT[page_number].frameNumMapped, lru);
		appendToFront(pageTable.PT[page_number].frameNumMapped, lru);
		return NULL;
	}
	
	unsigned short fn = findFirstOpenFrame();
	if(fn == NOTHING_SENTINEL){
		fn = getBackAndRemove(lru);
	}else{
		frameTable.size += 1;
	}
	
	PageAlgorithmResults* result = malloc(sizeof(PageAlgorithmResults));
	result->pageRequested = page_number;
	result->frameReplaced = fn;
	result->pageReplaced = frameTable.FT[fn].pageNum;
	addToFrameTable(fn, page_number);
	appendToFront(fn, lru);

	return result;	
}

static unsigned short findSmallestAccessPat(){
	unsigned short i = 1;
	byte_t min = frameTable.FT[0].accessPattern;
	unsigned short minLoc = 0;
	for(i = 1; i< MAX_FRAMES; i++){ //technically you could iterate to ft.size but whatever
		if(frameTable.FT[i].accessPattern < min){
			min =frameTable.FT[i].accessPattern;
			minLoc = i;
		}
	}
	return minLoc;
}

PageAlgorithmResults* least_recently_used_approx(unsigned short page_number, unsigned int time_interval) {
	if(checkPageNum(page_number) < 0){
		perror("Invalid page number, abort, abort");
		return NULL;
	}
	
	if(time_interval%99 == 0){
		int i = 0;
		for(i=0;i<MAX_FRAMES;i++){
			frameTable.FT[i].accessPattern >>= 1;
			frameTable.FT[i].accessPattern += 128*frameTable.FT[i].accessed;
		}
	}
	
	if((pageTable.PT[page_number]).valid == BIT_SET){
		return NULL;
	}
	
	unsigned short fn = findFirstOpenFrame();
	if(fn == NOTHING_SENTINEL){
		fn = findSmallestAccessPat();
	}else{
		frameTable.size += 1;
	}
	
	PageAlgorithmResults* result = malloc(sizeof(PageAlgorithmResults));
	result->pageRequested = page_number;
	result->frameReplaced = fn;
	result->pageReplaced = frameTable.FT[fn].pageNum;
	addToFrameTable(fn, page_number);	
	frameTable.FT[fn].accessed = BIT_SET;
	return result;
}

static unsigned short countBits(byte_t byte){
	unsigned short count = 0;
	while(byte){
		count += byte & 1;
		byte >>= 1;
	}
	return count;
}

static unsigned short findLFUframe(){
	unsigned short i = 1;
	unsigned short min = countBits(frameTable.FT[0].accessPattern);
	unsigned short minLoc = 0;
	unsigned short cBits = 0;
	for(i = 1; i< MAX_FRAMES; i++){ //technically you could iterate to ft.size but whatever
		cBits = countBits(frameTable.FT[i].accessPattern);
		if(cBits < min){
			min =cBits;
			minLoc = i;
		}
	}
	return minLoc;
}

static unsigned short findMFUframe(){
	unsigned short i = 1;
	unsigned short max = countBits(frameTable.FT[0].accessPattern);
	unsigned short maxLoc = 0;
	unsigned short cBits = 0;
	for(i = 1; i< MAX_FRAMES; i++){ //technically you could iterate to ft.size but whatever
		cBits = countBits(frameTable.FT[i].accessPattern);
		if(cBits > max){
			max = cBits;
			maxLoc = i;
		}
	}
	return maxLoc;
}

PageAlgorithmResults* least_frequently_used(unsigned short page_number, unsigned int time_interval) {
		if(checkPageNum(page_number) < 0){
		perror("Invalid page number, abort, abort");
		return NULL;
	}
	
	if(time_interval%99 == 0){
		int i = 0;
		for(i=0;i<MAX_FRAMES;i++){
			frameTable.FT[i].accessPattern >>= 1;
			frameTable.FT[i].accessPattern += 126*frameTable.FT[i].accessed;
		}
	}
	
	if((pageTable.PT[page_number]).valid == BIT_SET){
		return NULL;
	}
	
	unsigned short fn = findFirstOpenFrame();
	if(fn == NOTHING_SENTINEL){
		fn = findLFUframe();
	}else{
		frameTable.size += 1;
	}

	PageAlgorithmResults* result = malloc(sizeof(PageAlgorithmResults));
	result->pageRequested = page_number;
	result->frameReplaced = fn;
	result->pageReplaced = frameTable.FT[fn].pageNum;
	addToFrameTable(fn, page_number);	
	frameTable.FT[fn].accessed = BIT_SET;
	return result;
}

PageAlgorithmResults* most_frequently_used(unsigned short page_number, unsigned int time_interval) {
	if(checkPageNum(page_number) < 0){
		perror("Invalid page number, abort, abort");
		return NULL;
	}
	
	if(time_interval%99 == 0){
		int i = 0;
		for(i=0;i<MAX_FRAMES;i++){
			frameTable.FT[i].accessPattern >>= 1;
			frameTable.FT[i].accessPattern += 126*frameTable.FT[i].accessed;
		}
	}
	
	if((pageTable.PT[page_number]).valid == BIT_SET){
		return NULL;
	}
	
	unsigned short fn = findFirstOpenFrame();
	if(fn == NOTHING_SENTINEL){
		fn = findMFUframe();
	}else{
		frameTable.size += 1;
	}
	
	PageAlgorithmResults* result = malloc(sizeof(PageAlgorithmResults));
	result->pageRequested = page_number;
	result->frameReplaced = fn;
	result->pageReplaced = frameTable.FT[fn].pageNum;
	addToFrameTable(fn, page_number);	
	frameTable.FT[fn].accessed = BIT_SET;
	return result;
}

/*
 * USED IN TIER TWO
 **/  
bool init_backing_store() {
	vbs_initialize(VBS_FILENAME);
	vbs = vbs_open(VBS_FILENAME);
	
	/*
	 * Reserving 2048 blocks for swapping
	 **/
	 BlockType block;
	 block = vbs_make_block();
	 memset(block.buffer,0,1024);
	 int i = 8;
	 int j = 0;
	 for (;i < 2048 + 8; ++i) {
		/*
	     * Create simple data inside out buffer
  		 **/		 
		for (j = 0; j < 1024; ++j) {
			block.buffer[j] = j % 256;
		}

	 	if ( 1024 == vbs_write(vbs,i,block)) {
			return false;
		}
		memset(block.buffer,0,1024);
	}
	return false;
}

bool close_backing_store() {
	vbs_close(vbs);
	return true;
}
