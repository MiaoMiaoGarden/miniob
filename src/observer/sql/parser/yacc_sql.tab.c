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
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_GT = 42,                        /* GT  */
  YYSYMBOL_LE = 43,                        /* LE  */
  YYSYMBOL_GE = 44,                        /* GE  */
  YYSYMBOL_NE = 45,                        /* NE  */
  YYSYMBOL_COU = 46,                       /* COU  */
  YYSYMBOL_MI = 47,                        /* MI  */
  YYSYMBOL_MA = 48,                        /* MA  */
  YYSYMBOL_AV = 49,                        /* AV  */
  YYSYMBOL_NOT = 50,                       /* NOT  */
  YYSYMBOL_NULL_TOKEN = 51,                /* NULL_TOKEN  */
  YYSYMBOL_NULLABLE = 52,                  /* NULLABLE  */
  YYSYMBOL_IS = 53,                        /* IS  */
  YYSYMBOL_ISNOT = 54,                     /* ISNOT  */
  YYSYMBOL_GROUP = 55,                     /* GROUP  */
  YYSYMBOL_BY = 56,                        /* BY  */
  YYSYMBOL_ASC = 57,                       /* ASC  */
  YYSYMBOL_ORDER = 58,                     /* ORDER  */
  YYSYMBOL_ANYTHING = 59,                  /* ANYTHING  */
  YYSYMBOL_NUMBER = 60,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 61,                     /* FLOAT  */
  YYSYMBOL_ID = 62,                        /* ID  */
  YYSYMBOL_PATH = 63,                      /* PATH  */
  YYSYMBOL_SSS = 64,                       /* SSS  */
  YYSYMBOL_STAR = 65,                      /* STAR  */
  YYSYMBOL_STRING_V = 66,                  /* STRING_V  */
  YYSYMBOL_DATE = 67,                      /* DATE  */
  YYSYMBOL_YYACCEPT = 68,                  /* $accept  */
  YYSYMBOL_commands = 69,                  /* commands  */
  YYSYMBOL_command = 70,                   /* command  */
  YYSYMBOL_exit = 71,                      /* exit  */
  YYSYMBOL_help = 72,                      /* help  */
  YYSYMBOL_sync = 73,                      /* sync  */
  YYSYMBOL_begin = 74,                     /* begin  */
  YYSYMBOL_commit = 75,                    /* commit  */
  YYSYMBOL_rollback = 76,                  /* rollback  */
  YYSYMBOL_drop_table = 77,                /* drop_table  */
  YYSYMBOL_show_tables = 78,               /* show_tables  */
  YYSYMBOL_desc_table = 79,                /* desc_table  */
  YYSYMBOL_create_index = 80,              /* create_index  */
  YYSYMBOL_drop_index = 81,                /* drop_index  */
  YYSYMBOL_create_table = 82,              /* create_table  */
  YYSYMBOL_attr_def_list = 83,             /* attr_def_list  */
  YYSYMBOL_attr_def = 84,                  /* attr_def  */
  YYSYMBOL_number = 85,                    /* number  */
  YYSYMBOL_type = 86,                      /* type  */
  YYSYMBOL_ID_get = 87,                    /* ID_get  */
  YYSYMBOL_insert = 88,                    /* insert  */
  YYSYMBOL_value_list = 89,                /* value_list  */
  YYSYMBOL_value_opt = 90,                 /* value_opt  */
  YYSYMBOL_91_1 = 91,                      /* $@1  */
  YYSYMBOL_value = 92,                     /* value  */
  YYSYMBOL_delete = 93,                    /* delete  */
  YYSYMBOL_update = 94,                    /* update  */
  YYSYMBOL_select = 95,                    /* select  */
  YYSYMBOL_aggrevalue = 96,                /* aggrevalue  */
  YYSYMBOL_aggrevaluelist = 97,            /* aggrevaluelist  */
  YYSYMBOL_select_attr = 98,               /* select_attr  */
  YYSYMBOL_attr_list = 99,                 /* attr_list  */
  YYSYMBOL_rel_list = 100,                 /* rel_list  */
  YYSYMBOL_where = 101,                    /* where  */
  YYSYMBOL_condition_list = 102,           /* condition_list  */
  YYSYMBOL_condition = 103,                /* condition  */
  YYSYMBOL_groupby = 104,                  /* groupby  */
  YYSYMBOL_orderby = 105,                  /* orderby  */
  YYSYMBOL_orderby_attr_list = 106,        /* orderby_attr_list  */
  YYSYMBOL_orderby_attr = 107,             /* orderby_attr  */
  YYSYMBOL_AscDesc = 108,                  /* AscDesc  */
  YYSYMBOL_comOp = 109,                    /* comOp  */
  YYSYMBOL_aggretype = 110,                /* aggretype  */
  YYSYMBOL_load_data = 111                 /* load_data  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYLAST   242

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  249

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   322


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
      65,    66,    67
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   156,   156,   158,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   182,   187,   192,   198,   204,   210,   216,   222,   228,
     235,   241,   249,   256,   265,   267,   271,   282,   288,   299,
     313,   316,   317,   318,   319,   322,   331,   346,   348,   352,
     353,   353,   359,   368,   377,   387,   396,   408,   418,   428,
     449,   454,   459,   464,   469,   474,   475,   478,   481,   484,
     487,   493,   498,   503,   508,   513,   519,   521,   526,   533,
     540,   547,   549,   553,   555,   559,   561,   566,   587,   607,
     627,   649,   670,   691,   711,   713,   718,   725,   727,   731,
     733,   738,   744,   754,   757,   760,   765,   766,   767,   768,
     769,   770,   771,   772,   776,   779,   782,   785,   791
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
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT",
  "LE", "GE", "NE", "COU", "MI", "MA", "AV", "NOT", "NULL_TOKEN",
  "NULLABLE", "IS", "ISNOT", "GROUP", "BY", "ASC", "ORDER", "ANYTHING",
  "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V", "DATE",
  "$accept", "commands", "command", "exit", "help", "sync", "begin",
  "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "insert", "value_list",
  "value_opt", "$@1", "value", "delete", "update", "select", "aggrevalue",
  "aggrevaluelist", "select_attr", "attr_list", "rel_list", "where",
  "condition_list", "condition", "groupby", "orderby", "orderby_attr_list",
  "orderby_attr", "AscDesc", "comOp", "aggretype", "load_data", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322
};
#endif

#define YYPACT_NINF (-208)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -208,    65,  -208,   106,    76,    51,   -36,    23,    38,    24,
      32,     6,    80,    85,    86,    87,    98,    57,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,    44,    46,   103,    61,
      62,  -208,  -208,  -208,  -208,    -2,  -208,    94,   112,   124,
     132,  -208,    74,    83,   109,  -208,  -208,  -208,  -208,  -208,
     108,   131,   114,    89,   149,   150,    92,   -47,  -208,   102,
     101,  -208,  -208,   134,   140,   105,   113,   116,   117,   138,
    -208,  -208,     0,   159,   161,   161,   162,   163,   163,    18,
     163,   165,   167,   -39,   182,   146,   157,  -208,   169,    48,
     172,   128,   -12,  -208,   101,  -208,  -208,   129,   140,   110,
    -208,  -208,   130,  -208,  -208,   161,    82,  -208,  -208,  -208,
      -9,  -208,  -208,   115,   160,  -208,    82,   187,   116,   177,
    -208,  -208,  -208,  -208,    -4,   135,   179,   161,   161,   180,
     162,   141,   163,   163,    20,   163,   163,  -208,   181,   139,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,    43,    58,
     -39,  -208,   140,   142,   169,   199,   143,   154,  -208,   188,
     145,  -208,  -208,   161,  -208,   152,   155,  -208,  -208,   147,
    -208,  -208,  -208,    82,   193,   115,  -208,  -208,   183,  -208,
     160,   210,   211,  -208,  -208,  -208,   197,  -208,   213,   200,
    -208,   158,   166,   214,   163,   181,   202,    70,   164,  -208,
    -208,  -208,  -208,  -208,   216,    -5,   158,   168,  -208,  -208,
    -208,   202,   220,   195,  -208,  -208,  -208,  -208,   170,  -208,
    -208,  -208,   158,   196,  -208,  -208,   171,     5,  -208,   173,
     212,  -208,  -208,  -208,    82,   181,   209,   202,  -208
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,   114,   115,   116,   117,    76,    71,     0,     0,     0,
       0,    23,     0,     0,     0,    24,    25,    26,    22,    21,
       0,     0,     0,     0,     0,     0,     0,     0,    73,     0,
       0,    29,    28,     0,    83,     0,     0,     0,     0,     0,
      27,    32,    76,     0,    76,    76,    81,    65,    65,    65,
      65,     0,     0,     0,     0,     0,     0,    45,    34,     0,
       0,     0,     0,    78,     0,    74,    75,     0,    83,     0,
      63,    64,     0,    61,    60,    76,     0,    56,    52,    53,
       0,    54,    55,     0,    85,    57,     0,     0,     0,     0,
      41,    42,    43,    44,    38,     0,     0,    76,    76,     0,
      81,    97,    65,    65,    65,    65,    65,    72,    47,     0,
     106,   107,   108,   109,   110,   111,   112,   113,     0,     0,
       0,    84,    83,     0,    34,     0,     0,     0,    37,     0,
       0,    79,    80,    76,    82,     0,    94,    69,    70,     0,
      67,    66,    62,     0,     0,     0,    89,    87,    90,    88,
      85,     0,     0,    35,    33,    40,     0,    39,     0,     0,
      77,     0,     0,     0,    65,    47,    49,     0,     0,    86,
      58,   118,    36,    30,     0,   103,    99,     0,    59,    68,
      48,    49,     0,     0,    91,    92,    31,   105,     0,   104,
     101,    98,    99,    95,    50,    46,     0,   103,   100,     0,
       0,    93,   102,    96,     0,    47,     0,    49,    51
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,    64,   111,  -208,  -208,  -208,
    -208,  -194,  -207,  -208,  -116,  -208,  -208,  -208,   127,   -87,
    -208,   -77,    96,   -99,    47,    78,  -208,  -208,     2,    39,
       4,  -119,   176,  -208
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   129,    98,   196,   134,    99,
      31,   184,   222,   240,   123,    32,    33,    34,    91,   110,
      47,    68,   108,    94,   161,   124,   203,   176,   231,   232,
     230,   158,    48,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     148,   111,   113,   114,   159,   103,   227,   105,   106,   141,
     162,   220,   117,   166,   234,    84,   227,    66,    85,    66,
     149,   118,   119,   120,   228,   121,    49,    67,   122,   102,
      50,   150,   151,   152,   153,   154,   155,   109,   147,   109,
     248,    51,   187,   189,   156,   157,   167,   112,   168,   179,
     137,   246,   229,   138,    52,   177,   178,   180,   181,   182,
     171,   172,   229,   191,    53,     2,   207,   205,    54,     3,
       4,   130,   131,   132,   133,     5,     6,     7,     8,     9,
      10,    11,    39,    55,    40,    12,    13,    14,    56,    57,
      58,   224,    15,    16,   117,    60,   200,    41,    42,    43,
      44,    59,    17,   118,   119,   186,    61,   121,    62,   117,
     122,    63,    36,    45,    37,    38,    46,   219,   118,   119,
     188,   117,   121,    64,    65,   122,    69,    71,   245,    70,
     118,   119,   223,   117,   121,    72,    73,   122,    41,    42,
      43,    44,   118,   119,    75,    74,   121,    76,    77,   122,
      78,    79,    80,    81,    82,   150,   151,   152,   153,   154,
     155,    87,    88,    89,    86,    92,    90,    95,   156,   157,
     142,   143,   144,    93,   101,   145,   104,    96,    97,   100,
      66,   107,   109,   115,   116,   125,   126,   127,   128,   135,
     136,   140,   146,   163,   160,   165,   170,   169,   173,   175,
     183,   185,   194,   195,   192,   197,   198,   199,   201,   204,
     202,   206,   208,   210,   211,   212,   213,   218,   214,   226,
     215,   221,   217,   235,   236,   239,   225,   247,   193,   244,
     233,   139,   237,   241,   238,   243,   174,   209,   190,   164,
     216,   242,    83
};

static const yytype_uint8 yycheck[] =
{
     116,    88,    89,    90,   123,    82,    11,    84,    85,   108,
     126,   205,    51,    17,   221,    62,    11,    19,    65,    19,
      29,    60,    61,    62,    29,    64,    62,    29,    67,    29,
       7,    40,    41,    42,    43,    44,    45,    19,   115,    19,
     247,     3,   158,   159,    53,    54,    50,    29,    52,    29,
      62,   245,    57,    65,    30,   142,   143,   144,   145,   146,
     137,   138,    57,   162,    32,     0,   185,   183,    62,     4,
       5,    23,    24,    25,    26,    10,    11,    12,    13,    14,
      15,    16,     6,     3,     8,    20,    21,    22,     3,     3,
       3,   207,    27,    28,    51,    38,   173,    46,    47,    48,
      49,     3,    37,    60,    61,    62,    62,    64,    62,    51,
      67,     8,     6,    62,     8,     9,    65,   204,    60,    61,
      62,    51,    64,    62,    62,    67,    32,     3,   244,    17,
      60,    61,    62,    51,    64,     3,    62,    67,    46,    47,
      48,    49,    60,    61,    35,    62,    64,    39,    17,    67,
      36,    62,     3,     3,    62,    40,    41,    42,    43,    44,
      45,    60,    61,    62,    62,    31,    65,    62,    53,    54,
      60,    61,    62,    33,    36,    65,    17,    64,    62,    62,
      19,    19,    19,    18,    17,     3,    40,    30,    19,    17,
      62,    62,    62,     6,    34,    18,    17,    62,    18,    58,
      19,    62,     3,    60,    62,    51,    18,    62,    56,    62,
      55,    18,    29,     3,     3,    18,     3,     3,    18,     3,
      62,    19,    56,     3,    29,    29,    62,    18,   164,    17,
      62,   104,    62,    62,   232,    62,   140,   190,   160,   128,
     201,   237,    66
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    69,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    27,    28,    37,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    88,    93,    94,    95,   111,     6,     8,     9,     6,
       8,    46,    47,    48,    49,    62,    65,    98,   110,    62,
       7,     3,    30,    32,    62,     3,     3,     3,     3,     3,
      38,    62,    62,     8,    62,    62,    19,    29,    99,    32,
      17,     3,     3,    62,    62,    35,    39,    17,    36,    62,
       3,     3,    62,   110,    62,    65,    62,    60,    61,    62,
      65,    96,    31,    33,   101,    62,    64,    62,    84,    87,
      62,    36,    29,    99,    17,    99,    99,    19,   100,    19,
      97,    97,    29,    97,    97,    18,    17,    51,    60,    61,
      62,    64,    67,    92,   103,     3,    40,    30,    19,    83,
      23,    24,    25,    26,    86,    17,    62,    62,    65,    96,
      62,   101,    60,    61,    62,    65,    62,    99,    92,    29,
      40,    41,    42,    43,    44,    45,    53,    54,   109,   109,
      34,   102,    92,     6,    84,    18,    17,    50,    52,    62,
      17,    99,    99,    18,   100,    58,   105,    97,    97,    29,
      97,    97,    97,    19,    89,    62,    62,    92,    62,    92,
     103,   101,    62,    83,     3,    60,    85,    51,    18,    62,
      99,    56,    55,   104,    62,    92,    18,   109,    29,   102,
       3,     3,    18,     3,    18,    62,   107,    56,     3,    97,
      89,    19,    90,    62,    92,    62,     3,    11,    29,    57,
     108,   106,   107,    62,    90,     3,    29,    62,   106,    29,
      91,    62,   108,    62,    17,    92,    89,    18,    90
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    68,    69,    69,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    80,    81,    82,    83,    83,    84,    84,    84,    84,
      85,    86,    86,    86,    86,    87,    88,    89,    89,    90,
      91,    90,    92,    92,    92,    92,    92,    93,    94,    95,
      96,    96,    96,    96,    96,    97,    97,    97,    97,    97,
      97,    98,    98,    98,    98,    98,    99,    99,    99,    99,
      99,   100,   100,   101,   101,   102,   102,   103,   103,   103,
     103,   103,   103,   103,   104,   104,   104,   105,   105,   106,
     106,   107,   107,   108,   108,   108,   109,   109,   109,   109,
     109,   109,   109,   109,   110,   110,   110,   110,   111
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,    10,     4,     8,     0,     3,     5,     3,     2,     4,
       1,     1,     1,     1,     1,     1,    10,     0,     3,     0,
       0,     8,     1,     1,     1,     1,     1,     5,     8,     9,
       2,     2,     4,     2,     2,     0,     3,     3,     5,     3,
       3,     1,     5,     2,     4,     4,     0,     6,     3,     5,
       5,     0,     3,     0,     3,     0,     3,     3,     3,     3,
       3,     5,     5,     7,     0,     3,     5,     0,     4,     0,
       2,     2,     4,     0,     1,     1,     1,     1,     1,     1,
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
#line 182 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1423 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 187 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1431 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 192 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1439 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 198 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1447 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 204 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1455 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 210 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1463 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 216 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1472 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 222 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1480 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 228 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1489 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 236 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1498 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 242 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
            (CONTEXT->ssql->sstr.create_index).isUnique = 1;
            create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));

        }
#line 1509 "yacc_sql.tab.c"
    break;

  case 32: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 250 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1518 "yacc_sql.tab.c"
    break;

  case 33: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 257 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1530 "yacc_sql.tab.c"
    break;

  case 35: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 267 "yacc_sql.y"
                                   {    }
#line 1536 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 272 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number), 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1551 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def: ID_get type NULLABLE  */
#line 282 "yacc_sql.y"
                             {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		CONTEXT->value_length++;
	}
