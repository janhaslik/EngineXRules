#include "../include/ExecutionEngine.hpp"
#include "../include/Ruleset.hpp"

namespace enginexrules {

    ExecutionEngine::ExecutionEngine() = default;

    void ExecutionEngine::addRuleset(const Ruleset& ruleset) {
        rulesets.push_back(std::make_unique<Ruleset>(ruleset));
    }

    bool ExecutionEngine::execute(const std::string& name, const std::any& input) {
        for (const auto& rs : rulesets) {
            if (rs->getName() == name) {
                if (rs->evaluate(input)){
                    rs->callAction();
                    return true;
                }
            }
        }
        return false;
    }

    bool ExecutionEngine::execute(std::vector<std::string>& names, const std::any& input) {

        std::vector<std::function<void()>> actions;
        for (const auto& name: names){
            for (const auto& rs : rulesets) {
                if (rs->getName() == name) {
                    if (!rs->evaluate(input)){
                        return false;
                    }
                }
                
                auto action = rs->getAction();
                if (action) {
                    actions.push_back(action);
                }
            }
        }

        for (const auto& action: actions){
            action();
        }

        return true;
    }

}
