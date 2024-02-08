/*
 * Copyright ©2023 Justin Hsia.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Winter Quarter 2023 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

#include "libhw1/CSE333.h"
#include "./CrawlFileTree.h"
#include "./DocTable.h"
#include "./MemIndex.h"

#define INITIAL_SIZE 1024

//////////////////////////////////////////////////////////////////////////////
// Helper function declarations, constants, etc
static void Usage(void);
// processes the users input
static void ProcessQueries(DocTable* dt, MemIndex* mi);
// stores the users input in the given buffer in lowercase
// return a positve number if the user enter '\n'
// otherwise 0 or negative for eof or error input
static int GetNextLine(char* buffer);
// creates the queries from the given buffer
// returns the length of the queries and the queries
// through the given queries input
static int CreateQueries(char** queries, char* buffer);
// gets a search result based on the memory index, queries and querylength
// processes the results by getting the document name from the doctable
static void ProcessSearchResults(DocTable* dt, MemIndex* mi, char** queries,
                           int query_length);

//////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char** argv) {
  if (argc != 2) {
    Usage();
  }

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - Crawl from a directory provided by argv[1] to produce and index
  //  - Prompt the user for a query and read the query from stdin, in a loop
  //  - Split a query into words (check out strtok_r)
  //  - Process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.
  //
  // Note that you should make sure the fomatting of your
  // searchshell output exactly matches our solution binaries
  // to get full points on this part.

  // indexing
  printf("Indexing '%s'\n", argv[1]);
  DocTable* dt;
  MemIndex* mi;
  // crawl file
  int res = CrawlFileTree(argv[1], &dt, &mi);
  if (res == 0) {
    Usage();
  }
  ProcessQueries(dt, mi);
  MemIndex_Free(mi);
  DocTable_Free(dt);
  printf("%s\n", "shutting down...");
  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////
// Helper function definitions

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}

static void ProcessQueries(DocTable* dt, MemIndex* mi) {
  char** query = (char**) malloc(100 * sizeof(char*));
  char* buffer = malloc(INITIAL_SIZE * sizeof(char));
  int query_length = 0;
  printf("%s\n", "enter query:");
  // gets the next queries
  while (GetNextLine(buffer) > 0) {
    query_length = CreateQueries(query, buffer);
    ProcessSearchResults(dt, mi, query, query_length);
    printf("%s\n", "enter query:");
  }
  free(buffer);
  free(query);
}

static int GetNextLine(char* buffer) {
  size_t buffer_size = INITIAL_SIZE;
  size_t total = 0;
  char input;
  int eof = scanf("%c", &input);
  // read until eof or error occurs
  while (eof > 0) {
    // break on a newline
    if (input == '\n') {
      break;
    }
    // stores all input in lower case
    buffer[total] = tolower(input);
    total++;
    // allocate more memory
    if (total >= buffer_size) {
      buffer_size += INITIAL_SIZE;
      buffer = realloc(buffer, buffer_size * sizeof(char));
    }
    eof = scanf("%c", &input);
  }
  buffer[total] = '\0';
  return eof;
}

static int CreateQueries(char** query, char* buffer) {
  size_t query_size = INITIAL_SIZE;
  int query_length = 0;
  char* token;
  char* rest = buffer;
  while ((token = strtok_r(rest, " ", &rest))) {
    query[query_length] = token;
    query_length++;
    // allocate more memory
    if (query_length >= query_size) {
      query_size += INITIAL_SIZE;
      query = realloc(query, query_size * sizeof(char*));
    }
  }
  return query_length;
}

static void ProcessSearchResults(DocTable* dt, MemIndex* mi, char** queries,
                           int query_length) {
  LinkedList* ll_res = MemIndex_Search(mi, (char**) queries, query_length);
  // enter if MemIndex_Search was successful
  if (ll_res != NULL) {
    LLIterator* ll_it = LLIterator_Allocate(ll_res);
    bool has_next = true;
    SearchResult* res;
    while (has_next) {
      LLIterator_Get(ll_it, (LLPayload_t*) &res);
      // print the document names and its rank
      printf("  %s (%d)\n", DocTable_GetDocName(dt, res->doc_id), res->rank);
      has_next = LLIterator_Next(ll_it);
    }
    LLIterator_Free(ll_it);
    LinkedList_Free(ll_res, free);
  }
}
