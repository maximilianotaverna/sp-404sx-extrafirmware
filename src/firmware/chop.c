#include "chop.h"
#ifndef CHOP_DIV
#define CHOP_DIV(a,b) ((unsigned)((int(*)(int,int))0x0C0F48AC)((int)(a),(int)(b)))
#endif
static int chop_count_ok(unsigned n){return n>=2&&n<=16;}
int chop_plan_even(unsigned start,unsigned end,unsigned slices,unsigned quantum,unsigned minimum,unsigned*out){
 unsigned span,units,base,rem;if(!chop_count_ok(slices))return CHOP_PLAN_BAD_COUNT;if(end<=start)return CHOP_PLAN_BAD_RANGE;
 if((quantum!=2&&quantum!=4)||((start|end|minimum)&(quantum-1)))return CHOP_PLAN_BAD_QUANTUM;
 span=end-start;units=CHOP_DIV(span,quantum);if(CHOP_DIV(units,slices)<CHOP_DIV(minimum,quantum))return CHOP_PLAN_TOO_SHORT;
 base=CHOP_DIV(units,slices);rem=units-base*slices;out[0]=start;for(unsigned i=1;i<slices;i++)out[i]=start+(base*i+CHOP_DIV(rem*i,slices))*quantum;out[slices]=end;return CHOP_PLAN_OK;
}
int chop_execute_even(unsigned source,unsigned first,unsigned start,unsigned end,unsigned slices,unsigned quantum,unsigned minimum,const struct chop_ops*ops){
 unsigned b[17];int r=chop_plan_even(start,end,slices,quantum,minimum,b);if(r)return r;
 if(!ops||!ops->destination_empty||!ops->copy_pad||!ops->set_range||!ops->commit||source>=120||first>=120||slices>120-first)return CHOP_EXEC_BAD_PAD;
 for(unsigned i=0;i<slices;i++){unsigned d=first+i;if(d==source)return CHOP_EXEC_SOURCE_OVERLAP;if(!ops->destination_empty(d))return CHOP_EXEC_DEST_OCCUPIED;}
 for(unsigned i=0;i<slices;i++){unsigned d=first+i;if(ops->copy_pad(source,d)){if(i&&ops->commit())return CHOP_EXEC_COMMIT_FAILED;return CHOP_EXEC_COPY_FAILED;}ops->set_range(d,b[i],b[i+1]);}
 return ops->commit()?CHOP_EXEC_COMMIT_FAILED:CHOP_EXEC_OK;
}
