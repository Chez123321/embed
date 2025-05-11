#include "embed.hpp"
#include <cstdio>
#include <cstring>

int main() {
    FILE *file = fopen("text.txt", "r");
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);
    
    char *text = (char*)calloc(fsize + 1, sizeof(char));
    fread(text, fsize, 1, file);
    fclose(file);

    size_t embedded_text_size = embed::get("text.txt").size();
    char *embedded_text = (char*)malloc(embedded_text_size + 1);
    memcpy(embedded_text, embed::get("text.txt").data(), embedded_text_size);
    embedded_text[embedded_text_size] = '\0';

    printf("Text: %s\n", text);
    printf("Embedded Text: %s\n", embedded_text);

    return strcmp(text, embedded_text);
}