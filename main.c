#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int id;
    char model[50];
    char brand[50];
    char class[50];
    char body[50];
    char transmission[50];
    char fuel[50];
    float price, engineCapacity, enginePower;
} Car;

typedef struct {
    char surname[200];
    char firstname[200];
    char patronymic[200];
    char city[200];
    char email[200];
    char phone[200];
} Customer;

Customer customer;

typedef struct {
    Car car;
    int days;
} Rental;

Rental* rentals = NULL;

int numRentals = 0;

void listOfCars(Car* inventoryOfCars, int countCars) {
    printf("\nСписок продуктів:\n");
    for (int i = 0; i < countCars; i++) {
        printf("ID: %d, Бренд: %s, Модель: %s, Клас: %s, Кузов: %s, Трансмісія: %s, Паливо: %s, Двигун: %.2f л. %.2f к. с., Ціна: %.2f грн/день\n",
            inventoryOfCars[i].id, inventoryOfCars[i].brand, inventoryOfCars[i].model, inventoryOfCars[i].class,
            inventoryOfCars[i].body, inventoryOfCars[i].transmission, inventoryOfCars[i].fuel, inventoryOfCars[i].engineCapacity, inventoryOfCars[i].enginePower,
            inventoryOfCars[i].price);
    }
}

void registerCustomer() {
    printf("\nВас вітає інтернет-сайт НУБІП-РЕНТАЛ з оренди автомобілів!\n");
    printf("Будь ласка, зареєструйтеся для продовження.\n");

    printf("\nПрізвище: ");
    scanf("%49[^\n]%*c", customer.surname);

    printf("Ім'я: ");
    scanf("%49[^\n]%*c", customer.firstname);

    printf("По батькові: ");
    scanf("%49[^\n]%*c", customer.patronymic);

    printf("Місто: ");
    scanf("%49[^\n]%*c", customer.city);

    printf("Е-пошта: ");
    scanf("%99[^\n]%*c", customer.email);

    printf("Номер телефону: ");
    scanf("%19[^\n]%*c", customer.phone);

    printf("\nВітаємо, %s! Ви успішно зареєструвалися на нашому інтернет-сайті.\n", customer.firstname);
}


void addRentalToCart(Car* inventoryOfCars, int countCars) {
    int productId, days;

    printf("\nВведіть ID автомобіля для оренди: ");
    scanf("%d", &productId);

    bool carFound = false;
    for (int i = 0; i < countCars; i++) {
        if (inventoryOfCars[i].id == productId) {
            carFound = true;

            printf("Введіть кількість днів для оренди: ");
            scanf("%d", &days);

            Rental rental;
            rental.car = inventoryOfCars[i];
            rental.days = days;

    
            numRentals++;
            rentals = (Rental*)realloc(rentals, numRentals * sizeof(Rental));
            rentals[numRentals - 1] = rental;

            printf("\nОрендований автомобіль додано до кошика.\n");
            break;
        }
    }

    if (!carFound) {
        printf("\nПомилка: Автомобіль з ідентифікатором %d не знайдено.\n", productId);
    }
}

void showCart() {
    printf("Кошик оренд:\n");
    float totalPrice = 0;

    for (int i = 0; i < numRentals; i++) {
        Rental rental = rentals[i];
        printf("ID: %d, Бренд: %s, Модель: %s, Клас: %s, Кузов: %s, Трансмісія: %s, Паливо: %s, Двигун: %.2f л. %.2f к. с., Ціна: %.2f грн/день, Кількість днів: %d\n",
            rental.car.id, rental.car.brand, rental.car.model, rental.car.class,
            rental.car.body, rental.car.transmission, rental.car.fuel, rental.car.engineCapacity, rental.car.enginePower,
            rental.car.price, rental.days);

        totalPrice += rental.car.price * rental.days;
    }

    printf("\nЗагальна ціна оренди: %.2f грн\n", totalPrice);
}

void clearCart() {
    free(rentals);
    rentals = NULL;
    numRentals = 0;
    printf("\nКошик оренд порожній.\n");
}


