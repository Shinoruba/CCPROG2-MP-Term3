/********************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of other students and/or persons. 

Jericho Raymund Z. Lirio, DLSU ID# 122*****
Yazan M. Homssi,          DLSU ID# 122*****
*********************************************************************************/


#include <stdio.h>
#include <string.h>

#define INVENTORY_FILENAME "inventory.txt"

#define MAX 100
typedef char str20[21];
typedef char str30[31];

typedef struct {
  int unit_price[MAX];
  char productID[MAX][10];
  int quantity[MAX];
  str30 item_name[MAX];
} Item;

/* loginPage() - is where the user is prompted to input the correct password and if their input is right, they're then sent to the main menu

@return 1 - would return 1 to the main function after 3 failed attempts where it'll terminate the program

@return 0 - would then end the loginPage function, allowing users entry to the main menu
*/

int loginPage() {
  int lock = 0; //locks the function making it loop until either the correct input is placed, or 3 incorrect inputs is made

  while (lock != 3 && lock != 4) {
    str20 pass = "$up3rv1sor", input;
    printf("\nHello User!\nPlease login! ^.^\nPassword: ");
    scanf("%s", input);

    if (strcmp(pass, input) == 0) {
      printf("\nWelcome User!\n");
      lock = 4;
    } else {
      printf("\nUnauthorized access not allowed\nPlease try again :p\n");
      lock++;
    }
  }
  if (lock == 3) {
    printf("\nSorry no more tries bozo\n");
    return 1;
  }
  return 0;
}

/*
viewInventory() - is used to view all of the products stored in the text file after being stored inside of the array

@param Item product[] - allows the function access to all of the contents stored in the "Inventory.txt" file

@param count - makes the function know how many items are stored in the "Inventory.txt" file
*/

void viewInventory(Item product[], int count) {
  int flag = 1; //makes it so that the functions knows whether the "Inventory.txt" file exist or not

  FILE *fp = fopen("inventory.txt", "r");
  if (fp == NULL) {
    printf("\nInventory file does not exist, please add products first!\n");
    flag = 0; // Exit the function if the file doesn't exist
  }

  if (flag == 1) {
    printf("Hello user! This is your inventory:\n\n");

    int i = 0;
    while (fscanf(fp, " %[^,], %[^,], %d, %d", product[i].productID[i],
                  product[i].item_name[i], &product[i].quantity[i],
                  &product[i].unit_price[i]) != EOF) {
      
      printf("ID: %s\nItem: %s\nQuantity: %d\nPrice: $%d\n\n",
             product[i].productID[i], product[i].item_name[i],
             product[i].quantity[i], product[i].unit_price[i]);

      i++;
      }
    fclose(fp);
  }
} 

/*
addProduct() - is used to add products to the struct and then puts all of the new content into the "Inventory.txt" file by appending it.

@param Item product[] - allows the function access to all of the contents stored in the "Inventory.txt" file

@param count - makes the function know how many items are stored in the "Inventory.txt" file, as well as incrementing it
*/

void addProduct(Item product[], int *count) { // just testing some things out
  int flag = 0, i = 0, ID = 0; //ID is used to temporarily store the product before adding to the "Inventory.txt" file
  char str[20]; //stores the ID temporarily
  
  printf("What's the product ID?: ");
  scanf("%s", str); 
  
  if(*count == 100){
      printf("\nMaximum Items stored, sorry :(\n");
      flag = 1;
  }

  for (i = 0; i < *count; i++) {
    if (strcmp(product[i].productID[i], str) == 0) {
      printf("ID already exists bozo :p");
      flag = 1;
    }
  }

  if (flag == 0) {
    strcpy(product[*count].productID[ID], str);
    
    printf("What's the name of the product?: ");
    scanf(" %100[^\n]", product[*count].item_name[ID]);

    printf("How many do you want to add?: ");
    scanf("%d", &product[*count].quantity[ID]);

    printf("How much does it cost?: $");
    scanf("%d", &product[*count].unit_price[ID]);

    printf("Item added successfully! :3");
    

    FILE *fp = fopen("inventory.txt", "a");

      fprintf(fp, "\n%s, %s, %d, %d", *product[i].productID,
              *product[i].item_name, *product[i].quantity,
              *product[i].unit_price);
    
    i++;
    fclose(fp);
    (*count)++;
  }

}

