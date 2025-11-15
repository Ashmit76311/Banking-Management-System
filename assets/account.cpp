#include "account.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Account::Account(const std::string& name, int initial_balance)
    : name_(name), balance_(initial_balance) {
    if (initial_balance < 0)
        throw InvalidAmountException("Initial balance cannot be negative");
    record_transaction("Account Created", initial_balance);
}

// ------------------- Basic Getters -------------------
int Account::get_balance() const { return balance_; }
std::string Account::get_name() const { return name_; }
const std::vector<Transaction>& Account::get_transactions() const { return transactions_; }

// ------------------- Helper: Current Time -------------------
std::string Account::get_current_time() const {
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// ------------------- Record Transaction -------------------
void Account::record_transaction(const std::string& type, int amount) {
    Transaction tx{type, amount, get_current_time()};
    transactions_.push_back(tx);
}

// ------------------- Deposit -------------------
void Account::deposit(int amount) {
    if (amount <= 0)
        throw InvalidAmountException("Deposit amount must be positive");

    balance_ += amount;
    record_transaction("Deposit", amount);
}

// ------------------- Withdraw -------------------
void Account::withdraw(int amount) {
    if (amount <= 0)
        throw InvalidAmountException("Withdrawal amount must be positive");

    if (amount > balance_)
        throw InsufficientFundsException("Insufficient funds for withdrawal");

    balance_ -= amount;
    record_transaction("Withdrawal", amount);
}

// ------------------- Print Summary -------------------
void Account::print_summary() const {
    std::cout << "--------------------------------------\n";
    std::cout << "Account Holder : " << name_ << "\n";
    std::cout << "Current Balance: ₹" << balance_ << "\n";
    std::cout << "--------------------------------------\n";
    std::cout << "Transaction History:\n";

    for (const auto& tx : transactions_) {
        std::cout << std::left << std::setw(12) << tx.type
                  << " | Amount: " << std::setw(8) << tx.amount
                  << " | Date: " << tx.timestamp << "\n";
    }
    std::cout << "--------------------------------------\n";
}
