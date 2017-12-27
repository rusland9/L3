#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define N 10

int main() {
  //Считывание текста
  char* text=(char*)calloc(N,sizeof(char));
  int size, c, n=1, sent=0, sent2=0;                     //size - кол-во символов в исходном тексте
  size=1;                                               //sent(2) - кол-во предложений в исходном(конечном) тексте
  c=getchar();
  *text=c;                                            //text(2) - исходный(конечный) текст 
  while (text[size] != '\n' ){                     //n - кол-во фрагментов памяти размером N выделенных под текст
      if (size == (N*n-1)){
        n++;
        text =(char*)realloc(text,N*n*sizeof(char));
    }
      c=getchar();
      text[size]=c;
      if (text[size] == ('.' || '?' || ';'))
          sent++;
      size++;       
  } 
  text[size+1]='\0';
  //Форматирование текста
  char* text2=(char*)calloc((size+sent+1),sizeof(char));
  int i, j, sw=0, t=0, space=0;                       //space - кол-во пробелов
  for (i=0, j=0; i<=size; i++){                      //sw - индикатор слова с числом внутри
      if (text[i] == ('.' || '?' || ';')){          //t - кол-во букв слова 
          sent2++;                                 //i(j) - нумерация символов в исходном(конечном) тексте 
          text[j]=text[i];
          text[j+1]='\n';
          j+=2;
          continue;
      }    
      if (sw && (!isspace(text[i]) || (text[i] != ('.' || '?' || ';'))))
          continue;
      if (isspace(text[i]) && (space>0)) 
          continue;
      if (isspace(text[i])){
          space++;
          t=0;
      }
      else{
          space=0;
          t++;
      }
      j++;
      if (isdigit(text[i]) && isalpha(text[i-1]) && isalpha(text[i+1])){
          j=j-t;
          sw=1;
      }
      else
          text[j-1]=text[i];          
  }
  //Вывод текста
  printf("%sКоличество предложений до %d и количество предложений после %d\n", text2, sent, sent2);
  free(text);
  free(text2);
  return 0;
}
