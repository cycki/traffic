package scheduler;

simple AbstractScheduler
{
	parameters:
		volatile double processDelay @unit("s") = default(1s);
		
		@display("i=block/join");
	
	gates:
		input in[];
		output out;
}