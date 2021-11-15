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
  YYSYMBOL_HELP = 27,                      /* HELP  */
  YYSYMBOL_EXIT = 28,                      /* EXIT  */
  YYSYMBOL_DOT = 29,                       /* DOT  */
  YYSYMBOL_INTO = 30,                      /* INTO  */
  YYSYMBOL_VALUES = 31,                    /* VALUES  */
  YYSYMBOL_FROM = 32,                      /* FROM  */
  YYSYMBOL_WHERE = 33,                     /* WHERE  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_SET = 35,                       /* SET  */
  YYSYMBOL_ON = 36,                        /* ON  */
  YYSYMBOL_LOAD = 37,                      /* LOAD  */
  YYSYMBOL_DATA = 38,                      /* DATA  */
  YYSYMBOL_INFILE = 39,                    /* INFILE  */
  YYSYMBOL_EQ = 40,                        /* EQ  */
  YYSYMBOL_IN = 41,                        /* IN  */
  YYSYMBOL_NOTIN = 42,                     /* NOTIN  */
  YYSYMBOL_LT = 43,                        /* LT  */
  YYSYMBOL_GT = 44,                        /* GT  */
  YYSYMBOL_LE = 45,                        /* LE  */
  YYSYMBOL_GE = 46,                        /* GE  */
  YYSYMBOL_NE = 47,                        /* NE  */
  YYSYMBOL_COU = 48,                       /* COU  */
  YYSYMBOL_MI = 49,                        /* MI  */
  YYSYMBOL_MA = 50,                        /* MA  */
  YYSYMBOL_AV = 51,                        /* AV  */
  YYSYMBOL_NOT = 52,                       /* NOT  */
  YYSYMBOL_NULL_TOKEN = 53,                /* NULL_TOKEN  */
  YYSYMBOL_NULLABLE = 54,                  /* NULLABLE  */
  YYSYMBOL_IS = 55,                        /* IS  */
  YYSYMBOL_ISNOT = 56,                     /* ISNOT  */
  YYSYMBOL_GROUP = 57,                     /* GROUP  */
  YYSYMBOL_BY = 58,                        /* BY  */
  YYSYMBOL_ASC = 59,                       /* ASC  */
  YYSYMBOL_ORDER = 60,                     /* ORDER  */
  YYSYMBOL_INNER = 61,                     /* INNER  */
  YYSYMBOL_JOIN = 62,                      /* JOIN  */
  YYSYMBOL_NUMBER = 63,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 64,                     /* FLOAT  */
  YYSYMBOL_ID = 65,                        /* ID  */
  YYSYMBOL_PATH = 66,                      /* PATH  */
  YYSYMBOL_SSS = 67,                       /* SSS  */
  YYSYMBOL_STAR = 68,                      /* STAR  */
  YYSYMBOL_STRING_V = 69,                  /* STRING_V  */
  YYSYMBOL_DATE = 70,                      /* DATE  */
  YYSYMBOL_SUB_SELECTION = 71,             /* SUB_SELECTION  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_commands = 73,                  /* commands  */
  YYSYMBOL_command = 74,                   /* command  */
  YYSYMBOL_exit = 75,                      /* exit  */
  YYSYMBOL_help = 76,                      /* help  */
  YYSYMBOL_sync = 77,                      /* sync  */
  YYSYMBOL_begin = 78,                     /* begin  */
  YYSYMBOL_commit = 79,                    /* commit  */
  YYSYMBOL_rollback = 80,                  /* rollback  */
  YYSYMBOL_drop_table = 81,                /* drop_table  */
  YYSYMBOL_show_tables = 82,               /* show_tables  */
  YYSYMBOL_desc_table = 83,                /* desc_table  */
  YYSYMBOL_create_index = 84,              /* create_index  */
  YYSYMBOL_drop_index = 85,                /* drop_index  */
  YYSYMBOL_create_table = 86,              /* create_table  */
  YYSYMBOL_attr_def_list = 87,             /* attr_def_list  */
  YYSYMBOL_attr_def = 88,                  /* attr_def  */
  YYSYMBOL_type = 89,                      /* type  */
  YYSYMBOL_ID_get = 90,                    /* ID_get  */
  YYSYMBOL_insert = 91,                    /* insert  */
  YYSYMBOL_value_list = 92,                /* value_list  */
  YYSYMBOL_value_opt = 93,                 /* value_opt  */
  YYSYMBOL_94_1 = 94,                      /* $@1  */
  YYSYMBOL_value = 95,                     /* value  */
  YYSYMBOL_delete = 96,                    /* delete  */
  YYSYMBOL_update = 97,                    /* update  */
  YYSYMBOL_select = 98,                    /* select  */
  YYSYMBOL_innerjoin_list = 99,            /* innerjoin_list  */
  YYSYMBOL_innerjoin_conditions = 100,     /* innerjoin_conditions  */
  YYSYMBOL_innerjoin_condition_list = 101, /* innerjoin_condition_list  */
  YYSYMBOL_select_attr = 102,              /* select_attr  */
  YYSYMBOL_selectvalue = 103,              /* selectvalue  */
  YYSYMBOL_aggrevalue = 104,               /* aggrevalue  */
  YYSYMBOL_aggrevaluelist = 105,           /* aggrevaluelist  */
  YYSYMBOL_selectvalue_commaed = 106,      /* selectvalue_commaed  */
  YYSYMBOL_attr_list = 107,                /* attr_list  */
  YYSYMBOL_rel_list = 108,                 /* rel_list  */
  YYSYMBOL_where = 109,                    /* where  */
  YYSYMBOL_condition_list = 110,           /* condition_list  */
  YYSYMBOL_condition = 111,                /* condition  */
  YYSYMBOL_groupby = 112,                  /* groupby  */
  YYSYMBOL_groupby_list = 113,             /* groupby_list  */
  YYSYMBOL_orderby = 114,                  /* orderby  */
  YYSYMBOL_orderby_attr_list = 115,        /* orderby_attr_list  */
  YYSYMBOL_orderby_attr = 116,             /* orderby_attr  */
  YYSYMBOL_AscDesc = 117,                  /* AscDesc  */
  YYSYMBOL_comOp = 118,                    /* comOp  */
  YYSYMBOL_aggretype = 119,                /* aggretype  */
  YYSYMBOL_load_data = 120                 /* load_data  */
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
#define YYLAST   287

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  138
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  284

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   326


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
      65,    66,    67,    68,    69,    70,    71
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   160,   160,   162,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   186,   191,   196,   202,   208,   214,   220,   226,   232,
     239,   245,   253,   260,   269,   271,   275,   288,   294,   305,
     319,   320,   321,   322,   325,   334,   349,   351,   355,   356,
     356,   362,   371,   380,   390,   399,   411,   421,   431,   450,
     451,   455,   457,   461,   463,   469,   472,   477,   484,   489,
     494,   499,   506,   511,   516,   521,   526,   532,   533,   536,
     539,   542,   545,   550,   555,   560,   566,   568,   573,   578,
     580,   583,   587,   589,   593,   595,   600,   621,   641,   661,
     683,   704,   725,   744,   753,   761,   770,   779,   787,   796,
     798,   803,   810,   812,   817,   824,   826,   830,   832,   837,
     842,   851,   854,   857,   862,   863,   864,   865,   866,   867,
     868,   869,   870,   871,   875,   878,   881,   884,   890
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
  "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "IN",
  "NOTIN", "LT", "GT", "LE", "GE", "NE", "COU", "MI", "MA", "AV", "NOT",
  "NULL_TOKEN", "NULLABLE", "IS", "ISNOT", "GROUP", "BY", "ASC", "ORDER",
  "INNER", "JOIN", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR",
  "STRING_V", "DATE", "SUB_SELECTION", "$accept", "commands", "command",
  "exit", "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "desc_table", "create_index", "drop_index",
  "create_table", "attr_def_list", "attr_def", "type", "ID_get", "insert",
  "value_list", "value_opt", "$@1", "value", "delete", "update", "select",
  "innerjoin_list", "innerjoin_conditions", "innerjoin_condition_list",
  "select_attr", "selectvalue", "aggrevalue", "aggrevaluelist",
  "selectvalue_commaed", "attr_list", "rel_list", "where",
  "condition_list", "condition", "groupby", "groupby_list", "orderby",
  "orderby_attr_list", "orderby_attr", "AscDesc", "comOp", "aggretype",
  "load_data", YY_NULLPTR
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
     325,   326
};
#endif