void readIntInput(int* value) {
    while (scanf("%d", value) != 1) {
        printf("Невірне значення. Будь ласка, спробуйте ще раз: ");
        while (getchar() != '\n');
    }
}

void readFloatInput(float* value) {
    while (scanf("%f", value) != 1) {
        printf("Невірне значення. Будь ласка, спробуйте ще раз: ");
        while (getchar() != '\n'); 
    }
}

void removeRentalFromCart() {
    int productId;

    printf("\nВведіть ID автомобіля, який потрібно видалити з кошика: ");
    scanf("%d", &productId);

    bool carFound = false;
    for (int i = 0; i < numRentals; i++) {
        if (rentals[i].car.id == productId) {
            carFound = true;

            Rental* tempRentals = (Rental*)malloc((numRentals - 1) * sizeof(Rental));
            int index = 0;
            for (int j = 0; j < numRentals; j++) {
                if (j != i) {
                    tempRentals[index] = rentals[j];
                    index++;
                }
            }

            free(rentals);
            rentals = tempRentals;
            numRentals--;

            printf("\nОрендований автомобіль з ID %d видалено з кошика.\n", productId);
            break;
        }
    }

    if (!carFound) {
        printf("\nПомилка: Автомобіль з ідентифікатором %d не знайдено в кошику.\n", productId);
    }
}

void filterForCarsByBrand(Car inventoryOfCars[], int numCars) {
    char brandFilter[20];
    printf("\nВведіть назву бренду автомобілів: ");
    scanf("%s", brandFilter);

    printf("\nРезультати після фільтрації за брендом %s:\n", brandFilter);

    bool foundCars = false;

    for (int i = 0; i < numCars; i++) {
        if (strcmp(inventoryOfCars[i].brand, brandFilter) == 0) {
            foundCars = true;
            printf("ID: %d, Бренд: %s, Модель: %s, Клас: %s, Кузов: %s, Трансмісія: %s, Паливо: %s, Двигун: %.2f л. %.2f к. с., Ціна: %.2f грн/день\n",
                   inventoryOfCars[i].id, inventoryOfCars[i].brand, inventoryOfCars[i].model, inventoryOfCars[i].class,
                   inventoryOfCars[i].body, inventoryOfCars[i].transmission, inventoryOfCars[i].fuel, inventoryOfCars[i].engineCapacity, inventoryOfCars[i].enginePower,
                   inventoryOfCars[i].price);
        }
    }

    if (!foundCars) {
        printf("\nАвтомобілів бренду %s не знайдено.\n", brandFilter);
    }
}

void filterForCarsByClass(Car inventoryOfCars[], int numCars) {
    char classFilter[100];
    printf("\nВведіть клас автомобілів: ");
    scanf("%s", classFilter);

    printf("\nРезультати після фільтрації за класом %s:\n", classFilter);

    bool foundCars = false;

    for (int i = 0; i < numCars; i++) {
        if (strcmp(inventoryOfCars[i].class, classFilter) == 0) {
            foundCars = true;
            printf("ID: %d, Бренд: %s, Модель: %s, Клас: %s, Кузов: %s, Трансмісія: %s, Паливо: %s, Двигун: %.2f л. %.2f к. с., Ціна: %.2f грн/день\n",
                   inventoryOfCars[i].id, inventoryOfCars[i].brand, inventoryOfCars[i].model, inventoryOfCars[i].class,
                   inventoryOfCars[i].body, inventoryOfCars[i].transmission, inventoryOfCars[i].fuel, inventoryOfCars[i].engineCapacity, inventoryOfCars[i].enginePower,
                   inventoryOfCars[i].price);
        }
    }

    if (!foundCars) {
        printf("\nАвтомобілів класу %s не знайдено.\n", classFilter);
    }
}

