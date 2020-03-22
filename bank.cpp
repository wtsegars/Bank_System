#include <cstdio>

struct Logger {
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
};

struct AccountDatabase {
    virtual ~AccountDatabase() = default;
    virtual void retrieve_amount(double balance) = 0;
    virtual void set_amount(double old_balance, double new_balance) = 0;
};

struct ConsoleLogger : Logger {
    void log_transfer(long from, long to, double amount) override {
        printf("[cons] %ld -> %ld: %f\n", from, to, amount);
    }
};

struct FileLogger : Logger {
    void log_transfer(long from, long to, double amount) override {
        printf("[file] %ld,%ld,%f\n", from, to, amount);
    }
};

struct Bank {
    void set_logger(Logger* new_logger) {
        logger = new_logger;
    }
    void make_transfer(long from, long to, double amount) {
        if (logger) logger->log_transfer(from, to, amount);
    }
    void make_account(AccountDatabase* new_account) {
        accountdatabase = new_account;
    }
    void balance(double balance) {
        if (accountdatabase) accountdatabase->retrieve_amount(balance);
    }
    void change_balance(double old_balance, double new_balance) {
        if (accountdatabase) accountdatabase->set_amount(old_balance, new_balance);
    }
private:
    Logger* logger{};
    AccountDatabase* accountdatabase{};
};

struct InMemoryAccountDatabase : AccountDatabase {
    void retrieve_amount(double balance) {
        printf("The balace is: %f\n", balance);
    }
    void set_amount(double old_balance, double new_balance) {
        printf("The balance has been changed from %f to %f", old_balance, new_balance);
    }
};

int main() {
    ConsoleLogger console_logger;
    FileLogger file_logger;
    Bank bank;
    InMemoryAccountDatabase in_memory_account_database;
    bank.set_logger(&console_logger); 
    bank.make_transfer(1000, 2000, 49.95);
    bank.set_logger(&file_logger); 
    bank.make_transfer(2000, 4000, 20.00); 
    bank.make_account(&in_memory_account_database);
    bank.balance(69.95);
    bank.change_balance(69.95, 35.95);
}