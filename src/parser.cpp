/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

    #include<stdio.h>
    #include<stdlib.h>
    #include<iostream>
    #include"node.h"
    using namespace std;

    NBlock *programBlock; // the top level root node of our final AST
    extern int yylex();
    extern int yylineno;
    void yyerror(const char *s) {
        printf("ERROR: %s\n", s);
    }

#line 86 "parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_TINTEGER = 4,                   /* TINTEGER  */
  YYSYMBOL_TFLOAT = 5,                     /* TFLOAT  */
  YYSYMBOL_TCHAR = 6,                      /* TCHAR  */
  YYSYMBOL_TSTRING = 7,                    /* TSTRING  */
  YYSYMBOL_PLUS = 8,                       /* PLUS  */
  YYSYMBOL_MINUS = 9,                      /* MINUS  */
  YYSYMBOL_MUL = 10,                       /* MUL  */
  YYSYMBOL_DIV = 11,                       /* DIV  */
  YYSYMBOL_AND = 12,                       /* AND  */
  YYSYMBOL_OR = 13,                        /* OR  */
  YYSYMBOL_NOT = 14,                       /* NOT  */
  YYSYMBOL_GAD = 15,                       /* GAD  */
  YYSYMBOL_LET = 16,                       /* LET  */
  YYSYMBOL_GT = 17,                        /* GT  */
  YYSYMBOL_LEQ = 18,                       /* LEQ  */
  YYSYMBOL_GEQ = 19,                       /* GEQ  */
  YYSYMBOL_NEQ = 20,                       /* NEQ  */
  YYSYMBOL_EQU = 21,                       /* EQU  */
  YYSYMBOL_IF = 22,                        /* IF  */
  YYSYMBOL_ELSE = 23,                      /* ELSE  */
  YYSYMBOL_WHILE = 24,                     /* WHILE  */
  YYSYMBOL_BREAK = 25,                     /* BREAK  */
  YYSYMBOL_RETURN = 26,                    /* RETURN  */
  YYSYMBOL_27_ = 27,                       /* '('  */
  YYSYMBOL_28_ = 28,                       /* ')'  */
  YYSYMBOL_29_ = 29,                       /* '['  */
  YYSYMBOL_30_ = 30,                       /* ']'  */
  YYSYMBOL_31_ = 31,                       /* '!'  */
  YYSYMBOL_32_ = 32,                       /* '{'  */
  YYSYMBOL_33_ = 33,                       /* '}'  */
  YYSYMBOL_34_ = 34,                       /* ';'  */
  YYSYMBOL_35_ = 35,                       /* '='  */
  YYSYMBOL_36_ = 36,                       /* ','  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_program = 38,                   /* program  */
  YYSYMBOL_statements = 39,                /* statements  */
  YYSYMBOL_block = 40,                     /* block  */
  YYSYMBOL_stmt = 41,                      /* stmt  */
  YYSYMBOL_var_decl = 42,                  /* var_decl  */
  YYSYMBOL_func_decl = 43,                 /* func_decl  */
  YYSYMBOL_func_decl_args = 44,            /* func_decl_args  */
  YYSYMBOL_ident = 45,                     /* ident  */
  YYSYMBOL_const_value = 46,               /* const_value  */
  YYSYMBOL_expr = 47,                      /* expr  */
  YYSYMBOL_call_args = 48                  /* call_args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  28
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   298

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  102

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,     2,     2,     2,     2,     2,
      27,    28,     2,     2,    36,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
       2,    35,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    29,     2,    30,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    61,    61,    65,    66,    70,    71,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    87,    88,    89,    93,
      97,    98,    99,   103,   107,   108,   109,   110,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     139,   140,   141
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "TINTEGER", "TFLOAT", "TCHAR", "TSTRING", "PLUS", "MINUS", "MUL", "DIV",
  "AND", "OR", "NOT", "GAD", "LET", "GT", "LEQ", "GEQ", "NEQ", "EQU", "IF",
  "ELSE", "WHILE", "BREAK", "RETURN", "'('", "')'", "'['", "']'", "'!'",
  "'{'", "'}'", "';'", "'='", "','", "$accept", "program", "statements",
  "block", "stmt", "var_decl", "func_decl", "func_decl_args", "ident",
  "const_value", "expr", "call_args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-52)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     175,   -52,   -52,   -52,   -52,   -52,    -1,   -18,    -5,   -11,
      42,    57,    43,   175,   -52,    20,   -52,    15,   -52,   122,
      26,    57,    57,   -52,   -52,   -19,   141,   225,   -52,   -52,
     -52,   161,    57,    57,    -8,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,   -52,    57,   239,
     253,   -52,   -52,   -52,   267,   -16,   195,   267,    -1,    52,
      57,   277,   277,   277,   277,   153,   153,   -52,   -52,   -52,
     -52,   -52,   -52,   210,    33,    33,   -52,    57,    31,   -52,
      23,    -1,    38,   267,   -52,    83,    48,   -52,   267,    57,
      33,    -1,   -24,   -52,   -52,    96,    33,   267,   -52,   -52,
     -52,   -52
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    23,    24,    25,    26,    27,     0,     0,     0,     0,
       0,     0,     0,     2,     3,     0,     8,    45,    28,     0,
      48,     0,     0,    13,    14,    45,     0,     0,     1,     4,
       7,    50,     0,     0,    16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     9,     0,     0,
       0,    15,    41,    43,    51,     0,     0,    42,    20,     0,
       0,    29,    30,    31,    32,    39,    40,    37,    38,    34,
      35,    36,    33,     0,     0,     0,    44,     0,    46,    21,
       0,     0,     0,    17,    49,     0,    10,    12,    52,     0,
       0,     0,    16,    18,     6,     0,     0,    47,    19,    22,
       5,    11
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -52,   -52,   -10,   -23,   -12,   -51,   -52,   -52,     0,   -52,
      -7,   -52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    12,    13,    86,    14,    15,    16,    80,    25,    18,
      19,    55
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      17,    29,     1,    26,    27,    59,    20,    79,    31,    21,
      32,    60,    76,    17,    49,    50,    33,    34,     1,    58,
      77,    59,    22,    23,    54,    56,    57,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      99,    73,    31,    28,    32,     1,     2,     3,     4,     5,
      33,    90,    87,    83,    30,    48,    82,     6,    81,    91,
       1,     2,     3,     4,     5,    85,    89,    98,    93,    11,
      88,    96,     6,   101,     0,    95,    24,     0,     0,     0,
       0,    92,    97,    29,    11,    17,     1,     2,     3,     4,
       5,    81,     0,     0,     0,    17,     0,     0,     6,     1,
       2,     3,     4,     5,     0,     7,     0,     8,     9,    10,
      11,     6,     0,     0,     0,     0,    94,     0,     7,     0,
       8,     9,    10,    11,     0,     0,     0,     0,     0,   100,
      35,    36,    37,    38,    39,    40,     0,     0,    41,    42,
      43,    44,    45,    46,     0,     0,     0,     0,     0,    35,
      36,    37,    38,    39,    40,     0,    47,    41,    42,    43,
      44,    45,    46,     0,     1,     2,     3,     4,     5,    41,
      42,    43,    44,    45,    46,    51,     6,     0,     1,     2,
       3,     4,     5,     0,     0,     0,     0,     0,    11,    53,
       6,     0,     0,     0,     0,     0,     0,     7,     0,     8,
       9,    10,    11,    35,    36,    37,    38,    39,    40,     0,
       0,    41,    42,    43,    44,    45,    46,     0,    35,    36,
      37,    38,    39,    40,     0,    78,    41,    42,    43,    44,
      45,    46,     0,    35,    36,    37,    38,    39,    40,     0,
      84,    41,    42,    43,    44,    45,    46,    35,    36,    37,
      38,    39,    40,    52,     0,    41,    42,    43,    44,    45,
      46,    35,    36,    37,    38,    39,    40,    74,     0,    41,
      42,    43,    44,    45,    46,    35,    36,    37,    38,    39,
      40,    75,     0,    41,    42,    43,    44,    45,    46,    39,
      40,     0,     0,    41,    42,    43,    44,    45,    46
};

static const yytype_int8 yycheck[] =
{
       0,    13,     3,    10,    11,    29,     6,    58,    27,    27,
      29,    35,    28,    13,    21,    22,    35,    17,     3,    27,
      36,    29,    27,    34,    31,    32,    33,    35,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      91,    48,    27,     0,    29,     3,     4,     5,     6,     7,
      35,    28,    75,    60,    34,    29,     4,    15,    58,    36,
       3,     4,     5,     6,     7,    32,    35,    90,    30,    27,
      77,    23,    15,    96,    -1,    85,    34,    -1,    -1,    -1,
      -1,    81,    89,    95,    27,    85,     3,     4,     5,     6,
       7,    91,    -1,    -1,    -1,    95,    -1,    -1,    15,     3,
       4,     5,     6,     7,    -1,    22,    -1,    24,    25,    26,
      27,    15,    -1,    -1,    -1,    -1,    33,    -1,    22,    -1,
      24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,    33,
       8,     9,    10,    11,    12,    13,    -1,    -1,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,     8,
       9,    10,    11,    12,    13,    -1,    34,    16,    17,    18,
      19,    20,    21,    -1,     3,     4,     5,     6,     7,    16,
      17,    18,    19,    20,    21,    34,    15,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    27,    28,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,    24,
      25,    26,    27,     8,     9,    10,    11,    12,    13,    -1,
      -1,    16,    17,    18,    19,    20,    21,    -1,     8,     9,
      10,    11,    12,    13,    -1,    30,    16,    17,    18,    19,
      20,    21,    -1,     8,     9,    10,    11,    12,    13,    -1,
      30,    16,    17,    18,    19,    20,    21,     8,     9,    10,
      11,    12,    13,    28,    -1,    16,    17,    18,    19,    20,
      21,     8,     9,    10,    11,    12,    13,    28,    -1,    16,
      17,    18,    19,    20,    21,     8,     9,    10,    11,    12,
      13,    28,    -1,    16,    17,    18,    19,    20,    21,    12,
      13,    -1,    -1,    16,    17,    18,    19,    20,    21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    15,    22,    24,    25,
      26,    27,    38,    39,    41,    42,    43,    45,    46,    47,
      45,    27,    27,    34,    34,    45,    47,    47,     0,    41,
      34,    27,    29,    35,    45,     8,     9,    10,    11,    12,
      13,    16,    17,    18,    19,    20,    21,    34,    29,    47,
      47,    34,    28,    28,    47,    48,    47,    47,    27,    29,
      35,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    28,    28,    28,    36,    30,    42,
      44,    45,     4,    47,    30,    32,    40,    40,    47,    35,
      28,    36,    45,    30,    33,    39,    23,    47,    40,    42,
      33,    40
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    41,    41,    41,
      41,    41,    41,    41,    41,    41,    42,    42,    42,    43,
      44,    44,    44,    45,    46,    46,    46,    46,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      48,    48,    48
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     3,     2,     2,     1,     2,
       5,     7,     5,     2,     2,     3,     2,     4,     5,     6,
       0,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     1,     4,     6,     2,     5,
       0,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statements  */
