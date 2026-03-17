#include <stdio.h>
/*
Заменить  в  строке  все восьмеричные целые константы на символы с соответствующими кодами,
(например,  xxx101yyy102zzz на xxxAyyyBzzz)

src         - входная строка
dst         - выходной массив
dst_size    - размер выходного массива
p           - =1 если произошло переполнение
*/

int function(const char* src, char* dst, int dst_size, int* p)
{
    int i = 0;      // индекс src
    int j = 0;      // индекс dst
    *p = 0;

    while (src[i] != '\0')
    {
        if (src[i] >= '0' && src[i] <= '7')
        {
            int value = 0;

            while (src[i] >= '0' && src[i] <= '7')
            {
                value = value * 8 + (src[i] - '0');
                i++;
            }

            if (j >= dst_size - 1) // проверка переполнения 
            {
                *p = 1;
                return j;
            }

            dst[j++] = (char)value;
        }
        else
        {
            if (j >= dst_size - 1)
            {
                *p = 1;
                return j;
            }

            dst[j++] = src[i++];
        }
    }

    dst[j] = '\0';
    return j;
}

int main(){
    // обычная замена из примера
    {
        const char src[] = "xxx101yyy102zzz";
        char dst[100];
        int p;

        function(src, dst, 100, &p);

        printf("Test 1:\n");
        printf("src: %s\n", src);
        printf("dst: %s\n", dst);
        printf("p: %d\n\n", p);
    }

    // нет чисел
    {
        const char src[] = "DUHGIUdfd";
        char dst[100];
        int p;

        function(src, dst, 100, &p);

        printf("Test 2:\n");
        printf("src: %s\n", src);
        printf("dst: %s\n", dst);
        printf("p: %d\n\n", p);
    }

    // переполнение
    {
        const char src[] = "101102103104105106107110"; // будет много замен
        char dst[1];  // маленький буфер 
        int p;

        function(src, dst, 1, &p);

        printf("Test 3:\n");
        printf("src: %s\n", src);
        printf("dst: %s\n", dst);
        printf("p: %d\n", p);

        if (p)
            printf("overflow!\n");
    }

    return 0;
}
