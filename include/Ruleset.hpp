#ifndef RULESET_HPP
#define RULESET_HPP

#include <functional>
#include <vector>
#include <string>
#include <any>

namespace enginexrules {

    struct Rule {
        std::function<bool(const std::any&)> condition;
    };

    class Ruleset {
    public:
        Ruleset(const std::string& name, std::function<void()> action);
        void addRule(const Rule& rule);
        std::string getName() const;
        bool evaluate(const std::any& input) const;
        void callAction() const;
        std::function<void()> getAction() const;

    private:
        std::string name;
        std::vector<Rule> ruleset;
        std::function<void()> action;
    };

}

#endif
