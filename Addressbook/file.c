#include <stdio.h>
#include "contact.h"
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
 {
    
    FILE *fp = fopen("contacts.txt", "w");

   
    printf("Contacts saved successfully\n");

  for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s %s %s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }

    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt","r");

    if(fp == NULL)
    {
        printf("does not open the file\n");
        return;
    }

    fscanf(fp, "contactCount %d\n",&addressBook->contactCount);

    
    for(int i=0; i<addressBook->contactCount; i++)
    {
        fscanf(fp, "%s\n",addressBook->contacts[i].name);
        fscanf(fp, "%s\n",addressBook->contacts[i].phone);
        fscanf(fp, "%s\n",addressBook->contacts[i].email);
    }

    fclose(fp);
    
}