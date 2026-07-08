/* Name : Anita Moodur
Date : 28 / 4 / 2026 
Batch Id : 26001B_043


Address Book Project : 

This project was designed to save N number of contacts and to perform the certain operations. 


It has Home Page Menu with following options :
  
1.Creating the Contacts that stores name,phone number, Email ID of a person.
2.Searching particular contact using
     ->Name
     ->Phone number
     ->Email ID
3.Editing the contact (Name,Phone number, Email at a time )
4.Deleting particular contact by searching and finding particular contact
5.List the available contacts
6.save those contacts in file(csv) and exits the process.

->By pressing any options from 1 to 6, we can perform desired operations....
[9:56 PM, 4/28/2026] Shivu: Idu documentation
[9:57 PM, 4/28/2026] Shivu: Main.c li first idna add maadi comment maadu /* */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
#include<ctype.h>


void listContacts(AddressBook *addressBook) 
{

    if (addressBook->contactCount == 0) 
    {
        printf("No contacts found!\n");
        return;
    }
    
     printf("--------------------------------------------------------------------------\n");
     printf("R.No\t\tName\t\tPhone_Number\t\tEmail_Id\n");
     printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%d\t\t%s\t\t%s\t\t%s\n", i + 1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }   
}
    
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    
    
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);

}
   
void createContact(AddressBook *addressBook)
{ 
  if (addressBook->contactCount >= MAX_CONTACTS)
     
  { 
     printf("Address book is full!\n");
     return;    
   } 
        
   Contact *c = &addressBook->contacts[addressBook->contactCount];
          
   int i, valid, attempt;
          
         attempt = 0;
           
   while (attempt < 3)
            
   {
                
    valid = 1;
                
    printf("\nAttempt %d\n", attempt + 1);
    printf("Enter Name: ");
    scanf(" %[^\n]", c->name); 


                   
    for (i = 0; c->name[i] != '\0'; i++) 
                   
    {
                    
        if (!isalpha(c->name[i]) && c->name[i] != ' ')
                    
        {
             
            valid = 0;
                     
            break; 
                    
        } 
                    
    }
                    
    if (valid && strlen(c->name) >= 4)
    {
    
        break;
    }
    
                    
    else 
    {
        if(strlen(c->name) < 4)
            printf("Name must cotain at least 4 characters.\n");
       else
            printf("Invalid name! Only alphabets allowed.\n");

    
     attempt++; 
    }
}
                   
if (attempt == 3)
                        
{
                         
    printf("Failed to enter valid name.\n");
    return; 
                         
} 
            
                        
attempt = 0; 
                         
while (attempt < 3) 
                         
{ 
                          
    valid = 1;
                           
    printf("Attempt %d - Enter Phone: ", attempt + 1); 
    scanf("%s", c->phone); 
                            
    
                             
    if (strlen(c->phone) != 10) 
    {
    printf("Invalid phone! Must be exactly 10 digits.\n");
    valid = 0;
    }
    
    if (!(c->phone[0] >= '6' && c->phone[0] <= '9'))
    {
       printf("Invalid phone! Must start with digits 6 to 9.\n");

       valid = 0;
    } 
                           
    for(i = 0; c->phone[i] != '\0'; i++) 
                            
    {
                              
        if (!isdigit(c->phone[i]))
                              
        {
            printf("Invalid phone! Only digits are allowed.\n");                    
            valid = 0;
                                  
            break;
        } 
                               
    } 
                               
    if (valid)
                               
    break; 
                               
    else 
                               
         attempt++; 
                
                            
} 
                            
if (attempt == 3) 
                           

{
                              
    printf("Failed to enter valid phone.\n"); 
                               
    return;
                               
} 
                        
                                
attempt = 0;
                                 
while (attempt < 3) 
                                  
{ 
                                   
    valid = 1;
    int at_count = 0; 
                                    
    printf("Attempt %d - Enter Email: ", attempt + 1); 
                                     
    scanf("%s", c->email); 
                        
                                    
    for (i = 0; c->email[i] != '\0'; i++)
                                     
    { 
                                      
        if (isupper(c->email[i])) 
                                       
        { 
                                         
            valid = 0;
            printf("Email must be lowercase.\n");
                                         
            break;
                                       
        }
                                            
                                      
    } 
                            
                                      
    for (i = 0; c->email[i] != '\0'; i++) 
                                      
    {
                                        
        if (c->email[i] == '@')
                                        
                                        
        at_count++; 
                                       
    } 
                                        
    if (at_count != 1)
    {
       printf("Email must contain exactly one '@'.\n");
    
        valid = 0; 
    }
                                      
    
    if (strstr(c->email, "gmail") == NULL)
    {
        printf("Email must contain 'gmail'.\n");
                                        
    valid = 0; 
    }
                        
     
                        
    if (strstr(c->email, ".com") == NULL)
        {
            printf("Email must contain '.com'.\n");
            valid = 0;
        }

    int len = strlen(c->email);

     if (len < 4 || strcmp(&c->email[len - 4], ".com") != 0)
    {
       printf("Email must end with '.com'.\n");
       valid = 0;
    }  
    
    if (strstr(c->email, "..") != NULL)
   {
       printf("Email must not contain consecutive dots '..'.\n");
       valid = 0;
   }
    
                    
    if (valid)
                        
    break;
                        
    else 

     attempt++;
                        
     
} 
                        
if (attempt == 3) 
                        
{ 
                        
    printf("Failed to enter valid email.\n"); 
                         
    return;
                         
}
                
                          
addressBook->contactCount++;
                          
printf("Contact added successfully!\n");
}             


