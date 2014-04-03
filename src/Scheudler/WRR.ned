package pakietowiec.Scheudler;

simple WRR extends Scheduler
{
    parameters:
        int maxQueueSize = default(0);
        int queuesNum = default(1);
        string weights = default("1");
        
        @class(WRR);
}