#line 61 "parser.y"
               { programBlock = (yyvsp[0].block);}
#line 1220 "parser.cpp"
    break;

  case 3: /* statements: stmt  */
#line 65 "parser.y"
         { (yyval.block) = new NBlock(yylineno); (yyval.block)->stmts.push_back((yyvsp[0].stmt));}
#line 1226 "parser.cpp"
    break;

  case 4: /* statements: statements stmt  */
#line 66 "parser.y"
                      { (yyvsp[-1].block)->stmts.push_back((yyvsp[0].stmt));}
#line 1232 "parser.cpp"
    break;

  case 5: /* block: '{' statements '}'  */
#line 70 "parser.y"
                       { (yyval.block) = (yyvsp[-1].block);}
#line 1238 "parser.cpp"
    break;

  case 6: /* block: '{' '}'  */
#line 71 "parser.y"
              { (yyval.block) = new NBlock(yylineno);}
#line 1244 "parser.cpp"
    break;

  case 9: /* stmt: expr ';'  */
#line 77 "parser.y"
               { (yyval.stmt) = new NExpressionStatement(*(yyvsp[-1].expr), yylineno);}
#line 1250 "parser.cpp"
    break;

  case 10: /* stmt: IF '(' expr ')' block  */
#line 78 "parser.y"
                            { (yyval.stmt) = new NIfStatement(*(yyvsp[-2].expr), *(yyvsp[0].block), yylineno);}
