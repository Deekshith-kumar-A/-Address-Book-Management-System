/*
Name    : Deekshith Kumar A
Date    : 23/09/2025
Project : Address Book
Language: C

********Address Book Management System********

1. Project Overview

        The Address Book Management System is a C-based console application designed to manage a collection of contact details.
        Key features include adding, viewing, searching, editing, and deleting contacts.

        It allows users to:

        1. Add new contacts
        2. View existing contacts in a tabular format
        3. Search for specific contacts
        4. Edit or delete contacts
        5. Save contacts to a file and reload
        6. Save and exit

3. Features

    1. Add Contacts

        Create a new contact by entering:

        Name: Alphabets and spaces only.
        Mobile Number: Must be exactly 10 digits.
        Email ID: Must follow the format name@domain.com.
        Validates inputs and ensures:
        No duplicate mobile numbers.
        No duplicate email IDs.

    2. List Contacts

        Displays all stored contacts in a tabular, sorted format (sorted by Name).

    3. Search Contacts

        Allows searching by:

        Name
        Mobile Number
        Email ID
        Displays details of matching contacts.
        Supports selecting and viewing multiple matches.

    4. Edit Contacts

        Enables editing:

        Name
        Mobile Number
        Email ID
        All details at once.
        Ensures updated details remain unique and valid.


    5. Delete Contacts

        Delete a contact by searching via Name, Mobile Number, or Email ID.
        Handles deletion of multiple matches and shifts remaining records.

    6. Save & Load

        Contacts are saved to a text file (data.txt).
        Data is automatically loaded at program startup to preserve changes between sessions.

    7. Save and Exit

        Saves all contacts to the file and exits the program gracefully.
    

4. Usage Instructions
    
    1. Compile the program using a C compiler (e.g., gcc).
    2. Run the compiled executable.
    3. Follow on-screen prompts to navigate the menu and perform actions.
    4. Enter valid inputs as per the specified formats.
    5. To exit, choose the "Save and Exit" option from the menu.

5.User Interface

    Blue: Section headers.
    Yellow: User prompts.
    Green: Success messages.
    Red: Error messages.

6. Error Handling

    The program includes robust error handling to manage invalid inputs, duplicate entries, and file I/O issues.
    User-friendly messages guide users to correct errors.

7. Dependencies

    Standard C libraries (stdio.h, stdlib.h, string.h, etc.)
    No external libraries are required.

8. Future Enhancements

    1. Implement a graphical user interface (GUI) for better user experience.
    2. Add functionality to import/export contacts in various formats (CSV, vCard).
    3. Add more fields to contacts (address, birthday, notes, etc.).
    4. Enhance search functionality with partial matches and filters.

*/


#include <stdio.h>
#include "contact.h"

int main()
{
    /* Variable and structre defintion */
    int option;
    AddressBook addressbook;
    addressbook.contact_count = 0;

    init_intitalization(&addressbook);

    while (1)
    {
        printf("\n\033[1;34m----Address book menu----\n\033[0m");/* Give a prompt message for a user */
        printf("\n");
        printf("\033[1;35m1.Add contact\n2.Search contact\n3.Edit contact\n4.Delete contact\n5.Display contact\n6.Save contact\n7.Exit\n\033[0m");
        printf("\n");
        printf("\033[1;34mEnter the option : \033[0m");
        printf("\n");
        scanf("%d", &option);
        getchar();

        switch (option) /* Based on choosed option */
        {
            case 1:
            
                create_contact(&addressbook);
                break;

            case 2:
            
                search_contacts(&addressbook);
                break;
            
            case 3:

                edit_contact(&addressbook);
                break;

            case 4:
            
                delete_contact(&addressbook);
                break;
        
            case 5:
            

                list_contacts(&addressbook);
                break;
            

            case 6:
                printf("Saving contacts\n");
                save_contacts(&addressbook);
                break;

            case 7:
                
                save_and_exit(&addressbook); // exit(0);
                return 0;

            default:
                printf("\033[1;31m***Enter a valid option***\033[0m \n");
                break;
        }
    }
    return 0;
}
