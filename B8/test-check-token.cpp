#include "boost/test/auto_unit_test.hpp"
#include "check-token.hpp"

#include <vector>
#include <algorithm>

BOOST_AUTO_TEST_SUITE(CheckTokenTests)

BOOST_AUTO_TEST_CASE(CheckTokenEmptyInput)
{
  std::vector<token_t> tokens;
  BOOST_CHECK_NO_THROW(std::for_each(tokens.begin(), tokens.end(), check_token()));
}

BOOST_AUTO_TEST_CASE(CheckTokenVariousData)
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
  BOOST_CHECK_NO_THROW(std::for_each(tokens.begin(), tokens.end(), check_token()));
}
BOOST_AUTO_TEST_CASE(CheckTokenStartsWithPunctuation)
{
  std::vector<token_t> tokens =
  {
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, "."},
    token_t{token_t::KindOfToken::WORD, "word-word"},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::WORD, "word-word-word"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ","}
  };
  BOOST_CHECK_THROW(std::for_each(tokens.begin(), tokens.end(), check_token()), std::runtime_error);
}
BOOST_AUTO_TEST_CASE(CheckTokenContractingPunctuationCommaComma)
{
  std::vector<token_t> tokens =
  {
    token_t{token_t::KindOfToken::WORD, "word-word"},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::WORD, "smt"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ","},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ","}
  };
  BOOST_CHECK_THROW(std::for_each(tokens.begin(), tokens.end(), check_token()), std::runtime_error);
}
BOOST_AUTO_TEST_CASE(CheckTokenContractingPunctuationDashComma)
{
  std::vector<token_t> tokens =
  {
    token_t{token_t::KindOfToken::WORD, "word-word"},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::WORD, "smt"},
    token_t{token_t::KindOfToken::DASH, "---"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, ","}
  };
  BOOST_CHECK_THROW(std::for_each(tokens.begin(), tokens.end(), check_token()), std::runtime_error);
}
BOOST_AUTO_TEST_CASE(CheckTokenContractingInvalidSize)
{
  std::vector<token_t> tokens =
  {
    token_t{token_t::KindOfToken::WORD, "deep"},
    token_t{token_t::KindOfToken::WORD, "breath"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, "."},
    token_t{token_t::KindOfToken::WORD, "aaaaaaaaaaaaaaaaaaaaa"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, "!"}
  };
  BOOST_CHECK_THROW(std::for_each(tokens.begin(), tokens.end(), check_token()), std::runtime_error);
}
BOOST_AUTO_TEST_CASE(CheckTokenContractingInvalidToken)
{
  std::vector<token_t> tokens =
  {
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::WORD, "word"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, "."},
    token_t{token_t::KindOfToken::INVALID, "invalid"},
    token_t{token_t::KindOfToken::PUNCTUATION_MARK, "@"}
  };
  BOOST_CHECK_THROW(std::for_each(tokens.begin(), tokens.end(), check_token()), std::runtime_error);
}
BOOST_AUTO_TEST_SUITE_END()