/*
updateProductQuantity() - is used to update the quantity inside of "Inventory.txt" file by asking the user to input a specific ID and then replacing it with the Quantity value

@param Item *product - allows the function access to all of the contents stored in the "Inventory.txt" file

@param count - makes the function know how many items are stored in the "Inventory.txt" file
*/

void updateProductQuantity(Item *product, int count) {
  int flag = 1;
  int i = 0; //"i" is reverted back to "0" each time this function is called to properly loop through every product
  char ch[50]; //Asks user for ID to search for

  FILE *fp = fopen("inventory.txt", "r+");
  if (fp == NULL) {
    printf("\nInventory file does not exist, please add products first!\n");
    flag = 0; // Exit the function if the file doesn't exist
  }

  if (flag == 1) {
        Item temp; // Temporary struct to store the product

        printf("Hello user! This is your inventory:\n\n");

        while (fscanf(fp, " %[^,], %[^,], %d, %d", temp.productID[i],
                      temp.item_name[i], &temp.quantity[i], &temp.unit_price[i]) == 4) {

            printf("ID: %s\nItem: %s\nQuantity: %d\nPrice: $%d\n\n",
                   temp.productID[i], temp.item_name[i],
                   temp.quantity[i], temp.unit_price[i]);
            i++;
        }

        printf("Which item do you want to edit the Quantity?\nID: ");
        scanf("%s", ch);

        for (int i = 0; i < count; i++) {
            if (strcmp(ch, temp.productID[i]) == 0) {
                printf("Please enter the new quantity: ");
                scanf("%d", &temp.quantity[i]);// Exit the loop after updating the specific product
            }
        }

        fseek(fp, 0, SEEK_SET);

        for (int j = 0; j < count; j++) {
            fprintf(fp, "%s, %s, %d, %d\n", temp.productID[j], temp.item_name[j], temp.quantity[j], temp.unit_price[j]);
        }

        printf("Price changed successfully!\n");

        fclose(fp);
    }
}

/*
updateProductPrice() - is used to update the price inside of "Inventory.txt" file by asking the user to input a specific ID and then replacing it with the Quantity value

@param Item *product - allows the function access to all of the contents stored in the "Inventory.txt" file

@param count - makes the function know how many items are stored in the "Inventory.txt" file
*/


void updateProductPrice(Item *product, int count) {
    int flag = 1;
    int i = 0;
    char ch[10];

    FILE *fp = fopen("inventory.txt", "r+");
    if (fp == NULL) {
        printf("\nInventory file does not exist, please add products first!\n");
        flag = 0;
    }

    if (flag == 1) {
        Item temp; // Temporary struct to store the product

        printf("Hello user! This is your inventory:\n\n");

        while (fscanf(fp, " %[^,], %[^,], %d, %d", temp.productID[i],
                      temp.item_name[i], &temp.quantity[i], &temp.unit_price[i]) == 4) {

            printf("ID: %s\nItem: %s\nQuantity: %d\nPrice: $%d\n\n",
                   temp.productID[i], temp.item_name[i],
                   temp.quantity[i], temp.unit_price[i]);
            i++;
        }

        printf("Which item do you want to edit the price?\nID: ");
        scanf("%s", ch);

        for (int i = 0; i < count; i++) {
            if (strcmp(ch, temp.productID[i]) == 0) {
                printf("Please enter the new price: ");
                scanf("%d", &temp.unit_price[i]);// Exit the loop after updating the specific product
            }
        }

        fseek(fp, 0, SEEK_SET);

        for (int j = 0; j < count; j++) {
            fprintf(fp, "%s, %s, %d, %d\n", temp.productID[j], temp.item_name[j], temp.quantity[j], temp.unit_price[j]);
        }

        printf("Price changed successfully!\n");

        fclose(fp);
    }
}

/*
searchProduct() is used to search the entire content of "Inventory.txt" for the specific product or ID the user is searching for, it asks whether the user wants to search for ID or Name.

@param Item product[] allows the function access to all of the contents stored in the "Inventory.txt" file

@param count makes the function know how many items are stored in the "Inventory.txt" file
*/

