#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int main(int argc, string argv[])
{
    string key = argv[1];
    char cipher_text;
    int index;

    // Key restrictions
    if (key == NULL) // Lack of key
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        for (int j = 0, s = strlen(key) - 1; j < s; j++)
        {
            if (isdigit(key[i]) || isspace(key[i])) // Invalid characters in key
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
            else if (i != j && toupper(key[i]) - toupper(key[j]) == 0) // Dublicate characters in key
            {
                printf("Key must not contain dublicated characters.\n");
                return 1;
            }
            else if (strlen(key) != 26) // Invalid key length
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
    }
    string plain_text = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        // plaintext restrictions
        if (isalpha(plain_text[i]))
        {
            if (isupper(plain_text[i]))
            {
                index = plain_text[i] - 'A';
                cipher_text = toupper(key[index]);
            }
            else
            {
                index = plain_text[i] - 'a';
                cipher_text = tolower(key[index]);
            }
        }
        else
        {
            cipher_text = plain_text[i]; // the error is here
        }
        printf("%c", cipher_text);
    }
    printf("\n");
}
