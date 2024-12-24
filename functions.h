
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#define lim 30
#define MAX_KEY 3
#define MAX_LEN 3
/// structure of the header ------------------------------------------------------------------------------------------------------------
typedef struct Header
{
    int LasBlock;   /// number of blocks
    int FreePos;    /// first free position in the last block
    int NB_data;    /// non-deleted records
    int NB_deleted; /// number of deleted records >> if 50% => Reorganize file
} Header;
///------------------------------------------------------------------------------------------------------------------------------------


/// structure of a block --------------------------------------------------------------------------------------------------------------
typedef struct Block
{
    char table[lim + 1]; /// the data stored in the file , The lim+1 allows space for a null terminator ('\0')
    int last_pos;        /// position of the last key in a block
} Block;
///------------------------------------------------------------------------------------------------------------------------------------


/// structure of a file of a type TOVC/TnOVC ------------------------------------------------------------------------------------------
typedef struct TOVC
{
    FILE *f;
    Header header;
} TOVC;
///------------------------------------------------------------------------------------------------------------------------------------

/// structures of StringRecords -------------------------------------------------------------------------------------------------------
typedef char StringRecord[lim + 1]; /// Character string that will contain the data for retrieve_str and write_str

/// structure of a record -------------------------------------------------------------------------------------------------------------
typedef struct Record
{
    /* length of the data => 4 characters*/
    int key;            /// 4 characters
    int eff;            /// boolean (logically deleted)
    char data[lim - 6]; /// Remaining space for data, allowing for a maximum length of Record (6 = length of key + length of eff + 1 for null terminator)
} Record;
///------------------------------------------------------------------------------------------------------------------------------------

/**___________________________________________          HEAD OF FUNCTIONS        ____________________________________________________________**/

/// header: returns the characteristic i of the TOVC/TnOVC file -----------------------------------------------------------------------
int header(TOVC *file, int i) ;

/// SetHeader: allows assigning x to the chosen characteristic i of the TOVC/TnOVC file -----------------------------------------------
void SetHeader(TOVC *file, int i, int x) ;

/// Open: allows opening a file and returning a pointer of type TOVC/TnOVC ------------------------------------------------
TOVC *Open(char namef[30], char mode) ;

/// close: allows closing a file of type TOVC -------------------------------------------------------------------------------------
void close(TOVC *file) ;

/// WriteBlock: allows writing the buffer buf to the i-th block of a TOVC file --------------------------------------------------
void WriteBlock(TOVC *file, int i, Block buf) ;

/// ReadBlock: allows reading the i-th block from the TOVC file pointed to by file into the buffer buf --------------------------
void ReadBlock(TOVC *file, int i, Block *buf) ;

/// AllocBlock: allows allocating a new block -----------------------------------------------------------------------------------
void AllocBlock(TOVC *file) ;

/// int_to_string: transforms an integer num into a string s with a maximum length >>The difference is filled with zeros-------------
void int_to_string(int num, int max, char *s) ;

/// cpy_string: copies from string s starting at position i, to a substring r with a maximum length -----------------------------
void cpy_string(char *s, int i, int max, char *r) ;

/// cut_string: allows removing a portion of the string s with a maximum length starting from position i ------------------------
void cut_string(char *s, int i, int max) ;

/// StringRec_to_Rec: transforms a StringRecord into a Record >> Utility: facilitates data manipulation --------------------------
void StringRec_to_Rec(StringRecord se, Record *en) ;

/// Rec_to_StringRec: allows transforming a Record into a StringRecord  =/ StringRec_to_Rec ----------------------------------------------------------
void Rec_to_StringRec(Record en, StringRecord se) ;

/// get_se: retrieves a Record from the file and places it in the variable `se`
void get_se(TOVC *file, int *i, int *j, StringRecord se)  ;

/// Printout_header: displays the header of the file ----------------------------------------------------------------------------
void Printout_header(TOVC *file) ;

/// Printout_block: displays the contents of all blocks  ----------------------------------------------------------------------------
void Printout_block(TOVC *file)  ;

/// Printout_specific_block: displays the contents of block i which have been specified by the user -----------------------------
void Printout_specific_block(TOVC *file) ;

/// printout_file: allows displaying the Records from the file ------------------------------------------------------------------
void printout_file(TOVC *file) ;

/// Printout_overlapping: allows displaying overlapping Records ----------------------------------------
void Printout_overlapping(TOVC *file)  ;

/// Search_TnOVC: searches within the file (We traverse our file sequentially and compare the searched key with all keys) ----------------------------
void Search_TnOVC(TOVC *file, int key, int *i, int *j, int *found) ;

/// string_to_record--------------------------------------------------------------------------------------------------------------
void string_to_record(char *source, int pos, Record *rec);

/// Search in the file :We traverse our file dichotomously and compare the searched key to all keys--------------------------------------------
void Search_TOVC(TOVC *file, int key, int *i, int *j, int *found) ;

/// Performs the logical deletion of a Record, setting the eff field to 1 --------------------------------------------------------------
void delete_Log_TnOVC(TOVC *file, int key)  ;

/// Performs the logical deletion of a Record, setting the eff field to 1 --------------------------------------------------------------
void delete_Log_TOVC(TOVC *file, int key) ;

/// Performs physical deletion in the file -----------------------------------------------------------------------------
void delete_phy_TOVC(TOVC *file, int key)  ;

/// Performs physical deletion in the file -----------------------------------------------------------------------------
void delete_phy_TnOVC(TOVC *file, int key) ;

/// Inserts SE into block i at position j ---------------------------------------------------------------------------------
void insert_pos_rec(TOVC *file, int *i, int *j, StringRecord SE)  ;

/// Allows the insertion in TnOVC ------------------------------------------------------------------------------------------------------
void insert_TnOVC(TOVC *file, Record E)  ;

/// Insertion into the file --------------------------------------------------------------------------------------------------------
void insert_TOVC(TOVC *file, Record E) ;

/// Reorganizes the file ---------------------------------------------------------------------------------------------------------------
void Reorganize_TOVC(TOVC *file, char *new_file) ;

/// Initial load TOVC--------------------------------------------------------------------------------------------------------------------
void Initial_Load_TOVC(TOVC *file, int num) ;

/// Initial load TnOVC-------------------------------------------------------------------------------------------------------------------
void Initial_Load_TnOVC(TOVC *file, int num)  ;

///Concatenation------------------------------------------------------------------------------------------------------------------------
void ConcatenateTOVC(TOVC *file1, TOVC *file2)  ;

///Intersection: Finds common records between file1 and file2 and stores them in result_file.--------------------------------------------------------------
void Intersection_TOVC(TOVC *file1, TOVC *file2, TOVC *result_file) ;



/**___________________________________ Affichage __________________________________________**/

void Hello() ;
void bye() ;



#endif // FUNCTIONS_H_INCLUDED
