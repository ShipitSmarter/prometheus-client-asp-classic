<%

Dim factory: Set factory = Server.CreateObject("SIS.PrometheusCOM.Metrics")

Dim labeledCounter: Set labeledCounter = factory.CreateLabeledCounter("name2", "help2", Array("label"))
Dim labeledCounterSample: Set labeledCounterSample = labeledCounter.WithLabels(Array("test"))
labeledCounterSample.Inc()

Dim gauge: Set gauge = factory.CreateGauge("gauge1", "gauge help")
gauge.Set(2.67)

%>