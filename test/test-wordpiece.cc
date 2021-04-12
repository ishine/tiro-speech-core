// Copyright 2021 Tiro ehf.
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
#include <catch2/catch.hpp>
#include <string>
#include <vector>

#include "src/itn/wordpiece.h"


TEST_CASE(
    "WordPieceTokenizer can split a vector of words into a vector of subwords",
    "[itn]") {
  using namespace tiro_speech::itn;
  WordPieceTokenizerConfig opts;
  opts.vocab_filename = "test/wordpiece-vocab.txt";
  opts.max_input_chars_per_word = 100;
  opts.unk_token = "[UNK]";

  WordPieceTokenizer tokenizer{opts};

  SECTION("Splitting a word that should be split into two works") {
    std::vector<std::string> words{
      "Anna",
      "sem",
      "túlkar",
      "fyrir",
      "okkur"
    };
    std::vector<std::string> expected_word_pieces{
      "Anna",
      "sem",
      "túlka",
      "##r",
      "fyrir",
      "okkur"
    };

    std::vector<std::string> word_pieces = tokenizer.Tokenize(words);
    REQUIRE_THAT(word_pieces, Catch::Matchers::Equals(expected_word_pieces));
  }

  SECTION("Splitting a word that should be split into three works") {
    std::vector<std::string> words{
      "Þórólfur",
      "sóttvarnalæknis"
    };
    std::vector<std::string> expected_word_pieces{
      "Þórólfur",
      "sótt",
      "##varna",
      "##læknis"
    };

    std::vector<std::string> word_pieces = tokenizer.Tokenize(words);
    REQUIRE_THAT(word_pieces, Catch::Matchers::Equals(expected_word_pieces));
  }
}