void filterForCarsByBodyType(Car inventoryOfCars[], int numCars) {
    char bodyTypeFilter[100];
    printf("\nВведіть тип кузова автомобілів: ");
    scanf("%s", bodyTypeFilter);

    printf("\nРезультати після фільтрації за типом кузова %s:\n", bodyTypeFilter);

    bool foundCars = false;

    for (int i = 0; i < numCars; i++) {
        if (strcmp(inventoryOfCars[i].body, bodyTypeFilter) == 0) {
            foundCars = true;
            printf("ID: %d, Бренд: %s, Модель: %s, Клас: %s, Кузов: %s, Трансмісія: %s, Паливо: %s, Двигун: %.2f л. %.2f к. с., Ціна: %.2f грн/день\n",
                   inventoryOfCars[i].id, inventoryOfCars[i].brand, inventoryOfCars[i].model, inventoryOfCars[i].class,
                   inventoryOfCars[i].body, inventoryOfCars[i].transmission, inventoryOfCars[i].fuel, inventoryOfCars[i].engineCapacity, inventoryOfCars[i].enginePower,
                   inventoryOfCars[i].price);
        }
    }

    if (!foundCars) {
        printf("\nАвтомобілів з типом кузова %s не знайдено.\n", bodyTypeFilter);
    }
}

void filterForCarsByTransmission(Car inventoryOfCars[], int numCars) {
    char transmissionFilter[100];
    printf("\nВведіть тип трансмісії автомобілів: ");
    scanf("%s", transmissionFilter);

    printf("\nРезультати після фільтрації за типом трансмісії %s:\n", transmissionFilter);

    bool foundCars = false;

    for (int i = 0; i < numCars; i++) {
        if (strcmp(inventoryOfCars[i].transmission, transmissionFilter) == 0) {
            foundCars = true;
            printf("ID: %d, Бренд: %s, Модель: %s, Клас: %s, Кузов: %s, Трансмісія: %s, Паливо: %s, Двигун: %.2f л. %.2f к. с., Ціна: %.2f грн/день\n",
                   inventoryOfCars[i].id, inventoryOfCars[i].brand, inventoryOfCars[i].model, inventoryOfCars[i].class,
                   inventoryOfCars[i].body, inventoryOfCars[i].transmission, inventoryOfCars[i].fuel, inventoryOfCars[i].engineCapacity, inventoryOfCars[i].enginePower,
                   inventoryOfCars[i].price);
        }
    }

    if (!foundCars) {
        printf("\nАвтомобілів з типом трансмісії %s не знайдено.\n", transmissionFilter);
    }
}

void filterForCarsByFuelType(Car inventoryOfCars[], int numCars) {
    char fuelTypeFilter[100];
    printf("\nВведіть тип палива автомобілів: ");
    scanf("%s", fuelTypeFilter);

    printf("\nРезультати після фільтрації за типом палива %s:\n", fuelTypeFilter);

    bool foundCars = false;

    for (int i = 0; i < numCars; i++) {
        if (strcmp(inventoryOfCars[i].fuel, fuelTypeFilter) == 0) {
            foundCars = true;
            printf("ID: %d, Бренд: %s, Модель: %s, Клас: %s, Кузов: %s, Трансмісія: %s, Паливо: %s, Двигун: %.2f л. %.2f к. с., Ціна: %.2f грн/день\n",
                   inventoryOfCars[i].id, inventoryOfCars[i].brand, inventoryOfCars[i].model, inventoryOfCars[i].class,
                   inventoryOfCars[i].body, inventoryOfCars[i].transmission, inventoryOfCars[i].fuel, inventoryOfCars[i].engineCapacity, inventoryOfCars[i].enginePower,
                   inventoryOfCars[i].price);
        }
    }

    if (!foundCars) {
        printf("\nАвтомобілів з типом палива %s не знайдено.\n", fuelTypeFilter);
    }
}