#line 1562 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type  */
#line 289 "yacc_sql.y"
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
#line 1577 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type NOT NULL_TOKEN  */
#line 300 "yacc_sql.y"
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
#line 1592 "yacc_sql.tab.c"
    break;

  case 40: /* number: NUMBER  */
#line 313 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].string);}
#line 1598 "yacc_sql.tab.c"
    break;

  case 41: /* type: INT_T  */
#line 316 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1604 "yacc_sql.tab.c"
    break;

  case 42: /* type: STRING_T  */
#line 317 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1610 "yacc_sql.tab.c"
    break;

  case 43: /* type: FLOAT_T  */
#line 318 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1616 "yacc_sql.tab.c"
    break;

  case 44: /* type: DATE_T  */
#line 319 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1622 "yacc_sql.tab.c"
    break;

  case 45: /* ID_get: ID  */
#line 323 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1631 "yacc_sql.tab.c"
    break;

  case 46: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE value_opt SEMICOLON  */
#line 332 "yacc_sql.y"
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
#line 1650 "yacc_sql.tab.c"
    break;

  case 48: /* value_list: COMMA value value_list  */
#line 348 "yacc_sql.y"
                             {
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1658 "yacc_sql.tab.c"
    break;

  case 50: /* $@1: %empty  */
#line 353 "yacc_sql.y"
                       {
        CONTEXT->multi_insert_lines += 1;
    }
#line 1666 "yacc_sql.tab.c"
    break;

  case 51: /* value_opt: COMMA value_opt $@1 LBRACE value value_list RBRACE value_opt  */
#line 356 "yacc_sql.y"
                                             {
    }
#line 1673 "yacc_sql.tab.c"
    break;

  case 52: /* value: NUMBER  */
#line 359 "yacc_sql.y"
          {
        if (CONTEXT->multi_insert_lines == 0) {

  		    value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		} else {
		    size_t line = CONTEXT->multi_insert_lines - 1;
		    value_init_integer(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
		}
		}
#line 1687 "yacc_sql.tab.c"
    break;

  case 53: /* value: FLOAT  */
#line 368 "yacc_sql.y"
          {
        if (CONTEXT->multi_insert_lines == 0) {

  		    value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		} else {
            int line = CONTEXT->multi_insert_lines - 1;
            value_init_float(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
		}
		}
#line 1701 "yacc_sql.tab.c"
    break;

  case 54: /* value: SSS  */
#line 377 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
		if (CONTEXT->multi_insert_lines == 0)  {

  	    	value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		} else {
		    int line = CONTEXT->multi_insert_lines - 1;
		    value_init_string(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
		}
		}
#line 1716 "yacc_sql.tab.c"
    break;

  case 55: /* value: DATE  */
#line 387 "yacc_sql.y"
              {
	    (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string)) - 2);
	    if (CONTEXT->multi_insert_lines == 0) {
            value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
        } else {
            int line = CONTEXT->multi_insert_lines - 1;
            value_init_date(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++], (yyvsp[0].string));
	    }
	    }