void searchProduct(Item product[], int count) {
  int flag = 1, flag2 = 1, choice = 0;
  char str[20]; //str[] is used to search for either the ID or Name
  
  FILE *fp = fopen("inventory.txt", "r");
  if (fp == NULL) {
    printf("\nInventory file does not exist, please add products first!\n");
    flag = 0; // Exit the function if the file doesn't exist
  }
   int i = 0;
   while (fscanf(fp, " %[^,], %[^,], %d, %d", product[i].productID[i],
                  product[i].item_name[i], &product[i].quantity[i],
                  &product[i].unit_price[i]) != EOF) {
      i++;
    }

  if (flag == 1) {
    printf("Hello user!\nsearch with ID or name?\n1) ID\n2) Name\nChoice: ");
    scanf("%d", &choice);

  if(choice == 1 || choice == 2){
    switch(choice){
      case 1: printf("Please enter ID: "); //Searches by ID
              scanf("%s", str);
                for(int j = 0; j < i; j++){
                if(strcmp(str, product[j].productID[j]) == 0){
                  
                printf("\nID: %s\nItem: %s\nQuantity: %d\nPrice: $%d\n\n",
                product[j].productID[j], product[j].item_name[j],
                product[j].quantity[j], product[j].unit_price[j]);
                flag2 = 0;
                } 
              } if(flag2 == 1){
                  printf("\nItem not found\n");
                }
              break;

      case 2: printf("Please enter name: "); //Searches by name
              scanf("%s", str);
              for(int j = 0; j < i; j++){
                if(strcmp(str, product[j].item_name[j]) == 0){
                  
                printf("\nID: %s\nItem: %s\nQuantity: %d\nPrice: $%d\n\n",
                product[j].productID[j], product[j].item_name[j],
                product[j].quantity[j], product[j].unit_price[j]);
                flag2 = 0;
                } 
              } if(flag2 == 1){
                  printf("\nItem not found\n");
                }
              break;
      
      default: printf("Input invalid");
              break;
      }
    } else {
      printf("Invalid input");
    }
  }
}

/*
updateProductName() - is used to search the entire content of "Inventory.txt" for the specific product the user is searching for and changes the name. It asks the user to input the ID of the product

@param Item product[] - allows the function access to all of the contents stored in the "Inventory.txt" file

@param count - makes the function know how many items are stored in the "Inventory.txt" file
*/

void updateProductName(Item *product, int count) {
  int flag = 1;
  int i = 0;
  char ch[50]; //Asks user for ID to search for 

  FILE *fp = fopen("inventory.txt", "r+");
  if (fp == NULL) {
    printf("\nInventory file does not exist, please add products first!\n");
    flag = 0; // Exit the function if the file doesn't exist
  }

  if (flag == 1) {
    Item temp; // Temporary structure to store the product
    printf("Hello user! This is your inventory:\n\n");

    while (fscanf(fp, " %[^,], %[^,], %d, %d", temp.productID[i],
          temp.item_name[i], &temp.quantity[i], &temp.unit_price[i]) == 4) {

      printf("ID: %s\nItem: %s\nQuantity: %d\nPrice: $%d\n\n",
             temp.productID[i], temp.item_name[i],
             temp.quantity[i], temp.unit_price[i]);
      i++;
    }

    printf("Which item do you want to edit the name?\nID: ");
    scanf("%s", ch);
    getchar();
    
        for (i = 0; i < count; i++) {
            if (strcmp(ch, product[i].productID[i]) == 0) {
                printf("Please enter the new name: ");
                scanf(" %100[^\n]", temp.item_name[i]);
              
            }
        }

          fseek(fp, 0, SEEK_SET);
            for (int j = 0; j < count; j++) {
                fprintf(fp, "%s, %s, %d, %d\n", temp.productID[j], temp.item_name[j], temp.quantity[j], temp.unit_price[j]);
            }
            printf("Name changed successfully!\n");
        } else {
            printf("Item not found\n");
        }

        fclose(fp);
  }

