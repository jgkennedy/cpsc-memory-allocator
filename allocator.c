// Jesse Kennedy
// Operating Systems Project
// Fall 2015

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#define PAGESIZE 4096
#define SIZES 10

void __attribute__ ((constructor)) shim_init(void);
void __attribute__ ((destructor)) shim_cleanup(void);

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);

typedef struct blockheader {
  //int size;
  //void *payload;
  struct blockheader *next;
} blockheader_t;

typedef struct pageheader {
  blockheader_t *free_l, *alloc_l;
  struct pageheader *next;
} pageheader_t;

//int fd = open("/dev/zero", O_RDONLY);
pageheader_t pages[SIZES];  // Allocate an array of page headers to hold 2..1024 sized blocks

void page_init(pageheader_t *page, size_t size) {
  //page->next = NULL;

  blockheader_t *cursor = (void *) page + sizeof(pageheader_t);  // Advance cursor to beginning of data area
  blockheader_t *end = (void *) page + PAGESIZE;
  size_t blocksize = sizeof(blockheader_t) + size;

  while (cursor + blocksize < end) {
    cursor->next = page->free_l;
    page->free_l = cursor;
    cursor += blocksize;
  }
}

void shim_init(void) {
  for (int i = 1; i <= SIZES; i++) {
    page_init(&pages[i], 1 << i);
  }
}

void *malloc(size_t size) {
  blockheader_t *block;

  return block;
}

void free(void *ptr) {

}

void *calloc(size_t nmemb, size_t size) {

}

void *realloc(void *ptr, size_t size) {

}


void shim_cleanup(void) {

}
