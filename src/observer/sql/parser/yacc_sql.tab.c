/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "yacc_sql.y" /* yacc.c:339  */


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  size_t multi_insert_lines;
  extraValues extraValue[MAX_NUM];
  CompOp comp;
  AggreType aggre_type[MAX_NUM];
  int asc_desc;
	char id[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  context->asc_desc = -1;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 128 "yacc_sql.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yacc_sql.tab.h".  */
#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    UNIQUE = 264,
    SELECT = 265,
    DESC = 266,
    SHOW = 267,
    SYNC = 268,
    INSERT = 269,
    DELETE = 270,
    UPDATE = 271,
    LBRACE = 272,
    RBRACE = 273,
    COMMA = 274,
    TRX_BEGIN = 275,
    TRX_COMMIT = 276,
    TRX_ROLLBACK = 277,
    INT_T = 278,
    STRING_T = 279,
    FLOAT_T = 280,
    DATE_T = 281,
    TEXT_T = 282,
    HELP = 283,
    EXIT = 284,
    DOT = 285,
    INTO = 286,
    VALUES = 287,
    FROM = 288,
    WHERE = 289,
    AND = 290,
    SET = 291,
    ON = 292,
    LOAD = 293,
    DATA = 294,
    INFILE = 295,
    EQ = 296,
    IN = 297,
    NOTIN = 298,
    LT = 299,
    GT = 300,
    LE = 301,
    GE = 302,
    NE = 303,
    COU = 304,
    MI = 305,
    MA = 306,
    AV = 307,
    NOT = 308,
    NULL_TOKEN = 309,
    NULLABLE = 310,
    IS = 311,
    ISNOT = 312,
    GROUP = 313,
    BY = 314,
    ASC = 315,
    ORDER = 316,
    INNER = 317,
    JOIN = 318,
    NUMBER = 319,
    FLOAT = 320,
    ID = 321,
    EXPRESSION = 322,
    PATH = 323,
    SSS = 324,
    STAR = 325,
    STRING_V = 326,
    DATE = 327,
    SUB_SELECTION = 328
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 132 "yacc_sql.y" /* yacc.c:355  */

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
    char *position;


#line 253 "yacc_sql.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 269 "yacc_sql.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   289

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  142
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  290

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   328

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   162,   162,   164,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   188,   193,   198,   204,   210,   216,   222,   228,   234,
     241,   246,   254,   256,   260,   267,   276,   278,   282,   295,
     301,   312,   326,   327,   328,   329,   330,   333,   342,   357,
     359,   363,   364,   364,   370,   379,   388,   398,   407,   419,
     429,   439,   458,   459,   463,   465,   469,   471,   477,   480,
     485,   492,   497,   502,   507,   514,   519,   524,   529,   534,
     540,   541,   544,   547,   550,   553,   558,   563,   568,   574,
     576,   581,   586,   588,   591,   595,   597,   601,   603,   608,
     629,   649,   669,   691,   712,   733,   752,   761,   769,   778,
     787,   795,   804,   810,   812,   817,   824,   826,   831,   838,
     840,   844,   846,   851,   856,   865,   868,   871,   876,   877,
     878,   879,   880,   881,   882,   883,   884,   885,   889,   892,
     895,   898,   904
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "UNIQUE", "SELECT", "DESC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "IN", "NOTIN", "LT",
  "GT", "LE", "GE", "NE", "COU", "MI", "MA", "AV", "NOT", "NULL_TOKEN",
  "NULLABLE", "IS", "ISNOT", "GROUP", "BY", "ASC", "ORDER", "INNER",
  "JOIN", "NUMBER", "FLOAT", "ID", "EXPRESSION", "PATH", "SSS", "STAR",
  "STRING_V", "DATE", "SUB_SELECTION", "$accept", "commands", "command",
  "exit", "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "desc_table", "create_index", "id_list", "drop_index",
  "create_table", "attr_def_list", "attr_def", "type", "ID_get", "insert",
  "value_list", "value_opt", "$@1", "value", "delete", "update", "select",
  "innerjoin_list", "innerjoin_conditions", "innerjoin_condition_list",
  "select_attr", "selectvalue", "aggrevalue", "aggrevaluelist",
  "selectvalue_commaed", "attr_list", "rel_list", "where",
  "condition_list", "condition", "groupby", "groupby_list", "orderby",
  "orderby_attr_list", "orderby_attr", "AscDesc", "comOp", "aggretype",
  "load_data", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328
};
# endif