#line 1256 "parser.cpp"
    break;

  case 11: /* stmt: IF '(' expr ')' block ELSE block  */
#line 79 "parser.y"
                                       { (yyval.stmt) = new NIfElseStatement(*(yyvsp[-4].expr), *(yyvsp[-2].block), *(yyvsp[0].block), yylineno);}
#line 1262 "parser.cpp"
    break;

  case 12: /* stmt: WHILE '(' expr ')' block  */
#line 80 "parser.y"
                               { (yyval.stmt) = new NWhileStatement(*(yyvsp[-2].expr), *(yyvsp[0].block), yylineno);}
#line 1268 "parser.cpp"
    break;

  case 13: /* stmt: BREAK ';'  */
#line 81 "parser.y"
                { (yyval.stmt) = new NBreakStatement(yylineno);}
#line 1274 "parser.cpp"
    break;

  case 14: /* stmt: RETURN ';'  */
#line 82 "parser.y"
                 { (yyval.stmt) = new NReturnVoidStatement(yylineno);}
#line 1280 "parser.cpp"
    break;

  case 15: /* stmt: RETURN expr ';'  */
#line 83 "parser.y"
                      { (yyval.stmt) = new NReturnStatement(*(yyvsp[-1].expr), yylineno);}
#line 1286 "parser.cpp"
    break;

  case 16: /* var_decl: ident ident  */
