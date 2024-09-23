//
// Created by leo on 24-9-22.
//

#include "util/buf_match.h"

uint8_t BufMatch::pattern[3] = {0x00, 0x00, 0x03};
std::boyer_moore_searcher<const uint8_t*> BufMatch::searcher00(pattern, pattern+2);
std::boyer_moore_searcher<const uint8_t*> BufMatch::searcher003(pattern, pattern+3);