#define YYPACT_NINF -242

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-242)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -242,    94,  -242,   132,     9,    27,   -44,    31,    38,    12,
      24,     5,    84,    87,    92,   108,   115,    80,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,    55,    62,   122,    67,
      78,  -242,  -242,  -242,  -242,   116,  -242,   112,   131,   136,
     151,   154,  -242,    93,    99,   137,  -242,  -242,  -242,  -242,
    -242,   118,   150,   134,   102,   169,   174,   -20,   114,   135,
    -242,     0,  -242,  -242,   146,   168,   139,   138,   140,   142,
     144,  -242,  -242,  -242,  -242,    -7,   179,   131,   193,   131,
     192,   192,     2,   192,   194,   196,    19,   211,   175,   184,
    -242,   198,   173,   201,   153,   155,   157,   168,    30,  -242,
      16,  -242,    61,  -242,  -242,   156,  -242,  -242,   131,    48,
    -242,  -242,  -242,   -17,  -242,  -242,   147,   147,   188,  -242,
      48,   218,   140,   207,  -242,  -242,  -242,  -242,  -242,    -1,
     160,   210,    -7,   162,   170,  -242,  -242,   212,   192,   192,
       4,   192,   192,  -242,   213,   163,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,    70,    83,    97,    19,
    -242,   168,   167,   198,   231,   171,   182,  -242,   219,   176,
    -242,   200,   180,   183,   131,  -242,  -242,   177,  -242,  -242,
    -242,    48,   222,   147,  -242,  -242,  -242,   214,  -242,  -242,
     215,  -242,  -242,   188,   243,   244,  -242,  -242,   230,  -242,
     185,   232,   234,    19,   187,   189,   195,   250,  -242,   192,
     213,   237,   110,   191,   197,  -242,  -242,  -242,  -242,   219,
     255,   256,   225,   199,  -242,     3,   242,   202,  -242,  -242,
    -242,   237,   261,   235,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,    19,  -242,   203,  -242,   204,  -242,  -242,   189,  -242,
      23,  -242,  -242,   205,   225,   200,     8,   242,   206,   208,
    -242,   249,  -242,  -242,   187,  -242,  -242,    26,   248,    48,
    -242,   209,  -242,  -242,   213,   248,   258,  -242,   237,  -242
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,   138,   139,   140,   141,    72,    71,     0,    89,     0,
       0,     0,    23,     0,     0,     0,    24,    25,    26,    22,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      68,     0,    29,    28,     0,    95,     0,     0,     0,     0,
       0,    27,    34,    73,    74,    92,    86,    89,     0,    89,
      80,    80,    80,    80,     0,     0,     0,     0,     0,     0,
      47,    36,     0,     0,     0,     0,     0,    95,     0,    91,
       0,    70,     0,    78,    79,     0,    76,    75,    89,     0,
      58,    54,    55,     0,    56,    57,     0,     0,    97,    59,
       0,     0,     0,     0,    42,    43,    44,    45,    46,    40,
       0,     0,    92,     0,   119,    87,    88,     0,    80,    80,
      80,    80,    80,    69,    49,     0,   128,   136,   137,   129,
     130,   131,   132,   133,   134,   135,     0,     0,     0,     0,
      96,    95,     0,    36,     0,     0,     0,    39,    32,     0,
      93,    64,     0,   113,    89,    84,    85,     0,    82,    81,
      77,     0,     0,     0,   101,   106,    99,   109,   112,   110,
     102,   107,   100,    97,     0,     0,    37,    35,     0,    41,
       0,     0,     0,     0,    62,     0,     0,     0,    90,    80,
      49,    51,     0,     0,     0,    98,    60,   142,    38,    32,
       0,     0,    66,     0,    94,   125,   121,     0,    61,    83,
      50,    51,     0,     0,   108,   103,   111,   104,    33,    30,
      31,     0,    65,     0,   127,     0,   126,   123,     0,   120,
     116,    52,    48,     0,    66,    64,   125,   121,     0,     0,
     114,     0,   105,    67,    62,   124,   122,   116,   116,     0,
      63,     0,   117,   115,    49,   116,     0,   118,    51,    53
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,    44,  -242,  -242,   104,   148,  -242,  -242,
    -242,  -215,  -221,  -242,  -119,  -242,  -242,  -242,     7,    13,
      15,  -242,  -242,   172,   -90,  -242,   -83,   141,   -97,    81,
    -162,  -242,  -241,  -242,    18,    28,    21,  -118,   220,  -242
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   211,    29,    30,   133,   101,   139,   102,
      31,   192,   242,   271,   127,    32,    33,    34,   234,   214,
     252,    47,    48,    94,   113,    87,    70,   107,    97,   170,
     128,   217,   270,   183,   259,   236,   257,   166,    49,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     154,   114,   116,   117,   109,   240,   111,   203,   167,   168,
     144,   171,   105,   155,   254,    39,   175,    40,    89,   254,
     261,   112,    50,   112,   156,   157,   158,   159,   160,   161,
     162,   163,   115,   255,   187,   153,   282,   283,    51,   164,
     165,    52,   268,    53,   287,   268,    83,   196,   199,   202,
      84,   232,   176,   269,   177,   106,   281,    54,   185,   186,
     188,   189,   190,   256,    90,    91,    92,   289,   256,   286,
      93,    55,   220,   120,   204,   222,    41,    42,    43,    44,
      90,    91,    92,   121,   122,   123,    93,    56,   124,   264,
      57,   125,   126,    45,     2,    58,   145,    46,     3,     4,
     146,   218,   120,   245,     5,     6,     7,     8,     9,    10,
      11,    59,   121,   122,    12,    13,    14,   124,    60,    61,
     125,    62,    15,    16,   120,   148,   149,   150,    63,   239,
      64,   151,    17,    65,   121,   122,   194,   120,    36,   124,
      37,    38,   125,   195,    66,    68,    67,   121,   122,   197,
      69,   120,   124,    71,    72,   125,   198,    73,    77,    74,
     284,   121,   122,   200,   120,    75,   124,    78,    80,   125,
     201,    79,    81,    76,   121,   122,   243,    82,    95,   124,
      85,   104,   125,   244,    41,    42,    43,    44,   156,   157,
     158,   159,   160,   161,   162,   163,   134,   135,   136,   137,
     138,    86,    96,   164,   165,    98,   100,    99,   103,   108,
     110,   112,   118,   119,   129,   131,   130,   132,   140,   141,
     143,   142,   152,   169,   172,   174,   178,   179,   181,   193,
     184,   182,   191,   205,   207,   208,   209,   213,   210,   215,
     221,   216,   212,   219,   223,   224,   226,   227,   228,   233,
     230,   229,   231,   238,   237,   235,   241,   246,   249,   250,
     251,   258,   253,   247,   262,   263,   279,   268,   260,   265,
     266,   272,   277,   248,   278,   285,   288,   206,   274,   273,
     173,   280,   147,   180,   225,   276,   267,   275,     0,    88
};