#define YYPACT_NINF (-231)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -231,    76,  -231,   116,    37,   -28,   -48,    11,    21,     8,
      33,     5,    69,    75,    79,    80,    81,    55,  -231,  -231,
    -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,
    -231,  -231,  -231,  -231,  -231,  -231,    30,    53,   115,    67,
      68,  -231,  -231,  -231,  -231,   107,  -231,   105,   119,   126,
     142,   143,  -231,    90,   100,   133,  -231,  -231,  -231,  -231,
    -231,   131,   157,   144,   117,   176,   180,     9,   132,   110,
    -231,   -12,  -231,  -231,   167,   166,   137,   136,   139,   140,
     171,  -231,  -231,  -231,  -231,    -6,   177,   119,   191,   119,
     190,   190,     6,   190,   192,   194,   -37,   209,   173,   184,
    -231,   196,   170,   199,   152,   153,   158,   166,    34,  -231,
      51,  -231,   108,  -231,  -231,   154,  -231,  -231,   119,   114,
    -231,  -231,  -231,    65,  -231,  -231,   145,   145,   187,  -231,
     114,   216,   139,   205,  -231,  -231,  -231,  -231,    14,   159,
     208,    -6,   161,   168,  -231,  -231,   211,   190,   190,    10,
     190,   190,  -231,   212,   162,  -231,  -231,  -231,  -231,  -231,
    -231,  -231,  -231,  -231,  -231,    64,    99,    77,   -37,  -231,
     166,   165,   196,   229,   172,   181,  -231,   215,   174,  -231,
     200,   179,   183,   119,  -231,  -231,   178,  -231,  -231,  -231,
     114,   220,   145,  -231,  -231,  -231,   213,  -231,   217,  -231,
    -231,   187,   238,   241,  -231,  -231,   227,  -231,   244,   230,
     -37,   188,   185,   193,   249,  -231,   190,   212,   234,    86,
     189,   195,  -231,  -231,  -231,  -231,  -231,   252,   222,   197,
    -231,     3,   239,   198,  -231,  -231,  -231,   234,   254,   232,
    -231,  -231,  -231,  -231,  -231,   -37,  -231,   201,  -231,   202,
    -231,  -231,   185,  -231,    25,  -231,  -231,   203,   222,   200,
       4,   239,   204,   206,  -231,   245,  -231,  -231,   188,  -231,
    -231,    50,   246,   114,  -231,   207,  -231,  -231,   212,   246,
     255,  -231,   234,  -231
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
       0,   134,   135,   136,   137,    69,    68,     0,    86,     0,
       0,     0,    23,     0,     0,     0,    24,    25,    26,    22,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,     0,    29,    28,     0,    92,     0,     0,     0,     0,
       0,    27,    32,    70,    71,    89,    83,    86,     0,    86,
      77,    77,    77,    77,     0,     0,     0,     0,     0,     0,
      44,    34,     0,     0,     0,     0,     0,    92,     0,    88,
       0,    67,     0,    75,    76,     0,    73,    72,    86,     0,
      55,    51,    52,     0,    53,    54,     0,     0,    94,    56,
       0,     0,     0,     0,    40,    41,    42,    43,    38,     0,
       0,    89,     0,   115,    84,    85,     0,    77,    77,    77,
      77,    77,    66,    46,     0,   124,   132,   133,   125,   126,
     127,   128,   129,   130,   131,     0,     0,     0,     0,    93,
      92,     0,    34,     0,     0,     0,    37,     0,     0,    90,
      61,     0,   109,    86,    81,    82,     0,    79,    78,    74,
       0,     0,     0,    98,   103,    96,   106,   107,    99,   104,
      97,    94,     0,     0,    35,    33,     0,    39,     0,     0,
       0,    59,     0,     0,     0,    87,    77,    46,    48,     0,
       0,     0,    95,    57,   138,    36,    30,     0,    63,     0,
      91,   121,   117,     0,    58,    80,    47,    48,     0,     0,
     105,   100,   108,   101,    31,     0,    62,     0,   123,     0,
     122,   119,     0,   116,   112,    49,    45,     0,    63,    61,
     121,   117,     0,     0,   110,     0,   102,    64,    59,   120,
     118,   112,   112,     0,    60,     0,   113,   111,    46,   112,
       0,   114,    48,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,
    -231,  -231,  -231,  -231,  -231,    92,   138,  -231,  -231,  -231,
    -205,  -218,  -231,  -119,  -231,  -231,  -231,     7,    15,    18,
    -231,  -231,   169,   -90,  -231,   -82,   141,  -103,    82,  -160,
    -231,  -230,  -231,    16,    26,    20,  -117,   218,  -231
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   133,   101,   138,   102,    31,
     191,   238,   265,   127,    32,    33,    34,   230,   211,   246,
      47,    48,    94,   113,    87,    70,   107,    97,   169,   128,
     214,   264,   182,   253,   232,   251,   165,    49,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     153,   114,   116,   117,   143,   109,    89,   111,   201,   166,
     167,   170,   236,   105,   248,   248,   120,    50,    51,   255,
      41,    42,    43,    44,    52,   112,   121,   122,   123,   112,
     124,   174,   249,   125,   126,   115,   152,    45,    53,   186,
      46,   276,   277,    39,   262,    40,   195,   197,   200,   281,
     228,    90,    91,    92,   263,   106,    93,   184,   185,   187,
     188,   189,   250,   250,   283,    54,   175,   202,   176,   262,
      55,   217,    56,   280,    83,   219,     2,    84,    57,   275,
       3,     4,    58,    59,    60,   258,     5,     6,     7,     8,
       9,    10,    11,    61,   154,    62,    12,    13,    14,   144,
     241,   215,   145,    15,    16,   155,   156,   157,   158,   159,
     160,   161,   162,    17,    90,    91,    92,   120,    63,    93,
     163,   164,    36,    64,    37,    38,   235,   121,   122,   193,
     120,   124,    65,    66,   125,   194,    67,    68,    69,   120,
     121,   122,   198,    71,   124,    72,    73,   125,   199,   121,
     122,   239,   120,   124,   278,    74,   125,   240,    41,    42,
      43,    44,   121,   122,   196,    75,   124,   120,    76,   125,
      77,   147,   148,   149,    78,    86,   150,   121,   122,    81,
      79,   124,    80,    82,   125,   155,   156,   157,   158,   159,
     160,   161,   162,   134,   135,   136,   137,    85,    95,    96,
     163,   164,    98,    99,   100,   103,   108,   104,   110,   112,
     118,   119,   129,   130,   131,   132,   139,   140,   141,   151,
     142,   168,   171,   173,   177,   178,   180,   192,   181,   183,
     203,   190,   205,   208,   207,   206,   210,   212,   218,   209,
     213,   223,   220,   216,   224,   225,   221,   226,   227,   229,
     231,   233,   234,   237,   242,   244,   245,   256,   252,   247,
     243,   257,   273,   254,   204,   262,   259,   260,   266,   271,
     172,   272,   279,   282,   268,   274,   267,   270,   261,   146,
     269,     0,   179,   222,     0,     0,     0,    88
};

