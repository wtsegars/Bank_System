#include <cstdio>

struct Logger {
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
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
    void balance(long balance) {
        if (accountdatabase) accountdatabase->retrieve_amount(balance);
    }
    void change_balance(long old_balance, long new_balance) {
        if (accountdatabase) accountdatabase->set_amount(old_balance, new_balance);
    }
private:
    Logger* logger{};
    AccountDatabase* accountdatabase{};
};

struct AccountDatabase {
    virtual ~AccountDatabase() = default;
    virtual void retrieve_amount(long balance) = 0;
    virtual void set_amount(long old_balance, long new_balance) = 0;
};

struct InMemoryAccountDatabase : AccountDatabase {
    void retrieve_amount(long balance) {
        printf("The balace is: %ld\n", balance);
    }
    void set_amount(long old_balance, long new_balance) {
        printf("The balance has been changed from %ld to %ld", old_balance, new_balance);
    }
};

int main() {

}