static const yytype_int16 yycheck[] =
{
     119,    91,    92,    93,    87,   220,    89,   169,   126,   127,
     107,   130,    19,    30,    11,     6,    17,     8,    18,    11,
     241,    19,    66,    19,    41,    42,    43,    44,    45,    46,
      47,    48,    30,    30,    30,   118,   277,   278,     7,    56,
      57,     3,    19,    31,   285,    19,    66,   166,   167,   168,
      70,   213,    53,    30,    55,    62,    30,    33,   148,   149,
     150,   151,   152,    60,    64,    65,    66,   288,    60,   284,
      70,    66,   191,    54,   171,   193,    49,    50,    51,    52,
      64,    65,    66,    64,    65,    66,    70,     3,    69,   251,
       3,    72,    73,    66,     0,     3,    66,    70,     4,     5,
      70,   184,    54,   222,    10,    11,    12,    13,    14,    15,
      16,     3,    64,    65,    20,    21,    22,    69,     3,    39,
      72,    66,    28,    29,    54,    64,    65,    66,    66,   219,
       8,    70,    38,    66,    64,    65,    66,    54,     6,    69,
       8,     9,    72,    73,    66,    33,    30,    64,    65,    66,
      19,    54,    69,    17,     3,    72,    73,     3,    40,    66,
     279,    64,    65,    66,    54,    66,    69,    17,    66,    72,
      73,    37,     3,    36,    64,    65,    66,     3,    32,    69,
      66,    37,    72,    73,    49,    50,    51,    52,    41,    42,
      43,    44,    45,    46,    47,    48,    23,    24,    25,    26,
      27,    66,    34,    56,    57,    66,    66,    69,    66,    30,
      17,    19,    18,    17,     3,    31,    41,    19,    17,    66,
      63,    66,    66,    35,     6,    18,    66,    17,    66,    66,
      18,    61,    19,    66,     3,    64,    54,    37,    19,    59,
      18,    58,    66,    66,    30,    30,     3,     3,    18,    62,
      18,    66,    18,     3,    59,    66,    19,    66,     3,     3,
      35,    19,    63,    66,     3,    30,    17,    19,    66,    66,
      66,    66,    66,   229,    66,    66,    18,   173,   265,   264,
     132,   274,   110,   142,   203,   267,   258,   266,    -1,    69
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    75,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    28,    29,    38,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    88,
      89,    94,    99,   100,   101,   123,     6,     8,     9,     6,
       8,    49,    50,    51,    52,    66,    70,   105,   106,   122,
      66,     7,     3,    31,    33,    66,     3,     3,     3,     3,
       3,    39,    66,    66,     8,    66,    66,    30,    33,    19,
     110,    17,     3,     3,    66,    66,    36,    40,    17,    37,
      66,     3,     3,    66,    70,    66,    66,   109,   122,    18,
      64,    65,    66,    70,   107,    32,    34,   112,    66,    69,
      66,    91,    93,    66,    37,    19,    62,   111,    30,   110,
      17,   110,    19,   108,   108,    30,   108,   108,    18,    17,
      54,    64,    65,    66,    69,    72,    73,    98,   114,     3,
      41,    31,    19,    90,    23,    24,    25,    26,    27,    92,
      17,    66,    66,    63,   112,    66,    70,   107,    64,    65,
      66,    70,    66,   110,    98,    30,    41,    42,    43,    44,
      45,    46,    47,    48,    56,    57,   121,   121,   121,    35,
     113,    98,     6,    91,    18,    17,    53,    55,    66,    17,
     111,    66,    61,   117,    18,   108,   108,    30,   108,   108,
     108,    19,    95,    66,    66,    73,    98,    66,    73,    98,
      66,    73,    98,   114,   112,    66,    90,     3,    64,    54,
      19,    87,    66,    37,   103,    59,    58,   115,   110,    66,
      98,    18,   121,    30,    30,   113,     3,     3,    18,    66,
      18,    18,   114,    62,   102,    66,   119,    59,     3,   108,
      95,    19,    96,    66,    73,    98,    66,    66,    87,     3,
       3,    35,   104,    63,    11,    30,    60,   120,    19,   118,
      66,    96,     3,    30,   114,    66,    66,   119,    19,    30,
     116,    97,    66,   104,   103,   120,   118,    66,    66,    17,
     102,    30,   116,   116,    98,    66,    95,   116,    18,    96
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    86,    87,    87,    88,    89,    90,    90,    91,    91,
      91,    91,    92,    92,    92,    92,    92,    93,    94,    95,
      95,    96,    97,    96,    98,    98,    98,    98,    98,    99,
     100,   101,   102,   102,   103,   103,   104,   104,   105,   105,
     105,   106,   106,   106,   106,   107,   107,   107,   107,   107,
     108,   108,   108,   108,   108,   108,   109,   109,   109,   110,
     110,   110,   111,   111,   111,   112,   112,   113,   113,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   115,   115,   115,   116,   116,   116,   117,
     117,   118,   118,   119,   119,   120,   120,   120,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   122,   122,
     122,   122,   123
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    10,     0,     3,     4,     8,     0,     3,     5,     3,
       2,     4,     1,     1,     1,     1,     1,     1,    10,     0,
       3,     0,     0,     8,     1,     1,     1,     1,     1,     5,
       8,     9,     0,     5,     0,     3,     0,     3,     2,     5,
       4,     1,     1,     3,     3,     2,     2,     4,     2,     2,
       0,     3,     3,     5,     3,     3,     1,     3,     3,     0,
       6,     3,     0,     3,     5,     0,     3,     0,     3,     3,
       3,     3,     3,     5,     5,     7,     3,     3,     5,     3,
       3,     5,     3,     0,     4,     6,     0,     3,     5,     0,
       4,     0,     3,     2,     4,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     8
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (scanner, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 21:
#line 188 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1564 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 193 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1572 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 198 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1580 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 204 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1588 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 210 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1596 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 216 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1604 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 222 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1613 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 228 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1621 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 234 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1630 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 242 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX; //"create_index";
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string));
	}
