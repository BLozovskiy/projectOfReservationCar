#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int id;
    char model[100];
    char brand[20];
    char class[100];
    char body[100];
    char trasmissin[100];
    char fuel[100];
    char engine[100];
    float price, engineCapacity, enginePower;
} Car;

void listOfCars(Car* inventoryOfCars, int countCars) {
    printf("Список продуктів:\n");
    for (int i = 0; i < countCars; i++) {
        printf("ID: %d, Бренд: %s, Модель: %s, Клас: %s, Кузов: %s, Трансмісія: %s, Паливо: %s, Двигун: %f л. %f к. с., Ціна: %.2f грн\n",
            inventoryOfCars[i].id, inventoryOfCars[i].brand, inventoryOfCars[i].model, inventoryOfCars[i].class,
            inventoryOfCars[i].body, inventoryOfCars[i].transmission, inventoryOfCars[i].fuel, inventoryOfCars[i].engineCapacity, inventoryOfCars[i].enginePower,
            inventoryOfCars[i].price);
    }
}

void calculatingRentalPrice(Car* inventoryOfCars, int countCars) {
    int productId, days;
    float totalPrice = 0;

    printf("Введіть ID автомобіля для оренди: ");
    scanf("%d", &productId);

    bool carFound = false;
    for (int i = 0; i < countCars; i++) {
        if (inventoryOfCars[i].id == productId) {
            carFound = true;

            printf("Введіть кількість днів для оренди: ");
            scanf("%d", &days);

            totalPrice = inventoryOfCars[i].price * days;
            break;
        }
    }

    if (!carFound) {
        printf("Помилка: Автомобіль з ідентифікатором %d не знайдено.\n", productId);
    } else {
        printf("Загальна ціна оренди: %.2f грн\n", totalPrice);
    }
}

int main()
{
    printf("Hello World");

    return 0;
}
