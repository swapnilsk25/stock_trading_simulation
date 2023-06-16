#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Stock {
    string symbol;
    double price;
    int quantity;
};

class Trader {
private:
    vector<Stock> portfolio; // Vector to store stocks in the portfolio
    vector<Stock> stockMarket = { // Vector to store stocks available in the market
        {"FINSOL", 2000, 1000},
        {"TCS", 1500, 500},
        {"INFO", 1200, 600},         // Hard-coded stocks 
        {"AMZN", 1000, 400},
        {"WIPOR", 500, 800}
    };
    int fund = 0; // Available funds for trading

public:
    // Function to buy stocks
    void buyStock()
    {
        if (fund == 0)
        {
            cout << "Insufficient Fund. Add funds first." << endl;
            cout << "Enter the Amount: ";
            int fund;
            cin >> fund;
            addFunds(fund); // Add funds to the trading account
        }

        cout << "Name of Stock" << "\t" << "Price" << "\t" << "Quantity" << endl;
        for (Stock& show_stock : stockMarket) {
            cout << show_stock.symbol << "\t" << "\t" << show_stock.price << "\t" << show_stock.quantity << endl;
        }

        string name;
        int quantity;
        cout << "Enter Stock Name: ";
        cin >> name;
        cout << "Enter Stock Quantity: ";
        cin >> quantity;
        int flag = 0;
        for (Stock& buy : stockMarket) {
            if (buy.symbol == name)
            {
                flag = 1;
                int value = quantity * buy.price;
                if (value <= fund) {
                    if (buy.quantity > 0 && buy.quantity >= quantity)
                    {
                        buy.quantity -= quantity; // Reduce the available quantity of the stock
                        int size = portfolio.size();
                        if (portfolio.size() == 0) {
                            Stock addStock;
                            addStock.symbol = name;
                            addStock.price = buy.price;
                            addStock.quantity = quantity;
                            portfolio.push_back(addStock); // Add the stock to the portfolio
                            fund -= value; // Deduct the funds used for buying the stock
                            cout << "Bought " << quantity << " shares of " << name << " at $" << buy.price << " each." << endl;
                            cout << "Stock added to your portfolio. Please check the portfolio." << endl;
                            showportfolio(); // Display the updated portfolio
                        }
                        else {
                            for (Stock& addPortfolio : portfolio) {
                                if (addPortfolio.symbol == name)
                                {
                                    addPortfolio.quantity += quantity; // Increase the quantity of the existing stock in the portfolio
                                    fund -= value; // Deduct the funds used for buying the stock
                                    cout << "Stock added to Existing." << endl;
                                    showportfolio(); 
                                }
                                else
                                {
                                    Stock addStock;
                                    addStock.symbol = name;
                                    addStock.price = buy.price;
                                    addStock.quantity = quantity;
                                    portfolio.push_back(addStock); // Add the stock to the portfolio
                                    fund -= value; // Deduct the funds used for buying the stock
                                    cout << "Bought " << quantity << " shares of " << name << " at " << buy.price << " each." << endl;
                                    cout << "Stock added to your portfolio. Please check the portfolio." << endl;
                                    showportfolio(); // Display the updated portfolio
                                }
                            }
                        }
                    }
                    else
                    {
                        cout << "Insufficient stocks to sell." << endl;
                    }
                }
                else {
                    cout << "Insufficient funds. Please add funds." << endl;
                }
            }
        }
        if (flag == 0) {
            cout << "Stock " << name << " not found in the market or not listed." << endl;
        }
        mainMenu(); // Display the main menu
    }

    // Function to sell stocks
    void sellStock()
    {
        cout << "\nYour Portfolio\n" << endl;
        cout << "Symbol" << "\t" << "Price" << "\t" << "Quantity" << endl;
        for (Stock& stock : portfolio)
        {
            cout << stock.symbol << "\t " << stock.price << "\t" << stock.quantity << endl;
        }
        string name;
        int quantity;
        cout << "Enter the stock name you want to sell: ";
        cin >> name;
        cout << "Enter the quantity: ";
        cin >> quantity;
        for (Stock& sell : portfolio) {
            if (sell.symbol == name)
            {
                int value = sell.price * quantity;
                if (sell.quantity >= quantity)
                {
                    sell.quantity -= quantity; // Reduce the quantity of the stock in the portfolio
                    fund += value; // Add the funds obtained from selling the stock
                     cout << "Sold Successfully" << endl;
                    for (Stock& addMarket : stockMarket)
                    {
                        if (addMarket.symbol == name)
                        {
                            addMarket.quantity += quantity; // Increase the available quantity of the stock in the market
                        }
    
                    }
                }
                else {
                    cout << "Insufficient stocks to sell." << endl;
                }
            }
            else
            {
                cout << "This stock is not available in the portfolio." << endl;
            }
        }
        showportfolio(); // Display the updated portfolio
        //mainMenu(); // Display the main menu
    }

