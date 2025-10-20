#include "contact.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* Function definitions */
// void init_intitalization(AddressBook *addressbook)
// {
// }

// valid name

int is_valid_name(const char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ')) // if(isalpha(name[i]) == 0 || name[i] == ' ')

        {
            return 0; // Invalid character found
        }
    }
    return 1; // All characters are valid
}

// valid mobile number

int is_valid_mobile(const char *mobile)
{
    int length = strlen(mobile);
    if (length != 10)
    {
        return 0; // Mobile number must be exactly 10 digits
    }
    for (int i = 0; i < length; i++)
    {
        if (mobile[i] < '0' || mobile[i] > '9') // if (!isdigit((unsigned char)mobile[i])) // from <ctype.h>
            return 0;
    }
    return 1; // Valid mobile number
}

// check is unique number or not

int is_unique_number(AddressBook *addressbook, const char *mobile)
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (strcmp(addressbook->contact_details[i].Mobile_number, mobile) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int is_unique_number_for_edit(AddressBook *addressbook, const char *mobile, int index)
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (i != index && strcmp(addressbook->contact_details[i].Mobile_number, mobile) == 0)
            return 0; // Duplicate found
    }
    return 1; // Unique  
}

// check mail is valid

int is_valid_email(const char *email)
{
    int at_position = -1;
    int dot_position = -1;
    int length = strlen(email);

    for (int i = 0; i < length; i++)
    {
        if (!(email[i] >= 'a' && email[i] <= 'z' || email[i] >= '0' && email[i] <= '9' || email[i] == '@' || email[i] == '.' || email[i] == '_'))
        {
            return 0;
        }

        if (email[i] == '@')
        {
            if (at_position != -1)
            {
                return 0; // More than one '@' found
            }
            at_position = i;
        }

        if (email[i] == '.')
        {
            if (dot_position != -1)
            {
                return 0; // More than one '.' found
            }
            dot_position = i;
        }
    }
    // Check if '@' and '.' are in valid positions
    if (at_position <= 0 || dot_position == -1 || at_position > dot_position || dot_position >= length - 1 || dot_position - at_position <= 1)
    {
        return 0; // Invalid email format
    }

    return 1; // Valid email format
}

// check mail id is unique

int is_unique_email(AddressBook *addressbook, const char *email)
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (strcmp(addressbook->contact_details[i].Mail_ID, email) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int is_unique_email_for_edit(AddressBook *addressbook, const char *email, int index)
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (i != index && strcmp(addressbook->contact_details[i].Mail_ID, email) == 0)
            return 0;
    }
    return 1;
}

// create contact

int create_contact(AddressBook *addressbook)
{
    if (addressbook->contact_count >= 100)
    {
        printf("\033[1;31m***Address book is full. Cannot add more contacts.***\033[0m\n");
        return -1;
    }

    Contacts *new_contact = &addressbook->contact_details[addressbook->contact_count];

    // Name loop
    while (1)
    {
        printf("\033[1;33mEnter name: \033[0m");
        scanf("%[^\n]", new_contact->Name);
        getchar(); // Read full line including spaces
        if (!is_valid_name(new_contact->Name))
        {
            printf("\033[1;31m***Name must contain only alphabets and spaces.***\033[0m\n");
            continue;
        }
        else
        {
            printf("\033[1;32m***Name Saved Successfully***\033[0m\n\n");
            break;
        }
    }

    // Mobile number loop
    while (1)
    {
        printf("\033[1;33mEnter mobile number: \033[0m");
        scanf(" %s", new_contact->Mobile_number); // Read as Mobile Number
        if (!is_valid_mobile(new_contact->Mobile_number))
        {
            printf("\033[1;31m***Mobile number must be exactly 10 digits.***\033[0m\n");
            continue;
        }

        if (!(is_unique_number(addressbook, new_contact->Mobile_number)))
        {
            printf("\033[1;31m***Mobile number already exists, Please enter a different mobile number.***\033[0m\n");
            continue;
        }
        else
        {
            printf("\033[1;32m***Mobile number saved successfully***\033[0m\n");
        }
        printf("\n");
        break;
    }

    // Email loop
    while (1)
    {
        printf("\033[1;33mEnter email ID: \033[0m");
        scanf(" %s", new_contact->Mail_ID); // Read as string
        if (!is_valid_email(new_contact->Mail_ID))
        {
            printf("\033[1;31m***Email must be in the format name@domain.com***\033[0m\n");
            continue;
        }
        if (!(is_unique_email(addressbook, new_contact->Mail_ID)))
        {
            printf("\033[1;31m***Email ID already exists, Please enter a different email ID.***\033[0m\n");
            continue;
        }
        else
        {
            printf("\033[1;32m***Email ID saved successfully***\033[0m\n");
        }
        break;
    }

    addressbook->contact_count++;
    printf("\n");
    printf("\033[1;32m***Contact added successfully.***\033[0m\n");
    return 0;
}

