#include "addressbook.h"
#include<string.h>
/*Function declaration for validiting phone number & also unique phone num or not,
mail id & also unique mail id or not*/
int validate_phonenumber(char []);
int validate_mailid(char []);
int unique_phonenumber(struct AddressBook *addressBook,char []);
int unique_mailid(struct AddressBook *addressBook,char []);
void add_contact(struct AddressBook *addressBook)
{
    //To declare the contact name,phone number,mail id variable
    char contact_name[20],contact_mailid[50];
    char contact_phonenumber[20];
    int i = 0;
    printf("Enter the name: ");
    scanf("%s",contact_name);//Read the user name from user
    do
    {
      printf("Enter the phonenumber: ");
      scanf(" %s",contact_phonenumber);//Read the user phone number from user

      printf("Enter the email id: ");
      scanf("%s",contact_mailid);//Read the user mail id from user

    }while(i != 0);

    //Creat Temp variable for Validation
    char temp_phonenumber[20],temp_mailid[50];
    strcpy(temp_phonenumber,contact_phonenumber);//Coping the contact phone number to temp variable for validation
    strcpy(temp_mailid,contact_mailid);//Coping the contact mail id to temp variable for validation

    //For count the contact for all name,phone number,mail id
    int pos = addressBook->contactCount;

    //Function call
    int ret = validate_phonenumber(temp_phonenumber);
    int ret1 = validate_mailid(temp_mailid);
    if(ret == 1)
    {
        unique_phonenumber(addressBook,temp_phonenumber);//Function call for check unique phone number or not
        strcpy(contact_phonenumber,temp_phonenumber);//After the validation is true to store the temp phone number into contact phonenumber
    }
    else
    {
       //If the vaidation fail return 0 re enter the phone number and again vaild until the condition become true
       do
       {
         printf("Enter the phonenumber again: ");
         scanf(" %s",temp_phonenumber);//Read the temp phonenumber from user
         ret = validate_phonenumber(temp_phonenumber);//Again call function if the validation is 0
       }
       while(ret == 0);
       unique_phonenumber(addressBook,temp_phonenumber);//Function call for check unique phone number or not
       strcpy(contact_phonenumber,temp_phonenumber);//After the validation is true to store the temp phone number into contact phonenumber
    }

    if(ret1 == 1)
    {
        unique_mailid(addressBook,temp_mailid);//Function call for check unique mail id or not
        strcpy(contact_mailid,temp_mailid);//Coping the temp mail to original contact mail id after the validation
    }
    else
    {
        //If the vaidation fail return 0 re enter the mail id and again vaild until the condition become true
        do
        {
            printf("Enter the emailid again: ");
            scanf("%s",temp_mailid);//Read the temp mail id from user
            ret1 = validate_mailid(temp_mailid);//Function call
        }
        while(ret1 == 0);
        unique_mailid(addressBook,temp_mailid);//Function call for check unique mail id or not
        strcpy(contact_mailid,temp_mailid);//Coping the temp mail to original contact mail id after the validation
    }

    //Coping the name,phone number,email id after validation
    strcpy(addressBook->contacts[pos].name,contact_name);//copy the name into addressbook
    strcpy(addressBook->contacts[pos].phone,contact_phonenumber);//copy the phone number into addressbook
    strcpy(addressBook->contacts[pos].email,contact_mailid);//copy the mail id into addressbook
    addressBook->contactCount++;//contactcount for all name,phone number,email id 
}
//Function declaration for search user name,phone number,email id
void search_username(struct AddressBook *addressBook);
void search_userphonenumber(struct AddressBook *addressBook);
void search_useremail(struct AddressBook *addressBook);
void search_contact(struct AddressBook *addressBook)
{
    //To declare the variable
    int choice;
    printf("\nSearch contact Menu:\n");
	printf("1. Search name \n");
	printf("2. Search phone number\n");
	printf("3. Search email id\n");
    printf("Enter your choice: ");

    scanf("%d",&choice);//Read the choice from user
    
    if(choice == 1)
    {
       search_username(addressBook);//Function call for search the user name
    }
    else if(choice == 2)
    {
        search_userphonenumber(addressBook);//Function call for search the user phone number
    }
    else if(choice == 3)
    {
        search_useremail(addressBook);//Function call for search the user email id
    }
    else
    {
        printf("Invalid choice. Please try again.\n");//user enter the wrong choice
    }
    
    //Validation for user contact is found or not
    if(addressBook->ir_size == 0)//If there is no contact detail is found means print no contact and again go to main menu function
    {
        printf("Contact not found\n");
        addressBook->not_found = 0;//If no contact mean not_found = 0
    }
    else
    {
        int s_no = 1;//Display the user contact using serial number by number like 1,2,3..
        for(int i = 0; i < addressBook->ir_size; i++)
        {
            int index = addressBook->index_record[i];//Index record will give the search contact index value in vaildation function like addressBook->index_record[0] = 1,addressBook->index_record[1] = 3,addressBook->index_record[2] = 5 for both name,phone number,mail id
            printf("%d-> %s %s %s",s_no,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
            s_no++;
            printf("\n");
        }
        addressBook->not_found = 1;
    }
}
//Function declaration for edit the name,phone number,mail id
void edit_name(struct AddressBook *addressBook,int);
void edit_phonenumber(struct AddressBook *addressBook,int);
void edit_mailid(struct AddressBook *addressBook,int);
void edit_contact(struct AddressBook *addressBook)
{
   search_contact(addressBook);//Function call for edit the name,phone number,mail id and display the searched contact by using serial number by number
    int s_no;
   if(addressBook->not_found == 0)//validation for no contact is not found we return to main menu
   {
     printf("No contact found for search the user contact\n");
     addressBook->not_found = 1;
     return;
   }
   if(addressBook->ir_size != 0)//validation for contact is found means it will read the serial number
   {
    printf("Enter the serial number: ");
    scanf("%d",&s_no);//Read the serial number from user
   }
   if(s_no < 1 || s_no > addressBook->ir_size)
   {
     printf("Invalid serial number\n");
     return;
   }

   int array_index;
   array_index = s_no - 1;//contacts start from 0,1,2 and searched contact like 1,2,3 and we subract serial - 1 to access the index value of the contact

   int contact_index;
   contact_index = addressBook->index_record[array_index];//Store the index number in temp contact index

   int choice;
   do//Display the meanu for edit the contact and user enter the choice
   {
    printf("\nEdit contact Menu:\n");
	printf("1. Edit name \n");
	printf("2. Edit phone number\n");
	printf("3. Edit email id\n");
	printf("4. Exit \n");
    printf("Enter your choice: ");

   scanf("%d",&choice);//user enter the choice
   switch(choice)
   {
       case 1:
       edit_name(addressBook,contact_index);//Function call for edit user name
       break;

       case 2:
       edit_phonenumber(addressBook,contact_index);//Function call for edit user phone number
       break;

       case 3:
       edit_mailid(addressBook,contact_index);//Function call for edit user mail id
       break;

       case 4:
       printf("Saving and Exiting...\n");
       break;

       default:
       printf("Invalid choice. Please try again.\n");

   }
   }while(choice != 4);
}
void delete_contact(struct AddressBook *addressBook)
{
   search_contact(addressBook);//Function call for delete the name,phone number,mail id and display the searched contact by using serial number by number
   if(addressBook->not_found == 0)//validation for no contact is not found we return to main menu
   {
     printf("No contact found for search the user contact\n");
     addressBook->not_found = 1;
     return;
   }
   int s_no;
   if(addressBook->ir_size != 0)//validation for contact is found means it will read the serial number
   {
    printf("Enter the serial number: ");
    scanf("%d",&s_no);//Read the serial number from user
   }
   if(s_no < 1 || s_no > addressBook->ir_size)
   {
     printf("Invalid serial number\n");
     return;
   }

   int array_index;
   array_index = s_no - 1;//contacts start from 0,1,2 and searched contact like 1,2,3 and we subract serial - 1 to access the index value of the contact

   int contact_index;
   contact_index = addressBook->index_record[array_index];//Store the index number in temp contact index

    char choice;
    printf("\nDelete contact :\n");
    printf("Do you want delete the contact press yes or no\n");
    printf("Enter your choice: ");
   scanf(" %c",&choice);//user enter the choice
   if(choice == 'y' ||choice == 'Y')
   {
     for(int i = contact_index; i < addressBook->contactCount - 1; i++)//Delete the contact detail like 0,1,2,3,4,5 contacts are available user want to delete 3 index contact
     {                                            //so move the contact like 0,1,2,4,5 
        strcpy(addressBook->contacts[i].name,addressBook->contacts[i + 1].name);
        strcpy(addressBook->contacts[i].phone,addressBook->contacts[i + 1].phone);
        strcpy(addressBook->contacts[i].email,addressBook->contacts[i + 1].email);
     }
     addressBook->contactCount--;
     printf("Contact deleted successfully\n");
   }
   else
   {
    printf("User do not delete any contact\n");
   }

}
//Function declaration for list the contact
void list_contacts(struct AddressBook *addressBook)
{
    if(addressBook->contactCount == 0)
    {
      printf("No contacts found\n");
      return;
    }
    
    int s_no = 1;//Display the user contact using serial number by number like 1,2,3..
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d-> %s %s %s",s_no,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);//List all the user contact 
        s_no++;
        printf("\n");
    }
    return;
}
//Function declaration for store the contact in file
void save_contacts_to_file(struct AddressBook *addressBook)
{
    FILE *fp = fopen("database.csv","w");//using file IO user will save the contact with write mode in database.csv file

    if(fp == NULL)
    {
        printf("File opening failed\n");
        return;
    }

    for(int i = 0; i < addressBook->contactCount; i++)//contact count time loop will run
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);//print the contact detial in the database file
    }

    fclose(fp);//close the file

    if(addressBook->contactCount == 0)//validation for no contact
    {
       printf("No contact found\n");
    }
    else
    {
        printf("Contact saved successfully\n");
    }
   
}
//Function definition for validating phone number
int validate_phonenumber(char *temp_phonenumber)
{
    int num_length = strlen(temp_phonenumber);//Store the number length in num length for validating if it has 10 number or not
    int i = 0,start = 0;
    start = temp_phonenumber[0];
    if(start >= '6' && start <= '9')//Validation for number must have start from 6 to 9
    {
        if( num_length == 10 )//Validation for number must have 10 digit
        {
            while(temp_phonenumber[i] != '\0')
            {
                if(temp_phonenumber[i] >= '0' && temp_phonenumber[i] <= '9')//Validation for number should not have any symbol
                {
                  i++;
                }
                else
                {
                  printf("User do not enter any symbol must enter the number only\n");
                  return 0;
                }
            }
        }
        else
        {
          printf("User Must Enter ten Number\n");
          return 0;
        }
    }
    else  
    {
        printf("User number must starts with 6 to 9\n");
        return 0;
    }
    return 1;
}
//Function definition for validating unique phone number
int unique_phonenumber(struct AddressBook *addressBook,char *temp_phonenumber)
{
   int j = 0;
   int ret = 0;
   //If the vaidation phone number become true it also check the phone number is already used or not and store the contact
   while(j < addressBook->contactCount)//Contact count times loop run
    {
        if(strcmp(addressBook->contacts[j].phone,temp_phonenumber) == 0)//Validation for the unique number
        {
        printf("Number is already used please enter different number\n");//If Unique is found re enter the phone number until user enter diff number
        do
        {
            printf("Enter the phonenumber again: ");
            scanf(" %s",temp_phonenumber);
            ret = validate_phonenumber(temp_phonenumber);//Again call function if the validation is 0
        }
        while(ret == 0);
        j = -1;//Again j++ j become 0 and start to check the condition from the starting position of the contact list
        }
        j++;
    }
    return 1;
}
//Function definition for validating mail id
int validate_mailid(char *temp_mailid)
{
    int i = 0,len = 0,start,count = 0;
    char end[5];
    len = strlen(temp_mailid);
    if(len < 5)
    {
      printf("Invalid email id\n");
      return 0;
    }
    start = temp_mailid[0];
    strcpy(end,temp_mailid + len - 4);//Coping the .com is the end value of email
    if(start != '@')//Validation for start value is not a @ symbol
    {
        if(!strcmp(end, ".com"))//Validation for end value is .com or not
        {
          while(temp_mailid[i] != '\0')
          {
            if(temp_mailid[i] >= 'a' && temp_mailid[i] <= 'z')//Validation for all email character must small alphbets
            {
                i++;
            }
            else if(temp_mailid[i] == '.')//validation for user enter only one time .com in email id
            {
                i++;
                if(temp_mailid[i] == 'c')
                {
                    i++;
                    if(temp_mailid[i] == 'o')
                    {
                        i++;
                        if(temp_mailid[i] == 'm')
                        {
                            count++;
                        }
                    }
                }
            }
            else if(temp_mailid[i] == '@')//validation for user enter only one time @ in email id
            {
                i++;
                count++;
            }
            else if(temp_mailid[i] >= '0' && temp_mailid[i] <= '9' )//validation for user enter number also
            {
                i++;
            }
            else
            {
                printf("Mail id must be small alphabet character\n");
                return 0;
            }
          }
        }
        else
        {
            printf("Mail id must end with .com\n");
            return 0;
        }
        if(count != 2)//validation for user enter only one time @ and .com in email id
        {
           printf("User must enter only one time @ symbol or .com or must enter character after @ symbol\n");
           return 0;
        }
    }
    else
    {
        printf("First letter must be small alphbet character\n");
        return 0;
    }
    return 1;
}
//Function definition for validating unique mail id
int unique_mailid(struct AddressBook *addressBook,char *temp_mailid)
{
    int j = 0;
    int ret = 0;
    //If the vaidation become true it also check the mail id is already used or not and store the contact
    while(j < addressBook->contactCount)//Contact count times loop run
    {
        if(strcmp(addressBook->contacts[j].email,temp_mailid) == 0)//Validation for compare the email is unique or not
        {                                                             //if condition true means return 0 and 0 == 0 execute the if part and again read the email id 
            printf("Email id is already used please enter different mail id\n");
            do
            {
                printf("Enter the mail id again: ");
                scanf("%s",temp_mailid);
                ret = validate_mailid(temp_mailid);//Function call
            }
            while(ret == 0);
            j = -1;//Again j++ j become 0 and start to check the condition from the starting position of the contact list
        }
        j++;
    } 
    return 1;
}
//Function definition for search name
void search_username(struct AddressBook *addressBook)
{
    char search_name[20];
    int index_store = 0;
    addressBook->ir_size = 0;
    printf("Enter the search name: ");
    scanf("%s",search_name);//Read the search name input from user
    int i = 0;
    while(i < addressBook->contactCount)//Contact count times loop run
    {
        if(strcmp(addressBook->contacts[i].name,search_name) == 0)//Compare the give name is match in the contact if match means store the index in index_record
        {
            addressBook->index_record[index_store] = i;//Store the index value in index record  like addressBook->index_record[0] = 1,addressBook->index_record[1] = 3,addressBook->index_record[2] = 5 for both name,phone number,mail id
            addressBook->ir_size++;//Increament the ir_size for number of contact matched
            index_store++;
        }
        i++;
    }  
}
void search_userphonenumber(struct AddressBook *addressBook)
{
   char search_phonenumber[20];
   printf("Enter the search phonenumber: ");
   scanf("%s",search_phonenumber);//Read the search phone number input from user

   int i = 0;
   int index_store = 0;//Ever time function call the index start from zero
   addressBook->ir_size = 0;//Ever time function call the size start from zero
   int ret = validate_phonenumber(search_phonenumber);//Validating the mobile number
   if(ret == 1)
   { 
        while(i < addressBook->contactCount)//Contact count times loop run
        {
            if(strcmp(addressBook->contacts[i].phone,search_phonenumber) == 0)//Compare the give phone number is match in the contact if match means store the index in index_record
            {
               addressBook->index_record[index_store] = i;//Store the index value in index record  like addressBook->index_record[0] = 1,addressBook->index_record[1] = 3,addressBook->index_record[2] = 5 for both name,phone number,mail id
               addressBook->ir_size++;//Increament the ir_size for number of contact matched
               index_store++;
            }
            i++;
        }
    }
    else
    {
      search_userphonenumber(addressBook);//If validation is fail again re enter the phone nuber by function call
    }
}
void search_useremail(struct AddressBook *addressBook)
{
    char search_mailid[50];
    printf("Enter the search email: ");
    scanf("%s",search_mailid);//Read the search mail id input from user

    int i = 0;
    int index_store = 0;//Ever time function call the index start from zero
    addressBook->ir_size = 0;//Ever time function call the size start from zero
    int res = validate_mailid(search_mailid);//Validating the mail id

    if(res == 1)
    {
        while(i < addressBook->contactCount)//Contact count times loop run
        {
            if(strcmp(addressBook->contacts[i].email,search_mailid) == 0)//Compare the give mail id is match in the contact if match means store the index in index_record
            {
                addressBook->index_record[index_store] = i;//Store the index value in index record  like addressBook->index_record[0] = 1,addressBook->index_record[1] = 3,addressBook->index_record[2] = 5 for both name,phone number,mail id
                addressBook->ir_size++;//Increament the ir_size for number of contact matched
                index_store++;
            }
            i++;
        }
    }
    else
    {
        search_useremail(addressBook);//If validation is fail again re enter the mail id by function call
    }
}
//Function definition for edit the name
void edit_name(struct AddressBook *addressBook,int contact_index)
{
    char new_name[20];
    printf("Enter the new name: ");
    scanf("%s",new_name);//Read the new name input from user

    int s_no = 1;
    strcpy(addressBook->contacts[contact_index].name,new_name);//copy the new name to contact by using search function serial number stored index value
    for(int i = 0; i < addressBook->ir_size; i++)
    {
        int index = addressBook->index_record[i];//Index record will give the search contact index value in vaildation function like addressBook->index_record[0] = 1,addressBook->index_record[1] = 3,addressBook->index_record[2] = 5 for both name,phone number,mail id
        printf("%d-> %s %s %s",s_no,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
        s_no++;
        printf("\n");
    }
    printf("New Name is successfully edited\n");
}
//Function definition for edit the phone number
void edit_phonenumber(struct AddressBook *addressBook,int contact_index)
{
    char new_phonenumber[20];
    printf("Enter the new phone number: ");
    scanf("%s",new_phonenumber);//Read the new phone number input from user

    int s_no = 1;
    int ret = validate_phonenumber(new_phonenumber);//Validating the mobile number
    if(ret == 1)
    {
        int res = unique_phonenumber(addressBook,new_phonenumber);//Validation for compare the new number is unique or not
        if(res == 1)
        {
            strcpy(addressBook->contacts[contact_index].phone,new_phonenumber);//If the all condition is valid store the new number into contact by using search function serial number stored index value
            for(int i = 0; i < addressBook->ir_size; i++)
            {
                int index = addressBook->index_record[i];//Index record will give the search contact index value in vaildation function like addressBook->index_record[0] = 1,addressBook->index_record[1] = 3,addressBook->index_record[2] = 5 for both name,phone number,mail id
                printf("%d-> %s %s %s",s_no,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
                s_no++;
                printf("\n");
            }
            printf("New phone number is successfully edited\n");
        }
        else
        {
            edit_phonenumber(addressBook,contact_index);//If validation is fail again re enter the new phone nuber by function call
        }
    }
    else
    {
        edit_phonenumber(addressBook,contact_index);//If validation is fail again re enter the new phone nuber by function call
    }
}
//Function definition for edit the mail id
void edit_mailid(struct AddressBook *addressBook,int contact_index)
{
    char new_mailid[50];
    printf("Enter the new email id: ");
    scanf("%s",new_mailid);//Read the new mail id input from user

    int s_no = 1;
    int ret = validate_mailid(new_mailid);//Validating the new mail id
    if(ret == 1)
    {
        int res = unique_mailid(addressBook,new_mailid);//Validation for compare the new email is unique or not
        if(res == 1)
        {
            strcpy(addressBook->contacts[contact_index].email,new_mailid);//If the all condition is valid store the new mail id into contact by using search function serial number stored index value
            for(int i = 0; i < addressBook->ir_size; i++)
            {
                int index = addressBook->index_record[i];//Index record will give the search contact index value in vaildation function like addressBook->index_record[0] = 1,addressBook->index_record[1] = 3,addressBook->index_record[2] = 5 for both name,phone number,mail id
                printf("%d-> %s %s %s",s_no,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
                s_no++;
                printf("\n");
            }
            printf("New email id is successfully edited\n");
        }
        else
        {
            edit_mailid(addressBook,contact_index);//If validation is fail again re enter the new mail id by function call
        }
    }
    else
    {
        edit_mailid(addressBook,contact_index);//If validation is fail again re enter the new mail id by function call
    }
}
//Function definition for read  the contact and load that contact in file
void Load_contacts_from_file(struct AddressBook *addressBook)
{
    FILE *fp = fopen("database.csv","r");//user will be update the some more contact using file IO with read mode

    if(fp == NULL)//If there is no file means it return null
    {
        return;
    }

    addressBook->contactCount = 0;//Start the contact count from zero so the previous value will be in same position
    int i = 0;
    int eof = 3;
    while( eof == 3)//The fscanf return 3 ,the end ot file will return -1 while(-1 == 3) condition fail loop stop
    {
        eof = fscanf(fp," %[^,], %[^,], %[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        
        if(eof == 3)
        {
          addressBook->contactCount++;
          i++;
        }
    }

    fclose(fp);//close the file
}

