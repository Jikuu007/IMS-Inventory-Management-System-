#include<stdio.h>
#include<string.h>

struct Item
{
	int ID;
	char name[20];
	int PQ; //Product quantity จำนวนสินค้า
	float price;
};
int main(){
	struct Item item[100]; //รับ item ได้ 100 
	int numItem = 0;
	int choice;
	loadfile(item,&numItem);
	do{
		printf("\nInventory Management System\n");
		printf("1.ADD Item\n");
		printf("2.View Item\n");
		printf("3.Edit Item\n");
		printf("4.Delete Item\n");
		printf("5.Save to file\n");
		printf("6.Exit\n");
		printf("Enter your choice:");
		scanf("%d",&choice);

		switch(choice){
			case 1:addItem(item, &numItem); break;
			case 2:viewItem(item, numItem); break;
			case 3:editItem(item, numItem); break;
			case 4:deleteItem(item, &numItem); break;
			case 5:saveItemtoFile(item, numItem); break;
			case 6: printf("Exiting...\n");
			default: printf("The system is closed.\n");
		}
	}while(choice !=6);

	return 0;
}
void addItem(struct Item item[],int *numItem){
	printf("Enter Item ID:");
	scanf("%d",&item[*numItem].ID);
	printf("Enter Item Product name:");
	scanf("%s",item[*numItem].name);
	printf("Enter Product quantity:");
	scanf("%d",&item[*numItem].PQ);
	printf("Enter Price:"); 
	scanf("%f",&item[*numItem].price);
	(*numItem)++;
	printf("add itme DONE!!\n");
}
void viewItem(struct Item item[],int numItem){
	printf("\nItem list: \n");
	printf("ID\tName\t\tQuantity\tPrice\n");
	for(int i = 0; i < numItem; i++){
		printf("%d\t%s\t\t%d\t\t%.2f\n",item[i].ID,item[i].name,item[i].PQ,item[i].price);
	}
	
}
void editItem(struct Item item[], int numItem){
	int ID, found = 0;
	printf("Enter Item edit :");
	scanf("%d",&ID);
	for(int i = 0; i < numItem; i++){
		if(item[i].ID == ID){
			found = 1;
			printf("Enter new item name:");
			scanf("%s",item[i].name);
			printf("Enter new item Quantity:");
			scanf("%d",&item[i].PQ);
			printf("%d",&item[i].price);
			printf("Item Update Done!!");
			break;
		}
	}
	if(!found){
		printf("Item with ID %d not found.\n",ID);
	}
}
void deleteItem(struct Item item[],int *numItem){
	int ID, found = 0;
	printf("Enter Item ID to delete: ");
	scanf("%d",&ID);
	for(int i = 0; i < *numItem; i++){
		if(item[i].ID == ID){
			found = 1;
			for(int L = i;L < *numItem - 1; L++ ){
				item[L] = item[L + 1]; // เลือก Item ไปที่ Index ก่อนหน้า
			}
			(*numItem)--;
			printf("Item delete item DONE!!\n");
			break;
		}
	}
	if(!found){
		printf("Item with ID %d not found.\n");
	}
}
void saveItemtoFile(struct Item item[],int numItem){
	FILE *file = fopen("inventory.txt","w");
	if(file == NULL){
		printf("Error opening file. \n");
		return;
	}
	for(int i = 0; i < numItem; i++){
		fprintf(file, "%d %s %d %.2f\n", item[i].ID,item[i].name,item[i].PQ,item[i].price);
	}
	fclose(file);
	printf("Data saved to file DONE!!\n");
}
void loadfile(struct Item item[], int *numItem){

	FILE *file = fopen("inventory.txt","r");
	if (file == NULL){
		printf("ERROR opening file or file not found.\n");
		return;
	}
	while(fscanf(file, "%d %s %d %f", &item[*numItem].ID,item[*numItem].name,&item[*numItem].PQ,&item[*numItem].price) != EOF){
		(*numItem)++;
	}
	fclose(file);
	printf("Data loaded from file DONE!!.\n");
}