#line 1639 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 247 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag = SCF_CREATE_INDEX; //"create_index";
        (CONTEXT->ssql->sstr.create_index).isUnique = 1;
        create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
    }
#line 1649 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 256 "yacc_sql.y" /* yacc.c:1646  */
    {
		create_index_add_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1657 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 261 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1666 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 268 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1678 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 278 "yacc_sql.y" /* yacc.c:1646  */
    {    }
#line 1684 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 283 "yacc_sql.y" /* yacc.c:1646  */
    {
			AttrInfo attribute;
			int int_length;
			string2int(&int_length, (yyvsp[-1].string));
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), int_length, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1701 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 295 "yacc_sql.y" /* yacc.c:1646  */
    {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		CONTEXT->value_length++;
	}
#line 1712 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 302 "yacc_sql.y" /* yacc.c:1646  */
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1727 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 313 "yacc_sql.y" /* yacc.c:1646  */
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1742 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 326 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS; }
#line 1748 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 327 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS; }
#line 1754 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 328 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS; }
#line 1760 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 329 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES; }
#line 1766 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 330 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=TEXTS; }
#line 1772 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 334 "yacc_sql.y" /* yacc.c:1646  */
    {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1781 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 343 "yacc_sql.y" /* yacc.c:1646  */
    {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values, CONTEXT->value_length, CONTEXT->multi_insert_lines, CONTEXT->extraValue);

      //临时变量清零
      CONTEXT->value_length=0;
    }
