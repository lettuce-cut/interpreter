cmake_minimum_required(VERSION 3.20)
project(project_2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories(.)

add_executable(project_2
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h CommaAutomaton.h CommaAutomaton.cpp PeriodAutomaton.h PeriodAutomaton.cpp QmarkAutomaton.h QmarkAutomaton.cpp LeftParenAutomaton.cpp LeftParenAutomaton.h RightParenAutomaton.cpp RightParenAutomaton.h MultiplyAutomaton.h AddAutomaton.h MultiplyAutomaton.cpp AddAutomaton.cpp SchemesAutomaton.h SchemesAutomaton.cpp FactsAutomaton.cpp FactsAutomaton.h RulesAutomaton.cpp RulesAutomaton.h QueriesAutomaton.cpp QueriesAutomaton.h StringAutomaton.cpp CommentAutomaton.cpp UndefinedAutomaton.cpp EOFAutomaton.cpp StringAutomaton.h CommentAutomaton.h UndefinedAutomaton.h EOFAutomaton.h ID.h ID.cpp MultiComment.h MultiComment.cpp DatalogProgram.cpp DatalogProgram.h Rule.cpp Rule.h Predicate.cpp Predicate.h Parameter.cpp Parameter.h)
