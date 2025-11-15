#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <stdexcept>

struct Transaction {
    std::string type;      // "Deposit" or "Withdrawal"
    int amount;
    std::string timestamp; // formatted date-time
};

class InsufficientFundsException : public std::runtime_error {
public:
    explicit InsufficientFundsException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class InvalidAmountException : public std::runtime_error {
public:
    explicit InvalidAmountException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class Account {
public:
    Account(const std::string& name, int initial_balance = 0);

    // basic getters
    int get_balance() const;
    std::string get_name() const;

    // operations
    void deposit(int amount);
    void withdraw(int amount);

    // transaction log
    const std::vector<Transaction>& get_transactions() const;

    // helper to display info
    void print_summary() const;

private:
    std::string name_;
    int balance_;
    std::vector<Transaction> transactions_;

    std::string get_current_time() const;
    void record_transaction(const std::string& type, int amount);
};
