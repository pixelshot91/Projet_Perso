#pragma once

#include <fstream>
#include <utility> // pair
#include <queue>

#include "token.hh"

//#include "ast-node.hh"
//#include "AST/number-node.hh"
//#include "AST/bin-op-node.hh"

namespace bistro
{
/**
** AST factory node.
**
** This is an implementation of the factory pattern, where the AST is
** generated based on a stream.
**/
template <typename BigNum, typename Base>
class ASTFactory
{
  public:
  /*enum Token_id
  {
    NUMBER,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    PERCENT,
    L_PAR,
    R_PAR
  };
  std::string token_id_name[8] =
  {
    "number",
    "+",
    "-",
    "*",
    "/",
    "%",
    "(",
    ")"
  };*/

  /// BigNum.
  using num_t = BigNum;
  /// Base.
  using base_t = Base;
  /// Pointer to AST node.
  using node_t = std::shared_ptr<ASTNode<BigNum, Base>>;
  /// Character representation support for a digit.
  using char_t = typename base_t::char_t;

  //using token_t = std::pair<Token_id, typename BigNum::self_ptr_t>;
  using token_t = Token<BigNum>;
  using tokens_t = std::queue<token_t>;

    /**
  ** Read a stream, and return the base and AST represented.
  **
  ** \throw std::domain_error if the input is invalid.
  **/
  std::pair<node_t, base_t> read(std::ifstream& in);

  /**
  ** Read a base from a stream.
  **
  ** The base definition format is as follows:
  **   - the first line contains the numerical value of the base, in base
  **     10.
  **   - the second line contains the representation of each of the
  **     digits of the base, in order.
  **
  ** \throw std::domain_error if the base format is incorrect.
  **/
  base_t read_base(std::ifstream& in);

  /**
  ** Read an AST from the stream, in infix notation.
  **
  ** The operators handled are:
  **   - '+', '-' (both unary and binary)
  **   - '*', '/', '%' with a higher priority
  **   - '(', ')' for grouping
  **
  ** The LL grammar used is the following:
  **
  **   Exp := T
  **        | T '+' Exp
  **        | T '-' Exp
  **
  **   T := F
  **      | F '*' T
  **      | F '/' T
  **      | F '%' T
  **
  **   F := number
  **      | '(' Exp ')'
  **      | '-' F
  **      | '+' F
  **
  ** \throw std::domain_error if the expression is malformed.
  **/
  node_t read_AST(std::ifstream&, const base_t&);
  
 /* void print_token(token_t);
  void print_op(Token_id op);*/

private:
  tokens_t lexer(std::ifstream& in, const base_t& b);
  node_t parse_expr(tokens_t& tokens);
  node_t parse_term(tokens_t& tokens);
  node_t parse_factor(tokens_t& tokens);
  //void eat(tokens_t tokens, Token_id id);

};
}

#include "AST/ast-factory.hxx"