#line 1800 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 359 "yacc_sql.y" /* yacc.c:1646  */
    {
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1808 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 364 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->multi_insert_lines += 1;
    }
#line 1816 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 367 "yacc_sql.y" /* yacc.c:1646  */
    {
    }
#line 1823 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 370 "yacc_sql.y" /* yacc.c:1646  */
    {
        if (CONTEXT->multi_insert_lines == 0) {

  		    value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		} else {
		    size_t line = CONTEXT->multi_insert_lines - 1;
		    value_init_integer(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
		}
		}
#line 1837 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 379 "yacc_sql.y" /* yacc.c:1646  */
    {
        if (CONTEXT->multi_insert_lines == 0) {

  		    value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		} else {
            int line = CONTEXT->multi_insert_lines - 1;
            value_init_float(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
		}
		}
#line 1851 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 388 "yacc_sql.y" /* yacc.c:1646  */
    {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
		if (CONTEXT->multi_insert_lines == 0)  {

  	    	value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		} else {
		    int line = CONTEXT->multi_insert_lines - 1;
		    value_init_string(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
		}
		}
#line 1866 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 398 "yacc_sql.y" /* yacc.c:1646  */
    {
	    (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string)) - 2);
	    if (CONTEXT->multi_insert_lines == 0) {
            value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
        } else {
            int line = CONTEXT->multi_insert_lines - 1;
            value_init_date(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
	    }
	    }
#line 1880 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 407 "yacc_sql.y" /* yacc.c:1646  */
    {
        if (CONTEXT->multi_insert_lines == 0) {

  		    value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		} else {
		    size_t line = CONTEXT->multi_insert_lines - 1;
		    value_init_null(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++]);
		}
		}
#line 1894 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 420 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1906 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 430 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1918 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 440 "yacc_sql.y" /* yacc.c:1646  */
    {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
			if( CONTEXT->ssql->flag != SCF_FAILURE){
				CONTEXT->ssql->flag=SCF_SELECT;//"select";
			}
			
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1940 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 459 "yacc_sql.y" /* yacc.c:1646  */
    {
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 1948 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 465 "yacc_sql.y" /* yacc.c:1646  */
    {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1956 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 471 "yacc_sql.y" /* yacc.c:1646  */
    {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1964 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 477 "yacc_sql.y" /* yacc.c:1646  */
    {  
			
		}
#line 1972 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 480 "yacc_sql.y" /* yacc.c:1646  */
    {
			for (int i = 0; i<CONTEXT->ssql->sstr.selection.attr_num; i++){
				CONTEXT->ssql->sstr.selection.attributes[i].aggre_type = CONTEXT->aggre_type[i];
			}
		}
#line 1982 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 485 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_FAILURE;
		}
#line 1990 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 492 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2000 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 497 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2010 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 502 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2020 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 507 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2030 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 514 "yacc_sql.y" /* yacc.c:1646  */
    {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2040 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 519 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2050 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 524 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2060 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 529 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2070 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 534 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));     
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2080 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 541 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 2088 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 544 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 2096 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 547 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 2104 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 550 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 2112 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 553 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 2120 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 558 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2130 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 563 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2140 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 568 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2150 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 576 "yacc_sql.y" /* yacc.c:1646  */
    {
			for (int i = 0; i<CONTEXT->ssql->sstr.selection.attr_num; i++){
				CONTEXT->ssql->sstr.selection.attributes[i].aggre_type = CONTEXT->aggre_type[i];
			}
	    }
#line 2160 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 581 "yacc_sql.y" /* yacc.c:1646  */
    {
			
      }
#line 2168 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 588 "yacc_sql.y" /* yacc.c:1646  */
    {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2176 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 591 "yacc_sql.y" /* yacc.c:1646  */
    {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2184 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 597 "yacc_sql.y" /* yacc.c:1646  */
    {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2192 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 603 "yacc_sql.y" /* yacc.c:1646  */
    {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2200 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 609 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, NULL, &left_attr, NULL, 0, right_value, NULL, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2225 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 630 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, left_value, NULL, NULL, 0, right_value, NULL, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2249 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 650 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, NULL, &left_attr, NULL, 1, NULL, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2273 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 670 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, left_value, NULL, NULL, 1, NULL, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 2299 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 692 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, NULL, &left_attr, NULL, 0, right_value, NULL, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2324 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 713 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, left_value, NULL, NULL, 1, NULL, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2349 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 734 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, NULL, &left_attr, NULL, 1, NULL, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2372 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 753 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, NULL, &left_attr, NULL, 2, NULL, NULL, (yyvsp[0].string));
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2385 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 762 "yacc_sql.y" /* yacc.c:1646  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, left_value, NULL, NULL, 2, NULL, NULL, (yyvsp[0].string));
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2397 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 770 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, NULL, &left_attr, NULL, 2, NULL, NULL, (yyvsp[0].string));
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2410 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 779 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 2, NULL, NULL, (yyvsp[-2].string), 1, NULL, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2423 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 788 "yacc_sql.y" /* yacc.c:1646  */
    {		
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 2, NULL, NULL, (yyvsp[-2].string), 0,right_value, NULL, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2435 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 796 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 2, NULL, NULL, (yyvsp[-4].string), 1, NULL, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2448 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 805 "yacc_sql.y" /* yacc.c:1646  */
    {
			Condition condition;
			condition_init(&condition, CONTEXT->comp, 2, NULL, NULL, (yyvsp[-2].string), 2, NULL, NULL, (yyvsp[0].string));
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2458 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 812 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr attr;
		relation_attr_init(&attr, NULL,(yyvsp[-1].string));
        CONTEXT->ssql->sstr.selection.groupby_attr[(CONTEXT->ssql->sstr.selection.groupby_num)++] = attr;
	}
#line 2468 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 817 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string),(yyvsp[-1].string));
		CONTEXT->ssql->sstr.selection.groupby_attr[(CONTEXT->ssql->sstr.selection.groupby_num)++] = attr;
	}
#line 2478 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 826 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr attr;
		relation_attr_init(&attr, NULL,(yyvsp[-1].string));
		CONTEXT->ssql->sstr.selection.groupby_attr[(CONTEXT->ssql->sstr.selection.groupby_num)++] = attr;
	}
#line 2488 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 831 "yacc_sql.y" /* yacc.c:1646  */
    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string),(yyvsp[-1].string));
		CONTEXT->ssql->sstr.selection.groupby_attr[(CONTEXT->ssql->sstr.selection.groupby_num)++] = attr;
	}
#line 2498 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 840 "yacc_sql.y" /* yacc.c:1646  */
    {	
				//
			}
#line 2506 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 846 "yacc_sql.y" /* yacc.c:1646  */
    {
				// 
			}
#line 2514 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 851 "yacc_sql.y" /* yacc.c:1646  */
    {
		Orderby orderby;
		relation_attr_init(&orderby.attr, NULL, (yyvsp[-1].string));
		orderby_init_append(&(CONTEXT->ssql->sstr.selection), CONTEXT->asc_desc, &orderby);
	}
#line 2524 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 856 "yacc_sql.y" /* yacc.c:1646  */
    {
		Orderby orderby;
		relation_attr_init(&orderby.attr, (yyvsp[-3].string), (yyvsp[-1].string));
		orderby_init_append(&(CONTEXT->ssql->sstr.selection), CONTEXT->asc_desc, &orderby);
	}
#line 2534 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 865 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->asc_desc = 0;
	}
#line 2542 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 868 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->asc_desc = 0;
	}
