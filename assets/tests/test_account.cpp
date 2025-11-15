#include "account.h"
#include "gtest/gtest.h"

// Basic creation and initial balance test
TEST(AccountTest, InitialBalance) {
    Account a("Alice", 1000);
    EXPECT_EQ(a.get_balance(), 1000);
    EXPECT_EQ(a.get_name(), "Alice");
}

// Deposit increases balance
TEST(AccountTest, DepositIncreasesBalance) {
    Account a("Bob", 100);
    a.deposit(200);
    EXPECT_EQ(a.get_balance(), 300);
}

// Withdraw reduces balance correctly
TEST(AccountTest, WithdrawSuccess) {
    Account a("Carol", 500);
    a.withdraw(200);
    EXPECT_EQ(a.get_balance(), 300);
}

// Withdraw throws on insufficient funds
TEST(AccountTest, WithdrawFailInsufficient) {
    Account a("Dan", 100);
    EXPECT_THROW(a.withdraw(200), InsufficientFundsException);
}

// Withdraw throws on invalid amount
TEST(AccountTest, WithdrawInvalidAmount) {
    Account a("Eve", 300);
    EXPECT_THROW(a.withdraw(0), InvalidAmountException);
    EXPECT_THROW(a.withdraw(-50), InvalidAmountException);
}

// Deposit throws on invalid amount
TEST(AccountTest, DepositInvalidAmount) {
    Account a("Frank", 300);
    EXPECT_THROW(a.deposit(0), InvalidAmountException);
    EXPECT_THROW(a.deposit(-10), InvalidAmountException);
}

// Transaction history updates
TEST(AccountTest, TransactionHistoryRecorded) {
    Account a("Grace", 100);
    a.deposit(50);
    a.withdraw(30);
    const auto& txs = a.get_transactions();
    ASSERT_EQ(txs.size(), 3); // Created + Deposit + Withdrawal
    EXPECT_EQ(txs[0].type, "Account Created");
    EXPECT_EQ(txs[1].type, "Deposit");
    EXPECT_EQ(txs[2].type, "Withdrawal");
}