#line 87 "parser.y"
                { (yyval.stmt) = new NVariableDeclaration(*(yyvsp[-1].ident), *(yyvsp[0].ident), yylineno);}
#line 1292 "parser.cpp"
    break;

  case 17: /* var_decl: ident ident '=' expr  */
#line 88 "parser.y"
                           { (yyval.stmt) = new NVariableDeclaration(*(yyvsp[-3].ident), *(yyvsp[-2].ident), (yyvsp[0].expr), yylineno);}
#line 1298 "parser.cpp"
    break;

  case 18: /* var_decl: ident ident '[' TINTEGER ']'  */
#line 89 "parser.y"
                                   { (yyval.stmt) = new NVariableDeclaration(*(yyvsp[-4].ident), *(yyvsp[-3].ident), atoi((yyvsp[-1].str)->c_str()), yylineno);}
#line 1304 "parser.cpp"
    break;

  case 19: /* func_decl: ident ident '(' func_decl_args ')' block  */
#line 93 "parser.y"
                                             { (yyval.stmt) = new NFunctionDeclaration(*(yyvsp[-5].ident), *(yyvsp[-4].ident), *(yyvsp[-2].var_list), *(yyvsp[0].block), yylineno); delete (yyvsp[-2].var_list);}
#line 1310 "parser.cpp"
    break;

  case 20: /* func_decl_args: %empty  */
