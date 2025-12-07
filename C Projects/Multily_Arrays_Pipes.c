#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {

  int i = 0, j = 0, k = 0, l = 0, i1 = 0, j1 = 0; //Dilwsh metritwn, pinakwn gia pollaplasiasmo kai teliko pinaka, file descriptors 
  int **pin1, **pin2, **pin3;                     // gia ta pipes kai arithmo grammwn-stilwn pou tha paroume ws parametroi apo thn 
  int fd1[2], fd2[2];                             // grammh entolwn
  int rows1, cols1, rows2, cols2, count = 0;
        
        rows1 = atoi(argv[1]);
        cols1 = atoi(argv[2]);
        rows2 = atoi(argv[3]);                     //Metatropi strings se akeraious gia grammes-sthles
        cols2 = atoi(argv[4]);              
             
        if (cols1 != rows2) {
              printf("Den mporoume na pollaplasiasoume 2 pinakes an den einai isos a arithmos twn sthlwn tou 1ou me ton arithmo twn grammwn tou 2ou pinaka!\n");
              exit(EXIT_FAILURE);
        }

        pin1 = (int **)malloc(rows1 * sizeof(int *));       //Dhmiourgia pinakwn, anathesi tyxaiwn timwn gia ta stoixeia tous kai 
                                                            //emfanish
        for (i = 0; i < rows1; i++) {
          pin1[i] = (int *)malloc(cols1 * sizeof(int));
        }
       
        for (i = 0; i < rows1; i++) {
          for (j = 0; j < cols1; j++) {
                 pin1[i][j] = rand() % 21;
          }
        }
        printf("Disdiastatos pinakas 1 me tyxaious arithmous:\n");
      
        for (i = 0; i < rows1; i++) {
          for (j = 0; j < cols1; j++) {
              printf("%d\t", pin1[i][j]);
          }
          printf("\n");
        }
        printf("\n");
  
        pin2 = (int **)malloc(rows2 * sizeof(int *));  
  
        for (i = 0; i < rows2; i++) {
            pin2[i] = (int *)malloc(cols2 * sizeof(int));
        }
        
        for (i = 0; i < rows2; i++) {
            for (j = 0; j < cols2; j++) {
                   pin2[i][j] = rand() % 21;
            }
        }
         
        printf("Disdiastatos pinakas 2 me tyxaious arithmous:\n");

        for (i = 0; i < rows2; i++) {
            for (j = 0; j < cols2; j++) {
                printf("%d\t", pin2[i][j]);
            } 
            printf("\n");
        }
        printf("\n");
        
        pin3 = (int **)malloc(rows1 * sizeof(int *));
        
        for (i = 0; i < rows1; i++) {
            pin3[i] = (int *)malloc(cols2 * sizeof(int));
        }
         
        for (i1  = 0; i1 < rows1; i1++) {               //Pollaplasiazoume kathe grammi tou 2ou pinaka kai stili tou 1ou 
              for (j1 = 0; j1 < cols2; j1++) {          // kai to apotelesma mpanei ston trito pinaka kai sthn thesi pou orizei h
                                                        //h grammh tou 1ou pinaka kai  stili tou 2ou
                   pin3[i1][j1] = 0;
                   count++;
                  
                  if (pipe(fd1) < 0) {                  //Mhnuma se periptosi pou prokypsei sfalma sta pipes
                          printf("Pipe failed!");
                          printf("Error Number : %d\n", errno);
                          perror("Error Description");
                          return (-1);
                  }

                  if (pipe(fd2) < 0) {
                        printf("Pipe failed!");
                        printf("Error Number : %d\n", errno);
                        perror("Error Description");
                        return (-1);
                  }

                  pid_t cpid = fork();      //Gia kathe stoixeio tou 3ou pinaka pou tha ypologisoume se kathe thygatrikh diergasia
                  
                  if (cpid < 0) {
                            printf("Fork failed!\n");  //Mhnuma se periptosi pou prokypsei sfalma sthn fork
                            exit(0);
                            return (-1);
                  }                      

                  if (cpid > 0) {     

                      close(fd1[0]);     //Sto pipe 1 kleinoume to akro gia anagnwsi kai sto pipe 2 kleinoume to akro gia eggrafi
                      close(fd2[1]);     

                      write(fd1[1], &i1, sizeof(int));  //Grafoume grammes, sthles, twn 3 pinakwn kai thn thesi tou stoixeiou pou  
                      write(fd1[1], &j1, sizeof(int));  //ypologizoume
                      write(fd1[1], &cols1, sizeof(int));
                      write(fd1[1], &cols2, sizeof(int));                      
                      write(fd1[1], &rows1, sizeof(int));   
                      write(fd1[1], &rows2, sizeof(int));                     
                                          
                      for (i=0; i < rows1; i++) {
                        write(fd1[1], pin1[i],  cols1 * sizeof(int));
                      }
                      
                      for (i=0; i < rows2; i++) {
                        write(fd1[1], pin2[i],  cols2 * sizeof(int));
                      }
                      
                      for (i=0; i < rows1; i++) {
                        write(fd1[1], pin3[i],  cols2 * sizeof(int));
                      }                                                                            
                      
                      read(fd2[0], &pin3[i1][j1], sizeof(int));  //Diavazoume to stoixeio pou ypologisame sto pinaka 3 
                      
                      printf("Apo thn patrikh diergasia: ");     //Mhnyma pou emfanizei poio stoixeio ypologise h kathe fork
                      printf("\nfork %d: pinakas3[%d][%d]: %d\n",count, i1, j1, pin3[i1][j1]);   

                      close(fd1[1]);   //Kleinoume gia to pipe 1 to akro ths eggrafhs kai gia to pipe 2 ths anagnwshs
                      close(fd2[0]);
                  }
                  
                  if (cpid == 0) {
                          close(fd1[1]);   //Kleinoume gia to pipe 1 to akro ths eggrafhs kai gia to pipe 2 ths anagnwshs
                          close(fd2[0]);    
                          
                          int g,h, cols11, cols22, rows11,rows22, **arr1, **arr2, **arr3, i, j;
                          
                          read(fd1[0], &g, sizeof(int));
                          read(fd1[0], &h, sizeof(int));   //Diavazoume se kathe metavliti mesa sthn if ta stoixeia pou grapsame sthn
                          read(fd1[0], &cols11, sizeof(int));                    //patrikh diergasia
                          read(fd1[0], &cols22, sizeof(int));                                          
                          read(fd1[0], &rows11, sizeof(int));  
                          read(fd1[0], &rows22, sizeof(int));                 
                          
                          arr1 = (int **)malloc(rows11 * sizeof(int *));
                    //Dhmiourgoume  pinakes gia na diavasoume ta stoixeia twn pinakwn pou grapsame sthn patrikh
                          for (i = 0; i < rows11; i++) {
                             arr1[i] = (int *)malloc(cols11 * sizeof(int));
                             read(fd1[0], arr1[i], cols11 * sizeof(int));
                          }

                          arr2 = (int **)malloc(rows22 * sizeof(int *));
                          
                          for (i = 0; i < rows22; i++) {
                             arr2[i] = (int *)malloc(cols22 * sizeof(int));
                             read(fd1[0], arr2[i], cols22 * sizeof(int));
                          }
                          
                          arr3 = (int **)malloc(rows11 * sizeof(int *)); 
                          
                          for (i = 0; i < rows11; i++) {
                             arr3[i] = (int *)malloc(cols22 * sizeof(int));
                             read(fd1[0], arr3[i], cols22 * sizeof(int));
                          }
                                                    
                          for (k = 0; k < cols11; k++) {
                               arr3[g][h] = arr3[g][h] + arr1[g][k] * arr2[k][h]; //Kanoume ton pollaplasiasmo
                          }               
                          
                          write(fd2[1], &arr3[g][h], sizeof(int));    //Grafoume sto pipe 2 to stoixeio pou ypologisame
 
                          close(fd1[0]);
                          close(fd2[1]);    //Sto pipe 1 kleinoume to akro gia anagnwsi kai sto pipe 2 kleinoume to akro gia eggrafi
                          sleep(1);
                          exit(0);
                     }                                      
              }
        }       
        
        printf("\nO pinakas pou dhmiourgeitai me diastaseis %d, %d, apo ton pollaplasiasmo twn 2 allwn pinakwn einai: \n\n", rows1, cols2);
        for (i = 0; i < rows1; i++) {         //Emfanish telikou pinaka
              for (j = 0; j < cols2; j++) {
                    printf("%d\t", pin3[i][j]);
              }   
              printf("\n");
        }
       
        for (i = 0; i < rows2; i++) {  //Apodesmefsi twn 3 pinakwn
              free(pin2[i]);
        }
        free(pin2);
        
        for (i = 0; i < rows1; i++) {
            free(pin1[i]);
        }
        free(pin1);

        for (i = 0; i < rows1; i++) {
            free(pin3[i]);
        }
        free(pin3);
   
        return 0;
}
