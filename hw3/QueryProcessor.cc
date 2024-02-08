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

#include "./QueryProcessor.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <vector>
#include <map>

extern "C" {
  #include "./libhw1/CSE333.h"
}

using std::list;
using std::sort;
using std::string;
using std::vector;
using std::map;

namespace hw3 {

// looks up IDs from doc_id_map, if found it pushes a
// QueryResult into final_result
// Arguments:
// - final_result: the place to store the query result (an output parameter)
// - doc_id_map: a map containing doc_ids as keys and number of positions
//   as values
// - dtr: array of DocTableReader used for looking up a doc ID
static void ProcessIDLookUp(vector<QueryProcessor::QueryResult>* final_result,
                            map<DocID_t, int32_t> doc_id_map,
                            DocTableReader* dtr);

// Creats a map of DocID_t and int32_t which are the doc ids and
// number of positions
// Arguments:
// - doc_id_map: a map containing doc_ids as keys and number of positions
//   as values (an output parameter)
// - dIDtr: DocIDTableReader used to get list of doc ids
static void CreateMap(map<DocID_t, int32_t>* doc_id_map,
                      DocIDTableReader* dIDtr);

// Intersects 2 maps who share the same indexes
// Arguments:
// - doc_id_map: a map containing doc_ids as keys and number of positions
//   as values (an output parameter)
// - dIDtr: DocIDTableReader used to get list of doc ids
static void QueryIntersector(map<DocID_t, int32_t>* doc_id_map,
                             DocIDTableReader* dIDtr);

QueryProcessor::QueryProcessor(const list<string>& index_list, bool validate) {
  // Stash away a copy of the index list.
  index_list_ = index_list;
  array_len_ = index_list_.size();
  Verify333(array_len_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader* [array_len_];
  itr_array_ = new IndexTableReader* [array_len_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::const_iterator idx_iterator = index_list_.begin();
  for (int i = 0; i < array_len_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = fir.NewDocTableReader();
    itr_array_[i] = fir.NewIndexTableReader();
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (int i = 0; i < array_len_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

// This structure is used to store a index-file-specific query result.
typedef struct {
  DocID_t doc_id;  // The document ID within the index file.
  int     rank;    // The rank of the result so far.
} IdxQueryResult;

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string>& query) const {
  Verify333(query.size() > 0);

  // STEP 1.
  // (the only step in this file)
  vector<QueryProcessor::QueryResult> final_result;
  for (int i = 0; i < array_len_; i++) {
    vector<QueryProcessor::QueryResult>* final_result_ptr = &final_result;
    DocTableReader* dtr = dtr_array_[i];
    IndexTableReader* itr = itr_array_[i];
    // look up first query word
    DocIDTableReader* dIDtr = itr->LookupWord(query[0]);
    // check that the word was found
    if (dIDtr == nullptr) {
      continue;
    }
    map<DocID_t, int32_t> doc_id_map;
    map<DocID_t, int32_t>* doc_id_map_ptr = &doc_id_map;
    CreateMap(doc_id_map_ptr, dIDtr);
    // of there is only one word we are done processing this current
    // DocTableReader and IndexTableReader
    if (query.size() == 1) {
      ProcessIDLookUp(final_result_ptr, doc_id_map, dtr);
      continue;
    }
    // process the rest of the words in the query
    for (int i = 1; i < static_cast<int>(query.size()); i++) {
      // look up additional words
      dIDtr = itr->LookupWord(query[i]);
      // since dIDtr is null this means there were no matches
      // therfore we empty the doc_id_list;
      if (dIDtr == nullptr) {
        doc_id_map.clear();
        break;
      }
      // intersect indexes
      QueryIntersector(doc_id_map_ptr, dIDtr);
      // no intersection means we break
      if (doc_id_map.size() == 0) {
        break;
      }
    }
    // check that the map is not empty to process ids
    if (doc_id_map.size() != 0) {
      ProcessIDLookUp(final_result_ptr, doc_id_map, dtr);
    }
  }

  // Sort the final results.
  sort(final_result.begin(), final_result.end());
  return final_result;
}

static void ProcessIDLookUp(vector<QueryProcessor::QueryResult>* final_result,
                            map<DocID_t, int32_t> doc_id_map,
                            DocTableReader* dtr) {
  string name;
  for (auto& map_pair : doc_id_map) {
    if (dtr->LookupDocID(map_pair.first, &name)) {
      QueryProcessor::QueryResult qr;
      qr.document_name = name;
      qr.rank = map_pair.second;
      (*final_result).push_back(qr);
    }
  }
}

static void CreateMap(map<DocID_t, int32_t>* doc_id_map,
                      DocIDTableReader* dIDtr) {
    for (DocIDElementHeader& idh : dIDtr->GetDocIDList()) {
      (*doc_id_map)[idh.doc_id] = idh.num_positions;
    }
    delete dIDtr;
}

static void QueryIntersector(map<DocID_t, int32_t>* doc_id_map,
                            DocIDTableReader* dIDtr) {
    map<DocID_t, int32_t> map_to_intersect;
    map<DocID_t, int32_t>* map_to_intersect_ptr = &map_to_intersect;
    CreateMap(map_to_intersect_ptr, dIDtr);
    map<DocID_t, int32_t> temp_map;
    for (auto& match : *doc_id_map) {
      if (map_to_intersect.find(match.first) != map_to_intersect.end()) {
        temp_map[match.first] = match.second + map_to_intersect[match.first];
      }
    }
    *doc_id_map = temp_map;
}

}  // namespace hw3
