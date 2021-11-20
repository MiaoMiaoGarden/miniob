/* A Bison parser, made by GNU Bison 3.7.5.  */

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
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 133 "yacc_sql.tab.c"

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

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_UNIQUE = 9,                     /* UNIQUE  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_UPDATE = 16,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 20,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 21,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 22,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 23,                     /* INT_T  */
  YYSYMBOL_STRING_T = 24,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 25,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 26,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 27,                    /* TEXT_T  */
  YYSYMBOL_HELP = 28,                      /* HELP  */
  YYSYMBOL_EXIT = 29,                      /* EXIT  */
  YYSYMBOL_DOT = 30,                       /* DOT  */
  YYSYMBOL_INTO = 31,                      /* INTO  */
  YYSYMBOL_VALUES = 32,                    /* VALUES  */
  YYSYMBOL_FROM = 33,                      /* FROM  */
  YYSYMBOL_WHERE = 34,                     /* WHERE  */
  YYSYMBOL_AND = 35,                       /* AND  */
  YYSYMBOL_SET = 36,                       /* SET  */
  YYSYMBOL_ON = 37,                        /* ON  */
  YYSYMBOL_LOAD = 38,                      /* LOAD  */
  YYSYMBOL_DATA = 39,                      /* DATA  */
  YYSYMBOL_INFILE = 40,                    /* INFILE  */
  YYSYMBOL_EQ = 41,                        /* EQ  */
  YYSYMBOL_IN = 42,                        /* IN  */
  YYSYMBOL_NOTIN = 43,                     /* NOTIN  */
  YYSYMBOL_LT = 44,                        /* LT  */
  YYSYMBOL_GT = 45,                        /* GT  */
  YYSYMBOL_LE = 46,                        /* LE  */
  YYSYMBOL_GE = 47,                        /* GE  */
  YYSYMBOL_NE = 48,                        /* NE  */
  YYSYMBOL_COU = 49,                       /* COU  */
  YYSYMBOL_MI = 50,                        /* MI  */
  YYSYMBOL_MA = 51,                        /* MA  */
  YYSYMBOL_AV = 52,                        /* AV  */
  YYSYMBOL_NOT = 53,                       /* NOT  */
  YYSYMBOL_NULL_TOKEN = 54,                /* NULL_TOKEN  */
  YYSYMBOL_NULLABLE = 55,                  /* NULLABLE  */
  YYSYMBOL_IS = 56,                        /* IS  */
  YYSYMBOL_ISNOT = 57,                     /* ISNOT  */
  YYSYMBOL_GROUP = 58,                     /* GROUP  */
  YYSYMBOL_BY = 59,                        /* BY  */
  YYSYMBOL_ASC = 60,                       /* ASC  */
  YYSYMBOL_ORDER = 61,                     /* ORDER  */
  YYSYMBOL_INNER = 62,                     /* INNER  */
  YYSYMBOL_JOIN = 63,                      /* JOIN  */
  YYSYMBOL_NUMBER = 64,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 65,                     /* FLOAT  */
  YYSYMBOL_ID = 66,                        /* ID  */
  YYSYMBOL_EXPRESSION = 67,                /* EXPRESSION  */
  YYSYMBOL_PATH = 68,                      /* PATH  */
  YYSYMBOL_SSS = 69,                       /* SSS  */
  YYSYMBOL_STAR = 70,                      /* STAR  */
  YYSYMBOL_STRING_V = 71,                  /* STRING_V  */
  YYSYMBOL_DATE = 72,                      /* DATE  */
  YYSYMBOL_SUB_SELECTION = 73,             /* SUB_SELECTION  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_commands = 75,                  /* commands  */
  YYSYMBOL_command = 76,                   /* command  */
  YYSYMBOL_exit = 77,                      /* exit  */
  YYSYMBOL_help = 78,                      /* help  */
  YYSYMBOL_sync = 79,                      /* sync  */
  YYSYMBOL_begin = 80,                     /* begin  */
  YYSYMBOL_commit = 81,                    /* commit  */
  YYSYMBOL_rollback = 82,                  /* rollback  */
  YYSYMBOL_drop_table = 83,                /* drop_table  */
  YYSYMBOL_show_tables = 84,               /* show_tables  */
  YYSYMBOL_desc_table = 85,                /* desc_table  */
  YYSYMBOL_create_index = 86,              /* create_index  */
  YYSYMBOL_id_list = 87,                   /* id_list  */
  YYSYMBOL_drop_index = 88,                /* drop_index  */
  YYSYMBOL_create_table = 89,              /* create_table  */
  YYSYMBOL_attr_def_list = 90,             /* attr_def_list  */
  YYSYMBOL_attr_def = 91,                  /* attr_def  */
  YYSYMBOL_type = 92,                      /* type  */
  YYSYMBOL_ID_get = 93,                    /* ID_get  */
  YYSYMBOL_insert = 94,                    /* insert  */
  YYSYMBOL_value_list = 95,                /* value_list  */
  YYSYMBOL_value_opt = 96,                 /* value_opt  */
  YYSYMBOL_97_1 = 97,                      /* $@1  */
  YYSYMBOL_value = 98,                     /* value  */
  YYSYMBOL_delete = 99,                    /* delete  */
  YYSYMBOL_update = 100,                   /* update  */
  YYSYMBOL_select = 101,                   /* select  */
  YYSYMBOL_innerjoin_list = 102,           /* innerjoin_list  */
  YYSYMBOL_innerjoin_conditions = 103,     /* innerjoin_conditions  */
  YYSYMBOL_innerjoin_condition_list = 104, /* innerjoin_condition_list  */
  YYSYMBOL_select_attr = 105,              /* select_attr  */
  YYSYMBOL_selectvalue = 106,              /* selectvalue  */
  YYSYMBOL_aggrevalue = 107,               /* aggrevalue  */
  YYSYMBOL_aggrevaluelist = 108,           /* aggrevaluelist  */
  YYSYMBOL_selectvalue_commaed = 109,      /* selectvalue_commaed  */
  YYSYMBOL_attr_list = 110,                /* attr_list  */
  YYSYMBOL_rel_list = 111,                 /* rel_list  */
  YYSYMBOL_where = 112,                    /* where  */
  YYSYMBOL_condition_list = 113,           /* condition_list  */
  YYSYMBOL_condition = 114,                /* condition  */
  YYSYMBOL_groupby = 115,                  /* groupby  */
  YYSYMBOL_groupby_list = 116,             /* groupby_list  */
  YYSYMBOL_orderby = 117,                  /* orderby  */
  YYSYMBOL_orderby_attr_list = 118,        /* orderby_attr_list  */
  YYSYMBOL_orderby_attr = 119,             /* orderby_attr  */
  YYSYMBOL_AscDesc = 120,                  /* AscDesc  */
  YYSYMBOL_comOp = 121,                    /* comOp  */
  YYSYMBOL_aggretype = 122,                /* aggretype  */
  YYSYMBOL_load_data = 123                 /* load_data  */
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
typedef yytype_int16 yy_state_t;

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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


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
static const yytype_int16 yyrline[] =
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
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "UNIQUE", "SELECT", "DESC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ",
  "IN", "NOTIN", "LT", "GT", "LE", "GE", "NE", "COU", "MI", "MA", "AV",
  "NOT", "NULL_TOKEN", "NULLABLE", "IS", "ISNOT", "GROUP", "BY", "ASC",
  "ORDER", "INNER", "JOIN", "NUMBER", "FLOAT", "ID", "EXPRESSION", "PATH",
  "SSS", "STAR", "STRING_V", "DATE", "SUB_SELECTION", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "id_list", "drop_index", "create_table", "attr_def_list", "attr_def",
  "type", "ID_get", "insert", "value_list", "value_opt", "$@1", "value",
  "delete", "update", "select", "innerjoin_list", "innerjoin_conditions",
  "innerjoin_condition_list", "select_attr", "selectvalue", "aggrevalue",
  "aggrevaluelist", "selectvalue_commaed", "attr_list", "rel_list",
  "where", "condition_list", "condition", "groupby", "groupby_list",
  "orderby", "orderby_attr_list", "orderby_attr", "AscDesc", "comOp",
  "aggretype", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
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
#endif

