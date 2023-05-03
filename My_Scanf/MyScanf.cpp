#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void myScanf(const char* format, void* num1, void* num2, void* str, void* ch)
{
    char input[1024];
    fgets(input, 1024, stdin);

    char* token = strtok(input, "\t ");

    while (token != NULL && *format != '\0')
    {
        switch (*format)
        {
        case '%':
        {
            ++format;
            switch (*format)
            {
            case 'd':
            {
                int* num = (int*)num1;
                *num = atoi(token);
                num1 = (char*)num1 + sizeof(int);
                break;
            }
            case 'f':
            {
                float* num = (float*)num2;
                *num = atof(token);
                num2 = (char*)num2 + sizeof(float);
                break;
            }
            case 's':
            {
                char** strPtr = (char**)str;
                strcpy(*strPtr, token);
                str = (char*)str + sizeof(char*);
                break;
            }
            case 'c':
            {
                char* chPtr = (char*)ch;
                *chPtr = *token;
                ch = (char*)ch + sizeof(char);
                break;
            }
            default:
                break;
            }
            break;
        }
        default:
            break;
        }
        token = strtok(NULL, "\t ");
        ++format;
    }
}

int main()
{
    int num1;
    float num2;
    char str[100];
    char ch;

    myScanf("%d %f %s %c", &num1, &num2, str, &ch);

    printf("%d\n", num1);
    printf("%f\n", num2);
    printf("%s\n", str);
    printf("%c\n", ch);

    return 0;
}
