#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <locale.h>

int main(int argc, char** argv) 
{
    setlocale(LC_ALL, "Russian");
    char buff[255];
    int fp = open("./os09_012.txt", O_RDONLY);

    long offset, lpos;

    if (fp < 0)
        return EXIT_FAILURE;

    offset = 5L;
    lpos = lseek(fp, offset, SEEK_SET);
    printf("Текущая позиция=%ld\n", lpos);

    offset = 10L;
    lpos = lseek(fp, offset, SEEK_SET);
    printf("Текущая позиция=%ld\n", lpos);

    offset = 20L;
    lpos = lseek(fp, offset, SEEK_CUR);
    printf("Текущая позиция=%ld\n", lpos);

    ssize_t bytesRead = read(fp, buff, sizeof(buff));
    if (bytesRead == -1) {
        perror("Ошибка при чтении файла");
        close(fp);
        return EXIT_FAILURE;
    }
    write(STDOUT_FILENO, buff, bytesRead);

    offset = 20L;
    lpos = lseek(fp, offset, SEEK_END);
    printf("\nТекущая позиция=%ld\n", lpos);

    close(fp);

    return EXIT_SUCCESS;
}
