#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <sys/wait.h> 
#include <unistd.h>
#include <time.h>
#define buff_size 1024


struct product {  //dilosi domis product  me ta pedia poy mas zitoynte
  char description[1024];
  int price;
  int item_count;
};

int main() {

  int array1[20], array2[20];  //dilosh metabliton kai pinakon
  int  m1 = 0, m2 = 0, m3;
  int h;
  int tp = 0;
  int c1=0,c2=0,c3;
  char buffer1[1024];
  struct product catalog[20];
  int fd[2], errno;
  int wait1;
  int spr = 0;
  int c4 = 0;
  int  fd1[2];
  int l;
  char buffer8[1024];
  int k;
  int i,j;
  
  strcpy(buffer1, " "); //arxikopoioyme to buffer1  
  
  for (k = 0; k < 20; k++) {    //arxikopoioyme ta pedia twn stoixiwn toy pinaka typoy struct
      sprintf(catalog[k].description, "%d", k); //metatrepoyme kathe akereo apo 0-19 se string 
      catalog[k].price = rand() % 200 + 1; //dinoyme tyxaies times sto price  gia kathe stoixeio 
      catalog[k].item_count = 2; //thetoume to item.count se 2
  }
  
  for (i = 0; i < 5; i++) { //for gia kathe pelati
   for (j = 0; j < 10; j++) {  //gia kathe parageleia toy kathe pelati

   //dilonoyme 2 pipe kai stis if bgazoyme se periptosi sfalmatos na emfanisei minima  
      if (pipe(fd) < 0) {  
        printf("Error Number : %d\n", errno);
        perror("Error Description");
        return (-1);
      }
      
       if (pipe(fd1) < 0) {
        printf("Error Number : %d\n", errno); //kodikos sfalmatos
        perror("Error Description");  //idos sfalmatos
        return (-1);
       }
      
      pid_t cpid = fork(); //fork gia dimioyrgia kathe thigatrikis diergasias gia kathe paraggelia
      
      // se periptosi sfalmatos emfanizei minima oti apetyxe i for
       if (cpid < 0) {
        printf("Error Number : %d\n", errno);
        perror("Error Description\n");
        return (-2);
       }
       
      // kodikas thigatrikhs diergasias
      if (cpid == 0) {
        close(fd[0]); //klinoyme to akro tis anagnosis gia to proto pipe
        close(fd1[0]); //klinoyme to akro tis egrafis gia to deytero pipe
        printf("%s\n", buffer1);
        srand(time(NULL) + getpid()); //tyxea anathesi timon sti metabliti yo 0-19
        int yo = rand() % 20; 
        sprintf(buffer8, "%d", yo);  //metatrepoyme ton integer yo se xaratira kai ton metaferoyme sto buffer8
        write(fd[1], buffer8, strlen(buffer8) + 1);//grafoyme to periexomeno toy buffer8
        read(fd1[0], buffer1, strlen(buffer1) + 1);//diabazoyme apo to deytero pipe to minima toy buffer1 
        close(fd[1]);//klinoyme to akro tis eggrafis gia to proto pipe
        close(fd1[1]);//klinoyme to akro tis anagnosis gia to deytero pipe
        sleep(1);//anamoni 1 deyteroleptoy
        exit(0);
      }
    
      
      // kodikas patrikis diergasias
      wait1 = wait(NULL); //perimenoyme tin ektelesis thigatrikhs diergasias gia na ksekinisei to e-shop
      if (wait1 == cpid) {//an  i timi poy epistrefei to wait einai iso me to pid tis thigatrikhs pame sto kodika tis patrikhs
        close(fd1[1]);//klinoyme to akro tis eggrafhs gia to pipe 1
        close(fd[1]);//klinoyme to akro tis anagnosis gia to pipe 2
        read(fd[0], buffer8, strlen(buffer8) + 1); //diabazoyme  tin timi  toy buffer 8
        printf("For the client  at the position %d of the queue: \n", i);
        for (l = 0; l < 20; l++) { //prospelasi ton stoixiwn toy pinaka gia na vroume to sigkekrimeno proion me vash thn timh pou      edwse o pleaths
           if (strcmp(buffer8, catalog[l].description) == 0) {
              if (catalog[l].item_count > 0) { //an yparxei to proion kai to item count einai pano apo 0 ginete agora 
                strcpy(buffer1, "Purchase completed!\n"); // antigrafoyme sto buffer to minima tis epitixias 
                write(fd1[1], buffer1, strlen(buffer1) + 1);// to grafoyme sto buffer1
                c1++; //metritis poy metraei epitixi etimata
                printf("The product with description %s exists.\n", catalog[l].description);
                catalog[l].item_count = catalog[l].item_count - 1;  //meiosh toy item count kata 1
                printf("The item count is %d.\n", catalog[l].item_count);
                printf("The price is %d.\n", catalog[l].price);
                spr = spr + catalog[l].price; //enhmerosi tis synolikis timis poy tha plirosei o pelatis
                c3 = c1 + c2;
                c4++; //metritis poy mas deixnei  oti egine toylaxiston mia epitixis agora gia ton pelati
                break; // an brethei to proion kanoyme break gia na pame stin epomeni paraggelia
              }
              else { //an to item count einai 0 
                strcpy(buffer1,"Purchase failed!\n");//minima apotyxias
                write(fd1[1], buffer1, strlen(buffer1) + 1); //to grafoyme sto buffer 1 
                c2++;//metritis gia proionta pou zitithikan kai exoun exantlithei
                printf("The product with the description %s has been limited.\n", buffer8);
                c3 = c1 + c2; // sinolikos arithmos pelatwn 
                break; // an  brethei to proion kai exei exantlithei  kanoyme break gia na pame stin epomeni paraggelia
              } 
           }
        }
        close(fd1[0]);//klinoyme to akro tis egrafis gia to deytero pipe
        close(fd[0]);//klinoyme to akro tis anagnosis gia to proto pipe
      }
   }
   printf("\nThe total for the client %d is %d\n\n", i, spr);
   array1[i] = spr; //apothikeyoyme tin sinolikh timi gia ton kathe pelati sto array 1
   array2[i] = c4; //apothikyoyme ston array 2 tin timi toy c4 poy deixnei epitxia h apotixia tis paraggelias
   spr = 0; //midenismos tis sinolikhs timis kai toy c4 gia ton epomeno pelati
   c4 = 0;
  }
  
  for (h = 0; h < 5; h++) { 
    if (array2[h] > 0) { // an h timi poy apothikeutike ston pelati einai 1 tote emfanizei mnm synolikhs timhs
        tp = tp + array1[h]; //ipologismos   sinolikou kerdous gia to eshop
        printf("For client %d the total price is: %d\n", h + 1, array1[h]);
        m1++;//metritis gia pelates poy eksipiretithikan
        }
    else {  // diaforetika mnm apotyxias
        printf("The client %d made a purchased which failed!\n", h + 1);
        m2++;  // metritis gia pelates poy den eksipiretithikan kai einai se anamonh
        }
  }
  m3 = m1 + m2; //sinolikos arithmos pelaton 
  
  //sigketrotika minimata 
      printf("The total profit is %d.\n", tp);
      printf("The number of people who were serviced is %d.\n", m1);
      printf("The number of people who were not serviced and they are on queue is %d.\n", m2);
      printf("The total number of people is %d.\n", m3);    
      printf("The number of requests for products which were asked for and were limited %d.\n", c2);
      printf("The number of requests for products which were bought is %d.\n", c1);
      printf("The total number of requests for products is %d.\n", c3);
  return 0;
}