#line 2550 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 871 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->asc_desc = 1;
	}
#line 2558 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 876 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = EQUAL_TO; }
#line 2564 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 877 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = LESS_THAN; }
#line 2570 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 878 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = GREAT_THAN; }
#line 2576 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 879 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = LESS_EQUAL; }
#line 2582 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 880 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = GREAT_EQUAL; }
#line 2588 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 881 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp = NOT_EQUAL; }
#line 2594 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 882 "yacc_sql.y" /* yacc.c:1646  */
    {CONTEXT->comp = IS_COMPOP; }
#line 2600 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 883 "yacc_sql.y" /* yacc.c:1646  */
    {CONTEXT->comp = IS_NOT_COMPOP; }
#line 2606 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 884 "yacc_sql.y" /* yacc.c:1646  */
    {CONTEXT->comp = IN_COMPOP; }
#line 2612 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 885 "yacc_sql.y" /* yacc.c:1646  */
    {CONTEXT->comp = NOTIN_COMPOP; }
#line 2618 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 889 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = COUNT;
	}
#line 2626 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 892 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = MIN;
	}
#line 2634 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 895 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = MAX;
	}
#line 2642 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 898 "yacc_sql.y" /* yacc.c:1646  */
    {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = AVG;
	}
#line 2650 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 905 "yacc_sql.y" /* yacc.c:1646  */
    {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2659 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;


#line 2663 "yacc_sql.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
                      yytoken, &yylval, scanner);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 910 "yacc_sql.y" /* yacc.c:1906  */

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