// Display the contacts

void list_contacts(AddressBook *addressbook)
{
    if (addressbook->contact_count == 0)
    {
        printf("\033[1;31m***No contacts to display, Please add some contacts first.***\033[0m\n");
        return;
    }

    printf("\033[1;34m\n---List of Contacts---\n\033[0m");
    printf("\n");

    // sort contacts by name
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        for (int j = i + 1; j < addressbook->contact_count; j++)
        {
            if (strcmp(addressbook->contact_details[i].Name, addressbook->contact_details[j].Name) > 0)
            {
                Contacts temp = addressbook->contact_details[i];
                addressbook->contact_details[i] = addressbook->contact_details[j];
                addressbook->contact_details[j] = temp;
            }
        }
    }

    // print table header
    char *strline = "\033[1;34m----------------------------------------------------------------------------------------\033[0m";
    printf("%s\n", strline);
    printf("\033[1;33m| %-5s | %-25s | %-15s | %-30s |\033[0m\n", "S.No", "Name", "Mobile Number", "Email ID");
    printf("%s\n", strline);

    // print table rows

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        Contacts *contact = &addressbook->contact_details[i];

        printf("\033[1;32m| %-5d | %-25s | %-15s | %-30s |\033[0m\n", i + 1, contact->Name, contact->Mobile_number, contact->Mail_ID);
    }
    printf("%s\n", strline); 
    printf("\n");
}

// Search the contacts

int search_contacts(AddressBook *addressbook)
{
    if (addressbook->contact_count == 0)
    {
        printf("\033[1;31m***No contacts to search, Please add some contacts first.***\033[0m\n");
        return -1;
    }

    char again = 'y';
    while (again == 'y' || again == 'Y')
    {
        printf("\n\033[1;34m---Search the Contacts---\n\033[0m");
        printf("\033[1;35mSearch by:\n1. Name\n2. Mobile Number\n3. Email ID\n4. Exit\033[0m\n\n");

        int choice;
        scanf("%d", &choice);
        getchar(); // Consume newline

        char name[32], mobile[15], email[32];
        int match[100], match_count = 0;

        switch (choice)
        {
            case 1:
                printf("\033[1;33mEnter the name to search: \033[0m");
                scanf("%[^\n]", name);
                getchar();
                for (int i = 0; i < addressbook->contact_count; i++)
                    if (strcmp(addressbook->contact_details[i].Name, name) == 0)
                        match[match_count++] = i;
                break;

            case 2:
                printf("\033[1;33mEnter the mobile number to search: \033[0m");
                scanf("%s", mobile);
                getchar();
                for (int i = 0; i < addressbook->contact_count; i++)
                    if (strcmp(addressbook->contact_details[i].Mobile_number, mobile) == 0)
                        match[match_count++] = i;
                break;

            case 3:
                printf("\033[1;33mEnter the email ID to search: \033[0m");
                scanf("%s", email);
                getchar();
                for (int i = 0; i < addressbook->contact_count; i++)
                    if (strcmp(addressbook->contact_details[i].Mail_ID, email) == 0)
                        match[match_count++] = i;
                break;

            case 4:
                return -1;

            default:
                printf("\033[1;31m***Enter the correct choice, Please try again.***\033[0m\n");
                continue;
        }

        if (match_count == 0)
        {
            printf("\033[1;31m***No matching contacts found.***\033[0m\n");
        }
        else if (match_count == 1)
        {
            Contacts *c = &addressbook->contact_details[match[0]];
            printf("\n\033[1;34m---Contact found:---\n\033[0m");
            printf("\033[1;35mName: %s\n\033[0m", c->Name);
            printf("\033[1;35mMobile Number: %s\n\033[0m", c->Mobile_number);
            printf("\033[1;35mEmail ID: %s\n\033[0m", c->Mail_ID);
            printf("\n");
        }
        else
        {
            printf("\n\033[1;34m---%d Contacts found:---\n\033[0m", match_count);
            for (int i = 0; i < match_count; i++)
            {
                Contacts *c = &addressbook->contact_details[match[i]];
                printf("\033[1;35m%d. Name: %s\n\033[0m", i + 1, c->Name);
                printf("\033[1;35mMobile Number: %s\n\033[0m", c->Mobile_number);
                printf("\033[1;35mEmail ID: %s\n\033[0m", c->Mail_ID);
                printf("\n");
            }

            int select;
            printf("\033[1;33mEnter the number index of the contact to select (1-%d): \033[0m", match_count);
            scanf("%d", &select);
            getchar();

            if (select >= 1 && select <= match_count)
            {
                Contacts *c = &addressbook->contact_details[match[select - 1]];
                printf("\n\033[1;36m---Selected Contact---\n\033[0m");
                printf("\033[1;35mName: %s\n\033[0m", c->Name);
                printf("\033[1;35mMobile Number: %s\n\033[0m", c->Mobile_number);
                printf("\033[1;35mEmail ID: %s\n\033[0m", c->Mail_ID);
            }
            else
            {
                printf("\033[1;31m***Select Correct Index selection.***\033[0m\n");
            }
        }

        printf("\n\033[1;33mDo you want to search for another contact? (y/n): \033[0m");
        scanf(" %c", &again);
        getchar();
    }

    return 0;
}

