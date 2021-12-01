cmake_minimum_required(VERSION 3.20)
project(project_2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories(.)

add_executable(project_2
        Automaton.h
        Automatons/ColonAutomaton.cpp
        Automatons/ColonAutomaton.h
        Automatons/ColonDashAutomaton.cpp
        Automatons/ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h Automatons/CommaAutomaton.h Automatons/CommaAutomaton.cpp Automatons/PeriodAutomaton.h Automatons/PeriodAutomaton.cpp Automatons/QmarkAutomaton.h Automatons/QmarkAutomaton.cpp Automatons/LeftParenAutomaton.cpp Automatons/LeftParenAutomaton.h Automatons/RightParenAutomaton.cpp Automatons/RightParenAutomaton.h Automatons/MultiplyAutomaton.h Automatons/AddAutomaton.h Automatons/MultiplyAutomaton.cpp Automatons/AddAutomaton.cpp Automatons/SchemesAutomaton.h Automatons/SchemesAutomaton.cpp Automatons/FactsAutomaton.cpp Automatons/FactsAutomaton.h Automatons/RulesAutomaton.cpp Automatons/RulesAutomaton.h Automatons/QueriesAutomaton.cpp Automatons/QueriesAutomaton.h Automatons/StringAutomaton.cpp Automatons/CommentAutomaton.cpp Automatons/UndefinedAutomaton.cpp Automatons/EOFAutomaton.cpp Automatons/StringAutomaton.h Automatons/CommentAutomaton.h Automatons/UndefinedAutomaton.h Automatons/EOFAutomaton.h ID.h ID.cpp Automatons/MultiComment.h Automatons/MultiComment.cpp DatalogProgram.cpp DatalogProgram.h Rule.cpp Rule.h Predicate.cpp Predicate.h Parameter.cpp Parameter.h Interpreter.h Interpreter.cpp Tuple.cpp Tuple.h Relation.cpp Relation.h Header.cpp Header.h Database.cpp Database.h)
