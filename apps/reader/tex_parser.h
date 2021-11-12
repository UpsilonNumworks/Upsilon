#ifndef __TEX_PARSER_H__
#define __TEX_PARSER_H__

#include <poincare_layouts.h>
#include <poincare/layout_helper.h>
#include <string.h>

using namespace Poincare;

namespace Reader
{
/// @brief Class used in the WordWrapTextView class to parse a Tex expression
class TexParser {
public:
  TexParser(const char * text, const char * endOfText);
  Layout getLayout();
private:
  Layout popBlock();
  Layout popText(char stop);
  Layout popCommand();

  // Expressions
  Layout popFracCommand();
  Layout popSqrtCommand();
  Layout popOverrightarrowCommand();

  //Symbols
  Layout popSymbolCommand(int SymbolIndex);

  const char * m_text;
  const char * m_endOfText;
  bool m_hasError;

  inline bool isCommandEnded(char c) const;

  // Expressions that require specific handling
  static constexpr char const * k_fracCommand = "frac";
  static constexpr char const * k_sqrtCommand = "sqrt";
  static constexpr char const * k_overrightArrowCommand = "overrightarrow";

  static constexpr int const k_NumberOfSymbols = 70;
  static constexpr int const k_NumberOfFunctionCommands = 32;
};
  
}

#endif
