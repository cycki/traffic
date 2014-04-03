
package pakietowiec.Scheudler;

simple FIFO extends Scheduler
{
    parameters:
        int maxQueueSize = default(0);
        
        @class(FIFO);
}