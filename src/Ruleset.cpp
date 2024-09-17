#include "../include/Ruleset.hpp"
#include <iostream>

namespace enginexrules {

    Ruleset::Ruleset(const std::string& name, std::function<void()> action)
        : name(name), action(std::move(action)) {
    }

    void Ruleset::addRule(const Rule& rule) {
        ruleset.push_back(rule);
    }

    std::string Ruleset::getName() const {
        return name;
    }

    void Ruleset::callAction() const {
        this->action();
    }

    bool Ruleset::evaluate(const std::any& input) const {
        for (const auto& rule : ruleset) {
            if (!rule.condition(input)) {
                return false;
            }
        }

        return true;
    }

    std::function<void()> Ruleset::getAction() const {
        return action;
    }

}
