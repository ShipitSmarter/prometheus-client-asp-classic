<% Option Explicit %>

<!-- #include virtual = "/prometheus-client/collector-registry.inc" -->
<!-- #include virtual = "/prometheus-client/counter.inc" -->
<!-- #include virtual = "/prometheus-client/internal/datetime.inc" -->

<%

Response.Write "Hello World<br><br>"

Dim registry
Set registry = New CollectorRegistry

Dim someLabeledCounter, someLabeledCounterBuilder
Set someLabeledCounterBuilder = New CounterBuilder
someLabeledCounterBuilder().withName("some_name").withHelp("Test description").withLabelNames(Array("method", "code"))
Set someLabeledCounter = someLabeledCounterBuilder.register(registry)

Dim testLabeledCounterChild
someLabeledCounter.getForLabels(Array("post", "200")) ' Testing an already existing child
Set testLabeledCounterChild = someLabeledCounter.getForLabels(Array("post", "200"))

testLabeledCounterChild.inc
testLabeledCounterChild.incByValue 3.254

Response.Write "Value: " & testLabeledCounterChild.Value & " Created: " & testLabeledCounterChild.Created & "<br><br>"

someLabeledCounter.getForLabels(Array("get", "200"))
someLabeledCounter.getForLabels(Array("post", "500"))

Dim testMetricFamilySamples
Set testMetricFamilySamples = someLabeledCounter.collect()
Response.Write  "Family name: " & testMetricFamilySamples.Name & "<br>" & _
                "Type: " & testMetricFamilySamples.MetricType & "<br>" & _
                "Samples:<br>"
Dim iterSample
For Each iterSample in testMetricFamilySamples.Samples
    Response.Write  "&nbsp;&nbsp;Name: " & iterSample.Name & "<br>" & _
                    "&nbsp;&nbsp;Value: " & iterSample.Value & "<br>" & _
                    "&nbsp;&nbsp;Created: " & iterSample.Created & "<br>"
    Dim i, names, values
    names = iterSample.LabelNames
    values = iterSample.LabelValues
    For i = 0 To UBound(iterSample.LabelNames)
        Response.Write "&nbsp;&nbsp;" & names(i) & "=" & values(i) & "<br>"
    Next
    Response.Write "<br>"
Next

%>