#line 1730 "yacc_sql.tab.c"
    break;

  case 56: /* value: NULL_TOKEN  */
#line 396 "yacc_sql.y"
                   {
        if (CONTEXT->multi_insert_lines == 0) {

  		    value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		} else {
		    size_t line = CONTEXT->multi_insert_lines - 1;
		    value_init_null(&CONTEXT->extraValue[line].values[CONTEXT->extraValue[line].value_length++]);
		}
		}
#line 1744 "yacc_sql.tab.c"
    break;

  case 57: /* delete: DELETE FROM ID where SEMICOLON  */
#line 409 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1756 "yacc_sql.tab.c"
    break;

  case 58: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 419 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1768 "yacc_sql.tab.c"
    break;

  case 59: /* select: SELECT select_attr FROM ID rel_list where orderby groupby SEMICOLON  */
#line 429 "yacc_sql.y"
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
#line 1790 "yacc_sql.tab.c"
    break;

  case 60: /* aggrevalue: STAR aggrevaluelist  */
#line 449 "yacc_sql.y"
                           {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1800 "yacc_sql.tab.c"
    break;

  case 61: /* aggrevalue: ID aggrevaluelist  */
#line 454 "yacc_sql.y"
                       {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1810 "yacc_sql.tab.c"
    break;

  case 62: /* aggrevalue: ID DOT ID aggrevaluelist  */
#line 459 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1820 "yacc_sql.tab.c"
    break;

  case 63: /* aggrevalue: NUMBER aggrevaluelist  */
#line 464 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1830 "yacc_sql.tab.c"
    break;

  case 64: /* aggrevalue: FLOAT aggrevaluelist  */
#line 469 "yacc_sql.y"
                          {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));     
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1840 "yacc_sql.tab.c"
    break;

  case 66: /* aggrevaluelist: COMMA STAR aggrevaluelist  */
#line 475 "yacc_sql.y"
                                    {
			CONTEXT->ssql->flag = SCF_FAILURE;
	}
#line 1848 "yacc_sql.tab.c"
    break;

  case 67: /* aggrevaluelist: COMMA ID aggrevaluelist  */
#line 478 "yacc_sql.y"
                                           {
			CONTEXT->ssql->flag = SCF_FAILURE;
	}
#line 1856 "yacc_sql.tab.c"
    break;

  case 68: /* aggrevaluelist: COMMA ID DOT ID aggrevaluelist  */
#line 481 "yacc_sql.y"
                                                 {
			CONTEXT->ssql->flag = SCF_FAILURE;
	}
#line 1864 "yacc_sql.tab.c"
    break;

  case 69: /* aggrevaluelist: COMMA NUMBER aggrevaluelist  */
#line 484 "yacc_sql.y"
                                              {
			CONTEXT->ssql->flag = SCF_FAILURE;
	}
#line 1872 "yacc_sql.tab.c"
    break;

  case 70: /* aggrevaluelist: COMMA FLOAT aggrevaluelist  */
#line 487 "yacc_sql.y"
                                             {
			CONTEXT->ssql->flag = SCF_FAILURE;
	}
#line 1880 "yacc_sql.tab.c"
    break;

  case 71: /* select_attr: STAR  */
#line 493 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1890 "yacc_sql.tab.c"
    break;

  case 72: /* select_attr: aggretype LBRACE aggrevalue RBRACE attr_list  */
#line 498 "yacc_sql.y"
                                                      {
			for (int i = 0; i<CONTEXT->ssql->sstr.selection.attr_num; i++){
				CONTEXT->ssql->sstr.selection.attributes[i].aggre_type = CONTEXT->aggre_type[i];
			}
		}
#line 1900 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: ID attr_list  */
#line 503 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1910 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: ID DOT ID attr_list  */
#line 508 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1920 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: ID DOT STAR attr_list  */
#line 513 "yacc_sql.y"
                            {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 1930 "yacc_sql.tab.c"
    break;

  case 77: /* attr_list: COMMA aggretype LBRACE aggrevalue RBRACE attr_list  */
#line 521 "yacc_sql.y"
                                                            {
			for (int i = 0; i<CONTEXT->ssql->sstr.selection.attr_num; i++){
				CONTEXT->ssql->sstr.selection.attributes[i].aggre_type = CONTEXT->aggre_type[i];
			}
	    }
#line 1940 "yacc_sql.tab.c"
    break;

  case 78: /* attr_list: COMMA ID attr_list  */
#line 526 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	// CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1952 "yacc_sql.tab.c"
    break;

  case 79: /* attr_list: COMMA ID DOT ID attr_list  */
#line 533 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1964 "yacc_sql.tab.c"
    break;

  case 80: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 540 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 1974 "yacc_sql.tab.c"
    break;

  case 82: /* rel_list: COMMA ID rel_list  */
#line 549 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 1982 "yacc_sql.tab.c"
    break;

  case 84: /* where: WHERE condition condition_list  */
#line 555 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1990 "yacc_sql.tab.c"
    break;

  case 86: /* condition_list: AND condition condition_list  */
#line 561 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1998 "yacc_sql.tab.c"
    break;

  case 87: /* condition: ID comOp value  */
#line 567 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
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
#line 2023 "yacc_sql.tab.c"
    break;

  case 88: /* condition: value comOp value  */
#line 588 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
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
#line 2047 "yacc_sql.tab.c"
    break;

  case 89: /* condition: ID comOp ID  */
#line 608 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
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
#line 2071 "yacc_sql.tab.c"
    break;

  case 90: /* condition: value comOp ID  */
#line 628 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
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
#line 2097 "yacc_sql.tab.c"
    break;

  case 91: /* condition: ID DOT ID comOp value  */
#line 650 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
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
#line 2122 "yacc_sql.tab.c"
    break;

  case 92: /* condition: value comOp ID DOT ID  */
#line 671 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
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
#line 2147 "yacc_sql.tab.c"
    break;

  case 93: /* condition: ID DOT ID comOp ID DOT ID  */
#line 692 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
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
#line 2170 "yacc_sql.tab.c"
    break;

  case 95: /* groupby: GROUP BY ID  */
#line 713 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, NULL,(yyvsp[0].string));
		CONTEXT->ssql->sstr.selection.groupby_attr = &attr;
	}
#line 2180 "yacc_sql.tab.c"
    break;

  case 96: /* groupby: GROUP BY ID DOT ID  */
#line 718 "yacc_sql.y"
                             {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string),(yyvsp[0].string));
		CONTEXT->ssql->sstr.selection.groupby_attr = &attr;
	}
