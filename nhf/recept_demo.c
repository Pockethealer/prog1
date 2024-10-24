#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_UNIT_LENGTH 20
#define MAX_INGREDIENTS 50
#define MAX_INSTRUCTION_LENGTH 1000
#define MAX_LINE_LENGTH 1024

// Structure for an ingredient
typedef struct {
    char name[MAX_NAME_LENGTH];
    double amount;
    char unit[MAX_UNIT_LENGTH];
} Ingredient;

// Structure for a complete recipe
typedef struct {
    char name[MAX_NAME_LENGTH];
    Ingredient ingredients[MAX_INGREDIENTS];
    int ingredient_count;
    char instruction[MAX_INSTRUCTION_LENGTH];
} Recipe;

// Function to trim whitespace from strings
void trim(char* str) {
    char* start = str;
    while (*start == ' ' || *start == '\t') start++;

    if (str != start) {
        memmove(str, start, strlen(start) + 1);
    }

    char* end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        *end = '\0';
        end--;
    }
}

// Function to read a recipe from a file
Recipe* read_recipe(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    Recipe* recipe = malloc(sizeof(Recipe));
    if (!recipe) {
        fclose(file);
        return NULL;
    }

    recipe->ingredient_count = 0;
    char line[MAX_LINE_LENGTH];
    int section = 0;  // 0 = name, 1 = ingredients, 2 = instruction

    while (fgets(line, sizeof(line), file)) {
        trim(line);

        // Skip empty lines
        if (strlen(line) == 0) continue;

        // Check for section markers
        if (strcmp(line, "[NAME]") == 0) {
            section = 0;
            continue;
        }
        if (strcmp(line, "[INGREDIENTS]") == 0) {
            section = 1;
            continue;
        }
        if (strcmp(line, "[INSTRUCTION]") == 0) {
            section = 2;
            continue;
        }

        // Process each section
        switch (section) {
        case 0:  // Name
            strncpy(recipe->name, line, MAX_NAME_LENGTH - 1);
            recipe->name[MAX_NAME_LENGTH - 1] = '\0';
            break;

        case 1:  // Ingredients
            if (recipe->ingredient_count < MAX_INGREDIENTS) {
                Ingredient* ing = &recipe->ingredients[recipe->ingredient_count];
                // Parse ingredient line (format: amount unit name)
                char unit[MAX_UNIT_LENGTH];
                char name[MAX_NAME_LENGTH];
                if (sscanf(line, "%lf %s %[^\n]", &ing->amount, unit, name) == 3) {
                    strncpy(ing->unit, unit, MAX_UNIT_LENGTH - 1);
                    strncpy(ing->name, name, MAX_NAME_LENGTH - 1);
                    recipe->ingredient_count++;
                }
            }
            break;

        case 2:  // Instruction
            strncpy(recipe->instruction, line, MAX_INSTRUCTION_LENGTH - 1);
            recipe->instruction[MAX_INSTRUCTION_LENGTH - 1] = '\0';
            break;
        }
    }

    fclose(file);
    return recipe;
}

// Function to save a recipe to a file
void save_recipe(const Recipe* recipe, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }

    // Write name
    fprintf(file, "[NAME]\n%s\n\n", recipe->name);

    // Write ingredients
    fprintf(file, "[INGREDIENTS]\n");
    for (int i = 0; i < recipe->ingredient_count; i++) {
        fprintf(file, "%.2f %s %s\n",
            recipe->ingredients[i].amount,
            recipe->ingredients[i].unit,
            recipe->ingredients[i].name);
    }
    fprintf(file, "\n");

    // Write instruction
    fprintf(file, "[INSTRUCTION]\n%s\n", recipe->instruction);

    fclose(file);
}

// Function to print a recipe
void print_recipe(const Recipe* recipe) {
    printf("\nRecipe: %s\n", recipe->name);
    printf("\nIngredients:\n");
    for (int i = 0; i < recipe->ingredient_count; i++) {
        printf("- %.2f %s %s\n",
            recipe->ingredients[i].amount,
            recipe->ingredients[i].unit,
            recipe->ingredients[i].name);
    }
    printf("\nInstructions:\n%s\n", recipe->instruction);
}

// Example usage
int main() {
    // Example of creating and saving a recipe
    Recipe pancakes = {
        .name = "Classic Pancakes",
        .ingredient_count = 6,
        .ingredients = {
            {.amount = 1.5, .unit = "cups", .name = "all-purpose flour"},
            {.amount = 3.5, .unit = "tsp", .name = "baking powder"},
            {.amount = 0.25, .unit = "tsp", .name = "salt"},
            {.amount = 1, .unit = "tbsp", .name = "sugar"},
            {.amount = 1.25, .unit = "cups", .name = "milk"},
            {.amount = 1, .unit = "piece", .name = "egg"}
        },
        .instruction = "Mix dry ingredients. Add milk and egg. Cook on hot griddle until bubbles form, then flip."
    };

    // Save the recipe
    save_recipe(&pancakes, "pancakes.txt");

    // Read and print the recipe
    Recipe* loaded_recipe = read_recipe("pancakes.txt");
    if (loaded_recipe) {
        print_recipe(loaded_recipe);
        free(loaded_recipe);
    }

    return 0;
}