#ifndef SP404SX_CHOP_H
#define SP404SX_CHOP_H
#define CHOP_MAX_SLICES 16
enum chop_plan_result { CHOP_PLAN_OK=0, CHOP_PLAN_BAD_COUNT=-1, CHOP_PLAN_BAD_RANGE=-2, CHOP_PLAN_BAD_QUANTUM=-3, CHOP_PLAN_TOO_SHORT=-4 };
int chop_plan_even(unsigned start,unsigned end,unsigned slices,unsigned quantum,unsigned minimum,unsigned *boundaries);
struct chop_ops { int(*destination_empty)(unsigned); int(*copy_pad)(unsigned,unsigned); void(*set_range)(unsigned,unsigned,unsigned); int(*commit)(void); };
enum chop_execute_result { CHOP_EXEC_OK=0, CHOP_EXEC_BAD_PAD=-10, CHOP_EXEC_SOURCE_OVERLAP=-11, CHOP_EXEC_DEST_OCCUPIED=-12, CHOP_EXEC_COPY_FAILED=-13, CHOP_EXEC_COMMIT_FAILED=-14 };
int chop_execute_even(unsigned source,unsigned first_destination,unsigned start,unsigned end,unsigned slices,unsigned quantum,unsigned minimum,const struct chop_ops *ops);
#endif
