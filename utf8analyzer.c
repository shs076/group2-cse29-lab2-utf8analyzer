#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>



void utf8(char *str);
uint8_t is_ascii(char string[]) {
        int i = 0;
        while(string[i] != '\0') {
                if((unsigned char)string[i] > 127){
                        return 0;
                }
                i++;
        }
        return 1;
}

int32_t capitalize_ascii(char str[]) {
        int i = 0;
        while(str[i] != '\0'){
                if(str[i] >= 'a' && str[i] <= 'z'){
                        str[i] = str[i] - 32;
                }
                i++;
        }
        return i;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
        return 1;
    }        
         utf8(argv[1]);
    char buffer[100];
    uint8_t ascii_result;
    int32_t length;
        while(1) {
                char* maybe_eof = fgets(buffer, 99, stdin);
                if(maybe_eof == NULL) { break; }
                char* newline = strchr(buffer, '\n');
                if (newline) *newline = '\0';
                ascii_result = is_ascii(buffer);
                capitalize_ascii(buffer);
                length = strlen(buffer);

                if (ascii_result) {
                    printf("Valid ASCII: true\n");
                }
                else {
                    printf("Valid ASCII: false\n");
                }
                printf("Uppercased ASCII: %s\n", buffer);
                printf("Length in bytes: %d\n", length);

        }
         return 0;
    }
   
void utf8(char *str) {
    const unsigned char *s = (const unsigned char *)str;
    int i = 0;
    int total_codepoints = 0;

    while (s[i] != '\0') {
        int cp = 0, nbytes = 0;

        if (s[i] <= 0x7F) {
            cp = s[i];
            nbytes = 1;
        } else if ((s[i] & 0xE0) == 0xC0) {
            cp = ((s[i] & 0x1F) << 6) | (s[i+1] & 0x3F);
            nbytes = 2;
        } else if ((s[i] & 0xF0) == 0xE0) {
            cp = ((s[i] & 0x0F) << 12) |
                 ((s[i+1] & 0x3F) << 6) |
                 (s[i+2] & 0x3F);
            nbytes = 3;
        } else if ((s[i] & 0xF8) == 0xF0) {
            cp = ((s[i] & 0x07) << 18) |
                 ((s[i+1] & 0x3F) << 12) |
                 ((s[i+2] & 0x3F) << 6) |
                 (s[i+3] & 0x3F);
            nbytes = 4;
        } else {
            printf("Invalid UTF-8 at byte %d\n", i);
            return;
        }

        printf("Codepoint: %d (uses %d byte%s)\n", cp, nbytes, nbytes > 1 ? "s" : "");
        i += nbytes;
        total_codepoints++;
    }

    printf("Total UTF-8 codepoints: %d\n", total_codepoints);
}



// The program should take a UTF-8 encoded string as input and print out the following information in the terminal:
//Whether the string is valid ASCII (e.g. all bytes are 127 or less).
//The same input string, but any ASCII lowercase characters a-z are changed to their uppercase versions. Leaves all other characters unchanged. 
//Length of the whole string in bytes.
//The number of UTF-8 codepoints represented by the string.
//Decimal representations of each codepoint.
//How many bytes are used to represent each codepoint.
//Substring of the input string containing only the first 6 codepoints.
//All animal emojis in the input string.
//The code point with value one higher at index 3 (e.g. for ”é“ (U+00E9) that would be “ê” (U+00EA), and for “🐩” (U+1F429) that would be “🐪” (U+1F42A)). 

