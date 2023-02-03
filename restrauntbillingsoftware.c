#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

struct items{
    char item[20];
    float price;
    int quantity;
};

struct orders{
    char name[50];
    char date[50];
    int NoOfItems;
    struct items itm[50];
};
//functions to generate biils
void generateBillHeader(char name[50],char date[30])
{
    printf("\n\n");
        printf("\t\tRESTRAUNT NAME");
        printf("\n\t      ------------------");
        printf("\nDate:%s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("---------------------------------------\n");
        printf("Items\t\t");
        printf("Quantity\t\t");
        printf("Total\t\t");
        printf("\n---------------------------------------");
        printf("\n\n");
}

void generateBillBody(char item[30],int quantity, float price)
{
    printf("%s\t\t",item); 
        printf("%d\t\t",quantity); 
        printf("%.2f\t\t",quantity * price); 
        printf("\n");
}

void generateBillFooter(float total)
{
    printf("\n");
    float discount = 0.1*total;
    float netTotal = total-discount;
    float cgst = 0.09*netTotal;
    float sgst = 0.09*netTotal;
    float grandTotal = netTotal + cgst + sgst;
    printf("-------------------------------------------\n");
    printf("Sub total\t\t\t%.2f\n", total);
    printf("Discount @10%%\t\t\t%0.2f\n", discount);
    printf("\t\t\t\t-----------");
    printf("\n");
    printf("Net Total\t\t\t%0.2f\n\n", netTotal);
    printf("CGST\t\t\t  \t%0.2f\n", cgst);
    printf("SGST\t\t\t  \t%0.2f\n", sgst);
    printf("-------------------------------------------\n");
    printf("Grand Total\t\t\t%0.2f\n", grandTotal);
    printf("-------------------------------------------\n");
}

int main()
{
    int operation,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y',ContFlag = 'y';
    char NAME[50];
    FILE *fp;
       //dashboard
    while(ContFlag == 'y')
    {
    float total = 0;
    int InvoiceFound = 0;
    printf("\t============RESTAURANT NAME============");
    printf("\n\nPlease select your prefered operation");
    printf("\n\n1.Generate Invoice");
    printf("\n2.Show all Invoices");
    printf("\n3.Search Invoice");
    printf("\n4.Exit");

    printf("\n\nYour choice:\t");
    scanf("%d",&operation);
    fgetc(stdin);
    switch(operation)
    {
        case 1:
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.name,50,stdin);
        ord.name[strlen(ord.name)-1] = 0;
        strcpy(ord.date,__DATE__);
        printf("\nPlease enter the number of items:\t");
        scanf("%d",&n);
        ord.NoOfItems = n;
        for(int i=0;i<n;i++)
        {
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d:\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please enter the quantity:\t");
            scanf("%d",&ord.itm[i].quantity);
            printf("Please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total += ord.itm[i].quantity * ord.itm[i].price;
        }

        generateBillHeader(ord.name,ord.date);
        for(int i=0;i<ord.NoOfItems;i++){
            generateBillBody(ord.itm[i].item,ord.itm[i].quantity,ord.itm[i].price);
        }
        generateBillFooter(total);

        printf("\nDo you want to save the invoice [y/n]:\t");
        scanf("%s",&saveBill);

        if(saveBill == 'y')
        {
            fp = fopen("RestrauntBill.dat","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fwrite != 0)
            printf("\nSuccessfully saved");
            else 
            printf("\nError saving");
            fclose(fp);
        }
        break;

        case 2:
        fp = fopen("RestrauntBill.dat","r");
        printf("\n  *****Your Previous Invoices*****\n");
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            generateBillHeader(order.name,order.date);
            for(int i=0;i<order.NoOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].quantity,order.itm[i].price);
                tot+=order.itm[i].quantity * order.itm[i].price;
            }
            generateBillFooter(tot);
        }
        fclose(fp);
        break;

        case 3:
        printf("Enter the name of the customer:\t");
        fgets(NAME,50,stdin);
        NAME[strlen(NAME)-1] = 0;
        fp = fopen("RestrauntBill.dat","r");
        printf("\t*****Invoice of %s*****",NAME);
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            if(!strcmp(order.name,NAME)){
            generateBillHeader(order.name,order.date);
            for(int i=0;i<order.NoOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].quantity,order.itm[i].price);
                tot+=order.itm[i].quantity * order.itm[i].price;
            }
            generateBillFooter(tot);
            InvoiceFound = 1;
            }
        
        }
        if(!InvoiceFound){
            printf("Sorry the invoice for %s doesnot exists",NAME);
        }
        fclose(fp);
        break;

    case 4:
    printf("\n\t\t Bye Bye \n\n");
    exit(0);
    break;

    default:
    printf("Sorry invalid option");
    break;
    }
    printf("\nDo you want to perform another operation?[y/n]:\t");
    scanf("%s",&ContFlag);
    }
    printf("\n\t\t Bye Bye \n\n");
    printf("\n\n");
    getch();
    return 0;
}