void filterForCarsByEngineCapacity(Car inventoryOfCars[], int numCars) {
    float minCapacity, maxCapacity;
    printf("\nВведіть (через крапку) мінімальний об'єм двигуна (л): ");
    scanf("%f", &minCapacity);
    printf("Введіть (через крапку) максимальний об'єм двигуна (л): ");
    scanf("%f", &maxCapacity);

    printf("\nРезультати після фільтрації за об'ємом двигуна: %.2f л - %.2f л\n", minCapacity, maxCapacity);

    bool foundCars = false;

    for (int i = 0; i < numCars; i++) {
        if (inventoryOfCars[i].engineCapacity >= minCapacity && inventoryOfCars[i].engineCapacity <= maxCapacity) {
            foundCars = true;
            printf("ID: %d, Бренд: %s, Модель: %s, Клас: %s, Кузов: %s, Трансмісія: %s, Паливо: %s, Двигун: %.2f л. %.2f к. с., Ціна: %.2f грн/день\n",
                   inventoryOfCars[i].id, inventoryOfCars[i].brand, inventoryOfCars[i].model, inventoryOfCars[i].class,
                   inventoryOfCars[i].body, inventoryOfCars[i].transmission, inventoryOfCars[i].fuel, inventoryOfCars[i].engineCapacity, inventoryOfCars[i].enginePower,
                   inventoryOfCars[i].price);
        }
    }

    if (!foundCars) {
        printf("\nАвтомобілів за фільтром об'єму двигуна %.2f л - %.2f л не знайдено.\n", minCapacity, maxCapacity);
    }
}

void filterForCarsByEnginePower(Car inventoryOfCars[], int numCars) {
    float minPower, maxPower;
    printf("\nВведіть мінімальну потужність двигуна (к. с.): ");
    scanf("%f", &minPower);
    printf("Введіть максимальну потужність двигуна (к. с.): ");
    scanf("%f", &maxPower);

    printf("\nРезультати після фільтрації за потужністю двигуна: %.2f к. с. - %.2f к. с.\n", minPower, maxPower);

    bool foundCars = false;

    for (int i = 0; i < numCars; i++) {
        if (inventoryOfCars[i].enginePower >= minPower && inventoryOfCars[i].enginePower <= maxPower) {
            foundCars = true;
            printf("ID: %d, Бренд: %s, Модель: %s, Клас: %s, Кузов: %s, Трансмісія: %s, Паливо: %s, Двигун: %.2f л. %.2f к. с., Ціна: %.2f грн/день\n",
                   inventoryOfCars[i].id, inventoryOfCars[i].brand, inventoryOfCars[i].model, inventoryOfCars[i].class,
                   inventoryOfCars[i].body, inventoryOfCars[i].transmission, inventoryOfCars[i].fuel, inventoryOfCars[i].engineCapacity, inventoryOfCars[i].enginePower,
                   inventoryOfCars[i].price);
        }
    }

    if (!foundCars) {
        printf("\nАвтомобілів за фільтром потужності двигуна %.2f к. с. - %.2f к. с. не знайдено.\n", minPower, maxPower);
    }
}

void filterForCarsByPrice(Car inventoryOfCars[], int numCars) {
    float minPrice, maxPrice;
    printf("\nВведіть мінімальну ціну (грн/день): ");
    scanf("%f", &minPrice);
    printf("Введіть максимальну ціну (грн/день): ");
    scanf("%f", &maxPrice);

    printf("\nРезультати після фільтрації за ціною: %.2f грн/день - %.2f грн/день\n", minPrice, maxPrice);

    bool foundCars = false;

    for (int i = 0; i < numCars; i++) {
        if (inventoryOfCars[i].price >= minPrice && inventoryOfCars[i].price <= maxPrice) {
            foundCars = true;
            printf("ID: %d, Бренд: %s, Модель: %s, Клас: %s, Кузов: %s, Трансмісія: %s, Паливо: %s, Двигун: %.2f л. %.2f к. с., Ціна: %.2f грн/день\n",
                   inventoryOfCars[i].id, inventoryOfCars[i].brand, inventoryOfCars[i].model, inventoryOfCars[i].class,
                   inventoryOfCars[i].body, inventoryOfCars[i].transmission, inventoryOfCars[i].fuel, inventoryOfCars[i].engineCapacity, inventoryOfCars[i].enginePower,
                   inventoryOfCars[i].price);
        }
    }

    if (!foundCars) {
        printf("\nАвтомобілів за фільтром ціни %.2f грн/день - %.2f грн/день не знайдено.\n", minPrice, maxPrice);
    }
}


int main()
{
    printf("Hello World");

    return 0;
}
