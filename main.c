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


int main() {

    Car inventoryOfCars[50];
    int countCars = 50;

    inventoryOfCars[0].id = 1;
    strcpy(inventoryOfCars[0].brand, "Volkswagen");
    strcpy(inventoryOfCars[0].model, "Jetta VI");
    strcpy(inventoryOfCars[0].class, "Середній");
    strcpy(inventoryOfCars[0].body, "Седан");
    strcpy(inventoryOfCars[0].transmission, "Автомат");
    strcpy(inventoryOfCars[0].fuel, "Бензин");
    inventoryOfCars[0].engineCapacity = 1.4;
    inventoryOfCars[0].enginePower = 122;
    inventoryOfCars[0].price = 1650;
    
    inventoryOfCars[1].id = 2;
    strcpy(inventoryOfCars[1].brand, "Volkswagen");
    strcpy(inventoryOfCars[1].model, "Polo");
    strcpy(inventoryOfCars[1].class, "Середній");
    strcpy(inventoryOfCars[1].body, "Седан");
    strcpy(inventoryOfCars[1].transmission, "Автомат");
    strcpy(inventoryOfCars[1].fuel, "Бензин");
    inventoryOfCars[1].engineCapacity = 1.6;
    inventoryOfCars[1].enginePower = 105;
    inventoryOfCars[1].price = 1600;
    
    inventoryOfCars[2].id = 3;
    strcpy(inventoryOfCars[2].brand, "Hyundai");
    strcpy(inventoryOfCars[2].model, "Accent IV");
    strcpy(inventoryOfCars[2].class, "Економ");
    strcpy(inventoryOfCars[2].body, "Седан");
    strcpy(inventoryOfCars[2].transmission, "Автомат");
    strcpy(inventoryOfCars[2].fuel, "Бензин");
    inventoryOfCars[2].engineCapacity = 1.4;
    inventoryOfCars[2].enginePower = 107;
    inventoryOfCars[2].price = 1200;
    
    inventoryOfCars[3].id = 4;
    strcpy(inventoryOfCars[3].brand, "Ford");
    strcpy(inventoryOfCars[3].model, "Fiesta VI");
    strcpy(inventoryOfCars[3].class, "Економ");
    strcpy(inventoryOfCars[3].body, "Хетчбек");
    strcpy(inventoryOfCars[3].transmission, "Автомат");
    strcpy(inventoryOfCars[3].fuel, "Бензин");
    inventoryOfCars[3].engineCapacity = 1.0;
    inventoryOfCars[3].enginePower = 100;
    inventoryOfCars[3].price = 1000;
    
    inventoryOfCars[4].id = 5;
    strcpy(inventoryOfCars[4].brand, "Chevrolet");
    strcpy(inventoryOfCars[4].model, "Spark");
    strcpy(inventoryOfCars[4].class, "Економ");
    strcpy(inventoryOfCars[4].body, "Хетчбек");
    strcpy(inventoryOfCars[4].transmission, "Автомат");
    strcpy(inventoryOfCars[4].fuel, "Бензин");
    inventoryOfCars[4].engineCapacity = 1.25;
    inventoryOfCars[4].enginePower = 80;
    inventoryOfCars[4].price = 850;
    
    inventoryOfCars[5].id = 6;
    strcpy(inventoryOfCars[5].brand, "Citroen");
    strcpy(inventoryOfCars[5].model, "C-Elysee");
    strcpy(inventoryOfCars[5].class, "Економ");
    strcpy(inventoryOfCars[5].body, "Седан");
    strcpy(inventoryOfCars[5].transmission, "Автомат");
    strcpy(inventoryOfCars[5].fuel, "Бензин");
    inventoryOfCars[5].engineCapacity = 1.6;
    inventoryOfCars[5].enginePower = 115;
    inventoryOfCars[5].price = 1350;
    
    inventoryOfCars[6].id = 7;
    strcpy(inventoryOfCars[6].brand, "Renault");
    strcpy(inventoryOfCars[6].model, "Logan");
    strcpy(inventoryOfCars[6].class, "Економ");
    strcpy(inventoryOfCars[6].body, "Седан");
    strcpy(inventoryOfCars[6].transmission, "Механіка");
    strcpy(inventoryOfCars[6].fuel, "Дизель");
    inventoryOfCars[6].engineCapacity = 1.5;
    inventoryOfCars[6].enginePower = 90;
    inventoryOfCars[6].price = 1100;
    
    inventoryOfCars[7].id = 8;
    strcpy(inventoryOfCars[7].brand, "Toyota");
    strcpy(inventoryOfCars[7].model, "Corolla 2016");
    strcpy(inventoryOfCars[7].class, "Середній");
    strcpy(inventoryOfCars[7].body, "Седан");
    strcpy(inventoryOfCars[7].transmission, "Автомат");
    strcpy(inventoryOfCars[7].fuel, "Бензин");
    inventoryOfCars[7].engineCapacity = 1.6;
    inventoryOfCars[7].enginePower = 122;
    inventoryOfCars[7].price = 1750;
    
    inventoryOfCars[8].id = 9;
    strcpy(inventoryOfCars[8].brand, "Hyundai");
    strcpy(inventoryOfCars[8].model, "Elantra 2017");
    strcpy(inventoryOfCars[8].class, "Середній");
    strcpy(inventoryOfCars[8].body, "Седан");
    strcpy(inventoryOfCars[8].transmission, "Автомат");
    strcpy(inventoryOfCars[8].fuel, "Бензин");
    inventoryOfCars[8].engineCapacity = 1.6;
    inventoryOfCars[8].enginePower = 128;
    inventoryOfCars[8].price = 1700;
    
    inventoryOfCars[9].id = 10;
    strcpy(inventoryOfCars[9].brand, "Hyundai");
    strcpy(inventoryOfCars[9].model, "Elantra 2021");
    strcpy(inventoryOfCars[9].class, "Середній");
    strcpy(inventoryOfCars[9].body, "Седан");
    strcpy(inventoryOfCars[9].transmission, "Автомат");
    strcpy(inventoryOfCars[9].fuel, "Бензин");
    inventoryOfCars[9].engineCapacity = 1.6;
    inventoryOfCars[9].enginePower = 128;
    inventoryOfCars[9].price = 1700;
    
    inventoryOfCars[10].id = 11;
    strcpy(inventoryOfCars[10].brand, "Toyota");
    strcpy(inventoryOfCars[10].model, "Corolla 2023");
    strcpy(inventoryOfCars[10].class, "Середній");
    strcpy(inventoryOfCars[10].body, "Седан");
    strcpy(inventoryOfCars[10].transmission, "Автомат");
    strcpy(inventoryOfCars[10].fuel, "Бензин");
    inventoryOfCars[10].engineCapacity = 1.6;
    inventoryOfCars[10].enginePower = 140;
    inventoryOfCars[10].price = 2000;
    
    inventoryOfCars[11].id = 12;
    strcpy(inventoryOfCars[11].brand, "Volkswagen");
    strcpy(inventoryOfCars[11].model, "Jetta VII");
    strcpy(inventoryOfCars[11].class, "Середній");
    strcpy(inventoryOfCars[11].body, "Седан");
    strcpy(inventoryOfCars[11].transmission, "Автомат");
    strcpy(inventoryOfCars[11].fuel, "Бензин");
    inventoryOfCars[11].engineCapacity = 1.6;
    inventoryOfCars[11].enginePower = 150;
    inventoryOfCars[11].price = 1800;
    
    inventoryOfCars[12].id = 13;
    strcpy(inventoryOfCars[12].brand, "Skoda");
    strcpy(inventoryOfCars[12].model, "Octavia A8");
    strcpy(inventoryOfCars[12].class, "Середній");
    strcpy(inventoryOfCars[12].body, "Седан");
    strcpy(inventoryOfCars[12].transmission, "Автомат");
    strcpy(inventoryOfCars[12].fuel, "Бензин");
    inventoryOfCars[12].engineCapacity = 1.6;
    inventoryOfCars[12].enginePower = 110;
    inventoryOfCars[12].price = 1900;
    
    inventoryOfCars[13].id = 14;
    strcpy(inventoryOfCars[13].brand, "Volkswagen");
    strcpy(inventoryOfCars[13].model, "Passat B8");
    strcpy(inventoryOfCars[13].class, "Бізнес");
    strcpy(inventoryOfCars[13].body, "Седан");
    strcpy(inventoryOfCars[13].transmission, "Автомат");
    strcpy(inventoryOfCars[13].fuel, "Дизель");
    inventoryOfCars[13].engineCapacity = 2.0;
    inventoryOfCars[13].enginePower = 150;
    inventoryOfCars[13].price = 2750;
    
    inventoryOfCars[14].id = 15;
    strcpy(inventoryOfCars[14].brand, "Mazda");
    strcpy(inventoryOfCars[14].model, "6 New");
    strcpy(inventoryOfCars[14].class, "Бізнес");
    strcpy(inventoryOfCars[14].body, "Седан");
    strcpy(inventoryOfCars[14].transmission, "Автомат");
    strcpy(inventoryOfCars[14].fuel, "Бензин");
    inventoryOfCars[14].engineCapacity = 2.0;
    inventoryOfCars[14].enginePower = 165;
    inventoryOfCars[14].price = 2800;
    
    inventoryOfCars[15].id = 16;
    strcpy(inventoryOfCars[15].brand, "Infinity");
    strcpy(inventoryOfCars[15].model, "Q 50");
    strcpy(inventoryOfCars[15].class, "Бізнес");
    strcpy(inventoryOfCars[15].body, "Седан");
    strcpy(inventoryOfCars[15].transmission, "Автомат");
    strcpy(inventoryOfCars[15].fuel, "Бензин");
    inventoryOfCars[15].engineCapacity = 3.7;
    inventoryOfCars[15].enginePower = 333;
    inventoryOfCars[15].price = 3000;
    
    inventoryOfCars[16].id = 17;
    strcpy(inventoryOfCars[16].brand, "Toyota");
    strcpy(inventoryOfCars[16].model, "Camry VX70");
    strcpy(inventoryOfCars[16].class, "Бізнес");
    strcpy(inventoryOfCars[16].body, "Седан");
    strcpy(inventoryOfCars[16].transmission, "Автомат");
    strcpy(inventoryOfCars[16].fuel, "Бензин");
    inventoryOfCars[16].engineCapacity = 2.5;
    inventoryOfCars[16].enginePower = 181;
    inventoryOfCars[16].price = 3150;
    
    inventoryOfCars[17].id = 18;
    strcpy(inventoryOfCars[17].brand, "Mercedes");
    strcpy(inventoryOfCars[17].model, "C300 4matic");
    strcpy(inventoryOfCars[17].class, "Бізнес");
    strcpy(inventoryOfCars[17].body, "Седан");
    strcpy(inventoryOfCars[17].transmission, "Автомат");
    strcpy(inventoryOfCars[17].fuel, "Бензин");
    inventoryOfCars[17].engineCapacity = 3.0;
    inventoryOfCars[17].enginePower = 231;
    inventoryOfCars[17].price = 3500;
    
    inventoryOfCars[18].id = 19;
    strcpy(inventoryOfCars[18].brand, "Audi");
    strcpy(inventoryOfCars[18].model, "A4 B9");
    strcpy(inventoryOfCars[18].class, "Бізнес");
    strcpy(inventoryOfCars[18].body, "Седан");
    strcpy(inventoryOfCars[18].transmission, "Автомат");
    strcpy(inventoryOfCars[18].fuel, "Бензин");
    inventoryOfCars[18].engineCapacity = 2.0;
    inventoryOfCars[18].enginePower = 252;
    inventoryOfCars[18].price = 3450;
    
    inventoryOfCars[19].id = 20;
    strcpy(inventoryOfCars[19].brand, "Honda");
    strcpy(inventoryOfCars[19].model, "Accord X");
    strcpy(inventoryOfCars[19].class, "Бізнес");
    strcpy(inventoryOfCars[19].body, "Седан");
    strcpy(inventoryOfCars[19].transmission, "Автомат");
    strcpy(inventoryOfCars[19].fuel, "Бензин");
    inventoryOfCars[19].engineCapacity = 1.5;
    inventoryOfCars[19].enginePower = 192;
    inventoryOfCars[19].price = 3250;
    
    inventoryOfCars[20].id = 21;
    strcpy(inventoryOfCars[20].brand, "Audi");
    strcpy(inventoryOfCars[20].model, "Q7");
    strcpy(inventoryOfCars[20].class, "Преміум");
    strcpy(inventoryOfCars[20].body, "Позашляховик");
    strcpy(inventoryOfCars[20].transmission, "Автомат");
    strcpy(inventoryOfCars[20].fuel, "Бензин");
    inventoryOfCars[20].engineCapacity = 3.0;
    inventoryOfCars[20].enginePower = 333;
    inventoryOfCars[20].price = 6850;
    
    inventoryOfCars[21].id = 22;
    strcpy(inventoryOfCars[21].brand, "BMW");
    strcpy(inventoryOfCars[21].model, "X5 G05");
    strcpy(inventoryOfCars[21].class, "Преміум");
    strcpy(inventoryOfCars[21].body, "Позашляховик");
    strcpy(inventoryOfCars[21].transmission, "Автомат");
    strcpy(inventoryOfCars[21].fuel, "Дизель");
    inventoryOfCars[21].engineCapacity = 2.0;
    inventoryOfCars[21].enginePower = 231;
    inventoryOfCars[21].price = 6900;
    
    inventoryOfCars[22].id = 23;
    strcpy(inventoryOfCars[22].brand, "Mercedes-Benz");
    strcpy(inventoryOfCars[22].model, "GLE 300 2021");
    strcpy(inventoryOfCars[22].class, "Преміум");
    strcpy(inventoryOfCars[22].body, "Позашляховик");
    strcpy(inventoryOfCars[22].transmission, "Автомат");
    strcpy(inventoryOfCars[22].fuel, "Дизель");
    inventoryOfCars[22].engineCapacity = 2.0;
    inventoryOfCars[22].enginePower = 245;
    inventoryOfCars[22].price = 8000;
    
    inventoryOfCars[23].id = 24;
    strcpy(inventoryOfCars[23].brand, "Lexus");
    strcpy(inventoryOfCars[23].model, "ES Hybrid");
    strcpy(inventoryOfCars[23].class, "Преміум");
    strcpy(inventoryOfCars[23].body, "Седан");
    strcpy(inventoryOfCars[23].transmission, "Автомат");
    strcpy(inventoryOfCars[23].fuel, "Гібрид");
    inventoryOfCars[23].engineCapacity = 2.5;
    inventoryOfCars[23].enginePower = 205;
    inventoryOfCars[23].price = 5750;
    
    inventoryOfCars[24].id = 25;
    strcpy(inventoryOfCars[24].brand, "Audi");
    strcpy(inventoryOfCars[24].model, "A6");
    strcpy(inventoryOfCars[24].class, "Преміум");
    strcpy(inventoryOfCars[24].body, "Седан");
    strcpy(inventoryOfCars[24].transmission, "Автомат");
    strcpy(inventoryOfCars[24].fuel, "Бензин");
    inventoryOfCars[24].engineCapacity = 2.0;
    inventoryOfCars[24].enginePower = 252;
    inventoryOfCars[24].price = 4200;
    
    inventoryOfCars[25].id = 26;
    strcpy(inventoryOfCars[25].brand, "Toyota");
    strcpy(inventoryOfCars[25].model, "Land Cruiser 200");
    strcpy(inventoryOfCars[25].class, "Преміум");
    strcpy(inventoryOfCars[25].body, "Позашляховик");
    strcpy(inventoryOfCars[25].transmission, "Автомат");
    strcpy(inventoryOfCars[25].fuel, "Дизель");
    inventoryOfCars[25].engineCapacity = 4.4;
    inventoryOfCars[25].enginePower = 249;
    inventoryOfCars[25].price = 4200;
    
    inventoryOfCars[26].id = 27;
    strcpy(inventoryOfCars[26].brand, "BMW");
    strcpy(inventoryOfCars[26].model, "530 Hybrid 2019");
    strcpy(inventoryOfCars[26].class, "Преміум");
    strcpy(inventoryOfCars[26].body, "Седан");
    strcpy(inventoryOfCars[26].transmission, "Автомат");
    strcpy(inventoryOfCars[26].fuel, "Гібрид");
    inventoryOfCars[26].engineCapacity = 2.0;
    inventoryOfCars[26].enginePower = 252;
    inventoryOfCars[26].price = 5750;
    
    inventoryOfCars[27].id = 28;
    strcpy(inventoryOfCars[27].brand, "Suzuki");
    strcpy(inventoryOfCars[27].model, "Vitara IV");
    strcpy(inventoryOfCars[27].class, "Позашляховик");
    strcpy(inventoryOfCars[27].body, "Кросовер");
    strcpy(inventoryOfCars[27].transmission, "Автомат");
    strcpy(inventoryOfCars[27].fuel, "Бензин");
    inventoryOfCars[27].engineCapacity = 1.0;
    inventoryOfCars[27].enginePower = 111;
    inventoryOfCars[27].price = 2250;
    
    inventoryOfCars[28].id = 29;
    strcpy(inventoryOfCars[28].brand, "Toyota");
    strcpy(inventoryOfCars[28].model, "Land Cruiser 150");
    strcpy(inventoryOfCars[28].class, "Позашляховик");
    strcpy(inventoryOfCars[28].body, "Позашляховик");
    strcpy(inventoryOfCars[28].transmission, "Автомат");
    strcpy(inventoryOfCars[28].fuel, "Бензин");
    inventoryOfCars[28].engineCapacity = 2.7;
    inventoryOfCars[28].enginePower = 163;
    inventoryOfCars[28].price = 4250;
    
    inventoryOfCars[29].id = 30;
    strcpy(inventoryOfCars[29].brand, "Volkswagen");
    strcpy(inventoryOfCars[29].model, "Touareg");
    strcpy(inventoryOfCars[29].class, "Позашляховик");
    strcpy(inventoryOfCars[29].body, "Позашляховик");
    strcpy(inventoryOfCars[29].transmission, "Автомат");
    strcpy(inventoryOfCars[29].fuel, "Дизель");
    inventoryOfCars[29].engineCapacity = 3.0;
    inventoryOfCars[29].enginePower = 286;
    inventoryOfCars[29].price = 7250;
    
    inventoryOfCars[30].id = 31;
    strcpy(inventoryOfCars[30].brand, "Kia");
    strcpy(inventoryOfCars[30].model, "Sportage 2023");
    strcpy(inventoryOfCars[30].class, "Позашляховик");
    strcpy(inventoryOfCars[30].body, "Кросовер");
    strcpy(inventoryOfCars[30].transmission, "Автомат");
    strcpy(inventoryOfCars[30].fuel, "Бензин");
    inventoryOfCars[30].engineCapacity = 2.0;
    inventoryOfCars[30].enginePower = 156;
    inventoryOfCars[30].price = 3500;
    
    inventoryOfCars[31].id = 32;
    strcpy(inventoryOfCars[31].brand, "Toyota");
    strcpy(inventoryOfCars[31].model, "RAV 4");
    strcpy(inventoryOfCars[31].class, "Позашляховик");
    strcpy(inventoryOfCars[31].body, "Кроссовер");
    strcpy(inventoryOfCars[31].transmission, "Автомат");
    strcpy(inventoryOfCars[31].fuel, "Бензин");
    inventoryOfCars[31].engineCapacity = 2.0;
    inventoryOfCars[31].enginePower = 175;
    inventoryOfCars[31].price = 3000;
    
    inventoryOfCars[32].id = 33;
    strcpy(inventoryOfCars[32].brand, "Hyundai");
    strcpy(inventoryOfCars[32].model, "Tucson 2019");
    strcpy(inventoryOfCars[32].class, "Позашляховик");
    strcpy(inventoryOfCars[32].body, "Позашляховик");
    strcpy(inventoryOfCars[32].transmission, "Автомат");
    strcpy(inventoryOfCars[32].fuel, "Бензин");
    inventoryOfCars[32].engineCapacity = 2.0;
    inventoryOfCars[32].enginePower = 155;
    inventoryOfCars[32].price = 2800;
    
    inventoryOfCars[33].id = 34;
    strcpy(inventoryOfCars[33].brand, "Audi");
    strcpy(inventoryOfCars[33].model, "Q5 2023");
    strcpy(inventoryOfCars[33].class, "Позашляховик");
    strcpy(inventoryOfCars[33].body, "Кроссовер");
    strcpy(inventoryOfCars[33].transmission, "Автомат");
    strcpy(inventoryOfCars[33].fuel, "Бензин");
    inventoryOfCars[33].engineCapacity = 2.0;
    inventoryOfCars[33].enginePower = 249;
    inventoryOfCars[33].price = 5000;
    
    inventoryOfCars[34].id = 35;
    strcpy(inventoryOfCars[34].brand, "Renault");
    strcpy(inventoryOfCars[34].model, "Duster");
    strcpy(inventoryOfCars[34].class, "Позашляховик");
    strcpy(inventoryOfCars[34].body, "Кроссовер");
    strcpy(inventoryOfCars[34].transmission, "Механіка");
    strcpy(inventoryOfCars[34].fuel, "Дизель");
    inventoryOfCars[34].engineCapacity = 1.5;
    inventoryOfCars[34].enginePower = 110;
    inventoryOfCars[34].price = 2100;
    
    inventoryOfCars[35].id = 36;
    strcpy(inventoryOfCars[35].brand, "Lexus");
    strcpy(inventoryOfCars[35].model, "RX 300 2021");
    strcpy(inventoryOfCars[35].class, "Позашляховик");
    strcpy(inventoryOfCars[35].body, "Позашляховик");
    strcpy(inventoryOfCars[35].transmission, "Автомат");
    strcpy(inventoryOfCars[35].fuel, "Бензин");
    inventoryOfCars[35].engineCapacity = 2.0;
    inventoryOfCars[35].enginePower = 238;
    inventoryOfCars[35].price = 6800;
    
    inventoryOfCars[36].id = 37;
    strcpy(inventoryOfCars[36].brand, "Volkswagen");
    strcpy(inventoryOfCars[36].model, "Tiguan");
    strcpy(inventoryOfCars[36].class, "Позашляховик");
    strcpy(inventoryOfCars[36].body, "Кроссовер");
    strcpy(inventoryOfCars[36].transmission, "Автомат");
    strcpy(inventoryOfCars[36].fuel, "Бензин");
    inventoryOfCars[36].engineCapacity = 2.0;
    inventoryOfCars[36].enginePower = 200;
    inventoryOfCars[36].price = 3750;
    
    inventoryOfCars[37].id = 38;
    strcpy(inventoryOfCars[37].brand, "Mercedes-Benz");
    strcpy(inventoryOfCars[37].model, "GLC300");
    strcpy(inventoryOfCars[37].class, "Позашляховик");
    strcpy(inventoryOfCars[37].body, "Кроссовер");
    strcpy(inventoryOfCars[37].transmission, "Автомат");
    strcpy(inventoryOfCars[37].fuel, "Бензин");
    inventoryOfCars[37].engineCapacity = 2.0;
    inventoryOfCars[37].enginePower = 244;
    inventoryOfCars[37].price = 7250;
    
    inventoryOfCars[38].id = 39;
    strcpy(inventoryOfCars[38].brand, "Nissan");
    strcpy(inventoryOfCars[38].model, "Juke");
    strcpy(inventoryOfCars[38].class, "Позашляховик");
    strcpy(inventoryOfCars[38].body, "Кросовер");
    strcpy(inventoryOfCars[38].transmission, "Автомат");
    strcpy(inventoryOfCars[38].fuel, "Бензин");
    inventoryOfCars[38].engineCapacity = 1.6;
    inventoryOfCars[38].enginePower = 117;
    inventoryOfCars[38].price = 1850;
    
    inventoryOfCars[39].id = 40;
    strcpy(inventoryOfCars[39].brand, "Mazda");
    strcpy(inventoryOfCars[39].model, "CX5");
    strcpy(inventoryOfCars[39].class, "Позашляховик");
    strcpy(inventoryOfCars[39].body, "Кроссовер");
    strcpy(inventoryOfCars[39].transmission, "Автомат");
    strcpy(inventoryOfCars[39].fuel, "Бензин");
    inventoryOfCars[39].engineCapacity = 2.0;
    inventoryOfCars[39].enginePower = 160;
    inventoryOfCars[39].price = 3500;
    
    inventoryOfCars[40].id = 41;
    strcpy(inventoryOfCars[40].brand, "Volkswagen");
    strcpy(inventoryOfCars[40].model, "T6 MULTIVAN");
    strcpy(inventoryOfCars[40].class, "Мінівен");
    strcpy(inventoryOfCars[40].body, "Мінівен");
    strcpy(inventoryOfCars[40].transmission, "Автомат");
    strcpy(inventoryOfCars[40].fuel, "Дизель");
    inventoryOfCars[40].engineCapacity = 2.0;
    inventoryOfCars[40].enginePower = 140;
    inventoryOfCars[40].price = 5800;
    
    inventoryOfCars[41].id = 42;
    strcpy(inventoryOfCars[41].brand, "Renault");
    strcpy(inventoryOfCars[41].model, "Trafic");
    strcpy(inventoryOfCars[41].class, "Мінівен");
    strcpy(inventoryOfCars[41].body, "Мінівен");
    strcpy(inventoryOfCars[41].transmission, "Механіка");
    strcpy(inventoryOfCars[14].fuel, "Дизель");
    inventoryOfCars[41].engineCapacity = 1.9;
    inventoryOfCars[41].enginePower = 100;
    inventoryOfCars[41].price = 3200;
    
    
    inventoryOfCars[42].id = 43;
    strcpy(inventoryOfCars[42].brand, "Hyundai");
    strcpy(inventoryOfCars[42].model, "H1");
    strcpy(inventoryOfCars[42].class, "Мінівен");
    strcpy(inventoryOfCars[42].body, "Мінівен");
    strcpy(inventoryOfCars[42].transmission, "Автомат");
    strcpy(inventoryOfCars[42].fuel, "Дизель");
    inventoryOfCars[42].engineCapacity = 2.5;
    inventoryOfCars[42].enginePower = 170;
    inventoryOfCars[42].price = 4000;
    
    inventoryOfCars[43].id = 44;
    strcpy(inventoryOfCars[43].brand, "Volkswagen");
    strcpy(inventoryOfCars[43].model, "T5");
    strcpy(inventoryOfCars[43].class, "Комерційний");
    strcpy(inventoryOfCars[43].body, "Мінівен");
    strcpy(inventoryOfCars[43].transmission, "Механіка");
    strcpy(inventoryOfCars[43].fuel, "Дизель");
    inventoryOfCars[43].engineCapacity = 2.5;
    inventoryOfCars[43].enginePower = 130;
    inventoryOfCars[43].price = 2800;
    
    inventoryOfCars[44].id = 45;
    strcpy(inventoryOfCars[44].brand, "Tesla");
    strcpy(inventoryOfCars[44].model, "Model 3");
    strcpy(inventoryOfCars[44].class, "Електромобіль");
    strcpy(inventoryOfCars[44].body, "Седан");
    strcpy(inventoryOfCars[44].transmission, "Автомат");
    strcpy(inventoryOfCars[44].fuel, "Електро");
    inventoryOfCars[44].engineCapacity = 70;
    inventoryOfCars[44].enginePower = 224;
    inventoryOfCars[44].price = 4500;
    
    inventoryOfCars[45].id = 46;
    strcpy(inventoryOfCars[45].brand, "Tesla");
    strcpy(inventoryOfCars[45].model, "Model X");
    strcpy(inventoryOfCars[45].class, "Електромобіль");
    strcpy(inventoryOfCars[45].body, "Кроссовер");
    strcpy(inventoryOfCars[45].transmission, "Автомат");
    strcpy(inventoryOfCars[45].fuel, "Електро");
    inventoryOfCars[45].engineCapacity = 75;
    inventoryOfCars[45].enginePower = 329;
    inventoryOfCars[45].price = 15000;
    
    inventoryOfCars[46].id = 47;
    strcpy(inventoryOfCars[46].brand, "Nissan");
    strcpy(inventoryOfCars[46].model, "Leaf 2");
    strcpy(inventoryOfCars[46].class, "Електромобіль");
    strcpy(inventoryOfCars[46].body, "Хетчбек");
    strcpy(inventoryOfCars[46].transmission, "Автомат");
    strcpy(inventoryOfCars[46].fuel, "Електро");
    inventoryOfCars[46].engineCapacity = 40;
    inventoryOfCars[46].enginePower = 150;
    inventoryOfCars[46].price = 2100;
    
    inventoryOfCars[47].id = 48;
    strcpy(inventoryOfCars[47].brand, "Ford");
    strcpy(inventoryOfCars[47].model, "F-150");
    strcpy(inventoryOfCars[47].class, "Пікап");
    strcpy(inventoryOfCars[47].body, "Пікап");
    strcpy(inventoryOfCars[47].transmission, "Автомат");
    strcpy(inventoryOfCars[47].fuel, "Бензин");
    inventoryOfCars[47].engineCapacity = 2.7;
    inventoryOfCars[47].enginePower = 325;
    inventoryOfCars[47].price = 5000;
    
    inventoryOfCars[48].id = 49;
    strcpy(inventoryOfCars[48].brand, "Mini-Cooper");
    strcpy(inventoryOfCars[48].model, "Cabrio");
    strcpy(inventoryOfCars[48].class, "Кабріолет");
    strcpy(inventoryOfCars[48].body, "Кабріолет");
    strcpy(inventoryOfCars[48].transmission, "Автомат");
    strcpy(inventoryOfCars[48].fuel, "Бензин");
    inventoryOfCars[48].engineCapacity = 1.5;
    inventoryOfCars[48].enginePower = 286;
    inventoryOfCars[48].price = 4850;
    
    inventoryOfCars[49].id = 50;
    strcpy(inventoryOfCars[49].brand, "Dodge");
    strcpy(inventoryOfCars[49].model, "Challenger");
    strcpy(inventoryOfCars[49].class, "Купе");
    strcpy(inventoryOfCars[49].body, "Купе");
    strcpy(inventoryOfCars[49].transmission, "Автомат");
    strcpy(inventoryOfCars[49].fuel, "Бензин");
    inventoryOfCars[49].engineCapacity = 3.6;
    inventoryOfCars[49].enginePower = 305;
    inventoryOfCars[49].price = 5100;

    return 0;
}
