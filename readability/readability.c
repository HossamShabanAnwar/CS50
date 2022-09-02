#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");

    // Calculating the numbers of letters, words and sentences
    int num_letters = 0;
    int num_words = 1;
    int num_sentences = 0;

    // i is the counter of letters in the provided text
    for (int i = 0, n = strlen(text); i < n; i++)
    {

        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            num_letters += 1;
        }
        else if (text[i] == ' ')
        {
            num_words += 1;
        }
        else if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            num_sentences += 1;
        }
    }

    // Calculating the text grade
    float L = (num_letters * 100) / (float)num_words;
    float S = (num_sentences * 100) / (float)num_words;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int X = round(index);

    // printing the reading level
    if (X >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (X < 0)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", X);
    }
}
