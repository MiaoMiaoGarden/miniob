/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    UNIQUE = 264,                  /* UNIQUE  */
    SELECT = 265,                  /* SELECT  */
    DESC = 266,                    /* DESC  */
    SHOW = 267,                    /* SHOW  */
    SYNC = 268,                    /* SYNC  */
    INSERT = 269,                  /* INSERT  */
    DELETE = 270,                  /* DELETE  */
    UPDATE = 271,                  /* UPDATE  */
    LBRACE = 272,                  /* LBRACE  */
    RBRACE = 273,                  /* RBRACE  */
    COMMA = 274,                   /* COMMA  */
    TRX_BEGIN = 275,               /* TRX_BEGIN  */
    TRX_COMMIT = 276,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 277,            /* TRX_ROLLBACK  */
    INT_T = 278,                   /* INT_T  */
    STRING_T = 279,                /* STRING_T  */
    FLOAT_T = 280,                 /* FLOAT_T  */
    DATE_T = 281,                  /* DATE_T  */
<<<<<<< HEAD
    HELP = 282,                    /* HELP  */
    EXIT = 283,                    /* EXIT  */
    DOT = 284,                     /* DOT  */
    INTO = 285,                    /* INTO  */
    VALUES = 286,                  /* VALUES  */
    FROM = 287,                    /* FROM  */
    WHERE = 288,                   /* WHERE  */
    AND = 289,                     /* AND  */
    SET = 290,                     /* SET  */
    ON = 291,                      /* ON  */
    LOAD = 292,                    /* LOAD  */
    DATA = 293,                    /* DATA  */
    INFILE = 294,                  /* INFILE  */
    EQ = 295,                      /* EQ  */
    IN = 296,                      /* IN  */
    NOTIN = 297,                   /* NOTIN  */
    LT = 298,                      /* LT  */
    GT = 299,                      /* GT  */
    LE = 300,                      /* LE  */
    GE = 301,                      /* GE  */
    NE = 302,                      /* NE  */
    COU = 303,                     /* COU  */
    MI = 304,                      /* MI  */
    MA = 305,                      /* MA  */
    AV = 306,                      /* AV  */
    NOT = 307,                     /* NOT  */
    NULL_TOKEN = 308,              /* NULL_TOKEN  */
    NULLABLE = 309,                /* NULLABLE  */
    IS = 310,                      /* IS  */
    ISNOT = 311,                   /* ISNOT  */
    GROUP = 312,                   /* GROUP  */
    BY = 313,                      /* BY  */
    ASC = 314,                     /* ASC  */
    ORDER = 315,                   /* ORDER  */
    INNER = 316,                   /* INNER  */
    JOIN = 317,                    /* JOIN  */
    NUMBER = 318,                  /* NUMBER  */
    FLOAT = 319,                   /* FLOAT  */
    ID = 320,                      /* ID  */
    PATH = 321,                    /* PATH  */
    SSS = 322,                     /* SSS  */
    STAR = 323,                    /* STAR  */
    STRING_V = 324,                /* STRING_V  */
    DATE = 325,                    /* DATE  */
    SUB_SELECTION = 326            /* SUB_SELECTION  */
=======
    TEXT_T = 282,                  /* TEXT_T  */
    HELP = 283,                    /* HELP  */
    EXIT = 284,                    /* EXIT  */
    DOT = 285,                     /* DOT  */
    INTO = 286,                    /* INTO  */
    VALUES = 287,                  /* VALUES  */
    FROM = 288,                    /* FROM  */
    WHERE = 289,                   /* WHERE  */
    AND = 290,                     /* AND  */
    SET = 291,                     /* SET  */
    ON = 292,                      /* ON  */
    LOAD = 293,                    /* LOAD  */
    DATA = 294,                    /* DATA  */
    INFILE = 295,                  /* INFILE  */
    EQ = 296,                      /* EQ  */
    LT = 297,                      /* LT  */
    GT = 298,                      /* GT  */
    LE = 299,                      /* LE  */
    GE = 300,                      /* GE  */
    NE = 301,                      /* NE  */
    COU = 302,                     /* COU  */
    MI = 303,                      /* MI  */
    MA = 304,                      /* MA  */
    AV = 305,                      /* AV  */
    NOT = 306,                     /* NOT  */
    NULL_TOKEN = 307,              /* NULL_TOKEN  */
    NULLABLE = 308,                /* NULLABLE  */
    IS = 309,                      /* IS  */
    ISNOT = 310,                   /* ISNOT  */
    GROUP = 311,                   /* GROUP  */
    BY = 312,                      /* BY  */
    ASC = 313,                     /* ASC  */
    ORDER = 314,                   /* ORDER  */
    INNER = 315,                   /* INNER  */
    JOIN = 316,                    /* JOIN  */
    NUMBER = 317,                  /* NUMBER  */
    FLOAT = 318,                   /* FLOAT  */
    ID = 319,                      /* ID  */
    PATH = 320,                    /* PATH  */
    SSS = 321,                     /* SSS  */
    STAR = 322,                    /* STAR  */
    STRING_V = 323,                /* STRING_V  */
    DATE = 324,                    /* DATE  */
    TEXT = 325                     /* TEXT  */
>>>>>>> 32e9b56e07741c0e1b0df385e7ff5fbc6901ec63
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
<<<<<<< HEAD
#line 131 "yacc_sql.y"
=======
#line 130 "yacc_sql.y"
>>>>>>> 32e9b56e07741c0e1b0df385e7ff5fbc6901ec63

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
    char *position;


<<<<<<< HEAD
#line 146 "yacc_sql.tab.h"
=======
#line 145 "yacc_sql.tab.h"
>>>>>>> 32e9b56e07741c0e1b0df385e7ff5fbc6901ec63

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
