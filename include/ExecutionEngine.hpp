#ifndef EXECUTIONENGINE_HPP
#define EXECUTIONENGINE_HPP

#include <vector>
#include <memory>
#include "Ruleset.hpp"
#include <any>

namespace enginexrules {

    class ExecutionEngine {
    public:
        ExecutionEngine();
        void addRuleset(const Ruleset& ruleset);
        bool execute(const std::string& name, const std::any& input);
        bool execute(std::vector<std::string>& names, const std::any& input);

    private:
        std::vector<std::unique_ptr<Ruleset>> rulesets;
    };

}

#endif