    void CollectionOfStock()
    {
        cout << "Name of Stock" << "\t" << "Price" << "\t" << "Quantity" << endl;
        for (Stock& show_stock : stockMarket) {
            cout << show_stock.symbol << "\t" << "\t" << show_stock.price << "\t" << show_stock.quantity << endl;
        }
        mainMenu();
    }

    // Function to display the current portfolio
    void showportfolio()
    {
        cout << "\nYour Portfolio\n" << endl;
        cout << "Symbol" << "\t" << "Price" << "\t" << "Quantity" << endl;
        for (Stock& stock : portfolio)
        {
            cout << stock.symbol << "\t " << stock.price << "\t" << stock.quantity << endl;
        }
        mainMenu();
    }

    // Function to calculate the total value of the portfolio
    void getPortfolioValue()
    {
        double currentValue;
        double totalValue = 0;
        cout << "\nYour Portfolio\n" << endl;
        cout << "Symbol" << "\t" << "Price" << "\t" << "Quantity" << endl;
        for (Stock& stock : portfolio)
        {
            cout << stock.symbol << "\t " << stock.price << "\t" << stock.quantity << endl;
        }
        for (Stock& stock : portfolio)
        {
            cout << "\nEnter current value of stock " << stock.symbol << ": ";
            cin >> currentValue;
            totalValue += currentValue * stock.quantity;
        }
        cout << "\nTotal Portfolio Value: " << totalValue << endl;
        mainMenu();
    }

    // Function to calculate the overall profit or loss of the portfolio
    void calculateProfitLoss()
    {
        double currentValue;
        double initialPortfolioValue = 0;
        double currentPortfolioValue = 0;
        cout << "\nYour Portfolio\n" << endl;
        cout << "Symbol" << "\t" << "Price" << "\t" << "Quantity" << endl;
        for (Stock& stock : portfolio)
        {
            cout << stock.symbol << "\t " << stock.price << "\t" << stock.quantity << endl;
        }
        for (Stock& stock : portfolio)
        {
            cout << "\nEnter current value of stock " << stock.symbol << ": ";
            cin >> currentValue;
            currentPortfolioValue += currentValue * stock.quantity;
            initialPortfolioValue += stock.price * stock.quantity;
        }

        double profitLoss = currentPortfolioValue - initialPortfolioValue;
        if (profitLoss > 0) {
            cout << "\nYour Total Profit: " << profitLoss << endl;
        }
        else if (profitLoss == 0) {
            cout << "\nYou don't have any profit or loss." << endl;
        }
        else {
            profitLoss *= -1;
            cout << "\nYour Total Loss: " << profitLoss << endl;
        }
        mainMenu();
    }

    // Function to add funds to the trading account
    double addFunds(int fund) {
        this->fund = fund;
        return this->fund;
        mainMenu();
    }

    // Function to display the main menu and handle user input
    void mainMenu()
    {
        cout << "Main Menu" << endl;
        cout << "1. Collection Of Stocks" << endl;
        cout << "2. Buy Stocks" << endl;
        cout << "3. Sell Stocks" << endl;
        cout << "4. Show Portfolio" << endl;
        cout << "5. Portfolio Value" << endl;
        cout << "6. Overall Profit/Loss" << endl;
        cout << "7. Check Availability of Fund" << endl;
        cout << "Select From the Option: ";
        int num;
        cin >> num;
        switch (num)
        {
        case 1:
            CollectionOfStock();
            break;
        case 2:
            buyStock();
            break;
        case 3:
            sellStock();
            break;
        case 4:
            showportfolio();
            break;
        case 5:
            getPortfolioValue();
            break;
        case 6:
            calculateProfitLoss();
            break;
        case 7:
            double fund = this->fund;
            cout << "Trading Fund: " << fund << endl;
        }
    }
}; 

int main() {
    Trader trader;
    cout << "Welcome to the Stock Market!" << endl;
    trader.mainMenu();
}
