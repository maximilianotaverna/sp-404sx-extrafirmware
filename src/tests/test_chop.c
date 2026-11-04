#include <stdio.h>
#include <string.h>
#define CHOP_DIV(a,b) ((a)/(b))
#include "chop.c"
static int fails,checks;
#define CHECK(c,w) do{checks++;if(!(c)){fails++;printf("FAIL: %s\n",w);}}while(0)
static int empty[120],copies,ranges,commits,failat,failcommit;static unsigned cs[16],cd[16],rs[16],re[16];
static int emp(unsigned p){return empty[p];}static int cp(unsigned s,unsigned d){if(copies==failat)return-1;cs[copies]=s;cd[copies++]=d;return 0;}static void range(unsigned p,unsigned s,unsigned e){(void)p;rs[ranges]=s;re[ranges++]=e;}static int commit(void){commits++;return failcommit?-1:0;}static const struct chop_ops ops={emp,cp,range,commit};
static void reset(void){memset(empty,1,sizeof empty);copies=ranges=commits=0;failat=-1;failcommit=0;}
static void plan(unsigned s,unsigned e,unsigned n,unsigned q,unsigned m){unsigned b[17],lo=~0u,hi=0;int r=chop_plan_even(s,e,n,q,m,b);CHECK(!r,"valid plan");if(r)return;CHECK(b[0]==s&&b[n]==e,"endpoints");for(unsigned i=0;i<n;i++){unsigned z=b[i+1]-b[i];CHECK(b[i]<b[i+1],"increasing");CHECK(!((b[i]|b[i+1])&(q-1)),"aligned");CHECK(z>=m,"minimum");if(z<lo)lo=z;if(z>hi)hi=z;}CHECK(hi-lo<=q,"remainder");}
int main(void){for(unsigned n=2;n<=16;n++){plan(0x200,0x20200,n,2,0x800);plan(0x400,0x80400,n,4,0x1000);plan(0x1000,0x123458,n,2,0x800);}unsigned b[17];CHECK(chop_plan_even(0,100000,1,2,0x800,b)==-1,"count low");CHECK(chop_plan_even(0,100000,17,2,0x800,b)==-1,"count high");CHECK(chop_plan_even(100,100,4,2,0x800,b)==-2,"range");CHECK(chop_plan_even(0x201,0x2200,4,2,0x800,b)==-3,"alignment");CHECK(chop_plan_even(0x200,0x21fc,4,2,0x800,b)==-4,"short");
 reset();CHECK(chop_execute_even(3,12,512,4608,4,2,512,&ops)==0,"execute");CHECK(copies==4&&ranges==4&&commits==1,"counts");for(unsigned i=0;i<4;i++){CHECK(cs[i]==3&&cd[i]==12+i,"sequence");CHECK(rs[i]==512+i*1024&&re[i]==512+(i+1)*1024,"ranges");}
 reset();empty[14]=0;CHECK(chop_execute_even(3,12,512,4608,4,2,512,&ops)==-12,"occupied");CHECK(!copies&&!commits,"preflight");reset();CHECK(chop_execute_even(13,12,512,4608,4,2,512,&ops)==-11,"overlap");reset();failat=2;CHECK(chop_execute_even(3,12,512,4608,4,2,512,&ops)==-13,"copy failure");CHECK(copies==2&&ranges==2&&commits==1,"partial commit");reset();failcommit=1;CHECK(chop_execute_even(3,12,512,4608,4,2,512,&ops)==-14,"commit failure");printf("%d checks, %d failures\n",checks,fails);return !!fails;}
