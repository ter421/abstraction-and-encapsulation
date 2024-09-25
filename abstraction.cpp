// jed filip m. sayat
#include <iostream>
using namespace std;

class BankAccount 
{
private:
    double accountBalance;

public:
    BankAccount(double initialBalance) 
    {
        if (initialBalance >= 0) 
        {
            accountBalance = initialBalance;
        } 
        else 
        {
            accountBalance = 0;
            cout << "\nInvalid initial balance! Setting balance to 0." << endl;
        }
    }

    void deposit(double amount) 
    {
        if (amount > 0) 
        {
            accountBalance += amount;
            cout << "\nDeposit successful! \nNew balance: " << accountBalance << endl;
        } 
        else 
        {
            cout << "\nInvalid deposit amount! Please enter a positive number." << endl;
        }
    }

    void checkBalance() const 
    {
        cout << "\nCurrent balance: " << accountBalance << endl;
    }

    virtual void withdraw(double amount) = 0;

    double getBalance() const 
    {
        return accountBalance;
    }

    void setBalance(double newBalance) 
    {
        accountBalance = newBalance;
    }

};

class SavingsAccount : public BankAccount 
{
private:
    const double MINIMUM_BALANCE = 1000.0;

public:
    SavingsAccount(double initialBalance) : BankAccount(initialBalance) 
    {
        if (initialBalance < MINIMUM_BALANCE) 
        {
            cout << "\nInitial deposit must be at least " << MINIMUM_BALANCE << " for a savings account." << endl;
            setBalance(0);
        }
    }

    void withdraw(double amount) override 
    {
        if (amount <= 0) 
        {
            cout << "\nInvalid withdrawal amount! Please enter a positive number." << endl;
        } 
        else if (getBalance() - amount < MINIMUM_BALANCE) 
        {
            cout << "\nInsufficient balance! Minimum balance of " << MINIMUM_BALANCE << " must be maintained." << endl;
        } 
        else 
        {
            setBalance(getBalance() - amount);
            cout << "\nWithdrawal successful! \nNew balance: " << getBalance() << endl;
        }
    }
};

class CurrentAccount : public BankAccount 
{
public:
    CurrentAccount(double initialBalance) : BankAccount(initialBalance) {}

    void withdraw(double amount) override 
    {
        if (amount <= 0) 
        {
            cout << "\nInvalid withdrawal amount! Please enter a positive number." << endl;
        } 
        else if (amount > getBalance()) 
        {
            cout << "\nInsufficient funds!" << endl;
        } 
        else 
        {
            setBalance(getBalance() - amount);
            cout << "\nWithdrawal successful! \nNew balance: " << getBalance() << endl;
        }
    }
};

void showMainMenu() 
{
    cout << "\n=== Main Menu ===\n";
    cout << "1. Savings Account\n";
    cout << "2. Current Account\n";
    cout << "3. Exit\n";
    cout << "\nEnter your choice: ";
}

void showSubMenu() 
{
    cout << "\n=== Sub Menu ===\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Check Balance\n";
    cout << "4. Exit to Main Menu\n";
    cout << "\nEnter your choice: ";
}

bool isValidInput() 
{
    if (cin.fail()) 
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nInvalid input! Please enter a valid number." << endl;
        return false;
    }
    return true;
}

double getValidAmount() 
{
    double amount;
    cin >> amount;
    if (!isValidInput()) return -1;
    if (amount > 0) return amount;

    cout << "\nPlease enter a positive number." << endl;
    return -1;
}

int main() 
{
    int mainChoice = 0;
    int subChoice = 0;

    SavingsAccount savingsAccount(1000);
    CurrentAccount currentAccount(0);

    while (mainChoice != 3) 
    {
        showMainMenu();
        cin >> mainChoice;

        if (isValidInput()) 
        {
            BankAccount* account = nullptr;
            if (mainChoice == 1) 
            {
                account = &savingsAccount;
            } 
            else if (mainChoice == 2) 
            {
                account = &currentAccount;
            } 
            else if (mainChoice == 3) 
            {
                cout << "\nExiting the system. Goodbye!\n";
                break;
            } 
            else 
            {
                cout << "\nInvalid choice! Please try again.\n";
                continue;
            }

            while (subChoice != 4) 
            {
                showSubMenu();
                cin >> subChoice;
                if (isValidInput()) 
                {
                    if (subChoice == 1) 
                    {
                        cout << "\nEnter amount to deposit: ";
                        double amount = getValidAmount();
                        if (amount > 0) account->deposit(amount);
                    } 
                    else if (subChoice == 2) 
                    {
                        cout << "\nEnter amount to withdraw: ";
                        double amount = getValidAmount();
                        if (amount > 0) account->withdraw(amount);
                    } 
                    else if (subChoice == 3) 
                    {
                        account->checkBalance();
                    } 
                    else if (subChoice == 4) 
                    {
                        cout << "\nExiting to Main Menu...\n";
                    } 
                    else 
                    {
                        cout << "\nInvalid choice! Please try again.\n";
                    }
                }
            }
            subChoice = 0;
        }
    }

    return 0;
}
