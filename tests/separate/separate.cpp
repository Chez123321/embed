#include "embed.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    FILE *file1 = fopen("text1.txt", "r");
    fseek(file1, 0, SEEK_END);
    long file1_size = ftell(file1);
    rewind(file1);
    
    char *text1 = (char*)calloc(file1_size + 1, sizeof(char));
    fread(text1, file1_size, 1, file1);
    fclose(file1);

    size_t embedded_text1_size = embed::get("text1.txt").size();
    char *embedded_text1 = (char*)malloc(embedded_text1_size + 1);
    memcpy(embedded_text1, embed::get("text1.txt").data(), embedded_text1_size);
    embedded_text1[embedded_text1_size] = '\0';

    FILE *file2 = fopen("text2.txt", "r");
    fseek(file2, 0, SEEK_END);
    long file2_size = ftell(file2);
    rewind(file2);

    char *text2 = (char*)calloc(file2_size + 1, sizeof(char));
    fread(text2, file2_size, 1, file2);
    fclose(file2);

    size_t embedded_text2_size = embed::get("text2.txt").size();
    char *embedded_text2 = (char*)malloc(embedded_text2_size + 1);
    memcpy(embedded_text2, embed::get("text2.txt").data(), embedded_text2_size);
    embedded_text2[embedded_text2_size] = '\0';

    printf("Text 1: %s\n", text1);
    printf("Embedded Text 1: %s\n", embedded_text1);
    printf("Text 2: %s\n", text2);
    printf("Embedded Text 2: %s\n", embedded_text2);

    return !(strcmp(text1, embedded_text1) == 0 && strcmp(text2, embedded_text2) == 0);
}