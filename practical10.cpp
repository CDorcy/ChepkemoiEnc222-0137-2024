//ENC222-0137/2024
#include <iostream>
#include <string>
#include <map>
#include <memory>
class Symbol {
private:
    std::string name;
    std::string type;
    int scope_level;

public:
    Symbol(std::string n, std::string t, int s) 
        : name(n), type(t), scope_level(s) {}

    // *** MISSING MEMBER FUNCTION ADDED HERE ***
    std::string getName() const {
        return name;
    }
    // *****************************************

    void display() const {
        std::cout << "| Name: " << name << " | Type: " << type << " | Scope: " << scope_level << " |" << std::endl;
    }
};

// 2. The 'SymbolTable' Class (Manages Symbols - Association/Aggregation)
class SymbolTable {
private:
    std::map<std::string, std::unique_ptr<Symbol>> table;

public:
    void addSymbol(std::unique_ptr<Symbol> sym) {
        // The call to sym->getName() now works correctly
        std::cout << "Table: Registering symbol '" << sym->getName() << "'." << std::endl;
        table[sym->getName()] = std::move(sym);
    }

    Symbol* getSymbol(const std::string& name) {
        if (table.count(name)) {
            return table[name].get();
        }
        return nullptr;
    }
};

// 3. The 'SymbolRegistrar' Class (Utility Class - Dependency)
class SymbolRegistrar {
public:
    void registerSymbol(SymbolTable& table, const std::string& name, const std::string& type, int scope) {
        std::cout << "Registrar: Preparing to register a new symbol..." << std::endl;
        auto newSym = std::make_unique<Symbol>(name, type, scope); 
        table.addSymbol(std::move(newSym));
    }
};

// --- Driver Program ---
int main() {
    SymbolTable globalScopeTable; 
    SymbolRegistrar registrar;    

    registrar.registerSymbol(globalScopeTable, "myVariable", "int", 1);
    registrar.registerSymbol(globalScopeTable, "calculate", "function", 1);

    std::cout << "\nRetrieving a symbol from the table:" << std::endl;
    Symbol* s = globalScopeTable.getSymbol("myVariable");
    if (s) {
        s->display();
    }

    return 0;
}
