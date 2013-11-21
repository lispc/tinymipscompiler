/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     REG = 259,
     LABEL = 260,
     PUSH = 261,
     POP = 262,
     LT = 263,
     GT = 264,
     GE = 265,
     LE = 266,
     NE = 267,
     EQ = 268,
     STRING = 269,
     CALL = 270,
     RET = 271,
     END = 272,
     J0 = 273,
     J1 = 274,
     JMP = 275,
     ADD = 276,
     SUB = 277,
     MUL = 278,
     DIV = 279,
     MOD = 280,
     NEG = 281,
     AND = 282,
     OR = 283,
     GETI = 284,
     GETS = 285,
     GETC = 286,
     PUTI = 287,
     PUTS = 288,
     PUTC = 289,
     PUTI_ = 290,
     PUTS_ = 291,
     PUTC_ = 292
   };
#endif
/* Tokens.  */
#define INT 258
#define REG 259
#define LABEL 260
#define PUSH 261
#define POP 262
#define LT 263
#define GT 264
#define GE 265
#define LE 266
#define NE 267
#define EQ 268
#define STRING 269
#define CALL 270
#define RET 271
#define END 272
#define J0 273
#define J1 274
#define JMP 275
#define ADD 276
#define SUB 277
#define MUL 278
#define DIV 279
#define MOD 280
#define NEG 281
#define AND 282
#define OR 283
#define GETI 284
#define GETS 285
#define GETC 286
#define PUTI 287
#define PUTS 288
#define PUTC 289
#define PUTI_ 290
#define PUTS_ 291
#define PUTC_ 292




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 45 "nas.y"
{
  long i;
  char s[500];
}
/* Line 1529 of yacc.c.  */
#line 128 "nas.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

