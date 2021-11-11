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
  Layout popLeftCommand();
  Layout popRightCommand();
  Layout popSqrtCommand();
  Layout popSpaceCommand();

  //Symbols
  Layout popSymbolCommand(int SymbolIndex);

  const char * m_text;
  const char * m_endOfText;
  bool m_hasError;

  // Expressions that require specific handling
  static constexpr char const * k_fracCommand = "frac";
  static constexpr char const * k_leftCommand = "left";
  static constexpr char const * k_rightCommand = "right";
  static constexpr char const * k_sqrtCommand = "sqrt";
  static constexpr char const * k_spaceCommand = "space";

  static constexpr int const k_NumberOfSymbols = 70;
  static constexpr int const k_NumberOfFunctionCommands = 32;
};
  
}

#endif