static const yytype_int16 yycheck[] =
{
     119,    91,    92,    93,   107,    87,    18,    89,   168,   126,
     127,   130,   217,    19,    11,    11,    53,    65,     7,   237,
      48,    49,    50,    51,     3,    19,    63,    64,    65,    19,
      67,    17,    29,    70,    71,    29,   118,    65,    30,    29,
      68,   271,   272,     6,    19,     8,   165,   166,   167,   279,
     210,    63,    64,    65,    29,    61,    68,   147,   148,   149,
     150,   151,    59,    59,   282,    32,    52,   170,    54,    19,
      65,   190,     3,   278,    65,   192,     0,    68,     3,    29,
       4,     5,     3,     3,     3,   245,    10,    11,    12,    13,
      14,    15,    16,    38,    29,    65,    20,    21,    22,    65,
     219,   183,    68,    27,    28,    40,    41,    42,    43,    44,
      45,    46,    47,    37,    63,    64,    65,    53,    65,    68,
      55,    56,     6,     8,     8,     9,   216,    63,    64,    65,
      53,    67,    65,    65,    70,    71,    29,    32,    19,    53,
      63,    64,    65,    17,    67,     3,     3,    70,    71,    63,
      64,    65,    53,    67,   273,    65,    70,    71,    48,    49,
      50,    51,    63,    64,    65,    65,    67,    53,    35,    70,
      39,    63,    64,    65,    17,    65,    68,    63,    64,     3,
      36,    67,    65,     3,    70,    40,    41,    42,    43,    44,
      45,    46,    47,    23,    24,    25,    26,    65,    31,    33,
      55,    56,    65,    67,    65,    65,    29,    36,    17,    19,
      18,    17,     3,    40,    30,    19,    17,    65,    65,    65,
      62,    34,     6,    18,    65,    17,    65,    65,    60,    18,
      65,    19,     3,    18,    53,    63,    36,    58,    18,    65,
      57,     3,    29,    65,     3,    18,    29,     3,    18,    61,
      65,    58,     3,    19,    65,     3,    34,     3,    19,    62,
      65,    29,    17,    65,   172,    19,    65,    65,    65,    65,
     132,    65,    65,    18,   259,   268,   258,   261,   252,   110,
     260,    -1,   141,   201,    -1,    -1,    -1,    69
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    73,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    27,    28,    37,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    91,    96,    97,    98,   120,     6,     8,     9,     6,
       8,    48,    49,    50,    51,    65,    68,   102,   103,   119,
      65,     7,     3,    30,    32,    65,     3,     3,     3,     3,
       3,    38,    65,    65,     8,    65,    65,    29,    32,    19,
     107,    17,     3,     3,    65,    65,    35,    39,    17,    36,
      65,     3,     3,    65,    68,    65,    65,   106,   119,    18,
      63,    64,    65,    68,   104,    31,    33,   109,    65,    67,
      65,    88,    90,    65,    36,    19,    61,   108,    29,   107,
      17,   107,    19,   105,   105,    29,   105,   105,    18,    17,
      53,    63,    64,    65,    67,    70,    71,    95,   111,     3,
      40,    30,    19,    87,    23,    24,    25,    26,    89,    17,
      65,    65,    62,   109,    65,    68,   104,    63,    64,    65,
      68,    65,   107,    95,    29,    40,    41,    42,    43,    44,
      45,    46,    47,    55,    56,   118,   118,   118,    34,   110,
      95,     6,    88,    18,    17,    52,    54,    65,    17,   108,
      65,    60,   114,    18,   105,   105,    29,   105,   105,   105,
      19,    92,    65,    65,    71,    95,    65,    95,    65,    71,
      95,   111,   109,    65,    87,     3,    63,    53,    18,    65,
      36,   100,    58,    57,   112,   107,    65,    95,    18,   118,
      29,    29,   110,     3,     3,    18,     3,    18,   111,    61,
      99,    65,   116,    58,     3,   105,    92,    19,    93,    65,
      71,    95,    65,    65,     3,    34,   101,    62,    11,    29,
      59,   117,    19,   115,    65,    93,     3,    29,   111,    65,
      65,   116,    19,    29,   113,    94,    65,   101,   100,   117,
     115,    65,    65,    17,    99,    29,   113,   113,    95,    65,
      92,   113,    18,    93
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    73,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    84,    85,    86,    87,    87,    88,    88,    88,    88,
      89,    89,    89,    89,    90,    91,    92,    92,    93,    94,
      93,    95,    95,    95,    95,    95,    96,    97,    98,    99,
      99,   100,   100,   101,   101,   102,   102,   102,   103,   103,
     103,   103,   104,   104,   104,   104,   104,   105,   105,   105,
     105,   105,   105,   106,   106,   106,   107,   107,   107,   108,
     108,   108,   109,   109,   110,   110,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   112,
     112,   112,   113,   113,   113,   114,   114,   115,   115,   116,
     116,   117,   117,   117,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   119,   119,   119,   119,   120
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,    10,     4,     8,     0,     3,     5,     3,     2,     4,
       1,     1,     1,     1,     1,    10,     0,     3,     0,     0,
       8,     1,     1,     1,     1,     1,     5,     8,     9,     0,
       5,     0,     3,     0,     3,     2,     5,     4,     1,     1,
       3,     3,     2,     2,     4,     2,     2,     0,     3,     3,
       5,     3,     3,     1,     3,     3,     0,     6,     3,     0,
       3,     5,     0,     3,     0,     3,     3,     3,     3,     3,
       5,     5,     7,     3,     3,     5,     3,     3,     5,     0,
       4,     6,     0,     3,     5,     0,     4,     0,     3,     2,
       4,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     8
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
#line 186 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1462 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 191 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1470 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 196 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1478 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 202 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1486 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 208 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1494 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 214 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1502 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 220 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1511 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 226 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1519 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 232 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1528 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 240 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1537 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 246 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
            (CONTEXT->ssql->sstr.create_index).isUnique = 1;
            create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));

        }
