#include "boost/test/auto_unit_test.hpp"
#include "formatting-iterator.hpp"

#include <vector>
#include <algorithm>
#include <sstream>

BOOST_AUTO_TEST_SUITE(FormattingIteratorTests)

BOOST_AUTO_TEST_CASE(FormattingIteratorEmptyInput)
{
  std::vector<token_t> tokens;
  std::string expected;
  std::stringstream output;
  std::copy(tokens.begin(), tokens.end(), FormattingIterator(output, 10));
  BOOST_CHECK_EQUAL(output.str(), expected);
}

BOOST_AUTO_TEST_CASE(FormattingIteratorVariousData)
{
  std::vector<token_t> tokens =
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
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, "."}
  };
  std::string expected = "word-word --- word-word-word, something:\nreally: not_ important +1649 --- 1721\n10.10, --- hello hello --- 42.\n";
  std::stringstream output;
  std::copy(tokens.begin(), tokens.end(), FormattingIterator(output, 40));
  BOOST_CHECK_EQUAL(output.str(), expected);
}

BOOST_AUTO_TEST_CASE(FormattingIteratorDataCarryOverBeforeNumberCommaAndDash)
{
  std::vector<token_t> tokens =
  {
    token_t{token_t::KindOfToken::NUMBER, "123456789"},
    token_t{token_t::KindOfToken::NUMBER, "123456789"},
    token_t{token_t::KindOfToken::NUMBER, "12"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ","},
    token_t{token_t::KindOfToken::DASH, "---"},
  };
  std::string expected = "123456789 123456789\n12, ---\n";
  std::stringstream output;
  std::copy(tokens.begin(), tokens.end(), FormattingIterator(output, 25));
  BOOST_CHECK_EQUAL(output.str(), expected);
}
BOOST_AUTO_TEST_CASE(FormattingIteratorDataCarryOverBeforeWordCommaAndDash)
{
  std::vector<token_t> tokens =
  {
    token_t{token_t::KindOfToken::WORD, "wordwordword"},
    token_t{token_t::KindOfToken::WORD, "wordwordword"},
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ","},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, "&"},
  };
  std::string expected = "wordwordword wordwordword\nword, --- word&\n";
  std::stringstream output;
  std::copy(tokens.begin(), tokens.end(), FormattingIterator(output, 30));
  BOOST_CHECK_EQUAL(output.str(), expected);
}

BOOST_AUTO_TEST_CASE(FormattingIteratorDataCarryOverBeforeComma)
{
  std::vector<token_t> tokens =
  {
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::WORD, "words"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ","},
    token_t{token_t::KindOfToken::WORD, "mm"},
    token_t{token_t::KindOfToken::WORD, "words-my-words"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, "."},
  };
  std::string expected = "word word word word word word word\nwords, mm words-my-words.\n";
  std::stringstream output;
  std::copy(tokens.begin(), tokens.end(), FormattingIterator(output, 40));
  BOOST_CHECK_EQUAL(output.str(), expected);
}
BOOST_AUTO_TEST_SUITE_END()