#define YYPACT_NINF (-242)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
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
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   211,    29,    30,   133,   101,   139,   102,
      31,   192,   242,   271,   127,    32,    33,    34,   234,   214,
     252,    47,    48,    94,   113,    87,    70,   107,    97,   170,
     128,   217,   270,   183,   259,   236,   257,   166,    49,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
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
static const yytype_int8 yystos[] =
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
static const yytype_int8 yyr1[] =
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
static const yytype_int8 yyr2[] =
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


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
        yyerror (scanner, YY_("syntax error: cannot back up")); \
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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
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
                 int yyrule, void *scanner)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
      yychar = yylex (&yylval, scanner);
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
  case 21: /* exit: EXIT SEMICOLON  */
#line 188 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1468 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 193 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1476 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 198 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1484 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 204 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1492 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 210 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1500 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 216 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1508 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 222 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1517 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 228 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1525 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 234 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1534 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 242 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX; //"create_index";
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string));
	}
#line 1543 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 247 "yacc_sql.y"
    {
        CONTEXT->ssql->flag = SCF_CREATE_INDEX; //"create_index";
        (CONTEXT->ssql->sstr.create_index).isUnique = 1;
        create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
    }
#line 1553 "yacc_sql.tab.c"
    break;

  case 33: /* id_list: COMMA ID id_list  */