#line 2190 "yacc_sql.tab.c"
    break;

  case 98: /* orderby: ORDER BY orderby_attr orderby_attr_list  */
#line 727 "yacc_sql.y"
                                              {	
				//
			}
#line 2198 "yacc_sql.tab.c"
    break;

  case 100: /* orderby_attr_list: orderby_attr orderby_attr_list  */
#line 733 "yacc_sql.y"
                                     {
				// 
			}
#line 2206 "yacc_sql.tab.c"
    break;

  case 101: /* orderby_attr: ID AscDesc  */
#line 738 "yacc_sql.y"
                   {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		Orderby orderby;
		orderby_init_append(&(CONTEXT->ssql->sstr.selection), CONTEXT->asc_desc, &attr, &orderby);
	}
#line 2217 "yacc_sql.tab.c"
    break;

  case 102: /* orderby_attr: ID DOT ID AscDesc  */
#line 744 "yacc_sql.y"
                            {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		Orderby orderby;
		orderby_init_append(&(CONTEXT->ssql->sstr.selection), CONTEXT->asc_desc, &attr, &orderby);
	}
#line 2228 "yacc_sql.tab.c"
    break;

  case 103: /* AscDesc: %empty  */
#line 754 "yacc_sql.y"
        {
		CONTEXT->asc_desc = 0;
	}
