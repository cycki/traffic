package pakietowiec.Generator;

simple AbstractGenerator
{
    parameters:
        @signal[interval](type="double");
        @statistic[packetInterval](title="packet intervals"; source="interval"; record=vector, histogram; interpolationmode="none");
        int priority = default(2);
        int length = default(50);
        int sessionId = default(intuniform(0, 10));
        double end @unit("s") = default(0s);
        int lowerPriority = default(0);					//Minimalny proiorytet	
        int upperPriority = default(0);					//Maksymalny priorytet
        int lowerSessionId = default(0);				//Minimalne id sesji
        int upperSessionId = default(10);				//Maksymalne id sesji
        int meanLength = default(200);					//Srednia wielkosc pakietu
        int stdDevLength = default(100);				//Odchylenie standardowe od sredniej wielkosci pakietu
    gates:
        output out;
}
