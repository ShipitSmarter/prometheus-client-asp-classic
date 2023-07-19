<%

Dim factory: Set factory = Server.CreateObject("SIS.PrometheusCOM.MetricFactory")

Dim labeledCounter: Set labeledCounter = factory.CreateLabeledCounter("name2", "help2", Array("label"))
Dim labeledCounterSample: Set labeledCounterSample = labeledCounter.WithLabels(Array("test"))
labeledCounterSample.Inc()

%>