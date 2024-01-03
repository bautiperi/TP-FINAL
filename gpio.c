#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gpio.h"

void ini_leds(void)
{
    const int arr[8] = {17, 4, 18, 23, 24, 25, 22, 27};
    int i;

    for (i = 0; i < 8; i++)
    {
        // EXPORT
        FILE *handle_export;
        int nWritten;
        if ((handle_export = fopen("/sys/class/gpio/export", "w")) == NULL)
        {
            printf("Cannot open EXPORT File. Try again later.\n");
            exit(1);
        }
        nWritten = fprintf(handle_export, "%d", arr[i]);
        if (nWritten == -1)
        {
            printf("Cannot EXPORT PIN . Try again later.\n");
            exit(1);
        }
        else
            printf("EXPORT File opened succesfully \n");
        fclose(handle_export);
        usleep(5e5);

        // DIRECTION
        FILE *handle_direction;
        char str1[40];
        char *str = str1;
        sprintf(str, "/sys/class/gpio/gpio%d/direction", arr[i]);
        if ((handle_direction = fopen(str, "w")) == NULL)
        {
            printf("Cannot open DIRECTION File");
            exit(1);
        }

        if ((nWritten = fputs("out", handle_direction)) == -1)
        {
            printf("Cannot open DIRECTION pin. Try again later.\n");
            exit(1);
        }
        else
        {
            printf("DIRECTION File for PIN opened succesfully\n");
        }
        fclose(handle_direction);

        // SET PIN
        FILE *handle;
        char str2[40];
        char *pun = str2;
        sprintf(pun, "/sys/class/gpio/gpio%d/direction", arr[i]);
        if ((handle = fopen(pun, "w")) == NULL)
        {
            printf("Cannot open device. Try again later.\n");
            exit(1);
        }
        else
        {
            printf("Device successfully opened\n");
        }
        if (fputc('0', handle) == -1) // Set pin low
        {
            printf("Clr_Pin: Cannot write to file. Try again later.\n");
            exit(1);
        }
        else
            printf("Write to file %s successfully done.\n", pun);
        fclose(handle);
    }
}

void encender_led(int num)
{
    const int arr[8] = {17, 4, 18, 23, 24, 25, 22, 27};
    FILE *handle;
    char stre[40];
    char *pun = stre;
    sprintf(pun, "/sys/class/gpio/gpio%d/value", arr[num]);
    if ((handle = fopen(pun, "w")) == NULL)
    {
        printf("Cannot open device. Try again later.\n");
        exit(1);
    }
    else
    {
        printf("Device successfully opened\n");
    }
    if (fputc('1', handle) == -1) // Set pin low
    {
        printf("Clr_Pin: Cannot write to file. Try again later.\n");
        exit(1);
    }
    else
        printf("Write to file %s successfully done.\n", pun);
    fclose(handle);
}

void apagar_led(int num)
{
    const int arr[8] = {17, 4, 18, 23, 24, 25, 22, 27};
    FILE *handle;
    char stra[40];
    char *pun = stra;
    sprintf(pun, "/sys/class/gpio/gpio%d/value", arr[num]);
    if ((handle = fopen(pun, "w")) == NULL)
    {
        printf("Cannot open device. Try again later.\n");
        exit(1);
    }
    else
    {
        printf("Device successfully opened\n");
    }
    if (fputc('0', handle) == -1) // Set pin low
    {
        printf("Clr_Pin: Cannot write to file. Try again later.\n");
        exit(1);
    }
    else
        printf("Write to file %s successfully done.\n", pun);
    fclose(handle);
}