void searchContact(AddressBook *addressBook)
{
    int option;
    char input[50];
    int found = 0;

    if (addressBook->contactCount == 0)
    {
        printf("Address book is empty!\n");
        return;
    }

    printf("1. Search by Name\n2. Search by Phone\n3. Search by Email\n");
    printf("Enter your choice: ");
    scanf("%d", &option);

    while (getchar() != '\n');

    if (option == 1)
        printf("Enter Name: ");
    else if (option == 2)
        printf("Enter Phone: ");
    else if (option == 3)
        printf("Enter Email: ");
    else
    {
        printf("Invalid choice!\n");
        return;
    }

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((option == 1 && strcmp(input, addressBook->contacts[i].name) == 0) ||
            (option == 2 && strcmp(input, addressBook->contacts[i].phone) == 0) ||
            (option == 3 && strcmp(input, addressBook->contacts[i].email) == 0))
        {
            if (found == 0)
                printf("\nContact Found:\n");

            printf("Name : %s\n", addressBook->contacts[i].name);
            printf("Phone: %s\n", addressBook->contacts[i].phone);
            
            printf("Email: %s\n\n", addressBook->contacts[i].email);

            found = 1;
        }
    }

    if (!found)
        printf("Contact not found\n");
}

void editContact(AddressBook *addressBook)
{
    int index;

    if(addressBook->contactCount == 0)
    {
        printf("Address book is empty!\n");
        return;
    }

    printf("Contact List:\n");
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d. %s | %s | %s\n", i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }


    printf("Enter serial number to edit: ");
    scanf("%d", &index);

    
    if(index < 1 || index > addressBook->contactCount)
    {
        printf("Invalid choice!\n");
        return;
    }
    int i = index - 1;

    printf("Enter new name: ");
    scanf("%s", addressBook->contacts[i].name);

    printf("Enter new phone: ");
    scanf("%s", addressBook->contacts[i].phone);

    printf("Enter new email: ");
    scanf("%s", addressBook->contacts[i].email);

    printf("Contact updated successfully!\n");
}


void deleteContact(AddressBook *addressBook)
{
    int serial;
    
    if (addressBook->contactCount == 0)
    {
        printf("Address book is empty!\n");
        return;
    }
    printf("\nContact List:\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d. %s | %s | %s\n", i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("Enter serial number to delete: ");
    scanf("%d", &serial);

    
    if (serial < 1 || serial > addressBook->contactCount)
    {
        printf("Invalid serial number!\n");
        return;
    }

    int index = serial - 1;

    
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully!\n");
}
    