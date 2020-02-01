#include "formatting-iterator.hpp"

class FormattingIterator::Impl
{
public:
  Impl(std::ostream& out, size_t lineWidth);
  ~Impl();
  void operator=(const token_t& token);

private:
  std::ostream& out_;
  std::string line;
  size_t lineWidth_;
  token_t last_;
  bool isFirst_;
  int transferPoint_;
};

FormattingIterator::FormattingIterator(std::ostream& out, size_t lineWidth):
  pimpl_(std::make_shared<Impl>(out, lineWidth))
{
}
FormattingIterator& FormattingIterator::operator*()
{
  return *(this);
}
void FormattingIterator::operator=(const token_t& token)
{
  *pimpl_ = token;
}
FormattingIterator::Impl::Impl(std::ostream& out, size_t lineWidth):
  out_(out),
  lineWidth_(lineWidth),
  isFirst_(true)
{
  line.reserve(lineWidth_);
}
FormattingIterator::Impl::~Impl()
{
  if (!out_)
  {
    return;
  }
  if (!line.empty())
  {
    out_ << line << "\n";
  }
}
void FormattingIterator::Impl::operator=(const token_t& token)
{
  if (isFirst_)
  {
    isFirst_ = false;
    line = token.data;
    last_ = token;
    return;
  }
  if ((last_.kind != token_t::PUNCTUATION_MARK) || (token.kind != token_t::DASH))
  {
    transferPoint_ = 0;
  }
  if ((token.kind != token_t::PUNCTUATION_MARK) && (token.kind != token_t::DASH))
  {
    transferPoint_ = line.size();
  }
  else if (last_.kind != token_t::PUNCTUATION_MARK)
  {
    transferPoint_ = line.size() - last_.data.size() - 1;
  }
  if (token.kind == token_t::PUNCTUATION_MARK)
  {
    line += token.data;
  }
  else
  {
    line += ' ' + token.data;
  }
  if (line.size() > lineWidth_)
  {
    out_.write(line.c_str(), transferPoint_);
    out_ << "\n";
    line.erase(0, transferPoint_);
    if (std::isblank(line.front()))
    {
      line.erase(line.begin());
    }
  }
  transferPoint_ = line.size() - last_.data.size() - 2;
  last_ = token;
}
