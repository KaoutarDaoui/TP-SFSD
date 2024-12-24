#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "functions.h"
#include "functions.c"

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
#define BRIGHT_BLUE "\033[94m"
#define LIGHT_BLUE "\033[36m"

#define BOLD "\033[1m"

#define BG_WHITE "\033[48;5;7m"



///-------------------------------------------------------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------------------------------------------------------///
///-------------------------------------------------------------------------------------------------------------------------------------///
///------------------------------------------------------  M   E   N   U  --------------------------------------------------------------///
///-------------------------------------------------------------------------------------------------------------------------------------///
///-------------------------------------------------------------------------------------------------------------------------------------///

int main()
{
    system("title manipulation files de type TOVC / TnOVC");
    char namef[30];
    int k, i, j, key, found, choice, choice1, choice2,choice3;
    Block buf;
    TOVC *file ,*fileOld , *file1, *file2 , *result_file ;
    Record en;
    StringRecord se;

    ///BIENVENUE !! -----------------------------------------------------------------------------------------------------------------------------------///

    Hello();

    ///-----------------------------------------------------------------------------------------------------------------------------------///

menuprincipal:
    system("cls");

    printf("\n                                                                                                    ");
    printf("\n                                                                                                         ");
    printf(CYAN BOLD "\n                                         P R I N C I P L E       M E N U                            " RESET);
    printf("\n                                                                                              ");
    printf(CYAN "\n\n             ____________________________________________________________________________________________" RESET);
    Sleep(100);
    printf(CYAN "\n            |  ________________________________________________________________________________________  |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |                                                                                        | |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |             ___                                                                        | |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |            |   |                                                                       | |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |            |" RESET);
    printf(BOLD " 1" RESET);
    printf(CYAN " |        " RESET);
    printf(BOLD "Creation of a new file                                         " RESET);
    printf(CYAN "| |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |            |___|                                                                       | |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |             ___                                                                        | |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |            |   |                                                                       | |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |            |" RESET);
    printf(BOLD " 2 " RESET);
    printf(CYAN "|        " RESET);
    printf(BOLD "Visualisation of an existant file                              " RESET);
    printf(CYAN "| |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |            |___|                                                                       | |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |             ___                                                                        | |" RESET);
    printf(CYAN "\n            | |            |   |                                                                       | |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |            | " RESET);
    printf(BOLD "0 " RESET);
    printf(CYAN "|        " RESET);
    printf(BOLD "EXIT                                                           " RESET);
    printf(CYAN "| |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |            |___|                                                                       | |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |                                                                                        | |" RESET);
    Sleep(100);
    printf(CYAN "\n            | |________________________________________________________________________________________| |" RESET);
    Sleep(100);
    printf(CYAN "\n            |____________________________________________________________________________________________|" RESET);

    printf("\n\n\n YOUR CHOICE : ");
    scanf("%d", &choice);

    ///-----------------------------------------------------------------------------------------------------------------------------------///

    switch (choice)
    {
    case 0: // fin programme ;
    {
        goto end;
    }
    case 1: // new file
    {

        system("cls");
        printf("\n                                                                                                    ");
        printf("\n                                                                                                         ");
        printf(CYAN "\n                                    C R E A T I O N    O F    A    F I L E                             " RESET);
        printf("\n                                                                                              ");
        printf(CYAN "\n\n             ____________________________________________________________________________________________" RESET);
        Sleep(100);
        printf(CYAN "\n            |  ________________________________________________________________________________________  |" RESET);
        Sleep(100);
        printf(CYAN "\n            | |                                                                                        | |" RESET);
        Sleep(100);
        printf("\n            | |              ");
        printf(YELLOW "_____                                    _____                            " RESET);
        printf(CYAN "| |" RESET);
        Sleep(100);
        printf(CYAN "\n            | |             " RESET);
        printf(YELLOW "|_____\\______                            |_____\\_____                      " RESET);
        printf(CYAN "| |" RESET);
        Sleep(100);
        printf(CYAN "\n            | |             " RESET);
        printf(YELLOW "|             |                          |             |                   " RESET);
        printf(CYAN "| |" RESET);
        Sleep(100);
        printf(CYAN "\n            | |             " RESET);
        printf(YELLOW "| " RESET);
        printf(BOLD "1-TOVC      " RESET);
        printf(YELLOW "|                          | " RESET);
        printf("2-TnOVC     ");
        printf(YELLOW "|                   " RESET);
        printf(CYAN "| |" RESET);
        Sleep(100);
        printf(CYAN "\n            | |             " RESET);
        printf(YELLOW "|_____________|                          |_____________|                   " RESET);
        printf(CYAN "| |" RESET);
        Sleep(100);
        printf(CYAN "\n            | |                                                                                        | |" RESET);
        Sleep(100);
        printf(CYAN "\n            | |                                                                                        | |" RESET);
        Sleep(100);
        printf(CYAN BOLD "\n            | |                                     0 - EXIT                                           | |" RESET);
        Sleep(100);
        printf(CYAN "\n            | |________________________________________________________________________________________| |" RESET);
        Sleep(100);
        printf(CYAN "\n            |____________________________________________________________________________________________|" RESET);

        printf("\n\n\n YOUR CHOICE : ");
        scanf("%d", &choice2);

        switch (choice2)
        {
        case 0: //  ;
        {
            goto end;
        }
        case 1: // new file TOVC
        {

            printf(" Enter a name for the file : ");
            scanf("%s", namef);
            file = Open(namef, 'N');

        manipulation_file:

           system("cls");

    printf(CYAN"                                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"RESET, 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
    printf(CYAN"                                %c                                                     %c\n"RESET, 186, 186);
    printf(CYAN"                                %c                   MENU PRINCIPALE                   %c\n"RESET, 186, 186);
    printf(CYAN"                                %c                                                     %c\n"RESET, 186, 186);
    printf(CYAN"                                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"RESET, 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);


    printf("\n\n                         [1]  : InitialLoad \n");
    printf("                         [2]  : Display the header of the file \n");
    printf("                         [3]  : Display the content of the entire data file \n");
    printf("                         [4]  : Display the content of a specific block \n");
    printf("                         [5]  : Display the overlapping information in the data file \n");
    printf("                         [6]  : Insertion \n");
    printf("                         [7]  : Search \n");
    printf("                         [8]  : Logical deletion \n");
    printf("                         [9]  : Physical deletion \n");
    printf("                         [10] : Display \n");
    printf("                         [11] : Reorganization \n");
    printf("                         [12] : Leaving the program \n");
    printf("                         [0]  : Principal menu \n");

    printf("\n\n                         Your choice : ") ;

           scanf("%d", &choice1);


            switch (choice1)
            {
            case 0: // retour au menu principal
            {
                close(file);
                goto menuprincipal;
            }

            case 1: // initial load
            {
                system("cls");
                int nbr;
                printf(CYAN "\n\n\n ____________________________________________________________________________________\n");
                printf(CYAN BOLD"\n  INITIAL LOAD :");
                printf(CYAN"\n ____________________________________________________________________________________\n\n\n" RESET);
                printf(" Number of records that you want to add to your file : ");
                scanf("%d", &nbr);
                Initial_Load_TOVC(file, nbr);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file;
            }

             case 2: // DISPLAY THE HEADER OF THE FILE
            {
                system("cls");
                printf(CYAN "\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD "\n  DISPLAY THE HEADER OF THE FILE :");
                printf(CYAN"\n ______________________________________________________________________________\n\n" RESET);
                Printout_header(file);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file;
            }

             case 3: // DISPLAY THE CONTENT OF THE ENTIRE DATA FILE
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY THE CONTENT OF THE ENTIRE DATA FILE :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                printout_file(file);
                Printout_block(file);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file;
            }

            case 4: // DISPLAY THE CONTENT OF A SPECIFIC BLOCK
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY THE CONTENT OF A SPECIFIC BLOCK :");
                printf(CYAN"\n ______________________________________________________________________________\n\n" RESET);
                Printout_specific_block(file);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file;
            }

             case 5: // DISPLAY ALL THE OVERLAPPING INFORMATION IN THE DATA FILE:
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY ALL THE OVERLAPPING INFORMATION IN THE DATA FILE:");
                printf(CYAN"\n ______________________________________________________________________________\n\n" RESET);
                Printout_overlapping(file);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file;
            }
            case 6: // insertion
            {
                system("cls");
                int nbr;
                printf(CYAN"\n\n\n ____________________________________________________________________________________\n");
                printf(CYAN BOLD"\n  INSERTION :");
                printf(CYAN"\n ____________________________________________________________________________________\n\n\n" RESET);
                printf(" Number of records that you want to insert : ");
                scanf("%d", &nbr);
                for (k = 0; k < nbr; k++)
                {
                    sprintf(en.data, "%s", "");

                    printf("\n n%c%d : key = ", 248, k);
                    scanf("%d", &(en.key));

                    printf("       data  = ");
                    scanf("%s", en.data);

                    en.eff = 0;
                    insert_TOVC(file, en);
                }
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file;
            }

            case 7: //SEARCH
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  SEARCH :");
                printf(CYAN"\n ______________________________________________________________________________\n\n\n"RESET);
                printf(" Enter the key that you want to search for : ");
                scanf("%d", &key);
                Search_TnOVC(file, key, &i, &j, &found);
                if (!found)
                {
                    printf("Result : The key %d does not exist in the file", key);
                }
                else
                {
                    printf(" Result : block %d, position %d\n", i, j);
                }

                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file;
            }
            case 8: // LOGICAL DELETION
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  LOGICAL DELETION :");
                printf(CYAN"\n ______________________________________________________________________________\n\n\n"RESET);
                printf(" Enter the key that you wish deleting : ");
                scanf("%d", &key);
                delete_Log_TOVC(file, key);

                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file;
            }
            case 9: // PHYSICAL DELETION
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  PHYSICAL DELETION :");
                printf(CYAN"\n ______________________________________________________________________________\n\n\n"RESET);
                printf(" Enter the key that you wish deleting : ");
                scanf("%d", &key);
                delete_phy_TOVC(file, key);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file;
            }
            case 10: // DISPLAY
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                Printout_header(file);
                printout_file(file);
                Printout_block(file);
                Printout_overlapping(file);

                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file;
            }
            case 11: // REORGANIZATION
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  REORGANIZATION :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);

                int k1 = header(file, 4);
                float k2 = header(file, 3);
                printf("reo = %f", k1 / k2);
                if (k1 / k2 >= 0.5)
                {
                    Reorganize_TOVC(file, "file_reo");
                }


                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file;
            }
            case 12:
                bye();
            }
        }
        case 2://New file TnOVC
        {
            printf(" Enter the name of the file : ");
            scanf("%s", namef);
            file = Open(namef, 'N');
        manipulation_file2:

            system("cls");

    printf(CYAN"                                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"RESET, 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
    printf(CYAN"                                %c                                                     %c\n"RESET, 186, 186);
    printf(CYAN"                                %c                   MENU PRINCIPALE                   %c\n"RESET, 186, 186);
    printf(CYAN"                                %c                                                     %c\n"RESET, 186, 186);
    printf(CYAN"                                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"RESET, 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);


    printf("\n\n                         [1]  : InitialLoad \n");
    printf("                         [2]  : Display the header of the file \n");
    printf("                         [3]  : Display the content of the entire data file \n");
    printf("                         [4]  : Display the content of a specific block \n");
    printf("                         [5]  : Display the overlapping information in the data file \n");
    printf("                         [6]  : Insertion \n");
    printf("                         [7]  : Search \n");
    printf("                         [8]  : Logical deletion \n");
    printf("                         [9]  : Physical deletion \n");
    printf("                         [10] : Display \n");
    printf("                         [11] : Reorganization \n");
    printf("                         [12] : Leaving the program \n");
    printf("                         [0]  : Principal menu \n");

    printf("\n\n                         Your choice : ") ;


    printf("Your choice : ") ;

           scanf("%d", &choice1);


            switch (choice1)
            {
            case 0: // retour au menu principal
            {
                close(file);
                goto manipulation_file2;
            }

            case 1: // initial load
            {
                system("cls");
                int nbr;
                printf(CYAN"\n\n\n ____________________________________________________________________________________\n");
                printf(CYAN BOLD"\n  INITIAL LOAD :");
                printf(CYAN"\n ____________________________________________________________________________________\n\n\n"RESET);
                printf(" Number of records that you want to add to your file : ");
                scanf("%d", &nbr);
                Initial_Load_TnOVC(file, nbr);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file2;
            }

             case 2: // DISPLAY THE HEADER OF THE FILE
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY THE HEADER OF THE FILE :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                Printout_header(file);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file2;
            }

             case 3: // DISPLAY THE CONTENT OF THE ENTIRE DATA FILE
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY THE CONTENT OF THE ENTIRE DATA FILE :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                printout_file(file);
                Printout_block(file);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file2;
            }

            case 4: //  DISPLAY THE CONTENT OF A SPECIFIC BLOCK
                {
                printf("\n") ;
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY THE CONTENT OF A SPECIFIC BLOCK :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                Printout_specific_block(file);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file2;
            }

             case 5: // DISPLAY ALL THE OVERLAPPING INFORMATION IN THE DATA FILE
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY ALL THE OVERLAPPING INFORMATION IN THE DATA FILE:");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                Printout_overlapping(file);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file2;
            }
            case 6: // insertion
            {
                system("cls");
                int nbr;
                printf(CYAN"\n\n\n ____________________________________________________________________________________\n");
                printf(CYAN BOLD"\n  INSERTION :");
                printf(CYAN"\n ____________________________________________________________________________________\n\n\n"RESET);
                printf(" Number of records that you want to insert : ");
                scanf("%d", &nbr);
                for (k = 0; k < nbr; k++)
                {
                    sprintf(en.data, "%s", "");

                    printf("\n n%c%d : key = ", 248, k);
                    scanf("%d", &(en.key));

                    printf("       data  = ");
                    scanf("%s", en.data);

                    en.eff = 0;
                    insert_TnOVC(file, en);
                }
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file2;
            }

            case 7: // SEARCH
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  SEARCH :");
                printf(CYAN"\n ______________________________________________________________________________\n\n\n"RESET);
                printf(" Enter the key that you want to search for : ");
                scanf("%d", &key);
                Search_TnOVC(file, key, &i, &j, &found);
                if (!found)
                {
                    printf("Result : The key %d does not exist in the file", key);
                }
                else
                {
                    printf(" Result : block %d, position %d\n", i, j);
                }

                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file2;
            }
            case 8: // LOGICAL DELETION
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  LOGICAL DELETION :");
                printf(CYAN"\n ______________________________________________________________________________\n\n\n"RESET);
                printf(" Enter the key that you wish deleting : ");
                scanf("%d", &key);
                delete_Log_TnOVC(file, key);

                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file2;
            }
            case 9: // PHYSICAL DELETION.
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  PHYSICAL DELETION :");
                printf(CYAN"\n ______________________________________________________________________________\n\n\n"RESET);
                printf(" Enter the key that you wish deleting : ");
                scanf("%d", &key);
                delete_phy_TnOVC(file, key);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file2;
            }
            case 10: // DISPLAY
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                Printout_header(file);
                printout_file(file);
                Printout_block(file);
                Printout_overlapping(file);

                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file2;
            }
            case 11: // REORGANIZATION
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  REORGANIZATION :");
                printf("\n ______________________________________________________________________________\n\n"RESET);

                int k1 = header(file, 4);
                float k2 = header(file, 3);
                printf("reo = %f", k1 / k2);
                if (k1 / k2 >= 0.5)
                {
                    Reorganize_TOVC(file, "file_reo");
                }


                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file2;
            }
            case 12 :
                bye();
            }
        }
        }
        }
    case 2: // ancien file
    {
        system("cls");
        printf(CYAN"\n\n\n ______________________________________________________________________________\n");
        printf(CYAN BOLD"\n  OUVERTURE file :");
        printf(CYAN"\n ______________________________________________________________________________\n\n\n"RESET);
        printf(" Veuillez donner le nom de votre file : ");
        scanf("%s", namef);
        fileOld = Open(namef, 'o');

        if (fileOld == NULL)
            {
             printf("Error: Could not open file %s.\n", namef);
             return -1;
            }
        system("cls");
        manipulation_file3:

    printf(CYAN"                                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"RESET, 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
    printf(CYAN"                                %c                                                     %c\n"RESET, 186, 186);
    printf(CYAN"                                %c                   MENU PRINCIPALE                   %c\n"RESET, 186, 186);
    printf(CYAN"                                %c                                                     %c\n"RESET, 186, 186);
    printf(CYAN"                                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"RESET, 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);


    printf("\n\n                         [1]  : Display the header of the file \n");
    printf("                         [2]  : Display the content of the entire data file \n");
    printf("                         [3]  : Display the content of a specific block \n");
    printf("                         [4]  : Display the overlapping information in the data file \n");
    printf("                         [5]  : Insertion \n");
    printf("                         [6]  : Search \n");
    printf("                         [7]  : Logical deletion \n");
    printf("                         [8]  : Physical deletion \n");
    printf("                         [9] : Display \n");
    printf("                         [10] : Reorganization \n");
    printf("                         [11] : Concatenation of two existent files \n");
    printf("                         [12] : intersection \n");
    printf("                         [13] : Leaving the program \n");
    printf("                         [0]  : EXIT \n");

    printf("\n\n                         Your choice : ") ;


    printf("Your choice : ") ;
        scanf("%d", &choice3);

            switch (choice3)
            {
            case 0:
            {
                close(fileOld);
                goto menuprincipal;
            }

             case 1: // DISPLAY THE HEADER OF THE FILE
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY THE HEADER OF THE FILE :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                Printout_header(fileOld);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file3;
            }

             case 2: // DISPLAY THE CONTENT OF THE ENTIRE DATA FILE
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY THE CONTENT OF THE ENTIRE DATA FILE :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                printout_file(fileOld);
                Printout_block(fileOld);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file3;
            }

            case 3: // DISPLAY THE CONTENT OF A SPECIFIC BLOCK
            {
                system("cls");
                printf("\n\n\n ______________________________________________________________________________\n");
                printf("\n  DISPLAY THE CONTENT OF A SPECIFIC BLOCK :");
                printf("\n ______________________________________________________________________________\n\n");
                Printout_specific_block(fileOld);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file3;
            }

             case 4: // DISPLAY ALL THE OVERLAPPING INFORMATION IN THE DATA FILE
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY ALL THE OVERLAPPING INFORMATION IN THE DATA FILE:");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                Printout_overlapping(fileOld);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file3;
            }
            case 5: // insertion
            {
                system("cls");
                int nbr;
                printf(CYAN"\n\n\n ____________________________________________________________________________________\n");
                printf(CYAN BOLD"\n  INSERTION :");
                printf(CYAN"\n ____________________________________________________________________________________\n\n\n"RESET);
                printf(" Number of records that you want to insert : ");
                scanf("%d", &nbr);
                for (k = 0; k < nbr; k++)
                {
                    sprintf(en.data, "%s", "");

                    printf("\n n%c%d : key = ", 248, k);
                    scanf("%d", &(en.key));

                    printf("       data  = ");
                    scanf("%s", en.data);

                    en.eff = 0;
                    insert_TOVC(fileOld, en);
                }
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file3;
            }

            case 6: // SEARCH
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  SEARCH :");
                printf(CYAN"\n ______________________________________________________________________________\n\n\n"RESET);
                printf(" Enter the key that you want to search for : ");
                scanf("%d", &key);
                Search_TnOVC(fileOld, key, &i, &j, &found);
                if (!found)
                {
                    printf("Result : The key %d does not exist in the file", key);
                }
                else
                {
                    printf(" Result : block %d, position %d\n", i, j);
                }

                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file3;
            }
            case 7: // LOGICAL DELETION
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  LOGICAL DELETION :");
                printf(CYAN"\n ______________________________________________________________________________\n\n\n"RESET);
                printf(" Enter the key that you wish deleting : ");
                scanf("%d", &key);
                delete_Log_TOVC(fileOld, key);

                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file3;
            }
            case 8: // PHYSICAL DELETION
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  PHYSICAL DELETION :");
                printf(CYAN"\n ______________________________________________________________________________\n\n\n"RESET);
                printf(" Enter the key that you wish deleting : ");
                scanf("%d", &key);
                delete_phy_TOVC(fileOld, key);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file3;
            }
            case 9: // DISPLAY
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  DISPLAY :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                Printout_header(fileOld);
                printout_file(fileOld);
                Printout_block(fileOld);
                Printout_overlapping(fileOld);

                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file3;
            }
            case 10: // REORGANIZATION
            {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  REORGANIZATION :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);

                int k1 = header(fileOld, 4);
                float k2 = header(fileOld, 3);
                printf("reo = %f", k1 / k2);
                if (k1 / k2 >= 0.5)
                {
                    Reorganize_TOVC(fileOld, "file_reo");
                }


                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file3;
            }
            case 11: //Concatination
                {

                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  CONCATINATION :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                // Get file names from user input
                printf("Give the two files that you want to concatenate: \n");
                printf("Enter first file name: ");
                scanf("%s", file1);  // Get file name for the first file
                printf("Enter second file name: ");
                scanf("%s", file2);  // Get file name for the second file
                ConcatenateTOVC(&file1, &file2);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file3;
            }
            case 12:
                {
                system("cls");
                printf(CYAN"\n\n\n ______________________________________________________________________________\n");
                printf(CYAN BOLD"\n  INTERSECTION :");
                printf(CYAN"\n ______________________________________________________________________________\n\n"RESET);
                // Get file names from user input
                printf("Give the two files that you want to find intersection for: \n");
                printf("Enter first file name: ");
                scanf("%s", file1);  // Get file name for the first file
                printf("Enter second file name: ");
                scanf("%s", file2);  // Get file name for the second file

                // Call the function to find the intersection
                Intersection_TOVC(&file1, &file2, &result_file);
                printf("\n");
                system("pause");
                system("cls");
                goto manipulation_file3;
            }
            case 13:
                {
                bye();
                }

    }
    }

end:
    return 0;
}
}
