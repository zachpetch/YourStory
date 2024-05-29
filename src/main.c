#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

char *getInput(const char *prompt, ...) {

    va_list args;
    char formatted_prompt[1024];
    va_start(args, prompt);
    vsnprintf(formatted_prompt, sizeof(formatted_prompt), prompt, args);
    va_end(args);

    printf("%s\n> ", formatted_prompt);
    char *input = NULL;
    size_t len = 0;
    ssize_t read = getline(&input, &len, stdin);

    if (read == -1) {
        perror("I did not understand. Sorry.");
        exit(EXIT_FAILURE);
    }

    input[strcspn(input, "\n")] = '\0';

    return input;
}

int main() {
    int sleeper = 500000;

    printf("Welcome to your story!\n");

    char *name = getInput("Name your first character.");
    printf("This will be a story about %s.\n", name);

    char *place = getInput("Where is %s from?", name);
    printf("Long ago, in the land of %s, there lived a young ...\n", place);

    usleep(sleeper);

    printf("Hmm...\n");

    usleep(sleeper);

    char *species = getInput("What kind of being or creature is %s?", name);

    // Make lower case
    for (int i = 0; species[i]; i++) {
        species[i] = tolower(species[i]);
    }

    // Remove any leading "a " (so "a fish" becomes "fish")
    if (strncmp(species, "a ", 2) == 0) {
        memmove(species, species + 2, strlen(species) - 1);
    }

    // Remove trailing periods
    size_t length = strlen(species);
    while (length > 0 && (species[length - 1] == '.')) {
        species[length - 1] = '\0'; // Replace with null terminator
        length--;
    }

    printf("Long ago, in the land of %s, there lived a young %s named %s.\n", place, species, name);

    usleep(sleeper);

    printf("Looking good so far.\n");

    usleep(sleeper);

    char *food = getInput("Last question. What was the last thing you ate?");

    char prompt[2048];
    snprintf(prompt, sizeof(prompt), "ollama run llama3 Write a very short story that starts with \"Long ago, in the land of %s, there lived a young %s named %s.\" At some point in the story, there should be a character made of %s. Do not include any introduction. Just return the story.", place, species, name, food);

    int result = system(prompt);

    if (result != 0) {
        printf("There was a problem creating your story.");
    }

    return 0;
}
