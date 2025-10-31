#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h> 
int Little_big(int size){
    char *d=(char *)&size;
    for(int i=0;i<sizeof(size)/2;i++){
        char temp=d[i];
        d[i]=d[sizeof(size)-i-1];
        d[sizeof(size)-i-1]=temp;
    }
    return size;
}
void read_tags(char *tags,FILE *file){
    fread(tags,4,1,file);
    tags[4]='\0';
    if(tags[0]=='\0') 
    {
        printf("error");
        exit(0);
    }
}
void read_size(int *size,FILE *file_2){
    fread(size,4,1,file_2);
    *size=Little_big(*size);
    // fseek(file_2,3,SEEK_CUR);
}
void read_size_1(int *size,FILE *file_2){
    fread(size,4,1,file_2);
    *size=Little_big(*size);
     fseek(file_2,3,SEEK_CUR);
}
void read_data(char *data,FILE *file_3,int size){
  //  printf("Ftell => %ld\n", ftell(file_3));
  if(size<=0 || size>49){
    printf("invalid input");
    //exit(EXIT_FAILURE);
    exit(0);
  }
    fread(data,size-1,1,file_3);
   // printf("Size in func => %d\n", size);
   // printf("Len ==> %ld\n Data ==> %s\n",sizeof(data) ,data);
    data[size-1]='\0';
}


void View_operation(char *file){
    FILE *file_1=fopen(file,"rb");
    if(file_1==NULL){
        printf("file not present");
        return;
    }
    fseek(file_1,10,SEEK_SET);
    char tags[5],data[50];
    int size;
    for(int i=0;i<6;i++){
    read_tags(tags,file_1);
    read_size_1(&size,file_1);
    read_data(data,file_1,size);
    // printf("%s",tags);
    // printf("%d",size);
        // char buffer[size+1];
        // fread(buffer,size-1,1,file_1);
        // buffer[size]='\0';

        if(strcmp(tags,"TPE1")==0){
            printf("artist : %s\n",data);
        }
        else if (strcmp(tags,"TIT2")==0)
        {
            printf("Title name : %s\n",data);
        }
        else if (strcmp(tags,"TALB")==0)
        {
            printf("album : %s\n",data);
        }
        else if (strcmp(tags,"TYER")==0)
        {
            printf("Year : %s\n",data);
        }
        else if (strcmp(tags,"TCON")==0)
        {
            printf("content type : %s\n",data);
        }
        
        
    }
    printf("comment : ");
    if(strcmp(tags,"COMM")==0){
        for(int i=0;i<24;i++){
            printf("%c",data[i]);
        }
        
        
    }
   
    

fclose(file_1);
}

int edit_operation(char *file_name,char *option_flag){
    char modifier[10];
    char new_value[50];
   
        if(strcmp(option_flag,"-t")==0)
        {
            strcpy(modifier, "TPE1");
        }
        else if(strcmp(option_flag,"-r")==0)
        {
            strcpy(modifier,"TIT2");
        }
        else if(strcmp(option_flag,"-T")==0)
        {
            strcpy(modifier, "TALB");
        }
        else if(strcmp(option_flag,"-y")==0)
        {
            strcpy(modifier, "TYER");
        }
       else  if(strcmp(option_flag,"-c")==0)
        {
            strcpy(modifier, "TCON");
        }
        else if(strcmp(option_flag,"-o")==0)
        {
            strcpy(modifier,"COMM");
        }
        else{
            printf("invalid file the");
            //fclose(file_temp);
            //fclose(file_E);
             return 1;
        }
        FILE *file_E=fopen(file_name,"r");
        if(file_E==NULL){
            printf("invalid file name");
            return 1;
        }
        FILE *file_temp = fopen("temp.mp3","w");
        // printf("%s",file_temp);
         if(file_temp==NULL){
             printf("Invalid file");
             fclose(file_temp);
             return 1;
         }
    //     char header1[4];
    //     fread(header1,1,3,file_E);
    //    // printf("su")
    //     header1[4]='\0';
    //    // printf("%s",header1);
    //     if(strncmp(header1,"ID3",3)!=0){
    //         printf("invalid mp3 name");
    //         fclose(file_E);
    //         fclose(file_temp);
    //         return 1;
    
    //     }
        char tags1[5]={0};
        char header[10];
        rewind(file_E);
        rewind(file_temp);
        fread(header,10,1,file_E);
       
        fwrite(header,10,1,file_temp);
    
        
        
           // int size1;
           // read_tags(tags1,file_E);
    
           // read_size(&size1,file_E);

        printf("enter the new value %s : ",modifier);
        // getchar();
        scanf("%[^\n]",new_value);
        // new_value[strcspn(new_value,"\n")]=0;

    for(int i=0;i<6;i++)
    {
        char tags[5],data[50];
        int size;
        char flag[3];

        read_tags(tags,file_E);  //4
       // printf("Tag ==> %s\t", tags);
        read_size(&size,file_E); //4
       // printf("==> %d\n", size);
       // printf("In main ==> %ld\n", ftell(file_E));
        fread(flag,3,1,file_E); //3
        read_data(data,file_E,size);

    fwrite(tags,4,1,file_temp);
    if(strcmp(tags,modifier)==0)
     {
         int new_len=strlen(new_value)+1;
         int swapped=Little_big(new_len);
         fwrite(&swapped,4,1,file_temp);
         fwrite(flag,3,1,file_temp);
         fwrite(new_value,new_len-1,1,file_temp);
      }
      else
      {
         int ori_size=Little_big(size);
        
         fwrite(&ori_size,4,1,file_temp);
         fwrite(flag,3,1,file_temp);
         fwrite(data,size-1,1,file_temp);
      }
    }
    fclose(file_temp);
    fclose(file_E);
     remove(file_name);
     rename("temp.mp3",file_name);
    printf("updated successfully");
    return 0;
}

int main(int argc,char *argv[]){

    if(argc<3){
        printf("usage:%s -v <file.name><tags>",argv[0]);
        printf("usage:%s -e <file.name><tags>",argv[0]);
        return 1;
    }
    if(strcmp(argv[1],"-v")==0){
        View_operation(argv[2]);
    }
    else if(strcmp(argv[1],"-e")==0){
        if(argc<4){
            printf("error");
            return 1;
        }
        edit_operation(argv[2], argv[3]);
    }
    else{
        printf("invalid operation ");
    }
    return 0;
}