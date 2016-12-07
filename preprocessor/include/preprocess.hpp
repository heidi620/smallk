// Copyright 2014 Georgia Institute of Technology
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <vector>
#include "term_frequency_matrix.hpp"

// true and false values for masking operations
const unsigned int TT = 0xFFFFFFFF;
const unsigned int FF = 0;

struct IndexedData
{
    uint64_t value;
    uint32_t index;
};

// use SpookyHash to hash the sparse binary matrix columns
void HashColsSpooky(const unsigned int width,
                    const unsigned int* cols,
                    const TFData*    tf_data,
                    std::vector<IndexedData>& hash);

void HashColsSpooky(const unsigned int width,
                    const unsigned int* cols,
                    const unsigned int* rows,
                    std::vector<IndexedData>& hash);

bool preprocess_tf(TermFrequencyMatrix& A,
                   std::vector<unsigned int>& term_indices,
                   std::vector<unsigned int>& doc_indices,
                   std::vector<double>& scores,
                   const unsigned int MAX_ITER,
                   const unsigned int DOCS_PER_TERM,
                   const unsigned int TERMS_PER_DOC);

