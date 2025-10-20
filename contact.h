#ifndef CONTACT_H
#define CONTACT_H

//Structure Contacts fields
/* Structure declaration */
typedef struct Contact_data
{
    char Name[32];
    char Mobile_number[11];
    char Mail_ID[35];
} Contacts;

//Structure AdressBook 

typedef struct AddressBook_Data
{
    Contacts contact_details[100];
    int contact_count;
} AddressBook;

/* Function declarations */

void init_intitalization(AddressBook *);
int create_contact(AddressBook *);
void list_contacts(AddressBook *);
int search_contacts(AddressBook *);
int edit_contact(AddressBook *);
int delete_contact(AddressBook *);
int save_contacts(AddressBook *);
int save_and_exit(AddressBook *);


#endif // CONTACT_H
       // CONTACT_H