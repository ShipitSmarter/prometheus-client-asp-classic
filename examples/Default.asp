<% Option Explicit %>

<!-- #include virtual = "/prometheus-client/collector-registry.inc" -->
<!-- #include virtual = "/prometheus-client/counter.inc" -->
<!-- #include virtual = "/prometheus-client/internal/datetime.inc" -->

<%

Response.Write "Hello World<br><br>"

Dim registry
Set registry = New CollectorRegistry

Dim someCounter, someCounterBuilder
Set someCounterBuilder = New CounterBuilder
someCounterBuilder().withName("some_name").withHelp("Test description")
Set someCounter = someCounterBuilder.register(registry)

Dim testCounterSample
Set testCounterSample = someCounter.getWithoutLabels

testCounterSample.inc
testCounterSample.incByValue 5.75

Response.Write "Value: " & testCounterSample.Value & " Created: " & testCounterSample.Created & "<br><br>"

Dim someLabeledCounter, someLabeledCounterBuilder
Set someLabeledCounterBuilder = New CounterBuilder
someLabeledCounterBuilder().withName("some_name").withHelp("Test description").withLabelNames(Array("method", "code"))
Set someLabeledCounter = someLabeledCounterBuilder.register(registry)

Dim testLabeledCounterSample
someLabeledCounter.getForLabels(Array("post", "200")) ' Testing an already existing child
Set testLabeledCounterSample = someLabeledCounter.getForLabels(Array("post", "200"))

testLabeledCounterSample.inc
testLabeledCounterSample.incByValue 3.254

Response.Write "Value: " & testLabeledCounterSample.Value & " Created: " & testLabeledCounterSample.Created & "<br><br>"

%>