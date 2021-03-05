#include <stdlib.h>
#include <stdio.h>

#define MEMORY_LIMIT 100

int main(int argc, char** argv) {
    
    /* Check if the user specified a filename*/
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");

        /* Check if the file exists and is readable*/
        if (file) {

            /* Create the memory */
            char memory[MEMORY_LIMIT + 1] = {0};
            int memory_pointer = 0;

            /* Get the program source */
            fseek(file, 0L, SEEK_END);
            int program_size = ftell(file);
            fseek(file, 0L, SEEK_SET);
            char* program = (char*)calloc(program_size + 1, sizeof(char));
            fread(program, sizeof(char), program_size, file);
            fclose(file);
            
            /* Interpret program */
            int program_pointer = 0;
            int program_loop = 0;

            while (program_pointer < program_size) {
                switch (program[program_pointer]) {
                    case '>':
                        memory_pointer++;

                        if (memory_pointer > MEMORY_LIMIT) {
                            memory_pointer = 0;
                        }
                        break;
                    case '<':
                        memory_pointer--;

                        if (memory_pointer < 0) {
                            memory_pointer = MEMORY_LIMIT;
                        }
                        break;
                    case '+':
                        memory[memory_pointer]++;
                        break;
                    case '-':
                        memory[memory_pointer]--;
                        break;
                    case '.':
                        printf("%c", memory[memory_pointer]);
                        break;
                    case ',':
                        memory[memory_pointer] = getchar();
                        break;
                    case '[':
                        if (!memory[memory_pointer]) {
                            program_loop = 1;
                        
                            while (program_pointer < program_size && program_loop) {
                                program_pointer++;

                                if (program[program_pointer] == '[') {
                                    program_loop++;
                                } else if (program[program_pointer] == ']') {
                                    program_loop--;
                                }
                            }
                        }
                        break;
                    case ']':
                        if (memory[memory_pointer]) {
                            program_loop = 1;

                            while (program_pointer > 0 && program_loop) {
                                program_pointer--;

                                if (program[program_pointer] == '[') {
                                    program_loop--;
                                } else if (program[program_pointer] == ']') {
                                    program_loop++;
                                }
                            }
                        }
                        break;
                }
                program_pointer++;
            }
            free(program);
        } else {
            printf("Error, the specified file could not be read\n");
        }
    } else {
        printf("Error, no .bf file was specified\n");
    }

    return 0;
}