// Edit the contacts

int edit_contact(AddressBook *addressbook)
{
    if (addressbook->contact_count == 0)
    {
        printf("\033[1;31m***No contacts available to edit.***\033[0m\n");
        return 0;
    }

    char edit_again = 'y';
    while (edit_again == 'y' || edit_again == 'Y')
    {
        int contact_index = search_contacts(addressbook);
        if (contact_index == -1)
        {
            printf("\033[1;31m***Contact cannot be edited.***\033[0m\n");
            return 0;
        }

        int choice;
        printf("\n\033[1;36m--- Editing Contact Menu ---\n\033[0m");
        printf("\033[1;35m1. Edit Name\n2. Edit Mobile Number\n3. Edit Email ID\n4. Edit All\n5. Exit\nEnter your choice: \033[0m");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice)
        {
            case 1: // Edit Name
            {
                while (1)
                {
                    char new_name[32];
                    printf("\033[1;33mEnter new name: \033[0m");
                    scanf(" %[^\n]", new_name);
                    getchar();
                    if (!is_valid_name(new_name))
                    {
                        printf("\033[1;31m***Name must contain only alphabets and spaces.***\033[0m\n");
                        continue;
                    }
                    strcpy(addressbook->contact_details[contact_index].Name, new_name);
                    printf("\033[1;32m***Name updated successfully***\033[0m\n");
                    break;
                }
                break;
            }

            case 2: // Edit Mobile Number
            {
                while (1)
                {
                    char new_mobile[15];
                    printf("\033[1;33mEnter new mobile number: \033[0m");
                    scanf("%s", new_mobile);
                    getchar();
                    if (!is_valid_mobile(new_mobile))
                    {
                        printf("\033[1;31m***Mobile number must be exactly 10 digits.***\033[0m\n");
                        continue;
                    }
                    if (!is_unique_number_for_edit(addressbook, new_mobile, contact_index))
                    {
                        printf("\033[1;31m***Mobile number already exists.***\033[0m\n");
                        continue;
                    }
                    strcpy(addressbook->contact_details[contact_index].Mobile_number, new_mobile);
                    printf("\033[1;32m***Mobile number updated successfully***\033[0m\n");
                    break;
                }
                break;
            }

            case 3: // Edit Email
            {
                while (1)
                {
                    char new_email[32];
                    printf("\033[1;33mEnter new email ID: \033[0m");
                    scanf("%s", new_email);
                    getchar();
                    if (!is_valid_email(new_email))
                    {
                        printf("\033[1;31m***Email must be in the format name@domain.com***\033[0m\n");
                        continue;
                    }
                    if (!is_unique_email_for_edit(addressbook, new_email, contact_index))
                    {
                        printf("\033[1;31m***Email ID already exists.***\033[0m\n");
                        continue;
                    }
                    strcpy(addressbook->contact_details[contact_index].Mail_ID, new_email);
                    printf("\033[1;32m***Email ID updated successfully***\033[0m\n");
                    break;
                }
                break;
            }

            case 4: // Edit All
            {
                // Edit Name
                while (1)
                {
                    char new_name[32];
                    printf("\033[1;33mEnter new name: \033[0m");
                    scanf(" %[^\n]", new_name);
                    getchar();
                    if (!is_valid_name(new_name))
                    {
                        printf("\033[1;31m***Name must contain only alphabets and spaces.***\033[0m\n");
                        continue;
                    }
                    strcpy(addressbook->contact_details[contact_index].Name, new_name);
                    break;
                }

                // Edit Mobile
                while (1)
                {
                    char new_mobile[15];
                    printf("\033[1;33mEnter new mobile number: \033[0m");
                    scanf("%s", new_mobile);
                    getchar();
                    if (!is_valid_mobile(new_mobile))
                    {
                        printf("\033[1;31m***Mobile number must be exactly 10 digits.***\033[0m\n");
                        continue;
                    }
                    if (!is_unique_number_for_edit(addressbook, new_mobile, contact_index))
                    {
                        printf("\033[1;31m***Mobile number already exists.***\033[0m\n");
                        continue;
                    }
                    strcpy(addressbook->contact_details[contact_index].Mobile_number, new_mobile);
                    break;
                }

                // Edit Email
                while (1)
                {
                    char new_email[32];
                    printf("\033[1;33mEnter new email ID: \033[0m");
                    scanf("%s", new_email);
                    getchar();
                    if (!is_valid_email(new_email))
                    {
                        printf("\033[1;31m***Email must be in the format name@domain.com***\033[0m\n");
                        continue;
                    }
                    if (!is_unique_email_for_edit(addressbook, new_email, contact_index))
                    {
                        printf("\033[1;31m***Email ID already exists.***\033[0m\n");
                        continue;
                    }
                    strcpy(addressbook->contact_details[contact_index].Mail_ID, new_email);
                    break;
                }

                printf("\033[1;32m***Contact updated successfully***\033[0m\n");
                break;
            }

            case 5: // Exit
                return 0;

            default:
                printf("\033[1;31m***Enter a valid choice, Please try again.***\033[0m\n");
        }

        // Ask if the user wants to edit another contact
        printf("\n\033[1;33mDo you want to edit another contact? (y/n): \033[0m");
        scanf(" %c", &edit_again);
        getchar();
    }

    return 0;
}


