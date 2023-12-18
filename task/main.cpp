#include <iostream>
#include <fstream>
#include <string>

struct Product
{
    std::string name;
    double price;
    int quantity;
};

void addProductToFile(const Product& product)
{
    std::ofstream outFile("products.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << product.name << "," << product.price << "," << product.quantity << std::endl;
        outFile.close();
        std::cout << "Продукт успешно добавлен." << std::endl;
    } else {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
    }
}

void searchProduct(const std::string& name)
{
    std::ifstream inFile("products.txt");
    if (inFile.is_open())
    {
        std::string line;
        bool found = false;
        while (std::getline(inFile, line))
        {
            size_t pos = line.find(',');
            std::string name_product = line.substr(0, pos);
            if (name == name_product)
            {
                std::cout << "Найден продукт: " << line << std::endl;
                found = true;
                break;
            }
        }
        inFile.close();
        if (!found)
        {
            std::cout << "Продукт не найден." << std::endl;
        }
    } else
    {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

void sortProduct()
{
    std::ifstream inFile("products.txt");
    if (inFile.is_open())
    {
        std::string lines[500];
        int count = 0;
        std::string line;
        while (std::getline(inFile, line))
        {
            lines[count] = line;
            count++;
        }
        inFile.close();
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                size_t pos1 = lines[j].find_last_of(',');
                size_t pos2 = lines[j + 1].find_last_of(',');
                double price1 = std::stod(lines[j].substr(pos1 + 1));
                double price2 = std::stod(lines[j + 1].substr(pos2 + 1));
                if (price1 < price2)
                {
                    std::swap(lines[j], lines[j + 1]);
                }
            }
        }
        std::ofstream outFile("products.txt");
        if (outFile.is_open())
        {
            for (int i = 0; i < count; i++)
            {
                outFile << lines[i] << std::endl;
            }
            outFile.close();
            std::cout << "Продукты отсортированны по цене." << std::endl;
        } else
        {
            std::cerr << "Не удалось открыть файл для записи." << std::endl;
        }
    } else
    {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

void outputProductByLimitPrice(int price)
{
    std::ifstream inFile("product.txt");
    std::string line;
    bool found = false;
    while (getline(inFile, line))
    {
        size_t pos = line.find_last_of(',');
        double price1 = stod(line.substr(pos + 1));
        if (price1 <= price)
        {
            if (!found)
            {
                std::cout << "Найден продукст: " << std::endl;
                found = true;
            }
            std::cout << line << std::endl;
        }
    }
    inFile.close();
    if (!found)
    {
        std::cout << "Нет подходящих продуктов." << std::endl;
    }
}


int main()
{
    int choice;
    std::string name;

    do {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить продукт" << std::endl;
        std::cout << "2. Поиск продукта" << std::endl;
        std::cout << "3. Сортировать продукты по цене" << std::endl;
        std::cout << "4. Вывести продукты дешевле указанной цены" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
            {
                std::cin.ignore();
                std::string name;
                double price;
                int quantity;
                std::cout << "Введите название продукта: ";
                std::getline(std::cin, name);
                if (name.empty())
                {
                    std::cout << "Ввод прерван." << std::endl;
                    break;
                }
                std::cout << "Введите цену: ";
                std::cin >> price;
                std::cout << "Введите количество: ";
                std::cin >> quantity;
                Product newProduct = {name, price, quantity};
                addProductToFile(newProduct);
                break;
            }
            case 2:
            {
                std::cin.ignore();
                std::cout << "Введите продукт для поиска: ";
                std::getline(std::cin, name);
                searchProduct(name);
                break;
            }
            case 3:
            {
                sortProduct();
                break;
            }
            case 4:
            {
                std::cin.ignore();
                int lprice;
                std::cout << "Введите лимит цены: ";
                std::cin >> lprice;
                outputProductByLimitPrice(lprice);
                  break;
            }
            case 0:
            {
                std::cout << "Программа завершена." << std::endl;
                break;
            }
            default:
            {
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
