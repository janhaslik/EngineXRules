#include <iostream>
#include <string>
#include <any>
#include <functional>
#include <vector>
#include "ExecutionEngine.hpp"
#include "Ruleset.hpp"

void onBuyTriggered() {
    std::cout << "Buy trigger activated!" << std::endl;
}

void onSellTriggered() {
    std::cout << "Sell trigger activated!" << std::endl;
}

struct TradeData {
    int tradeId;
    std::string symbol;
    float price;
    int volume;
};

int main() {
    enginexrules::ExecutionEngine engine;

    // Buy ruleset
    enginexrules::Ruleset buyRuleset("buyRuleset", onBuyTriggered);
    buyRuleset.addRule({[](const std::any& input) -> bool {
        try {
            const TradeData& trade = std::any_cast<TradeData>(input);
            return trade.price < 100.0f && trade.volume > 1000;  // Buy condition
        } catch (const std::bad_any_cast&) {
            return false;
        }
    }});
    engine.addRuleset(buyRuleset);

    // Sell ruleset
    enginexrules::Ruleset sellRuleset("sellRuleset", onSellTriggered);
    sellRuleset.addRule({[](const std::any& input) -> bool {
        try {
            const TradeData& trade = std::any_cast<TradeData>(input);
            return trade.price > 150.0f && trade.volume < 500;  // Sell condition
        } catch (const std::bad_any_cast&) {
            return false;
        }
    }});
    engine.addRuleset(sellRuleset);

    std::vector<TradeData> trades = {
        {1, "AAPL", 150.0f, 2000},
        {2, "GOOGL", 120.0f, 500},
        {3, "AAPL", 80.0f, 2500},
        {4, "AAPL", 200.0f, 300},
        {5, "MSFT", 130.0f, 1200}
    };

    for (const auto& trade : trades) {
        std::cout << "Evaluating trade ID " << trade.tradeId << " with symbol " << trade.symbol << std::endl;
        engine.execute("buyRuleset", trade);
        engine.execute("sellRuleset", trade);
    }

    return 0;
}
