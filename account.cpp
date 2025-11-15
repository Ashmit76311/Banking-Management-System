#include "account.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

// Helper: get current local time as string
static std::string current_time_str() {
    std::time_t now = std::time(nullptr);
    std::tm local_tm;
#ifdef _WIN32
    localtime_s(&local_tm, &now);
#else
    localtime_r(&now, &local_tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// Constructor
Account::Account(const std::string& name, int initial_balance)
    : name_(name), balance_(initial_balance) {
    if (initial_balance < 0)
        throw InvalidAmountException("Initial balance cannot be negative");
    record_transaction("Account Created", initial_balance);
}

// Getters
int Account::get_balance() const { return balance_; }
std::string Account::get_name() const { return name_; }
const std::vector<Transaction>& Account::get_transactions() const { return transactions_; }

// Internal: record a transaction with timestamp
void Account::record_transaction(const std::string& type, int amount) {
    Transaction tx{ type, amount, current_time_str() };
    transactions_.push_back(tx);
}

// Deposit
void Account::deposit(int amount) {
    if (amount <= 0) throw InvalidAmountException("Deposit amount must be positive");
    balance_ += amount;
    record_transaction("Deposit", amount);
}

// Withdraw
void Account::withdraw(int amount) {
    if (amount <= 0) throw InvalidAmountException("Withdrawal amount must be positive");
    if (amount > balance_) throw InsufficientFundsException("Insufficient funds for withdrawal");
    balance_ -= amount;
    record_transaction("Withdrawal", amount);
}

// Print a human-friendly summary
void Account::print_summary() const {
    std::cout << "--------------------------------------\n";
    std::cout << "Account Holder : " << name_ << "\n";
    std::cout << "Current Balance: " << balance_ << "\n";
    std::cout << "--------------------------------------\n";
    std::cout << "Transaction History:\n";
    for (const auto& tx : transactions_) {
        std::cout << std::left << std::setw(15) << tx.type
                  << " | Amount: " << std::setw(8) << tx.amount
                  << " | Date: " << tx.timestamp << "\n";
    }
    std::cout << "--------------------------------------\n";
}
