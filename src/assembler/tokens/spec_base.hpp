#pragma once

#define Def static TokenParser
#define As =
#define Else |
#define EndDef ;
#define Then >>

#define DefParser(name, parser) Def name As OptSpace Then (parser) Then OptSpace
#define DefType(type, parser) Def type As OptSpace Then (JoinWithType((parser), #type)) Then OptSpace
#define DefLine(name, parser) Def name As OptSpace Then (parser) Then OptSpace >> Require(Close, "Expected line end")
#define ParserTypeOf(type) #type