#line 97 "parser.y"
                {(yyval.var_list) = new VariableList();}
#line 1316 "parser.cpp"
    break;

  case 21: /* func_decl_args: var_decl  */
#line 98 "parser.y"
               { (yyval.var_list) = new VariableList(); (yyval.var_list)->push_back((yyvsp[0].variable_decl));}
#line 1322 "parser.cpp"
    break;

  case 22: /* func_decl_args: func_decl_args ',' var_decl  */
#line 99 "parser.y"
                                  { (yyvsp[-2].var_list)->push_back((yyvsp[0].variable_decl));}
#line 1328 "parser.cpp"
    break;

  case 23: /* ident: IDENTIFIER  */
#line 103 "parser.y"
               { (yyval.ident) = new NIdentifier(*(yyvsp[0].str), yylineno); delete (yyvsp[0].str);}
#line 1334 "parser.cpp"
    break;

  case 24: /* const_value: TINTEGER  */
#line 107 "parser.y"
             { (yyval.expr) = new NInteger(atol((yyvsp[0].str)->c_str()), yylineno); delete (yyvsp[0].str);}
#line 1340 "parser.cpp"
    break;

  case 25: /* const_value: TFLOAT  */
#line 108 "parser.y"
             { (yyval.expr) = new NFloat((atof((yyvsp[0].str)->c_str())), yylineno); delete (yyvsp[0].str);}
#line 1346 "parser.cpp"
    break;

  case 26: /* const_value: TCHAR  */
#line 109 "parser.y"
            { (yyval.expr) = new NChar(*(yyvsp[0].str), yylineno); delete (yyvsp[0].str);}
#line 1352 "parser.cpp"
    break;

  case 27: /* const_value: TSTRING  */
#line 110 "parser.y"
              { (yyval.expr) = new NString(*(yyvsp[0].str), yylineno); delete (yyvsp[0].str);}
#line 1358 "parser.cpp"
    break;

  case 29: /* expr: expr PLUS expr  */
#line 115 "parser.y"
                     { (yyval.expr) = new NBinaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr), *(yyvsp[0].expr), yylineno);}
#line 1364 "parser.cpp"
    break;

  case 30: /* expr: expr MINUS expr  */
#line 116 "parser.y"
                      { (yyval.expr) = new NBinaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr), *(yyvsp[0].expr), yylineno);}
#line 1370 "parser.cpp"
    break;

  case 31: /* expr: expr MUL expr  */
#line 117 "parser.y"
                    { (yyval.expr) = new NBinaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr), *(yyvsp[0].expr), yylineno);}
#line 1376 "parser.cpp"
    break;

  case 32: /* expr: expr DIV expr  */
#line 118 "parser.y"
                    { (yyval.expr) = new NBinaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr), *(yyvsp[0].expr), yylineno);}
#line 1382 "parser.cpp"
    break;

  case 33: /* expr: expr EQU expr  */
#line 119 "parser.y"
                    { (yyval.expr) = new NBinaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr), *(yyvsp[0].expr), yylineno);}
#line 1388 "parser.cpp"
    break;

  case 34: /* expr: expr LEQ expr  */
#line 120 "parser.y"
                    { (yyval.expr) = new NBinaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr), *(yyvsp[0].expr), yylineno);}
#line 1394 "parser.cpp"
    break;

  case 35: /* expr: expr GEQ expr  */
#line 121 "parser.y"
                    { (yyval.expr) = new NBinaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr), *(yyvsp[0].expr), yylineno);}
#line 1400 "parser.cpp"
    break;

  case 36: /* expr: expr NEQ expr  */
#line 122 "parser.y"
                    { (yyval.expr) = new NBinaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr), *(yyvsp[0].expr), yylineno);}
#line 1406 "parser.cpp"
    break;

  case 37: /* expr: expr LET expr  */
