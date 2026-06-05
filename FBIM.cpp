#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

class FoodItem
{
public:
    int id;
    string name;
    int quantity;
    string expiryDate;

    FoodItem() {}

    FoodItem(int i, string n, int q, string e)
    {
        id = i;
        name = n;
        quantity = q;
        expiryDate = e;
    }
};

class FoodBank
{
private:
    vector<FoodItem> inventory;

public:
    void addFood()
    {
        int id, quantity;
        string name, expiry;

        cout << "\nEnter Food ID: ";
        cin >> id;

        for (auto &item : inventory)
        {
            if (item.id == id)
            {
                cout << "\nFood ID already exists!\n";
                return;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Food Name: ";
        getline(cin, name);

        cout << "Enter Quantity: ";
        cin >> quantity;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Expiry Date (DD/MM/YYYY): ";
        getline(cin, expiry);

        inventory.push_back(FoodItem(id, name, quantity, expiry));

        cout << "\nFood Item Added Successfully!\n";
    }

    void viewInventory()
    {
        if (inventory.empty())
        {
            cout << "\nInventory is Empty!\n";
            return;
        }

        cout << "\n========== FOOD INVENTORY ==========\n";

        for (auto &item : inventory)
        {
            cout << "ID          : " << item.id << endl;
            cout << "Name        : " << item.name << endl;
            cout << "Quantity    : " << item.quantity << endl;
            cout << "Expiry Date : " << item.expiryDate << endl;
            cout << "-----------------------------------\n";
        }
    }

    void searchFood()
    {
        int id;

        cout << "\nEnter Food ID to Search: ";
        cin >> id;

        for (auto &item : inventory)
        {
            if (item.id == id)
            {
                cout << "\nFood Found!\n";
                cout << "ID          : " << item.id << endl;
                cout << "Name        : " << item.name << endl;
                cout << "Quantity    : " << item.quantity << endl;
                cout << "Expiry Date : " << item.expiryDate << endl;
                return;
            }
        }

        cout << "\nFood Item Not Found!\n";
    }

    void updateStock()
    {
        int id, newQuantity;

        cout << "\nEnter Food ID: ";
        cin >> id;

        for (auto &item : inventory)
        {
            if (item.id == id)
            {
                cout << "Enter New Quantity: ";
                cin >> newQuantity;

                item.quantity = newQuantity;

                cout << "\nStock Updated Successfully!\n";
                return;
            }
        }

        cout << "\nFood Item Not Found!\n";
    }

    void distributeFood()
    {
        int id, amount;

        cout << "\nEnter Food ID: ";
        cin >> id;

        for (auto &item : inventory)
        {
            if (item.id == id)
            {
                cout << "Enter Quantity to Distribute: ";
                cin >> amount;

                if (amount <= item.quantity)
                {
                    item.quantity -= amount;
                    cout << "\nFood Distributed Successfully!\n";
                }
                else
                {
                    cout << "\nInsufficient Stock!\n";
                }
                return;
            }
        }

        cout << "\nFood Item Not Found!\n";
    }

    void deleteFood()
    {
        int id;

        cout << "\nEnter Food ID to Delete: ";
        cin >> id;

        for (size_t i = 0; i < inventory.size(); i++)
        {
            if (inventory[i].id == id)
            {
                inventory.erase(inventory.begin() + i);

                cout << "\nFood Item Deleted Successfully!\n";
                return;
            }
        }

        cout << "\nFood Item Not Found!\n";
    }

    void generateReport()
    {
        int totalItems = inventory.size();
        int totalQuantity = 0;

        for (auto &item : inventory)
        {
            totalQuantity += item.quantity;
        }

        cout << "\n========== FOOD BANK REPORT ==========\n";
        cout << "Total Food Items       : " << totalItems << endl;
        cout << "Total Quantity in Stock: " << totalQuantity << endl;
    }

    void saveToFile()
    {
        ofstream file("food_inventory.txt");

        if (!file)
        {
            cout << "\nError Opening File!\n";
            return;
        }

        for (auto &item : inventory)
        {
            file << item.id << ","
                 << item.name << ","
                 << item.quantity << ","
                 << item.expiryDate << endl;
        }

        file.close();

        cout << "\nData Saved Successfully!\n";
    }

    void loadFromFile()
    {
        ifstream file("food_inventory.txt");

        if (!file)
        {
            return;
        }

        inventory.clear();

        string line;

        while (getline(file, line))
        {
            stringstream ss(line);

            string idStr, name, qtyStr, expiry;

            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, qtyStr, ',');
            getline(ss, expiry);

            inventory.push_back(
                FoodItem(stoi(idStr),
                         name,
                         stoi(qtyStr),
                         expiry));
        }

        file.close();
    }
};

int main()
{
    FoodBank fb;

    fb.loadFromFile();

    int choice;

    do
    {
        cout << "\n===================================";
        cout << "\n FOOD BANK INVENTORY MANAGEMENT";
        cout << "\n===================================";
        cout << "\n1. Add Food Item";
        cout << "\n2. View Inventory";
        cout << "\n3. Search Food Item";
        cout << "\n4. Update Stock";
        cout << "\n5. Distribute Food";
        cout << "\n6. Delete Food Item";
        cout << "\n7. Generate Report";
        cout << "\n8. Save Data to File";
        cout << "\n9. Exit";
        cout << "\nEnter Choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            fb.addFood();
            break;

        case 2:
            fb.viewInventory();
            break;

        case 3:
            fb.searchFood();
            break;

        case 4:
            fb.updateStock();
            break;

        case 5:
            fb.distributeFood();
            break;

        case 6:
            fb.deleteFood();
            break;

        case 7:
            fb.generateReport();
            break;

        case 8:
            fb.saveToFile();
            break;

        case 9:
            fb.saveToFile();
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 9);

    return 0;
}