#line 1548 "yacc_sql.tab.c"
    break;

  case 32: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 254 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1557 "yacc_sql.tab.c"
    break;

  case 33: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 261 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1569 "yacc_sql.tab.c"
    break;

  case 35: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 271 "yacc_sql.y"
                                   {    }
#line 1575 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def: ID_get type LBRACE NUMBER RBRACE  */
#line 276 "yacc_sql.y"
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
#line 1592 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def: ID_get type NULLABLE  */
#line 288 "yacc_sql.y"
                             {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		CONTEXT->value_length++;
	}
#line 1603 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type  */
#line 295 "yacc_sql.y"
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
#line 1618 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type NOT NULL_TOKEN  */
#line 306 "yacc_sql.y"
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
#line 1633 "yacc_sql.tab.c"
    break;

  case 40: /* type: INT_T  */
#line 319 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1639 "yacc_sql.tab.c"
    break;

  case 41: /* type: STRING_T  */
#line 320 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1645 "yacc_sql.tab.c"
    break;

  case 42: /* type: FLOAT_T  */
#line 321 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1651 "yacc_sql.tab.c"
    break;

  case 43: /* type: DATE_T  */
#line 322 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1657 "yacc_sql.tab.c"
    break;

  case 44: /* ID_get: ID  */
#line 326 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1666 "yacc_sql.tab.c"
    break;

  case 45: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE value_opt SEMICOLON  */
