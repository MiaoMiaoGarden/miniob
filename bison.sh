#! /bin/bash

cd ./src/observer/sql/parser/

bison -d -b yacc_sql yacc_sql.y
flex lex_sql.l
