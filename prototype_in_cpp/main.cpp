#include <iostream>
#include <string>
#include <vector>
#include <math.h>

/* To handle properly information about expenses we difine the Expense class.
It includes Names of people, how much each one paid and how much is their share.
*/

class Person {
private:
    float Debit = 0.0;  // initilized in zero
    float Share;
public:
    std::string Name;   // initilized by constructor
    float Paid;         // initilized by constructor

    Person(std::string name, float paid, float share) { Name = name ; Share = share ; Paid = paid; } // constructor

    float getDebit() const { return Debit; } //getter
    void setDebit (float debit) { Debit = debit; } //setter
    float getShare() const { return Share; } //getter
    void setShare (float share) { Share = share; } //setter

    void Status () {
        if (Debit < 0)
            std::cout << Name << " should receive " << abs(Debit) << std::endl;
        else if ( Debit > 0 )
            std::cout << Name << " should give " << Debit << std::endl;
        else
            std::cout << Name << " isn't in charge of anything!" << std::endl;
    }
};

class Expense {
private:
    std::vector<Person> People;

public:
    uint Id;
    float Cost;

    static uint id_counter;
    
    Expense (float cost) { Cost = cost ; Id = ++id_counter;}


    void addPerson(std::string name, float paid, float share) { //setter
        People.emplace_back(name, paid, share);
    }
    void displayPeople() { //getter
        for (size_t i = 0; i < People.size() ; i++)
            std::cout << i+1 << ". Name = " << People[i].Name << std::endl;
    }

    void calculateShare(bool equal_flag) {
        float expense_mean = Cost / People.size();
        float whole_expense = 0;
        for (size_t i = 0; i < People.size() ; i++)
            whole_expense += People[i].getShare();
        float expense_difference = (Cost - whole_expense);

        if ( equal_flag ==  1 ) {
            std::cout << "Equally sharing is activated!" << std::endl;
            for (size_t i = 0 ; i < People.size() ; i++)
                People[i].setShare(expense_mean); }
        else if ( expense_difference == 0 )
            std::cout << "Good job! You did a precised calculation, We don't change values." << std::endl;
        else if ( abs(expense_difference) < 0.20 * Cost ) {
            std::cout << "There is " << abs(expense_difference) / Cost *100 <<  "\% differences between values. Maybe taxes are the root cause!" << std::endl;
            for (size_t i = 0; i < People.size() ; i++)
                People[i].setShare ( People[i].getShare() + expense_difference / People.size() ); }
        else
            std::cout << "There are huge differences between values. We don't change any values but we strongly recommend you to double check!" << std::endl << "Totoal Expense: " << Cost << " Reported Expense: " << whole_expense << std::endl;
        }
    void setDebit() {
        for (size_t i = 0 ; i < People.size() ; i++)
            People[i].setDebit(People[i].getShare() - People[i].Paid ); 
    }
    void Result() {
        for (size_t i = 0 ; i < People.size() ; i++)
            People[i].Status();
    }
};


uint Expense::id_counter = 1000;


int main() {
    std::string version = "v0.0.1:alpha";
    std::cout << "Let's Go Dutch: " << version << std::endl;

    Expense expense1 = Expense(100.0);
    expense1.addPerson("Ali", 20.0, 30.0);
    expense1.addPerson("Ahmad", 35.0, 50.0);
    expense1.addPerson("Abbas", 35.0, 10.0);
    std::cout << "People are in charge:" << std::endl;
    expense1.displayPeople();
    expense1.calculateShare(0);
    expense1.setDebit();

    expense1.Result();



    return 0;
}