#line 335 "yacc_sql.y"
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
#line 1685 "yacc_sql.tab.c"
    break;

  case 47: /* value_list: COMMA value value_list  */
#line 351 "yacc_sql.y"
                             {
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1693 "yacc_sql.tab.c"
    break;

  case 49: /* $@1: %empty  */
#line 356 "yacc_sql.y"
                       {
        CONTEXT->multi_insert_lines += 1;
    }
#line 1701 "yacc_sql.tab.c"
    break;

  case 50: /* value_opt: COMMA value_opt $@1 LBRACE value value_list RBRACE value_opt  */
#line 359 "yacc_sql.y"
                                             {
    }
#line 1708 "yacc_sql.tab.c"
    break;

  case 51: /* value: NUMBER  */
#line 362 "yacc_sql.y"
          {
        if (CONTEXT->multi_insert_lines == 0) {

  		    value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		} else {
		    size_t line = CONTEXT->multi_insert_lines - 1;
		    value_init_integer(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
		}
		}
#line 1722 "yacc_sql.tab.c"
    break;

  case 52: /* value: FLOAT  */
#line 371 "yacc_sql.y"
          {
        if (CONTEXT->multi_insert_lines == 0) {

  		    value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		} else {
            int line = CONTEXT->multi_insert_lines - 1;
            value_init_float(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
		}
		}
#line 1736 "yacc_sql.tab.c"
    break;

  case 53: /* value: SSS  */
#line 380 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
		if (CONTEXT->multi_insert_lines == 0)  {

  	    	value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		} else {
		    int line = CONTEXT->multi_insert_lines - 1;
		    value_init_string(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
		}
		}
#line 1751 "yacc_sql.tab.c"
    break;

  case 54: /* value: DATE  */
#line 390 "yacc_sql.y"
              {
	    (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string)) - 2);
	    if (CONTEXT->multi_insert_lines == 0) {
            value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
        } else {
            int line = CONTEXT->multi_insert_lines - 1;
            value_init_date(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
	    }
	    }
#line 1765 "yacc_sql.tab.c"
    break;

  case 55: /* value: NULL_TOKEN  */
#line 399 "yacc_sql.y"
                   {
        if (CONTEXT->multi_insert_lines == 0) {

  		    value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		} else {
		    size_t line = CONTEXT->multi_insert_lines - 1;
		    value_init_null(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++]);
		}
		}
#line 1779 "yacc_sql.tab.c"
    break;

  case 56: /* delete: DELETE FROM ID where SEMICOLON  */
#line 412 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1791 "yacc_sql.tab.c"
    break;

  case 57: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 422 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1803 "yacc_sql.tab.c"
    break;

  case 58: /* select: SELECT select_attr FROM ID rel_list where orderby groupby SEMICOLON  */
#line 432 "yacc_sql.y"
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
#line 1825 "yacc_sql.tab.c"
    break;

  case 60: /* innerjoin_list: INNER JOIN ID innerjoin_conditions innerjoin_list  */
#line 451 "yacc_sql.y"
                                                           {
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 1833 "yacc_sql.tab.c"
    break;

  case 62: /* innerjoin_conditions: ON condition innerjoin_condition_list  */
#line 457 "yacc_sql.y"
                                            {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1841 "yacc_sql.tab.c"
    break;

  case 64: /* innerjoin_condition_list: AND condition innerjoin_condition_list  */
#line 463 "yacc_sql.y"
                                             {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1849 "yacc_sql.tab.c"
    break;

  case 65: /* select_attr: selectvalue attr_list  */
#line 469 "yacc_sql.y"
                         {  
			
		}
#line 1857 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: aggretype LBRACE aggrevalue RBRACE attr_list  */
#line 472 "yacc_sql.y"
                                                      {
			for (int i = 0; i<CONTEXT->ssql->sstr.selection.attr_num; i++){
				CONTEXT->ssql->sstr.selection.attributes[i].aggre_type = CONTEXT->aggre_type[i];
			}
		}
#line 1867 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: aggretype LBRACE RBRACE attr_list  */
#line 477 "yacc_sql.y"
                                            {
			CONTEXT->ssql->flag = SCF_FAILURE;
		}
#line 1875 "yacc_sql.tab.c"
    break;

  case 68: /* selectvalue: STAR  */
#line 484 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1885 "yacc_sql.tab.c"
    break;

  case 69: /* selectvalue: ID  */
#line 489 "yacc_sql.y"
              {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1895 "yacc_sql.tab.c"
    break;

  case 70: /* selectvalue: ID DOT ID  */
#line 494 "yacc_sql.y"
                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1905 "yacc_sql.tab.c"
    break;

  case 71: /* selectvalue: ID DOT STAR  */
#line 499 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 1915 "yacc_sql.tab.c"
    break;

  case 72: /* aggrevalue: STAR aggrevaluelist  */
#line 506 "yacc_sql.y"
                            {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1925 "yacc_sql.tab.c"
    break;

  case 73: /* aggrevalue: ID aggrevaluelist  */
#line 511 "yacc_sql.y"
                        {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1935 "yacc_sql.tab.c"
    break;

  case 74: /* aggrevalue: ID DOT ID aggrevaluelist  */
#line 516 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1945 "yacc_sql.tab.c"
    break;

  case 75: /* aggrevalue: NUMBER aggrevaluelist  */
#line 521 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1955 "yacc_sql.tab.c"
    break;

  case 76: /* aggrevalue: FLOAT aggrevaluelist  */
#line 526 "yacc_sql.y"
                           {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));     
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1965 "yacc_sql.tab.c"
    break;

  case 78: /* aggrevaluelist: COMMA STAR aggrevaluelist  */
#line 533 "yacc_sql.y"
                                    {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 1973 "yacc_sql.tab.c"
    break;

  case 79: /* aggrevaluelist: COMMA ID aggrevaluelist  */
#line 536 "yacc_sql.y"
                                   {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 1981 "yacc_sql.tab.c"
    break;

  case 80: /* aggrevaluelist: COMMA ID DOT ID aggrevaluelist  */
#line 539 "yacc_sql.y"
                                         {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 1989 "yacc_sql.tab.c"
    break;

  case 81: /* aggrevaluelist: COMMA NUMBER aggrevaluelist  */
#line 542 "yacc_sql.y"
                                      {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 1997 "yacc_sql.tab.c"
    break;

  case 82: /* aggrevaluelist: COMMA FLOAT aggrevaluelist  */
#line 545 "yacc_sql.y"
                                     {
			CONTEXT->ssql->flag = SCF_FAILURE;
	    }
#line 2005 "yacc_sql.tab.c"
    break;

  case 83: /* selectvalue_commaed: ID  */
#line 550 "yacc_sql.y"
            {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2015 "yacc_sql.tab.c"
    break;

  case 84: /* selectvalue_commaed: ID DOT ID  */
#line 555 "yacc_sql.y"
                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2025 "yacc_sql.tab.c"
    break;

  case 85: /* selectvalue_commaed: ID DOT STAR  */
#line 560 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2035 "yacc_sql.tab.c"
    break;

  case 87: /* attr_list: COMMA aggretype LBRACE aggrevalue RBRACE attr_list  */
#line 568 "yacc_sql.y"
                                                             {
			for (int i = 0; i<CONTEXT->ssql->sstr.selection.attr_num; i++){
				CONTEXT->ssql->sstr.selection.attributes[i].aggre_type = CONTEXT->aggre_type[i];
			}
	    }
#line 2045 "yacc_sql.tab.c"
    break;

  case 88: /* attr_list: COMMA selectvalue_commaed attr_list  */
#line 573 "yacc_sql.y"
                                          {
			
      }
#line 2053 "yacc_sql.tab.c"
    break;

  case 90: /* rel_list: COMMA ID rel_list  */
#line 580 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2061 "yacc_sql.tab.c"
    break;

  case 91: /* rel_list: INNER JOIN ID innerjoin_conditions innerjoin_list  */
#line 583 "yacc_sql.y"
                                                            {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2069 "yacc_sql.tab.c"
    break;

  case 93: /* where: WHERE condition condition_list  */
#line 589 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2077 "yacc_sql.tab.c"
    break;

  case 95: /* condition_list: AND condition condition_list  */
#line 595 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2085 "yacc_sql.tab.c"
    break;

  case 96: /* condition: ID comOp value  */
#line 601 "yacc_sql.y"
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
#line 2110 "yacc_sql.tab.c"
    break;

  case 97: /* condition: value comOp value  */
#line 622 "yacc_sql.y"
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
#line 2134 "yacc_sql.tab.c"
    break;

  case 98: /* condition: ID comOp ID  */
#line 642 "yacc_sql.y"
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
#line 2158 "yacc_sql.tab.c"
    break;

  case 99: /* condition: value comOp ID  */
#line 662 "yacc_sql.y"
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
#line 2184 "yacc_sql.tab.c"
    break;

  case 100: /* condition: ID DOT ID comOp value  */
#line 684 "yacc_sql.y"
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
#line 2209 "yacc_sql.tab.c"
    break;

  case 101: /* condition: value comOp ID DOT ID  */
#line 705 "yacc_sql.y"
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
#line 2234 "yacc_sql.tab.c"
    break;

  case 102: /* condition: ID DOT ID comOp ID DOT ID  */
#line 726 "yacc_sql.y"
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
#line 2257 "yacc_sql.tab.c"
    break;

  case 103: /* condition: ID comOp SUB_SELECTION  */
#line 745 "yacc_sql.y"
        {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, NULL, &left_attr, NULL, 2, NULL, NULL, (yyvsp[0].string));
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2270 "yacc_sql.tab.c"
    break;

  case 104: /* condition: value comOp SUB_SELECTION  */
#line 754 "yacc_sql.y"
        {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, left_value, NULL, NULL, 2, NULL, NULL, (yyvsp[0].string));
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2282 "yacc_sql.tab.c"
    break;

  case 105: /* condition: ID DOT ID comOp SUB_SELECTION  */
#line 762 "yacc_sql.y"
        {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, NULL, &left_attr, NULL, 2, NULL, NULL, (yyvsp[0].string));
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2295 "yacc_sql.tab.c"
    break;

  case 106: /* condition: SUB_SELECTION comOp ID  */
#line 771 "yacc_sql.y"
        {
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 2, NULL, NULL, (yyvsp[-2].string), 1, NULL, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2308 "yacc_sql.tab.c"
    break;

  case 107: /* condition: SUB_SELECTION comOp value  */
#line 780 "yacc_sql.y"
        {		
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 2, NULL, NULL, (yyvsp[-2].string), 0,right_value, NULL, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2320 "yacc_sql.tab.c"
    break;

  case 108: /* condition: SUB_SELECTION comOp ID DOT ID  */
#line 788 "yacc_sql.y"
        {
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 2, NULL, NULL, (yyvsp[-4].string), 1, NULL, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2333 "yacc_sql.tab.c"
    break;

  case 110: /* groupby: GROUP BY ID groupby_list  */
#line 798 "yacc_sql.y"
                                  {
		RelAttr attr;
		relation_attr_init(&attr, NULL,(yyvsp[-1].string));
        CONTEXT->ssql->sstr.selection.groupby_attr[(CONTEXT->ssql->sstr.selection.groupby_num)++] = attr;
	}
#line 2343 "yacc_sql.tab.c"
    break;

  case 111: /* groupby: GROUP BY ID DOT ID groupby_list  */
#line 803 "yacc_sql.y"
                                         {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string),(yyvsp[-1].string));
		CONTEXT->ssql->sstr.selection.groupby_attr[(CONTEXT->ssql->sstr.selection.groupby_num)++] = attr;
	}
#line 2353 "yacc_sql.tab.c"
    break;

  case 113: /* groupby_list: COMMA ID groupby_list  */
#line 812 "yacc_sql.y"
                              {
		RelAttr attr;
		relation_attr_init(&attr, NULL,(yyvsp[-1].string));
		CONTEXT->ssql->sstr.selection.groupby_attr[(CONTEXT->ssql->sstr.selection.groupby_num)++] = attr;
	}
#line 2363 "yacc_sql.tab.c"
    break;

  case 114: /* groupby_list: COMMA ID DOT ID groupby_list  */
#line 817 "yacc_sql.y"
                                     {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string),(yyvsp[-1].string));
		CONTEXT->ssql->sstr.selection.groupby_attr[(CONTEXT->ssql->sstr.selection.groupby_num)++] = attr;
	}
#line 2373 "yacc_sql.tab.c"
    break;

  case 116: /* orderby: ORDER BY orderby_attr orderby_attr_list  */
#line 826 "yacc_sql.y"
                                              {	
				//
			}
#line 2381 "yacc_sql.tab.c"
    break;

  case 118: /* orderby_attr_list: COMMA orderby_attr orderby_attr_list  */
#line 832 "yacc_sql.y"
                                           {
				// 
			}
#line 2389 "yacc_sql.tab.c"
    break;

  case 119: /* orderby_attr: ID AscDesc  */
#line 837 "yacc_sql.y"
                   {
		Orderby orderby;
		relation_attr_init(&orderby.attr, NULL, (yyvsp[-1].string));
		orderby_init_append(&(CONTEXT->ssql->sstr.selection), CONTEXT->asc_desc, &orderby);
	}
#line 2399 "yacc_sql.tab.c"
    break;

  case 120: /* orderby_attr: ID DOT ID AscDesc  */
#line 842 "yacc_sql.y"
                            {
		Orderby orderby;
		relation_attr_init(&orderby.attr, (yyvsp[-3].string), (yyvsp[-1].string));
		orderby_init_append(&(CONTEXT->ssql->sstr.selection), CONTEXT->asc_desc, &orderby);
	}
#line 2409 "yacc_sql.tab.c"
    break;

  case 121: /* AscDesc: %empty  */
#line 851 "yacc_sql.y"
        {
		CONTEXT->asc_desc = 0;
	}
#line 2417 "yacc_sql.tab.c"
    break;

  case 122: /* AscDesc: ASC  */
#line 854 "yacc_sql.y"
              {
		CONTEXT->asc_desc = 0;
	}
#line 2425 "yacc_sql.tab.c"
    break;

  case 123: /* AscDesc: DESC  */
#line 857 "yacc_sql.y"
               {
		CONTEXT->asc_desc = 1;
	}
#line 2433 "yacc_sql.tab.c"
    break;

  case 124: /* comOp: EQ  */
#line 862 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2439 "yacc_sql.tab.c"
    break;

  case 125: /* comOp: LT  */
#line 863 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2445 "yacc_sql.tab.c"
    break;

  case 126: /* comOp: GT  */
#line 864 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2451 "yacc_sql.tab.c"
    break;

  case 127: /* comOp: LE  */
#line 865 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2457 "yacc_sql.tab.c"
    break;

  case 128: /* comOp: GE  */
#line 866 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2463 "yacc_sql.tab.c"
    break;

  case 129: /* comOp: NE  */
#line 867 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2469 "yacc_sql.tab.c"
    break;

  case 130: /* comOp: IS  */
#line 868 "yacc_sql.y"
             {CONTEXT->comp = IS_COMPOP; }
#line 2475 "yacc_sql.tab.c"
    break;

  case 131: /* comOp: ISNOT  */
#line 869 "yacc_sql.y"
                {CONTEXT->comp = IS_NOT_COMPOP; }
#line 2481 "yacc_sql.tab.c"
    break;

  case 132: /* comOp: IN  */
#line 870 "yacc_sql.y"
             {CONTEXT->comp = IN_COMPOP; }
#line 2487 "yacc_sql.tab.c"
    break;

  case 133: /* comOp: NOTIN  */
#line 871 "yacc_sql.y"
                {CONTEXT->comp = NOTIN_COMPOP; }
#line 2493 "yacc_sql.tab.c"
    break;

  case 134: /* aggretype: COU  */
#line 875 "yacc_sql.y"
            {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = COUNT;
	}
#line 2501 "yacc_sql.tab.c"
    break;

  case 135: /* aggretype: MI  */
#line 878 "yacc_sql.y"
             {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = MIN;
	}
#line 2509 "yacc_sql.tab.c"
    break;

  case 136: /* aggretype: MA  */
#line 881 "yacc_sql.y"
             {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = MAX;
	}
#line 2517 "yacc_sql.tab.c"
    break;

  case 137: /* aggretype: AV  */
#line 884 "yacc_sql.y"
             {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = AVG;
	}
#line 2525 "yacc_sql.tab.c"
    break;

  case 138: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 891 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2534 "yacc_sql.tab.c"
    break;


#line 2538 "yacc_sql.tab.c"

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

#line 896 "yacc_sql.y"

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