#line 123 "parser.y"
                    { (yyval.expr) = new NBinaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr), *(yyvsp[0].expr), yylineno);}
#line 1412 "parser.cpp"
    break;

  case 38: /* expr: expr GT expr  */
#line 124 "parser.y"
                   { (yyval.expr) = new NBinaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr), *(yyvsp[0].expr), yylineno);}
#line 1418 "parser.cpp"
    break;

  case 39: /* expr: expr AND expr  */
#line 125 "parser.y"
                    { (yyval.expr) = new NBinaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr), *(yyvsp[0].expr), yylineno);}
#line 1424 "parser.cpp"
    break;

  case 40: /* expr: expr OR expr  */
#line 126 "parser.y"
                   { (yyval.expr) = new NBinaryOperator((yyvsp[-1].token), *(yyvsp[-2].expr), *(yyvsp[0].expr), yylineno);}
#line 1430 "parser.cpp"
    break;

  case 41: /* expr: '(' expr ')'  */
#line 127 "parser.y"
                   { (yyval.expr) = (yyvsp[-1].expr);}
#line 1436 "parser.cpp"
    break;

  case 42: /* expr: ident '=' expr  */
#line 128 "parser.y"
                     { (yyval.expr) = new NAssignment(*(yyvsp[-2].ident), *(yyvsp[0].expr), yylineno);}
#line 1442 "parser.cpp"
    break;

  case 43: /* expr: ident '(' ')'  */
#line 129 "parser.y"
                    { (yyval.expr) = new NFunctionCall(*(yyvsp[-2].ident), yylineno);}
#line 1448 "parser.cpp"
    break;

  case 44: /* expr: ident '(' call_args ')'  */
#line 130 "parser.y"
                              { (yyval.expr) = new NFunctionCall(*(yyvsp[-3].ident), *(yyvsp[-1].exp_list), yylineno); delete (yyvsp[-1].exp_list);}
#line 1454 "parser.cpp"
    break;

  case 45: /* expr: ident  */
#line 131 "parser.y"
            { (yyval.ident) = (yyvsp[0].ident);}
#line 1460 "parser.cpp"
    break;

  case 46: /* expr: ident '[' expr ']'  */
#line 132 "parser.y"
                         { (yyval.expr) = new NArrayElement(*(yyvsp[-3].ident), *(yyvsp[-1].expr), yylineno);}
#line 1466 "parser.cpp"
    break;

  case 47: /* expr: ident '[' expr ']' '=' expr  */
#line 133 "parser.y"
                                  { (yyval.expr) = new NArrayElementAssign(*(yyvsp[-5].ident), *(yyvsp[-3].expr), *(yyvsp[0].expr), yylineno);}
#line 1472 "parser.cpp"
    break;

  case 48: /* expr: GAD ident  */
#line 134 "parser.y"
                { (yyval.expr) = new NGetAddr(*(yyvsp[0].ident), yylineno);}
#line 1478 "parser.cpp"
    break;

  case 49: /* expr: GAD ident '[' expr ']'  */
#line 135 "parser.y"
                             { (yyval.expr) = new NGetArrayAddr(*(yyvsp[-3].ident), *(yyvsp[-1].expr), yylineno);}
#line 1484 "parser.cpp"
    break;

  case 50: /* call_args: %empty  */
#line 139 "parser.y"
                { (yyval.exp_list) = new ExpressionList();}
#line 1490 "parser.cpp"
    break;

  case 51: /* call_args: expr  */
#line 140 "parser.y"
           { (yyval.exp_list) = new ExpressionList(); (yyval.exp_list)->push_back((yyvsp[0].expr));}
#line 1496 "parser.cpp"
    break;

  case 52: /* call_args: call_args ',' expr  */
#line 141 "parser.y"
                         { (yyvsp[-2].exp_list)->push_back((yyvsp[0].expr));}
#line 1502 "parser.cpp"
    break;


#line 1506 "parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 148 "parser.y"