// Delete the contacts

int delete_contact(AddressBook *addressbook)
{
    if (addressbook->contact_count == 0)
    {
        printf("\033[1;31m***No contacts to delete, Please add some contacts first.***\033[0m\n");
        return 0;
    }

    printf("\n\033[1;36m---Delete Contact Menu---\033[0m\n");
    printf("\033[1;35mSearch by:\n1. Name\n2. Mobile Number\n3. Email ID\n4. Exit\n\033[0m");
    printf("\n");
    printf("\033[1;33mEnter your choice: \033[0m");

    int choice;
    if (scanf("%d", &choice) != 1)
        return 0;
    getchar(); // clear newline

    char again = 'y';

    while (again == 'y' && addressbook->contact_count > 0)
    {
        char input[64];
        int match[100]; // store indexes of matching contacts
        int match_count = 0;

        // Take input based on search type
        switch (choice) 
        {
        case 1:
            printf("\033[1;33mEnter the name to search: \033[0m");
            scanf("%[^\n]", input);
            getchar();
            for (int i = 0; i < addressbook->contact_count; i++)
                if (strcmp(addressbook->contact_details[i].Name, input) == 0)
                    match[match_count++] = i;
            break;

        case 2:
            printf("\033[1;33mEnter the mobile number to search: \033[0m");
            scanf("%s", input);
            getchar();
            for (int i = 0; i < addressbook->contact_count; i++)
                if (strcmp(addressbook->contact_details[i].Mobile_number, input) == 0)
                    match[match_count++] = i;
            break;

        case 3:
            printf("\033[1;33mEnter the email ID to search: \033[0m");
            scanf("%s", input);
            getchar();
            for (int i = 0; i < addressbook->contact_count; i++)
                if (strcmp(addressbook->contact_details[i].Mail_ID, input) == 0)
                    match[match_count++] = i;
            break;
        case 4:
            return 0; // Exit delete

        default:
            printf("\033[1;31m***Enter a valid choice, Please try again.***\033[0m\n");
            return 0;
        }

        if (match_count == 0)
        {
            printf("\033[1;31m***No matching contacts found***\033[0m\n");
            break;
        }

        // Display matches
        printf("\n\033[1;34m---Matching Contacts---\033[0m\n");
        printf("\n");
        for (int i = 0; i < match_count; i++)
        {
            Contacts *c = &addressbook->contact_details[match[i]];
            printf("%d.\n", i + 1);
            printf("\033[1;35mName: %s\n\033[0m", c->Name);
            printf("\033[1;35mMobile Number: %s\n\033[0m", c->Mobile_number);
            printf("\033[1;35mEmail ID: %s\n\033[0m", c->Mail_ID);
        }

        printf("\n");
        // Select index to delete
        int delete_Index;
        printf("\n\033[1;33mEnter the index of the contact to delete (1-%d): \033[0m", match_count);
        printf("\n");
        if (scanf("%d", &delete_Index) != 1 || delete_Index < 1 || delete_Index > match_count)
        {
            printf("\033[1;31m***Index not matched, Please try again.***\033[0m\n");
            break;
        }
        getchar();

        int actualIndex = match[delete_Index - 1];

        // Delete the selected contact
        for (int i = actualIndex; i < addressbook->contact_count - 1; i++)
            addressbook->contact_details[i] = addressbook->contact_details[i + 1];

        addressbook->contact_count--;

        printf("\033[1;32m***Contact deleted successfully***\033[0m\n");

        if (addressbook->contact_count == 0)
        {
            printf("\033[1;32m***No more contacts to delete, Please add some contacts first.***\033[0m\n");
            break;
        }

        // Ask if user wants to delete another
        printf("\033[1;32m\nDo you want to delete another contact ? (y/n): \033[0m");
        scanf(" %c", &again);
        getchar();
    }

    return 0;
}