#line 256 "yacc_sql.y"
                          {
		create_index_add_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1561 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 261 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1570 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 268 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1582 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 278 "yacc_sql.y"
                                   {    }
#line 1588 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type LBRACE NUMBER RBRACE  */
#line 283 "yacc_sql.y"
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
#line 1605 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type NULLABLE  */
#line 295 "yacc_sql.y"
                             {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		CONTEXT->value_length++;
	}
#line 1616 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type  */
#line 302 "yacc_sql.y"
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
#line 1631 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type NOT NULL_TOKEN  */
#line 313 "yacc_sql.y"
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
#line 1646 "yacc_sql.tab.c"
    break;

  case 42: /* type: INT_T  */
#line 326 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1652 "yacc_sql.tab.c"
    break;

  case 43: /* type: STRING_T  */
#line 327 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1658 "yacc_sql.tab.c"
    break;

  case 44: /* type: FLOAT_T  */
#line 328 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1664 "yacc_sql.tab.c"
    break;

  case 45: /* type: DATE_T  */
#line 329 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1670 "yacc_sql.tab.c"
    break;

  case 46: /* type: TEXT_T  */
#line 330 "yacc_sql.y"
                { (yyval.number)=TEXTS; }
#line 1676 "yacc_sql.tab.c"
    break;

  case 47: /* ID_get: ID  */
#line 334 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1685 "yacc_sql.tab.c"
    break;

  case 48: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE value_opt SEMICOLON  */
#line 343 "yacc_sql.y"
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
#line 1704 "yacc_sql.tab.c"
    break;

  case 50: /* value_list: COMMA value value_list  */
#line 359 "yacc_sql.y"
                             {
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1712 "yacc_sql.tab.c"
    break;

  case 52: /* $@1: %empty  */
#line 364 "yacc_sql.y"
                       {
        CONTEXT->multi_insert_lines += 1;
    }
#line 1720 "yacc_sql.tab.c"
    break;

  case 53: /* value_opt: COMMA value_opt $@1 LBRACE value value_list RBRACE value_opt  */
#line 367 "yacc_sql.y"
                                             {
    }
#line 1727 "yacc_sql.tab.c"
    break;

  case 54: /* value: NUMBER  */
#line 370 "yacc_sql.y"
          {
        if (CONTEXT->multi_insert_lines == 0) {

  		    value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		} else {
		    size_t line = CONTEXT->multi_insert_lines - 1;
		    value_init_integer(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
		}
		}
#line 1741 "yacc_sql.tab.c"
    break;

  case 55: /* value: FLOAT  */
#line 379 "yacc_sql.y"
          {
        if (CONTEXT->multi_insert_lines == 0) {

  		    value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		} else {
            int line = CONTEXT->multi_insert_lines - 1;
            value_init_float(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
		}
		}
#line 1755 "yacc_sql.tab.c"
    break;

  case 56: /* value: SSS  */
#line 388 "yacc_sql.y"
         {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
		if (CONTEXT->multi_insert_lines == 0)  {

  	    	value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		} else {
		    int line = CONTEXT->multi_insert_lines - 1;
		    value_init_string(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
		}
		}
#line 1770 "yacc_sql.tab.c"
    break;

  case 57: /* value: DATE  */
#line 398 "yacc_sql.y"
              {
	    (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string)) - 2);
	    if (CONTEXT->multi_insert_lines == 0) {
            value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
        } else {
            int line = CONTEXT->multi_insert_lines - 1;
            value_init_date(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
	    }
	    }
#line 1784 "yacc_sql.tab.c"
    break;

  case 58: /* value: NULL_TOKEN  */
#line 407 "yacc_sql.y"
                   {
        if (CONTEXT->multi_insert_lines == 0) {

  		    value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		} else {
		    size_t line = CONTEXT->multi_insert_lines - 1;
		    value_init_null(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++]);
		}
		}
#line 1798 "yacc_sql.tab.c"
    break;

  case 59: /* delete: DELETE FROM ID where SEMICOLON  */
#line 420 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1810 "yacc_sql.tab.c"
    break;

  case 60: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 430 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1822 "yacc_sql.tab.c"
    break;

  case 61: /* select: SELECT select_attr FROM ID rel_list where orderby groupby SEMICOLON  */
#line 440 "yacc_sql.y"
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
#line 1844 "yacc_sql.tab.c"
    break;

  case 63: /* innerjoin_list: INNER JOIN ID innerjoin_conditions innerjoin_list  */
#line 459 "yacc_sql.y"
                                                           {
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 1852 "yacc_sql.tab.c"
    break;

  case 65: /* innerjoin_conditions: ON condition innerjoin_condition_list  */
#line 465 "yacc_sql.y"
                                            {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1860 "yacc_sql.tab.c"
    break;

  case 67: /* innerjoin_condition_list: AND condition innerjoin_condition_list  */
#line 471 "yacc_sql.y"
                                             {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1868 "yacc_sql.tab.c"
    break;

  case 68: /* select_attr: selectvalue attr_list  */
#line 477 "yacc_sql.y"
                         {  
			
		}
#line 1876 "yacc_sql.tab.c"
    break;

  case 69: /* select_attr: aggretype LBRACE aggrevalue RBRACE attr_list  */
#line 480 "yacc_sql.y"
                                                      {
			for (int i = 0; i<CONTEXT->ssql->sstr.selection.attr_num; i++){
				CONTEXT->ssql->sstr.selection.attributes[i].aggre_type = CONTEXT->aggre_type[i];
			}
		}
#line 1886 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: aggretype LBRACE RBRACE attr_list  */
#line 485 "yacc_sql.y"
                                            {
			CONTEXT->ssql->flag = SCF_FAILURE;
		}
#line 1894 "yacc_sql.tab.c"
    break;

  case 71: /* selectvalue: STAR  */
#line 492 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1904 "yacc_sql.tab.c"
    break;

  case 72: /* selectvalue: ID  */
#line 497 "yacc_sql.y"
              {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1914 "yacc_sql.tab.c"
    break;

  case 73: /* selectvalue: ID DOT ID  */
#line 502 "yacc_sql.y"
                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1924 "yacc_sql.tab.c"
    break;

  case 74: /* selectvalue: ID DOT STAR  */
#line 507 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 1934 "yacc_sql.tab.c"
    break;

  case 75: /* aggrevalue: STAR aggrevaluelist  */
#line 514 "yacc_sql.y"
                            {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1944 "yacc_sql.tab.c"
    break;

  case 76: /* aggrevalue: ID aggrevaluelist  */
#line 519 "yacc_sql.y"
                        {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1954 "yacc_sql.tab.c"
    break;

  case 77: /* aggrevalue: ID DOT ID aggrevaluelist  */
#line 524 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1964 "yacc_sql.tab.c"
    break;

  case 78: /* aggrevalue: NUMBER aggrevaluelist  */
#line 529 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1974 "yacc_sql.tab.c"
    break;

  case 79: /* aggrevalue: FLOAT aggrevaluelist  */
#line 534 "yacc_sql.y"
                           {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));     
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1984 "yacc_sql.tab.c"
    break;

  case 81: /* aggrevaluelist: COMMA STAR aggrevaluelist  */
#line 541 "yacc_sql.y"
                                    {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 1992 "yacc_sql.tab.c"
    break;

  case 82: /* aggrevaluelist: COMMA ID aggrevaluelist  */
#line 544 "yacc_sql.y"
                                   {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 2000 "yacc_sql.tab.c"
    break;

  case 83: /* aggrevaluelist: COMMA ID DOT ID aggrevaluelist  */
#line 547 "yacc_sql.y"
                                         {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 2008 "yacc_sql.tab.c"
    break;

  case 84: /* aggrevaluelist: COMMA NUMBER aggrevaluelist  */
#line 550 "yacc_sql.y"
                                      {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 2016 "yacc_sql.tab.c"
    break;

  case 85: /* aggrevaluelist: COMMA FLOAT aggrevaluelist  */
#line 553 "yacc_sql.y"
                                     {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 2024 "yacc_sql.tab.c"
    break;

  case 86: /* selectvalue_commaed: ID  */
#line 558 "yacc_sql.y"
            {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2034 "yacc_sql.tab.c"
    break;

  case 87: /* selectvalue_commaed: ID DOT ID  */
#line 563 "yacc_sql.y"
                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2044 "yacc_sql.tab.c"
    break;

  case 88: /* selectvalue_commaed: ID DOT STAR  */
#line 568 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2054 "yacc_sql.tab.c"
    break;

  case 90: /* attr_list: COMMA aggretype LBRACE aggrevalue RBRACE attr_list  */
#line 576 "yacc_sql.y"
                                                             {
			for (int i = 0; i<CONTEXT->ssql->sstr.selection.attr_num; i++){
				CONTEXT->ssql->sstr.selection.attributes[i].aggre_type = CONTEXT->aggre_type[i];
			}
	    }
#line 2064 "yacc_sql.tab.c"
    break;

  case 91: /* attr_list: COMMA selectvalue_commaed attr_list  */
#line 581 "yacc_sql.y"
                                          {
			
      }
#line 2072 "yacc_sql.tab.c"
    break;

  case 93: /* rel_list: COMMA ID rel_list  */
#line 588 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2080 "yacc_sql.tab.c"
    break;

  case 94: /* rel_list: INNER JOIN ID innerjoin_conditions innerjoin_list  */
#line 591 "yacc_sql.y"
                                                            {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2088 "yacc_sql.tab.c"
    break;

  case 96: /* where: WHERE condition condition_list  */
#line 597 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2096 "yacc_sql.tab.c"
    break;

  case 98: /* condition_list: AND condition condition_list  */
#line 603 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2104 "yacc_sql.tab.c"
    break;

  case 99: /* condition: ID comOp value  */
#line 609 "yacc_sql.y"
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
#line 2129 "yacc_sql.tab.c"
    break;

  case 100: /* condition: value comOp value  */
#line 630 "yacc_sql.y"
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
#line 2153 "yacc_sql.tab.c"
    break;

  case 101: /* condition: ID comOp ID  */
#line 650 "yacc_sql.y"
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
#line 2177 "yacc_sql.tab.c"
    break;

  case 102: /* condition: value comOp ID  */
#line 670 "yacc_sql.y"
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
#line 2203 "yacc_sql.tab.c"
    break;

  case 103: /* condition: ID DOT ID comOp value  */
#line 692 "yacc_sql.y"
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
#line 2228 "yacc_sql.tab.c"
    break;

  case 104: /* condition: value comOp ID DOT ID  */
#line 713 "yacc_sql.y"
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
#line 2253 "yacc_sql.tab.c"
    break;

  case 105: /* condition: ID DOT ID comOp ID DOT ID  */
#line 734 "yacc_sql.y"
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
#line 2276 "yacc_sql.tab.c"
    break;

  case 106: /* condition: ID comOp SUB_SELECTION  */
#line 753 "yacc_sql.y"
        {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, NULL, &left_attr, NULL, 2, NULL, NULL, (yyvsp[0].string));
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2289 "yacc_sql.tab.c"
    break;

  case 107: /* condition: value comOp SUB_SELECTION  */
#line 762 "yacc_sql.y"
        {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, left_value, NULL, NULL, 2, NULL, NULL, (yyvsp[0].string));
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2301 "yacc_sql.tab.c"
    break;

  case 108: /* condition: ID DOT ID comOp SUB_SELECTION  */
#line 770 "yacc_sql.y"
        {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, NULL, &left_attr, NULL, 2, NULL, NULL, (yyvsp[0].string));
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2314 "yacc_sql.tab.c"
    break;

  case 109: /* condition: SUB_SELECTION comOp ID  */
#line 779 "yacc_sql.y"
        {
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 2, NULL, NULL, (yyvsp[-2].string), 1, NULL, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2327 "yacc_sql.tab.c"
    break;

  case 110: /* condition: SUB_SELECTION comOp value  */
#line 788 "yacc_sql.y"
        {		
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 2, NULL, NULL, (yyvsp[-2].string), 0,right_value, NULL, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2339 "yacc_sql.tab.c"
    break;

  case 111: /* condition: SUB_SELECTION comOp ID DOT ID  */
#line 796 "yacc_sql.y"
        {
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 2, NULL, NULL, (yyvsp[-4].string), 1, NULL, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2352 "yacc_sql.tab.c"
    break;

  case 112: /* condition: SUB_SELECTION comOp SUB_SELECTION  */
#line 805 "yacc_sql.y"
        {
			Condition condition;
			condition_init(&condition, CONTEXT->comp, 2, NULL, NULL, (yyvsp[-2].string), 2, NULL, NULL, (yyvsp[0].string));
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2362 "yacc_sql.tab.c"
    break;

  case 114: /* groupby: GROUP BY ID groupby_list  */
#line 812 "yacc_sql.y"
                                  {
		RelAttr attr;
		relation_attr_init(&attr, NULL,(yyvsp[-1].string));
        CONTEXT->ssql->sstr.selection.groupby_attr[(CONTEXT->ssql->sstr.selection.groupby_num)++] = attr;
	}
#line 2372 "yacc_sql.tab.c"
    break;

  case 115: /* groupby: GROUP BY ID DOT ID groupby_list  */
#line 817 "yacc_sql.y"
                                         {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string),(yyvsp[-1].string));
		CONTEXT->ssql->sstr.selection.groupby_attr[(CONTEXT->ssql->sstr.selection.groupby_num)++] = attr;
	}
#line 2382 "yacc_sql.tab.c"
    break;

  case 117: /* groupby_list: COMMA ID groupby_list  */
#line 826 "yacc_sql.y"
                              {
		RelAttr attr;
		relation_attr_init(&attr, NULL,(yyvsp[-1].string));
		CONTEXT->ssql->sstr.selection.groupby_attr[(CONTEXT->ssql->sstr.selection.groupby_num)++] = attr;
	}
#line 2392 "yacc_sql.tab.c"
    break;

  case 118: /* groupby_list: COMMA ID DOT ID groupby_list  */
#line 831 "yacc_sql.y"
                                     {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string),(yyvsp[-1].string));
		CONTEXT->ssql->sstr.selection.groupby_attr[(CONTEXT->ssql->sstr.selection.groupby_num)++] = attr;
	}
#line 2402 "yacc_sql.tab.c"
    break;

  case 120: /* orderby: ORDER BY orderby_attr orderby_attr_list  */
#line 840 "yacc_sql.y"
                                              {	
				//
			}
#line 2410 "yacc_sql.tab.c"
    break;

  case 122: /* orderby_attr_list: COMMA orderby_attr orderby_attr_list  */
#line 846 "yacc_sql.y"
                                           {
				// 
			}
#line 2418 "yacc_sql.tab.c"
    break;

  case 123: /* orderby_attr: ID AscDesc  */
#line 851 "yacc_sql.y"
                   {
		Orderby orderby;
		relation_attr_init(&orderby.attr, NULL, (yyvsp[-1].string));
		orderby_init_append(&(CONTEXT->ssql->sstr.selection), CONTEXT->asc_desc, &orderby);
	}
#line 2428 "yacc_sql.tab.c"
    break;

  case 124: /* orderby_attr: ID DOT ID AscDesc  */
#line 856 "yacc_sql.y"
                            {
		Orderby orderby;
		relation_attr_init(&orderby.attr, (yyvsp[-3].string), (yyvsp[-1].string));
		orderby_init_append(&(CONTEXT->ssql->sstr.selection), CONTEXT->asc_desc, &orderby);
	}
#line 2438 "yacc_sql.tab.c"
    break;

  case 125: /* AscDesc: %empty  */
#line 865 "yacc_sql.y"
        {
		CONTEXT->asc_desc = 0;
	}
#line 2446 "yacc_sql.tab.c"
    break;

  case 126: /* AscDesc: ASC  */
#line 868 "yacc_sql.y"
              {
		CONTEXT->asc_desc = 0;
	}
#line 2454 "yacc_sql.tab.c"
    break;

  case 127: /* AscDesc: DESC  */
#line 871 "yacc_sql.y"
               {
		CONTEXT->asc_desc = 1;
	}
#line 2462 "yacc_sql.tab.c"
    break;

  case 128: /* comOp: EQ  */
#line 876 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2468 "yacc_sql.tab.c"
    break;

  case 129: /* comOp: LT  */
#line 877 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2474 "yacc_sql.tab.c"
    break;

  case 130: /* comOp: GT  */
#line 878 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2480 "yacc_sql.tab.c"
    break;

  case 131: /* comOp: LE  */
#line 879 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2486 "yacc_sql.tab.c"
    break;

  case 132: /* comOp: GE  */
#line 880 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2492 "yacc_sql.tab.c"
    break;

  case 133: /* comOp: NE  */
#line 881 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2498 "yacc_sql.tab.c"
    break;

  case 134: /* comOp: IS  */
#line 882 "yacc_sql.y"
             {CONTEXT->comp = IS_COMPOP; }
#line 2504 "yacc_sql.tab.c"
    break;

  case 135: /* comOp: ISNOT  */
#line 883 "yacc_sql.y"
                {CONTEXT->comp = IS_NOT_COMPOP; }
#line 2510 "yacc_sql.tab.c"
    break;

  case 136: /* comOp: IN  */
#line 884 "yacc_sql.y"
             {CONTEXT->comp = IN_COMPOP; }
#line 2516 "yacc_sql.tab.c"
    break;

  case 137: /* comOp: NOTIN  */
#line 885 "yacc_sql.y"
                {CONTEXT->comp = NOTIN_COMPOP; }
#line 2522 "yacc_sql.tab.c"
    break;

  case 138: /* aggretype: COU  */
#line 889 "yacc_sql.y"
            {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = COUNT;
	}
#line 2530 "yacc_sql.tab.c"
    break;

  case 139: /* aggretype: MI  */
#line 892 "yacc_sql.y"
             {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = MIN;
	}
#line 2538 "yacc_sql.tab.c"
    break;

  case 140: /* aggretype: MA  */
#line 895 "yacc_sql.y"
             {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = MAX;
	}
#line 2546 "yacc_sql.tab.c"
    break;

  case 141: /* aggretype: AV  */
#line 898 "yacc_sql.y"
             {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = AVG;
	}
#line 2554 "yacc_sql.tab.c"
    break;

  case 142: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 905 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2563 "yacc_sql.tab.c"
    break;


#line 2567 "yacc_sql.tab.c"

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
      yyerror (scanner, YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 910 "yacc_sql.y"

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
