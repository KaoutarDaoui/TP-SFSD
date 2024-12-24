
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "functions.h"

#define lim 30
#define MAX_KEY 3
#define MAX_LEN 3

// Define color codes
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[38;5;11m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"
#define BRIGHT_BLUE "\033[37m"
#define LIGHT_BLUE "\033[104m"

#define BOLD "\033[1m"

#define BG_WHITE "\033[48;5;7m"

/// header: returns the characteristic i of the TOVC/TnOVC file -----------------------------------------------------------------------
int header(TOVC *file, int i)
{
    if (i == 1)
    {
        return (file->header.LasBlock); ///(1) Returns the position of the last block of the file
    }
    else if (i == 2)
    {
        return (file->header.FreePos); ///(2)Returns the first free position
    }
    else if (i == 3)
    {
        return (file->header.NB_data); ///(3) Returns the number of data non-deleted
    }
    else if (i == 4)
    {
        return (file->header.NB_deleted); ///(4) Returns the number of logically deleted data
    }
    else
    {
        printf("Error: the i entered in Header function is invalid.\n");
        return -1;
    }
}
///------------------------------------------------------------------------------------------------------------------------------------


/// SetHeader: allows assigning x to the chosen characteristic i of the TOVC/TnOVC file -----------------------------------------------
void SetHeader(TOVC *file, int i, int x)
{
    if (i == 1)
    {
        file->header.LasBlock = x; /// Assigns x to the position of the last block of the file
    }
    else if (i == 2)
    {
        file->header.FreePos = x; /// Assigns x to the first free position
    }
    else if (i == 3)
    {
        file->header.NB_data = x; /// Assigns x to the number of data non-deleted
    }
    else if (i == 4)
    {
        file->header.NB_deleted = x; /// Assigns x to the number of deleted data
    }
    else
    {
        printf("Error: the value of i entered in SetHeader function is invalid.\n");
    }
}
///------------------------------------------------------------------------------------------------------------------------

/// Open: allows opening a file and returning a pointer of type TOVC/TnOVC ------------------------------------------------
TOVC *Open(char namef[30], char mode)
{
    TOVC *file = malloc(sizeof(TOVC));

    /// if opening in new mode
    if ((mode == 'n') || (mode == 'N'))
    {
        file->f = fopen(namef, "wb+");
        if (file->f != NULL)
        {
            printf("File opened successfully\n\n");
            /// Initialize the header:
            file->header.LasBlock = 0;
            file->header.FreePos = 0;
            file->header.NB_data = 0;
            file->header.NB_deleted = 0;

            rewind(file->f);                                     /// Position at the beginning of the file
            fwrite(&(file->header), sizeof(Header), 1, file->f); /// Why not use sizeof(header) directly?
        }
        else
        {
            printf("File not created successfully\n");
        }
    }

    /// if opening in existing mode (old mode)
    else
    {
        if ((mode == 'o') || (mode == 'O'))
        {
            file->f = fopen(namef, "rb+");
            if (file->f != NULL)
            {
                printf("File opened successfully\n");
                rewind(file->f);
                fread(&(file->header), sizeof(Header), 1, file->f);
            }
            else
            {
                printf("Error : File not opened successfully, create the file before continuing\n");
            }
        }
    }

    /// rewind(file->f);
    return (file);
}
///--------------------------------------------------------------------------------------------------------------------------------

/// close: allows closing a file of type TOVC -------------------------------------------------------------------------------------
void close(TOVC *file)
{
    rewind(file->f);                                     /// Position at the beginning of the file
    fwrite(&(file->header), sizeof(Header), 1, file->f); /// Write the header back to the file
    fclose(file->f);                                     /// Close the file
    free(file);                                          /// Free the allocated memory for the file structure
}
///------------------------------------------------------------------------------------------------------------------------------


/// WriteBlock: allows writing the buffer buf to the i-th block of a TOVC file --------------------------------------------------
void WriteBlock(TOVC *file, int i, Block buf)
{
    if (i < 1 || i > file->header.LasBlock)
    { // if the i is invalid
        printf("Error: Invalid block index.\n");
    }
    else
    {
        /// Position at the beginning of the i-th block and then write to file->f
        fseek(file->f, sizeof(Header) + (sizeof(Block) * (i - 1)), SEEK_SET);
        fwrite(&buf, sizeof(Block), 1, file->f);
    }
}

///-------------------------------------------------------------------------------------------------------------------------------

/// ReadBlock: allows reading the i-th block from the TOVC file pointed to by file into the buffer buf --------------------------
void ReadBlock(TOVC *file, int i, Block *buf)
{
    if (fread(buf, sizeof(*buf), 1, file->f) != 1)
    {
        printf("Error: Reading the block.\n");
    }
    if (i > file->header.LasBlock || i < 1)
    { // If the position of the block is invalid : either smaller than one or greater than the actual number of blocks in the file
        printf("Error: Invalid block index.\n");
        return -1;
    }
    else
    {
        /// Position at the beginning of the i-th block and then read it into buf
        fseek(file->f, sizeof(Header) + (sizeof(Block) * (i - 1)), SEEK_SET);
        fread(buf, sizeof(Block), 1, file->f);
    }
}
///------------------------------------------------------------------------------------------------------------------------------

/// AllocBlock: allows allocating a new block -----------------------------------------------------------------------------------
void AllocBlock(TOVC *file)
{
    SetHeader(file, 1, header(file, 1) + 1); /// Increment the last block count in the header by 1
}
///------------------------------------------------------------------------------------------------------------------------------


/// int_to_string: transforms an integer num into a string s with a maximum length >>The difference is filled with zeros-------------
void int_to_string(int num, int max, char *s)
{
    char s_num[4]; /// We know that the int num is at most 3 digits (+1 for /0)

    sprintf(s_num, "%d", num); /// Convert the integer to a string

    int j = max - strlen(s_num); /// Calculate the number of leading zeros needed
    sprintf(s, "%s", "");        /// Initialize the string s
    while (j > 0)
    {
        sprintf(s, "%s0", s); /// Append zeros to the string
        j--;
    }
    sprintf(s, "%s%s", s, s_num); /// Append the converted number to the string
}
/**
---> EXAMPLE:

Suppose we want to convert the integer 45 to a string with a maximum length of 5, filling the remaining spaces with zeros.

int num = 45;
int max_length = 5;
char s[6]; // Array to store the resulting string (5 for digits + 1 for '\0')
int_to_string(num, max_length, s);

Result:
The value of `s` will be "00045".

Explanation:
1. The integer `num` is converted to the string "45".
2. Since the maximum length is 5, the function calculates the number of leading zeros needed (5 - 2 = 3).
3. Three zeros are added in front of "45" to produce the string "00045".
4. The final string "00045" is stored in `s`.
*/

///------------------------------------------------------------------------------------------------------------------------------


/// cpy_string: copies from string s starting at position i, to a substring r with a maximum length -----------------------------
void cpy_string(char *s, int i, int max, char *r)
{
    /// if (i < 0) i = 0;   // Uncomment to handle negative indices by setting i to 0
    sprintf(r, "%s", "");            // Initialize the substring r
    while (i < strlen(s) && max > 0) // Continue while within bounds of s and max length not exceeded
    {
        sprintf(r, "%s%c", r, s[i]); // Append character from s to r
        i++;
        max--;
    }
}
/**
---> EXAMPLE:

Suppose we have the following strings:

char source[] = "Hello, World!";
char destination[20]; // Buffer to hold the copied substring
int start_index = 7;  // We want to start copying from the character at index 7
int max_length = 5;   // We want to copy a maximum of 5 characters

- Call the cpy_string function to copy from source to destination
cpy_string(source, start_index, max_length, destination);

- After the function call, the destination will contain:
  destination = "Wor" This is because we started copying from index 7, which is 'W', and we copied a maximum of 5 characters (i.e., 'W', 'o', 'r').
*/

///------------------------------------------------------------------------------------------------------------------------------


/// cut_string: allows removing a portion of the string s with a maximum length starting from position i ------------------------
void cut_string(char *s, int i, int max)
{
    char right_part[lim + 1]; // Buffer for the right part of the string
    char left_part[lim + 1];  // Buffer for the left part of the string

    cpy_string(s, 0, i, left_part);                // Copy the left part of the string
    cpy_string(s, i + max, strlen(s), right_part); // Copy the right part of the string

    sprintf(s, "%s%s", left_part, right_part); // Concatenate left and right parts back into s
}
/**
---> EXAMPLE:

Suppose we have the following string:

char original[] = "Hello, World!";
int start_index = 5;  // We want to start removing from index 5 (which is 'o')
int max_length = 7;   // We want to remove up to 7 characters (which includes ', W')

cut_string(original, start_index, max_length);

// After the function call, the original string will contain:
// original = "Hello!"

// This is because we removed the substring "o, World", starting from index 5 and spanning 7 characters.
*/
///------------------------------------------------------------------------------------------------------------------------------


/// StringRec_to_Rec: transforms a StringRecord into a Record >> Utility: facilitates data manipulation --------------------------
void StringRec_to_Rec(StringRecord se, Record *en)
{
    char str[lim + 1]; // Buffer for temporary string storage

    /// The key :
    sprintf(str, "%s", "");    // Initialize the string (empty for now)
    cpy_string(se, 3, 3, str); // Copy the key from the StringRecord ( the key has 3 characters)
    en->key = atoi(str);       // Convert the string to an integer and assign it to the Record

    /// The boolean :
    sprintf(str, "%c", se[6]); // Get the boolean value as a character
    en->eff = atoi(str);       // Convert the character to an integer and assign it to the Record

    /// The data
    cpy_string(se, 7, strlen(se) - 7, en->data); // Copy the data portion from StringRecord to Record
} /**
 ---> EXAMPLE:

 Suppose we have a StringRecord `se` that looks like this:
     "12300123ABCD"
     - The first 3 characters are the key: "123"
     - The next character is the boolean "eff" flag: "0" (indicating an active record)
     - The rest is data: "123ABCD"

 1. The function `StringRec_to_Rec(se, &en)` is called.
 2. The `cpy_string(se, 3, 3, str)` function copies the key "123" from `se` and converts it to an integer, storing it in `en->key` (123).
 3. The boolean "eff" value is extracted next, assigning the integer value 0 to `en->eff`.
 4. Finally, the remaining part "123ABCD" is copied into `en->data`.

 After the transformation, `en` will be a Record with:
    en->key = 123
    en->eff = 0
    en->data = "123ABCD"
 */

///------------------------------------------------------------------------------------------------------------------------------

/// Rec_to_StringRec: allows transforming a Record into a StringRecord  =/ StringRec_to_Rec ----------------------------------------------------------
void Rec_to_StringRec(Record en, StringRecord se)
{
    char str[4];                  // Buffer for temporary string storage
    int length = strlen(en.data); // Length of the data

    sprintf(se, "%s", ""); // Initialize the StringRecord

    /// Write the length of the data into the StringRecord :
    int_to_string(length, 3, str); // Convert length to string with a maximum of 3 digits
    sprintf(se, "%s%s", se, str);  // Append length to StringRecord

    /// Write the key into the StringRecord :
    int_to_string(en.key, 3, str); // Convert key to string with a maximum of 3 digits
    sprintf(se, "%s%s", se, str);  // Append key to StringRecord

    /// Write the boolean value eff :
    int_to_string(en.eff, 1, str); // Convert boolean to string
    sprintf(se, "%s%s", se, str);  // Append boolean to StringRecord

    /// Write the data
    sprintf(se, "%s%s", se, en.data); // Append the actual data to StringRecord
}

/**    ------------>  "   StringRecord se = |data length|key|eff|data|    "  <------------------**/

/**  ---> EXAMPLE:

   Suppose we have the following Record:
   Record example = {key: 45, eff: 0, data: "Hello, World!"};
   StringRecord result;

   We would call the function like this:

   Rec_to_StringRec(example, result);

   After the function call, the result will contain:
   result = "0120450Hello, World!"
   - The length of "Hello, World!" is 13, so it is represented as "013".
   - The key is 45, represented as "045".
   - The boolean value eff is 0, represented as "0".
   - The actual data is appended directly after these values.
*/
///------------------------------------------------------------------------------------------------------------------------------

/// get_se: retrieves a Record from the file and places it in the variable `se`
void get_se(TOVC *file, int *i, int *j, StringRecord se)
{
    Block buf;
    char length[4]; // Buffer to hold the string representation of the data's length (up to 3 digits)
    int k;

    // Initialize the `length` string (to store data length) and `se` string (to store the entire record)
    sprintf(length, "%s", "");
    sprintf(se, "%s", "");

    // Read the block `*i` (current block index) into `buf`
    ReadBlock(file, (*i), &buf);

    // Loop to extract the 3-digit length of the data from `buf`
    for (k = 0; k < 3; k++)
    {
        // If within current block's limit, directly append character at `*j` position
        if ((*j) < lim)
        {
            sprintf(length, "%s%c", length, buf.table[*j]); // Append the character to `length`
            sprintf(se, "%s%c", se, buf.table[*j]);         // Append the same character to `se` (record)

            (*j)++; // Move to next position in the current block
        }
        else
        {
            // If end of block is reached, go to the next block
            (*i)++;                      // Increment block index
            ReadBlock(file, (*i), &buf); // Read the next block into `buf`

            // Append the first character of the new block to both `length` and `se`
            sprintf(length, "%s%c", length, buf.table[0]);
            sprintf(se, "%s%c", se, buf.table[0]);

            (*j) = 1; // Reset position within block to 1 (second character, as first is already read)
        }
    }

    // Convert `length` to integer for the number of characters to extract
    int data_length = atoi(length);

    // Retrieve the remaining record information (key, boolean, and data), whose length is `data_length + 4`
    for (k = 0; k < (data_length + 4); k++)
    {
        // If within current block's limit, directly append character at `*j` position to `se`
        if ((*j) < lim)
        {
            sprintf(se, "%s%c", se, buf.table[*j]); // Append character to `se`
            (*j)++;                                 // Move to next position
        }
        else
        {
            // If end of block is reached, go to the next block
            (*i)++;                      // Increment block index
            ReadBlock(file, (*i), &buf); // Read the next block into `buf`

            // Append the first character of the new block to `se`
            sprintf(se, "%s%c", se, buf.table[0]);
            (*j) = 1; // Reset position within block to 1 (second character, as first is already read)
        }
    }
}
/** ---> EXAMPLE:
   Suppose we have the following data stored across multiple blocks:

   Block 1: "003010hello worl"
   Block 2: "d"

   - Here, "003" is the 3-character length string, indicating the data length is 3.
   - "010" is the key of the record.
   - "0" is the boolean flag (indicating this record is active).
   - The actual data is "hello world" which spans across both blocks.

   Usage in the function:
      - The function starts by extracting "003" from the first three characters (for data length).
      - Then, it moves to the key ("010"), the flag ("0"),  and finally the data ("hello world").
      - It seamlessly handles block transitions, gathering the full record "0030hello world".
*/

///------------------------------------------------------------------------------------------------------------------------------

/// Printout_header: displays the header of the file ----------------------------------------------------------------------------
void Printout_header(TOVC *file)
{
    printf("\n%s============================================================%s\n", CYAN, RESET);
    printf("%s             FILE CHARACTERISTICS                     %s\n", BOLD, RESET);
    printf("%s============================================================%s\n", CYAN, RESET);
    printf("| %s%-40s%s: %s%-10d%s      |\n", BRIGHT_BLUE, "Address of the last block", RESET, YELLOW, header(file, 1), RESET);
    printf("| %s%-40s%s: %s%-10d%s      |\n", BRIGHT_BLUE, "Free position in the last block", RESET, YELLOW, header(file, 2), RESET);
    printf("| %s%-40s%s: %s%-10d%s      |\n", BRIGHT_BLUE, "Number of characters inserted", RESET, YELLOW, header(file, 3), RESET);
    printf("| %s%-40s%s: %s%-10d%s      |\n", BRIGHT_BLUE, "Number of characters deleted", RESET, YELLOW, header(file, 4), RESET);
    printf("%s============================================================%s\n", CYAN, RESET);
}
///------------------------------------------------------------------------------------------------------------------------------

/// Printout_block: displays the contents of all blocks ----------------------------------------------------------------------------
void Printout_block(TOVC *file)
{
    Block buf;
    int i;
    printf(CYAN"\n============================================================\n"RESET);
    printf("%s             CONTENTS OF ALL BLOCKS                \n", BOLD);
    printf(CYAN"============================================================\n"RESET);    if (header(file, 1) > 0) // Check if there are any blocks
    {
        for (i = 1; i <= header(file, 1); i++)
        {
            ReadBlock(file, i, &buf);                           // Read the block into buf
            printf(" Content of block %d: %s\n", i, buf.table); // Print the contents of the block
        }
    }
}
///------------------------------------------------------------------------------------------------------------------------------

/// Printout_specific_block: displays the contents of block i which have been specified by the user -----------------------------
void Printout_specific_block(TOVC *file)
{
    Block buf;
    int i;
     printf(CYAN"\n============================================================\n"RESET);
    printf("%s             CONTENTS OF A SPECIFIC BLOCK                \n", BOLD);
    printf(CYAN"============================================================\n"RESET);

    if (header(file, 1) <= 0) { // Check if there are any blocks
        printf("%sNo blocks available in the file.%s\n", RED, RESET);
        printf(CYAN"============================================================\n"RESET);
        return;
    }

    // Prompt the user for block number
    printf("%sWhich block do you want to display? %s", BRIGHT_BLUE, RESET);
    scanf("%d", &i);

    if (i < 1 || i > header(file, 1)) { // Validate the block number
        printf("%sInvalid block number. Please enter a value between 1 and %d.%s\n", RED, header(file, 1), RESET);
    } else {
        ReadBlock(file, i, &buf); // Read the block into buf
        printf("| %sBlock %-4d%s | %s%-40s%s |\n", GREEN, i, RESET, YELLOW, buf.table, RESET);
    }

    printf(CYAN"============================================================\n"RESET);
}

///------------------------------------------------------------------------------------------------------------------------------

/// printout_file: allows displaying the Records from the file ------------------------------------------------------------------
/// Logically deleted Records are not displayed:
void printout_file(TOVC *file)
{
    int i = 1;       // Block index
    int j = 0;       // Character index
    Record en;       // Variable to hold the Record
    StringRecord se; // Variable to hold the StringRecord
    char length[4];  // Buffer for length as a string ( 3charters + 1for \0)

    printf(CYAN"\n============================================================\n"RESET);
    printf("%s             RECORDS                             \n", BOLD);
    printf(CYAN"============================================================\n"RESET);
    printf("| %sKEY %s|%sEFF%s| %sDATA%s\n", GREEN, RESET, YELLOW, RESET, BRIGHT_BLUE, RESET);
    printf("------------------------------------------------------------\n");
    while (i <= header(file, 1)) // Iterate through all blocks
    {
        get_se(file, &i, &j, se); // Retrieve the StringRecord from the file
        // printf("se = %s   i = %d   j = %d\n", se, i, j); // Debugging line
        StringRec_to_Rec(se, &en);        // Convert StringRecord to Record
        int_to_string(en.key, 3, length); // Convert key to string

        printf("  %s | %d | %s\n", length, en.eff, en.data); // Display Record details
        if ((i == header(file, 1)) && (j == header(file, 2)))
            break; // Exit if end of records is reached
    }
}
///------------------------------------------------------------------------------------------------------------------------------


/// Printout_overlapping: allows displaying overlapping Records ----------------------------------------
void Printout_overlapping(TOVC *file)
{
    int i = 1;  // Initialize the current block index to 1
    int i1 = 1; // Initialize i1 to track the current record's block during comparison
    int j = 0;  // Initialize the character index within the block
    int j1 = 0; // Initialize j1 to track the character index for the comparison record

    Record en;       // A structure to hold the transformed record
    StringRecord se; // A temporary string to hold the data read from the file
    char length[4];  // A buffer to hold the string representation of the length of data

    printf(CYAN"\n============================================================\n"RESET);
    printf("%s             OVERLAPPING RECORDS                    \n", BOLD);
    printf(CYAN"============================================================\n"RESET);

    // Loop through the blocks until the last block is reached !
    while (i <= header(file, 1))
    {
        // Retrieve a record from the file, updating i1 and j1 accordingly
        get_se(file, &i1, &j1, se);

        // Check if the block number of the retrieved record (i1) differs from the current block (i)
        if (i1 != i)
        {
            // Convert the string record to a structured Record
            StringRec_to_Rec(se, &en);

            // Generate a string representation of the length of the record's data
            int_to_string(en.key, 3, length);

            // Display the record if it is not logically deleted (eff == 0)
            if (en.eff == 0)
            {
                // Print details of the overlapping record, including block numbers, length, and data
                printf("Between block %d and %d: %s | %d | %s  \n", i, i1, length, en.eff, en.data);
            }

            // Check if the end of the current block has been reached
            if (j1 == lim)
            {
                i1++;   // Move to the next block
                j1 = 0; // Reset the character index to the beginning of the new block
            }

            // Update the current block and character index for the next iteration
            i = i1;
            j = j1;
        }

        // Exit condition: if we reach the last block and have read all records
        if ((i == header(file, 1)) && (j == header(file, 2)))
            break; // Exit the loop
    }
}

///------------------------------------------------------------------------------------------------------------------------------


/// Search_TnOVC: searches within the file (We traverse our file sequentially and compare the searched key with all keys) ----------------------------
void Search_TnOVC(TOVC *file, int key, int *i, int *j, int *found)
{
    (*found) = 0; // Initialize found flag to 0
    (*i) = 1;     // Initialize block index
    (*j) = 0;     // Initialize character index

    int i1 = 1, j1 = 0; // Temporary indices for traversal

    StringRecord SE; // String record to hold data
    Record E;        // Record structure to hold the current record

    if (header(file, 1) > 0) // The search only proceeds if the file is not empty (one block at least)
    {
        sprintf(SE, "%s", "");
        while (!(*found) && (*i) <= header(file, 1))
        {
            get_se(file, &i1, &j1, SE); // Retrieve the record into SE and position to the beginning of the next record
            StringRec_to_Rec(SE, &E);   // Convert string record to Record structure

            if (!E.eff && E.key >= key)
                break; // Break if the key is found or doesn't exist
            if (!(*found))
            {
                (*i) = i1; // Update the block index
                (*j) = j1; // Update the character index
            }
            if (((*i) == header(file, 1)) && (*j) == header(file, 2))
                break; // Exit if end of file is reached without finding
        }
        if ((!E.eff) && (E.key == key))
        {
            (*found) = 1;
        } // Mark as found if the key matches
    }
}
///------------------------------------------------------------------------------------------------------------------------------


/// string_to_record--------------------------------------------------------------------------------------------------------------
void string_to_record(char *source, int pos, Record *rec)
{
    char s[100]; // Temporary string buffer to hold extracted data
    int i;

    // Extract the key from the source string:
    sprintf(s, ""); // Initialize the temporary string
    for (i = 0; i < MAX_KEY; i++)
    {                                           // Loop to extract MAX_KEY characters
        sprintf(s, "%s%c", s, source[pos + i]); // Append characters to the string for the key
    }
    rec->key = atoi(s); // Convert the accumulated string to an integer and assign it to the key of the record

    // Clear the temporary string for the next use
    sprintf(s, "");                               // Initialize the string again
    sprintf(s, "%s%c", s, source[pos + MAX_KEY]); // Get the boolean value from the next character
    rec->eff = atoi(s);                           // Convert this single character string to an integer and assign it to the record

    // Clear the temporary string for the next use
    sprintf(s, ""); // Initialize the string again
    for (i = 0; i < MAX_LEN; i++)
    {                                                         // Extract the data length (the next MAX_LEN characters)
        sprintf(s, "%s%c", s, source[pos + MAX_KEY + 1 + i]); // Append characters to the string for length
    }

    int info_length = atoi(s); // Convert the string representing the length of data into an integer

    // Clear the temporary string for the next use
    sprintf(s, ""); // Initialize the string again
    for (i = 0; i < info_length; i++)
    {                                                                   // Extract the actual data based on the previously obtained length
        sprintf(s, "%s%c", s, source[pos + MAX_KEY + 1 + MAX_LEN + i]); // Append characters to the string for data
    }
    s[info_length] = '\0'; // Null-terminate the string to properly format the C string

    // Copy the extracted data into the Record structure
    strcpy(rec->data, s); // Use strcpy to assign the extracted string to the data field of the record
}
/**
 ---> EXAMPLE:

Consider a scenario where we have a source string that represents a record with the following format:
- The first 3 characters represent the key (an integer).
- The 4th character represents the "eff" (an integer flag).
- The next 3 characters represent the length of the actual data (an integer).
- The actual data follows based on the specified length.

Source string:
    "12303abc"   // Example string with:
    // Key: 123 (first 3 characters)
    // eff: 0 (4th character)
    // Length: 3 (next 3 characters, meaning the data will be 3 characters long)
    // Data: "abc" (last 3 characters)

Let's say we want to extract this record starting from position 0.

Record rec; // Define a Record structure to hold the extracted data
string_to_record("12301abc", 0, &rec); // Call the function to populate 'rec'

- After calling the function, 'rec' will contain:
- rec.key = 123       // Integer key extracted from the string
- rec.eff = 0        // Integer eff value extracted from the string
- rec.data = "abc"   // String data extracted from the string

- We can now use 'rec' as needed in our program, e.g.,
- printf("Key: %d, Eff: %d, Data: %s\n", rec.key, rec.eff, rec.data);
* This would output --> Key: 123, Eff: 0, Data: abc
*/

///--------------------------------------------------------------------------------------------------------------------------------------------


/// Search in the file :We traverse our file dichotomously and compare the searched key to all keys--------------------------------------------
void Search_TOVC(TOVC *file, int key, int *i, int *j, int *found)
{
    int stop = 0;
    Block buffer, nextBuffer;
    Record rec, recNextBuffer;

    int lowerBlock = 1, upperBlock = header(file, 1); //--- lowerBlock and upperBlock represent the lower and upper block bounds respectively ---//
    if (upperBlock == 0)
    {
        upperBlock++;
    }
    (*found) = 0; // Initialize found flag to 0
    (*i) = 1;     // Initialize block index
    (*j) = 0;     // Initialize character index
    while ((lowerBlock <= upperBlock) && (!*found) && (!stop))
    {
        *i = (lowerBlock + upperBlock) / 2; // Calculate the middle block

        ReadBlock(file, *i, &buffer);         // Read the current block
        ReadBlock(file, *i + 1, &nextBuffer); // Read the next block

        string_to_record(buffer.table, 0, &rec);               // Convert the current block to a record
        string_to_record(nextBuffer.table, 0, &recNextBuffer); // Convert the next block to a record

        if ((key >= rec.key) && (key < recNextBuffer.key)) // Check if the key is in the range of current and next record
        {
            while ((!*found) && (!stop))
            {
                if (key == rec.key)
                    *found = 1; // Key found
                else if ((*j < buffer.last_pos) && (key > rec.key))
                {
                    *j = *j + strlen(rec.data) + 1 + MAX_KEY + MAX_LEN; // Update position for the next record
                    string_to_record(buffer.table, *j, &rec);           // Read the next record
                }
                else
                    stop = 1; // Stop searching
            }
        }
        else
        {
            if (key < rec.key)
                upperBlock = *i - 1; // Move to the left half
            else
                lowerBlock = *i + 1; // Move to the right half
        }
    }

    if ((!*found) && (!stop))
        *i = lowerBlock; //--- Case where the searched information should be at the head or tail of the file ---//

    if ((*j == 0) && (*i > 1) && (!*found)) //--- Case where a record should be at the end of a block instead of the beginning ---//
    {
        *i = *i - 1;                  // Move to the previous block
        ReadBlock(file, *i, &buffer); // Read the previous block

        string_to_record(buffer.table, 0, &rec); // Convert to record
        while ((!*found) && (!stop))
        {
            if (key == rec.key)
                *found = 1; // Key found
            else if ((*j < buffer.last_pos) && (key > rec.key))
            {
                *j = *j + strlen(rec.data) + 1 + MAX_KEY + MAX_LEN; // Update position for the next record
                string_to_record(buffer.table, *j, &rec);           // Read the next record
            }
            else
                stop = 1; // Stop searching
        }
    }

    if ((*found) && (rec.eff == 1))
        *found = 0; //--- The search respects logical deletions ---//
}
///-------------------------------------------------------------------------------------------------------------------------------------

/// Performs the logical deletion of a Record, setting the eff field to 1 --------------------------------------------------------------
// TnOVC:
void delete_Log_TnOVC(TOVC *file, int key)
{
    Block buf;
    int i, j, found, k;
    char length[4];

    Search_TnOVC(file, key, &i, &j, &found); // Search for the record with the specified key
    if (found)
    {
        /// Retrieve the length of the data to update the header
        ReadBlock(file, i, &buf);
        sprintf(length, "%s", "");
        for (k = 0; k < 3; k++)
        {
            if (j < lim)
            {
                sprintf(length, "%s%c", length, buf.table[j]); // Get the length from the buffer
                j++;
            }
            else
            {
                i++;
                ReadBlock(file, i, &buf);                      // Move to the next block
                sprintf(length, "%s%c", length, buf.table[0]); // Get the first character of the next block
                j = 1;                                         // Reset j to point to the first character of the next block
            }
        }

        /// Modify the eff field; at this point j is positioned at the first character of the key,
        /// j+3 is the position of the eff character
        if (j + 3 < lim)
        {
            buf.table[j + 3] = '1';   // Set eff to '1' for logical deletion
            WriteBlock(file, i, buf); // Write the modified block back to the file
        }
        else
        {
            /// Increment i to read the next block
            ReadBlock(file, i + 1, &buf);
            buf.table[(j + 3) % lim] = '1'; // Use modulo to wrap around to the start of the block
            WriteBlock(file, i + 1, buf);   // Write the modified block back to the file
        }
        SetHeader(file, 4, header(file, 4) + atoi(length) + 7); // Update the header for logical deletions
    }
}
///--------------------------------------------------------------------------------------------------------------------

/// TOVC:(it's the same we just change the search function)-------------------------------------------------------------
void delete_Log_TOVC(TOVC *file, int key)
{
    Block buf;
    int i, j, found, k;
    char length[4];

    Search_TnOVC(file, key, &i, &j, &found); // Search for the record with the specified key
    if (found)
    {
        /// Retrieve the length of the data to update the header
        ReadBlock(file, i, &buf);
        sprintf(length, "%s", "");
        for (k = 0; k < 3; k++)
        {
            if (j < lim)
            {
                sprintf(length, "%s%c", length, buf.table[j]); // Get the length from the buffer
                j++;
            }
            else
            {
                i++;
                ReadBlock(file, i, &buf);                      // Move to the next block
                sprintf(length, "%s%c", length, buf.table[0]); // Get the first character of the next block
                j = 1;                                         // Reset j to point to the first character of the next block
            }
        }

        /// Modify the eff field; at this point j is positioned at the first character of the key,
        /// j+3 is the position of the eff character
        if (j + 3 < lim)
        {
            buf.table[j + 3] = '1';   // Set eff to '1' for logical deletion
            WriteBlock(file, i, buf); // Write the modified block back to the file
        }
        else
        {
            /// Increment i to read the next block
            ReadBlock(file, i + 1, &buf);
            buf.table[(j + 3) % lim] = '1'; // Use modulo to wrap around to the start of the block
            WriteBlock(file, i + 1, buf);   // Write the modified block back to the file
        }
        SetHeader(file, 4, header(file, 4) + atoi(length) + 7); // Update the header for logical deletions
    }
}

///-------------------------------------------------------------------------------------------------------------------------------------

/// Performs physical deletion in the file -----------------------------------------------------------------------------
void delete_phy_TOVC(TOVC *file, int key)
{
    int i, j, i1, j1, found, stop, k;
    char length[4];
    StringRecord se, part1, part2;
    Block buf;

    Search_TnOVC(file, key, &i, &j, &found); // Search for the record with the specified key
   // printf("\nSearch result for key = %d\n i = %d,  j = %d, found = %d ", key, i, j, found);

    if (found)
    {
        i1 = i; // i1 and j1 are used for traversal in the buffer
        j1 = j;
        stop = 0;

        get_se(file, &i1, &j1, se); // Set i and j to the beginning of the Records
       // printf("\n\nResult of get_se\nse = %s,  i1 = %d,  j1 = %d", se, i1, j1);

        cpy_string(se, 0, 3, length); // Copy the length of the data from the Record to be deleted
       // printf("\n\nResult of copy_string\nlength = %s", length);

        while (!stop)
        {
            get_se(file, &i1, &j1, se); // Retrieve Records to shift one by one
           // printf("\n\nResult of get_se in while\nse = %s,  i1 = %d,  j1 = %d", se, i1, j1);

            cpy_string(se, 0, lim - j, part1); // Copy part of the string to part1
            //printf("\n\nResult of copy_string\npart1 = %s", part1);

            cpy_string(se, strlen(part1), strlen(se), part2); // Copy the remaining part to part2
            //printf("\n\nResult of copy_string\npart2 = %s", part2);

            ReadBlock(file, i, &buf);
            buf.table[j] = '\0';                          // Clear the string starting from position j
            sprintf(buf.table, "%s%s", buf.table, part1); // Concatenate part1 to the buffer
            WriteBlock(file, i, buf);

            j = j + strlen(part1); // If another insertion occurs in this block, it will follow part1

            if (strlen(part2) != 0) // If part2 is not empty
            {
                i = i1;            // Update i to i1
                j = strlen(part2); // Update j to the length of part2
                ReadBlock(file, i, &buf);
                for (k = 0; k < j; k++)
                {
                    buf.table[k] = part2[k];
                } // Shift the string to the beginning of the block
                WriteBlock(file, i, buf);
            }
            if ((i1 >= header(file, 1)) && (j1 >= header(file, 2)))
            {
                stop = 1;
            } // Reached the end of the file, shifts done
        }

        /// Update the header
        SetHeader(file, 1, i);                                    // Update the number of blocks
        SetHeader(file, 2, j);                                    // Update the position of the last character
        SetHeader(file, 3, header(file, 3) - (atoi(length) + 7)); // Update the number of characters removed
    }
}
///-------------------------------------------------------------------------------------------------------------------------------------

/// Performs physical deletion in the file -----------------------------------------------------------------------------
void delete_phy_TnOVC(TOVC *file, int key)
{
    int i, j, i1, j1, found, stop, k;
    char length[4];
    StringRecord se, part1, part2;
    Block buf;

    Search_TnOVC(file, key, &i, &j, &found); // Search for the record with the specified key
   // printf("\nSearch result for key = %d\n i = %d,  j = %d, found = %d ", key, i, j, found);

    if (found)
    {
        i1 = i; // i1 and j1 are used for traversal in the buffer
        j1 = j;
        stop = 0;

        get_se(file, &i1, &j1, se); // Set i and j to the beginning of the Records
       // printf("\n\nResult of get_se\nse = %s,  i1 = %d,  j1 = %d", se, i1, j1);

        cpy_string(se, 0, 3, length); // Copy the length of the data from the Record to be deleted
      //  printf("\n\nResult of copy_string\nlength = %s", length);

        while (!stop)
        {
            get_se(file, &i1, &j1, se); // Retrieve Records to shift one by one
            //printf("\n\nResult of get_se in while\nse = %s,  i1 = %d,  j1 = %d", se, i1, j1);

            cpy_string(se, 0, lim - j, part1); // Copy part of the string to part1
            //printf("\n\nResult of copy_string\npart1 = %s", part1);

            cpy_string(se, strlen(part1), strlen(se), part2); // Copy the remaining part to part2
            //printf("\n\nResult of copy_string\npart2 = %s", part2);

            ReadBlock(file, i, &buf);
            buf.table[j] = '\0';                          // Clear the string starting from position j
            sprintf(buf.table, "%s%s", buf.table, part1); // Concatenate part1 to the buffer
            WriteBlock(file, i, buf);

            j = j + strlen(part1); // If another insertion occurs in this block, it will follow part1

            if (strlen(part2) != 0) // If part2 is not empty
            {
                i = i1;            // Update i to i1
                j = strlen(part2); // Update j to the length of part2
                ReadBlock(file, i, &buf);
                for (k = 0; k < j; k++)
                {
                    buf.table[k] = part2[k];
                } // Shift the string to the beginning of the block
                WriteBlock(file, i, buf);
            }
            if ((i1 >= header(file, 1)) && (j1 >= header(file, 2)))
            {
                stop = 1;
            } // Reached the end of the file, shifts done
        }

        /// Update the header
        SetHeader(file, 1, i);                                    // Update the number of blocks
        SetHeader(file, 2, j);                                    // Update the position of the last character
        SetHeader(file, 3, header(file, 3) - (atoi(length) + 7)); // Update the number of characters removed
    }
}
///-------------------------------------------------------------------------------------------------------------------------------------

/// Inserts SE into block i at position j ---------------------------------------------------------------------------------
void insert_pos_rec(TOVC *file, int *i, int *j, StringRecord SE)
{
    Block buf;
    StringRecord part1, part2, SI; /// part1, part2: variables used to split the string to insert
                                   /// SI: contains the part of the block removed for insertion, which will be reinserted as we proceed

    if ((*i) <= header(file, 1))
    {
        sprintf(buf.table, "%s", "");
        sprintf(part2, "%s", "");
        sprintf(SI, "%s", "");

        ReadBlock(file, (*i), &buf);

        cpy_string(SE, 0, lim - (*j), part1);                             /// Copy into part1 the number of characters from SE that can be inserted into block i
        cpy_string(SE, strlen(part1), strlen(SE) - strlen(part1), part2); /// The remainder of the Record to insert
        cpy_string(buf.table, (*j), lim - (*j), SI);                      /// The part of the block that needs to be shifted for insertion

        sprintf(part2, "%s%s", part2, SI); /// part2 becomes the string to insert
        buf.table[(*j)] = '\0';
        sprintf(buf.table, "%s%s", buf.table, part1); /// Insert part1 into the buffer

        (*j) = (*j) + strlen(part1);
        WriteBlock(file, (*i), buf);

        if ((*i) == header(file, 1))
        {
            SetHeader(file, 2, *j);
        }
        if (strlen(part2) != 0)
        {
            if (*j >= lim)
            {
                (*i)++;
                (*j) = (*j) % lim;
            }
            insert_pos_rec(file, i, j, part2); // Recursive call for any remaining part to insert
        }
    }
    else
    {
        AllocBlock(file);
        /// sprintf(buf.table,"%s",""); ///
        sprintf(buf.table, "%s", SE); // Insert the remaining SE into a new block

        (*j) = strlen(SE);
        SetHeader(file, 2, *j); // Update the header with the new position
        WriteBlock(file, (*i), buf);
    }
}
///-------------------------------------------------------------------------------------------------------------------------------------

/// Allows the insertion in TnOVC ------------------------------------------------------------------------------------------------------
void insert_TnOVC(TOVC *file, Record E)
{
    int found;
    int i = header(file, 1); // Last block index
    if (i == 0)
    {
        i = 1;
    };
    printf("the i: %d\n", i);
    int j = header(file, 2); // First free position in the last block
    printf("the j: %d\n", j);

    StringRecord SE;
    // If the record with the key is not found, proceed with the insertion
    // Convert the record to its string representation
    Rec_to_StringRec(E, SE);

    // Insert the string record into the file at the end position
    insert_pos_rec(file, &i, &j, SE);

    // Update the header with the new size and position of the data in the file
    SetHeader(file, 1, i);                            // Update last block index
    SetHeader(file, 2, j);                            // Update free position within the last block
    SetHeader(file, 3, header(file, 3) + strlen(SE)); // Update data size in the file
}
///-------------------------------------------------------------------------------------------------------------------------------------

/// Insertion into the file --------------------------------------------------------------------------------------------------------
void insert_TOVC(TOVC *file, Record E)
{
    int i, j, found; // Initialize variables for block index, position, and found status
    StringRecord SE; // String representation of the record to be inserted

    // Search for the position of the record with the given key
    Search_TnOVC(file, E.key, &i, &j, &found);

    // If the record with the key is not found, proceed with the insertion
    if (!found)
    {
        // Convert the record to its string representation
        Rec_to_StringRec(E, SE);

        // Insert the string record into the file at the identified position
        insert_pos_rec(file, &i, &j, SE);

        // Update the header with the new size of the data in the file
        SetHeader(file, 3, header(file, 3) + strlen(SE));
    }
}
///-------------------------------------------------------------------------------------------------------------------------------------

/// Reorganizes the file ---------------------------------------------------------------------------------------------------------------

void Reorganize_TOVC(TOVC *file, char *new_file)
{
    int i = 1;       // Index for the current block in the old file
    int i1 = 1;      // Index for the current block in the new file
    int j = 0;       // Position within the current block in the old file
    int j1 = 0;      // Position within the current block in the new file
    StringRecord se; // String representation of the record to be transferred
    Record en;       // Struct to hold the record data

    // Open a new file for writing
    TOVC *new = Open(new_file, 'N');

    // Loop through all blocks in the old file
    while (i <= header(file, 1))
    {
        sprintf(se, "%s", "");     // Initialize se as an empty string to avoid issues
        get_se(file, &i, &j, se);  // Retrieve the string from the old file
        StringRec_to_Rec(se, &en); // Convert the string representation to a Record struct

        // Check if the record is logically not deleted
        if (en.eff == 0) // If the "eff" field is 0, the record is not logically deleted
        {
            if (j1 > (lim / 2)) // Ensuring the organization so the file is 50% full
            {
                i1++; // Move to the next block on that case
                j1 = 0; // Reset the position within the new block
            }
            // Insert the valid record into the new file
            insert_pos_rec(new, &i1, &j1, se);
            // Update the header with the new size of inserted characters
            SetHeader(new, 3, header(new, 3) + strlen(se));
        }

        // Break the loop if we've reached the end of the old file
        if ((i == header(file, 1)) && (j == header(file, 2)))
            break;
    }

    // Print the header and contents of the new file
    Printout_header(new);
    printout_file(new);
    // close(new); // Uncomment this line to close the new file after processing
}

///-------------------------------------------------------------------------------------------------------------------------------------

/// Initial load TOVC--------------------------------------------------------------------------------------------------------------------
void Initial_Load_TOVC(TOVC *file, int num)
{
    int x = 0, k = 0;
    int i, j, found;
    StringRecord SE;
    Record en;
    Block buf;

    while (x < num)
    {
        sprintf(en.data, "%s", "");
        printf("\n n%c%d : key = ", 248, k);
        scanf("%d", &(en.key));
        printf("       data  = ");
        scanf("%s", en.data);
        en.eff = 0;

        i = 0;
        j = 0;
        found = 0;
        Search_TnOVC(file, en.key, &i, &j, &found);

        if (!found)
        {
            // Convert record to string
            Rec_to_StringRec(en, SE);

            while (1)
            {
                if (i <= header(file, 1))
                {
                    sprintf(buf.table, "%s", "");
                    StringRecord part1, part2, SI;
                    sprintf(part2, "%s", "");
                    sprintf(SI, "%s", "");

                    ReadBlock(file, i, &buf);

                    cpy_string(SE, 0, lim - j, part1);                                // Copy part1
                    cpy_string(SE, strlen(part1), strlen(SE) - strlen(part1), part2); // Copy part2
                    cpy_string(buf.table, j, lim - j, SI);                            // Copy shifted portion

                    sprintf(part2, "%s%s", part2, SI);
                    buf.table[j] = '\0';
                    sprintf(buf.table, "%s%s", buf.table, part1);

                    j += strlen(part1);
                    WriteBlock(file, i, buf);

                    if (i == header(file, 1))
                    {
                        SetHeader(file, 2, j);
                    }

                    if (strlen(part2) == 0)
                    {
                        break;
                    }

                    if (j >= lim)
                    {
                        i++;
                        j = j % lim;
                    }
                    sprintf(SE, "%s", part2); // Prepare SE for next iteration
                }
                else
                {
                    AllocBlock(file);
                    sprintf(buf.table, "%s", SE); // Insert remaining SE
                    j = strlen(SE);
                    SetHeader(file, 2, j);
                    WriteBlock(file, i, buf);
                    break;
                }
            }

            // Update file header for the total size
            SetHeader(file, 3, header(file, 3) + strlen(SE));
        }

        x++;
        k++;
    }
}
///-------------------------------------------------------------------------------------------------------------------------------------

/// Initial load TnOVC-------------------------------------------------------------------------------------------------------------------
void Initial_Load_TnOVC(TOVC *file, int num)
{
    int x = 0, k = 0;
    Record en;
    int i, j, found;
    StringRecord SE;
    Block buf;

    while (x < num)
    {
        // Input the key and data for the record
        sprintf(en.data, "%s", "");
        printf("\n n%c%d : key = ", 248, k);
        scanf("%d", &(en.key));
        printf("       data  = ");
        scanf("%s", en.data);
        en.eff = 0;

        // Inline the logic from insert_TnOVC
        i = 0;
        j = 0;
        found = 0;

        // Search for the position of the record with the given key
        Search_TnOVC(file, en.key, &i, &j, &found);

        if (!found)
        {
            // Convert the record to its string representation
            Rec_to_StringRec(en, SE);

            // Inline the logic for insertion
            while (1)
            {
                if (i <= header(file, 1))
                {
                    StringRecord part1, part2, SI; // Parts of the record for splitting
                    sprintf(buf.table, "%s", "");
                    sprintf(part2, "%s", "");
                    sprintf(SI, "%s", "");

                    // Read the current block
                    ReadBlock(file, i, &buf);

                    // Split the string record
                    cpy_string(SE, 0, lim - j, part1);                                // Extract part1
                    cpy_string(SE, strlen(part1), strlen(SE) - strlen(part1), part2); // Extract part2
                    cpy_string(buf.table, j, lim - j, SI);                            // Extract part of the block for shifting

                    // Concatenate the parts
                    sprintf(part2, "%s%s", part2, SI); // Prepare part2 for next insertion
                    buf.table[j] = '\0';
                    sprintf(buf.table, "%s%s", buf.table, part1); // Add part1 to the buffer

                    // Update the position
                    j += strlen(part1);
                    WriteBlock(file, i, buf);

                    if (i == header(file, 1))
                    {
                        SetHeader(file, 2, j);
                    }

                    if (strlen(part2) == 0)
                    {
                        break; // Stop if there's nothing more to insert
                    }

                    if (j >= lim)
                    {
                        i++;
                        j = j % lim; // Move to the next block
                    }

                    sprintf(SE, "%s", part2); // Update SE for the next iteration
                }
                else
                {
                    // Allocate a new block for the remaining data
                    AllocBlock(file);
                    sprintf(buf.table, "%s", SE); // Insert remaining SE
                    j = strlen(SE);
                    SetHeader(file, 2, j);
                    WriteBlock(file, i, buf);
                    break;
                }
            }

            // Update the file size in the header
            SetHeader(file, 3, header(file, 3) + strlen(SE));
        }

        // Move to the next record
        x++;
        k++;
    }
}

///-------------------------------------------------------------------------------------------------------------------------------------


///Concatenation Function: Merges the content of file2 into file1.---------------------------------------------------------------------------------------
void ConcatenateTOVC(TOVC *file1, TOVC *file2) {
    // Validate both files
    if (file1 == NULL || file2 == NULL) {
        printf("\033[31mError: One or both files are invalid.\033[0m\n"); // Red error message
        return;
    }

    printf("\n\033[36mStarting file concatenation...\033[0m\n");

    // Loop through all blocks in file2
    for (int i = 1; i <= header(file2, 1); i++) {
        Block buf;
        ReadBlock(file2, i, &buf); // Read the block from file2
        AllocBlock(file1);        // Allocate a new block in file1
        WriteBlock(file1, header(file1, 1), buf); // Write the block to file1
    }

    // Update metadata for file1
    SetHeader(file1, 3, header(file1, 3) + header(file2, 3)); // Add non-deleted record count
    SetHeader(file1, 4, header(file1, 4) + header(file2, 4)); // Add deleted record count

    printf("\033[32mFiles concatenated successfully!\033[0m\n\n"); // Green success message
    Printout_header(file1); // Print updated file1 header
}

///-------------------------------------------------------------------------------------------------------------------------------------


///Intersection Function: Finds common records between file1 and file2 and stores them in result_file.--------------------------------------------------------------
void Intersection_TOVC(TOVC *file1, TOVC *file2, TOVC *result_file) {
    // Validate input files
    if (file1 == NULL || file2 == NULL || result_file == NULL) {
        printf("\033[31mError: One or more files are invalid.\033[0m\n"); // Red error message
        return;
    }

    int i1 = 1, i2 = 1;         // Block indices for file1 and file2
    int j1 = 0, j2 = 0;         // Positions within current blocks of file1 and file2
    int i_res = 1, j_res = 0;   // Block and position for the result file
    StringRecord rec1, rec2;    // String representations of records
    Record en1, en2;            // Struct representations of records

    // Initialize result file headers
    SetHeader(result_file, 1, 1); // Start with one block
    SetHeader(result_file, 2, 0); // No characters written initially
    SetHeader(result_file, 3, 0); // No records yet

    printf("\n\033[36mStarting intersection...\033[0m\n");

    while (i1 <= header(file1, 1) && i2 <= header(file2, 1)) {
        // Read records from file1 and file2
        get_se(file1, &i1, &j1, rec1);
        StringRec_to_Rec(rec1, &en1);

        get_se(file2, &i2, &j2, rec2);
        StringRec_to_Rec(rec2, &en2);

        // Compare keys
        if (en1.key < en2.key) {
            if (j1 == header(file1, 2)) {
                i1++;
                j1 = 0;
            }
        } else if (en1.key > en2.key) {
            if (j2 == header(file2, 2)) {
                i2++;
                j2 = 0;
            }
        } else {
            // Keys match; check if records are not logically deleted
            if (en1.eff == 0 && en2.eff == 0) {
                insert_pos_rec(result_file, &i_res, &j_res, rec1);
                SetHeader(result_file, 3, header(result_file, 3) + 1); // Increment record count
                SetHeader(result_file, 2, header(result_file, 2) + strlen(rec1)); // Update character count
            }
            // Advance both files
            if (j1 == header(file1, 2)) {
                i1++;
                j1 = 0;
            }
            if (j2 == header(file2, 2)) {
                i2++;
                j2 = 0;
            }
        }
    }

    printf("\033[32mIntersection completed successfully!\033[0m\n\n");
    Printout_header(result_file); // Print header of result_file
    printout_file(result_file);   // Print contents of result_file
}

///-------------------------------------------------------------------------------------------------------------------------------------


/**___________________________________________ Affichage _________________________________________________**/

///BIENVENUE !! -----------------------------------------------------------------------------------------------------------------------------------///
    void Hello() {
    system("cls");
    printf("\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf("\n\n\n");
    printf("        ___________________________________________________________________________________________________________ \n");
    printf("       |                                                                                                           |\n");
    printf("       |  $$$$$$$$   $$$$   $$$$$$$$   $$    $$     $$  $$    $$$$$$$$   $$    $$   $    $   $$$$$$$$    ##   ##   |\n");
    printf("       |  $$      $   $$    $$         $ $   $$      $  $     $$         $ $   $$   $    $   $$          ##   ##   |\n");
    printf("       |  $$$$$$$$    $$    $$$$$$$$   $  $  $$      $  $     $$$$$$$$   $  $  $$   $    $   $$$$$$$$    ##   ##   |\n");
    printf("       |  $$      $   $$    $$         $   $ $$      $  $     $$         $   $ $$   $    $   $$                    |\n");
    printf("       |  $$$$$$$$   $$$$   $$$$$$$$   $    $$$       $$      $$$$$$$$   $    $$$   $$$$$$   $$$$$$$$    ##   ##   |\n");
    printf("       |___________________________________________________________________________________________________________|\n\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("\n");
    printf("                                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
    printf("                                %c     Notre programme vous donne la possibilite de    %c\n", 186, 186);
    printf("                                %c     bien manipuler les fichiers scolaires d'une     %c\n", 186, 186);
    printf("                                %c     ecole  primaire  a l'aide de deux structures !  %c\n", 186, 186);
    printf("                                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
    printf(" \n\n                                     Appuyer sur la touche ENTRER  pour continuer ! ");
    getchar();

    ///-----------------------------------------------------------------------------------------------------------------------------------///

    system("cls");
    printf("\n\n\n\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("                       %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 203, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
    printf("                       %c                                    %c                                   %c\n", 186, 186, 186);
    printf("                       %c    $$$$$$$     $$$$$$$$$     $$    %c         DAOUI KAOUTAR             %c\n", 186, 186, 186);
    printf("                       %c    $$          $$                  %c         BOURGUIG LEILASERINE      %c\n", 186, 186, 186);
    printf("                       %c    $$$$$$$     $$$$$$$$$     $$    %c         GROUPE : 02               %c\n", 186, 186, 186);
    printf("                       %c    $$                 $$     $$    %c         2024|2025                 %c\n", 186, 186, 186);
    printf("                       %c    $$$$$$$     $$$$$$$$$     $$    %c                                   %c\n", 186, 186, 186);
    printf("                       %c                                    %c                                   %c\n", 186, 186, 186);
    printf("                       %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 202, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("                                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
    printf("                                %c   ECOLE   NATIONALE   SUPERIEURE   D'INFORMATIQUE   %c\n", 186, 186);
    printf("                                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    printf("                                         Merci d'avoir choisir notre application ! ");
    printf(" \n\n                                       Appuyer sur la touche ENTRER  pour continuer ! ");
    getchar();
    }



void bye(){
    system("cls");

    printf("\n\n\n\n\n");

    // Set cyan text color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);

    // Top border
    printf("                       ");
    for (int i = 0; i < 74; i++) printf("%c", i == 37 ? 203 : 205);
    printf("\n");

    // Empty row inside the box
    printf("                       %c%72s%c\n", 186, "", 186);
    // Thank-you message
    printf(  "\033[36m""                       %c                     THANK YOU FOR USING OUR PROGRAM!                   %c\n", 186, 186);

    // Empty row inside the box
    printf("                       %c%72s%c\n", 186, "", 186);

    // Bottom border
    printf("                       ");
    for (int i = 0; i < 74; i++) printf("%c", i == 37 ? 202 : 205);
    printf("\n");

    // Reset text color to default
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    getchar();
}