#line 2236 "yacc_sql.tab.c"
    break;

  case 104: /* AscDesc: ASC  */
#line 757 "yacc_sql.y"
              {
		CONTEXT->asc_desc = 0;
	}
#line 2244 "yacc_sql.tab.c"
    break;

  case 105: /* AscDesc: DESC  */
#line 760 "yacc_sql.y"
               {
		CONTEXT->asc_desc = 1;
	}
#line 2252 "yacc_sql.tab.c"
    break;

  case 106: /* comOp: EQ  */
#line 765 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2258 "yacc_sql.tab.c"
    break;

  case 107: /* comOp: LT  */
#line 766 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2264 "yacc_sql.tab.c"
    break;

  case 108: /* comOp: GT  */
#line 767 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2270 "yacc_sql.tab.c"
    break;

  case 109: /* comOp: LE  */
#line 768 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2276 "yacc_sql.tab.c"
    break;

  case 110: /* comOp: GE  */
#line 769 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2282 "yacc_sql.tab.c"
    break;

  case 111: /* comOp: NE  */
#line 770 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2288 "yacc_sql.tab.c"
    break;

  case 112: /* comOp: IS  */
#line 771 "yacc_sql.y"
             {CONTEXT->comp = IS_COMPOP; }
#line 2294 "yacc_sql.tab.c"
    break;

  case 113: /* comOp: ISNOT  */
#line 772 "yacc_sql.y"
                {CONTEXT->comp = IS_NOT_COMPOP; }
#line 2300 "yacc_sql.tab.c"
    break;

  case 114: /* aggretype: COU  */
#line 776 "yacc_sql.y"
            {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = COUNT;
	}
#line 2308 "yacc_sql.tab.c"
    break;

  case 115: /* aggretype: MI  */
#line 779 "yacc_sql.y"
             {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = MIN;
	}
#line 2316 "yacc_sql.tab.c"
    break;

  case 116: /* aggretype: MA  */
#line 782 "yacc_sql.y"
             {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = MAX;
	}
#line 2324 "yacc_sql.tab.c"
    break;

  case 117: /* aggretype: AV  */
#line 785 "yacc_sql.y"
             {
		CONTEXT->aggre_type[CONTEXT->ssql->sstr.selection.attr_num] = AVG;
	}
#line 2332 "yacc_sql.tab.c"
    break;

  case 118: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 792 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2341 "yacc_sql.tab.c"
    break;


#line 2345 "yacc_sql.tab.c"

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

#line 797 "yacc_sql.y"

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