/*
priceRange() - asks the user to input the minimum and maximum price they want
and the program finds the products that is between or equal to the prices the user wants 
@param Item product[] - allows the function access to all of the contents stored in the "Inventory.txt" file

@param count - makes the function know how many items are stored in the "Inventory.txt" file
*/

void priceRange(Item product[], int count){
  int cheapest = 0, expensive = 0, flag = 1; //cheapest gets the minimum value while expensive gets the maximum value

  printf("Hello user!\nEnter minimum price: ");
  scanf("%d", &cheapest);

  printf("Enter maximum price: ");
  scanf("%d", &expensive);

  for(int i = 0; i < count; i++){
    if(product[i].unit_price[i] >= cheapest && product[i].unit_price[i] <= expensive){
       printf("\nID: %s\nItem: %s\nQuantity: %d\nPrice: $%d\n\n",
             product[i].productID[i], product[i].item_name[i],
             product[i].quantity[i], product[i].unit_price[i]);
             flag = 0; 
    }  
  }
  if(flag == 1){
      printf("No products found within that price range :((");
    }
}

/*
deleteAll() - asks the user if they want to delete all the contents of "Inventory.txt" file, if they input yes it deletes everything, if no then the contents remain unchanged
*/

void deleteAll(){
  char choice[20]; //Gets the choice between yes or na
  printf("\nAre you sure you want to delete all contents?\n\nyes or no: ");
  scanf("%s", choice);

  if(strcmp(choice, "yes") == 0){
    FILE *fp = fopen("inventory.txt", "w");
    fprintf(fp, " ");
    fclose(fp);
    printf("\nDeleted Successfully!!!\n\n");

  } else if(strcmp(choice, "no") == 0){
    printf("Oki ^.^\n");
    } 
}

/*
main() - is the main function of the program serving as the main menu as well. The user is shown all of the options the program has to offer, including the extras as well. The main function is also where the "Inventory.txt" file contents are read to be stored inside the structs to be used by other functions.
*/

int main() {
  Item product[MAX]; //The array of structures stores up to 100 products
  int lock = 0, choice = 0, count = 0; //count is incremented to know how many products are stored
  int flag = 1;

  if (loginPage() == 1) {
    return 0;
  } //ends the program if 3 failed attempts are made

  FILE *fp = fopen("inventory.txt", "r");
  if (fp == NULL) {
    printf("\nInventory file does not exist, please add products first!\n");
    flag = 0; // Exit the function if the file doesn't exist
  }

  if (flag == 1) {
    int i = 0;
    while (fscanf(fp, " %[^,], %[^,], %d, %d", product[i].productID[i],
                  product[i].item_name[i], &product[i].quantity[i],
                  &product[i].unit_price[i]) != EOF) {

      count++;
      i++; 
    } //scans the contents of "Inventory.txt" and stores it in the structures
    fclose(fp);
  }

  while (lock == 0) {
    printf("\nHey!hey!hey! User!!!! ^w^\nWelcome To the program!!!\n");
    printf("\nWhat would you like to do?\n\n1) View Inventory\n\n2) Add "
           "Product\n\n3) Update Product Quantity\n\n4) Update Product "
           "Price\n\n5) Search Product\n\n0) Exit\n");

    printf("\n\n!!Extras!!\n\n6) Edit Product Name\n\n7) Find by Price Range\n\n8) Delete All Contents\n");
    printf("\nChoice: ");

    scanf("%d", &choice);
    switch (choice) {
    case 1:
      viewInventory(product, count); //Goes to the view inventory function
      break;

    case 2:
      addProduct(product, &count); //Goes to the add products function
      break;

    case 3:
      updateProductQuantity(product, count); //Goes to the update quantity function
      break;

    case 4:
      updateProductPrice(product, count); //Goes to the update price function
      break;

    case 5:
      searchProduct(product, count); //Goes to the search product function
      break;

    case 0: 
      printf("\nTHANK YOU FOR USING THE PROGRAM!!! ^v^\n"); //closes the program
      lock = 1;
      break;

    case 6:
      updateProductName(product, count); //Goes to the update name function
      break;

    case 7:
      priceRange(product, count); //Goes to the price range function
      break;

    case 8:
      deleteAll(); //Goes to the delete all function
      break;
    }
  }
  return 0;
}
