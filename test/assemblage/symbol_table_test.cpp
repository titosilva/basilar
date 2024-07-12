#include "../../src/assembler/assemblage/symbol_table.hpp"
#include "../test_suite.hpp"

using namespace std;
using namespace basilar::assembler::assemblage;

DefineTestSuiteFor(SymbolTable)

    DefineTest(ShouldAddReferenceToUndefinedSymbol) {
        SymbolTable table;
        table.add_reference_to("symbol", 21);

        ASSERT_EQ(table.get_address("symbol"), -1);
        ASSERT_EQ(table.get_references("symbol"), list<int>({21}));
    }

    DefineTest(ShouldDefineSymbol) {
        SymbolTable table;
        table.add_reference_to("symbol", 21);
        table.define("symbol", 42);
        auto refs = table.get_references("symbol");

        ASSERT_EQ(table.get_address("symbol"), 42);
        ASSERT_EQ(refs, list<int>({21}));
    }

    DefineTest(ShouldReturnFalseWhenDefiningTwice) {
        SymbolTable table;
        table.add_reference_to("symbol", 21);
        table.define("symbol", 42);

        ASSERT_FALSE(table.define("symbol", 42));
    }

    DefineTest(ShouldReturnMinusOneWhenSymbolNotFound) {
        SymbolTable table;

        ASSERT_EQ(table.get_address("symbol"), -1);
    }

EndTestSuite

RunTest(SymbolTable, ShouldAddReferenceToUndefinedSymbol)
RunTest(SymbolTable, ShouldDefineSymbol)
RunTest(SymbolTable, ShouldReturnFalseWhenDefiningTwice)
RunTest(SymbolTable, ShouldReturnMinusOneWhenSymbolNotFound)

