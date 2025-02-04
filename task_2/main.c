#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define DEPOSIT_CAPACITY 100

// Shared resources
int flour_deposit_A = 0, flour_deposit_B = 0, flour_deposit_C = 0;
int egg_deposit_A = 0, egg_deposit_B = 0, egg_deposit_C = 0;
int baguette_deposit = 0;
int petit_pain_deposit1 = 0, petit_pain_deposit2 = 0;

// Production rates
int flour_rate = 5; // units per second
int egg_rate = 10;  // units per second

// Bakery consumption rates
int baguette_produced = 0, petit_pain_produced = 0;
int customer_consumption = 0, restaurant_consumption = 0;

// Factory threads
void *flour_factory(void *arg)
{
    while (1)
    {
        if (flour_deposit_A < DEPOSIT_CAPACITY)
        {
            flour_deposit_A += flour_rate;
            printf("Flour Factory: Added %d flour to Deposit A. Current: %d\n", flour_rate, flour_deposit_A);
        }
        else if (flour_deposit_C < DEPOSIT_CAPACITY)
        {
            flour_deposit_C += flour_rate;
            printf("Flour Factory: Added %d flour to Deposit C. Current: %d\n", flour_rate, flour_deposit_C);
        }
        else if (flour_deposit_B < DEPOSIT_CAPACITY)
        {
            flour_deposit_B += flour_rate;
            printf("Flour Factory: Added %d flour to Deposit B. Current: %d\n", flour_rate, flour_deposit_B);
        }
        usleep(1000000); // Simulate production time
    }
}

void *egg_factory(void *arg)
{
    while (1)
    {
        if (egg_deposit_A < DEPOSIT_CAPACITY)
        {
            egg_deposit_A += egg_rate;
            printf("Egg Factory: Added %d eggs to Deposit A. Current: %d\n", egg_rate, egg_deposit_A);
        }
        else if (egg_deposit_C < DEPOSIT_CAPACITY)
        {
            egg_deposit_C += egg_rate;
            printf("Egg Factory: Added %d eggs to Deposit C. Current: %d\n", egg_rate, egg_deposit_C);
        }
        else if (egg_deposit_B < DEPOSIT_CAPACITY)
        {
            egg_deposit_B += egg_rate;
            printf("Egg Factory: Added %d eggs to Deposit B. Current: %d\n", egg_rate, egg_deposit_B);
        }
        usleep(1000000); // Simulate production time
    }
}

// Bakery threads
void *bakery_A(void *arg)
{
    while (1)
    {
        if (flour_deposit_A >= 1 && egg_deposit_A >= 2)
        {
            flour_deposit_A--;
            egg_deposit_A -= 2;
            baguette_deposit += 5;
            baguette_produced += 5;
            printf("Bakery A: Produced 5 baguettes. Total baguettes produced: %d\n", baguette_produced);
        }
        else if (flour_deposit_C >= 1 && egg_deposit_C >= 2)
        {
            flour_deposit_C--;
            egg_deposit_C -= 2;
            baguette_deposit += 5;
            baguette_produced += 5;
            printf("Bakery A: Used Deposit C to produce 5 baguettes. Total baguettes produced: %d\n", baguette_produced);
        }
        usleep(1000000); // Simulate production time
    }
}

void *bakery_B(void *arg)
{
    while (1)
    {
        if (flour_deposit_B >= 1 && egg_deposit_B >= 2)
        {
            flour_deposit_B--;
            egg_deposit_B -= 2;
            petit_pain_deposit1 += 2;
            petit_pain_deposit2 += 2;
            petit_pain_produced += 4;
            printf("Bakery B: Produced 4 Petit-pain. Total Petit-pain produced: %d\n", petit_pain_produced);
        }
        else if (flour_deposit_C >= 1 && egg_deposit_C >= 2)
        {
            flour_deposit_C--;
            egg_deposit_C -= 2;
            petit_pain_deposit1 += 2;
            petit_pain_deposit2 += 2;
            petit_pain_produced += 4;
            printf("Bakery B: Used Deposit C to produce 4 Petit-pain. Total Petit-pain produced: %d\n", petit_pain_produced);
        }
        usleep(1000000); // Simulate production time
    }
}

// Consumer threads
void *customer(void *arg)
{
    while (1)
    {
        if (baguette_deposit > 0)
        {
            baguette_deposit--;
            customer_consumption++;
            printf("Customer: Consumed 1 baguette. Total consumed: %d\n", customer_consumption);
        }
        if (petit_pain_deposit1 > 1)
        {
            petit_pain_deposit1 -= 2;
            customer_consumption += 2;
            printf("Customer: Consumed 2 petit-pain(s). Total consumed: %d\n", customer_consumption);
        }
        usleep(1000000); // Simulate consumption time
    }
}

void *restaurant(void *arg)
{
    while (1)
    {
        if (petit_pain_deposit2 >= 4)
        {
            petit_pain_deposit2 -= 4;
            restaurant_consumption += 4;
            printf("Restaurant: Consumed 4 Petit-pain(s). Total consumed: %d\n", restaurant_consumption);
        }
        usleep(1000000); // Simulate consumption time
    }
}

// Summary function to periodically display the current state
void *display_summary(void *arg)
{
    while (1)
    {
        printf("\n=============== System Summary ===============\n");
        printf("Flour Deposits: A=%d, B=%d, C=%d\n", flour_deposit_A, flour_deposit_B, flour_deposit_C);
        printf("Egg Deposits: A=%d, B=%d, C=%d\n", egg_deposit_A, egg_deposit_B, egg_deposit_C);
        printf("Baguette Deposit: %d\n", baguette_deposit);
        printf("Petit-pain Deposits: 1=%d, 2=%d\n", petit_pain_deposit1, petit_pain_deposit2);
        printf("Total Baguettes Produced: %d, Consumed: %d\n", baguette_produced, customer_consumption);
        printf("Total Petit-pain Produced: %d, Consumed: %d\n", petit_pain_produced, restaurant_consumption);
        printf("=============================================\n");
        sleep(5); // Display every 5 seconds
    }
}

// Main function
int main()
{
    pthread_t threads[12];

    // Create factory threads
    pthread_create(&threads[0], NULL, flour_factory, NULL);
    pthread_create(&threads[1], NULL, egg_factory, NULL);

    // Create bakery threads
    pthread_create(&threads[2], NULL, bakery_A, NULL);
    pthread_create(&threads[3], NULL, bakery_B, NULL);

    // Create consumer threads
    for (int i = 4; i < 9; i++)
    {
        pthread_create(&threads[i], NULL, customer, NULL);
    }
    pthread_create(&threads[9], NULL, restaurant, NULL);
    pthread_create(&threads[10], NULL, restaurant, NULL);

    // Create summary thread
    pthread_create(&threads[11], NULL, display_summary, NULL);

    // Join threads (optional in this case, as threads run indefinitely)
    for (int i = 0; i < 12; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