// Save the contacts

int save_contacts(AddressBook *addressbook)
{
    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL)
    {
        printf("\033[1;31m***Could not open file for saving.***\033[0m\n");
        return -1;
    }
    fprintf(fp, "#%d\n", addressbook->contact_count); // Write contact count first

    // Write each contact
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        Contacts *contact = &addressbook->contact_details[i];
        fprintf(fp, "%s, %s, %s\n", contact->Name, contact->Mobile_number, contact->Mail_ID);
    }

    fclose(fp);
    printf("\033[1;32m***Contacts saved successfully to data.txt***\033[0m\n");

    return 0;
}

// Load the contacts

void init_intitalization(AddressBook *addressbook)
{
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("\033[1;31m*** Could not open file for loading.***\033[0m\n");
        return;
    }

    fscanf(fp, "#%d\n", &addressbook->contact_count);
    // Read each contact
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        Contacts *contact = &addressbook->contact_details[i];
        fscanf(fp, "%[^,], %[^,], %[^\n]\n", contact->Name, contact->Mobile_number, contact->Mail_ID);
    }

    fclose(fp);
    printf("\033[1;32m***Loaded %d contacts from data.txt successfully***\033[0m\n", addressbook->contact_count);
    return;
}

// Save and exit the contacts

int save_and_exit(AddressBook *addressbook)
{
    save_contacts(addressbook);
    printf("\n");
    printf("\033[1;35m***~~Goodbye!!!! Thank You for using the Address Book!!!***\033[0m\n");
    printf("\n");
    return 0;
}