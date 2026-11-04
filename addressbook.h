#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>


struct Contact{
    char name[50];
    char phone[15];
    char email[50];
};

struct AddressBook {
    struct Contact contacts[100];
    int contactCount;
    int index_record[100];
    int ir_size;
    int not_found;
};

void add_contact(struct AddressBook *addressBook);
void search_contact(struct AddressBook *addressBook);
void edit_contact(struct AddressBook *addressBook);
void delete_contact(struct AddressBook *addressBook);
void list_contacts(struct AddressBook *addressBook);
void save_contacts_to_file(struct AddressBook *addressBook);
void Load_contacts_from_file(struct AddressBook *addressBook);

#endif
