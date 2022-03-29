/*
 * One-Liner-Sorting314 by Artjom Moisejev - Copyright (C) 2021 <domain_69@hotmail.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * See <http://www.gnu.org/licenses/>.
 */

/*
 * It's basically a one-liner ;)
 * 3-D View of this code: http://domain314.ddns.net/jsTest.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct iN{char l314;struct iN*n31415;}iN;typedef struct N314{iN*w31415;struct N314*n31415;int l31415;}N314;typedef struct h31415{N314*n314;int wA31415;}h31415;int ca31415(N314*m,N314*n){int vM31=m->w31415?m->w31415->l314:0;int vN31=n->w31415?n->w31415->l314:0;int d3141=vM31-vN31;return d3141;}int cl31415(N314*m,N314*n){int vM31=m?m->l31415:0;int vN31=n?n->l31415:0;int d3141=vM31-vN31;return d3141;}void cP3141592(N314*tz31,N314*te3141){iN*tz3141=tz31->w31415;int tA3=tz31->l31415;tz31->w31415=te3141->w31415;tz31->l31415=te3141->l31415;te3141->w31415=tz3141;te3141->l31415=tA3;}void sort(N314*h31415,int(*compare)(N314*,N314*),int d314ending_,int wA31415){for(int i=0;i<wA31415-1;i++){for(int j=0;j<wA31415;j++){N314*tz31=h31415,*te3141;for(int k=0;k<j;++k){tz31=tz31->n31415;}te3141=tz31->n31415;if(te3141==NULL){continue;}int d3141=compare(tz31,te3141);if(d3141<0&&d314ending_==0){cP3141592(tz31,te3141);}else if(d3141>0&&d314ending_==1){cP3141592(tz31,te3141);}}}}void iS314(h31415*h314){char cS314,cC3141;int d314=0;printf("\nSort (a)lphabetically or by (l)ength?");scanf(" %c",&cS314);printf("\nSort (a)scending or (d)escending?");scanf(" %c",&cC3141);if(cC3141=='a'){d314=1;}if(cS314=='a'){sort(h314->n314,ca31415,d314,h314->wA31415);}else{sort(h314->n314,cl31415,d314,h314->wA31415);}}iN*cN31415(char b3[]){iN*iN314=(iN*)malloc(sizeof(iN)),*te31=iN314;te31->l314=b3[0];for(int i=1;i<strlen(b3);i++){iN*newN314=malloc(sizeof(iN));newN314->l314=b3[i];newN314->n31415=NULL;te31->n31415=newN314;te31=te31->n31415;}return iN314;}N314*cN3141(char b3[]){N314*oN314=(N314*)malloc(sizeof(N314));oN314->w31415=cN31415(b3);oN314->l31415=strlen(b3);return oN314;}void aW3141(h31415*h314){printf("\nEnter Word: ");char b3[100];scanf(" %99s",b3);N314*te31=h314->n314;if (te31->w31415==NULL){te31->w31415=cN31415(b3);te31->l31415=strlen(b3);}else{while(te31->n31415!=NULL){te31=te31->n31415;}te31->n31415=cN3141(b3);te31->n31415->n31415=NULL;}h314->wA31415++;}void iW314(h31415*h314){int i31415;char b3[100];printf("\nEnter Index: ");scanf(" %d",&i31415);if (i31415==0&&h314->wA31415==0){aW3141(h314);}else{printf("\nEnter Word: ");scanf(" %99s",b3);N314*te31=h314->n314;if(i31415==0){N314*newN314=cN3141(b3);newN314->n31415=te31;h314->n314=newN314;}else{for(int i=0;i<i31415-1;i++){te31=te31->n31415;}N314*newN314=cN3141(b3),*secN314;secN314=te31->n31415;te31->n31415=newN314;newN314->n31415=secN314;}h314->wA31415++;}}void pL31415(h31415*h314){if(h314->wA31415==0){printf("\nempty list");}else{printf("\n");N314*n314=h314->n314;while(1){iN*iN314=n314->w31415;while(1){printf("%c", iN314->l314);if(iN314->n31415==NULL)break;iN314=iN314->n31415;}n314=n314->n31415;if(n314==NULL)break;printf(" ");}}}void rF314(iN*iN314){if(iN314!=NULL){if(iN314->n31415!=NULL){rF314(iN314->n31415);}}free(iN314);}void rF3145(N314*n3141){if(n3141->n31415!=NULL){rF3145(n3141->n31415);}rF314(n3141->w31415);free(n3141);}void fA314(h31415*h314){if(h314->n314!=NULL){rF3145(h314->n314);}free(h314);}void dW31415(h31415*h314){int i31415;N314*te31=h314->n314;printf("\nEnter Index: ");scanf(" %d",&i31415);if(i31415==0){h314->n314=h314->n314->n31415;rF314(te31->w31415);free(te31);}else{for(int i=0;i<i31415-1;i++){te31=te31->n31415;}N314*secN314;if(NULL==(secN314=te31->n31415->n31415)){rF314(te31->n31415->w31415);free(te31->n31415);te31->n31415=NULL;}else{rF314(te31->n31415->w31415);free(te31->n31415);te31->n31415=secN314;}}h314->wA31415--;if(h314->n314==NULL){N314*n314=(N314*)calloc(1,sizeof(N314));h314->n314=n314;}}void pM31415(h31415*h314){printf("\nChoose action: (a)ppend, (i)nsert, (d)elete, (s)ort, (p)rint, e(x)it: ");char choice;scanf(" %c",&choice);switch(choice){case'a':aW3141(h314); break;case'i':iW314(h314);break;case'd':dW31415(h314);break;case's':iS314(h314);break;case'p':pL31415(h314);break;case'x':h314->wA31415=-1;break;}}int main(){N314*n314=(N314*)calloc(1,sizeof(N314));h31415*h314=(h31415*)malloc(sizeof(h31415));h314->n314=n314;h314->wA31415=0;while(1){pM31415(h314);if(h314->wA31415==-1)break;}fA314(h314);return 0;}
