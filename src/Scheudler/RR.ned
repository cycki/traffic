package pakietowiec.Scheudler;

simple RR extends Scheduler
{
    parameters:
        int queueLength = default(5);
        int maxPriority = default(10);
        int maxQueueSize = default(0);

        @class(RR);
}