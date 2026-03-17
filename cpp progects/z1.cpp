#include <stdio.h>

/*
Заменяет в строке все константы вида:
[основание][цифры числа]
основание < 10
все цифры числа < основания

src         - входная строка
dst         - выходной массив
dst_size    - размер выходного массива
p           - =1 если произошло переполнение
*/

int function(const char* src, char* dst, int dst_size, int* p)
{
    int i = 0;   // индекс src
    int j = 0;   // индекс dst
    *p = 0;

    while (src[i] != '\0')
    {
        if (src[i] >= '1' && src[i] <= '9') // проверяем цифра ли основание 
        {
            int base = src[i] - '0';
            int value = 0;
            i++; 

            while (src[i] >= '0' && src[i] <= '9' && (src[i] - '0') < base) // считаем цифры, пока они < основания
            {
                value = value * base + (src[i] - '0');
                i++;
            }

            if (j >= dst_size - 1) // проверка переполнения выходного массива
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

            dst[j++] = src[i++]; // если не цифра, то копируем 
        }
    }
    dst[j] = '\0';
    return j;
}


int main(){
    // разные основания
    {
        const char src[] = "xxx8101yyy2101zzz";
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
        const char src[] = "8101810181018101";
        char dst[1];   // маленький буфер
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
