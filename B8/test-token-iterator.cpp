#include "boost/test/auto_unit_test.hpp"
#include "token-iterator.hpp"

#include <vector>
#include <algorithm>
#include <sstream>

BOOST_AUTO_TEST_SUITE(TokenIteratorTests)

BOOST_AUTO_TEST_CASE(TokenIteratorSingleWord)
{
  std::string text = "word";
  std::vector<token_t> expected =
  {
    token_t{token_t::KindOfToken::WORD, "word"},
  };
  std::stringstream input(text);
  std::vector<token_t> output;
  std::copy(TokenIterator(input), TokenIterator(), std::back_inserter(output));

  BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(TokenIteratorSingleNumberPositiveInteger)
{
  std::string text = "+1925";
  std::vector<token_t> expected =
  {
    token_t{token_t::KindOfToken::NUMBER, "+1925"},
  };
  std::stringstream input(text);
  std::vector<token_t> output;
  std::copy(TokenIterator(input), TokenIterator(), std::back_inserter(output));

  BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(), expected.begin(), expected.end());
}
BOOST_AUTO_TEST_CASE(TokenIteratorSingleNumberNegativeInteger)
{
  std::string text = "-1933";
  std::vector<token_t> expected =
  {
    token_t{token_t::KindOfToken::NUMBER, "-1933"},
  };
  std::stringstream input(text);
  std::vector<token_t> output;
  std::copy(TokenIterator(input), TokenIterator(), std::back_inserter(output));

  BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(), expected.begin(), expected.end());
}
BOOST_AUTO_TEST_CASE(TokenIteratorSingleNumberFractional)
{
  std::string text = "1924.1953";
  std::vector<token_t> expected =
  {
    token_t{token_t::KindOfToken::NUMBER, "1924.1953"},
  };
  std::stringstream input(text);
  std::vector<token_t> output;
  std::copy(TokenIterator(input), TokenIterator(), std::back_inserter(output));

  BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(), expected.begin(), expected.end());
}
BOOST_AUTO_TEST_CASE(TokenIteratorCommaAndDash)
{
  std::string text = "word,---";
  std::vector<token_t> expected =
  {
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ","},
    token_t{token_t::KindOfToken::DASH, "---"},
  };
  std::stringstream input(text);
  std::vector<token_t> output;
  std::copy(TokenIterator(input), TokenIterator(), std::back_inserter(output));

  BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(), expected.begin(), expected.end());
}
BOOST_AUTO_TEST_CASE(TokenIteratorDashWithoutSpaces)
{
  std::string text = "word---word---10---+20---words---";
  std::vector<token_t> expected =
  {
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::NUMBER, "10"},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::NUMBER, "+20"},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::WORD, "words"},
    token_t{token_t::KindOfToken::DASH, "---"},
  };
  std::stringstream input(text);
  std::vector<token_t> output;
  std::copy(TokenIterator(input), TokenIterator(), std::back_inserter(output));

  BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(TokenIteratorVariousData)
{
  std::string text =
      "word-word---word-word-word  ,\
      something:really:not_important +1649---1721\
      \t\t\t10.10,--- \nhello\nhello---42.";
  std::vector<token_t> expected =
  {
    token_t{token_t::KindOfToken::WORD, "word-word"},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::WORD, "word-word-word"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ","},
    token_t{token_t::KindOfToken::WORD, "something"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ":"},
    token_t{token_t::KindOfToken::WORD, "really"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ":"},
    token_t{token_t::KindOfToken::WORD, "not"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, "_"},
    token_t{token_t::KindOfToken::WORD, "important"},
    token_t{token_t::KindOfToken::NUMBER, "+1649"},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::NUMBER, "1721"},
    token_t{token_t::KindOfToken::NUMBER, "10.10"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ","},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::WORD, "hello"},
    token_t{token_t::KindOfToken::WORD, "hello"},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::NUMBER, "42"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, "."},
  };
  std::stringstream input(text);
  std::vector<token_t> output;
  std::copy(TokenIterator(input), TokenIterator(), std::back_inserter(output));

  BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(), expected.begin(), expected.end());
}
BOOST_AUTO_TEST_CASE(TokenIteratorEmptyInput)
{
  std::string text1;
  std::string text2 = "         \t\n\n\t";

  std::vector<token_t> expected1;
  std::vector<token_t> expected2;

  std::stringstream input1(text1);
  std::stringstream input2(text2);

  std::vector<token_t> output1;
  std::vector<token_t> output2;

  std::copy(TokenIterator(input1), TokenIterator(), std::back_inserter(output1));
  std::copy(TokenIterator(input2), TokenIterator(), std::back_inserter(output2));
  BOOST_CHECK_EQUAL_COLLECTIONS(output1.begin(), output1.end(), expected1.begin(), expected1.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(output2.begin(), output2.end(), expected2.begin(), expected2.end());

}
BOOST_AUTO_TEST_CASE(TokenIteratorInvalidTokens)
{
  std::string text = "word1, word2";
  std::vector<token_t> expected =
  {
    token_t{token_t::KindOfToken::INVALID, "word"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ","},
    token_t{token_t::KindOfToken::INVALID, "word"},
  };
  std::stringstream input(text);
  std::vector<token_t> output;
  std::copy(TokenIterator(input), TokenIterator(), std::back_inserter(output));

  BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(), expected.begin(), expected.end());
}
BOOST_AUTO_TEST_SUITE_END()
