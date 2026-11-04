/*Author name:Nitheesh K M
  start date:22/10/2026
  complition date:3/11/2026
  description:Address Book Management System in C - Project
              The Address Book Management System is a console-based application developed in the 
			  C programming language to store and manage contact information. The project allows 
			  users to create, search, edit, delete, list, save, and load contacts. Each contact 
			  contains a Name, Phone Number, and Email ID.
			  The application uses structures to organize contact details and stores multiple 
			  contacts in an array. It performs validation to ensure that phone numbers and email 
			  addresses are entered in the correct format and prevents duplicate phone numbers and email IDs. 
			  Contact information can be saved to a CSV file and loaded back when the application starts, 
			  providing simple data persistence using file handling.
  Features: Add/Create Contact
            Search Contact by:
            Name
            Phone Number
            Email ID
			Edit Contact
			Delete Contact
			List All Contacts
			Validate Phone Numbers
			Validate Email IDs
			Check Unique Phone Numbers
			Check Unique Email IDs
			Save Contacts to File
			Load Contacts 
	Concepts/Commands You Learned in This Project: Structures,Nested Structures,Functions,Function Calls,Arrays,
	Array of Structures,Pointers,Structure Pointer Operator,String Handling Functions,Loops,for Loop,
	Conditional Statements,Nested if Statements,do-while Loop,Switch Case,File Handling,
	CSV File Processing,Input/Output Functions*/
#include "addressbook.h"
#include<string.h>
int main() 
{
    int choice;

    struct AddressBook addressBook;
    addressBook.contactCount = 0;
    addressBook.ir_size = 0;
	addressBook.not_found = 0;

	Load_contacts_from_file(&addressBook);

    do 
    {
	printf("\nAddress Book Menu:\n");
	printf("1. Add/Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. save all contacts\n");
	printf("7. Exit\n");
	printf("Enter your choice: ");

	scanf("%d", &choice);

	switch (choice) 
	{
	    case 1:
		add_contact(&addressBook);
		break;
	    case 2:
		search_contact(&addressBook);
		break;
	    case 3:
		edit_contact(&addressBook);
		break;
	    case 4:
		delete_contact(&addressBook);
		break;
	    case 5:
		list_contacts(&addressBook);
		break;
	    case 6:
		save_contacts_to_file(&addressBook);
		break;
		case 7:
		printf("Exit,Thank you\n");
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 7);

    return 0;
}
